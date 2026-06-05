//! Module loader: resolves a program's `uses` graph across files (and embedded
//! stdlib units), parses each module once, detects circular dependencies, and
//! produces a topological order for analysis/codegen.
//!
//! Shared by the compiler binary and the language server.

use crate::ast::CompilationUnit;
use crate::lexer;
use crate::parser;
use crate::stdlib_assets::get_stdlib_assets;
use std::collections::{HashMap, HashSet};
use std::fs;
use std::path::{Path, PathBuf};

/// The `system` unit provides the language runtime intrinsics and is linked
/// into every program implicitly, whether or not it is explicitly `use`d.
pub const IMPLICIT_RUNTIME_UNIT: &str = "system";

/// A parsed module plus the resolution of its `uses` specs to module ids,
/// computed in the importing module's directory context.
pub struct LoadedModule {
    pub unit: CompilationUnit,
    /// use-spec (lowercased) -> module id
    pub uses_map: HashMap<String, String>,
}

pub struct ModuleLoader {
    /// key: module id
    pub modules: HashMap<String, LoadedModule>,
    /// builtin name -> source
    pub embedded_units: HashMap<String, String>,
    pub search_paths: Vec<PathBuf>,
    /// module ids currently being loaded (cycle detection)
    loading_stack: Vec<String>,
}

impl Default for ModuleLoader {
    fn default() -> Self {
        Self::new()
    }
}

impl ModuleLoader {
    pub fn new() -> Self {
        let mut loader = Self {
            modules: HashMap::new(),
            embedded_units: HashMap::new(),
            search_paths: Vec::new(),
            loading_stack: Vec::new(),
        };

        for asset in get_stdlib_assets() {
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
    pub fn file_module_id(path: &Path) -> Result<String, String> {
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

    pub fn load_recursively(
        &mut self,
        source_path: &Path,
        verbose: bool,
    ) -> Result<String, String> {
        let id = Self::file_module_id(source_path)?;
        if self.modules.contains_key(&id) {
            return Ok(id);
        }
        let input = fs::read_to_string(source_path)
            .map_err(|e| format!("Failed to read {}: {}", source_path.display(), e))?;
        let base_dir = source_path.parent().unwrap_or(Path::new(".")).to_path_buf();
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
            use logos::Logos;
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

    pub fn topological_sort(&self) -> Option<Vec<String>> {
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
pub fn resolve_uses(
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
