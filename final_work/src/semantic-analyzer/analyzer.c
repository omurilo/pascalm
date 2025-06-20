#include "analyzer.h"
#include "../logger.h"
#include <assert.h>

/* ================================================================== */
/* DECLARAÇÕES ANTECIPADAS (FORWARD DECLS)                 */
/* ================================================================== */
// Funções estáticas internas ao módulo do analisador. Essencial para
// permitir que as funções se chamem mutuamente de forma organizada.

static void analyze_statement(ASTNode *statement, CompilerContext *context);
static ASTNode *analyze_expression(ASTNode *expression,
                                   CompilerContext *context);
static void analyze_type_definition(SymbolEntry *type_symbol,
                                    CompilerContext *context);
static void analyze_sub_routine_body(SymbolEntry *func_symbol,
                                     CompilerContext *context);

/* ================================================================== */
/* FUNÇÕES AUXILIARES DE ANÁLISE                    */
/* ================================================================== */

static void insert_builtin_types(CompilerContext *context,
                                 SourceLocation location) {
  char *builtin_types[5] = {"integer", "real", "boolean", "char", "string"};

  for (int i = 0; i < 5; i++) {
    ASTNode *result =
        create_builtin_type_identifier(builtin_types[i], location);
    TypeIdentifierNode *tid = (TypeIdentifierNode *)result;
    IdentifierNode *id = (IdentifierNode *)tid->id;

    SymbolEntry *s = create_symbol_entry(
        id->name, SYMBOL_BUILTIN, context->scope_stack->scope_level, location);
    s->info.type_info.definition = result;
    s->info.type_info.fields = NULL;

    id->symbol = s;
    tid->symbol = s;

    context_insert(context, id->name, s);
  }
}

// Retorna um nó de tipo built-in para um dado literal.
static ASTNode *get_type_from_literal(ASTNode *literal_node,
                                      CompilerContext *context) {
  if (!literal_node || literal_node->type != NODE_LITERAL)
    return NULL;
  LiteralNode *l = (LiteralNode *)literal_node;
  char *type_name;
  switch (l->literal_type) {
  case LITERAL_INTEGER:
    type_name = "integer";
    break;
  case LITERAL_REAL:
    type_name = "real";
    break;
  case LITERAL_BOOLEAN:
    type_name = "boolean";
    break;
  case LITERAL_CHAR:
    type_name = "char";
    break;
  case LITERAL_STRING:
    type_name = "string";
    break;
  default:
    return NULL;
  }
  return create_builtin_type_identifier(type_name, l->base.location);
}

static SymbolEntry *resolve_to_type_symbol(ASTNode *type_node,
                                           CompilerContext *context) {
  if (!type_node)
    return NULL;

  if (type_node->type == NODE_TYPE_IDENTIFIER) {
    IdentifierNode *id = ((TypeIdentifierNode *)type_node)->id;
    if (!id->symbol) {
      id->symbol = context_lookup(context, id->name);
    }
    SymbolEntry *s = id->symbol;
    return s;
  }
  if (type_node->type == NODE_STRUCTURED_TYPE) {
    return resolve_to_type_symbol(((StructuredTypeNode *)type_node)->type,
                                  context);
  }
  if (type_node->type == NODE_SIMPLE_TYPE) {
    return resolve_to_type_symbol(((SimpleTypeNode *)type_node)->type, context);
  }
  return NULL;
}

// Navega por apelidos de tipo (ex: type T2 = T1) até encontrar a definição re
// l.
static ASTNode *resolve_to_actual_type_def(ASTNode *type_node,
                                           CompilerContext *context) {
  if (!type_node)
    return NULL;

  if (type_node->type == NODE_TYPE_IDENTIFIER) {
    IdentifierNode *id = ((TypeIdentifierNode *)type_node)->id;
    if (!id->symbol) {
      id->symbol = context_lookup(context, id->name);
    }
    SymbolEntry *s = id->symbol;
    if (s && s->kind == SYMBOL_TYPE) {
      return resolve_to_actual_type_def(s->info.type_info.definition, context);
    }
  }

  if (type_node->type == NODE_STRUCTURED_TYPE) {
    return ((StructuredTypeNode *)type_node)->type;
  }
  if (type_node->type == NODE_SIMPLE_TYPE) {
    return resolve_to_actual_type_def(((SimpleTypeNode *)type_node)->type,
                                      context);
  }
  return type_node;
}

