use crate::ast::*;
use crate::symbol_table::{SymbolId, SymbolKind, SymbolTable};
use crate::typed_ast as typed;
use std::collections::HashMap;

/// A semantic error tied to a source span, surfaced as an LSP diagnostic.
#[derive(Debug, Clone)]
pub struct Diagnostic {
    pub span: Span,
    pub message: String,
}

#[derive(Debug)]
pub struct SemanticAnalyzer {
    pub symbol_table: SymbolTable,
    current_block_labels: Vec<i64>,
    external_interfaces: HashMap<String, HashMap<String, SymbolKind>>,
    /// Semantic errors collected during analysis (consumed by the LSP).
    pub diagnostics: Vec<Diagnostic>,
    /// Definition sites: where each symbol is declared.
    pub definitions: Vec<(Span, SymbolId)>,
    /// Reference sites: where each symbol is used.
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

    /// Insert a declaration and record its definition span for the LSP.
    fn define(&mut self, name: String, kind: SymbolKind, span: Span) -> Result<SymbolId, String> {
        let id = self.symbol_table.insert(name, kind, span)?;
        self.definitions.push((span, id));
        Ok(id)
    }

    /// Record a use-site reference to `name`, if it resolves to a known symbol.
    fn record_reference(&mut self, name: &str, span: Span) {
        if span == Span::default() {
            return;
        }
        if let Some(id) = self.symbol_table.lookup_id(name) {
            self.references.push((span, id));
        }
    }

    fn setup_builtins(&mut self) {
        let builtins = ["integer", "real", "boolean", "char", "string"];
        for t in builtins {
            let _ = self.symbol_table.insert(
                t.to_string(),
                SymbolKind::Type {
                    type_expr: TypeExpr::Simple(t.to_string()),
                },
                Span::default(),
            );
        }
        let builtin_procs = ["write", "writeln", "read", "readln"];
        for p in builtin_procs {
            let _ = self.symbol_table.insert(
                p.to_string(),
                SymbolKind::Procedure {
                    params: Vec::new(),
                    external_name: None,
                },
                Span::default(),
            );
        }
        let _ = self.symbol_table.insert(
            "maxint".to_string(),
            SymbolKind::Constant {
                type_expr: TypeExpr::Simple("integer".to_string()),
                value: i64::MAX.to_string(),
            },
            Span::default(),
        );
        // Note: runtime intrinsics such as Sqrt, Halt and RuntimeInit are NOT
        // hardcoded here. They are provided by the `system` unit, which every
        // program implicitly uses, so their signatures (and `external name`
        // bindings) come from that unit's interface.
    }

    pub fn analyze_program(&mut self, program: &Program) -> Result<typed::TypedProgram, String> {
        self.import_uses(&program.uses)?;
        let typed_block = self.analyze_block(&program.block)?;
        Ok(typed::TypedProgram {
            name: program.name.clone(),
            uses: program.uses.clone().unwrap_or_default(),
            block: typed_block,
        })
    }

