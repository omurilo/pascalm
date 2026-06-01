use inkwell::context::Context;
use inkwell::module::Module;
use inkwell::builder::Builder;
use inkwell::values::{FunctionValue, PointerValue, BasicValueEnum, BasicValue};
use inkwell::types::BasicType;
use crate::ast::*;
use crate::symbol_table::SymbolKind;
use std::collections::HashMap;

pub struct CodeGen<'ctx> {
    pub context: &'ctx Context,
    pub module: Module<'ctx>,
    pub builder: Builder<'ctx>,
    variables: Vec<HashMap<String, (PointerValue<'ctx>, inkwell::types::BasicTypeEnum<'ctx>, TypeExpr)>>,
    types: HashMap<String, (inkwell::types::BasicTypeEnum<'ctx>, TypeExpr)>,
    record_fields: HashMap<String, HashMap<String, u32>>,
    labels: HashMap<i64, inkwell::basic_block::BasicBlock<'ctx>>,
    external_interfaces: HashMap<String, HashMap<String, SymbolKind>>,
}

impl<'ctx> CodeGen<'ctx> {
    pub fn new(context: &'ctx Context, module_name: &str) -> Self {
        let module = context.create_module(module_name);
        let builder = context.create_builder();
        let mut cg = Self {
            context,
            module,
            builder,
            variables: vec![HashMap::new()], // Global scope
            types: HashMap::new(),
            record_fields: HashMap::new(),
            labels: HashMap::new(),
            external_interfaces: HashMap::new(),
        };
        cg.setup_builtins();
        cg
    }

    pub fn with_interfaces(context: &'ctx Context, module_name: &str, interfaces: HashMap<String, HashMap<String, SymbolKind>>) -> Self {
        let mut cg = Self::new(context, module_name);
        cg.external_interfaces = interfaces;
        cg
    }

    fn setup_builtins(&mut self) {
        let i64_type = self.context.i64_type();
        let maxint = self.module.add_global(i64_type, None, "maxint");
        maxint.set_initializer(&i64_type.const_int(i64::MAX as u64, false));
        maxint.set_constant(true);
        self.variables[0].insert("maxint".to_string(), (maxint.as_pointer_value(), i64_type.as_basic_type_enum(), TypeExpr::Simple("integer".to_string())));
    }

