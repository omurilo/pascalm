use std::collections::HashMap;
use crate::ast::*;
use crate::typed_ast as typed;
use crate::symbol_table::{SymbolTable, SymbolKind};

pub struct SemanticAnalyzer {
    symbol_table: SymbolTable,
    current_block_labels: Vec<i64>,
    external_interfaces: HashMap<String, HashMap<String, SymbolKind>>,
}

impl SemanticAnalyzer {
    // ... setup_builtins etc ...
    
    fn convert_type(&self, te: &TypeExpr) -> typed::Type {
        match te {
            TypeExpr::Simple(name) => match name.to_lowercase().as_str() {
                "integer" => typed::Type::Integer,
                "real" => typed::Type::Real,
                "boolean" => typed::Type::Boolean,
                "char" => typed::Type::Char,
                "string" => typed::Type::String,
                _ => {
                    if let Some(SymbolKind::Type { type_expr }) = self.symbol_table.lookup(name) {
                        self.convert_type(type_expr)
                    } else {
                        typed::Type::Void // Error case
                    }
                }
            }
            TypeExpr::Array { element_type, .. } => typed::Type::Array {
                element_type: Box::new(self.convert_type(element_type)),
                size: 100, // Placeholder
            },
            TypeExpr::Record { fields, .. } => {
                let mut typed_fields = Vec::new();
                for f in fields {
                    let ft = self.convert_type(&f.type_expr);
                    for id in &f.ids {
                        typed_fields.push((id.clone(), ft.clone()));
                    }
                }
                typed::Type::Record { fields: typed_fields }
            }
            TypeExpr::Pointer(inner) => typed::Type::Pointer(Box::new(self.convert_type(inner))),
            TypeExpr::Set(inner) => typed::Type::Set(Box::new(self.convert_type(inner))),
            TypeExpr::Enum(ids) => typed::Type::Enum(ids.clone()),
            _ => typed::Type::Void,
        }
    }
    pub fn new() -> Self {
        let mut analyzer = Self {
            symbol_table: SymbolTable::new(),
            current_block_labels: Vec::new(),
            external_interfaces: HashMap::new(),
        };
        analyzer.setup_builtins();
        analyzer
    }

    pub fn with_interfaces(interfaces: HashMap<String, HashMap<String, SymbolKind>>) -> Self {
        let mut analyzer = Self::new();
        analyzer.external_interfaces = interfaces;
        analyzer
    }

    fn setup_builtins(&mut self) {
        let builtins = ["integer", "real", "boolean", "char", "string"];
        for t in builtins {
            let _ = self.symbol_table.insert(t.to_string(), SymbolKind::Type { 
                type_expr: TypeExpr::Simple(t.to_string()) 
            });
        }
        let builtin_procs = ["write", "writeln", "read", "readln"];
        for p in builtin_procs {
            let _ = self.symbol_table.insert(p.to_string(), SymbolKind::Procedure { 
                params: Vec::new() 
            });
        }
        let _ = self.symbol_table.insert("maxint".to_string(), SymbolKind::Constant {
            type_expr: TypeExpr::Simple("integer".to_string()),
            value: i64::MAX.to_string(),
        });
        let _ = self.symbol_table.insert("Chr".to_string(), SymbolKind::Function {
            params: vec![Param::Variable { is_var: false, ids: vec!["num".to_string()], type_name: "integer".to_string() }],
            return_type: "char".to_string(),
        });
        let _ = self.symbol_table.insert("Ord".to_string(), SymbolKind::Function {
            params: vec![Param::Variable { is_var: false, ids: vec!["val".to_string()], type_name: "char".to_string() }],
            return_type: "integer".to_string(),
        });

        // Runtime functions
        let _ = self.symbol_table.insert("RuntimeInit".to_string(), SymbolKind::Procedure { params: Vec::new() });
        let _ = self.symbol_table.insert("Sqrt".to_string(), SymbolKind::Function {
            params: vec![Param::Variable { is_var: false, ids: vec!["n".to_string()], type_name: "real".to_string() }],
            return_type: "real".to_string(),
        });
        let _ = self.symbol_table.insert("Halt".to_string(), SymbolKind::Procedure {
            params: vec![Param::Variable { is_var: false, ids: vec!["code".to_string()], type_name: "integer".to_string() }],
        });
    }

    pub fn analyze_program(&mut self, program: &Program) -> Result<(), String> {
        self.import_uses(&program.uses)?;
        self.analyze_block(&program.block)
    }

