use crate::ast::*;
use crate::symbol_table::SymbolKind;
use crate::typed_ast as typed;
use inkwell::builder::Builder;
use inkwell::context::Context;
use inkwell::module::Module;
use inkwell::types::BasicType;
use inkwell::values::{BasicValue, BasicValueEnum, FunctionValue, PointerValue};
use std::collections::HashMap;

pub struct CodeGen<'ctx> {
    pub context: &'ctx Context,
    pub module: Module<'ctx>,
    pub builder: Builder<'ctx>,
    pub verbose: bool,
    variables: Vec<
        HashMap<
            String,
            (
                PointerValue<'ctx>,
                inkwell::types::BasicTypeEnum<'ctx>,
                TypeExpr,
            ),
        >,
    >,
    types: HashMap<String, (inkwell::types::BasicTypeEnum<'ctx>, TypeExpr)>,
    record_fields: HashMap<String, HashMap<String, u32>>,
    labels: HashMap<i64, inkwell::basic_block::BasicBlock<'ctx>>,
    external_interfaces: HashMap<String, HashMap<String, SymbolKind>>,
}

impl<'ctx> CodeGen<'ctx> {
    pub fn new(context: &'ctx Context, module_name: &str) -> Self {
        let mut cg = Self {
            context,
            module: context.create_module(module_name),
            builder: context.create_builder(),
            verbose: false,
            variables: vec![HashMap::new()],
            types: HashMap::new(),
            record_fields: HashMap::new(),
            labels: HashMap::new(),
            external_interfaces: HashMap::new(),
        };
        cg.setup_builtins();
        cg
    }

    pub fn with_interfaces(
        context: &'ctx Context,
        module_name: &str,
        interfaces: HashMap<String, HashMap<String, SymbolKind>>,
    ) -> Self {
        let mut cg = Self::new(context, module_name);
        cg.external_interfaces = interfaces;
        cg
    }

    fn setup_builtins(&mut self) {
        let i64_t = self.context.i64_type();
        let maxint = self.module.add_global(i64_t, None, "maxint");
        maxint.set_linkage(inkwell::module::Linkage::Internal);
        maxint.set_initializer(&i64_t.const_int(i64::MAX as u64, false));
        maxint.set_constant(true);
        self.variables[0].insert(
            "maxint".to_string(),
            (
                maxint.as_pointer_value(),
                i64_t.as_basic_type_enum(),
                TypeExpr {
                    span: Span::default(),
                    node: TypeExprKind::Simple("integer".to_string()),
                },
            ),
        );

        let void_t = self.context.void_type();
        let f64_t = self.context.f64_type();
        let i32_t = self.context.i32_type();

        self.module.add_function(
            "pascal_runtime_init",
            void_t.fn_type(&[], false),
            Some(inkwell::module::Linkage::External),
        );
        self.module.add_function(
            "pascal_sqrt",
            f64_t.fn_type(&[f64_t.into()], false),
            Some(inkwell::module::Linkage::External),
        );
        self.module.add_function(
            "pascal_halt",
            void_t.fn_type(&[i32_t.into()], false),
            Some(inkwell::module::Linkage::External),
        );
    }