    pub fn analyze_unit(
        &mut self,
        unit: &Unit,
    ) -> Result<(HashMap<String, SymbolKind>, typed::TypedBlock), String> {
        self.import_uses(&unit.interface.uses)?;
        if let Some(headers) = &unit.interface.headers {
            for h in headers {
                match h {
                    ProcFuncDecl::Procedure {
                        name,
                        name_span,
                        params,
                        block_or_forward,
                    } => {
                        let external_name = match block_or_forward {
                            BlockOrForward::External(n) => n.clone(),
                            _ => None,
                        };
                        self.define(
                            name.clone(),
                            SymbolKind::Procedure {
                                params: params.clone().unwrap_or_default(),
                                external_name,
                            },
                            *name_span,
                        )?;
                    }
                    ProcFuncDecl::Function {
                        name,
                        name_span,
                        params,
                        return_type,
                        block_or_forward,
                    } => {
                        let external_name = match block_or_forward {
                            BlockOrForward::External(n) => n.clone(),
                            _ => None,
                        };
                        self.define(
                            name.clone(),
                            SymbolKind::Function {
                                params: params.clone().unwrap_or_default(),
                                return_type: return_type.clone(),
                                external_name,
                            },
                            *name_span,
                        )?;
                    }
                }
            }
        }
        let _ = self.analyze_block_internal(
            &unit.interface.constants,
            &unit.interface.types,
            &unit.interface.variables,
            &None,
            &[],
        );
        let mut interface_symbols = self.symbol_table.global_scope();
        self.import_uses(&unit.implementation.uses)?;
        let typed_block = self.analyze_block_internal(
            &unit.implementation.constants,
            &unit.implementation.types,
            &unit.implementation.variables,
            &unit.implementation.bodies,
            &unit.initialization.clone().unwrap_or_default(),
        )?;
        // The `external name '...'` binding lives on the implementation
        // declaration, but the interface signature is what callers see. Merge
        // those bindings into the exported interface so call sites resolve the
        // correct native link symbol.
        if let Some(bodies) = &unit.implementation.bodies {
            for body in bodies {
                let (name, block_or_forward) = match body {
                    ProcFuncDecl::Procedure {
                        name,
                        block_or_forward,
                        ..
                    } => (name, block_or_forward),
                    ProcFuncDecl::Function {
                        name,
                        block_or_forward,
                        ..
                    } => (name, block_or_forward),
                };
                if let BlockOrForward::External(Some(ext)) = block_or_forward {
                    if let Some(sym) = interface_symbols.get_mut(name) {
                        match sym {
                            SymbolKind::Function { external_name, .. }
                            | SymbolKind::Procedure { external_name, .. } => {
                                *external_name = Some(ext.clone());
                            }
                            _ => {}
                        }
                    }
                }
            }
        }
        Ok((interface_symbols, typed_block))
    }

    fn analyze_block(&mut self, block: &Block) -> Result<typed::TypedBlock, String> {
        self.analyze_block_internal(
            &block.constants,
            &block.types,
            &block.variables,
            &block.procedures_functions,
            &block.statements,
        )
    }

