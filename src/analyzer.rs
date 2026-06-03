use std::collections::HashMap;
use crate::ast::*;
use crate::typed_ast as typed;
use crate::symbol_table::{SymbolTable, SymbolKind, SymbolId};

#[derive(Debug, Clone)]
pub struct Diagnostic {
    pub span: Span,
    pub message: String,
}

#[derive(Debug)]
pub struct SemanticAnalyzer {
    pub symbol_table: SymbolTable,
    pub current_block_labels: Vec<i64>,
    pub external_interfaces: HashMap<String, HashMap<String, SymbolKind>>,
    pub diagnostics: Vec<Diagnostic>,
    pub definitions: Vec<(Span, SymbolId)>,
    pub references: Vec<(Span, SymbolId)>,
}

impl SemanticAnalyzer {
    pub fn new() -> Self {
        let mut analyzer = Self {
            symbol_table: SymbolTable::new(),
            current_block_labels: Vec::new(),
            external_interfaces: HashMap::new(),
            diagnostics: Vec::new(),
            definitions: Vec::new(),
            references: Vec::new(),
        };
        analyzer.setup_builtins();
        analyzer
    }

    pub fn with_interfaces(interfaces: HashMap<String, HashMap<String, SymbolKind>>) -> Self {
        let mut analyzer = Self::new();
        analyzer.external_interfaces = interfaces;
        analyzer
    }

    pub fn error(&mut self, span: Span, message: impl Into<String>) {
        self.diagnostics.push(Diagnostic {
            span,
            message: message.into(),
        });
    }

    fn setup_builtins(&mut self) {
        let builtins = ["integer", "real", "boolean", "char", "string"];
        for t in builtins {
            if let Ok(id) = self.symbol_table.insert(t.to_string(), SymbolKind::Type { 
                type_expr: Spanned { span: Span::default(), node: TypeExprKind::Simple(t.to_string()) }
            }, Span::default()) {
                self.definitions.push((Span::default(), id));
            }
        }
        let builtin_procs = ["write", "writeln", "read", "readln"];
        for p in builtin_procs {
            if let Ok(id) = self.symbol_table.insert(p.to_string(), SymbolKind::Procedure { 
                params: Vec::new() 
            }, Span::default()) {
                self.definitions.push((Span::default(), id));
            }
        }
        if let Ok(id) = self.symbol_table.insert("maxint".to_string(), SymbolKind::Constant {
            type_expr: Spanned { span: Span::default(), node: TypeExprKind::Simple("integer".to_string()) },
            value: i64::MAX.to_string(),
        }, Span::default()) {
            self.definitions.push((Span::default(), id));
        }
        if let Ok(id) = self.symbol_table.insert("Chr".to_string(), SymbolKind::Function {
            params: vec![Param { span: Span::default(), node: ParamKind::Variable { is_var: false, ids: vec!["num".to_string()], type_expr: Spanned { span: Span::default(), node: TypeExprKind::Simple("integer".to_string()) } } }],
            return_type: "char".to_string(),
        }, Span::default()) {
            self.definitions.push((Span::default(), id));
        }
        if let Ok(id) = self.symbol_table.insert("Ord".to_string(), SymbolKind::Function {
            params: vec![Param { span: Span::default(), node: ParamKind::Variable { is_var: false, ids: vec!["val".to_string()], type_expr: Spanned { span: Span::default(), node: TypeExprKind::Simple("char".to_string()) } } }],
            return_type: "integer".to_string(),
        }, Span::default()) {
            self.definitions.push((Span::default(), id));
        }

        // Runtime functions
        if let Ok(id) = self.symbol_table.insert("RuntimeInit".to_string(), SymbolKind::Procedure { params: Vec::new() }, Span::default()) {
            self.definitions.push((Span::default(), id));
        }
        if let Ok(id) = self.symbol_table.insert("Sqrt".to_string(), SymbolKind::Function {
            params: vec![Param { span: Span::default(), node: ParamKind::Variable { is_var: false, ids: vec!["n".to_string()], type_expr: Spanned { span: Span::default(), node: TypeExprKind::Simple("real".to_string()) } } }],
            return_type: "real".to_string(),
        }, Span::default()) {
            self.definitions.push((Span::default(), id));
        }
        if let Ok(id) = self.symbol_table.insert("Halt".to_string(), SymbolKind::Procedure {
            params: vec![Param { span: Span::default(), node: ParamKind::Variable { is_var: false, ids: vec!["code".to_string()], type_expr: Spanned { span: Span::default(), node: TypeExprKind::Simple("integer".to_string()) } } }],
        }, Span::default()) {
            self.definitions.push((Span::default(), id));
        }
    }