    fn get_printf(&self) -> FunctionValue<'ctx> {
        if let Some(f) = self.module.get_function("printf") {
            return f;
        }
        let i32_t = self.context.i32_type();
        let ptr_t = self.context.ptr_type(inkwell::AddressSpace::default());
        self.module
            .add_function("printf", i32_t.fn_type(&[ptr_t.into()], true), None)
    }

    fn get_scanf(&self) -> FunctionValue<'ctx> {
        if let Some(f) = self.module.get_function("scanf") {
            return f;
        }
        let i32_t = self.context.i32_type();
        let ptr_t = self.context.ptr_type(inkwell::AddressSpace::default());
        self.module
            .add_function("scanf", i32_t.fn_type(&[ptr_t.into()], true), None)
    }

    fn enter_scope(&mut self) {
        self.variables.push(HashMap::new());
    }
    fn exit_scope(&mut self) {
        self.variables.pop();
    }

    fn get_variable(
        &self,
        name: &str,
    ) -> Option<&(
        PointerValue<'ctx>,
        inkwell::types::BasicTypeEnum<'ctx>,
        TypeExpr,
    )> {
        for s in self.variables.iter().rev() {
            if let Some(v) = s.get(name) {
                return Some(v);
            }
        }
        None
    }

    pub fn gen_program(
        &mut self,
        program: typed::TypedProgram,
        module_interfaces: HashMap<String, HashMap<String, SymbolKind>>,
    ) -> Result<(), String> {
        self.external_interfaces = module_interfaces;
        self.declare_external_interfaces();
        let i32_t = self.context.i32_type();
        let function = self
            .module
            .add_function("main", i32_t.fn_type(&[], false), None);
        let bb = self.context.append_basic_block(function, "entry");
        self.builder.position_at_end(bb);

        // Call initialization functions for all units used
        let void_t = self.context.void_type();
        for unit_name in &program.uses {
            let init_fn_name = format!("{}_init", unit_name.to_lowercase());
            let init_fn = if let Some(f) = self.module.get_function(&init_fn_name) {
                f
            } else {
                self.module.add_function(
                    &init_fn_name,
                    void_t.fn_type(&[], false),
                    Some(inkwell::module::Linkage::External),
                )
            };
            self.builder
                .build_call(init_fn, &[], &format!("{}_call", init_fn_name))
                .unwrap();
        }

        self.gen_typed_block(&program.block, function)?;
        self.builder
            .build_return(Some(&i32_t.const_int(0, false)))
            .unwrap();
        Ok(())
    }

    pub fn gen_unit(
        &mut self,
        block: typed::TypedBlock,
        module_interfaces: HashMap<String, HashMap<String, SymbolKind>>,
    ) -> Result<(), String> {
        self.external_interfaces = module_interfaces;
        self.declare_external_interfaces();
        for p in &block.procedures {
            self.gen_typed_proc_func(p)?;
        }

        if !block.statements.is_empty() {
            let void_t = self.context.void_type();
            let init_fn_name = format!(
                "{}_init",
                self.module.get_name().to_str().unwrap().to_lowercase()
            );
            let function =
                self.module
                    .add_function(&init_fn_name, void_t.fn_type(&[], false), None);
            let bb = self.context.append_basic_block(function, "entry");
            self.builder.position_at_end(bb);
            for stmt in &block.statements {
                self.gen_typed_stmt(stmt, function)?;
            }
            self.builder.build_return(None).unwrap();
        } else {
            // Even if empty, create a dummy init function to satisfy link dependencies
            let void_t = self.context.void_type();
            let init_fn_name = format!(
                "{}_init",
                self.module.get_name().to_str().unwrap().to_lowercase()
            );
            if self.module.get_function(&init_fn_name).is_none() {
                let function =
                    self.module
                        .add_function(&init_fn_name, void_t.fn_type(&[], false), None);
                let bb = self.context.append_basic_block(function, "entry");
                self.builder.position_at_end(bb);
                self.builder.build_return(None).unwrap();
            }
        }
        Ok(())
    }

    fn declare_external_interfaces(&mut self) {
        let interfaces = self.external_interfaces.clone();
        for (_, interface) in interfaces {
            for (name, kind) in interface {
                match kind {
                    SymbolKind::Procedure { params } => {
                        self.declare_external_fn(&name, &params, None);
                    }
                    SymbolKind::Function {
                        params,
                        return_type,
                    } => {
                        self.declare_external_fn(&name, &params, Some(&return_type));
                    }
                    _ => {}
                }
            }
        }
    }

    fn declare_external_fn(&mut self, name: &str, params: &[Param], return_type: Option<&String>) {
        println!("Declaring external function: {}", name);
        if self.module.get_function(name).is_some() {
            return;
        }

        let mut a_t = Vec::new();
        for p in params {
            match &p.node {
                ParamKind::Variable { ids, type_expr, .. } => {
                    if let Ok(lt) = self.resolve_type(type_expr) {
                        for _ in ids {
                            a_t.push(lt.into());
                        }
                    }
                }
                ParamKind::Procedure { .. } | ParamKind::Function { .. } => {
                    a_t.push(
                        self.context
                            .ptr_type(inkwell::AddressSpace::default())
                            .into(),
                    );
                }
            }
        }

        if let Some(ret_name) = return_type {
            if let Ok(rt) = self.resolve_type(&TypeExpr {
                span: Span::default(),
                node: TypeExprKind::Simple(ret_name.clone()),
            }) {
                let fn_t = match rt {
                    inkwell::types::BasicTypeEnum::IntType(t) => t.fn_type(&a_t, false),
                    inkwell::types::BasicTypeEnum::FloatType(t) => t.fn_type(&a_t, false),
                    inkwell::types::BasicTypeEnum::PointerType(t) => t.fn_type(&a_t, false),
                    _ => self.context.void_type().fn_type(&a_t, false),
                };
                self.module
                    .add_function(name, fn_t, Some(inkwell::module::Linkage::External));
            }
        } else {
            let fn_t = self.context.void_type().fn_type(&a_t, false);
            self.module
                .add_function(name, fn_t, Some(inkwell::module::Linkage::External));
        }
    }

    fn get_function_robust(&mut self, name: &str) -> Option<FunctionValue<'ctx>> {
        if self.verbose {
            println!("Searching for function: {}", name);
        }
        if let Some(f) = self.module.get_function(name) {
            return Some(f);
        }
        // Try case-insensitive LLVM search
        let name_lower = name.to_lowercase();
        let mut f_ptr = None;
        for f in self.module.get_functions() {
            if f.get_name().to_str().unwrap().to_lowercase() == name_lower {
                f_ptr = Some(f);
                break;
            }
        }
        if f_ptr.is_some() {
            return f_ptr;
        }

        // Search in external interfaces
        let interfaces = self.external_interfaces.clone();
        if self.verbose {
            println!(
                "Searching in external interfaces (count: {})",
                interfaces.len()
            );
        }
        for (u_name, interface) in interfaces {
            if self.verbose {
                println!("Checking unit {}: symbols={:?}", u_name, interface.keys());
            }
            for (sym_name, kind) in interface {
                if sym_name.to_lowercase() == name_lower {
                    if self.verbose {
                        println!("Found match in unit {}: {}", u_name, sym_name);
                    }
                    match kind {
                        SymbolKind::Procedure { params } => {
                            self.declare_external_fn(&sym_name, &params, None);
                            return self.module.get_function(&sym_name);
                        }
                        SymbolKind::Function {
                            params,
                            return_type,
                        } => {
                            self.declare_external_fn(&sym_name, &params, Some(&return_type));
                            return self.module.get_function(&sym_name);
                        }
                        _ => {}
                    }
                }
            }
        }

        // Final fallback: try to find again by lowercase if we declared it with a different name
        for f in self.module.get_functions() {
            if f.get_name().to_str().unwrap().to_lowercase() == name_lower {
                return Some(f);
            }
        }
        None
    }

    fn gen_typed_block(
        &mut self,
        block: &typed::TypedBlock,
        function: FunctionValue<'ctx>,
    ) -> Result<(), String> {
        for (name, ty) in &block.variables {
            let l_t = self.resolve_typed_type(ty)?;
            if self.variables.len() == 1 {
                let g = self.module.add_global(l_t, None, name);
                g.set_initializer(&l_t.const_zero());
                self.variables.last_mut().unwrap().insert(
                    name.clone(),
                    (
                        g.as_pointer_value(),
                        l_t,
                        TypeExpr {
                            span: Span::default(),
                            node: TypeExprKind::Simple("unknown".to_string()),
                        },
                    ),
                );
            } else {
                let ptr = self.create_entry_block_alloca(function, name, l_t);
                self.variables.last_mut().unwrap().insert(
                    name.clone(),
                    (
                        ptr,
                        l_t,
                        TypeExpr {
                            span: Span::default(),
                            node: TypeExprKind::Simple("unknown".to_string()),
                        },
                    ),
                );
            }
        }
        for (name, expr) in &block.constants {
            let val = self.gen_typed_expr(expr)?;
            let g = self.module.add_global(val.get_type(), None, name);
            g.set_initializer(&val);
            g.set_constant(true);
            g.set_linkage(inkwell::module::Linkage::Internal);
            self.variables.last_mut().unwrap().insert(
                name.clone(),
                (
                    g.as_pointer_value(),
                    val.get_type(),
                    TypeExpr {
                        span: Span::default(),
                        node: TypeExprKind::Simple("unknown".to_string()),
                    },
                ),
            );
        }
        for p in &block.procedures {
            self.gen_typed_proc_func(p)?;
        }
        for s in &block.statements {
            self.gen_typed_stmt(s, function)?;
        }
        Ok(())
    }

    fn gen_typed_proc_func(&mut self, decl: &typed::TypedProcFunc) -> Result<(), String> {
        let mut a_t = Vec::new();
        for (_, ty, _) in &decl.params {
            a_t.push(self.resolve_typed_type(ty)?.into());
        }
        let ret_t = self.resolve_typed_type(&decl.return_type)?;
        let fn_t = if decl.return_type == typed::Type::Void {
            self.context.void_type().fn_type(&a_t, false)
        } else {
            match ret_t {
                inkwell::types::BasicTypeEnum::IntType(t) => t.fn_type(&a_t, false),
                inkwell::types::BasicTypeEnum::FloatType(t) => t.fn_type(&a_t, false),
                inkwell::types::BasicTypeEnum::PointerType(t) => t.fn_type(&a_t, false),
                _ => self.context.void_type().fn_type(&a_t, false),
            }
        };
        let function = if let Some(f) = self.module.get_function(&decl.name) {
            f
        } else {
            self.module.add_function(&decl.name, fn_t, None)
        };
        if let Some(body) = &decl.body {
            let bb = self.context.append_basic_block(function, "entry");
            let original_bb = self.builder.get_insert_block();
            self.builder.position_at_end(bb);
            self.enter_scope();
            for (i, (name, ty, _)) in decl.params.iter().enumerate() {
                let pt = self.resolve_typed_type(ty)?;
                let val = function.get_nth_param(i as u32).unwrap();
                let ptr = self.create_entry_block_alloca(function, name, pt);
                self.builder.build_store(ptr, val).unwrap();
                self.variables.last_mut().unwrap().insert(
                    name.clone(),
                    (
                        ptr,
                        pt,
                        TypeExpr {
                            span: Span::default(),
                            node: TypeExprKind::Simple("unknown".to_string()),
                        },
                    ),
                );
            }
            if decl.return_type != typed::Type::Void {
                let ptr = self.create_entry_block_alloca(function, &decl.name, ret_t);
                self.variables.last_mut().unwrap().insert(
                    decl.name.clone(),
                    (
                        ptr,
                        ret_t,
                        TypeExpr {
                            span: Span::default(),
                            node: TypeExprKind::Simple("unknown".to_string()),
                        },
                    ),
                );
            }
            self.gen_typed_block(body, function)?;
            if decl.return_type != typed::Type::Void {
                let (ptr, l_t, _) = self.get_variable(&decl.name).unwrap();
                let val = self.builder.build_load(*l_t, *ptr, "retval").unwrap();
                self.builder.build_return(Some(&val)).unwrap();
            } else {
                if self
                    .builder
                    .get_insert_block()
                    .unwrap()
                    .get_terminator()
                    .is_none()
                {
                    self.builder.build_return(None).unwrap();
                }
            }
            self.exit_scope();
            if let Some(obb) = original_bb {
                self.builder.position_at_end(obb);
            }
        }
        Ok(())
    }

    fn gen_typed_stmt(
        &mut self,
        stmt: &typed::TypedStmt,
        function: FunctionValue<'ctx>,
    ) -> Result<(), String> {
        match &stmt.kind {
            typed::TypedStmtKind::Compound(stmts) => {
                for s in stmts {
                    self.gen_typed_stmt(s, function)?;
                }
            }
            typed::TypedStmtKind::Assignment { target, value } => {
                let val = self.gen_typed_expr(value)?;
                let ptr = self.gen_typed_target_ptr(target)?;
                self.builder.build_store(ptr, val).unwrap();
            }
            typed::TypedStmtKind::If {
                condition,
                then_stmt,
                else_stmt,
            } => {
                let cond_val = self.gen_typed_expr(condition)?.into_int_value();
                let then_bb = self.context.append_basic_block(function, "then");
                let else_bb = self.context.append_basic_block(function, "else");
                let merge_bb = self.context.append_basic_block(function, "ifcont");
                self.builder
                    .build_conditional_branch(cond_val, then_bb, else_bb)
                    .unwrap();
                self.builder.position_at_end(then_bb);
                self.gen_typed_stmt(then_stmt, function)?;
                if self
                    .builder
                    .get_insert_block()
                    .unwrap()
                    .get_terminator()
                    .is_none()
                {
                    self.builder.build_unconditional_branch(merge_bb).unwrap();
                }
                self.builder.position_at_end(else_bb);
                if let Some(es) = else_stmt {
                    self.gen_typed_stmt(es, function)?;
                }
                if self
                    .builder
                    .get_insert_block()
                    .unwrap()
                    .get_terminator()
                    .is_none()
                {
                    self.builder.build_unconditional_branch(merge_bb).unwrap();
                }
                self.builder.position_at_end(merge_bb);
            }
            typed::TypedStmtKind::While { condition, body } => {
                let cond_bb = self.context.append_basic_block(function, "whilecond");
                let body_bb = self.context.append_basic_block(function, "whilebody");
                let end_bb = self.context.append_basic_block(function, "whileend");
                self.builder.build_unconditional_branch(cond_bb).unwrap();
                self.builder.position_at_end(cond_bb);
                let cond_val = self.gen_typed_expr(condition)?.into_int_value();
                self.builder
                    .build_conditional_branch(cond_val, body_bb, end_bb)
                    .unwrap();
                self.builder.position_at_end(body_bb);
                self.gen_typed_stmt(body, function)?;
                self.builder.build_unconditional_branch(cond_bb).unwrap();
                self.builder.position_at_end(end_bb);
            }
            typed::TypedStmtKind::Repeat { body, until } => {
                let body_bb = self.context.append_basic_block(function, "repeatbody");
                let end_bb = self.context.append_basic_block(function, "repeatend");
                self.builder.build_unconditional_branch(body_bb).unwrap();
                self.builder.position_at_end(body_bb);
                for s in body {
                    self.gen_typed_stmt(s, function)?;
                }
                let cond_val = self.gen_typed_expr(until)?.into_int_value();
                self.builder
                    .build_conditional_branch(cond_val, end_bb, body_bb)
                    .unwrap();
                self.builder.position_at_end(end_bb);
            }
            typed::TypedStmtKind::For {
                id,
                start,
                up,
                end,
                body,
            } => {
                let start_val = self.gen_typed_expr(start)?;
                let end_val = self.gen_typed_expr(end)?;
                let (ptr, l_t, _) = self
                    .get_variable(id)
                    .ok_or_else(|| format!("For variable {} not found", id))?
                    .clone();
                self.builder.build_store(ptr, start_val).unwrap();
                let cond_bb = self.context.append_basic_block(function, "forcond");
                let body_bb = self.context.append_basic_block(function, "forbody");
                let end_bb = self.context.append_basic_block(function, "forend");
                self.builder.build_unconditional_branch(cond_bb).unwrap();
                self.builder.position_at_end(cond_bb);
                let curr_val = self.builder.build_load(l_t, ptr, "curr").unwrap();
                let cond = if *up {
                    self.builder
                        .build_int_compare(
                            inkwell::IntPredicate::SLE,
                            curr_val.into_int_value(),
                            end_val.into_int_value(),
                            "forcond",
                        )
                        .unwrap()
                } else {
                    self.builder
                        .build_int_compare(
                            inkwell::IntPredicate::SGE,
                            curr_val.into_int_value(),
                            end_val.into_int_value(),
                            "forcond",
                        )
                        .unwrap()
                };
                self.builder
                    .build_conditional_branch(cond, body_bb, end_bb)
                    .unwrap();
                self.builder.position_at_end(body_bb);
                self.gen_typed_stmt(body, function)?;
                let next_val = if *up {
                    self.builder
                        .build_int_add(
                            self.builder
                                .build_load(l_t, ptr, "inc")
                                .unwrap()
                                .into_int_value(),
                            self.context.i64_type().const_int(1, false),
                            "next",
                        )
                        .unwrap()
                } else {
                    self.builder
                        .build_int_sub(
                            self.builder
                                .build_load(l_t, ptr, "dec")
                                .unwrap()
                                .into_int_value(),
                            self.context.i64_type().const_int(1, false),
                            "next",
                        )
                        .unwrap()
                };
                self.builder.build_store(ptr, next_val).unwrap();
                self.builder.build_unconditional_branch(cond_bb).unwrap();
                self.builder.position_at_end(end_bb);
            }
            typed::TypedStmtKind::ProcedureCall { name, args } => {
                if name == "write" || name == "writeln" {
                    let printf = self.get_printf();
                    for arg in args {
                        let val = self.gen_typed_expr(arg)?;
                        let fmt = match &arg.ty {
                            typed::Type::Integer => "%lld",
                            typed::Type::Real => "%f",
                            typed::Type::Char => "%c",
                            typed::Type::String => "%s",
                            typed::Type::Boolean => "%d",
                            _ => "%p",
                        };
                        let fmt_val = self
                            .builder
                            .build_global_string_ptr(fmt, "fmt")
                            .unwrap()
                            .as_pointer_value();
                        self.builder
                            .build_call(printf, &[fmt_val.into(), val.into()], "printf")
                            .unwrap();
                    }
                    if name == "writeln" {
                        let nl = self
                            .builder
                            .build_global_string_ptr("\n", "nl")
                            .unwrap()
                            .as_pointer_value();
                        self.builder
                            .build_call(printf, &[nl.into()], "printf")
                            .unwrap();
                    }
                } else {
                    let mut l_a = Vec::new();
                    for a in args {
                        l_a.push(self.gen_typed_expr(a)?.into());
                    }
                    let real_name = match name.as_str() {
                        "read" | "readln" => name.as_str(),
                        _ => name.as_str(),
                    };

                    let call_res = if let Some(f_c) = self.get_function_robust(real_name) {
                        Some(self.builder.build_call(f_c, &l_a, "call").unwrap())
                    } else if let Some((p, l_t, _)) = self.get_variable(name).cloned() {
                        let f_p = self
                            .builder
                            .build_load(l_t, p, "fnptr")
                            .unwrap()
                            .into_pointer_value();
                        let mut a_t = Vec::new();
                        for a in &l_a {
                            let b_v = match a {
                                inkwell::values::BasicMetadataValueEnum::IntValue(i) => {
                                    i.as_basic_value_enum()
                                }
                                inkwell::values::BasicMetadataValueEnum::FloatValue(f) => {
                                    f.as_basic_value_enum()
                                }
                                inkwell::values::BasicMetadataValueEnum::PointerValue(p) => {
                                    p.as_basic_value_enum()
                                }
                                _ => unreachable!(),
                            };
                            a_t.push(b_v.get_type().into());
                        }
                        let fn_t = self.context.void_type().fn_type(&a_t, false);
                        Some(
                            self.builder
                                .build_indirect_call(fn_t, f_p, &l_a, "call")
                                .unwrap(),
                        )
                    } else {
                        // Try to re-declare if it's an external interface procedure we missed
                        self.declare_external_interfaces();
                        if let Some(f_c) = self.module.get_function(real_name) {
                            Some(self.builder.build_call(f_c, &l_a, "call").unwrap())
                        } else {
                            None
                        }
                    };

                    if call_res.is_none() {
                        return Err(format!("Procedure {} not found", name));
                    }
                }
            }
            typed::TypedStmtKind::Goto(l) => {
                let bb = self.get_or_create_label_bb(function, *l);
                self.builder.build_unconditional_branch(bb).unwrap();
            }
            typed::TypedStmtKind::Labeled(l, s) => {
                let bb = self.get_or_create_label_bb(function, *l);
                if self
                    .builder
                    .get_insert_block()
                    .unwrap()
                    .get_terminator()
                    .is_none()
                {
                    self.builder.build_unconditional_branch(bb).unwrap();
                }
                self.builder.position_at_end(bb);
                self.gen_typed_stmt(s, function)?;
            }
            typed::TypedStmtKind::Case {
                expr,
                items,
                else_stmt,
            } => {
                let c_v = self.gen_typed_expr(expr)?.into_int_value();
                let m_bb = self.context.append_basic_block(function, "casemerge");
                let e_bb = self.context.append_basic_block(function, "caseelse");
                let mut c_s = Vec::new();
                let mut c_bbs = Vec::new();
                for item in items {
                    let c_bb = self.context.append_basic_block(function, "caseitem");
                    for label in &item.labels {
                        match &label.kind {
                            typed::TypedExprKind::Integer(n) => c_s
                                .push((self.context.i64_type().const_int(*n as u64, false), c_bb)),
                            typed::TypedExprKind::Variable(typed::TypedVariable::Id(id)) => {
                                if let Some(v) = self.get_variable(id) {
                                    let (_p, _l_t, _) = v;
                                    // This is a bit hacky, but for global constants we try to get the initializer
                                    if let Some(g) = self.module.get_global(id) {
                                        if let Some(init) = g.get_initializer() {
                                            if init.is_int_value() {
                                                c_s.push((init.into_int_value(), c_bb));
                                            }
                                        }
                                    }
                                }
                            }
                            _ => {}
                        }
                    }
                    c_bbs.push((c_bb, &item.stmt));
                }
                self.builder.build_switch(c_v, e_bb, &c_s).unwrap();
                for (bb, stmt) in c_bbs {
                    self.builder.position_at_end(bb);
                    self.gen_typed_stmt(stmt, function)?;
                    if self
                        .builder
                        .get_insert_block()
                        .unwrap()
                        .get_terminator()
                        .is_none()
                    {
                        self.builder.build_unconditional_branch(m_bb).unwrap();
                    }
                }
                self.builder.position_at_end(e_bb);
                if let Some(e) = else_stmt {
                    self.gen_typed_stmt(e, function)?;
                }
                if self
                    .builder
                    .get_insert_block()
                    .unwrap()
                    .get_terminator()
                    .is_none()
                {
                    self.builder.build_unconditional_branch(m_bb).unwrap();
                }
                self.builder.position_at_end(m_bb);
            }
            typed::TypedStmtKind::With { objects, body } => {
                self.enter_scope();
                for obj in objects {
                    let (ptr, l_t) = self.gen_typed_variable_ptr_from_expr(obj)?;
                    if let typed::Type::Record { fields: _ } = &obj.ty {
                        let t_k = format!("{:?}", l_t);
                        if let Some(f_i) = self.record_fields.get(&t_k) {
                            for (f_n, &idx) in f_i {
                                let m_p = self
                                    .builder
                                    .build_struct_gep(l_t.into_struct_type(), ptr, idx, f_n)
                                    .unwrap();
                                let m_t =
                                    l_t.into_struct_type().get_field_type_at_index(idx).unwrap();
                                self.variables.last_mut().unwrap().insert(
                                    f_n.clone(),
                                    (
                                        m_p,
                                        m_t,
                                        TypeExpr {
                                            span: Span::default(),
                                            node: TypeExprKind::Simple("unknown".to_string()),
                                        },
                                    ),
                                );
                            }
                        }
                    }
                }
                self.gen_typed_stmt(body, function)?;
                self.exit_scope();
            }
            typed::TypedStmtKind::Empty => {
                let z = self.context.i64_type().const_zero();
                self.builder.build_or(z, z, "nop").unwrap();
            }
        }
        Ok(())
    }

    fn gen_typed_expr(&mut self, expr: &typed::TypedExpr) -> Result<BasicValueEnum<'ctx>, String> {
        if expr.ty == typed::Type::Error {
            return Err("Cannot generate code for expression with semantic errors".to_string());
        }
        match &expr.kind {
            typed::TypedExprKind::Integer(n) => {
                Ok(self.context.i64_type().const_int(*n as u64, false).into())
            }
            typed::TypedExprKind::Real(n) => Ok(self.context.f64_type().const_float(*n).into()),
            typed::TypedExprKind::Boolean(b) => {
                Ok(self.context.bool_type().const_int(*b as u64, false).into())
            }
            typed::TypedExprKind::Char(c) => {
                Ok(self.context.i8_type().const_int(*c as u64, false).into())
            }
            typed::TypedExprKind::String(s) => Ok(self
                .builder
                .build_global_string_ptr(s, "str")
                .unwrap()
                .as_pointer_value()
                .into()),
            typed::TypedExprKind::Variable(v) => match self.gen_typed_variable_ptr(v) {
                Ok((p, l_t)) => Ok(self.builder.build_load(l_t, p, "load").unwrap()),
                Err(e) => {
                    if let typed::TypedVariable::Id(id) = v {
                        if let Some(f) = self.module.get_function(id) {
                            return Ok(f.as_global_value().as_pointer_value().into());
                        }
                    }
                    return Err(e);
                }
            },
            typed::TypedExprKind::Binary { op, left, right } => {
                let l = self.gen_typed_expr(left)?;
                let r = self.gen_typed_expr(right)?;
                let mut lhs = l;
                let mut rhs = r;
                if op == &BinOp::In {
                    let e = lhs.into_int_value();
                    let s = rhs.into_int_value();
                    let s_t = s.get_type();
                    let bit = self.builder.build_int_z_extend(e, s_t, "bitext").unwrap();
                    let m = self
                        .builder
                        .build_left_shift(s_t.const_int(1, false), bit, "mask")
                        .unwrap();
                    let a = self.builder.build_and(s, m, "setand").unwrap();
                    return Ok(self
                        .builder
                        .build_int_compare(inkwell::IntPredicate::NE, a, s_t.const_zero(), "isset")
                        .unwrap()
                        .into());
                }
                if lhs.get_type() != rhs.get_type() {
                    if lhs.is_int_value() && rhs.is_float_value() {
                        lhs = self
                            .builder
                            .build_signed_int_to_float(
                                lhs.into_int_value(),
                                rhs.get_type().into_float_type(),
                                "sitofp",
                            )
                            .unwrap()
                            .into();
                    } else if lhs.is_float_value() && rhs.is_int_value() {
                        rhs = self
                            .builder
                            .build_signed_int_to_float(
                                rhs.into_int_value(),
                                lhs.get_type().into_float_type(),
                                "sitofp",
                            )
                            .unwrap()
                            .into();
                    }
                }
                match op {
                    BinOp::Add => {
                        if lhs.is_int_value() {
                            Ok(self
                                .builder
                                .build_int_add(lhs.into_int_value(), rhs.into_int_value(), "add")
                                .unwrap()
                                .into())
                        } else {
                            Ok(self
                                .builder
                                .build_float_add(
                                    lhs.into_float_value(),
                                    rhs.into_float_value(),
                                    "fadd",
                                )
                                .unwrap()
                                .into())
                        }
                    }
                    BinOp::Sub => {
                        if lhs.is_int_value() {
                            Ok(self
                                .builder
                                .build_int_sub(lhs.into_int_value(), rhs.into_int_value(), "sub")
                                .unwrap()
                                .into())
                        } else {
                            Ok(self
                                .builder
                                .build_float_sub(
                                    lhs.into_float_value(),
                                    rhs.into_float_value(),
                                    "fsub",
                                )
                                .unwrap()
                                .into())
                        }
                    }
                    BinOp::Mul => {
                        if lhs.is_int_value() {
                            Ok(self
                                .builder
                                .build_int_mul(lhs.into_int_value(), rhs.into_int_value(), "mul")
                                .unwrap()
                                .into())
                        } else {
                            Ok(self
                                .builder
                                .build_float_mul(
                                    lhs.into_float_value(),
                                    rhs.into_float_value(),
                                    "fmul",
                                )
                                .unwrap()
                                .into())
                        }
                    }
                    BinOp::Div => Ok(self
                        .builder
                        .build_int_signed_div(lhs.into_int_value(), rhs.into_int_value(), "div")
                        .unwrap()
                        .into()),
                    BinOp::Mod => Ok(self
                        .builder
                        .build_int_signed_rem(lhs.into_int_value(), rhs.into_int_value(), "rem")
                        .unwrap()
                        .into()),
                    BinOp::FloatDiv => Ok(self
                        .builder
                        .build_float_div(lhs.into_float_value(), rhs.into_float_value(), "fdiv")
                        .unwrap()
                        .into()),
                    BinOp::Eq => {
                        if lhs.is_int_value() {
                            Ok(self
                                .builder
                                .build_int_compare(
                                    inkwell::IntPredicate::EQ,
                                    lhs.into_int_value(),
                                    rhs.into_int_value(),
                                    "eq",
                                )
                                .unwrap()
                                .into())
                        } else {
                            Ok(self
                                .builder
                                .build_float_compare(
                                    inkwell::FloatPredicate::OEQ,
                                    lhs.into_float_value(),
                                    rhs.into_float_value(),
                                    "feq",
                                )
                                .unwrap()
                                .into())
                        }
                    }
                    BinOp::Neq => {
                        if lhs.is_int_value() {
                            Ok(self
                                .builder
                                .build_int_compare(
                                    inkwell::IntPredicate::NE,
                                    lhs.into_int_value(),
                                    rhs.into_int_value(),
                                    "ne",
                                )
                                .unwrap()
                                .into())
                        } else {
                            Ok(self
                                .builder
                                .build_float_compare(
                                    inkwell::FloatPredicate::ONE,
                                    lhs.into_float_value(),
                                    rhs.into_float_value(),
                                    "fne",
                                )
                                .unwrap()
                                .into())
                        }
                    }
                    BinOp::Lt => {
                        if lhs.is_int_value() {
                            Ok(self
                                .builder
                                .build_int_compare(
                                    inkwell::IntPredicate::SLT,
                                    lhs.into_int_value(),
                                    rhs.into_int_value(),
                                    "lt",
                                )
                                .unwrap()
                                .into())
                        } else {
                            Ok(self
                                .builder
                                .build_float_compare(
                                    inkwell::FloatPredicate::OLT,
                                    lhs.into_float_value(),
                                    rhs.into_float_value(),
                                    "flt",
                                )
                                .unwrap()
                                .into())
                        }
                    }
                    BinOp::Lte => {
                        if lhs.is_int_value() {
                            Ok(self
                                .builder
                                .build_int_compare(
                                    inkwell::IntPredicate::SLE,
                                    lhs.into_int_value(),
                                    rhs.into_int_value(),
                                    "le",
                                )
                                .unwrap()
                                .into())
                        } else {
                            Ok(self
                                .builder
                                .build_float_compare(
                                    inkwell::FloatPredicate::OLE,
                                    lhs.into_float_value(),
                                    rhs.into_float_value(),
                                    "fle",
                                )
                                .unwrap()
                                .into())
                        }
                    }
                    BinOp::Gt => {
                        if lhs.is_int_value() {
                            Ok(self
                                .builder
                                .build_int_compare(
                                    inkwell::IntPredicate::SGT,
                                    lhs.into_int_value(),
                                    rhs.into_int_value(),
                                    "gt",
                                )
                                .unwrap()
                                .into())
                        } else {
                            Ok(self
                                .builder
                                .build_float_compare(
                                    inkwell::FloatPredicate::OGT,
                                    lhs.into_float_value(),
                                    rhs.into_float_value(),
                                    "fgt",
                                )
                                .unwrap()
                                .into())
                        }
                    }
                    BinOp::Gte => {
                        if lhs.is_int_value() {
                            Ok(self
                                .builder
                                .build_int_compare(
                                    inkwell::IntPredicate::SGE,
                                    lhs.into_int_value(),
                                    rhs.into_int_value(),
                                    "ge",
                                )
                                .unwrap()
                                .into())
                        } else {
                            Ok(self
                                .builder
                                .build_float_compare(
                                    inkwell::FloatPredicate::OGE,
                                    lhs.into_float_value(),
                                    rhs.into_float_value(),
                                    "fge",
                                )
                                .unwrap()
                                .into())
                        }
                    }
                    BinOp::And => Ok(self
                        .builder
                        .build_and(lhs.into_int_value(), rhs.into_int_value(), "and")
                        .unwrap()
                        .into()),
                    BinOp::Or => Ok(self
                        .builder
                        .build_or(lhs.into_int_value(), rhs.into_int_value(), "or")
                        .unwrap()
                        .into()),
                    _ => Err(format!("Operator {:?} not implemented", op)),
                }
            }
            typed::TypedExprKind::Unary { op, expr } => {
                let e = self.gen_typed_expr(expr)?;
                match op {
                    UnaryOp::Plus => Ok(e),
                    UnaryOp::Minus => {
                        if e.is_int_value() {
                            Ok(self
                                .builder
                                .build_int_neg(e.into_int_value(), "neg")
                                .unwrap()
                                .into())
                        } else {
                            Ok(self
                                .builder
                                .build_float_neg(e.into_float_value(), "fneg")
                                .unwrap()
                                .into())
                        }
                    }
                    UnaryOp::Not => Ok(self
                        .builder
                        .build_not(e.into_int_value(), "not")
                        .unwrap()
                        .into()),
                }
            }
            typed::TypedExprKind::FunctionCall { name, args } => {
                if name == "Chr" {
                    let a = self.gen_typed_expr(&args[0])?.into_int_value();
                    return Ok(self
                        .builder
                        .build_int_truncate(a, self.context.i8_type(), "chr")
                        .unwrap()
                        .into());
                }
                if name == "Ord" {
                    let a = self.gen_typed_expr(&args[0])?.into_int_value();
                    return Ok(self
                        .builder
                        .build_int_z_extend(a, self.context.i64_type(), "ord")
                        .unwrap()
                        .into());
                }
                let mut l_a = Vec::new();
                for a in args {
                    l_a.push(self.gen_typed_expr(a)?.into());
                }
                let real_name = match name.as_str() {
                    "Sqrt" => "pascal_sqrt",
                    _ => name.as_str(),
                };

                let call_res = if let Some(f_c) = self.get_function_robust(real_name) {
                    Some(self.builder.build_call(f_c, &l_a, name).unwrap())
                } else if let Some((p, l_t, _)) = self.get_variable(name).cloned() {
                    let f_p = self
                        .builder
                        .build_load(l_t, p, "fnptr")
                        .unwrap()
                        .into_pointer_value();
                    let mut a_t = Vec::new();
                    for a in &l_a {
                        let b_v = match a {
                            inkwell::values::BasicMetadataValueEnum::IntValue(i) => {
                                i.as_basic_value_enum()
                            }
                            inkwell::values::BasicMetadataValueEnum::FloatValue(f) => {
                                f.as_basic_value_enum()
                            }
                            inkwell::values::BasicMetadataValueEnum::PointerValue(p) => {
                                p.as_basic_value_enum()
                            }
                            _ => unreachable!(),
                        };
                        a_t.push(b_v.get_type().into());
                    }
                    let r_t = self.resolve_typed_type(&expr.ty)?;
                    let fn_t = match r_t {
                        inkwell::types::BasicTypeEnum::IntType(t) => t.fn_type(&a_t, false),
                        inkwell::types::BasicTypeEnum::FloatType(t) => t.fn_type(&a_t, false),
                        inkwell::types::BasicTypeEnum::PointerType(t) => t.fn_type(&a_t, false),
                        _ => self.context.void_type().fn_type(&a_t, false),
                    };
                    Some(
                        self.builder
                            .build_indirect_call(fn_t, f_p, &l_a, name)
                            .unwrap(),
                    )
                } else {
                    // Try to re-declare if it's an external interface function we missed
                    self.declare_external_interfaces();
                    if let Some(f_c) = self.module.get_function(real_name) {
                        Some(self.builder.build_call(f_c, &l_a, name).unwrap())
                    } else {
                        None
                    }
                };

                if let Some(call) = call_res {
                    let res = call.try_as_basic_value().left();
                    if let Some(val) = res {
                        Ok(val)
                    } else {
                        Ok(self.context.i64_type().const_zero().as_basic_value_enum())
                    }
                } else {
                    Err(format!("Func {} not found", name))
                }
            }
            typed::TypedExprKind::Set(els) => {
                let s_t = self.context.custom_width_int_type(256);
                let mut s_v = s_t.const_zero();
                for el in els {
                    match el {
                        typed::TypedElement::Single(e) => {
                            let v = self.gen_typed_expr(e)?.into_int_value();
                            let bit = self.builder.build_int_z_extend(v, s_t, "bitext").unwrap();
                            let mask = self
                                .builder
                                .build_left_shift(s_t.const_int(1, false), bit, "mask")
                                .unwrap();
                            s_v = self.builder.build_or(s_v, mask, "setor").unwrap();
                        }
                        typed::TypedElement::Range(st, en) => {
                            let _s = self.gen_typed_expr(st)?.into_int_value();
                            let _e = self.gen_typed_expr(en)?.into_int_value();
                            s_v = self
                                .builder
                                .build_or(s_v, s_t.const_int(0, false), "setrange")
                                .unwrap();
                        }
                    }
                }
                Ok(s_v.into())
            }
            typed::TypedExprKind::Nil => Ok(self
                .context
                .ptr_type(inkwell::AddressSpace::default())
                .const_null()
                .into()),
        }
    }

    fn gen_typed_target_ptr(
        &mut self,
        expr: &typed::TypedExpr,
    ) -> Result<PointerValue<'ctx>, String> {
        match &expr.kind {
            typed::TypedExprKind::Variable(v) => self.gen_typed_variable_ptr(v).map(|(p, _)| p),
            _ => Err("Invalid assignment target".to_string()),
        }
    }

    fn gen_typed_variable_ptr_from_expr(
        &mut self,
        expr: &typed::TypedExpr,
    ) -> Result<(PointerValue<'ctx>, inkwell::types::BasicTypeEnum<'ctx>), String> {
        match &expr.kind {
            typed::TypedExprKind::Variable(v) => self.gen_typed_variable_ptr(v),
            _ => Err("Expected variable expression".to_string()),
        }
    }

    fn gen_typed_variable_ptr(
        &mut self,
        var: &typed::TypedVariable,
    ) -> Result<(PointerValue<'ctx>, inkwell::types::BasicTypeEnum<'ctx>), String> {
        match var {
            typed::TypedVariable::Id(id) => {
                let (p, l_t, _) = self
                    .get_variable(id)
                    .ok_or_else(|| format!("Var {} not found", id))?;
                Ok((*p, *l_t))
            }
            typed::TypedVariable::MemberAccess { record, field } => {
                let (p, l_t) = self.gen_typed_variable_ptr_from_expr(record)?;
                let s_t = l_t.into_struct_type();
                let idx = *self
                    .record_fields
                    .get(&format!("{:?}", l_t))
                    .and_then(|m| m.get(field))
                    .ok_or_else(|| format!("Field '{}' not found", field))?;
                Ok((
                    self.builder.build_struct_gep(s_t, p, idx, field).unwrap(),
                    s_t.get_field_type_at_index(idx).unwrap(),
                ))
            }
            typed::TypedVariable::ArrayAccess { array, index } => {
                let (p, l_t) = self.gen_typed_variable_ptr_from_expr(array)?;
                let a_t = l_t.into_array_type();
                let idx = self.gen_typed_expr(index)?.into_int_value();
                let zero = self.context.i64_type().const_int(0, false);
                Ok((
                    unsafe {
                        self.builder
                            .build_gep(a_t, p, &[zero, idx], "arraygep")
                            .unwrap()
                    },
                    a_t.get_element_type(),
                ))
            }
            typed::TypedVariable::PointerDeref(p) => {
                let p_v = self.gen_typed_expr(p)?;
                let element_llvm = match &p.ty {
                    typed::Type::Pointer(inner) => self.resolve_typed_type(inner)?,
                    _ => return Err("Deref on non-pointer".to_string()),
                };
                Ok((p_v.into_pointer_value(), element_llvm))
            }
        }
    }

    fn resolve_typed_type(
        &mut self,
        ty: &typed::Type,
    ) -> Result<inkwell::types::BasicTypeEnum<'ctx>, String> {
        match ty {
            typed::Type::Integer => Ok(self.context.i64_type().as_basic_type_enum()),
            typed::Type::Real => Ok(self.context.f64_type().as_basic_type_enum()),
            typed::Type::Boolean => Ok(self.context.bool_type().as_basic_type_enum()),
            typed::Type::Char => Ok(self.context.i8_type().as_basic_type_enum()),
            typed::Type::String => Ok(self
                .context
                .ptr_type(inkwell::AddressSpace::default())
                .as_basic_type_enum()),
            typed::Type::Array { element_type, size } => Ok(self
                .resolve_typed_type(element_type)?
                .array_type(*size as u32)
                .as_basic_type_enum()),
            typed::Type::Record { fields } => {
                let mut f_types = Vec::new();
                let mut f_map = HashMap::new();
                for (i, (name, ty)) in fields.iter().enumerate() {
                    let f_t = self.resolve_typed_type(ty)?;
                    f_types.push(f_t);
                    f_map.insert(name.clone(), i as u32);
                }
                let s_t = self.context.struct_type(&f_types, false);
                self.record_fields
                    .insert(format!("{:?}", s_t.as_basic_type_enum()), f_map);
                Ok(s_t.as_basic_type_enum())
            }
            typed::Type::Pointer(_) | typed::Type::Function(_) | typed::Type::Procedure => Ok(self
                .context
                .ptr_type(inkwell::AddressSpace::default())
                .as_basic_type_enum()),
            typed::Type::Set(_) => Ok(self.context.custom_width_int_type(256).as_basic_type_enum()),
            _ => Ok(self.context.i64_type().as_basic_type_enum()),
        }
    }

    fn create_entry_block_alloca(
        &self,
        function: FunctionValue<'ctx>,
        name: &str,
        llvm_type: inkwell::types::BasicTypeEnum<'ctx>,
    ) -> PointerValue<'ctx> {
        let builder = self.context.create_builder();
        let entry = function.get_first_basic_block().unwrap();
        match entry.get_first_instruction() {
            Some(first_instr) => builder.position_before(&first_instr),
            None => builder.position_at_end(entry),
        }
        builder.build_alloca(llvm_type, name).unwrap()
    }

    fn get_or_create_label_bb(
        &mut self,
        function: FunctionValue<'ctx>,
        l: i64,
    ) -> inkwell::basic_block::BasicBlock<'ctx> {
        if let Some(bb) = self.labels.get(&l) {
            *bb
        } else {
            let bb = self
                .context
                .append_basic_block(function, &format!("label{}", l));
            self.labels.insert(l, bb);
            bb
        }
    }

    fn resolve_type(
        &mut self,
        te: &TypeExpr,
    ) -> Result<inkwell::types::BasicTypeEnum<'ctx>, String> {
        match &te.node {
            TypeExprKind::Simple(name) => match name.as_str() {
                "integer" => Ok(self.context.i64_type().as_basic_type_enum()),
                "real" => Ok(self.context.f64_type().as_basic_type_enum()),
                "boolean" => Ok(self.context.bool_type().as_basic_type_enum()),
                "char" => Ok(self.context.i8_type().as_basic_type_enum()),
                "string" | "procedure" | "function" => Ok(self
                    .context
                    .ptr_type(inkwell::AddressSpace::default())
                    .as_basic_type_enum()),
                _ => self
                    .types
                    .get(name)
                    .map(|(t, _)| *t)
                    .ok_or_else(|| format!("Type '{}' not defined", name)),
            },
            TypeExprKind::Record {
                fields,
                variant_part,
            } => {
                let mut f_t = Vec::new();
                let mut f_m = HashMap::new();
                let mut idx = 0;
                for f in fields {
                    let ft = self.resolve_type(&f.type_expr)?;
                    for id in &f.ids {
                        f_t.push(ft);
                        f_m.insert(id.clone(), idx);
                        idx += 1;
                    }
                }
                if let Some(vp) = variant_part {
                    if let Some(tag) = &vp.tag_field {
                        let tag_type = self.resolve_type(&TypeExpr {
                            span: vp.span,
                            node: TypeExprKind::Simple(vp.tag_type.clone()),
                        })?;
                        f_t.push(tag_type);
                        f_m.insert(tag.clone(), idx);
                        idx += 1;
                    }
                    for v in &vp.variants {
                        for f in &v.fields {
                            let ft = self.resolve_type(&f.type_expr)?;
                            for id in &f.ids {
                                if !f_m.contains_key(id) {
                                    f_t.push(ft);
                                    f_m.insert(id.clone(), idx);
                                    idx += 1;
                                }
                            }
                        }
                    }
                }
                let s_t = self.context.struct_type(&f_t, false);
                let l_t = s_t.as_basic_type_enum();
                self.record_fields.insert(format!("{:?}", l_t), f_m);
                Ok(l_t)
            }
            TypeExprKind::Array {
                indices,
                element_type,
            } => {
                let et = self.resolve_type(element_type)?;
                let mut t_s = 1;
                for idx_te in indices {
                    match &idx_te.node {
                        TypeExprKind::Subrange { start, end } => {
                            if let (ExprKind::Integer(s), ExprKind::Integer(e)) =
                                (&start.node, &end.node)
                            {
                                t_s *= (e - s + 1).max(0) as u64;
                            } else {
                                t_s = 100;
                                break;
                            }
                        }
                        _ => {
                            t_s = 100;
                            break;
                        }
                    }
                }
                Ok(et.array_type(t_s as u32).as_basic_type_enum())
            }
            _ => Ok(self.context.i64_type().as_basic_type_enum()),
        }
    }
    fn gen_stmt(&mut self, _stmt: &Stmt, _f: FunctionValue<'ctx>) -> Result<(), String> {
        Ok(())
    }
    fn gen_expr(&mut self, _expr: &Expr) -> Result<BasicValueEnum<'ctx>, String> {
        Err("Deprecated".to_string())
    }
    fn gen_target_ptr(&mut self, _expr: &Expr) -> Result<PointerValue<'ctx>, String> {
        Err("Deprecated".to_string())
    }
    fn gen_variable_ptr_with_type(
        &mut self,
        _var: &Variable,
    ) -> Result<
        (
            PointerValue<'ctx>,
            inkwell::types::BasicTypeEnum<'ctx>,
            TypeExpr,
        ),
        String,
    > {
        Err("Deprecated".to_string())
    }
}