    fn analyze_block_internal(
        &mut self,
        constants: &Option<Vec<ConstDecl>>,
        types: &Option<Vec<TypeDecl>>,
        variables: &Option<Vec<VarDecl>>,
        procedures: &Option<Vec<ProcFuncDecl>>,
        statements: &[Stmt],
    ) -> Result<typed::TypedBlock, String> {
        let old_labels = self.current_block_labels.clone();
        let mut typed_constants = Vec::new();
        if let Some(consts) = constants {
            for c in consts {
                let typed_val = self.analyze_expr(&c.value)?;
                let const_kind = SymbolKind::Constant {
                    type_expr: self.convert_to_legacy_type(&typed_val.ty),
                    value: format!("{:?}", c.value),
                };
                self.define(c.name.clone(), const_kind, c.name_span)?;
                typed_constants.push((c.name.clone(), typed_val));
            }
        }
        if let Some(t_decls) = types {
            for t in t_decls {
                self.define(
                    t.name.clone(),
                    SymbolKind::Type {
                        type_expr: t.type_expr.clone(),
                    },
                    t.name_span,
                )?;
                if let TypeExpr::Enum(ids) = &t.type_expr {
                    for (i, id) in ids.iter().enumerate() {
                        self.define(
                            id.clone(),
                            SymbolKind::Constant {
                                type_expr: TypeExpr::Simple(t.name.clone()),
                                value: i.to_string(),
                            },
                            Span::default(),
                        )?;
                        typed_constants.push((
                            id.clone(),
                            typed::TypedExpr {
                                ty: typed::Type::Integer,
                                kind: typed::TypedExprKind::Integer(i as i64),
                            },
                        ));
                    }
                }
            }
        }
        let mut typed_vars = Vec::new();
        if let Some(vars) = variables {
            for v in vars {
                let ty = self.convert_type(&v.type_expr);
                for (i, id) in v.ids.iter().enumerate() {
                    let span = v.id_spans.get(i).copied().unwrap_or_default();
                    self.define(
                        id.clone(),
                        SymbolKind::Variable {
                            type_expr: v.type_expr.clone(),
                        },
                        span,
                    )?;
                    typed_vars.push((id.clone(), ty.clone()));
                }
            }
        }
        let mut typed_procs = Vec::new();
        if let Some(procs) = procedures {
            for p in procs {
                match p {
                    ProcFuncDecl::Procedure {
                        name,
                        name_span,
                        params,
                        block_or_forward,
                    } => {
                        if self.symbol_table.lookup(name).is_none() {
                            let external_name = match block_or_forward {
                                BlockOrForward::External(n) => n.clone(),
                                _ => None,
                            };
                            self.define(
                                name.clone(),
                                SymbolKind::Procedure {
                                    params: params.clone().unwrap_or_default(),
                                    external_name,
                                },
                                *name_span,
                            )?;
                        }
                    }
                    ProcFuncDecl::Function {
                        name,
                        name_span,
                        params,
                        return_type,
                        block_or_forward,
                    } => {
                        if self.symbol_table.lookup(name).is_none() {
                            let external_name = match block_or_forward {
                                BlockOrForward::External(n) => n.clone(),
                                _ => None,
                            };
                            self.define(
                                name.clone(),
                                SymbolKind::Function {
                                    params: params.clone().unwrap_or_default(),
                                    return_type: return_type.clone(),
                                    external_name,
                                },
                                *name_span,
                            )?;
                        }
                    }
                }
            }
            for p in procs {
                match p {
                    ProcFuncDecl::Procedure {
                        name,
                        params,
                        block_or_forward,
                        ..
                    } => {
                        let mut typed_params = Vec::new();
                        if let Some(params_vec) = params {
                            for param in params_vec {
                                match param {
                                    Param::Variable {
                                        ids,
                                        type_name,
                                        is_var,
                                        ..
                                    } => {
                                        let ty =
                                            self.convert_type(&TypeExpr::Simple(type_name.clone()));
                                        for id in ids {
                                            typed_params.push((id.clone(), ty.clone(), *is_var));
                                        }
                                    }
                                    Param::Procedure { id, .. } => {
                                        typed_params.push((
                                            id.clone(),
                                            typed::Type::Procedure,
                                            false,
                                        ));
                                    }
                                    Param::Function {
                                        id, return_type, ..
                                    } => {
                                        typed_params.push((
                                            id.clone(),
                                            typed::Type::Function(Box::new(self.convert_type(
                                                &TypeExpr::Simple(return_type.clone()),
                                            ))),
                                            false,
                                        ));
                                    }
                                }
                            }
                        }
                        let body = if let BlockOrForward::Block(b) = block_or_forward {
                            self.symbol_table.enter_scope();
                            self.add_params_to_scope(params)?;
                            let tb = self.analyze_block(b)?;
                            self.symbol_table.exit_scope();
                            Some(tb)
                        } else {
                            None
                        };
                        let external_name = match block_or_forward {
                            BlockOrForward::External(n) => n.clone(),
                            _ => None,
                        };
                        typed_procs.push(typed::TypedProcFunc {
                            name: name.clone(),
                            params: typed_params,
                            return_type: typed::Type::Void,
                            body,
                            external_name,
                        });
                    }
                    ProcFuncDecl::Function {
                        name,
                        params,
                        return_type,
                        block_or_forward,
                        ..
                    } => {
                        let mut typed_params = Vec::new();
                        if let Some(params_vec) = params {
                            for param in params_vec {
                                match param {
                                    Param::Variable {
                                        ids,
                                        type_name,
                                        is_var,
                                        ..
                                    } => {
                                        let ty =
                                            self.convert_type(&TypeExpr::Simple(type_name.clone()));
                                        for id in ids {
                                            typed_params.push((id.clone(), ty.clone(), *is_var));
                                        }
                                    }
                                    Param::Procedure { id, .. } => {
                                        typed_params.push((
                                            id.clone(),
                                            typed::Type::Procedure,
                                            false,
                                        ));
                                    }
                                    Param::Function {
                                        id, return_type, ..
                                    } => {
                                        typed_params.push((
                                            id.clone(),
                                            typed::Type::Function(Box::new(self.convert_type(
                                                &TypeExpr::Simple(return_type.clone()),
                                            ))),
                                            false,
                                        ));
                                    }
                                }
                            }
                        }
                        let body = if let BlockOrForward::Block(b) = block_or_forward {
                            self.symbol_table.enter_scope();
                            self.add_params_to_scope(params)?;
                            self.symbol_table.insert(
                                name.clone(),
                                SymbolKind::Variable {
                                    type_expr: TypeExpr::Simple(return_type.clone()),
                                },
                                Span::default(),
                            )?;
                            let tb = self.analyze_block(b)?;
                            self.symbol_table.exit_scope();
                            Some(tb)
                        } else {
                            None
                        };
                        let external_name = match block_or_forward {
                            BlockOrForward::External(n) => n.clone(),
                            _ => None,
                        };
                        typed_procs.push(typed::TypedProcFunc {
                            name: name.clone(),
                            params: typed_params,
                            return_type: self.convert_type(&TypeExpr::Simple(return_type.clone())),
                            body,
                            external_name,
                        });
                    }
                }
            }
        }
        let mut typed_stmts = Vec::new();
        for stmt in statements {
            typed_stmts.push(self.analyze_stmt(stmt)?);
        }
        self.current_block_labels = old_labels;
        Ok(typed::TypedBlock {
            labels: self.current_block_labels.clone(),
            constants: typed_constants,
            variables: typed_vars,
            procedures: typed_procs,
            statements: typed_stmts,
        })
    }