    pub fn analyze_program(&mut self, program: &Program) -> Result<typed::TypedProgram, String> {
        if let Err(e) = self.import_uses(&program.uses) {
            self.error(program.span, &e);
            return Err(e);
        }
        let typed_block = self.analyze_block(&program.block)?;
        Ok(typed::TypedProgram {
            name: program.name.clone(),
            uses: program.uses.clone().unwrap_or_default(),
            block: typed_block,
        })
    }

    pub fn analyze_unit(&mut self, unit: &Unit) -> Result<(HashMap<String, SymbolKind>, typed::TypedBlock), String> {
        if let Err(e) = self.import_uses(&unit.interface.uses) {
            self.error(unit.interface.span, &e);
        }
        if let Some(headers) = &unit.interface.headers {
            for h in headers {
                match h {
                    ProcFuncDecl::Procedure { name, params, span, .. } => { 
                        match self.symbol_table.insert(name.clone(), SymbolKind::Procedure { params: params.clone().unwrap_or_default() }, *span) {
                            Ok(id) => self.definitions.push((*span, id)),
                            Err(e) => self.error(*span, e),
                        }
                    }
                    ProcFuncDecl::Function { name, params, return_type, span, .. } => { 
                        match self.symbol_table.insert(name.clone(), SymbolKind::Function { params: params.clone().unwrap_or_default(), return_type: return_type.clone() }, *span) {
                            Ok(id) => self.definitions.push((*span, id)),
                            Err(e) => self.error(*span, e),
                        }
                    }
                }
            }
        }
        let _ = self.analyze_block_internal(&unit.interface.constants, &unit.interface.types, &unit.interface.variables, &None, &[], unit.interface.span);
        let interface_symbols = self.symbol_table.global_scope();
        if let Err(e) = self.import_uses(&unit.implementation.uses) {
            self.error(unit.implementation.span, e);
        }
        let typed_block = self.analyze_block_internal(&unit.implementation.constants, &unit.implementation.types, &unit.implementation.variables, &unit.implementation.bodies, &unit.initialization.clone().unwrap_or_default(), unit.implementation.span)?;
        
        if !self.diagnostics.is_empty() {
            return Err("Semantic errors found in unit".to_string());
        }
        Ok((interface_symbols, typed_block))
    }

    fn analyze_block(&mut self, block: &Block) -> Result<typed::TypedBlock, String> {
        self.analyze_block_internal(&block.constants, &block.types, &block.variables, &block.procedures_functions, &block.statements, block.span)
    }