// Verifica se dois tipos são compatíveis para atribuição (dest := src).
static int check_type_compatibility(ASTNode *dest_type, ASTNode *src_type,
                                    CompilerContext *context) {
  if (!dest_type || !src_type)
    return 1;

  SymbolEntry *resolved_dest = resolve_to_type_symbol(dest_type, context);
  SymbolEntry *resolved_src = resolve_to_type_symbol(src_type, context);

  LOG_DEBUG("%s - %s", resolved_dest ? resolved_dest->name : NULL,
            resolved_src ? resolved_src->name : NULL);

  if (resolved_dest == resolved_src)
    return 1;

  // switch (resolved_dest->type) {
  // case NODE_TYPE_IDENTIFIER:
  //   TypeIdentifierNode *tid = (TypeIdentifierNode *)resolved_dest;
  //   IdentifierNode *id = (IdentifierNode *)tid->id;
  //   SymbolEntry *s = context_lookup(context, id->name);
  //   LOG_DEBUG("1.1 - %s - %x", id->name, s);
  //   break;
  // default:
  //   break;
  // }

  // TODO: Adicionar mais regras (ex: integer -> real)
  return 0;
}

/* ================================================================== */
/* ANALISADOR DE EXPRESSÕES (RETORNA TIPO)                 */
/* ================================================================== */
#include "analyzer.h"