    fn analyze_stmt(&mut self, stmt: &Stmt) -> Result<typed::TypedStmt, String> {
        match stmt {
            Stmt::Compound(stmts) => {
                let mut typed_stmts = Vec::new();
                for s in stmts {
                    typed_stmts.push(self.analyze_stmt(s)?);
                }
                Ok(typed::TypedStmt::Compound(typed_stmts))
            }
            Stmt::Assignment { target, value } => {
                let typed_target = self.analyze_expr(target)?;
                let typed_value = self.analyze_expr(value)?;
                Ok(typed::TypedStmt::Assignment {
                    target: typed_target,
                    value: typed_value,
                })
            }
            Stmt::If {
                condition,
                then_stmt,
                else_stmt,
            } => {
                let typed_cond = self.analyze_expr(condition)?;
                let typed_then = self.analyze_stmt(then_stmt)?;
                let typed_else = if let Some(e) = else_stmt {
                    Some(Box::new(self.analyze_stmt(e)?))
                } else {
                    None
                };
                Ok(typed::TypedStmt::If {
                    condition: typed_cond,
                    then_stmt: Box::new(typed_then),
                    else_stmt: typed_else,
                })
            }
            Stmt::While { condition, body } => {
                let typed_cond = self.analyze_expr(condition)?;
                let typed_body = self.analyze_stmt(body)?;
                Ok(typed::TypedStmt::While {
                    condition: typed_cond,
                    body: Box::new(typed_body),
                })
            }
            Stmt::Repeat { body, until } => {
                let mut typed_body = Vec::new();
                for s in body {
                    typed_body.push(self.analyze_stmt(s)?);
                }
                let typed_until = self.analyze_expr(until)?;
                Ok(typed::TypedStmt::Repeat {
                    body: typed_body,
                    until: typed_until,
                })
            }
            Stmt::For {
                id,
                id_span,
                start,
                up,
                end,
                body,
            } => {
                self.record_reference(id, *id_span);
                let typed_start = self.analyze_expr(start)?;
                let typed_end = self.analyze_expr(end)?;
                let typed_body = self.analyze_stmt(body)?;
                Ok(typed::TypedStmt::For {
                    id: id.clone(),
                    start: typed_start,
                    up: *up,
                    end: typed_end,
                    body: Box::new(typed_body),
                })
            }
            Stmt::ProcedureCall {
                name,
                name_span,
                args,
            } => {
                self.record_reference(name, *name_span);
                let mut typed_args = Vec::new();
                if let Some(args_vec) = args {
                    for arg in args_vec {
                        typed_args.push(self.analyze_expr(arg)?);
                    }
                }
                Ok(typed::TypedStmt::ProcedureCall {
                    name: name.clone(),
                    args: typed_args,
                })
            }
            Stmt::With { ids, body } => {
                self.symbol_table.enter_scope();
                let mut typed_objects = Vec::new();
                for id_expr in ids {
                    let typed_obj = self.analyze_expr(id_expr)?;
                    typed_objects.push(typed_obj.clone());
                    if let typed::Type::Record { fields } = &typed_obj.ty {
                        let field_defs: Vec<(String, SymbolKind)> = fields
                            .iter()
                            .map(|(f_n, f_t)| {
                                (
                                    f_n.clone(),
                                    SymbolKind::Variable {
                                        type_expr: self.convert_to_legacy_type(f_t),
                                    },
                                )
                            })
                            .collect();
                        for (f_n, kind) in field_defs {
                            self.symbol_table.insert(f_n, kind, Span::default())?;
                        }
                    }
                }
                let typed_body = self.analyze_stmt(body)?;
                self.symbol_table.exit_scope();
                Ok(typed::TypedStmt::With {
                    objects: typed_objects,
                    body: Box::new(typed_body),
                })
            }
            Stmt::Goto(l) => Ok(typed::TypedStmt::Goto(*l)),
            Stmt::Labeled(l, s) => {
                let typed_s = self.analyze_stmt(s)?;
                Ok(typed::TypedStmt::Labeled(*l, Box::new(typed_s)))
            }
            Stmt::Case {
                expr,
                items,
                else_stmt,
            } => {
                let typed_expr = self.analyze_expr(expr)?;
                let mut typed_items = Vec::new();
                for item in items {
                    let mut typed_labels = Vec::new();
                    for l in &item.labels {
                        typed_labels.push(self.analyze_expr(l)?);
                    }
                    let typed_s = self.analyze_stmt(&item.stmt)?;
                    typed_items.push(typed::TypedCaseItem {
                        labels: typed_labels,
                        stmt: typed_s,
                    });
                }
                let typed_else = if let Some(e) = else_stmt {
                    Some(Box::new(self.analyze_stmt(e)?))
                } else {
                    None
                };
                Ok(typed::TypedStmt::Case {
                    expr: typed_expr,
                    items: typed_items,
                    else_stmt: typed_else,
                })
            }
            Stmt::Empty => Ok(typed::TypedStmt::Empty),
        }
    }