    fn analyze_block_internal(
        &mut self,
        constants: &Option<Vec<ConstDecl>>,
        types: &Option<Vec<TypeDecl>>,
        variables: &Option<Vec<VarDecl>>,
        procedures: &Option<Vec<ProcFuncDecl>>,
        statements: &[Stmt],
        span: Span,
    ) -> Result<typed::TypedBlock, String> {
        let old_labels = self.current_block_labels.clone();
        let mut typed_constants = Vec::new();
        if let Some(consts) = constants {
            for c in consts {
                match self.analyze_expr(&c.value) {
                    Ok(typed_val) => {
                        match self.symbol_table.insert(c.name.clone(), SymbolKind::Constant { type_expr: self.convert_to_legacy_type(&typed_val.ty), value: format!("{:?}", c.value) }, c.span) {
                            Ok(id) => self.definitions.push((c.span, id)),
                            Err(e) => self.error(c.span, e),
                        }
                        typed_constants.push((c.name.clone(), typed_val));
                    }
                    Err(e) => {
                        self.error(c.span, e);
                    }
                }
            }
        }
        if let Some(t_decls) = types {
            for t in t_decls {
                match self.symbol_table.insert(t.name.clone(), SymbolKind::Type { type_expr: t.type_expr.clone() }, t.span) {
                    Ok(id) => self.definitions.push((t.span, id)),
                    Err(e) => self.error(t.span, e),
                }
                if let TypeExprKind::Enum(ids) = &t.type_expr.node {
                    for (i, id) in ids.iter().enumerate() { 
                        match self.symbol_table.insert(id.clone(), SymbolKind::Constant { type_expr: Spanned { span: t.type_expr.span, node: TypeExprKind::Simple(t.name.clone()) }, value: i.to_string() }, t.span) {
                            Ok(sym_id) => self.definitions.push((t.span, sym_id)),
                            Err(e) => self.error(t.span, e),
                        }
                        typed_constants.push((id.clone(), typed::TypedExpr { ty: typed::Type::Integer, kind: typed::TypedExprKind::Integer(i as i64), span: t.type_expr.span }));
                    }
                }
            }
        }
        let mut typed_vars = Vec::new();
        if let Some(vars) = variables {
            for v in vars {
                let ty = self.convert_type(&v.type_expr);
                for id in &v.ids { 
                    match self.symbol_table.insert(id.clone(), SymbolKind::Variable { type_expr: v.type_expr.clone() }, v.span) {
                        Ok(sym_id) => self.definitions.push((v.span, sym_id)),
                        Err(e) => self.error(v.span, e),
                    }
                    typed_vars.push((id.clone(), ty.clone())); 
                }
            }
        }
        let mut typed_procs = Vec::new();
        if let Some(procs) = procedures {
            for p in procs {
                match p {
                    ProcFuncDecl::Procedure { name, params, block_or_forward, span, .. } => {
                        let mut typed_params = Vec::new();
                        if let Some(params_vec) = params {
                             for param in params_vec {
                                 match &param.node {
                                     ParamKind::Variable { ids, type_expr, is_var } => {
                                         let ty = self.convert_type(type_expr);
                                         for id in ids { typed_params.push((id.clone(), ty.clone(), *is_var)); }
                                     },
                                     ParamKind::Procedure { id, .. } => { typed_params.push((id.clone(), typed::Type::Procedure, false)); }
                                     ParamKind::Function { id, return_type, .. } => { typed_params.push((id.clone(), typed::Type::Function(Box::new(self.convert_type(&Spanned { span: param.span, node: TypeExprKind::Simple(return_type.clone()) }))), false)); }
                                 }
                             }
                        }
                        let body = if let BlockOrForward::Block(b) = block_or_forward { 
                            self.symbol_table.enter_scope(); 
                            if let Err(e) = self.add_params_to_scope(params) {
                                self.error(*span, e);
                            }
                            let tb = self.analyze_block(b).ok(); 
                            self.symbol_table.exit_scope(); 
                            tb
                        } else { None };
                        typed_procs.push(typed::TypedProcFunc { name: name.clone(), params: typed_params, return_type: typed::Type::Void, body, span: *span });
                    }
                    ProcFuncDecl::Function { name, params, return_type, block_or_forward, span, .. } => {
                        let mut typed_params = Vec::new();
                        if let Some(params_vec) = params {
                             for param in params_vec {
                                 match &param.node {
                                     ParamKind::Variable { ids, type_expr, is_var } => {
                                         let ty = self.convert_type(type_expr);
                                         for id in ids { typed_params.push((id.clone(), ty.clone(), *is_var)); }
                                     },
                                     ParamKind::Procedure { id, .. } => { typed_params.push((id.clone(), typed::Type::Procedure, false)); }
                                     ParamKind::Function { id, return_type, .. } => { typed_params.push((id.clone(), typed::Type::Function(Box::new(self.convert_type(&Spanned { span: param.span, node: TypeExprKind::Simple(return_type.clone()) }))), false)); }
                                 }
                             }
                        }
                        let body = if let BlockOrForward::Block(b) = block_or_forward { 
                            self.symbol_table.enter_scope(); 
                            if let Err(e) = self.add_params_to_scope(params) {
                                self.error(*span, e);
                            }
                            match self.symbol_table.insert(name.clone(), SymbolKind::Variable { type_expr: Spanned { span: Span::default(), node: TypeExprKind::Simple(return_type.clone()) } }, *span) {
                                Ok(id) => self.definitions.push((*span, id)),
                                Err(e) => self.error(*span, e),
                            }
                            let tb = self.analyze_block(b).ok(); 
                            self.symbol_table.exit_scope(); 
                            tb
                        } else { None };
                        typed_procs.push(typed::TypedProcFunc { 
                            name: name.clone(), 
                            params: typed_params, 
                            return_type: self.convert_type(&Spanned { span: Span::default(), node: TypeExprKind::Simple(return_type.clone()) }), 
                            body,
                            span: *span,
                        });
                    }
                }
            }
        }
        let mut typed_stmts = Vec::new();
        for stmt in statements { 
            if let Ok(ts) = self.analyze_stmt(stmt) {
                typed_stmts.push(ts);
            }
        }
        self.current_block_labels = old_labels;
        Ok(typed::TypedBlock { 
            span,
            labels: self.current_block_labels.clone(), 
            constants: typed_constants, 
            variables: typed_vars, 
            procedures: typed_procs, 
            statements: typed_stmts 
        })
    }

