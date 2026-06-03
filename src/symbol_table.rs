use std::collections::HashMap;
use crate::ast::{TypeExpr, Param, Span};

use std::fmt;

#[derive(Debug, Clone, PartialEq)]
pub enum SymbolKind {
    Variable { type_expr: TypeExpr },
    Constant { type_expr: TypeExpr, value: String },
    Procedure { params: Vec<Param> },
    Function { params: Vec<Param>, return_type: String },
    Type { type_expr: TypeExpr },
}

impl fmt::Display for SymbolKind {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            SymbolKind::Variable { type_expr } => write!(f, "{}", type_expr.node),
            SymbolKind::Constant { type_expr, value } => write!(f, "{} = {}", type_expr.node, value),
            SymbolKind::Procedure { params } => {
                write!(f, "procedure")?;
                if !params.is_empty() {
                    write!(f, "(")?;
                    for (i, p) in params.iter().enumerate() {
                        if i > 0 { write!(f, "; ")?; }
                        write!(f, "{}", p.node)?;
                    }
                    write!(f, ")")?;
                }
                Ok(())
            }
            SymbolKind::Function { params, return_type } => {
                write!(f, "function")?;
                if !params.is_empty() {
                    write!(f, "(")?;
                    for (i, p) in params.iter().enumerate() {
                        if i > 0 { write!(f, "; ")?; }
                        write!(f, "{}", p.node)?;
                    }
                    write!(f, ")")?;
                }
                write!(f, ": {}", return_type)
            }
            SymbolKind::Type { type_expr } => write!(f, "{}", type_expr.node),
        }
    }
}

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
    pub scopes: Vec<HashMap<String, SymbolId>>,
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

    pub fn insert(&mut self, name: String, kind: SymbolKind, span: Span) -> Result<SymbolId, String> {
        let current_scope = self.scopes.last_mut().unwrap();
        if current_scope.contains_key(&name) {
            return Err(format!("Symbol '{}' already declared in this scope", name));
        }
        
        let id = self.all_symbols.len();
        let info = SymbolInfo {
            id,
            name: name.clone(),
            kind,
            span,
        };
        self.all_symbols.push(info);
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

    pub fn lookup(&self, name: &str) -> Option<&SymbolInfo> {
        for scope in self.scopes.iter().rev() {
            if let Some(&id) = scope.get(name) {
                return Some(&self.all_symbols[id]);
            }
        }
        None
    }

    pub fn get_symbol(&self, id: SymbolId) -> Option<&SymbolInfo> {
        self.all_symbols.get(id)
    }

    pub fn get_all_symbols(&self) -> &[SymbolInfo] {
        &self.all_symbols
    }
}