    fn analyze_expr(&mut self, expr: &Expr) -> Result<typed::TypedExpr, String> {
        match expr {
            Expr::Integer(n) => Ok(typed::TypedExpr {
                ty: typed::Type::Integer,
                kind: typed::TypedExprKind::Integer(*n),
            }),
            Expr::Real(n) => Ok(typed::TypedExpr {
                ty: typed::Type::Real,
                kind: typed::TypedExprKind::Real(*n),
            }),
            Expr::Boolean(b) => Ok(typed::TypedExpr {
                ty: typed::Type::Boolean,
                kind: typed::TypedExprKind::Boolean(*b),
            }),
            Expr::Char(c) => Ok(typed::TypedExpr {
                ty: typed::Type::Char,
                kind: typed::TypedExprKind::Char(*c),
            }),
            Expr::String(s) => Ok(typed::TypedExpr {
                ty: typed::Type::String,
                kind: typed::TypedExprKind::String(s.clone()),
            }),
            Expr::Variable(v) => {
                let typed_var = self.analyze_variable(v)?;
                let ty = self.get_typed_variable_type(&typed_var);
                Ok(typed::TypedExpr {
                    ty,
                    kind: typed::TypedExprKind::Variable(typed_var),
                })
            }
            Expr::Binary { op, left, right } => {
                let l = self.analyze_expr(left)?;
                let r = self.analyze_expr(right)?;
                let ty = self.resolve_binop_type(&l.ty, &r.ty, op)?;
                Ok(typed::TypedExpr {
                    ty,
                    kind: typed::TypedExprKind::Binary {
                        op: op.clone(),
                        left: Box::new(l),
                        right: Box::new(r),
                    },
                })
            }
            Expr::Unary { op, expr } => {
                let e = self.analyze_expr(expr)?;
                Ok(typed::TypedExpr {
                    ty: e.ty.clone(),
                    kind: typed::TypedExprKind::Unary {
                        op: op.clone(),
                        expr: Box::new(e),
                    },
                })
            }
            Expr::FunctionCall {
                name,
                name_span,
                args,
            } => {
                self.record_reference(name, *name_span);
                let mut typed_args = Vec::new();
                if let Some(args_vec) = args {
                    for arg in args_vec {
                        typed_args.push(self.analyze_expr(arg)?);
                    }
                }
                let ret_ty = if let Some(kind) = self.symbol_table.lookup(name) {
                    match kind {
                        SymbolKind::Function { return_type, .. } => {
                            self.convert_type(&TypeExpr::Simple(return_type.clone()))
                        }
                        SymbolKind::Variable { type_expr } => match self.convert_type(type_expr) {
                            typed::Type::Function(r) => *r,
                            _ => typed::Type::Integer,
                        },
                        _ => typed::Type::Integer,
                    }
                } else {
                    typed::Type::Integer
                };
                Ok(typed::TypedExpr {
                    ty: ret_ty,
                    kind: typed::TypedExprKind::FunctionCall {
                        name: name.clone(),
                        args: typed_args,
                    },
                })
            }
            Expr::Set(els) => {
                let mut typed_els = Vec::new();
                for el in els {
                    match el {
                        Element::Single(e) => {
                            typed_els.push(typed::TypedElement::Single(self.analyze_expr(e)?))
                        }
                        Element::Range(s, e) => typed_els.push(typed::TypedElement::Range(
                            self.analyze_expr(s)?,
                            self.analyze_expr(e)?,
                        )),
                    }
                }
                Ok(typed::TypedExpr {
                    ty: typed::Type::Set(Box::new(typed::Type::Void)),
                    kind: typed::TypedExprKind::Set(typed_els),
                })
            }
            Expr::Nil => Ok(typed::TypedExpr {
                ty: typed::Type::Pointer(Box::new(typed::Type::Void)),
                kind: typed::TypedExprKind::Nil,
            }),
            _ => Err(format!("TypedExpr not implemented: {:?}", expr)),
        }
    }