    fn get_printf(&self) -> FunctionValue<'ctx> {
        if let Some(f) = self.module.get_function("printf") {
            return f;
        }
        let i32_type = self.context.i32_type();
        let i8_ptr_type = self.context.ptr_type(inkwell::AddressSpace::default());
        let printf_type = i32_type.fn_type(&[i8_ptr_type.into()], true);
        self.module.add_function("printf", printf_type, None)
    }

    fn get_scanf(&self) -> FunctionValue<'ctx> {
        if let Some(f) = self.module.get_function("scanf") {
            return f;
        }
        let i32_type = self.context.i32_type();
        let i8_ptr_type = self.context.ptr_type(inkwell::AddressSpace::default());
        let scanf_type = i32_type.fn_type(&[i8_ptr_type.into()], true);
        self.module.add_function("scanf", scanf_type, None)
    }

    fn enter_scope(&mut self) {
        self.variables.push(HashMap::new());
    }

    fn exit_scope(&mut self) {
        self.variables.pop();
    }

    fn get_variable(&self, name: &str) -> Option<&(PointerValue<'ctx>, inkwell::types::BasicTypeEnum<'ctx>, TypeExpr)> {
        for scope in self.variables.iter().rev() {
            if let Some(v) = scope.get(name) {
                return Some(v);
            }
        }
        None
    }

    pub fn gen_program(&mut self, program: &Program) -> Result<(), String> {
        self.import_uses(&program.uses)?;
        let i32_type = self.context.i32_type();
        let fn_type = i32_type.fn_type(&[], false);
        let function = self.module.add_function("main", fn_type, None);
        let basic_block = self.context.append_basic_block(function, "entry");
        self.builder.position_at_end(basic_block);

        self.gen_block(&program.block, function)?;

        let ret_val = i32_type.const_int(0, false);
        self.builder.build_return(Some(&ret_val)).map_err(|e| e.to_string())?;

        Ok(())
    }

    pub fn gen_unit(&mut self, unit: &Unit) -> Result<(), String> {
        self.import_uses(&unit.interface.uses)?;
        
        // 1. Interface Declarations (as exports)
        if let Some(vars) = &unit.interface.variables {
            for v_decl in vars {
                let llvm_type = self.resolve_type(&v_decl.type_expr)?;
                for id in &v_decl.ids {
                    let global = self.module.add_global(llvm_type, None, id);
                    global.set_initializer(&llvm_type.const_zero());
                    self.variables[0].insert(id.clone(), (global.as_pointer_value(), llvm_type, v_decl.type_expr.clone()));
                }
            }
        }
        if let Some(headers) = &unit.interface.headers {
            for h in headers {
                self.gen_proc_func(h)?;
            }
        }

        // 2. Implementation
        self.import_uses(&unit.implementation.uses)?;
        if let Some(vars) = &unit.implementation.variables {
            for v_decl in vars {
                let llvm_type = self.resolve_type(&v_decl.type_expr)?;
                for id in &v_decl.ids {
                    let global = self.module.add_global(llvm_type, None, id);
                    global.set_initializer(&llvm_type.const_zero());
                    self.variables[0].insert(id.clone(), (global.as_pointer_value(), llvm_type, v_decl.type_expr.clone()));
                }
            }
        }
        if let Some(bodies) = &unit.implementation.bodies {
            for b in bodies {
                // If it was already declared in interface, we need to find it and define it
                // gen_proc_func currently adds a new function, might need adjustment
                self.gen_proc_func(b)?;
            }
        }

        // 3. Initialization
        if let Some(init) = &unit.initialization {
            let fn_name = format!("{}_init", unit.name);
            let fn_type = self.context.void_type().fn_type(&[], false);
            let function = self.module.add_function(&fn_name, fn_type, None);
            let bb = self.context.append_basic_block(function, "entry");
            self.builder.position_at_end(bb);
            for stmt in init { self.gen_stmt(stmt, function)?; }
            self.builder.build_return(None).unwrap();
        }

        Ok(())
    }

    fn import_uses(&mut self, uses: &Option<Vec<String>>) -> Result<(), String> {
        if let Some(units) = uses {
            for unit_name in units {
                let unit_lower = unit_name.to_lowercase();
                if let Some(interface) = self.external_interfaces.get(&unit_lower).cloned() {
                    for (name, kind) in interface {
                        match kind {
                            SymbolKind::Variable { type_expr } => {
                                let llvm_type = self.resolve_type(&type_expr)?;
                                if self.module.get_global(&name).is_none() {
                                    let global = self.module.add_global(llvm_type, None, &name);
                                    global.set_linkage(inkwell::module::Linkage::External);
                                    self.variables[0].insert(name.clone(), (global.as_pointer_value(), llvm_type, type_expr.clone()));
                                }
                            }
                            SymbolKind::Procedure { params } => {
                                if self.module.get_function(&name).is_none() {
                                    let mut arg_types = Vec::new();
                                    for p in params {
                                        match p {
                                            Param::Variable { type_name, ids, .. } => {
                                                let pt = self.resolve_type(&TypeExpr::Simple(type_name.clone()))?;
                                                for _ in ids { arg_types.push(pt.into()); }
                                            }
                                            _ => { arg_types.push(self.context.ptr_type(inkwell::AddressSpace::default()).into()); }
                                        }
                                    }
                                    let fn_type = self.context.void_type().fn_type(&arg_types, false);
                                    self.module.add_function(&name, fn_type, Some(inkwell::module::Linkage::External));
                                }
                            }
                            SymbolKind::Function { params, return_type } => {
                                if self.module.get_function(&name).is_none() {
                                    let mut arg_types = Vec::new();
                                    for p in params {
                                        match p {
                                            Param::Variable { type_name, ids, .. } => {
                                                let pt = self.resolve_type(&TypeExpr::Simple(type_name.clone()))?;
                                                for _ in ids { arg_types.push(pt.into()); }
                                            }
                                            _ => { arg_types.push(self.context.ptr_type(inkwell::AddressSpace::default()).into()); }
                                        }
                                    }
                                    let rt_llvm = self.resolve_type(&TypeExpr::Simple(return_type.clone()))?;
                                    let fn_type = rt_llvm.fn_type(&arg_types, false);
                                    self.module.add_function(&name, fn_type, Some(inkwell::module::Linkage::External));
                                }
                            }
                            _ => {}
                        }
                    }
                }
            }
        }
        Ok(())
    }

    fn gen_block(&mut self, block: &Block, function: FunctionValue<'ctx>) -> Result<(), String> {
        // Pre-create label blocks
        if let Some(labels) = &block.labels {
            for &l in labels {
                let bb = self.context.append_basic_block(function, &format!("label{}", l));
                self.labels.insert(l, bb);
            }
        }

        if let Some(constants) = &block.constants {
            for c in constants {
                let val = self.gen_expr(&c.value)?;
                let llvm_type = val.get_type();
                let global = self.module.add_global(llvm_type, None, &c.name);
                global.set_initializer(&val);
                global.set_constant(true);
                self.variables.last_mut().unwrap().insert(c.name.clone(), (global.as_pointer_value(), llvm_type, TypeExpr::Simple("integer".to_string()))); // Defaulting to integer for constants
            }
        }

        if let Some(types) = &block.types {
            for t_decl in types {
                let llvm_type = self.resolve_type(&t_decl.type_expr)?;
                self.types.insert(t_decl.name.clone(), (llvm_type, t_decl.type_expr.clone()));
                
                // Register enum members as constants
                if let TypeExpr::Enum(ids) = &t_decl.type_expr {
                    for (i, id) in ids.iter().enumerate() {
                        let val = self.context.i64_type().const_int(i as u64, false);
                        let global = self.module.add_global(val.get_type(), None, id);
                        global.set_initializer(&val);
                        global.set_constant(true);
                        self.variables[0].insert(id.clone(), (global.as_pointer_value(), val.get_type().as_basic_type_enum(), TypeExpr::Simple(t_decl.name.clone())));
                    }
                }
            }
        }

        if let Some(vars) = &block.variables {
            for v_decl in vars {
                let llvm_type = self.resolve_type(&v_decl.type_expr)?;
                for id in &v_decl.ids {
                    if self.variables.len() == 1 {
                        let global = self.module.add_global(llvm_type, None, id);
                        global.set_initializer(&llvm_type.const_zero());
                        self.variables.last_mut().unwrap().insert(id.clone(), (global.as_pointer_value(), llvm_type, v_decl.type_expr.clone()));
                    } else {
                        let ptr = self.create_entry_block_alloca(function, id, llvm_type);
                        self.variables.last_mut().unwrap().insert(id.clone(), (ptr, llvm_type, v_decl.type_expr.clone()));
                    }
                }
            }
        }

        if let Some(procs) = &block.procedures_functions {
            for p in procs {
                self.gen_proc_func(p)?;
            }
        }

        for stmt in &block.statements {
            self.gen_stmt(stmt, function)?;
        }

        Ok(())
    }

    fn gen_proc_func(&mut self, decl: &ProcFuncDecl) -> Result<(), String> {
        let (name, params, return_type, block_or_forward) = match decl {
            ProcFuncDecl::Procedure { name, params, block_or_forward } => (name, params, None, block_or_forward),
            ProcFuncDecl::Function { name, params, return_type, block_or_forward } => (name, params, Some(return_type), block_or_forward),
        };

        let mut arg_types = Vec::new();
        if let Some(params) = params {
            for p in params {
                match p {
                    Param::Variable { type_name, ids, .. } => {
                        let pt = self.resolve_type(&TypeExpr::Simple(type_name.clone()))?;
                        for _ in ids {
                            arg_types.push(pt.into());
                        }
                    }
                    Param::Procedure { .. } | Param::Function { .. } => {
                        let pt = self.context.ptr_type(inkwell::AddressSpace::default());
                        arg_types.push(pt.into());
                    }
                }
            }
        }

        let fn_type = if let Some(rt) = return_type {
            let rt_llvm = self.resolve_type(&TypeExpr::Simple(rt.clone()))?;
            rt_llvm.fn_type(&arg_types, false)
        } else {
            self.context.void_type().fn_type(&arg_types, false)
        };

        let function = self.module.add_function(name, fn_type, None);

        if let BlockOrForward::Block(b) = block_or_forward {
            let bb = self.context.append_basic_block(function, "entry");
            let original_builder_bb = self.builder.get_insert_block();
            self.builder.position_at_end(bb);

            self.enter_scope();
            
            // Handle parameters
            let mut arg_idx = 0;
            if let Some(params) = params {
                for p in params {
                    match p {
                        Param::Variable { type_name, ids, .. } => {
                            let pt_expr = TypeExpr::Simple(type_name.clone());
                            let pt = self.resolve_type(&pt_expr)?;
                            for id in ids {
                                let val = function.get_nth_param(arg_idx).unwrap();
                                let ptr = self.create_entry_block_alloca(function, id, pt);
                                self.builder.build_store(ptr, val).unwrap();
                                self.variables.last_mut().unwrap().insert(id.clone(), (ptr, pt, pt_expr.clone()));
                                arg_idx += 1;
                            }
                        }
                        Param::Procedure { id, .. } => {
                            let val = function.get_nth_param(arg_idx).unwrap();
                            let pt = self.context.ptr_type(inkwell::AddressSpace::default());
                            let ptr = self.create_entry_block_alloca(function, id, pt.into());
                            self.builder.build_store(ptr, val).unwrap();
                            // Use a special TypeExpr for procedures/functions as parameters
                            self.variables.last_mut().unwrap().insert(id.clone(), (ptr, pt.into(), TypeExpr::Simple("procedure".to_string())));
                            arg_idx += 1;
                        }
                        Param::Function { id, return_type, .. } => {
                            let val = function.get_nth_param(arg_idx).unwrap();
                            let pt = self.context.ptr_type(inkwell::AddressSpace::default());
                            let ptr = self.create_entry_block_alloca(function, id, pt.into());
                            self.builder.build_store(ptr, val).unwrap();
                            self.variables.last_mut().unwrap().insert(id.clone(), (ptr, pt.into(), TypeExpr::Simple(format!("function:{}", return_type))));
                            arg_idx += 1;
                        }
                    }
                }
            }

            // Return variable for functions
            if let Some(rt) = return_type {
                let rt_expr = TypeExpr::Simple(rt.clone());
                let rt_llvm = self.resolve_type(&rt_expr)?;
                let ret_ptr = self.create_entry_block_alloca(function, name, rt_llvm);
                self.variables.last_mut().unwrap().insert(name.clone(), (ret_ptr, rt_llvm, rt_expr));
            }

            self.gen_block(b, function)?;

            if return_type.is_some() {
                let rt_llvm = self.resolve_type(&TypeExpr::Simple(return_type.unwrap().clone()))?;
                let ret_ptr = self.get_variable(name).unwrap().0;
                let ret_val = self.builder.build_load(rt_llvm, ret_ptr, "retval").unwrap();
                self.builder.build_return(Some(&ret_val)).unwrap();
            } else {
                self.builder.build_return(None).unwrap();
            }

            self.exit_scope();
            if let Some(obb) = original_builder_bb {
                self.builder.position_at_end(obb);
            }
        }

        Ok(())
    }

    fn resolve_type(&mut self, te: &TypeExpr) -> Result<inkwell::types::BasicTypeEnum<'ctx>, String> {
        match te {
            TypeExpr::Simple(name) => {
                match name.as_str() {
                    "integer" => Ok(self.context.i64_type().as_basic_type_enum()),
                    "real" => Ok(self.context.f64_type().as_basic_type_enum()),
                    "boolean" => Ok(self.context.bool_type().as_basic_type_enum()),
                    "char" => Ok(self.context.i8_type().as_basic_type_enum()),
                    "string" | "procedure" | "function" => Ok(self.context.ptr_type(inkwell::AddressSpace::default()).as_basic_type_enum()),
                    _ => {
                        self.types.get(name).map(|(t, _)| *t).ok_or_else(|| format!("Type '{}' not defined", name))
                    }
                }
            }
            TypeExpr::Record { fields, variant_part } => {
                let mut field_types = Vec::new();
                let mut field_map = HashMap::new();
                let mut index = 0;
                for f in fields {
                    let ft = self.resolve_type(&f.type_expr)?;
                    for id in &f.ids {
                        field_types.push(ft);
                        field_map.insert(id.clone(), index);
                        index += 1;
                    }
                }
                if let Some(vp) = variant_part {
                    if let Some(tag) = &vp.tag_field {
                        let tag_type = self.resolve_type(&TypeExpr::Simple(vp.tag_type.clone()))?;
                        field_types.push(tag_type);
                        field_map.insert(tag.clone(), index);
                        index += 1;
                    }
                    // Include all variant fields in the flat struct for now (like a union in C but simpler)
                    for v in &vp.variants {
                        for f in &v.fields {
                            let ft = self.resolve_type(&f.type_expr)?;
                            for id in &f.ids {
                                if !field_map.contains_key(id) {
                                    field_types.push(ft);
                                    field_map.insert(id.clone(), index);
                                    index += 1;
                                }
                            }
                        }
                    }
                }
                let struct_type = self.context.struct_type(&field_types, false);
                let llvm_type = struct_type.as_basic_type_enum();
                self.record_fields.insert(format!("{:?}", llvm_type), field_map);
                Ok(llvm_type)
            }
            TypeExpr::Array { indices, element_type } => {
                let et = self.resolve_type(element_type)?;
                let mut total_size = 1;
                for idx_te in indices {
                    match idx_te {
                        TypeExpr::Subrange { start, end } => {
                            if let (Expr::Integer(s), Expr::Integer(e)) = (start, end) {
                                total_size *= (e - s + 1).max(0) as u64;
                            } else { total_size = 100; break; }
                        }
                        TypeExpr::Simple(name) if name == "boolean" => { total_size *= 2; }
                        TypeExpr::Simple(name) if name == "char" => { total_size *= 256; }
                        _ => { total_size = 100; break; }
                    }
                }
                Ok(et.array_type(total_size as u32).as_basic_type_enum()) 
            }
            TypeExpr::Subrange { .. } | TypeExpr::Enum(_) => {
                Ok(self.context.i64_type().as_basic_type_enum())
            }
            TypeExpr::Pointer(_) | TypeExpr::File(_) => {
                Ok(self.context.ptr_type(inkwell::AddressSpace::default()).as_basic_type_enum())
            }
            TypeExpr::Set(_) => {
                Ok(self.context.custom_width_int_type(256).as_basic_type_enum())
            }
            _ => Err(format!("Type resolution not implemented for {:?}", te)),
        }
    }

    fn create_entry_block_alloca(&self, function: FunctionValue<'ctx>, name: &str, llvm_type: inkwell::types::BasicTypeEnum<'ctx>) -> PointerValue<'ctx> {
        let builder = self.context.create_builder();
        let entry = function.get_first_basic_block().unwrap();
        match entry.get_first_instruction() {
            Some(first_instr) => builder.position_before(&first_instr),
            None => builder.position_at_end(entry),
        }
        builder.build_alloca(llvm_type, name).unwrap()
    }

    fn gen_stmt(&mut self, stmt: &Stmt, function: FunctionValue<'ctx>) -> Result<(), String> {
        match stmt {
            Stmt::Labeled(l, s) => {
                let target_bb = self.labels.get(l).ok_or_else(|| format!("Label {} not declared", l))?;
                // Fallthrough from previous statement to this labeled block
                self.builder.build_unconditional_branch(*target_bb).unwrap();
                self.builder.position_at_end(*target_bb);
                self.gen_stmt(s, function)?;
            }
            Stmt::Compound(stmts) => {
                for s in stmts {
                    self.gen_stmt(s, function)?;
                }
            }
            Stmt::Assignment { target, value } => {
                let val = self.gen_expr(value)?;
                let ptr = self.gen_target_ptr(target)?;
                self.builder.build_store(ptr, val).map_err(|e| e.to_string())?;
            }
            Stmt::If { condition, then_stmt, else_stmt } => {
                let cond = self.gen_expr(condition)?.into_int_value();
                let then_bb = self.context.append_basic_block(function, "then");
                let else_bb = self.context.append_basic_block(function, "else");
                let merge_bb = self.context.append_basic_block(function, "ifcont");

                self.builder.build_conditional_branch(cond, then_bb, else_bb).map_err(|e| e.to_string())?;

                self.builder.position_at_end(then_bb);
                self.gen_stmt(then_stmt, function)?;
                self.builder.build_unconditional_branch(merge_bb).map_err(|e| e.to_string())?;

                self.builder.position_at_end(else_bb);
                if let Some(else_s) = else_stmt {
                    self.gen_stmt(else_s, function)?;
                }
                self.builder.build_unconditional_branch(merge_bb).map_err(|e| e.to_string())?;

                self.builder.position_at_end(merge_bb);
            }
            Stmt::While { condition, body } => {
                let cond_bb = self.context.append_basic_block(function, "whilecond");
                let body_bb = self.context.append_basic_block(function, "whilebody");
                let after_bb = self.context.append_basic_block(function, "afterwhile");

                self.builder.build_unconditional_branch(cond_bb).map_err(|e| e.to_string())?;
                self.builder.position_at_end(cond_bb);

                let cond = self.gen_expr(condition)?.into_int_value();
                self.builder.build_conditional_branch(cond, body_bb, after_bb).map_err(|e| e.to_string())?;

                self.builder.position_at_end(body_bb);
                self.gen_stmt(body, function)?;
                self.builder.build_unconditional_branch(cond_bb).map_err(|e| e.to_string())?;

                self.builder.position_at_end(after_bb);
            }
            Stmt::Repeat { body, until } => {
                let loop_bb = self.context.append_basic_block(function, "loop");
                let after_bb = self.context.append_basic_block(function, "afterloop");

                self.builder.build_unconditional_branch(loop_bb).map_err(|e| e.to_string())?;
                self.builder.position_at_end(loop_bb);

                for s in body {
                    self.gen_stmt(s, function)?;
                }

                let cond = self.gen_expr(until)?.into_int_value();
                let not_cond = self.builder.build_not(cond, "notcond").unwrap();
                self.builder.build_conditional_branch(not_cond, loop_bb, after_bb).map_err(|e| e.to_string())?;

                self.builder.position_at_end(after_bb);
            }
            Stmt::For { id, start, up, end, body } => {
                let start_val = self.gen_expr(start)?;
                let (var_ptr, var_type, _) = *self.get_variable(id).ok_or_else(|| format!("For variable '{}' not found", id))?;
                self.builder.build_store(var_ptr, start_val).map_err(|e| e.to_string())?;

                let cond_bb = self.context.append_basic_block(function, "forcond");
                let body_bb = self.context.append_basic_block(function, "forbody");
                let after_bb = self.context.append_basic_block(function, "afterfor");

                self.builder.build_unconditional_branch(cond_bb).map_err(|e| e.to_string())?;
                self.builder.position_at_end(cond_bb);

                let current_val = self.builder.build_load(var_type, var_ptr, "current_for_val").unwrap().into_int_value();
                let end_val = self.gen_expr(end)?.into_int_value();
                
                let cond = if *up {
                    self.builder.build_int_compare(inkwell::IntPredicate::SLE, current_val, end_val, "forupto").unwrap()
                } else {
                    self.builder.build_int_compare(inkwell::IntPredicate::SGE, current_val, end_val, "fordownto").unwrap()
                };

                self.builder.build_conditional_branch(cond, body_bb, after_bb).map_err(|e| e.to_string())?;

                self.builder.position_at_end(body_bb);
                self.gen_stmt(body, function)?;

                let next_val = if *up {
                    self.builder.build_int_add(current_val, self.context.i64_type().const_int(1, false), "nextval").unwrap()
                } else {
                    self.builder.build_int_sub(current_val, self.context.i64_type().const_int(1, false), "nextval").unwrap()
                };
                self.builder.build_store(var_ptr, next_val).map_err(|e| e.to_string())?;
                self.builder.build_unconditional_branch(cond_bb).map_err(|e| e.to_string())?;

                self.builder.position_at_end(after_bb);
            }
            Stmt::Case { expr, items, else_stmt } => {
                let case_val = self.gen_expr(expr)?.into_int_value();
                let merge_bb = self.context.append_basic_block(function, "casecont");
                let else_bb = if else_stmt.is_some() {
                    self.context.append_basic_block(function, "caseelse")
                } else {
                    merge_bb
                };

                let mut cases = Vec::new();
                let mut case_bbs = Vec::new();

                for item in items {
                    let case_bb = self.context.append_basic_block(function, "caseitem");
                    for label in &item.labels {
                        match label {
                            Expr::Range(start, end) => {
                                if let (Expr::Integer(s), Expr::Integer(e)) = (&**start, &**end) {
                                    for v in *s..=*e {
                                        let val = self.context.i64_type().const_int(v as u64, false);
                                        cases.push((val, case_bb));
                                    }
                                }
                            }
                            _ => {
                                let label_val = self.gen_expr(label)?.into_int_value();
                                cases.push((label_val, case_bb));
                            }
                        }
                    }
                    case_bbs.push((case_bb, &item.stmt));
                }

                self.builder.build_switch(case_val, else_bb, &cases).unwrap();
                
                for (bb, stmt) in case_bbs {
                    self.builder.position_at_end(bb);
                    self.gen_stmt(stmt, function)?;
                    self.builder.build_unconditional_branch(merge_bb).unwrap();
                }

                if let Some(else_s) = else_stmt {
                    self.builder.position_at_end(else_bb);
                    self.gen_stmt(else_s, function)?;
                    self.builder.build_unconditional_branch(merge_bb).unwrap();
                }

                self.builder.position_at_end(merge_bb);
            }
            Stmt::Goto(l) => {
                let target_bb = self.labels.get(l).ok_or_else(|| format!("Label {} not found", l))?;
                self.builder.build_unconditional_branch(*target_bb).unwrap();
                let dead_bb = self.context.append_basic_block(function, "deadcode");
                self.builder.position_at_end(dead_bb);
            }
            Stmt::ProcedureCall { name, args } => {
                if name == "write" || name == "writeln" {
                    let printf = self.get_printf();
                    if let Some(args) = args {
                        for arg in args {
                            let val = self.gen_expr(arg)?;
                            let (fmt, val_to_print) = match val {
                                BasicValueEnum::IntValue(i) => {
                                    let width = i.get_type().get_bit_width();
                                    if width == 8 { ("%c".to_string(), i.into()) }
                                    else if width == 1 { ("%d".to_string(), i.into()) }
                                    else { ("%lld".to_string(), i.into()) }
                                },
                                BasicValueEnum::FloatValue(f) => ("%f".to_string(), f.into()),
                                BasicValueEnum::PointerValue(p) => ("%s".to_string(), p.into()),
                                _ => ("%p".to_string(), val),
                            };
                            let fmt_str = self.builder.build_global_string_ptr(&fmt, "fmt").unwrap();
                            self.builder.build_call(printf, &[fmt_str.as_pointer_value().into(), val_to_print.into()], "printf").unwrap();
                        }
                    }
                    if name == "writeln" {
                        let nl = self.builder.build_global_string_ptr("\n", "nl").unwrap();
                        self.builder.build_call(printf, &[nl.as_pointer_value().into()], "printf").unwrap();
                    }
                } else if name == "read" || name == "readln" {
                    let scanf = self.get_scanf();
                    if let Some(args) = args {
                        for arg in args {
                            let ptr = self.gen_target_ptr(arg)?;
                            let target_type = match arg {
                                Expr::Variable(v) => self.gen_variable_ptr_with_type(v)?.1,
                                _ => return Err("Read target must be a variable".to_string()),
                            };
                            let fmt = if target_type.is_int_type() {
                                let width = target_type.into_int_type().get_bit_width();
                                if width == 8 { " %c" } else { "%lld" }
                            } else if target_type.is_float_type() { "%lf" } else { "%s" };
                            let fmt_str = self.builder.build_global_string_ptr(fmt, "fmt").unwrap();
                            self.builder.build_call(scanf, &[fmt_str.as_pointer_value().into(), ptr.into()], "scanf").unwrap();
                        }
                    }
                } else {
                    let mut llvm_args = Vec::new();
                    if let Some(args) = args {
                        for arg in args {
                            llvm_args.push(self.gen_expr(arg)?.into());
                        }
                    }
                    
                    if let Some(function_to_call) = self.module.get_function(name) {
                         self.builder.build_call(function_to_call, &llvm_args, name).unwrap();
                    } else {
                        // Indirect call?
                        let (ptr, llvm_type, te) = self.get_variable(name).ok_or_else(|| format!("Procedure '{}' not found", name))?;
                        let fn_ptr = self.builder.build_load(*llvm_type, *ptr, "fnptr").unwrap().into_pointer_value();
                        
                        let mut arg_types = Vec::new();
                        for arg in &llvm_args {
                            let basic_val = match arg {
                                inkwell::values::BasicMetadataValueEnum::IntValue(i) => i.as_basic_value_enum(),
                                inkwell::values::BasicMetadataValueEnum::FloatValue(f) => f.as_basic_value_enum(),
                                inkwell::values::BasicMetadataValueEnum::PointerValue(p) => p.as_basic_value_enum(),
                                _ => unreachable!(),
                            };
                            arg_types.push(basic_val.get_type().into());
                        }

                        let ret_type = match te {
                            TypeExpr::Simple(n) if n.starts_with("function:") => {
                                let rt_name = &n["function:".len()..];
                                Some(self.resolve_type(&TypeExpr::Simple(rt_name.to_string())).unwrap())
                            }
                            _ => None,
                        };

                        let fn_type = if let Some(rt) = ret_type {
                            match rt {
                                inkwell::types::BasicTypeEnum::IntType(t) => t.fn_type(&arg_types, false),
                                inkwell::types::BasicTypeEnum::FloatType(t) => t.fn_type(&arg_types, false),
                                inkwell::types::BasicTypeEnum::PointerType(t) => t.fn_type(&arg_types, false),
                                _ => self.context.void_type().fn_type(&arg_types, false),
                            }
                        } else {
                            self.context.void_type().fn_type(&arg_types, false)
                        };
                        self.builder.build_indirect_call(fn_type, fn_ptr, &llvm_args, name).unwrap();
                    }
                }
            }
            Stmt::With { ids, body } => {
                self.enter_scope();
                for id_expr in ids {
                    let (ptr, llvm_type, te) = match id_expr {
                        Expr::Variable(v) => self.gen_variable_ptr_with_type(v)?,
                        _ => return Err("With target must be a variable".to_string()),
                    };
                    if !llvm_type.is_struct_type() {
                        return Err("With target must be a record".to_string());
                    }
                    let struct_type = llvm_type.into_struct_type();
                    let type_key = format!("{:?}", llvm_type);
                    
                    let resolved_te = self.resolve_type_expr_meta(&te)?;
                    if let TypeExpr::Record { fields, variant_part } = resolved_te {
                        if let Some(field_indices) = self.record_fields.get(&type_key) {
                            for (field_name, &index) in field_indices {
                                let member_ptr = self.builder.build_struct_gep(struct_type, ptr, index, field_name).unwrap();
                                let member_type = struct_type.get_field_type_at_index(index).unwrap();
                                let field_te = self.find_field_te(&fields, variant_part.as_ref(), field_name).unwrap();
                                self.variables.last_mut().unwrap().insert(field_name.clone(), (member_ptr, member_type, field_te));
                            }
                        }
                    }
                }
                self.gen_stmt(body, function)?;
                self.exit_scope();
            }
            Stmt::Empty => {}
            _ => {}
        }
        Ok(())
    }

    fn gen_expr(&mut self, expr: &Expr) -> Result<BasicValueEnum<'ctx>, String> {
        match expr {
            Expr::Integer(n) => Ok(self.context.i64_type().const_int(*n as u64, false).into()),
            Expr::Real(n) => Ok(self.context.f64_type().const_float(*n).into()),
            Expr::Boolean(b) => Ok(self.context.bool_type().const_int(*b as u64, false).into()),
            Expr::Char(c) => Ok(self.context.i8_type().const_int(*c as u64, false).into()),
            Expr::String(s) => Ok(self.builder.build_global_string_ptr(s, "str").unwrap().as_pointer_value().into()),
            Expr::Nil => Ok(self.context.ptr_type(inkwell::AddressSpace::default()).const_null().into()),
            Expr::Variable(v) => {
                match self.gen_variable_ptr_with_type(&**v) {
                    Ok((ptr, llvm_type, _)) => {
                        Ok(self.builder.build_load(llvm_type, ptr, "loadtmp").unwrap().into())
                    }
                    Err(e) => {
                        // Allow procedure/function names as values for parameters
                        if let Variable::Id(id) = &**v {
                            if let Some(f) = self.module.get_function(id) {
                                return Ok(f.as_global_value().as_pointer_value().into());
                            }
                        }
                        Err(e)
                    }
                }
            }
            Expr::Unary { op, expr } => {
                let val = self.gen_expr(expr)?;
                match op {
                    UnaryOp::Not => Ok(self.builder.build_not(val.into_int_value(), "nottmp").unwrap().into()),
                    UnaryOp::Minus => {
                        if val.is_int_value() { Ok(self.builder.build_int_neg(val.into_int_value(), "negtmp").unwrap().into()) }
                        else { Ok(self.builder.build_float_neg(val.into_float_value(), "negtmp").unwrap().into()) }
                    }
                    UnaryOp::Plus => Ok(val),
                }
            }
            Expr::Binary { op, left, right } => {
                let mut lhs = self.gen_expr(left)?;
                let mut rhs = self.gen_expr(right)?;
                match op {
                    BinOp::Add | BinOp::Sub | BinOp::Mul | BinOp::Div | BinOp::Mod |
                    BinOp::Lt | BinOp::Lte | BinOp::Gt | BinOp::Gte | BinOp::Eq | BinOp::Neq => {
                        let (nl, nr) = self.coerce_to_same_type(lhs, rhs)?;
                        lhs = nl; rhs = nr;
                    }
                    _ => {}
                }
                match op {
                    BinOp::Add => {
                        if lhs.is_int_value() && rhs.is_int_value() {
                            let lw = lhs.into_int_value().get_type().get_bit_width();
                            if lw == 256 {
                                Ok(self.builder.build_or(lhs.into_int_value(), rhs.into_int_value(), "setunion").unwrap().into())
                            } else {
                                Ok(self.builder.build_int_add(lhs.into_int_value(), rhs.into_int_value(), "addtmp").unwrap().into())
                            }
                        } else if lhs.is_float_value() && rhs.is_float_value() {
                             Ok(self.builder.build_float_add(lhs.into_float_value(), rhs.into_float_value(), "addtmp").unwrap().into())
                        } else {
                            // Falling back to int if types are mixed after coercion attempt
                            Ok(lhs) 
                        }
                    }
                    BinOp::Sub => {
                         if lhs.is_int_value() && rhs.is_int_value() {
                            let lw = lhs.into_int_value().get_type().get_bit_width();
                            if lw == 256 {
                                let not_rhs = self.builder.build_not(rhs.into_int_value(), "notrhs").unwrap();
                                Ok(self.builder.build_and(lhs.into_int_value(), not_rhs, "setdiff").unwrap().into())
                            } else {
                                Ok(self.builder.build_int_sub(lhs.into_int_value(), rhs.into_int_value(), "subtmp").unwrap().into())
                            }
                         } else if lhs.is_float_value() && rhs.is_float_value() {
                              Ok(self.builder.build_float_sub(lhs.into_float_value(), rhs.into_float_value(), "subtmp").unwrap().into())
                         } else { Ok(lhs) }
                    }
                    BinOp::Mul => {
                         if lhs.is_int_value() && rhs.is_int_value() {
                            let lw = lhs.into_int_value().get_type().get_bit_width();
                            if lw == 256 {
                                Ok(self.builder.build_and(lhs.into_int_value(), rhs.into_int_value(), "setinter").unwrap().into())
                            } else {
                                Ok(self.builder.build_int_mul(lhs.into_int_value(), rhs.into_int_value(), "multmp").unwrap().into())
                            }
                         } else if lhs.is_float_value() && rhs.is_float_value() {
                              Ok(self.builder.build_float_mul(lhs.into_float_value(), rhs.into_float_value(), "multmp").unwrap().into())
                         } else { Ok(lhs) }
                    }
                    BinOp::Div => Ok(self.builder.build_int_signed_div(lhs.into_int_value(), rhs.into_int_value(), "divtmp").unwrap().into()),
                    BinOp::FloatDiv => Ok(self.builder.build_float_div(lhs.into_float_value(), rhs.into_float_value(), "fdivtmp").unwrap().into()),
                    BinOp::Mod => Ok(self.builder.build_int_signed_rem(lhs.into_int_value(), rhs.into_int_value(), "modtmp").unwrap().into()),
                    BinOp::And => Ok(self.builder.build_and(lhs.into_int_value(), rhs.into_int_value(), "andtmp").unwrap().into()),
                    BinOp::Or => Ok(self.builder.build_or(lhs.into_int_value(), rhs.into_int_value(), "ortmp").unwrap().into()),
                    BinOp::In => {
                        let element = lhs.into_int_value();
                        let set = rhs.into_int_value();
                        let set_type = set.get_type();
                        let bit = self.builder.build_int_z_extend(element, set_type, "bitext").unwrap();
                        let mask = self.builder.build_left_shift(set_type.const_int(1, false), bit, "mask").unwrap();
                        let and = self.builder.build_and(set, mask, "setand").unwrap();
                        Ok(self.builder.build_int_compare(inkwell::IntPredicate::NE, and, set_type.const_zero(), "isset").unwrap().into())
                    }
                    BinOp::Lt => Ok(self.builder.build_int_compare(inkwell::IntPredicate::SLT, lhs.into_int_value(), rhs.into_int_value(), "lttmp").unwrap().into()),
                    BinOp::Lte => Ok(self.builder.build_int_compare(inkwell::IntPredicate::SLE, lhs.into_int_value(), rhs.into_int_value(), "ltetmp").unwrap().into()),
                    BinOp::Gt => Ok(self.builder.build_int_compare(inkwell::IntPredicate::SGT, lhs.into_int_value(), rhs.into_int_value(), "gttmp").unwrap().into()),
                    BinOp::Gte => Ok(self.builder.build_int_compare(inkwell::IntPredicate::SGE, lhs.into_int_value(), rhs.into_int_value(), "gtetmp").unwrap().into()),
                    BinOp::Eq => Ok(self.builder.build_int_compare(inkwell::IntPredicate::EQ, lhs.into_int_value(), rhs.into_int_value(), "eqtmp").unwrap().into()),
                    BinOp::Neq => Ok(self.builder.build_int_compare(inkwell::IntPredicate::NE, lhs.into_int_value(), rhs.into_int_value(), "neqtmp").unwrap().into()),
                    _ => Err(format!("Operator {:?} not implemented in codegen", op)),
                }
            }
            Expr::Set(elements) => {
                let set_type = self.context.custom_width_int_type(256);
                let mut set_val = set_type.const_zero();
                for el in elements {
                    match el {
                        Element::Single(e) => {
                            let val = self.gen_expr(e)?.into_int_value();
                            let bit = self.builder.build_int_z_extend(val, set_type, "bitext").unwrap();
                            let mask = self.builder.build_left_shift(set_type.const_int(1, false), bit, "mask").unwrap();
                            set_val = self.builder.build_or(set_val, mask, "setor").unwrap();
                        }
                        Element::Range(start, end) => {
                            let s = self.gen_expr(start)?.into_int_value();
                            let e = self.gen_expr(end)?.into_int_value();
                            
                            let s_ext = self.builder.build_int_z_extend(s, set_type, "sext").unwrap();
                            let e_ext = self.builder.build_int_z_extend(e, set_type, "eext").unwrap();
                            
                            // Mask = (all_ones << s) & (all_ones >> (255 - e))
                            let all_ones = set_type.const_all_ones();
                            let mask_s = self.builder.build_left_shift(all_ones, s_ext, "masks").unwrap();
                            
                            let max_bits = set_type.const_int(255, false);
                            let shift_r = self.builder.build_int_sub(max_bits, e_ext, "shiftr").unwrap();
                            let mask_e = self.builder.build_right_shift(all_ones, shift_r, false, "maske").unwrap();
                            
                            let range_mask = self.builder.build_and(mask_s, mask_e, "rangemask").unwrap();
                            set_val = self.builder.build_or(set_val, range_mask, "setor").unwrap();
                        }
                    }
                }
                Ok(set_val.into())
            }
            Expr::FunctionCall { name, args } => {
                if name == "Chr" {
                    let arg = self.gen_expr(&args.as_ref().unwrap()[0])?.into_int_value();
                    return Ok(self.builder.build_int_truncate(arg, self.context.i8_type(), "chr").unwrap().into());
                }
                if name == "Ord" {
                    let arg = self.gen_expr(&args.as_ref().unwrap()[0])?.into_int_value();
                    return Ok(self.builder.build_int_z_extend(arg, self.context.i64_type(), "ord").unwrap().into());
                }

                let mut llvm_args = Vec::new();
                if let Some(args) = args {
                    for arg in args {
                        llvm_args.push(self.gen_expr(arg)?.into());
                    }
                }

                if let Some(function_to_call) = self.module.get_function(name) {
                    Ok(self.builder.build_call(function_to_call, &llvm_args, name).unwrap().try_as_basic_value().left().unwrap())
                } else {
                    // Indirect function call
                    let (ptr, llvm_type, te) = self.get_variable(name).ok_or_else(|| format!("Function '{}' not found", name))?;
                    let fn_ptr = self.builder.build_load(*llvm_type, *ptr, "fnptr").unwrap().into_pointer_value();
                    
                    let mut arg_types = Vec::new();
                    for arg in &llvm_args {
                        let basic_val = match arg {
                            inkwell::values::BasicMetadataValueEnum::IntValue(i) => i.as_basic_value_enum(),
                            inkwell::values::BasicMetadataValueEnum::FloatValue(f) => f.as_basic_value_enum(),
                            inkwell::values::BasicMetadataValueEnum::PointerValue(p) => p.as_basic_value_enum(),
                            _ => unreachable!(),
                        };
                        arg_types.push(basic_val.get_type().into());
                    }
                    
                    let ret_type = match te {
                        TypeExpr::Simple(n) if n.starts_with("function:") => {
                            let rt_name = &n["function:".len()..];
                            self.resolve_type(&TypeExpr::Simple(rt_name.to_string())).unwrap()
                        }
                        _ => self.context.i64_type().as_basic_type_enum(), // Default for functions
                    };

                    let fn_type = match ret_type {
                        inkwell::types::BasicTypeEnum::IntType(t) => t.fn_type(&arg_types, false),
                        inkwell::types::BasicTypeEnum::FloatType(t) => t.fn_type(&arg_types, false),
                        inkwell::types::BasicTypeEnum::PointerType(t) => t.fn_type(&arg_types, false),
                        _ => self.context.i64_type().fn_type(&arg_types, false),
                    };
                    Ok(self.builder.build_indirect_call(fn_type, fn_ptr, &llvm_args, name).unwrap().try_as_basic_value().left().unwrap())
                }
            }
            _ => Err(format!("Expression {:?} not implemented in codegen", expr)),
        }
    }

    fn gen_target_ptr(&mut self, expr: &Expr) -> Result<PointerValue<'ctx>, String> {
        match expr {
            Expr::Variable(v) => self.gen_variable_ptr(v),
            _ => Err("Invalid assignment target".to_string()),
        }
    }

    fn gen_variable_ptr(&mut self, var: &Variable) -> Result<PointerValue<'ctx>, String> {
        self.gen_variable_ptr_with_type(var).map(|(ptr, _, _)| ptr)
    }

    fn gen_variable_ptr_with_type(&mut self, var: &Variable) -> Result<(PointerValue<'ctx>, inkwell::types::BasicTypeEnum<'ctx>, TypeExpr), String> {
        match var {
            Variable::Id(id) => {
                self.get_variable(id).cloned().ok_or_else(|| format!("Variable '{}' not found in codegen", id))
            }
            Variable::MemberAccess { record, field } => {
                let (ptr, llvm_type, te) = match &**record {
                    Expr::Variable(v) => self.gen_variable_ptr_with_type(v)?,
                    _ => return Err("Member access source must be a variable".to_string()),
                };
                if !llvm_type.is_struct_type() { return Err("Member access target is not a record".to_string()); }
                let struct_type = llvm_type.into_struct_type();
                let type_key = format!("{:?}", llvm_type);
                let index = *self.record_fields.get(&type_key).and_then(|m| m.get(field))
                    .ok_or_else(|| format!("Field '{}' not found in record", field))?;
                let member_ptr = self.builder.build_struct_gep(struct_type, ptr, index, field).unwrap();
                let member_type = struct_type.get_field_type_at_index(index).unwrap();
                
                // We need the TypeExpr of the field.
                let resolved_te = self.resolve_type_expr_meta(&te)?;
                if let TypeExpr::Record { fields, variant_part } = resolved_te {
                    let field_te = self.find_field_te(&fields, variant_part.as_ref(), field)
                        .ok_or_else(|| format!("Field '{}' not found in record AST", field))?;
                    Ok((member_ptr, member_type, field_te))
                } else {
                    Err("Internal error: resolved record type is not a record".to_string())
                }
            }
            Variable::ArrayAccess { array, indices } => {
                let (ptr, llvm_type, te) = match &**array {
                    Expr::Variable(v) => self.gen_variable_ptr_with_type(v)?,
                    _ => return Err("Array access source must be a variable".to_string()),
                };
                if !llvm_type.is_array_type() { return Err("Array access target is not an array".to_string()); }
                let array_type = llvm_type.into_array_type();
                let index = self.gen_expr(&indices[0])?.into_int_value();
                let zero = self.context.i64_type().const_int(0, false);
                let element_ptr = unsafe { self.builder.build_gep(array_type, ptr, &[zero, index], "arraygep").unwrap() };
                let element_type = array_type.get_element_type();
                
                let resolved_te = self.resolve_type_expr_meta(&te)?;
                if let TypeExpr::Array { element_type: et_expr, .. } = resolved_te {
                    Ok((element_ptr, element_type, *et_expr))
                } else {
                    Err("Internal error: resolved array type is not an array".to_string())
                }
            }
            Variable::PointerDeref(p) => {
                let ptr_val = self.gen_expr(p)?;
                if !ptr_val.is_pointer_value() {
                    return Err("Deref target is not a pointer".to_string());
                }
                let ptr = ptr_val.into_pointer_value();
                
                let p_te = match &**p {
                    Expr::Variable(v) => self.gen_variable_ptr_with_type(v)?.2,
                    _ => return Err("Pointer deref only supported on named variables for now".to_string()),
                };
                let resolved_te = self.resolve_type_expr_meta(&p_te)?;
                if let TypeExpr::Pointer(inner) = resolved_te {
                    let element_llvm = self.resolve_type(&inner)?;
                    Ok((ptr, element_llvm, *inner))
                } else {
                    Err("Deref on non-pointer type".to_string())
                }
            }
        }
    }

    fn resolve_type_expr_meta(&self, te: &TypeExpr) -> Result<TypeExpr, String> {
        match te {
            TypeExpr::Simple(name) => {
                match name.as_str() {
                    "integer" | "real" | "boolean" | "char" | "string" => Ok(te.clone()),
                    _ => {
                        self.types.get(name).map(|(_, t)| t.clone()).ok_or_else(|| format!("Type '{}' not defined", name))
                    }
                }
            }
            _ => Ok(te.clone()),
        }
    }

    fn find_field_te(&self, fields: &[VarDecl], variant_part: Option<&VariantPart>, field: &str) -> Option<TypeExpr> {
        for f in fields {
            if f.ids.contains(&field.to_string()) { return Some(f.type_expr.clone()); }
        }
        if let Some(vp) = variant_part {
            if let Some(tag) = &vp.tag_field {
                if tag == field { return Some(TypeExpr::Simple(vp.tag_type.clone())); }
            }
            for variant in &vp.variants {
                if let Some(t) = self.find_field_te(&variant.fields, variant.nested_variant.as_deref(), field) {
                    return Some(t);
                }
            }
        }
        None
    }

    fn coerce_to_same_type(&mut self, lhs: BasicValueEnum<'ctx>, rhs: BasicValueEnum<'ctx>) -> Result<(BasicValueEnum<'ctx>, BasicValueEnum<'ctx>), String> {
        if lhs.get_type() == rhs.get_type() { return Ok((lhs, rhs)); }
        
        // Handle pointer vs other (mostly for string + char which is currently a pointer to constant string)
        if lhs.is_pointer_value() && (rhs.is_int_value() || rhs.is_float_value()) {
            return Ok((lhs, rhs)); // Let the caller handle this or fail gracefully
        }

        if lhs.is_int_value() && rhs.is_int_value() {
            let lw = lhs.into_int_value().get_type().get_bit_width();
            let rw = rhs.into_int_value().get_type().get_bit_width();
            if lw < rw { return Ok((self.builder.build_int_s_extend(lhs.into_int_value(), rhs.into_int_value().get_type(), "sext").unwrap().into(), rhs)); }
            else { return Ok((lhs, self.builder.build_int_s_extend(rhs.into_int_value(), lhs.into_int_value().get_type(), "sext").unwrap().into())); }
        }
        if lhs.is_int_value() && rhs.is_float_value() {
            return Ok((self.builder.build_signed_int_to_float(lhs.into_int_value(), rhs.get_type().into_float_type(), "sitofp").unwrap().into(), rhs));
        }
        if lhs.is_float_value() && rhs.is_int_value() {
            return Ok((lhs, self.builder.build_signed_int_to_float(rhs.into_int_value(), lhs.get_type().into_float_type(), "sitofp").unwrap().into()));
        }
        Ok((lhs, rhs))
    }
}