void analyze_labels(ASTNode *label, CompilerContext *context) {
  LabelDeclarationNode *ld = (LabelDeclarationNode *)label;
  switch (ld->value->type) {
  case NODE_LITERAL: {
    // LiteralNode *l = (LiteralNode *)ld->value;
    // char *id;
    // if (l->literal_type == LITERAL_INTEGER) {
    //   sprintf(id, "L%d", l->value.int_val);
    // } else if (l->literal_type == LITERAL_REAL) {
    //   sprintf(id, "L%.2f", l->value.real_val);
    // } else if (l->literal_type == LITERAL_CHAR) {
    //   sprintf(id, "L%c", l->value.char_val);
    // } else if (l->literal_type == LITERAL_BOOLEAN) {
    //   sprintf(id, "L%s", l->value.bool_val ? "true" : "false");
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
  s->info.const_info.definition = const_node->const_expr;
  id->symbol = s;
  context_insert(context, id->name, s);
  ConstantValue v = evaluate_constant(context, constant);
  LOG_TRACE("[ANALYZE] %s is valid? %s", id->name, v.is_valid ? "sim" : "não");
}

void analyze_types(ASTNode *types, CompilerContext *context) {
  if (types == NULL)
    return;

  if (types->type != NODE_LIST) {
    ListNode *new_list = calloc(1, sizeof(ListNode *));
    new_list->base.type = NODE_LIST;
    types = (ASTNode *)new_list;
  }

  ListNode *curr = (ListNode *)types;
  while (curr) {
    if (curr->element) {
      TypeDeclarationNode *td = (TypeDeclarationNode *)curr->element;
      TypeIdentifierNode *tid = (TypeIdentifierNode *)td->identifier;
      IdentifierNode *id = (IdentifierNode *)tid->id;

      SymbolEntry *s = create_symbol_entry(id->name, tid->kind,
                                           context->scope_stack->scope_level,
                                           td->base.location);

      s->info.type_info.definition = td->type_expr;
      s->info.type_info.fields = NULL;
      id->symbol = s;
      tid->symbol = id->symbol;

      context_insert(context, id->name, s);
    }

    curr = (ListNode *)curr->next;
  }
}

void analyze_variables(ASTNode *variables, CompilerContext *context) {
  if (variables == NULL)
    return;

  if (variables->type != NODE_LIST) {
    ListNode *new_list = calloc(1, sizeof(ListNode *));
    new_list->base.type = NODE_LIST;
    new_list->base.location = variables->location;
    variables = (ASTNode *)new_list;
  }

  ListNode *vars = (ListNode *)variables;

  int offset = 0;
  int index = 0;
  while (vars) {
    if (vars->element) {
      VarDeclarationNode *variable = (VarDeclarationNode *)vars->element;
      ListNode *curr = (ListNode *)variable->var_list;
      while (curr) {
        if (curr->element) {
          IdentifierNode *id = (IdentifierNode *)curr->element;
          SymbolEntry *s = create_symbol_entry(
              id->name, SYMBOL_VARIABLE, context->scope_stack->scope_level,
              vars->base.location);

          s->info.var_info.offset = offset + index;
          s->info.var_info.type = variable->type_node;
          id->symbol = s;
          context_insert(context, id->name, s);
        }

        curr = (ListNode *)curr->next;
        offset++;
      }
    }

    vars = (ListNode *)vars->next;
    index++;
  }
}

void analyze_functions(ASTNode *funcs, CompilerContext *context) {
  if (funcs == NULL)
    return;

  if (funcs->type != NODE_LIST) {
    ListNode *new_list = calloc(1, sizeof(ListNode *));
    new_list->base.type = NODE_LIST;
    funcs = (ASTNode *)new_list;
  }

  ListNode *curr = (ListNode *)funcs;
  while (curr) {
    if (curr->element) {
      FuncDeclarationNode *fd = (FuncDeclarationNode *)curr->element;
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
            if (param->kind != PARAM_PROCEDURE &&
                param->kind != PARAM_FUNCTION) {
              ListNode *identifiers = (ListNode *)param->identifiers;
              int offset = 0;
              while (identifiers) {
                if (identifiers->element) {
                  IdentifierNode *id = (IdentifierNode *)identifiers->element;
                  SymbolEntry *s_p = create_symbol_entry(
                      id->name, SYMBOL_PARAMETER,
                      context->scope_stack->scope_level, fd->base.location);
                  s_p->info.var_info.is_ref = param->kind == PARAM_VAR;
                  s_p->info.var_info.type = param->type;
                  s_p->info.var_info.offset = index + offset;

                  context_insert(context, id->name, s_p);
                }

                identifiers = (ListNode *)identifiers->next;
                offset++;
              }
            } else {
              // TODO: tratar parametros de função e procedure
            }
          }

          params = (ListNode *)params->next;
          index++;
        }
      }

      analyze_statement(fd->parameters, context);
      analyze_statement(fd->block_or_forward, context);
      scope_stack_pop(context->scope_stack);
      context->current_function = NULL;
    }

    curr = (ListNode *)curr->next;
  }
}