    fn analyze_stmt(&mut self, stmt: &Stmt) -> Result<typed::TypedStmt, String> {
        let span = stmt.span;
        let kind = match &stmt.node {
            StmtKind::Compound(stmts) => {
                let mut typed_stmts = Vec::new();
                for s in stmts { if let Ok(ts) = self.analyze_stmt(s) { typed_stmts.push(ts); } }
                typed::TypedStmtKind::Compound(typed_stmts)
            }
            StmtKind::Assignment { target, value } => {
                let t = self.analyze_expr(target)?;
                let v = self.analyze_expr(value)?;
                typed::TypedStmtKind::Assignment { target: t, value: v }
            }
            StmtKind::If { condition, then_stmt, else_stmt } => {
                let c = self.analyze_expr(condition)?;
                let t = Box::new(self.analyze_stmt(then_stmt)?);
                let e = if let Some(es) = else_stmt { Some(Box::new(self.analyze_stmt(es)?)) } else { None };
                typed::TypedStmtKind::If { condition: c, then_stmt: t, else_stmt: e }
            }
            StmtKind::While { condition, body } => {
                let c = self.analyze_expr(condition)?;
                let b = Box::new(self.analyze_stmt(body)?);
                typed::TypedStmtKind::While { condition: c, body: b }
            }
            StmtKind::Repeat { body, until } => {
                let mut b_vec = Vec::new();
                for s in body { if let Ok(ts) = self.analyze_stmt(s) { b_vec.push(ts); } }
                let u = self.analyze_expr(until)?;
                typed::TypedStmtKind::Repeat { body: b_vec, until: u }
            }
            StmtKind::For { id, start, up, end, body } => {
                let s = self.analyze_expr(start)?;
                let e = self.analyze_expr(end)?;
                let b = Box::new(self.analyze_stmt(body)?);
                if let Some(info) = self.symbol_table.lookup(id) {
                    self.references.push((stmt.span, info.id));
                }
                typed::TypedStmtKind::For { id: id.clone(), start: s, up: *up, end: e, body: b }
            }
            StmtKind::ProcedureCall { name, args } => {
                let mut t_args = Vec::new();
                if let Some(a_vec) = args { for a in a_vec { t_args.push(self.analyze_expr(a)?); } }
                if let Some(info) = self.symbol_table.lookup(name) {
                    self.references.push((stmt.span, info.id));
                }
                typed::TypedStmtKind::ProcedureCall { name: name.clone(), args: t_args }
            }
            StmtKind::Goto(l) => typed::TypedStmtKind::Goto(*l),
            StmtKind::Labeled(l, s) => typed::TypedStmtKind::Labeled(*l, Box::new(self.analyze_stmt(s)?)),
            StmtKind::Case { expr, items, else_stmt } => {
                let e = self.analyze_expr(expr)?;
                let mut t_items = Vec::new();
                for item in items {
                    let mut t_labels = Vec::new();
                    for l in &item.labels { t_labels.push(self.analyze_expr(l)?); }
                    t_items.push(typed::TypedCaseItem { span: item.span, labels: t_labels, stmt: self.analyze_stmt(&item.stmt)? });
                }
                let t_else = if let Some(es) = else_stmt { Some(Box::new(self.analyze_stmt(es)?)) } else { None };
                typed::TypedStmtKind::Case { expr: e, items: t_items, else_stmt: t_else }
            }
            StmtKind::With { ids, body } => {
                let mut t_objs = Vec::new();
                for id_expr in ids { t_objs.push(self.analyze_expr(id_expr)?); }
                self.symbol_table.enter_scope();
                for obj in &t_objs {
                    if let typed::Type::Record { fields } = &obj.ty {
                        for (f_n, f_t) in fields {
                             match self.symbol_table.insert(f_n.clone(), SymbolKind::Variable { type_expr: self.convert_to_legacy_type(f_t) }, span) {
                                 Ok(id) => self.definitions.push((span, id)),
                                 Err(e) => self.error(span, e),
                             }
                        }
                    }
                }
                let b = Box::new(self.analyze_stmt(body)?);
                self.symbol_table.exit_scope();
                typed::TypedStmtKind::With { objects: t_objs, body: b }
            }
            StmtKind::Empty => typed::TypedStmtKind::Empty,
        };
        Ok(typed::TypedStmt { kind, span })
    }

