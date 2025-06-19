#include "analyzer.h"
#include "../logger.h"

void analyze_semantics(ASTNode *root_node, CompilerContext *curr_context) {
  ProgramNode *program = (ProgramNode *)root_node;
  BlockNode *block = (BlockNode *)program->block;
  ListNode *types = (ListNode *)block->types;
  ListNode *variables = (ListNode *)block->variables;
  ListNode *procs_funcs = (ListNode *)block->procs_funcs;
  ListNode *labels = (ListNode *)block->labels;
  ListNode *constants = (ListNode *)block->constants;
  ListNode *statements = (ListNode *)block->statements;

  ListNode *curr = labels;

  while (curr) {
    if (curr->element) {
      analyze_labels(curr->element, curr_context);
    }

    curr = (ListNode *)curr->next;
  }

  curr = constants;

  while (curr) {
    if (curr->element) {
      analyze_constants(curr->element, curr_context);
    }

    curr = (ListNode *)curr->next;
  }

  curr = types;

  while (curr) {
    if (curr->element) {
      analyze_types(curr->element, curr_context);
    }

    curr = (ListNode *)curr->next;
  }

  curr = variables;

  while (curr) {
    if (curr->element) {
      analyze_variables(curr->element, curr_context);
    }

    curr = (ListNode *)curr->next;
  }

  curr = procs_funcs;

  while (curr) {
    if (curr->element) {
      analyze_functions(curr->element, curr_context);
    }

    curr = (ListNode *)curr->next;
  }

  curr = statements;
  while (curr) {
    if (curr->element) {
      analyze_statements(curr->element, curr_context);
    }

    curr = (ListNode *)curr->next;
  }
}

void analyze_labels(ASTNode *label, CompilerContext *context) {
  LabelDeclarationNode *ld = (LabelDeclarationNode *)label;
  switch (ld->value->type) {
  case NODE_LITERAL: {
    // LiteralNode *l = (LiteralNode *)ld->value;
    // char *id;
    // if (l->literal_type == LITERAL_INTEGER) {
    //   sfprintf(stderr, id, "L%d", l->value.int_val);
    // } else if (l->literal_type == LITERAL_REAL) {
    //   sfprintf(stderr, id, "L%.2f", l->value.real_val);
    // } else if (l->literal_type == LITERAL_CHAR) {
    //   sfprintf(stderr, id, "L%c", l->value.char_val);
    // } else if (l->literal_type == LITERAL_BOOLEAN) {
    //   sfprintf(stderr, id, "L%s", l->value.bool_val ? "true" : "false");
    // }
    //
    // SymbolEntry *s = create_symbol_entry(strdup(id), SYMBOL_LABEL,
    //                                      context->scope_stack->scope_level,
    //                                      ld->base.location);
    // context_insert(context, strdup(id), s);
    break;
  }
  default:
    break;
  }
}

void analyze_constants(ASTNode *constant, CompilerContext *context) {
  ConstDeclarationNode *const_node = (ConstDeclarationNode *)constant;
  IdentifierNode *id = (IdentifierNode *)const_node->identifier;
  SymbolEntry *s = create_symbol_entry(id->name, SYMBOL_CONSTANT,
                                       context->scope_stack->scope_level,
                                       const_node->base.location);
  s->info.const_info.value = const_node->const_expr;
  id->symbol = s;
  context_insert(context, id->name, s);
  ConstantValue v = evaluate_constant(context, constant);
  LOG_DEBUG("[ANALYZE] %s is valid? %s", id->name, v.is_valid ? "sim" : "não");
}

void analyze_types(ASTNode *type, CompilerContext *context) {
  TypeDeclarationNode *td = (TypeDeclarationNode *)type;
  TypeIdentifierNode *tid = (TypeIdentifierNode *)td->identifier;
  IdentifierNode *id = (IdentifierNode *)tid->id;

  SymbolEntry *s =
      create_symbol_entry(id->name, tid->kind,
                          context->scope_stack->scope_level, td->base.location);

  s->info.type_info.definition = td->type_expr;
  tid->symbol = s;
  id->symbol = tid->symbol;

  context_insert(context, id->name, s);
}