    pub fn analyze_unit(&mut self, unit: &Unit) -> Result<HashMap<String, SymbolKind>, String> {
        // Analysis of Interface
        self.import_uses(&unit.interface.uses)?;
        
        if let Some(constants) = &unit.interface.constants {
            for c in constants {
                let inferred_type = self.get_expr_type(&c.value)?;
                self.symbol_table.insert(c.name.clone(), SymbolKind::Constant { 
                    type_expr: inferred_type,
                    value: format!("{:?}", c.value) 
                })?;
            }
        }
        if let Some(types) = &unit.interface.types {
            for t in types {
                self.symbol_table.insert(t.name.clone(), SymbolKind::Type { type_expr: t.type_expr.clone() })?;
            }
        }
        if let Some(variables) = &unit.interface.variables {
            for v in variables {
                for id in &v.ids {
                    self.symbol_table.insert(id.clone(), SymbolKind::Variable { type_expr: v.type_expr.clone() })?;
                }
            }
        }
        if let Some(headers) = &unit.interface.headers {
            for h in headers {
                match h {
                    ProcFuncDecl::Procedure { name, params, .. } => {
                        self.symbol_table.insert(name.clone(), SymbolKind::Procedure { params: params.clone().unwrap_or_default() })?;
                    }
                    ProcFuncDecl::Function { name, params, return_type, .. } => {
                        self.symbol_table.insert(name.clone(), SymbolKind::Function { 
                            params: params.clone().unwrap_or_default(), 
                            return_type: return_type.clone() 
                        })?;
                    }
                }
            }
        }

        let interface_symbols = self.symbol_table.global_scope();

        // Analysis of Implementation
        self.import_uses(&unit.implementation.uses)?;
        
        if let Some(constants) = &unit.implementation.constants {
            for c in constants {
                let inferred_type = self.get_expr_type(&c.value)?;
                self.symbol_table.insert(c.name.clone(), SymbolKind::Constant { 
                    type_expr: inferred_type,
                    value: format!("{:?}", c.value) 
                })?;
            }
        }
        if let Some(types) = &unit.implementation.types {
            for t in types {
                self.symbol_table.insert(t.name.clone(), SymbolKind::Type { type_expr: t.type_expr.clone() })?;
            }
        }
        if let Some(variables) = &unit.implementation.variables {
            for v in variables {
                for id in &v.ids {
                    self.symbol_table.insert(id.clone(), SymbolKind::Variable { type_expr: v.type_expr.clone() })?;
                }
            }
        }
        if let Some(bodies) = &unit.implementation.bodies {
            for b in bodies {
                match b {
                    ProcFuncDecl::Procedure { name: _, params, block_or_forward } => {
                        if let BlockOrForward::Block(block) = block_or_forward {
                            self.symbol_table.enter_scope();
                            self.add_params_to_scope(params)?;
                            self.analyze_block(block)?;
                            self.symbol_table.exit_scope();
                        }
                    }
                    ProcFuncDecl::Function { name, params, return_type, block_or_forward } => {
                        if let BlockOrForward::Block(block) = block_or_forward {
                            self.symbol_table.enter_scope();
                            self.add_params_to_scope(params)?;
                            self.symbol_table.insert(name.clone(), SymbolKind::Variable { 
                                type_expr: TypeExpr::Simple(return_type.clone()) 
                            })?;
                            self.analyze_block(block)?;
                            self.symbol_table.exit_scope();
                        }
                    }
                }
            }
        }

        if let Some(init) = &unit.initialization {
            for stmt in init { self.analyze_stmt(stmt)?; }
        }
        
        Ok(interface_symbols)
    }

    fn import_uses(&mut self, uses: &Option<Vec<String>>) -> Result<(), String> {
        if let Some(units) = uses {
            for unit_name in units {
                let unit_lower = unit_name.to_lowercase();
                if let Some(interface) = self.external_interfaces.get(&unit_lower).cloned() {
                    for (name, kind) in interface {
                        let _ = self.symbol_table.insert(name, kind);
                    }
                } else {
                    return Err(format!("Unit '{}' not found in dependencies", unit_name));
                }
            }
        }
        Ok(())
    }