    fn analyze_variable(&mut self, var: &Variable) -> Result<typed::TypedVariable, String> {
        match var {
            Variable::Id(id, span) => {
                self.record_reference(id, *span);
                Ok(typed::TypedVariable::Id(id.clone()))
            }
            Variable::MemberAccess { record, field } => Ok(typed::TypedVariable::MemberAccess {
                record: Box::new(self.analyze_expr(record)?),
                field: field.clone(),
            }),
            Variable::ArrayAccess { array, indices } => {
                // Lower a multi-index access `a[i, j]` into nested single-index
                // accesses `(a[i])[j]`, matching the nested array type layout.
                let mut cur_expr = self.analyze_expr(array)?;
                let n = indices.len();
                for (k, idx) in indices.iter().enumerate() {
                    let typed_idx = self.analyze_expr(idx)?;
                    let elem_ty = match &cur_expr.ty {
                        typed::Type::Array { element_type, .. } => (**element_type).clone(),
                        _ => typed::Type::Void,
                    };
                    let tv = typed::TypedVariable::ArrayAccess {
                        array: Box::new(cur_expr),
                        index: Box::new(typed_idx),
                    };
                    if k + 1 == n {
                        return Ok(tv);
                    }
                    cur_expr = typed::TypedExpr {
                        ty: elem_ty,
                        kind: typed::TypedExprKind::Variable(tv),
                    };
                }
                Err("Array access without indices".to_string())
            }
            Variable::PointerDeref(p) => Ok(typed::TypedVariable::PointerDeref(Box::new(
                self.analyze_expr(p)?,
            ))),
        }
    }