void analyze_variables(ASTNode *variable, CompilerContext *context) {
  VarDeclarationNode *vars = (VarDeclarationNode *)variable;

  ListNode *curr = (ListNode *)vars->var_list;
  int offset = 0;
  while (curr) {
    if (curr->element) {
      IdentifierNode *id = (IdentifierNode *)curr->element;
      SymbolEntry *s = create_symbol_entry(id->name, SYMBOL_VARIABLE,
                                           context->scope_stack->scope_level,
                                           vars->base.location);

      if (vars->type_node->type == NODE_STRUCTURED_TYPE) {
        StructuredTypeNode *st_node = (StructuredTypeNode *)vars->type_node;
        if (st_node->type->type == NODE_ARRAY_TYPE) {
          ArrayTypeNode *arr_type = (ArrayTypeNode *)st_node->type;
          IndexList *idx_list = (IndexList *)arr_type->index_list;

          // s->info.var_info.num_dimensions = idx_list->count;
          // s->info.var_info.dimensions =
          //     calloc(idx_list->count, sizeof(DimensionBounds));
          s->info.var_info.offset = offset;
          s->info.var_info.type = vars->type_node;

          id->symbol = s;

          // for (int i = 0; i < idx_list->count; i++) {
          //   ASTNode *index_def = idx_list->indexes[i];
          //   if (index_def->type == NODE_SUBRANGE_TYPE) {
          //     SubrangeTypeNode *range = (SubrangeTypeNode *)index_def;
          //
          //     ConstantValue lower = evaluate_constant(context, range->lower);
          //     ConstantValue upper = evaluate_constant(context, range->upper);
          //
          //     if (lower.is_valid && upper.is_valid) {
          //       s->info.var_info.dimensions[i].lower = lower.value.int_val;
          //       s->info.var_info.dimensions[i].upper = upper.value.int_val;
          //     }
          //   }
          // }

          context_insert(context, id->name, s);

          offset++;
        }
        curr = (ListNode *)curr->next;
      }
    }
  }
}

void analyze_functions(ASTNode *func, CompilerContext *context) {
  FuncDeclarationNode *fd = (FuncDeclarationNode *)func;
  IdentifierNode *id = (IdentifierNode *)fd->identifier;
  SymbolEntry *s = context_lookup(context, id->name);

  if (!s) {
    s = create_symbol_entry(id->name, SYMBOL_FUNCTION,
                            context->scope_stack->scope_level,
                            fd->base.location);

    s->info.func_info.return_type = fd->type;
    s->info.func_info.params = fd->parameters;
    s->info.func_info.body = fd->block_or_forward;
    s->info.func_info.is_forward =
        fd->block_or_forward->type == NODE_FORWARD_DECL;

    context_insert(context, id->name, s);
  }

  id->symbol = s;

  scope_stack_push(context->scope_stack);
  context->current_function = s;

  if (fd->parameters && fd->parameters->type == NODE_PARAMETER) {
    ParameterNode *parameters = (ParameterNode *)fd->parameters;
    ListNode *params = (ListNode *)parameters->params_list;
    int index = 0;
    while (params) {
      if (params->element) {
        FormalParameterSectionNode *param =
            (FormalParameterSectionNode *)params->element;
        if (param->kind != PARAM_PROCEDURE && param->kind != PARAM_FUNCTION) {
          ListNode *identifiers = (ListNode *)param->identifiers;
          int offset = 0;
          while (identifiers) {
            if (identifiers->element) {
              IdentifierNode *id = (IdentifierNode *)identifiers->element;
              SymbolEntry *s_p = create_symbol_entry(
                  id->name, SYMBOL_PARAMETER, context->scope_stack->scope_level,
                  fd->base.location);
              s_p->info.var_info.is_ref = param->kind == PARAM_VAR;
              s_p->info.var_info.type = param->type;
              s_p->info.var_info.offset = index + offset;

              context_insert(context, id->name, s_p);
            }

            identifiers = (ListNode *)identifiers->next;
            offset++;
          }
        } else {
          // tratar parametros de função e procedure
        }
      }

      params = (ListNode *)params->next;
      index++;
    }
  }

  analyze_statements(fd->parameters, context);
  analyze_statements(fd->block_or_forward, context);
  scope_stack_pop(context->scope_stack);
  context->current_function = NULL;
}