    fn analyze_expr(&mut self, expr: &Expr) -> Result<typed::TypedExpr, String> {
        let span = expr.span;
        let (ty, kind) = match &expr.node {
            ExprKind::Integer(n) => (typed::Type::Integer, typed::TypedExprKind::Integer(*n)),
            ExprKind::Real(n) => (typed::Type::Real, typed::TypedExprKind::Real(*n)),
            ExprKind::Boolean(b) => (typed::Type::Boolean, typed::TypedExprKind::Boolean(*b)),
            ExprKind::Char(c) => (typed::Type::Char, typed::TypedExprKind::Char(*c)),
            ExprKind::String(s) => (typed::Type::String, typed::TypedExprKind::String(s.clone())),
            ExprKind::Nil => (typed::Type::Pointer(Box::new(typed::Type::Void)), typed::TypedExprKind::Nil),
            ExprKind::Variable(v) => {
                match self.analyze_variable(v) {
                    Ok(typed_var) => {
                        let ty = self.get_variable_type(v);
                        (ty, typed::TypedExprKind::Variable(typed_var))
                    }
                    Err(e) => {
                        self.error(span, &e);
                        (typed::Type::Error, typed::TypedExprKind::Nil)
                    }
                }
            }
            ExprKind::Binary { op, left, right } => {
                let l = self.analyze_expr(left)?;
                let r = self.analyze_expr(right)?;
                let res_ty = match op {
                    BinOp::Add | BinOp::Sub | BinOp::Mul | BinOp::Div | BinOp::Mod => typed::Type::Integer,
                    BinOp::FloatDiv => typed::Type::Real,
                    _ => typed::Type::Boolean,
                };
                (res_ty, typed::TypedExprKind::Binary { op: op.clone(), left: Box::new(l), right: Box::new(r) })
            }
            ExprKind::Unary { op, expr } => {
                let e = self.analyze_expr(expr)?;
                (e.ty.clone(), typed::TypedExprKind::Unary { op: op.clone(), expr: Box::new(e) })
            }
            ExprKind::FunctionCall { name, args } => {
                let mut t_args = Vec::new();
                if let Some(a_vec) = args { for a in a_vec { t_args.push(self.analyze_expr(a)?); } }
                let res_ty = if let Some(info) = self.symbol_table.lookup(name) {
                    self.references.push((expr.span, info.id));
                    match &info.kind {
                        SymbolKind::Function { return_type, .. } => self.convert_type(&Spanned { span: expr.span, node: TypeExprKind::Simple(return_type.clone()) }),
                        _ => typed::Type::Integer,
                    }
                } else { typed::Type::Integer };
                (res_ty, typed::TypedExprKind::FunctionCall { name: name.clone(), args: t_args })
            }
            ExprKind::Set(els) => {
                let mut typed_els = Vec::new();
                for e in els {
                    match &e.node {
                        ElementKind::Single(expr) => typed_els.push(typed::TypedElement::Single(self.analyze_expr(expr)?)),
                        ElementKind::Range(start, end) => typed_els.push(typed::TypedElement::Range(self.analyze_expr(start)?, self.analyze_expr(end)?)),
                    }
                }
                (typed::Type::Set(Box::new(typed::Type::Integer)), typed::TypedExprKind::Set(typed_els))
            }
            _ => (typed::Type::Integer, typed::TypedExprKind::Nil),
        };
        Ok(typed::TypedExpr { ty, kind, span })
    }