    fn get_typed_variable_type(&self, var: &typed::TypedVariable) -> typed::Type {
        match var {
            typed::TypedVariable::Id(id) => {
                if let Some(kind) = self.symbol_table.lookup(id) {
                    match kind {
                        SymbolKind::Variable { type_expr } => self.convert_type(type_expr),
                        SymbolKind::Constant { type_expr, .. } => self.convert_type(type_expr),
                        SymbolKind::Function { return_type, .. } => {
                            self.convert_type(&TypeExpr::Simple(return_type.clone()))
                        }
                        _ => typed::Type::Void,
                    }
                } else {
                    typed::Type::Void
                }
            }
            typed::TypedVariable::MemberAccess { record, field } => {
                if let typed::Type::Record { fields } = &record.ty {
                    for (f, ty) in fields {
                        if f == field {
                            return ty.clone();
                        }
                    }
                }
                typed::Type::Void
            }
            typed::TypedVariable::ArrayAccess { array, .. } => {
                if let typed::Type::Array { element_type, .. } = &array.ty {
                    *element_type.clone()
                } else {
                    typed::Type::Void
                }
            }
            typed::TypedVariable::PointerDeref(p) => {
                if let typed::Type::Pointer(inner) = &p.ty {
                    *inner.clone()
                } else {
                    typed::Type::Void
                }
            }
        }
    }