void analyze_statements(ASTNode *statement, CompilerContext *context) {
  if (!statement)
    return;

  switch (statement->type) {
  case NODE_ASSIGN_STMT: {
    AssignmentNode *ass = (AssignmentNode *)statement;
    ASTNode *target_type = analyze_and_get_expression_type(ass->target, context);
    ASTNode *expr_type = analyze_and_get_expression_type(ass->expression, context);

    if (!check_type_compatibility(target_type, expr_type)) {
      yyerror("Type mismatch.");
    }
    break;

    if (ass->target->type == NODE_IDENTIFIER) {
      IdentifierNode *id = (IdentifierNode *)ass->target;
      switch (id->kind) {
      case SYMBOL_VARIABLE:
      case SYMBOL_LOCAL_VAR:
      case SYMBOL_GLOBAL_VAR:
      case SYMBOL_PARAMETER:
      case SYMBOL_VAR_PARAM:
      case SYMBOL_FIELD:
        break;
      case SYMBOL_FUNCTION:
        if (context->current_function &&
            strcmp(context->current_function->name, id->name) != 0) {
          LOG_ERROR("Only is possible to assign to %s (%s) as a return type of "
                    "function.",
                    get_symbol_kind_name(id->kind), id->name);
          exit(1);
        }
        break;
      case SYMBOL_CONSTANT:
      case SYMBOL_TYPE:
      case SYMBOL_ENUM_VALUE:
      case SYMBOL_PROCEDURE:
        LOG_ERROR("Cannot assign to %s (%s -> not a variable)",
                  get_symbol_kind_name(id->kind), id->name);
        exit(1);
        break;
      case SYMBOL_UNKNOWN:
        LOG_ERROR("Identifier not resolved: %s", id->name);
        exit(1);
        break;
      default:
        yyerror("Invalid assignment target");
        exit(1);
        break;
      }
    }
    break;
  }
  case NODE_PROC_CALL: {
    FunctionCallNode *func = (FunctionCallNode *)statement;
    IdentifierNode *id = (IdentifierNode *)func->function;

    if (id->kind == SYMBOL_BUILTIN) {
      SymbolEntry *s = context_lookup(context, id->name);

      if (!s) {
        s = create_symbol_entry(id->name, SYMBOL_BUILTIN, 0,
                                func->base.location);

        context_insert(context, id->name, s);
      }

      s->info.func_info.return_type = NULL;
      s->info.func_info.params = func->params;

      id->symbol = s;
    }

    analyze_statements(func->function, context);
    analyze_statements(func->params, context);

    SymbolEntry *s = context_lookup(context, id->name);
    id->symbol = s;

    break;
  }
  case NODE_IF_STMT: {
    IfNode *if_stmt = (IfNode *)statement;
    analyze_statements(if_stmt->condition, context);
    analyze_statements(if_stmt->then_stmt, context);
    if (if_stmt->else_stmt != NULL)
      analyze_statements(if_stmt->else_stmt, context);
    break;
  }
  case NODE_WHILE_STMT: {
    WhileStmtNode *while_stmt = (WhileStmtNode *)statement;
    analyze_statements(while_stmt->condition, context);
    analyze_statements(while_stmt->body, context);
    break;
  }
  case NODE_REPEAT_STMT: {
    RepeatUntilNode *repeat = (RepeatUntilNode *)statement;
    analyze_statements(repeat->condition, context);
    analyze_statements(repeat->body, context);
    break;
  }
  case NODE_FOR_STMT: {
    ForStmtNode *for_stmt = (ForStmtNode *)statement;
    analyze_statements(for_stmt->start_expr, context);
    analyze_statements(for_stmt->end_expr, context);
    analyze_statements(for_stmt->variable, context);
    analyze_statements(for_stmt->body, context);
    break;
  }
  case NODE_WITH_STMT: {
    WithNode *wi = (WithNode *)statement;
    analyze_statements(wi->record_list, context);
    analyze_statements(wi->body, context);
    break;
  }
  case NODE_GOTO_STMT: {
    break;
  }
  case NODE_LABELED_STMT: {
    break;
  }
  case NODE_LIST: {
    ListNode *list = (ListNode *)statement;
    while (list) {
      if (list->element) {
        analyze_statements(list->element, context);
      }

      list = (ListNode *)list->next;
    }
    break;
  }
  case NODE_BLOCK: {
    scope_stack_push(context->scope_stack);
    BlockNode *block = (BlockNode *)statement;
    if (block->labels)
      analyze_statements(block->labels, context);
    if (block->constants)
      analyze_statements(block->constants, context);
    if (block->types)
      analyze_statements(block->types, context);
    if (block->variables)
      analyze_statements(block->variables, context);
    if (block->procs_funcs)
      analyze_statements(block->procs_funcs, context);
    if (block->statements)
      analyze_statements(block->statements, context);
    scope_stack_pop(context->scope_stack);
    break;
  }
  default:
    LOG_DEBUG("statements - %s\n", get_node_type_name(statement->type));
    break;
  }
}