    fn analyze_variable(&mut self, var: &Variable) -> Result<typed::TypedVariable, String> {
        match &var.node {
            VariableKind::Id(name) => {
                if let Some(info) = self.symbol_table.lookup(name) {
                    self.references.push((var.span, info.id));
                    Ok(typed::TypedVariable::Id(name.clone()))
                } else { Err(format!("Undeclared identifier '{}'", name)) }
            }
            VariableKind::MemberAccess { record, field } => Ok(typed::TypedVariable::MemberAccess { record: Box::new(self.analyze_expr(record)?), field: field.clone() }),
            VariableKind::ArrayAccess { array, indices } => Ok(typed::TypedVariable::ArrayAccess { array: Box::new(self.analyze_expr(array)?), index: Box::new(self.analyze_expr(&indices[0])?) }),
            VariableKind::PointerDeref(p) => Ok(typed::TypedVariable::PointerDeref(Box::new(self.analyze_expr(p)?))),
        }
    }

    fn get_variable_type(&self, var: &Variable) -> typed::Type {
        match &var.node {
            VariableKind::Id(name) => if let Some(info) = self.symbol_table.lookup(name) { match &info.kind { SymbolKind::Variable { type_expr } | SymbolKind::Constant { type_expr, .. } => self.convert_type(type_expr), _ => typed::Type::Integer } } else { typed::Type::Integer },
            _ => typed::Type::Integer,
        }
    }

    fn import_uses(&mut self, uses: &Option<Vec<String>>) -> Result<(), String> {
        if let Some(units) = uses {
            for u_name in units {
                if let Some(interface) = self.external_interfaces.get(&u_name.to_lowercase()).cloned() {
                    for (name, kind) in interface {
                        let _ = self.symbol_table.insert(name, kind, Span::default());
                    }
                } else { return Err(format!("Unit {} not found", u_name)); }
            }
        }
        Ok(())
    }