// void analyze_statement(ASTNode *statement, CompilerContext *context) {
//   switch (statement->type) {
//   case NODE_LITERAL: {
//     break;
//   }
//   case NODE_LABEL_DECL: {
//     analyze_labels(statement, context);
//     break;
//   }
//   case NODE_CONST_DECL: {
//     analyze_constants(statement, context);
//     break;
//   }
//   case NODE_TYPE_DECL: {
//     analyze_types(statement, context);
//     break;
//   }
//   case NODE_VAR_DECL: {
//     analyze_variables(statement, context);
//     break;
//   }
//   case NODE_PROC_DECL:
//   case NODE_FUNC_DECL: {
//     analyze_functions(statement, context);
//     break;
//   }
//   case NODE_FORWARD_DECL: {
//     break;
//   }
//   case NODE_ENUMERATED_TYPE: {
//     break;
//   }
//   case NODE_SUBRANGE_TYPE: {
//     break;
//   }
//   case NODE_STRUCTURED_TYPE: {
//     break;
//   }
//   case NODE_SIMPLE_TYPE: {
//     break;
//   }
//   case NODE_ARRAY_TYPE: {
//     break;
//   }
//   case NODE_RECORD_TYPE: {
//     break;
//   }
//   case NODE_SET_TYPE: {
//     break;
//   }
//   case NODE_FILE_TYPE: {
//     break;
//   }
//   case NODE_POINTER_TYPE: {
//     break;
//   }
//   case NODE_POINTER_DEREF: {
//     break;
//   }
//   case NODE_COMPOUND_STMT: {
//     break;
//   }
//   case NODE_ASSIGN_STMT: {
//     AssignmentNode *ass = (AssignmentNode *)statement;
//     analyze_statement(ass->target, context);
//     analyze_statement(ass->expression, context);
//
//     if (ass->target->type == NODE_IDENTIFIER) {
//       IdentifierNode *id = (IdentifierNode *)ass->target;
//       char err[255];
//       switch (id->kind) {
//       case SYMBOL_VARIABLE:
//       case SYMBOL_LOCAL_VAR:
//       case SYMBOL_GLOBAL_VAR:
//       case SYMBOL_PARAMETER:
//       case SYMBOL_VAR_PARAM:
//       case SYMBOL_FIELD:
//         break;
//       case SYMBOL_FUNCTION:
//         if (context->current_function &&
//             strcmp(context->current_function->name, id->name) != 0) {
//           sprintf(err,
//                   "Only is possible to assign to %s (%s) as a return type of
//                   " "function.", get_symbol_kind_name(id->kind), id->name);
//           yyerror(err);
//           exit(1);
//         }
//         break;
//       case SYMBOL_CONSTANT:
//       case SYMBOL_TYPE:
//       case SYMBOL_ENUM_VALUE:
//       case SYMBOL_PROCEDURE:
//         sprintf(err, "Cannot assign to %s (%s -> not a variable)",
//                 get_symbol_kind_name(id->kind), id->name);
//         yyerror(err);
//         exit(1);
//         break;
//       case SYMBOL_UNKNOWN:
//         sprintf(err, "Identifier not resolved: %s", id->name);
//         yyerror(err);
//         exit(1);
//         break;
//       default:
//         yyerror("Invalid assignment target");
//         exit(1);
//         break;
//       }
//     }
//     break;
//   }
//   case NODE_FUNC_CALL:
//   case NODE_PROC_CALL: {
//     FunctionCallNode *func = (FunctionCallNode *)statement;
//     IdentifierNode *id = (IdentifierNode *)func->function;
//
//     if (id->kind == SYMBOL_BUILTIN) {
//       SymbolEntry *s = context_lookup(context, id->name);
//
//       if (!s) {
//         s = create_symbol_entry(id->name, SYMBOL_BUILTIN, 0,
//                                 func->base.location);
//
//         context_insert(context, id->name, s);
//       }
//
//       s->info.func_info.return_type = NULL;
//       s->info.func_info.params = func->params;
//
//       id->symbol = s;
//     }
//
//     analyze_statement(func->function, context);
//     analyze_statement(func->params, context);
//
//     SymbolEntry *s = context_lookup(context, id->name);
//     id->symbol = s;
//
//     break;
//   }
//   case NODE_IF_STMT: {
//     IfNode *if_stmt = (IfNode *)statement;
//     analyze_statement(if_stmt->condition, context);
//     analyze_statement(if_stmt->then_stmt, context);
//     if (if_stmt->else_stmt != NULL)
//       analyze_statement(if_stmt->else_stmt, context);
//     break;
//   }
//   case NODE_CASE_STMT: {
//     break;
//   }
//   case NODE_CASE_ITEM: {
//     break;
//   }
//   case NODE_CASE_LABEL: {
//     break;
//   }
//   case NODE_CASE_ELSE: {
//     break;
//   }
//   case NODE_WHILE_STMT: {
//     WhileStmtNode *while_stmt = (WhileStmtNode *)statement;
//     analyze_statement(while_stmt->condition, context);
//     analyze_statement(while_stmt->body, context);
//     break;
//   }
//   case NODE_REPEAT_STMT: {
//     RepeatUntilNode *repeat = (RepeatUntilNode *)statement;
//     analyze_statement(repeat->condition, context);
//     analyze_statement(repeat->body, context);
//     break;
//   }
//   case NODE_FOR_STMT: {
//     ForStmtNode *for_stmt = (ForStmtNode *)statement;
//     analyze_statement(for_stmt->start_expr, context);
//     analyze_statement(for_stmt->end_expr, context);
//     analyze_statement(for_stmt->variable, context);
//     analyze_statement(for_stmt->body, context);
//     break;
//   }
//   case NODE_WITH_STMT: {
//     WithNode *wi = (WithNode *)statement;
//     analyze_statement(wi->record_list, context);
//     analyze_statement(wi->body, context);
//     break;
//   }
//   case NODE_GOTO_STMT: {
//     break;
//   }
//   case NODE_LABELED_STMT: {
//     break;
//   }
//   case NODE_BINARY_EXPR: {
//     break;
//   }
//   case NODE_UNARY_EXPR: {
//     break;
//   }
//   case NODE_IDENTIFIER: {
//     IdentifierNode *id_node = (IdentifierNode *)statement;
//     SymbolEntry *entry = context_lookup(context, id_node->name);
//     if (entry == NULL) {
//       char err_msg[256];
//       sprintf(err_msg, "Undeclared identifier '%s'", id_node->name);
//       yyerror(err_msg);
//       exit(1);
//     } else {
//       id_node->symbol = entry;
//     }
//     break;
//   }
//   case NODE_MEMBER_ACCESS: {
//     MemberAccessNode *m_node = (MemberAccessNode *)statement;
//     if (context->current_function != NULL) {
//       analyze_statement(m_node->record, context);
//     }
//     break;
//   }
//   case NODE_ARRAY_ACCESS: {
//     ArrayAccessNode *arr = (ArrayAccessNode *)statement;
//     if (context->current_function != NULL) {
//       analyze_statement(arr->subscript_list, context);
//     }
//
//     break;
//   }
//   case NODE_SET_CONSTRUCTOR: {
//     break;
//   }
//   case NODE_TYPE_IDENTIFIER: {
//     TypeIdentifierNode *tid = (TypeIdentifierNode *)statement;
//     IdentifierNode *id = tid->id;
//     if (tid->kind == SYMBOL_TYPE) {
//       analyze_statement((ASTNode *)tid->id, context);
//     }
//     tid->symbol = id->symbol;
//     break;
//   }
//   case NODE_FIELD_LIST: {
//     break;
//   }
//   case NODE_RECORD_FIELD: {
//     break;
//   }
//   case NODE_INDEX_LIST: {
//     break;
//   }
//   case NODE_PARAMETER: {
//     ParameterNode *p = (ParameterNode *)statement;
//     analyze_statement(p->params_list, context);
//     break;
//   }
//   case NODE_VARIANT_RECORD: {
//     break;
//   }
//   case NODE_VARIANT_LIST: {
//     break;
//   }
//   case NODE_VARIANT_PART: {
//     break;
//   }
//   case NODE_TAG_FIELD: {
//     break;
//   }
//   case NODE_FIXED_PART: {
//     break;
//   }
//   case NODE_FORMAL_PARAM_SECTION: {
//     FormalParameterSectionNode *fp = (FormalParameterSectionNode *)statement;
//     // TypeIdentifierNode *t_id = (TypeIdentifierNode *)fp->type; //
//     verificar
//     // os tipos
//
//     switch (fp->kind) {
//     case PARAM_FUNCTION:
//       analyze_statement(fp->parameters, context);
//       analyze_statement(fp->return_type, context);
//       break;
//     case PARAM_PROCEDURE:
//       analyze_statement(fp->parameters, context);
//       break;
//     case PARAM_VAR:
//     case PARAM_VALUE:
//       analyze_statement(fp->type, context);
//       analyze_statement(fp->identifiers, context);
//
//       ListNode *identifiers = (ListNode *)fp->identifiers;
//
//       while (identifiers) {
//         if (identifiers->element) {
//           IdentifierNode *id = (IdentifierNode *)identifiers->element;
//           SymbolEntry *s = context_lookup(context, id->name);
//
//           if (s) {
//             s->info.var_info.is_ref = fp->kind == PARAM_VAR;
//             id->symbol = s;
//           }
//         }
//
//         identifiers = (ListNode *)identifiers->next;
//       }
//
//       analyze_statement(fp->identifiers, context);
//       break;
//     }
//
//     break;
//   }
//   case NODE_LIST: {
//     ListNode *list = (ListNode *)statement;
//     while (list) {
//       if (list->element) {
//         analyze_statement(list->element, context);
//       }
//
//       list = (ListNode *)list->next;
//     }
//     break;
//   }
//   default:
//     printf("%s\n", get_node_type_name(statement->type));
//     break;
//   }
// }