    fn analyze_block(&mut self, block: &Block) -> Result<(), String> {
        let old_labels = std::mem::replace(&mut self.current_block_labels, block.labels.clone().unwrap_or_default());
        
        if let Some(constants) = &block.constants {
            for c in constants {
                let inferred_type = self.get_expr_type(&c.value)?;
                self.symbol_table.insert(c.name.clone(), SymbolKind::Constant { 
                    type_expr: inferred_type,
                    value: format!("{:?}", c.value) 
                })?;
            }
        }
        if let Some(types) = &block.types {
            for t in types {
                self.symbol_table.insert(t.name.clone(), SymbolKind::Type { 
                    type_expr: t.type_expr.clone() 
                })?;
                // Register enum members as constants
                if let TypeExpr::Enum(ids) = &t.type_expr {
                    for (i, id) in ids.iter().enumerate() {
                        self.symbol_table.insert(id.clone(), SymbolKind::Constant {
                            type_expr: TypeExpr::Simple(t.name.clone()),
                            value: i.to_string(),
                        })?;
                    }
                }
            }
        }
        if let Some(variables) = &block.variables {
            for v in variables {
                for id in &v.ids {
                    self.symbol_table.insert(id.clone(), SymbolKind::Variable { type_expr: v.type_expr.clone() })?;
                }
            }
        }
        if let Some(procs) = &block.procedures_functions {
            // First pass: register all proc/func headers
            for p in procs {
                match p {
                    ProcFuncDecl::Procedure { name, params, .. } => {
                        if self.symbol_table.lookup(name).is_none() {
                            self.symbol_table.insert(name.clone(), SymbolKind::Procedure { params: params.clone().unwrap_or_default() })?;
                        }
                    }
                    ProcFuncDecl::Function { name, params, return_type, .. } => {
                        if self.symbol_table.lookup(name).is_none() {
                            self.symbol_table.insert(name.clone(), SymbolKind::Function { 
                                params: params.clone().unwrap_or_default(), 
                                return_type: return_type.clone() 
                            })?;
                        }
                    }
                }
            }
            // Second pass: analyze bodies
            for p in procs {
                match p {
                    ProcFuncDecl::Procedure { params, block_or_forward, .. } => {
                        if let BlockOrForward::Block(b) = block_or_forward {
                            self.symbol_table.enter_scope();
                            self.add_params_to_scope(params)?;
                            self.analyze_block(b)?;
                            self.symbol_table.exit_scope();
                        }
                    }
                    ProcFuncDecl::Function { name, params, return_type, block_or_forward } => {
                        if let BlockOrForward::Block(b) = block_or_forward {
                            self.symbol_table.enter_scope();
                            self.add_params_to_scope(params)?;
                            // Allow assigning to function name for return value
                            self.symbol_table.insert(name.clone(), SymbolKind::Variable { 
                                type_expr: TypeExpr::Simple(return_type.clone()) 
                            })?;
                            self.analyze_block(b)?;
                            self.symbol_table.exit_scope();
                        }
                    }
                }
            }
        }
        for stmt in &block.statements {
            self.analyze_stmt(stmt)?;
        }
        
        self.current_block_labels = old_labels;
        Ok(())
    }

    fn add_params_to_scope(&mut self, params: &Option<Vec<Param>>) -> Result<(), String> {
        if let Some(params) = params {
            for p in params {
                match p {
                    Param::Variable { ids, type_name, .. } => {
                        for id in ids {
                            self.symbol_table.insert(id.clone(), SymbolKind::Variable { type_expr: TypeExpr::Simple(type_name.clone()) })?;
                        }
                    }
                    Param::Procedure { id, params } => {
                        self.symbol_table.insert(id.clone(), SymbolKind::Procedure { params: params.clone().unwrap_or_default() })?;
                    }
                    Param::Function { id, params, return_type } => {
                        self.symbol_table.insert(id.clone(), SymbolKind::Function { 
                            params: params.clone().unwrap_or_default(), 
                            return_type: return_type.clone() 
                        })?;
                    }
                }
            }
        }
        Ok(())
    }

    fn add_record_fields_to_scope(&mut self, fields: &[VarDecl], variant_part: Option<&VariantPart>) -> Result<(), String> {
        for f in fields {
            for id in &f.ids {
                self.symbol_table.insert(id.clone(), SymbolKind::Variable { type_expr: f.type_expr.clone() })?;
            }
        }
        if let Some(vp) = variant_part {
            if let Some(tag) = &vp.tag_field {
                self.symbol_table.insert(tag.clone(), SymbolKind::Variable { type_expr: TypeExpr::Simple(vp.tag_type.clone()) })?;
            }
            for variant in &vp.variants {
                self.add_record_fields_to_scope(&variant.fields, variant.nested_variant.as_deref())?;
            }
        }
        Ok(())
    }