    fn add_params_to_scope(&mut self, params: &Option<Vec<Param>>) -> Result<(), String> {
        if let Some(params_vec) = params {
            for p in params_vec {
                match &p.node {
                    ParamKind::Variable { ids, type_expr, .. } => { 
                        for id in ids { 
                            match self.symbol_table.insert(id.clone(), SymbolKind::Variable { type_expr: type_expr.clone() }, p.span) {
                                Ok(sym_id) => self.definitions.push((p.span, sym_id)),
                                Err(e) => return Err(e),
                            }
                        } 
                    }
                    ParamKind::Procedure { id, params } => { 
                        match self.symbol_table.insert(id.clone(), SymbolKind::Procedure { params: params.clone().unwrap_or_default() }, p.span) {
                            Ok(sym_id) => self.definitions.push((p.span, sym_id)),
                            Err(e) => return Err(e),
                        }
                    }
                    ParamKind::Function { id, params, return_type } => { 
                        match self.symbol_table.insert(id.clone(), SymbolKind::Function { params: params.clone().unwrap_or_default(), return_type: return_type.clone() }, p.span) {
                            Ok(sym_id) => self.definitions.push((p.span, sym_id)),
                            Err(e) => return Err(e),
                        }
                    }
                }
            }
        }
        Ok(()) 
    }

    fn convert_type(&self, te: &TypeExpr) -> typed::Type {
        match &te.node {
            TypeExprKind::Simple(name) => match name.to_lowercase().as_str() {
                "integer" => typed::Type::Integer, "real" => typed::Type::Real, "boolean" => typed::Type::Boolean, "char" => typed::Type::Char, "string" => typed::Type::String,
                _ => { if let Some(info) = self.symbol_table.lookup(name) { if let SymbolKind::Type { type_expr } = &info.kind { self.convert_type(type_expr) } else { typed::Type::Integer } } else { typed::Type::Integer } }
            },
            TypeExprKind::Array { element_type, .. } => typed::Type::Array { element_type: Box::new(self.convert_type(element_type)), size: 100 },
            TypeExprKind::Record { fields, variant_part } => {
                let mut f_vec = Vec::new();
                for f in fields {
                    let ft = self.convert_type(&f.type_expr);
                    for id in &f.ids { f_vec.push((id.clone(), ft.clone())); }
                }
                if let Some(vp) = variant_part {
                    if let Some(tag) = &vp.tag_field {
                        f_vec.push((tag.clone(), self.convert_type(&Spanned { span: vp.span, node: TypeExprKind::Simple(vp.tag_type.clone()) })));
                    }
                    for v in &vp.variants {
                        for f in &v.fields {
                            let ft = self.convert_type(&f.type_expr);
                            for id in &f.ids {
                                if !f_vec.iter().any(|(n, _)| n == id) {
                                    f_vec.push((id.clone(), ft.clone()));
                                }
                            }
                        }
                    }
                }
                typed::Type::Record { fields: f_vec }
            }
            TypeExprKind::Pointer(inner) => typed::Type::Pointer(Box::new(self.convert_type(inner))),
            TypeExprKind::Set(inner) => typed::Type::Set(Box::new(self.convert_type(inner))),
            TypeExprKind::Enum(ids) => typed::Type::Enum(ids.clone()),
            TypeExprKind::Subrange { .. } => typed::Type::Integer,
            TypeExprKind::File(inner) => typed::Type::Pointer(Box::new(self.convert_type(inner))),
            TypeExprKind::Procedure { .. } => typed::Type::Procedure,
            TypeExprKind::Function { return_type, .. } => typed::Type::Function(Box::new(self.convert_type(&Spanned { span: te.span, node: TypeExprKind::Simple(return_type.clone()) }))),
        }
    }

    fn convert_to_legacy_type(&self, ty: &typed::Type) -> TypeExpr {
        match ty { 
            typed::Type::Integer => TypeExpr { span: Span::default(), node: TypeExprKind::Simple("integer".to_string()) }, 
            typed::Type::Real => TypeExpr { span: Span::default(), node: TypeExprKind::Simple("real".to_string()) }, 
            typed::Type::Boolean => TypeExpr { span: Span::default(), node: TypeExprKind::Simple("boolean".to_string()) }, 
            typed::Type::Char => TypeExpr { span: Span::default(), node: TypeExprKind::Simple("char".to_string()) }, 
            typed::Type::String => TypeExpr { span: Span::default(), node: TypeExprKind::Simple("string".to_string()) }, 
            _ => TypeExpr { span: Span::default(), node: TypeExprKind::Simple("unknown".to_string()) } 
        }
    }
}