static ASTNode *analyze_expression(ASTNode *expression,
                                   CompilerContext *context) {
  if (!expression)
    return NULL;

  switch (expression->type) {
  case NODE_IDENTIFIER: {
    IdentifierNode *id = (IdentifierNode *)expression;
    if (id->symbol == NULL) {
      id->symbol = context_lookup(context, id->name);
      if (!id->symbol) {
        char err[100];
        sprintf(err, "Undeclared identifier '%s'", id->name);
        yyerror(err);
        exit(1);
      }
    }

    expression->result_type = id->symbol->info.var_info.type;
    return expression->result_type;
  }
  case NODE_LITERAL: {
    expression->result_type = get_type_from_literal(expression, context);
    return expression->result_type;
  }
  case NODE_ARRAY_ACCESS: {
    ArrayAccessNode *a_node = (ArrayAccessNode *)expression;
    ASTNode *array_base_type = analyze_expression(a_node->array, context);
    analyze_statement(a_node->subscript_list, context);

    ASTNode *array_def = resolve_to_actual_type_def(array_base_type, context);
    if (array_def && array_def->type == NODE_ARRAY_TYPE) {
      ASTNode *element_type = ((ArrayTypeNode *)array_def)->type;
      expression->result_type = element_type;
      return element_type;
    }
    yyerror("Variable is not an array and cannot be indexed.");
    exit(1);
  }
  case NODE_MEMBER_ACCESS: {
    MemberAccessNode *m_node = (MemberAccessNode *)expression;
    ASTNode *record_base_type = analyze_expression(m_node->record, context);
    ASTNode *record_def = resolve_to_actual_type_def(record_base_type, context);

    if (!record_def || record_def->type != NODE_RECORD_TYPE) {
      yyerror("Attempt to access a field on a non-record type.");
      exit(1);
    }

    SymbolEntry *record_type_symbol =
        resolve_to_type_symbol(record_base_type, context);
    IdentifierNode *field_id = (IdentifierNode *)m_node->field;
    SymbolEntry *field_symbol = context_lookup_field(
        record_type_symbol->info.type_info.fields, field_id->name);

    if (!field_symbol) {
      char err[100];
      sprintf(err, "Field '%s' not found in record type.", field_id->name);
      yyerror(err);
      exit(1);
    }

    field_id->symbol = field_symbol;
    expression->result_type = field_symbol->info.var_info.type;
    return expression->result_type;
  }
  case NODE_BINARY_EXPR: {
    BinaryOperationNode *bin_op = (BinaryOperationNode *)expression;
    ASTNode *left_type = analyze_expression(bin_op->left, context);
    ASTNode *right_type = analyze_expression(bin_op->right, context);
    // TODO: Lógica para determinar o tipo resultante e checar compatibilidade
    expression->result_type = left_type; // Placeholder
    return expression->result_type;
  }
  case NODE_FUNC_CALL:
    break;
  case NODE_LIST: { // Usado para listas de expressões (ex: subscripts de array)
    ListNode *list = (ListNode *)expression;
    while (list) {
      if (list->element)
        analyze_expression(list->element, context);
      list = (ListNode *)list->next;
    }
    return NULL;
  }
  default:
    LOG_ERROR("Compiler error: Unhandled node type '%s' in analyze_expression.",
              get_node_type_name(expression->type));
    return NULL;
  }
}