    fn analyze_stmt(&mut self, stmt: &Stmt) -> Result<(), String> {
        match stmt {
            Stmt::Compound(stmts) => {
                for s in stmts { self.analyze_stmt(s)?; }
            }
            Stmt::Assignment { target, value } => {
                let target_type = self.get_expr_type(target)?;
                let value_type = self.get_expr_type(value)?;
                if !self.is_compatible(&target_type, &value_type) {
                    return Err(format!("Incompatible types in assignment: target={:?}, value={:?}", target_type, value_type));
                }
            }
            Stmt::If { condition, then_stmt, else_stmt } => {
                let cond_type = self.get_expr_type(condition)?;
                if !self.is_boolean(&cond_type) { return Err(format!("If condition must be boolean, found {:?}", cond_type)); }
                self.analyze_stmt(then_stmt)?;
                if let Some(e) = else_stmt { self.analyze_stmt(e)?; }
            }
            Stmt::While { condition, body } => {
                let cond_type = self.get_expr_type(condition)?;
                if !self.is_boolean(&cond_type) { return Err(format!("While condition must be boolean, found {:?}", cond_type)); }
                self.analyze_stmt(body)?;
            }
            Stmt::Repeat { body, until } => {
                for s in body { self.analyze_stmt(s)?; }
                let until_type = self.get_expr_type(until)?;
                if !self.is_boolean(&until_type) { return Err(format!("Repeat until condition must be boolean, found {:?}", until_type)); }
            }
            Stmt::For { id, start, end, body, .. } => {
                let id_type = self.get_variable_type(&Variable::Id(id.clone()))?;
                let start_type = self.get_expr_type(start)?;
                let end_type = self.get_expr_type(end)?;
                if !self.is_integer(&id_type) || !self.is_integer(&start_type) || !self.is_integer(&end_type) {
                    return Err("For loop bounds and variable must be integer".to_string());
                }
                self.analyze_stmt(body)?;
            }
            Stmt::ProcedureCall { name, args } => {
                match self.symbol_table.lookup(name) {
                    Some(SymbolKind::Procedure { .. }) | Some(SymbolKind::Function { .. }) | Some(SymbolKind::Variable { .. }) => {
                        if let Some(args) = args {
                            for arg in args { self.get_expr_type(arg)?; }
                        }
                    }
                    _ => return Err(format!("Procedure '{}' not declared or invalid", name)),
                }
            }
            Stmt::Labeled(_, s) => self.analyze_stmt(s)?,
            Stmt::Goto(l) => {
                if !self.current_block_labels.contains(l) {
                    return Err(format!("Label {} not declared in this block", l));
                }
            }
            Stmt::Case { expr, items, else_stmt } => {
                self.get_expr_type(expr)?;
                for item in items {
                    for label in &item.labels { self.get_expr_type(label)?; }
                    self.analyze_stmt(&item.stmt)?;
                }
                if let Some(e) = else_stmt { self.analyze_stmt(e)?; }
            }
            Stmt::With { ids, body } => {
                self.symbol_table.enter_scope();
                for id_expr in ids {
                    let te = self.get_expr_type(id_expr)?;
                    let resolved = self.resolve_type(&te)?;
                    if let TypeExpr::Record { fields, variant_part } = resolved {
                        self.add_record_fields_to_scope(&fields, variant_part.as_ref())?;
                    }
                }
                self.analyze_stmt(body)?;
                self.symbol_table.exit_scope();
            }
            _ => {} 
        }
        Ok(())
    }

