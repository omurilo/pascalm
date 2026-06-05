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

include!(concat!(env!("OUT_DIR"), "/libs.rs"));

/// The `system` unit provides the language runtime intrinsics and is linked
/// into every program implicitly, whether or not it is explicitly `use`d.
const IMPLICIT_RUNTIME_UNIT: &str = "system";

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

/// A parsed module plus the resolution of its `uses` specs to module ids,
/// computed in the importing module's directory context.
struct LoadedModule {
    unit: CompilationUnit,
    uses_map: HashMap<String, String>, // use-spec (lowercased) -> module id
}

struct ModuleLoader {
    modules: HashMap<String, LoadedModule>, // key: module id
    embedded_units: HashMap<String, String>, // builtin name -> source
    search_paths: Vec<PathBuf>,
    loading_stack: Vec<String>, // module ids currently being loaded
}

impl ModuleLoader {
    fn new() -> Self {
        let mut loader = Self {
            modules: HashMap::new(),
            embedded_units: HashMap::new(),
            search_paths: Vec::new(),
            loading_stack: Vec::new(),
        };

        let assets = get_stdlib_assets();
        for asset in assets {
            loader
                .embedded_units
                .insert(asset.name.to_lowercase(), asset.source.to_string());
        }

        loader
    }

    /// A module's stable identity. File modules use a sanitized form of their
    /// canonical path, so the same file reached via different `uses` paths is
    /// one module, while two distinct files that share a `unit` name stay
    /// separate. Builtin (embedded) units are identified by their name.
    fn file_module_id(path: &Path) -> Result<String, String> {
        let canonical = fs::canonicalize(path)
            .map_err(|e| format!("Failed to resolve {}: {}", path.display(), e))?;
        Ok(Self::sanitize_id(&canonical.to_string_lossy()))
    }

    fn sanitize_id(raw: &str) -> String {
        let mut out = String::from("m_");
        for c in raw.chars() {
            if c.is_ascii_alphanumeric() {
                out.push(c.to_ascii_lowercase());
            } else {
                out.push('_');
            }
        }
        out
    }

    fn load_recursively(&mut self, source_path: &Path, verbose: bool) -> Result<String, String> {
        let id = Self::file_module_id(source_path)?;
        if self.modules.contains_key(&id) {
            return Ok(id);
        }
        let input = fs::read_to_string(source_path)
            .map_err(|e| format!("Failed to read {}: {}", source_path.display(), e))?;
        let base_dir = source_path
            .parent()
            .unwrap_or(Path::new("."))
            .to_path_buf();
        self.load_unit(id, input, base_dir, verbose)
    }

    fn load_unit(
        &mut self,
        id: String,
        input: String,
        base_dir: PathBuf,
        verbose: bool,
    ) -> Result<String, String> {
        if self.loading_stack.contains(&id) {
            return Err(format!(
                "Circular dependency detected: {} -> {}",
                self.loading_stack.join(" -> "),
                id
            ));
        }
        if self.modules.contains_key(&id) {
            return Ok(id);
        }

        if verbose {
            println!("Tokens for {}:", id);
            let mut debug_lexer = lexer::Token::lexer(&input);
            while let Some(token) = debug_lexer.next() {
                println!("  {:?} at {:?}", token, debug_lexer.span());
            }
        }
        let lexer = lexer::Lexer::new(&input);
        let parser = parser::CompilationUnitParser::new();
        let mut unit = parser
            .parse(lexer)
            .map_err(|e| format!("Parser failed: {:?}", e))?;

        // Every program implicitly uses the `system` unit so that the language
        // intrinsics (Sqrt, Halt, ...) are in scope without an explicit `uses`.
        if id != IMPLICIT_RUNTIME_UNIT {
            if let CompilationUnit::Program(p) = &mut unit {
                let uses = p.uses.get_or_insert_with(Vec::new);
                if !uses.iter().any(|u| u.to_lowercase() == IMPLICIT_RUNTIME_UNIT) {
                    uses.insert(0, IMPLICIT_RUNTIME_UNIT.to_string());
                }
            }
        }

        self.loading_stack.push(id.clone());

        let specs: Vec<String> = match &unit {
            CompilationUnit::Program(p) => p.uses.clone().unwrap_or_default(),
            CompilationUnit::Unit(u) => {
                let mut d = u.interface.uses.clone().unwrap_or_default();
                d.extend(u.implementation.uses.clone().unwrap_or_default());
                d
            }
        };

        let mut uses_map: HashMap<String, String> = HashMap::new();
        for spec in specs {
            let spec_lower = spec.to_lowercase();
            if uses_map.contains_key(&spec_lower) {
                continue;
            }
            let dep_id = self.resolve_dependency(&spec_lower, &base_dir, verbose)?;
            uses_map.insert(spec_lower, dep_id);
        }

        self.modules
            .insert(id.clone(), LoadedModule { unit, uses_map });
        self.loading_stack.pop();
        Ok(id)
    }

    /// Resolves a single `uses` spec to a module id, loading it if necessary.
    /// Embedded builtin units win by name; otherwise the spec is treated as a
    /// path relative to the importer's directory, then the `-L` search paths.
    fn resolve_dependency(
        &mut self,
        spec_lower: &str,
        base_dir: &Path,
        verbose: bool,
    ) -> Result<String, String> {
        if let Some(content) = self.embedded_units.get(spec_lower).cloned() {
            let id = spec_lower.to_string();
            if !self.modules.contains_key(&id) {
                self.load_unit(id.clone(), content, PathBuf::from("."), verbose)?;
            }
            return Ok(id);
        }

        let mut candidates = vec![base_dir.to_path_buf()];
        candidates.extend(self.search_paths.clone());
        for dir in candidates {
            for ext in ["pas", "pascalm"] {
                let file_path = dir.join(format!("{}.{}", spec_lower, ext));
                if file_path.exists() {
                    return self.load_recursively(&file_path, verbose);
                }
            }
        }
        Err(format!("Unit {} not found", spec_lower))
    }

    fn topological_sort(&self) -> Option<Vec<String>> {
        let mut sorted = Vec::new();
        let mut visited = HashSet::new();
        let mut temp_visited = HashSet::new();

        for id in self.modules.keys() {
            if !self.visit(id, &mut visited, &mut temp_visited, &mut sorted) {
                return None;
            }
        }
        Some(sorted)
    }

    fn visit(
        &self,
        id: &str,
        visited: &mut HashSet<String>,
        temp_visited: &mut HashSet<String>,
        sorted: &mut Vec<String>,
    ) -> bool {
        if temp_visited.contains(id) {
            return false;
        }
        if visited.contains(id) {
            return true;
        }

        temp_visited.insert(id.to_string());

        if let Some(module) = self.modules.get(id) {
            for dep_id in module.uses_map.values() {
                if !self.visit(dep_id, visited, temp_visited, sorted) {
                    return false;
                }
            }
        }

        temp_visited.remove(id);
        visited.insert(id.to_string());
        sorted.push(id.to_string());
        true
    }
}

/// Maps a unit's `uses` specs to their resolved module ids for the analyzer
/// and codegen, preserving order. Unknown specs fall back to their lowercase
/// form (e.g. builtins that were resolved by name).
fn resolve_uses(
    specs: &Option<Vec<String>>,
    uses_map: &HashMap<String, String>,
) -> Option<Vec<String>> {
    specs.as_ref().map(|v| {
        v.iter()
            .map(|u| {
                uses_map
                    .get(&u.to_lowercase())
                    .cloned()
                    .unwrap_or_else(|| u.to_lowercase())
            })
            .collect()
    })
}