// NOVA FUNÇÃO: Analisa COMANDOS e estruturas de controle.
static void analyze_statement(ASTNode *statement, CompilerContext *context) {
  if (!statement)
    return;
  switch (statement->type) {
  case NODE_ASSIGN_STMT: {
    AssignmentNode *ass = (AssignmentNode *)statement;
    ASTNode *target_type = analyze_expression(ass->target, context);
    ASTNode *expr_type = analyze_expression(ass->expression, context);
    if (!check_type_compatibility(target_type, expr_type, context)) {
      yyerror("Type mismatch in assignment.");
    }
    break;
  }
  case NODE_IF_STMT: {
    IfNode *if_stmt = (IfNode *)statement;
    /* ASTNode* cond_type = */ analyze_expression(if_stmt->condition, context);
    // TODO: if(cond_type is not boolean) yyerror(...)

    analyze_statement(if_stmt->then_stmt, context);
    analyze_statement(if_stmt->else_stmt, context);
    break;
  }
  case NODE_BLOCK: {
    BlockNode *block = (BlockNode *)statement;
    // Um bloco dentro de outro pode ter suas próprias declarações
    scope_stack_push(context->scope_stack);
    if (block->variables)
      analyze_variables(block->variables, context);
    analyze_statement(block->statements, context);
    scope_stack_pop(context->scope_stack);
    break;
  }
  case NODE_LIST: {
    ListNode *list = (ListNode *)statement;
    while (list) {
      // A lista de um comando (ex: corpo de um FOR) contém outros comandos
      analyze_statement(list->element, context);
      list = (ListNode *)list->next;
    }
    break;
  }
  default:
    // Se não for um comando conhecido, pode ser uma chamada de procedimento
    // ou um erro. A delegação para analyze_expression aqui é um ponto fraco
    // e deve ser evitada. O ideal é ter cases para todos os tipos de COMANDOS.
    break;
  }
}
static void analyze_record_fields(SymbolEntry *record_type_symbol,
                                  CompilerContext *context) {
  ASTNode *def = resolve_to_actual_type_def(
      record_type_symbol->info.type_info.definition, context);
  if (!def || def->type != NODE_RECORD_TYPE)
    return;

  RecordTypeNode *r_node = (RecordTypeNode *)def;
  if (r_node->field_list) {
    FixedPartNode *fp =
        (FixedPartNode *)((FieldListNode *)r_node->field_list)->fixed_part;
    VariantPartNode *vp =
        (VariantPartNode *)((FieldListNode *)r_node->field_list)->variant_part;
    if (fp) {
      ListNode *field_decls = (ListNode *)fp->fields;
      while (field_decls) {
        RecordFieldNode *field_decl = (RecordFieldNode *)field_decls->element;
        ListNode *ids = (ListNode *)field_decl->field_list;
        while (ids) {
          IdentifierNode *id = (IdentifierNode *)ids->element;
          SymbolEntry *field_symbol = create_symbol_entry(
              id->name, SYMBOL_FIELD, record_type_symbol->scope_level + 1,
              id->base.location);
          field_symbol->info.var_info.type = field_decl->record_type;
          context_insert_field(context, record_type_symbol, field_symbol);
          id->symbol = field_symbol;
          ids = (ListNode *)ids->next;
        }
        field_decls = (ListNode *)field_decls->next;
      }
    }
    if (vp) {
      TagFieldNode *tag = (TagFieldNode *)vp->tag_field;
      IdentifierNode *tag_id = (IdentifierNode *)tag->field;
      TypeIdentifierNode *tag_tid = (TypeIdentifierNode *)tag->tag_type;
      SymbolEntry *tag_t_s =
          context_lookup(context, ((IdentifierNode *)tag_tid->id)->name);
      LOG_DEBUG("Qual é status? %s - %s", ((IdentifierNode *)tag_tid->id)->name, 
                tag_id->name);

      SymbolEntry *tag_symbol = create_symbol_entry(
          tag_id->name, SYMBOL_FIELD, record_type_symbol->scope_level + 1,
          tag_id->base.location);
      tag_symbol->info.var_info.type = tag->tag_type;
      context_insert_field(context, record_type_symbol, tag_symbol);
      tag_id->symbol = tag_symbol;

      VariantListNode *v_list_node = (VariantListNode *)vp->variant_list;
      ListNode *variants = (ListNode *)v_list_node->variants;
      int variant_index = 0;
      //
      while (variants) {
        VariantRecordNode *v_rec_node = (VariantRecordNode *)variants->element;
        if (v_rec_node->field_list) {
          FieldListNode *fl_node = (FieldListNode *)v_rec_node->field_list;
          FixedPartNode *fp_node = (FixedPartNode *)fl_node->fixed_part;
        }
        variants = (ListNode *)variants->next;
        variant_index++;
      }
    }
  }
}