    fn get_expr_type(&self, expr: &Expr) -> Result<TypeExpr, String> {
        match expr {
            Expr::Integer(_) => Ok(TypeExpr::Simple("integer".to_string())),
            Expr::Real(_) => Ok(TypeExpr::Simple("real".to_string())),
            Expr::Char(_) => Ok(TypeExpr::Simple("char".to_string())),
            Expr::String(_) => Ok(TypeExpr::Simple("string".to_string())),
            Expr::Boolean(_) => Ok(TypeExpr::Simple("boolean".to_string())),
            Expr::Variable(v) => {
                match self.get_variable_type(&**v) {
                    Ok(t) => Ok(t),
                    Err(e) => {
                        // Allow procedure/function names as "variables" for passing as parameters
                        if let Variable::Id(id) = &**v {
                            match self.symbol_table.lookup(id) {
                                Some(SymbolKind::Procedure { .. }) => Ok(TypeExpr::Simple("procedure".to_string())),
                                Some(SymbolKind::Function { return_type, .. }) => Ok(TypeExpr::Simple(return_type.clone())),
                                _ => Err(e),
                            }
                        } else {
                            Err(e)
                        }
                    }
                }
            }
            Expr::Binary { op, left, right } => {
                let lt = self.get_expr_type(left)?;
                let rt = self.get_expr_type(right)?;
                self.resolve_binop_type(op, &lt, &rt)
            }
            Expr::Unary { op, expr } => {
                let t = self.get_expr_type(expr)?;
                match op {
                    UnaryOp::Not => if self.is_boolean(&t) { Ok(t) } else { Err("NOT requires boolean".to_string()) }
                    _ => if self.is_numeric(&t) { Ok(t) } else { Err("Unary +/- requires numeric".to_string()) }
                }
            }
            Expr::FunctionCall { name, .. } => {
                match self.symbol_table.lookup(name) {
                    Some(SymbolKind::Function { return_type, .. }) => Ok(TypeExpr::Simple(return_type.clone())),
                    Some(SymbolKind::Variable { .. }) => Ok(TypeExpr::Simple("integer".to_string())), // Recursion
                    _ => Err(format!("Function '{}' not declared", name)),
                }
            }
            Expr::Set(_) => Ok(TypeExpr::Simple("SET".to_string())),
            Expr::Range(s, e) => {
                let _st = self.get_expr_type(s)?;
                let _et = self.get_expr_type(e)?;
                Ok(TypeExpr::Subrange { start: *s.clone(), end: *e.clone() })
            }
            _ => Ok(TypeExpr::Simple("unknown".to_string())),
        }
    }

    fn find_field_in_record(&self, fields: &[VarDecl], variant_part: Option<&VariantPart>, field: &str) -> Option<TypeExpr> {
        for f in fields {
            if f.ids.contains(&field.to_string()) { return Some(f.type_expr.clone()); }
        }
        if let Some(vp) = variant_part {
            if let Some(tag) = &vp.tag_field {
                if tag == field { return Some(TypeExpr::Simple(vp.tag_type.clone())); }
            }
            for variant in &vp.variants {
                if let Some(t) = self.find_field_in_record(&variant.fields, variant.nested_variant.as_deref(), field) {
                    return Some(t);
                }
            }
        }
        None
    }

    fn get_variable_type(&self, var: &Variable) -> Result<TypeExpr, String> {
        match var {
            Variable::Id(id) => {
                match self.symbol_table.lookup(id) {
                    Some(SymbolKind::Variable { type_expr }) => Ok(type_expr.clone()),
                    Some(SymbolKind::Constant { type_expr, .. }) => Ok(type_expr.clone()),
                    Some(SymbolKind::Function { return_type, .. }) => Ok(TypeExpr::Simple(return_type.clone())),
                    _ => Err(format!("Variable '{}' not declared", id)),
                }
            }
            Variable::MemberAccess { record, field } => {
                let te = self.get_expr_type(record)?;
                let resolved = self.resolve_type(&te)?;
                if let TypeExpr::Record { fields, variant_part } = resolved {
                    if let Some(t) = self.find_field_in_record(&fields, variant_part.as_ref(), field) {
                        Ok(t)
                    } else {
                        Err(format!("Field '{}' not found in record", field))
                    }
                } else {
                    Err("Member access on non-record".to_string())
                }
            }
            Variable::ArrayAccess { array, .. } => {
                let te = self.get_expr_type(array)?;
                let resolved = self.resolve_type(&te)?;
                if let TypeExpr::Array { element_type, .. } = resolved {
                    Ok(*element_type.clone())
                } else {
                    Err("Array access on non-array".to_string())
                }
            }
            Variable::PointerDeref(p) => {
                let te = self.get_expr_type(p)?;
                let resolved = self.resolve_type(&te)?;
                if let TypeExpr::Pointer(inner) = resolved {
                    Ok(*inner.clone())
                } else {
                    Err("Deref on non-pointer".to_string())
                }
            }
        }
    }

