use std::collections::HashMap;
use crate::ast::{TypeExpr, Param};

#[derive(Debug, Clone, PartialEq)]
pub enum SymbolKind {
    Variable { type_expr: TypeExpr },
    Constant { type_expr: TypeExpr, value: String },
    Procedure { params: Vec<Param> },
    Function { params: Vec<Param>, return_type: String },
    Type { type_expr: TypeExpr },
}

pub struct SymbolTable {
    scopes: Vec<HashMap<String, SymbolKind>>,
}

impl SymbolTable {
    pub fn new() -> Self {
        Self {
            scopes: vec![HashMap::new()], // Global scope
        }
    }

    pub fn enter_scope(&mut self) {
        self.scopes.push(HashMap::new());
    }

    pub fn exit_scope(&mut self) {
        self.scopes.pop();
    }

    pub fn insert(&mut self, name: String, kind: SymbolKind) -> Result<(), String> {
        let current_scope = self.scopes.last_mut().unwrap();
        if current_scope.contains_key(&name) {
            return Err(format!("Symbol '{}' already declared in this scope", name));
        }
        current_scope.insert(name, kind);
        Ok(())
    }

    pub fn global_scope(&self) -> HashMap<String, SymbolKind> {
        self.scopes[0].clone()
    }

    pub fn lookup(&self, name: &str) -> Option<&SymbolKind> {
        for scope in self.scopes.iter().rev() {
            if let Some(kind) = scope.get(name) {
                return Some(kind);
            }
        }
        None
    }
}