// A função pública que orquestra tudo.
void analyze_semantics(ASTNode *root_node, CompilerContext *context) {
  if (!root_node) {
    LOG_ERROR("AST root is NULL. Aborting analysis.");
    return;
  }
  LOG_TRACE("Iniciando Análise Semântica...");

  ProgramNode *program = (ProgramNode *)root_node;
  if (!program->block) {
    LOG_ERROR("Program block is NULL. Aborting analysis.");
    return;
  }
  BlockNode *block = (BlockNode *)program->block;

  LOG_TRACE("Passagem 1: Coletando declarações de topo...");
  /* ADDING BUILTIN TYPES TO GLOBAL CONTEXT */
  insert_builtin_types(context, program->base.location);
  if (block->types) {
    analyze_types(block->types, context);
  }
  if (block->procs_funcs) {
    analyze_functions(block->procs_funcs, context);
  }

  LOG_TRACE("Passagem 2: Analisando definições de tipos e variáveis...");
  if (block->types) {
    ListNode *types = (ListNode *)block->types;
    while (types) {
      TypeDeclarationNode *td = (TypeDeclarationNode *)types->element;
      IdentifierNode *id = ((TypeIdentifierNode *)td->identifier)->id;
      if (id->symbol) {
        analyze_record_fields(id->symbol, context);
      }
      types = (ListNode *)types->next;
    }
  }
  if (block->variables) {
    analyze_variables(block->variables, context);
  }

  // --- PASSAGEM 3: Analisar corpos de funções e o bloco principal ---
  LOG_TRACE("Passagem 3: Analisando comandos...");
  if (block->procs_funcs) {
    ListNode *funcs = (ListNode *)block->procs_funcs;
    while (funcs) {
      if (funcs->element) {
        FuncDeclarationNode *func_decl = (FuncDeclarationNode *)funcs->element;
        analyze_statement(func_decl->block_or_forward, context);
      }
      funcs = (ListNode *)funcs->next;
    }
  }
  if (block->statements) {
    analyze_statement(block->statements, context);
  }

  LOG_TRACE("Análise Semântica concluída.");
}