    fn resolve_binop_type(
        &self,
        lt: &typed::Type,
        rt: &typed::Type,
        op: &BinOp,
    ) -> Result<typed::Type, String> {
        // Set algebra: union (+), difference (-), intersection (*) keep the set type.
        if matches!(lt, typed::Type::Set(_)) || matches!(rt, typed::Type::Set(_)) {
            if let BinOp::Add | BinOp::Sub | BinOp::Mul = op {
                let set_ty = if matches!(lt, typed::Type::Set(_)) {
                    lt.clone()
                } else {
                    rt.clone()
                };
                return Ok(set_ty);
            }
        }
        match op {
            BinOp::Add => {
                if *lt == typed::Type::String
                    || *rt == typed::Type::String
                    || *lt == typed::Type::Char
                    || *rt == typed::Type::Char
                {
                    return Ok(typed::Type::String);
                }
                if *lt == typed::Type::Real || *rt == typed::Type::Real {
                    Ok(typed::Type::Real)
                } else {
                    Ok(typed::Type::Integer)
                }
            }
            BinOp::Sub | BinOp::Mul => {
                if *lt == typed::Type::Real || *rt == typed::Type::Real {
                    Ok(typed::Type::Real)
                } else {
                    Ok(typed::Type::Integer)
                }
            }
            BinOp::FloatDiv => Ok(typed::Type::Real),
            BinOp::Div | BinOp::Mod => Ok(typed::Type::Integer),
            _ => Ok(typed::Type::Boolean),
        }
    }

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
                    } else if name.starts_with("function:") {
                        typed::Type::Function(Box::new(self.convert_type(&TypeExpr::Simple(
                            name["function:".len()..].to_string(),
                        ))))
                    } else {
                        typed::Type::Integer
                    }
                }
            },
            TypeExpr::Array {
                indices,
                element_type,
            } => {
                // Build a nested array type, one level per index dimension, so
                // that `array[1..3, 1..2] of T` becomes Array(Array(T)).
                let mut ty = self.convert_type(element_type);
                let levels = indices.len().max(1);
                for _ in 0..levels {
                    ty = typed::Type::Array {
                        element_type: Box::new(ty),
                        size: 100,
                    };
                }
                ty
            }
            TypeExpr::Record {
                fields,
                variant_part,
            } => {
                let mut f_vec = Vec::new();
                for f in fields {
                    let ft = self.convert_type(&f.type_expr);
                    for id in &f.ids {
                        f_vec.push((id.clone(), ft.clone()));
                    }
                }
                if let Some(vp) = variant_part {
                    if let Some(tag) = &vp.tag_field {
                        f_vec.push((
                            tag.clone(),
                            self.convert_type(&TypeExpr::Simple(vp.tag_type.clone())),
                        ));
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
            TypeExpr::Pointer(inner) => typed::Type::Pointer(Box::new(self.convert_type(inner))),
            TypeExpr::Set(inner) => typed::Type::Set(Box::new(self.convert_type(inner))),
            TypeExpr::Enum(ids) => typed::Type::Enum(ids.clone()),
            TypeExpr::Subrange { .. } => typed::Type::Integer,
            TypeExpr::File(inner) => typed::Type::Pointer(Box::new(self.convert_type(inner))),
            _ => typed::Type::Void,
        }
    }

    fn convert_to_legacy_type(&self, ty: &typed::Type) -> TypeExpr {
        match ty {
            typed::Type::Integer => TypeExpr::Simple("integer".to_string()),
            typed::Type::Real => TypeExpr::Simple("real".to_string()),
            typed::Type::Boolean => TypeExpr::Simple("boolean".to_string()),
            typed::Type::Char => TypeExpr::Simple("char".to_string()),
            typed::Type::String => TypeExpr::Simple("string".to_string()),
            _ => TypeExpr::Simple("unknown".to_string()),
        }
    }

    fn import_uses(&mut self, uses: &Option<Vec<String>>) -> Result<(), String> {
        if let Some(units) = uses {
            for u_name in units {
                if let Some(interface) = self
                    .external_interfaces
                    .get(&u_name.to_lowercase())
                    .cloned()
                {
                    for (name, kind) in interface {
                        let _ = self.symbol_table.insert(name, kind, Span::default());
                    }
                }
            }
        }
        Ok(())
    }

    fn add_params_to_scope(&mut self, params: &Option<Vec<Param>>) -> Result<(), String> {
        if let Some(params_vec) = params {
            for p in params_vec {
                match p {
                    Param::Variable {
                        ids,
                        id_spans,
                        type_name,
                        ..
                    } => {
                        for (i, id) in ids.iter().enumerate() {
                            let span = id_spans.get(i).copied().unwrap_or_default();
                            self.define(
                                id.clone(),
                                SymbolKind::Variable {
                                    type_expr: TypeExpr::Simple(type_name.clone()),
                                },
                                span,
                            )?;
                        }
                    }
                    Param::Procedure {
                        id,
                        id_span,
                        params,
                    } => {
                        self.define(
                            id.clone(),
                            SymbolKind::Procedure {
                                params: params.clone().unwrap_or_default(),
                                external_name: None,
                            },
                            *id_span,
                        )?;
                    }
                    Param::Function {
                        id,
                        id_span,
                        params,
                        return_type,
                    } => {
                        self.define(
                            id.clone(),
                            SymbolKind::Function {
                                params: params.clone().unwrap_or_default(),
                                return_type: return_type.clone(),
                                external_name: None,
                            },
                            *id_span,
                        )?;
                    }
                }
            }
        }
        Ok(())
    }
}
