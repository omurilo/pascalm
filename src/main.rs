use crate::ast::CompilationUnit;
use clap::Parser;
use inkwell::context::Context;
use lalrpop_util::lalrpop_mod;
use logos::Logos;
use std::collections::{HashMap, HashSet};
use std::fs;
use std::path::{Path, PathBuf};

mod analyzer;
mod ast;
mod codegen;
mod lexer;
mod symbol_table;
mod typed_ast;
lalrpop_mod!(pub parser);

#[derive(Parser, Debug)]
#[command(author, version, about, long_about = None)]
struct Args {
    #[arg(short, long)]
    file: String,

    #[arg(short, long)]
    output: Option<String>,

    #[arg(short, long, default_value_t = false)]
    verbose: bool,

    #[arg(short = 'L', long)]
    lib_path: Vec<String>,
}

const RUNTIME_BC: &[u8] = include_bytes!(concat!(env!("OUT_DIR"), "/runtime_lib.bc"));
include!(concat!(env!("OUT_DIR"), "/libs.rs"));

fn main() {
    let args = Args::parse();
    let mut loader = ModuleLoader::new();
    loader.search_paths = args.lib_path.iter().map(PathBuf::from).collect();

    match loader.load_recursively(Path::new(&args.file), args.verbose) {
        Ok(_) => {
            let sorted_units = loader
                .topological_sort()
                .expect("Circular dependency detected");
            let context = Context::create();
            let mut module_interfaces = HashMap::new();
            let mut generated_ir_files = Vec::new();
            let mut used_builtin_libs = HashSet::new();

            for name in sorted_units {
                let is_builtin = loader.embedded_units.contains_key(&name);
                if is_builtin {
                    used_builtin_libs.insert(name.clone());
                }
                let unit = loader.modules.get(&name).unwrap();
                match unit {
                    CompilationUnit::Program(p) => {
                        let mut resolved_p = p.clone();
                        if let Some(uses) = &p.uses {
                            resolved_p.uses = Some(
                                uses.iter()
                                    .map(|u| {
                                        loader
                                            .name_mapping
                                            .get(&u.to_lowercase())
                                            .cloned()
                                            .unwrap_or(u.to_lowercase())
                                    })
                                    .collect(),
                            );
                        }
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
                                    eprintln!("Codegen error in program {}: {}", name, e);
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
                                eprintln!("Semantic error in program {}: {}", name, e);
                                std::process::exit(1);
                            }
                        }
                    }
                    CompilationUnit::Unit(u) => {
                        let mut resolved_u = u.clone();
                        if let Some(uses) = &u.interface.uses {
                            resolved_u.interface.uses = Some(
                                uses.iter()
                                    .map(|u| {
                                        loader
                                            .name_mapping
                                            .get(&u.to_lowercase())
                                            .cloned()
                                            .unwrap_or(u.to_lowercase())
                                    })
                                    .collect(),
                            );
                        }
                        if let Some(uses) = &u.implementation.uses {
                            resolved_u.implementation.uses = Some(
                                uses.iter()
                                    .map(|u| {
                                        loader
                                            .name_mapping
                                            .get(&u.to_lowercase())
                                            .cloned()
                                            .unwrap_or(u.to_lowercase())
                                    })
                                    .collect(),
                            );
                        }
                        let mut analyzer =
                            analyzer::SemanticAnalyzer::with_interfaces(module_interfaces.clone());
                        match analyzer.analyze_unit(&resolved_u) {
                            Ok((interface, typed_block)) => {
                                module_interfaces.insert(name.clone(), interface);

                                if !is_builtin {
                                    let mut codegen = codegen::CodeGen::with_interfaces(
                                        &context,
                                        &u.name,
                                        module_interfaces.clone(),
                                    );
                                    if let Err(e) = codegen.gen_unit(typed_block) {
                                        eprintln!("Codegen error in unit {}: {}", name, e);
                                        std::process::exit(1);
                                    }

                                    let ir_path = format!("{}.ll", u.name);
                                    codegen
                                        .module
                                        .print_to_file(&ir_path)
                                        .expect("Failed to write LLVM IR");
                                    generated_ir_files.push(ir_path);
                                }
                            }
                            Err(e) => {
                                eprintln!("Semantic error in unit {}: {}", name, e);
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

                for lib_name in used_builtin_libs {
                    if let Some(asset) = get_stdlib_assets().iter().find(|a| a.name == lib_name) {
                        let temp_path = std::env::temp_dir().join(format!("lib{}_tmp.a", lib_name));
                        fs::write(&temp_path, asset.archive)
                            .expect("Failed to write temporary library");
                        clang_args.push(temp_path.to_str().unwrap().to_string());
                        temp_libs.push(temp_path);
                    }
                }

                let runtime_path = std::env::temp_dir().join("runtime_lib.bc");
                fs::write(&runtime_path, RUNTIME_BC).expect("Failed to write temporary runtime");
                clang_args.push(runtime_path.to_str().unwrap().to_string());

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
                let _ = fs::remove_file(runtime_path);
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

struct ModuleLoader {
    modules: HashMap<String, CompilationUnit>,
    embedded_units: HashMap<String, String>,
    search_paths: Vec<PathBuf>,
    loading_stack: Vec<String>,
    name_mapping: HashMap<String, String>,
}

impl ModuleLoader {
    fn new() -> Self {
        let mut loader = Self {
            modules: HashMap::new(),
            embedded_units: HashMap::new(),
            search_paths: Vec::new(),
            loading_stack: Vec::new(),
            name_mapping: HashMap::new(),
        };

        let assets = get_stdlib_assets();
        for asset in assets {
            loader
                .embedded_units
                .insert(asset.name.to_lowercase(), asset.source.to_string());
        }

        loader
    }

    fn load_recursively(&mut self, source_path: &Path, verbose: bool) -> Result<String, String> {
        let input = fs::read_to_string(source_path)
            .map_err(|e| format!("Failed to read {}: {}", source_path.display(), e))?;
        self.parse_and_load(input, source_path.to_path_buf(), verbose)
    }

    pub fn parse_and_load(
        &mut self,
        input: String,
        source_path: PathBuf,
        verbose: bool,
    ) -> Result<String, String> {
        if verbose {
            println!("Tokens for {}:", source_path.display());
            let mut debug_lexer = lexer::Token::lexer(&input);
            while let Some(token) = debug_lexer.next() {
                println!("  {:?} at {:?}", token, debug_lexer.span());
            }
        }
        let lexer = lexer::Lexer::new(&input);
        let parser = parser::CompilationUnitParser::new();
        let unit = parser
            .parse(lexer)
            .map_err(|e| format!("Parser failed: {:?}", e))?;

        let actual_name = match &unit {
            CompilationUnit::Program(p) => p.name.clone(),
            CompilationUnit::Unit(u) => u.name.clone(),
        }
        .to_lowercase();

        if self.loading_stack.contains(&actual_name) {
            return Err(format!(
                "Circular dependency detected: {} -> {}",
                self.loading_stack.join(" -> "),
                actual_name
            ));
        }

        if self.modules.contains_key(&actual_name) {
            return Ok(actual_name);
        }

        self.loading_stack.push(actual_name.clone());

        let deps = match &unit {
            CompilationUnit::Program(p) => p.uses.clone().unwrap_or_default(),
            CompilationUnit::Unit(u) => {
                let mut d = u.interface.uses.clone().unwrap_or_default();
                d.extend(u.implementation.uses.clone().unwrap_or_default());
                d
            }
        };

        let base_dir = source_path.parent().unwrap_or(Path::new("."));

        for dep in deps {
            let dep_lower = dep.to_lowercase();
            if !self.modules.contains_key(&dep_lower) && !self.name_mapping.contains_key(&dep_lower)
            {
                if let Some(content) = self.embedded_units.get(&dep_lower) {
                    let virtual_path = PathBuf::from(format!("builtin://{}.pas", dep_lower));
                    let real_unit_name =
                        self.parse_and_load(content.to_string(), virtual_path, verbose)?;
                    self.name_mapping.insert(dep_lower.clone(), real_unit_name);
                    continue;
                }

                let mut found = false;
                let mut paths_to_check = vec![base_dir.to_path_buf()];
                paths_to_check.extend(self.search_paths.clone());

                for path in paths_to_check {
                    let file_path = path.join(format!("{}.pas", dep_lower));
                    if file_path.exists() {
                        let real_unit_name = self.load_recursively(&file_path, verbose)?;
                        self.name_mapping.insert(dep_lower.clone(), real_unit_name);
                        found = true;
                        break;
                    }
                    let file_path_pascalm = path.join(format!("{}.pascalm", dep_lower));
                    if file_path_pascalm.exists() {
                        let real_unit_name = self.load_recursively(&file_path_pascalm, verbose)?;
                        self.name_mapping.insert(dep_lower.clone(), real_unit_name);
                        found = true;
                        break;
                    }
                }

                if !found {
                    return Err(format!("Unit {} not found", dep));
                }
            }
        }

        self.modules.insert(actual_name.clone(), unit);
        self.loading_stack.pop();
        Ok(actual_name)
    }

    fn topological_sort(&self) -> Option<Vec<String>> {
        let mut sorted = Vec::new();
        let mut visited = HashSet::new();
        let mut temp_visited = HashSet::new();

        for name in self.modules.keys() {
            if !self.visit(name, &mut visited, &mut temp_visited, &mut sorted) {
                return None;
            }
        }
        Some(sorted)
    }

    fn visit(
        &self,
        name: &str,
        visited: &mut HashSet<String>,
        temp_visited: &mut HashSet<String>,
        sorted: &mut Vec<String>,
    ) -> bool {
        let actual_name = self
            .name_mapping
            .get(name)
            .unwrap_or(&name.to_string())
            .to_string();

        if temp_visited.contains(&actual_name) {
            return false;
        }
        if visited.contains(&actual_name) {
            return true;
        }

        temp_visited.insert(actual_name.clone());

        let unit = self.modules.get(&actual_name).unwrap();
        let deps = match unit {
            CompilationUnit::Program(p) => p.uses.clone().unwrap_or_default(),
            CompilationUnit::Unit(u) => {
                let mut d = u.interface.uses.clone().unwrap_or_default();
                d.extend(u.implementation.uses.clone().unwrap_or_default());
                d
            }
        };

        for dep in deps {
            if !self.visit(&dep.to_lowercase(), visited, temp_visited, sorted) {
                return false;
            }
        }

        temp_visited.remove(&actual_name);
        visited.insert(actual_name.clone());
        sorted.push(actual_name);
        true
    }
}
