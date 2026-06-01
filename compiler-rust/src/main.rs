use clap::Parser;
use std::fs;
use std::collections::{HashMap, HashSet};
use std::path::{Path, PathBuf};
use lalrpop_util::lalrpop_mod;
use inkwell::context::Context;
use logos::Logos;
use crate::ast::CompilationUnit;

mod lexer;
mod ast;
mod symbol_table;
mod analyzer;
mod codegen;
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
}

fn main() {
    let args = Args::parse();
    let mut loader = ModuleLoader::new();
    
    match loader.load_recursively(Path::new(&args.file), args.verbose) {
        Ok(_) => {
            let sorted_units = loader.topological_sort().expect("Circular dependency detected");
            let context = Context::create();
            let mut module_interfaces = HashMap::new();
            let mut generated_ir_files = Vec::new();

            for name in sorted_units {
                let unit = loader.modules.get(&name).unwrap();
                match unit {
                    CompilationUnit::Program(p) => {
                        let mut analyzer = analyzer::SemanticAnalyzer::with_interfaces(module_interfaces.clone());
                        if let Err(e) = analyzer.analyze_program(p) {
                            eprintln!("Semantic error in program {}: {}", name, e);
                            std::process::exit(1);
                        }
                        
                        let mut codegen = codegen::CodeGen::with_interfaces(&context, &p.name, module_interfaces.clone());
                        if let Err(e) = codegen.gen_program(p) {
                            eprintln!("Codegen error in program {}: {}", name, e);
                            std::process::exit(1);
                        }
                        
                        let ir_path = format!("{}.ll", p.name);
                        codegen.module.print_to_file(&ir_path).expect("Failed to write LLVM IR");
                        generated_ir_files.push(ir_path);
                    }
                    CompilationUnit::Unit(u) => {
                        let mut analyzer = analyzer::SemanticAnalyzer::with_interfaces(module_interfaces.clone());
                        match analyzer.analyze_unit(u) {
                            Ok(interface) => {
                                module_interfaces.insert(name.clone(), interface);
                            }
                            Err(e) => {
                                eprintln!("Semantic error in unit {}: {}", name, e);
                                std::process::exit(1);
                            }
                        }

                        let mut codegen = codegen::CodeGen::with_interfaces(&context, &u.name, module_interfaces.clone());
                        if let Err(e) = codegen.gen_unit(u) {
                            eprintln!("Codegen error in unit {}: {}", name, e);
                            std::process::exit(1);
                        }

                        let ir_path = format!("{}.ll", u.name);
                        codegen.module.print_to_file(&ir_path).expect("Failed to write LLVM IR");
                        generated_ir_files.push(ir_path);
                    }
                }
            }

            println!("Compilation successful. Generated files: {:?}", generated_ir_files);
            println!("To link (example): clang {} -o {}", generated_ir_files.join(" "), args.output.as_deref().unwrap_or("output"));
        }
        Err(e) => {
            eprintln!("Error: {}", e);
            std::process::exit(1);
        }
    }
}

struct ModuleLoader {
    modules: HashMap<String, CompilationUnit>,
    loading_stack: Vec<String>,
}

impl ModuleLoader {
    fn new() -> Self {
        Self {
            modules: HashMap::new(),
            loading_stack: Vec::new(),
        }
    }

    fn load_recursively(&mut self, path: &Path, verbose: bool) -> Result<(), String> {
        let input = fs::read_to_string(path).map_err(|e| format!("Failed to read {}: {}", path.display(), e))?;
        if verbose {
            println!("Tokens for {}:", path.display());
            let mut debug_lexer = lexer::Token::lexer(&input);
            while let Some(token) = debug_lexer.next() {
                println!("  {:?} at {:?}", token, debug_lexer.span());
            }
        }
        let lexer = lexer::Lexer::new(&input);
        let parser = parser::CompilationUnitParser::new();
        
        let unit = parser.parse(lexer).map_err(|e| format!("Parse error in {}: {:?}", path.display(), e))?;
        let name = match &unit {
            CompilationUnit::Program(p) => p.name.to_lowercase(),
            CompilationUnit::Unit(u) => u.name.to_lowercase(),
        };

        if self.loading_stack.contains(&name) {
            return Err(format!("Circular dependency detected: {} -> {}", self.loading_stack.join(" -> "), name));
        }

        if self.modules.contains_key(&name) {
            return Ok(());
        }

        self.loading_stack.push(name.clone());

        let deps = match &unit {
            CompilationUnit::Program(p) => p.uses.clone().unwrap_or_default(),
            CompilationUnit::Unit(u) => {
                let mut d = u.interface.uses.clone().unwrap_or_default();
                d.extend(u.implementation.uses.clone().unwrap_or_default());
                d
            }
        };

        let base_dir = path.parent().unwrap_or(Path::new("."));
        for dep in deps {
            let dep_lower = dep.to_lowercase();
            if !self.modules.contains_key(&dep_lower) {
                // Try to find dep.pas or dep.pascalm
                let mut dep_path = base_dir.join(format!("{}.pas", dep_lower));
                if !dep_path.exists() {
                    dep_path = base_dir.join(format!("{}.pascalm", dep_lower));
                }
                if !dep_path.exists() {
                    return Err(format!("Could not find unit '{}' used in {}", dep, path.display()));
                }
                self.load_recursively(&dep_path, verbose)?;
            }
        }

        self.modules.insert(name, unit);
        self.loading_stack.pop();
        Ok(())
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

    fn visit(&self, name: &str, visited: &mut HashSet<String>, temp_visited: &mut HashSet<String>, sorted: &mut Vec<String>) -> bool {
        if temp_visited.contains(name) { return false; }
        if visited.contains(name) { return true; }

        temp_visited.insert(name.to_string());

        let unit = &self.modules[name];
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

        temp_visited.remove(name);
        visited.insert(name.to_string());
        sorted.push(name.to_string());
        true
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_parse_minimal() {
        let input = "program minimal; begin end.";
        let lexer = lexer::Lexer::new(input);
        let parser = parser::CompilationUnitParser::new();
        let result = parser.parse(lexer);
        assert!(result.is_ok(), "Failed to parse minimal program: {:?}", result.err());
    }

    #[test]
    fn test_scope_isolation() {
        let input = "
program scopes;
procedure p;
var local: integer;
begin
  local := 1;
end;
begin
  local := 2;
end.";
        let lexer = lexer::Lexer::new(input);
        let parser = parser::CompilationUnitParser::new();
        let unit = parser.parse(lexer).unwrap();
        if let CompilationUnit::Program(ast) = unit {
            let mut analyzer = analyzer::SemanticAnalyzer::new();
            let result = analyzer.analyze_program(&ast);
            assert!(result.is_err());
            assert!(result.unwrap_err().contains("Variable 'local' not declared"));
        } else { panic!("Expected program"); }
    }
}
