use clap::{Parser, Subcommand};
use inkwell::context::Context;
use pascalm::ast::CompilationUnit;
use pascalm::loader::{resolve_uses, ModuleLoader, IMPLICIT_RUNTIME_UNIT};
use pascalm::stdlib_assets::get_stdlib_assets;
use pascalm::{analyzer, codegen, formatter, lexer, parser};
use std::collections::{HashMap, HashSet};
use std::fs;
use std::path::{Path, PathBuf};

#[derive(Subcommand, Debug)]
#[command(args_conflicts_with_subcommands = true)]
pub enum Commands {
    #[command(arg_required_else_help = true)]
    Fmt {
        #[arg(long)]
        all: bool,

        #[arg(short, long = "file")]
        file_path: Option<String>,
    },
}

#[derive(Parser, Debug)]
#[command(author, version, about, long_about = None)]
struct Args {
    #[arg(short, long)]
    file: Option<String>,

    #[arg(short, long)]
    output: Option<String>,

    #[arg(short, long, default_value_t = false)]
    verbose: bool,

    #[arg(short = 'L', long)]
    lib_path: Vec<String>,

    #[command(subcommand)]
    command: Commands,
}

fn main() {
    let args = Args::parse();

    let mut loader = ModuleLoader::new();
    loader.search_paths = args.lib_path.iter().map(PathBuf::from).collect();

    match args.command {
        Commands::Fmt { all, file_path } => {
            // TODO: resolve all files and format when all is true or format file of file_path
            if all {
                // TODO: scan all files and format
                fn visit_dir(path: &Path) -> std::io::Result<()> {
                    for entry in fs::read_dir(path)? {
                        let entry = entry?;
                        let path = entry.path();

                        if path.is_dir() {
                            visit_dir(&path)?;
                        } else {
                            let source = match path.extension().and_then(|e| e.to_str()) {
                                Some("pas") | Some("pascalm") => std::fs::read_to_string(&path)?,
                                _ => continue,
                            };
                            let lexer = lexer::Lexer::new(&source);
                            let parser = parser::CompilationUnitParser::new();
                            let Ok(unit) = parser.parse(lexer) else {
                                continue;
                            };

                            let formatted = formatter::format_compilation_unit(&unit, &source);
                            if formatted == source {
                                continue;
                            }

                            let _ = std::fs::write(path, formatted);
                        }
                    }

                    Ok(())
                }

                let _ = visit_dir(Path::new("."));
                return;
            }

            let file = file_path.expect("file is required");
            // TODO: retrieve file and format
            // formatter::format_compilation_unit()
            let source = std::fs::read_to_string(&file).unwrap();

            let lexer = lexer::Lexer::new(&source);
            let parser = parser::CompilationUnitParser::new();
            let Ok(unit) = parser.parse(lexer) else {
                return ();
            };

            let formatted = formatter::format_compilation_unit(&unit, &source);
            if formatted == source {
                return ();
            }

            let _ = std::fs::write(file, formatted);
            return;
        }
    }

    let file = args.file.expect("file is required");

    match loader.load_recursively(Path::new(&file), args.verbose) {
        Ok(_) => {
            let sorted_units = loader
                .topological_sort()
                .expect("Circular dependency detected");
            let context = Context::create();
            let mut module_interfaces = HashMap::new();
            let mut generated_ir_files = Vec::new();
            let mut used_builtin_libs = HashSet::new();

            for id in sorted_units {
                let is_builtin = loader.embedded_units.contains_key(&id);
                if is_builtin {
                    used_builtin_libs.insert(id.clone());
                }
                let loaded = loader.modules.get(&id).unwrap();
                let uses_map = loaded.uses_map.clone();
                let unit = loaded.unit.clone();
                match &unit {
                    CompilationUnit::Program(p) => {
                        let mut resolved_p = p.clone();
                        resolved_p.uses = resolve_uses(&p.uses, &uses_map);
                        let mut analyzer =
                            analyzer::SemanticAnalyzer::with_interfaces(module_interfaces.clone());
                        match analyzer.analyze_program(&resolved_p) {
                            Ok(typed_ast) => {
                                let mut codegen = codegen::CodeGen::with_interfaces(
                                    &context,
                                    &p.name,
                                    module_interfaces.clone(),
                                );
                                if let Err(e) = codegen.gen_program(typed_ast) {
                                    eprintln!("Codegen error in program {}: {}", id, e);
                                    std::process::exit(1);
                                }

                                let ir_path = format!("{}.ll", p.name);
                                codegen
                                    .module
                                    .print_to_file(&ir_path)
                                    .expect("Failed to write LLVM IR");
                                generated_ir_files.push(ir_path);
                            }
                            Err(e) => {
                                eprintln!("Semantic error in program {}: {}", id, e);
                                std::process::exit(1);
                            }
                        }
                    }
                    CompilationUnit::Unit(u) => {
                        let mut resolved_u = u.clone();
                        resolved_u.interface.uses = resolve_uses(&u.interface.uses, &uses_map);
                        resolved_u.implementation.uses =
                            resolve_uses(&u.implementation.uses, &uses_map);
                        let mut analyzer =
                            analyzer::SemanticAnalyzer::with_interfaces(module_interfaces.clone());
                        match analyzer.analyze_unit(&resolved_u) {
                            Ok((interface, typed_block)) => {
                                module_interfaces.insert(id.clone(), interface);

                                if !is_builtin {
                                    // The module id (a sanitized canonical path)
                                    // names the unit's LLVM module so its
                                    // `<id>_init` symbol is unique even across
                                    // units that share a `unit` name.
                                    let mut codegen = codegen::CodeGen::with_interfaces(
                                        &context,
                                        &id,
                                        module_interfaces.clone(),
                                    );
                                    if let Err(e) = codegen.gen_unit(typed_block) {
                                        eprintln!("Codegen error in unit {}: {}", id, e);
                                        std::process::exit(1);
                                    }

                                    let ir_path = format!("{}.ll", id);
                                    codegen
                                        .module
                                        .print_to_file(&ir_path)
                                        .expect("Failed to write LLVM IR");
                                    generated_ir_files.push(ir_path);
                                }
                            }
                            Err(e) => {
                                eprintln!("Semantic error in unit {}: {}", id, e);
                                std::process::exit(1);
                            }
                        }
                    }
                }
            }

            if !generated_ir_files.is_empty() {
                let output_exe = args.output.unwrap_or_else(|| "output".to_string());
                println!("Linking into executable '{}'...", output_exe);

                let mut clang_args = generated_ir_files.clone();
                let mut temp_libs = Vec::new();

                // The `system` runtime is always linked last (lowest-level), so
                // emit the explicitly-used libs first and skip it here to avoid
                // linking it twice if it was also `use`d directly.
                let mut libs_to_link: Vec<String> = used_builtin_libs
                    .into_iter()
                    .filter(|l| l != IMPLICIT_RUNTIME_UNIT)
                    .collect();
                libs_to_link.push(IMPLICIT_RUNTIME_UNIT.to_string());

                for lib_name in libs_to_link {
                    if let Some(asset) = get_stdlib_assets().iter().find(|a| a.name == lib_name) {
                        let temp_path = std::env::temp_dir().join(format!("lib{}_tmp.a", lib_name));
                        fs::write(&temp_path, asset.archive)
                            .expect("Failed to write temporary library");
                        clang_args.push(temp_path.to_str().unwrap().to_string());
                        temp_libs.push(temp_path);
                    }
                }

                let status = std::process::Command::new("clang")
                    .args(&clang_args)
                    .arg("-o")
                    .arg(&output_exe)
                    .arg("-lm")
                    .arg("-lpthread")
                    .status();

                match status {
                    Ok(s) if s.success() => println!("Linking successful!"),
                    Ok(s) => {
                        eprintln!("Linker failed with exit code: {}", s.code().unwrap_or(1));
                        std::process::exit(1);
                    }
                    Err(e) => {
                        eprintln!("Failed to run clang: {}", e);
                        std::process::exit(1);
                    }
                }

                // Cleanup temp files
                for lib in temp_libs {
                    let _ = fs::remove_file(lib);
                }
            }
        }
        Err(e) => {
            eprintln!("Error loading modules: {}", e);
            std::process::exit(1);
        }
    }
}