ASTNode *analyze_and_get_expression_type(ASTNode *expression,
                                         CompilerContext *context) {
  if (!expression)
    return NULL;

  switch (expression->type) {
  case NODE_FUNC_CALL:
  case NODE_CASE_STMT: {
    break;
  }
  case NODE_CASE_ITEM: {
    break;
  }
  case NODE_CASE_LABEL: {
    break;
  }
  case NODE_CASE_ELSE: {
    break;
  }
  case NODE_BINARY_EXPR: {
    break;
  }
  case NODE_UNARY_EXPR: {
    break;
  }
  case NODE_ARRAY_ACCESS: {
    ArrayAccessNode *arr = (ArrayAccessNode *)expression;
    if (context->current_function != NULL) {
      // analyze_statements(arr->subscript_list, context);
    }

    break;
  }
  case NODE_SET_CONSTRUCTOR: {
    break;
  }
  case NODE_TYPE_IDENTIFIER: {
    TypeIdentifierNode *tid = (TypeIdentifierNode *)expression;
    IdentifierNode *id = tid->id;
    if (tid->kind == SYMBOL_TYPE) {
      // analyze_statements((ASTNode *)tid->id, context);
    }
    tid->symbol = id->symbol;
    break;
  }
  case NODE_FIELD_LIST: {
    break;
  }
  case NODE_RECORD_FIELD: {
    break;
  }
  case NODE_INDEX_LIST: {
    break;
  }
  case NODE_PARAMETER: {
    ParameterNode *p = (ParameterNode *)expression;
    // analyze_statements(p->params_list, context);
    break;
  }
  case NODE_VARIANT_RECORD: {
    break;
  }
  case NODE_VARIANT_LIST: {
    break;
  }
  case NODE_VARIANT_PART: {
    break;
  }
  case NODE_TAG_FIELD: {
    break;
  }
  case NODE_FIXED_PART: {
    break;
  }
  case NODE_FORMAL_PARAM_SECTION: {
    FormalParameterSectionNode *fp = (FormalParameterSectionNode *)expression;
    // TypeIdentifierNode *t_id = (TypeIdentifierNode *)fp->type; //
    // verificar os tipos

    switch (fp->kind) {
    case PARAM_FUNCTION:
      // analyze_statements(fp->parameters, context);
      // analyze_statements(fp->return_type, context);
      break;
    case PARAM_PROCEDURE:
      // analyze_statements(fp->parameters, context);
      break;
    case PARAM_VAR:
    case PARAM_VALUE:
      // analyze_statements(fp->type, context);
      // analyze_statements(fp->identifiers, context);

      ListNode *identifiers = (ListNode *)fp->identifiers;

      while (identifiers) {
        if (identifiers->element) {
          IdentifierNode *id = (IdentifierNode *)identifiers->element;
          SymbolEntry *s = context_lookup(context, id->name);

          if (s) {
            s->info.var_info.is_ref = fp->kind == PARAM_VAR;
            id->symbol = s;
          }
        }

        identifiers = (ListNode *)identifiers->next;
      }

      // analyze_statements(fp->identifiers, context);
      break;
    }

    break;
  }
  case NODE_IDENTIFIER: {
    IdentifierNode *id_node = (IdentifierNode *)expression;
    SymbolEntry *entry = context_lookup(context, id_node->name);
    if (entry == NULL) {
      LOG_ERROR("Undeclared identifier '%s'", id_node->name);
      exit(1);
    }      

    id_node->symbol = entry;
    return entry->info.var_info.type;
  }
  case NODE_MEMBER_ACCESS: {
    MemberAccessNode *m_node = (MemberAccessNode *)expression;
    // Analisa recursivamente a parte do record
    ASTNode *record_type =
        analyze_and_get_expression_type(m_node->record, context);

    // Agora, com o tipo do record, procure o campo 'field' dentro dele
    // e retorne o tipo do campo.
    // ...
  }
  case NODE_LITERAL: {
    break;
  }
  case NODE_LABEL_DECL: {
    analyze_labels(expression, context);
    break;
  }
  case NODE_CONST_DECL: {
    analyze_constants(expression, context);
    break;
  }
  case NODE_TYPE_DECL: {
    analyze_types(expression, context);
    break;
  }
  case NODE_VAR_DECL: {
    analyze_variables(expression, context);
    break;
  }
  case NODE_PROC_DECL:
  case NODE_FUNC_DECL: {
    analyze_functions(expression, context);
    break;
  }
  case NODE_FORWARD_DECL: {
    break;
  }
  case NODE_ENUMERATED_TYPE: {
    break;
  }
  case NODE_SUBRANGE_TYPE: {
    break;
  }
  case NODE_STRUCTURED_TYPE: {
    break;
  }
  case NODE_SIMPLE_TYPE: {
    break;
  }
  case NODE_ARRAY_TYPE: {
    break;
  }
  case NODE_RECORD_TYPE: {
    break;
  }
  case NODE_SET_TYPE: {
    break;
  }
  case NODE_FILE_TYPE: {
    break;
  }
  case NODE_POINTER_TYPE: {
    break;
  }
  case NODE_POINTER_DEREF: {
    break;
  }
  case NODE_COMPOUND_STMT: {
    break;
  }
  default:
                           break;
  }
  return NULL; // Tipo desconhecido
}

bool check_type_compatibility(ASTNode* type, ASTNode* check_type) {
  if (type->type != check_type->type) return false;
  // check deeply if the types is compatible
}