    fn resolve_type(&self, te: &TypeExpr) -> Result<TypeExpr, String> {
        match te {
            TypeExpr::Simple(name) => {
                match name.as_str() {
                    "integer" | "real" | "boolean" | "char" | "string" => Ok(te.clone()),
                    _ => {
                        if let Some(SymbolKind::Type { type_expr }) = self.symbol_table.lookup(name) {
                            match type_expr {
                                TypeExpr::Simple(inner_name) if inner_name == name => Ok(te.clone()),
                                _ => self.resolve_type(type_expr),
                            }
                        } else { Ok(te.clone()) }
                    }
                }
            }
            _ => Ok(te.clone()),
        }
    }

    fn resolve_binop_type(&self, op: &BinOp, lt: &TypeExpr, rt: &TypeExpr) -> Result<TypeExpr, String> {
        let lt_name = self.get_type_name(lt)?;
        let rt_name = self.get_type_name(rt)?;

        let resolved_lt = self.resolve_type(lt).unwrap_or(lt.clone());
        let resolved_rt = self.resolve_type(rt).unwrap_or(rt.clone());
        let is_set_op = matches!(resolved_lt, TypeExpr::Set(_)) || matches!(resolved_rt, TypeExpr::Set(_)) || lt_name == "SET" || rt_name == "SET";

        match op {
            BinOp::Add => {
                if is_set_op { return Ok(TypeExpr::Simple("SET".to_string())); }
                if (lt_name == "string" || lt_name == "char") && (rt_name == "string" || rt_name == "char") {
                    return Ok(TypeExpr::Simple("string".to_string()));
                }
                if lt_name == "integer" && rt_name == "integer" { Ok(TypeExpr::Simple("integer".to_string())) }
                else { Ok(TypeExpr::Simple("real".to_string())) }
            }
            BinOp::Sub | BinOp::Mul => {
                if is_set_op { return Ok(TypeExpr::Simple("SET".to_string())); }
                if lt_name == "integer" && rt_name == "integer" { Ok(TypeExpr::Simple("integer".to_string())) }
                else { Ok(TypeExpr::Simple("real".to_string())) }
            }
            BinOp::Div | BinOp::Mod => {
                if lt_name == "integer" && rt_name == "integer" { Ok(TypeExpr::Simple("integer".to_string())) }
                else { Ok(TypeExpr::Simple("real".to_string())) }
            }
            BinOp::FloatDiv => Ok(TypeExpr::Simple("real".to_string())),
            BinOp::And | BinOp::Or => Ok(TypeExpr::Simple("boolean".to_string())),
            _ => Ok(TypeExpr::Simple("boolean".to_string())),
        }
    }

    fn get_type_name(&self, te: &TypeExpr) -> Result<String, String> {
        let resolved = self.resolve_type(te)?;
        match resolved {
            TypeExpr::Simple(name) => Ok(name),
            _ => Ok("complex".to_string()),
        }
    }

    fn is_compatible(&self, target: &TypeExpr, source: &TypeExpr) -> bool {
        let mut tn = self.get_type_name(target).unwrap_or_default();
        let mut sn = self.get_type_name(source).unwrap_or_default();
        
        // Resolve underlying types for sets and others
        let resolved_target = self.resolve_type(target).unwrap_or(target.clone());
        let resolved_source = self.resolve_type(source).unwrap_or(source.clone());

        if tn == sn { return true; }
        if tn == "real" && sn == "integer" { return true; }
        if tn == "string" && sn == "char" { return true; }
        
        // Enum compatibility: allow same named type
        if let (TypeExpr::Enum(_), _) = (&resolved_target, &resolved_source) {
             if tn == sn { return true; }
        }

        if tn == "SET" || sn == "SET" || matches!(resolved_target, TypeExpr::Set(_)) || matches!(resolved_source, TypeExpr::Set(_)) {
            match (&resolved_target, &resolved_source) {
                (TypeExpr::Set(_), TypeExpr::Set(_)) => return true,
                (TypeExpr::Set(_), TypeExpr::Simple(n)) if n == "SET" => return true,
                (TypeExpr::Simple(n), TypeExpr::Set(_)) if n == "SET" => return true,
                _ => {}
            }
        }
        false
    }

    fn is_boolean(&self, te: &TypeExpr) -> bool { self.get_type_name(te).unwrap_or_default() == "boolean" }
    fn is_integer(&self, te: &TypeExpr) -> bool { self.get_type_name(te).unwrap_or_default() == "integer" }
    fn is_numeric(&self, te: &TypeExpr) -> bool { 
        let n = self.get_type_name(te).unwrap_or_default();
        n == "integer" || n == "real"
    }
}
