use crate::ast::{Param, Span, TypeExpr};
use std::collections::HashMap;
use std::fmt;

#[derive(Debug, Clone, PartialEq)]
pub enum SymbolKind {
    Variable {
        type_expr: TypeExpr,
    },
    Constant {
        type_expr: TypeExpr,
        value: String,
    },
    Procedure {
        params: Vec<Param>,
        external_name: Option<String>,
    },
    Function {
        params: Vec<Param>,
        return_type: String,
        external_name: Option<String>,
    },
    Type {
        type_expr: TypeExpr,
    },
}

/// Short human-readable rendering of a type expression, used by the LSP hover.
fn type_expr_label(te: &TypeExpr) -> String {
    match te {
        TypeExpr::Simple(s) => s.clone(),
        TypeExpr::Array { .. } => "array".to_string(),
        TypeExpr::Record { .. } => "record".to_string(),
        TypeExpr::Pointer(_) => "pointer".to_string(),
        TypeExpr::Set(_) => "set".to_string(),
        TypeExpr::File(_) => "file".to_string(),
        TypeExpr::Subrange { .. } => "subrange".to_string(),
        TypeExpr::Enum(_) => "enum".to_string(),
        TypeExpr::Procedure { .. } => "procedure".to_string(),
        TypeExpr::Function { .. } => "function".to_string(),
    }
}

impl fmt::Display for SymbolKind {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            SymbolKind::Variable { type_expr } => write!(f, "{}", type_expr_label(type_expr)),
            SymbolKind::Constant { type_expr, value } => {
                write!(f, "{} = {}", type_expr_label(type_expr), value)
            }
            SymbolKind::Procedure { .. } => write!(f, "procedure"),
            SymbolKind::Function { return_type, .. } => write!(f, "function: {}", return_type),
            SymbolKind::Type { type_expr } => write!(f, "{}", type_expr_label(type_expr)),
        }
    }
}

/// Index into [`SymbolTable::all_symbols`]. Used by the LSP to identify a symbol
/// independently of the scope it currently lives in.
pub type SymbolId = usize;

#[derive(Debug, Clone)]
pub struct SymbolInfo {
    pub id: SymbolId,
    pub name: String,
    pub kind: SymbolKind,
    pub span: Span,
}

#[derive(Debug)]
pub struct SymbolTable {
    scopes: Vec<HashMap<String, SymbolId>>,
    /// Every symbol ever inserted, keyed by `SymbolId`. Scopes only hold ids, so
    /// a symbol's metadata (kind, definition span) survives `exit_scope` and stays
    /// reachable by the language server.
    pub all_symbols: Vec<SymbolInfo>,
}

impl SymbolTable {
    pub fn new() -> Self {
        Self {
            scopes: vec![HashMap::new()], // Global scope
            all_symbols: Vec::new(),
        }
    }

    pub fn enter_scope(&mut self) {
        self.scopes.push(HashMap::new());
    }

    pub fn exit_scope(&mut self) {
        self.scopes.pop();
    }

    pub fn insert(
        &mut self,
        name: String,
        kind: SymbolKind,
        span: Span,
    ) -> Result<SymbolId, String> {
        let current_scope = self.scopes.last_mut().unwrap();
        if current_scope.contains_key(&name) {
            return Err(format!("Symbol '{}' already declared in this scope", name));
        }
        let id = self.all_symbols.len();
        self.all_symbols.push(SymbolInfo {
            id,
            name: name.clone(),
            kind,
            span,
        });
        current_scope.insert(name, id);
        Ok(id)
    }

    pub fn global_scope(&self) -> HashMap<String, SymbolKind> {
        let mut result = HashMap::new();
        for (name, &id) in &self.scopes[0] {
            result.insert(name.clone(), self.all_symbols[id].kind.clone());
        }
        result
    }

    pub fn lookup(&self, name: &str) -> Option<&SymbolKind> {
        self.lookup_id(name).map(|id| &self.all_symbols[id].kind)
    }

    /// Like [`lookup`], but returns the stable id so the analyzer can record a
    /// reference from a use-site span to the resolved symbol.
    pub fn lookup_id(&self, name: &str) -> Option<SymbolId> {
        for scope in self.scopes.iter().rev() {
            if let Some(&id) = scope.get(name) {
                return Some(id);
            }
        }
        None
    }
}
