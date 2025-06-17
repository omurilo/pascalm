#include "code.h"
#include "../symbol-table/symbol-table.h"
#include "utils.c"

CodeGenerator *create_code_generator(char *output_file) {
  CodeGenerator *code_gen = (CodeGenerator *)malloc(sizeof(CodeGenerator));

  code_gen->output_file = fopen(output_file, "w");
  code_gen->indent_level = 0;

  return code_gen;
}

void print_indent(CodeGenerator *code_gen) {
  for (int i = 0; i < code_gen->indent_level; i++) {
    fprintf(code_gen->output_file, "    ");
  }
}

const char *cast_pascal_to_c_type(TypeIdentifierNode *node) {
  printf("[DEBUG - cast] node type -> %s : node kind -> %s - name: ",
         get_node_type_name(node->base.type), get_symbol_kind_name(node->kind));
  switch (node->kind) {
  case SYMBOL_BUILTIN: {
    printf("%s (%d.%d-%d.%d)\n", node->name, node->base.location.first_line,
           node->base.location.first_column, node->base.location.last_line,
           node->base.location.last_column);
    if (strcmp(node->name, "char") == 0)
      return "char";
    if (strcmp(node->name, "integer") == 0)
      return "int";
    if (strcmp(node->name, "real") == 0)
      return "double";
    if (strcmp(node->name, "boolean") == 0)
      return "bool";
    if (strcmp(node->name, "string") == 0)
      return "string";
    return "void";
  }
  case SYMBOL_TYPE:
    printf("struct\n\n\n");
    return "struct";
  default:
    printf("void (%d.%d-%d.%d)\n\n\n", node->base.location.first_line,
           node->base.location.first_column, node->base.location.last_line,
           node->base.location.last_column);
    return "void";
  }
}

const char *resolve_expression(ASTNode *node) {
  switch (node->type) {
  case NODE_BINARY_EXPR:
    // left - op - right
    break;
  case NODE_UNARY_EXPR:
    // op - right
    break;
  case NODE_SET_CONSTRUCTOR:
    // lower - upper (elemet) / elements - capacity - count
    break;
  case NODE_FUNC_CALL:
    break;
  case NODE_LITERAL: {
    LiteralNode *literal = (LiteralNode *)node;
    char *final;
    if (literal->literal_type == LITERAL_INTEGER) {
      if (asprintf(&final, "%d", literal->value.int_val) < 0) {
        yyerror("Out of memory");
        exit(2);
      }
      return (const char *) final;
    } else if (literal->literal_type == LITERAL_STRING) {
      if (asprintf(&final, "%s", literal->value.str_val) < 0) {
        yyerror("Out of memory");
        exit(2);
      }
      return (const char *) final;
    } else if (literal->literal_type == LITERAL_CHAR) {
      char *final;
      if (asprintf(&final, "%c", literal->value.char_val) < 0) {
        yyerror("Out of memory");
        exit(2);
      }
      return (const char *) final;
    } else if (literal->literal_type == LITERAL_BOOLEAN) {
      if (asprintf(&final, "%s", literal->value.bool_val ? "true" : "false") <
          0) {
        yyerror("Out of memory");
        exit(2);
      }
      return (const char *) final;
    } else if (literal->literal_type == LITERAL_REAL) {
      if (asprintf(&final, "%.2f", literal->value.real_val) < 0) {
        yyerror("Out of memory");
        exit(2);
      }
      return (const char *) final;
    } else if (literal->literal_type == LITERAL_NIL) {
      printf("[DEBUG] Literal value nil: (null)\n");
      return NULL;
    }
    break;
  }
  case NODE_IDENTIFIER: {
    const char *id = resolve_variable_identifier(node);
    printf("NODE_IDENTIFIER: %s\n", id);
    return id;
  }

  case NODE_ARRAY_ACCESS: {
    const char *id = resolve_variable_identifier(node);
    printf("NODE_ARRAY_ACCESS: %s\n", id);
    return id;
  }

  case NODE_MEMBER_ACCESS: {
    const char *id = resolve_variable_identifier(node);
    printf("NODE_MEMBER_ACCESS: %s\n", id);
    return id;
  }

  case NODE_POINTER_DEREF: {
    const char *id = resolve_variable_identifier(node);
    printf("NODE_POINTER_DEREF: %s\n", id);
    return id;
  }
  default:
    printf(
        "[DEBUG resolve expression] -> NODE NOT MAPPED - node type name %s\n",
        get_node_type_name(node->type));
    break;
  }
  return NULL;
}

const char *resolve_identifier(ASTNode *node) {
  IdentifierNode *id_node = (IdentifierNode *)node;
  return id_node->name;
}

const char *resolve_type_identifier(ASTNode *node) {
  TypeIdentifierNode *type_node = (TypeIdentifierNode *)node;
  if (type_node->kind == SYMBOL_TYPE) {
    return resolve_identifier((ASTNode *)type_node->id);
  }
  return cast_pascal_to_c_type(type_node);
}

const char *resolve_variable_identifier(ASTNode *node) {
  if (node->type == NODE_IDENTIFIER) {
    return resolve_identifier(node);
  } else if (node->type == NODE_ARRAY_ACCESS) {
    // array - subscript_list (array maybe any of this self if)
    ArrayAccessNode *a_node = (ArrayAccessNode *)node;
    const char *id = resolve_variable_identifier(a_node->array);
    ListNode *subscripts = (ListNode *)a_node->subscript_list;
    char *final;
    if (asprintf(&final, "%s[", id) < 0) {
      yyerror("Out of memory");
      exit(2);
    }

    while (subscripts) {
      if (subscripts->element) {
        if (asprintf(&final, "%s%s", final,
                     resolve_expression(subscripts->element)) < 0) {
          yyerror("Out of memory");
          exit(2);
        }
      }

      subscripts = (ListNode *)subscripts->next;
      if (subscripts) {
        if (asprintf(&final, "%s, ", final) < 0) {
          yyerror("Out of memory");
          exit(2);
        }
      }
    }

    if (asprintf(&final, "%s]", final) < 0) {
      yyerror("Out of memory");
      exit(2);
    }

    return (const char *) final;
  } else if (node->type == NODE_MEMBER_ACCESS) {
    MemberAccessNode *m_node = (MemberAccessNode *)node;
    // record - field
    const char *record = resolve_variable_identifier(m_node->record);
    const char *field = resolve_variable_identifier(m_node->field);
    // TODO: refazer a parte de verificar o símbolo usando o contexto;
    int is_ref = 0;
    SymbolEntry *s = malloc(sizeof(SymbolEntry));
    if (s != NULL && s->kind == SYMBOL_VARIABLE) {
      is_ref = s->info.var_info.is_ref;
    }
    char *final;
    if (is_ref) {
      if (asprintf(&final, "%s->%s", record, field) < 0) {
        yyerror("Out of memory");
        exit(2);
      }
    } else {
      if (asprintf(&final, "%s.%s", record, field) < 0) {
        yyerror("Out of memory");
        exit(2);
      }
    }
    return (const char *) final;
  } else if (node->type == NODE_POINTER_DEREF) {
    // PointerDerefNode *d_node = (PointerDerefNode *)node;
    // pointer
  }
  return NULL;
}

void generate_program(CodeGenerator *code_gen, ASTNode *node) {
  ProgramNode *program = (ProgramNode *)node;

  fprintf(code_gen->output_file, "#include <stdio.h>\n");
  fprintf(code_gen->output_file, "#include <stdlib.h>\n");
  fprintf(code_gen->output_file, "#include <string.h>\n");
  fprintf(code_gen->output_file, "#include <stdbool.h>\n\n");

  generate_string_definition(code_gen);

  generate_block(code_gen, program->block, true);

  print_indent(code_gen);
  fprintf(code_gen->output_file, "return 0;\n");
  code_gen->indent_level--;
  fprintf(code_gen->output_file, "}\n");
}

void generate_block(CodeGenerator *code_gen, ASTNode *node, bool is_global) {
  /*
   struct BlockNode {
     ASTNode *labels;
     ->ASTNode *types;
     ASTNode *constants;
     ->ASTNode *variables;
     ->+-ASTNode *procs_funcs;
     ->ASTNode *statements;
   }
    */
  BlockNode *block = (BlockNode *)node;

  ListNode *types = (ListNode *)block->types;
  while (types) {
    if (types->element) {
      generate_type(code_gen, types->element);
    }

    types = (ListNode *)types->next;
    if (!types)
      fprintf(code_gen->output_file, "\n");
  }

  ListNode *vars = (ListNode *)block->variables;
  while (vars) {
    if (vars->element) {
      generate_vars(code_gen, vars->element);
    }

    vars = (ListNode *)vars->next;
    if (!vars)
      fprintf(code_gen->output_file, "\n");
  }

  if (is_global) {
    generate_strings_helper_functions(code_gen);
    generate_set_helper_functions(code_gen);
  }

  ListNode *procs_funcs = (ListNode *)block->procs_funcs;
  while (procs_funcs) {
    if (procs_funcs->element) {
      generate_function(code_gen, procs_funcs->element);
    }

    procs_funcs = (ListNode *)procs_funcs->next;
  }

  if (is_global) {
    fprintf(code_gen->output_file, "int main() {\n");
    code_gen->indent_level++;
  }

  ListNode *statements = (ListNode *)block->statements;
  while (statements) {
    if (statements->element) {
      generate_statement(code_gen, statements->element);
    }

    statements = (ListNode *)statements->next;
  }
}

void generate_vars(CodeGenerator *code_gen, ASTNode *node) {
  VarDeclarationNode *v_node = (VarDeclarationNode *)node;

  ASTNode **identifiers = (ASTNode **)malloc(sizeof(ASTNode **));

  ListNode *var_list = (ListNode *)v_node->var_list;
  int index = 0;
  while (var_list) {
    if (var_list->element) {
      if (index > 0)
        identifiers = realloc(identifiers, (index + 1) * sizeof(ASTNode **));
      identifiers[index] = var_list->element;
    }

    var_list = (ListNode *)var_list->next;
    index++;
  }

  TypeIdentifierNode *c_type_id =
      (TypeIdentifierNode *)malloc(sizeof(TypeIdentifierNode));
  switch (v_node->type_node->type) {
  case NODE_STRUCTURED_TYPE: {
    StructuredTypeNode *st_node = (StructuredTypeNode *)v_node->type_node;
    if (st_node->type->type == NODE_RECORD_TYPE) {
      for (int i = 0; i < index; i++) {
        if (code_gen->indent_level > 0) {
          print_indent(code_gen);
        }
        fprintf(code_gen->output_file, "%s %s;\n",
                resolve_type_identifier(st_node->type),
                resolve_identifier(identifiers[i]));
      }
      break;
    } else if (st_node->type->type == NODE_SET_TYPE) {
      printf("[DEBUG variables] -> NODE_SET_TYPE");
      if (code_gen->indent_level > 0) {
        print_indent(code_gen);
      }
      for (int i = 0; i < index; i++) {
        fprintf(code_gen->output_file, "unsigned long long %s = 0ULL;\n",
                resolve_identifier(identifiers[i]));
      }
      break;
    } else if (st_node->type->type == NODE_ARRAY_TYPE) {
      TypeDeclarationNode *t_node =
          (TypeDeclarationNode *)malloc(sizeof(TypeDeclarationNode));
      c_type_id->kind = SYMBOL_TYPE;
      for (int i = 0; i < index; i++) {
        c_type_id->id = (IdentifierNode *)identifiers[i];
        t_node->type_expr = v_node->type_node;
        t_node->identifier = (ASTNode *)c_type_id;
        generate_array(code_gen, (ASTNode *)t_node, false);
      }
      free(t_node);

      return;
    } else if (st_node->type->type == NODE_FILE_TYPE) {
      break;
    }

    break;
  }
  case NODE_SIMPLE_TYPE: {
    SimpleTypeNode *s_node = (SimpleTypeNode *)v_node->type_node;
    if (s_node->type->type == NODE_TYPE_IDENTIFIER) {
      c_type_id = (TypeIdentifierNode *)s_node->type;

      for (int i = 0; i < index; i++) {
        if (code_gen->indent_level > 0) {
          print_indent(code_gen);
        }

        fprintf(code_gen->output_file, "%s %s",
                resolve_type_identifier(s_node->type),
                resolve_identifier(identifiers[i]));
        if (c_type_id->kind == SYMBOL_BUILTIN &&
            strcmp(c_type_id->name, "integer") == 0) {
          fprintf(code_gen->output_file, " = 0");
        } else if (c_type_id->kind == SYMBOL_BUILTIN &&
                   strcmp(c_type_id->name, "boolean") == 0) {
          fprintf(code_gen->output_file, " = false");
        } else if (c_type_id->kind == SYMBOL_TYPE) {
          SymbolEntry *s = malloc(sizeof(SymbolEntry));
          if (s->info.type_info.definition->type == NODE_STRUCTURED_TYPE) {
            StructuredTypeNode *sym_t_node =
                (StructuredTypeNode *)s->info.type_info.definition;
            if (sym_t_node->type->type == NODE_SET_TYPE) {
              fprintf(code_gen->output_file, " = 0ULL");
            }
          } else if (s->info.type_info.definition->type == NODE_SIMPLE_TYPE) {
            printf("NODE_SIMPLE_TYPE\n");
          } else {
            printf("NODE_POINTER_TYPE\n");
          }
        }
        fprintf(code_gen->output_file, ";\n");
      }
      break;
    } else if (s_node->type->type == NODE_ENUMERATED_TYPE) {
      break;
    } else if (s_node->type->type == NODE_SUBRANGE_TYPE) {
      break;
    }
    break;
  }
  case NODE_POINTER_TYPE: {
    // PointerTypeNode *pt_node = (PointerTypeNode *)v_node->type_node;
    break;
  }
  default:
    break;
  }

  free(c_type_id);
  free(identifiers);
}

void generate_function(CodeGenerator *code_gen, ASTNode *node) {
  /* struct FuncDeclarationNode {
   ASTNode base;
   ASTNode *identifier;
   ASTNode *parameters;
   ASTNode *type;
   ASTNode *block_or_forward;
 };*/
  FuncDeclarationNode *func = (FuncDeclarationNode *)node;
  ProcDeclarationNode *proc = (ProcDeclarationNode *)node;

  SymbolEntry *s = (SymbolEntry *)malloc(sizeof(SymbolEntry));
  ASTNode *block_or_forward = (ASTNode *)malloc(sizeof(ASTNode));
  ASTNode *params = (ASTNode *)malloc(sizeof(ASTNode));

  if (node->type == NODE_FUNC_DECL) {
    fprintf(code_gen->output_file, "%s %s(",
            resolve_type_identifier(func->type), s->name);
    block_or_forward = func->block_or_forward;
    params = func->parameters;
  } else {
    fprintf(code_gen->output_file, "void %s(", s->name);
    block_or_forward = proc->block_or_forward;
    params = proc->parameters;
  }

  generate_parameters(code_gen, params);

  if (block_or_forward->type == NODE_FORWARD_DECL) {
    fprintf(code_gen->output_file, ");\n\n");
    free(s);
    free(params);
    free(block_or_forward);
    return;
  }

  fprintf(code_gen->output_file, "){\n");
  code_gen->indent_level++;

  generate_block(code_gen, s->info.func_info.body, false);

  code_gen->indent_level--;
  fprintf(code_gen->output_file, "}\n\n");

  // free(s);
  free(params);
  free(block_or_forward);
}

void generate_parameters(CodeGenerator *code_gen, ASTNode *node) {
  ParameterNode *params = (ParameterNode *)node;
  ListNode *params_list = (ListNode *)params->params_list;

  while (params_list) {
    if (params_list->element) {
      FormalParameterSectionNode *param =
          (FormalParameterSectionNode *)params_list->element;
      ListNode *identifiers = (ListNode *)param->identifiers;
      TypeIdentifierNode *p_t_id = (TypeIdentifierNode *)param->type;
      while (identifiers) {
        if (identifiers->element) {
          if (param->kind == PARAM_VALUE) {
            fprintf(code_gen->output_file, "%s %s",
                    resolve_type_identifier((ASTNode *)p_t_id),
                    resolve_identifier(identifiers->element));
          } else if (param->kind == PARAM_VAR) {
            fprintf(code_gen->output_file, "%s *%s",
                    resolve_type_identifier((ASTNode *)p_t_id),
                    resolve_identifier(identifiers->element));
          } else {
            if (param->kind == PARAM_PROCEDURE) {
              fprintf(code_gen->output_file, "void %s(",
                      resolve_identifier(identifiers->element));
            } else if (param->kind == PARAM_FUNCTION) {
              fprintf(code_gen->output_file, "%s %s(",
                      resolve_type_identifier(param->return_type),
                      resolve_identifier(identifiers->element));
            }
            generate_parameters(code_gen, param->parameters);
            fprintf(code_gen->output_file, ")");
          }
        }

        identifiers = (ListNode *)identifiers->next;
        if (identifiers)
          fprintf(code_gen->output_file, ", ");
      }
    }

    params_list = (ListNode *)params_list->next;
    if (params_list)
      fprintf(code_gen->output_file, ", ");
  }
}

void generate_type(CodeGenerator *code_gen, ASTNode *node) {
  TypeDeclarationNode *type_node = (TypeDeclarationNode *)node;
  switch (type_node->type_expr->type) {
  case NODE_SIMPLE_TYPE: {
    SimpleTypeNode *s_node = (SimpleTypeNode *)type_node->type_expr;
    if (s_node->type->type == NODE_TYPE_IDENTIFIER) {
      fprintf(code_gen->output_file, "typedef %s %s;\n",
              resolve_type_identifier(s_node->type),
              resolve_type_identifier(type_node->identifier));
      break;
    } else if (s_node->type->type == NODE_ENUMERATED_TYPE) {
      break;
    } else if (s_node->type->type == NODE_SUBRANGE_TYPE) {
      break;
    }

    break;
  }
  case NODE_STRUCTURED_TYPE: {
    StructuredTypeNode *s_node = (StructuredTypeNode *)type_node->type_expr;
    if (s_node->type->type == NODE_RECORD_TYPE) {
      generate_record(code_gen, node);
      break;
    } else if (s_node->type->type == NODE_SET_TYPE) {
      fprintf(code_gen->output_file, "typedef unsigned long long %s;\n",
              resolve_type_identifier(type_node->identifier));
    } else if (s_node->type->type == NODE_ARRAY_TYPE) {
      fprintf(code_gen->output_file, "typedef ");
      generate_array(code_gen, node, true);
      break;
    } else if (s_node->type->type == NODE_FILE_TYPE) {
      fprintf(code_gen->output_file, "// generate file\n");
      break;
    }
    break;
  }
  case NODE_POINTER_TYPE:
  default:
    printf("[DEBUG - generate type] %s node type\n",
           get_node_type_name(type_node->type_expr->type));
    break;
  }
}

void generate_record(CodeGenerator *code_gen, ASTNode *node) {
  TypeDeclarationNode *t_node = (TypeDeclarationNode *)node;
  StructuredTypeNode *s_node = (StructuredTypeNode *)t_node->type_expr;
  RecordTypeNode *r_node = (RecordTypeNode *)s_node->type;
  const char *type_name = resolve_type_identifier(t_node->identifier);
  fprintf(code_gen->output_file, "typedef struct %s {\n", type_name);
  code_gen->indent_level++;

  ListNode *fields = (ListNode *)r_node->field_list;
  while (fields) {
    if (fields->element) {
      ListNode *fixed_part =
          (ListNode *)((FieldListNode *)fields->element)->fixed_part;
      while (fixed_part) {
        if (fixed_part->element) {
          print_indent(code_gen);
          RecordFieldNode *rf_node = (RecordFieldNode *)fixed_part->element;
          SimpleTypeNode *rf_type = (SimpleTypeNode *)rf_node->record_type;

          ListNode *rf_field_list = (ListNode *)rf_node->field_list;
          while (rf_field_list) {
            if (rf_field_list->element) {
              fprintf(code_gen->output_file, "%s %s;\n",
                      resolve_type_identifier(rf_type->type),
                      resolve_identifier(rf_field_list->element));
            }
            rf_field_list = (ListNode *)rf_field_list->next;
          }
        }

        fixed_part = (ListNode *)fixed_part->next;
      }
    }

    fields = (ListNode *)fields->next;
  }

  code_gen->indent_level--;
  fprintf(code_gen->output_file, "} %s;\n", type_name);
}

void generate_array(CodeGenerator *code_gen, ASTNode *node,
                    bool disable_initialization) {
  TypeDeclarationNode *t_node = (TypeDeclarationNode *)node;
  StructuredTypeNode *s_node = (StructuredTypeNode *)t_node->type_expr;
  ArrayTypeNode *a_node = (ArrayTypeNode *)s_node->type;

  // type
  const char *element_type = (char *)malloc(sizeof(char));
  if (a_node->type->type == NODE_SIMPLE_TYPE) {
    SimpleTypeNode *s = (SimpleTypeNode *)a_node->type;
    element_type = resolve_type_identifier(s->type);
  }

  // index_list -> IndexList<indexes, count, capacity>
  IndexList *index_list = (IndexList *)a_node->index_list;
  int array_size = index_list->capacity;

  if (code_gen->indent_level > 0) {
    print_indent(code_gen);
  }

  for (int i = 0; i < index_list->count; i++) {
    ASTNode *element = index_list->indexes[i];
    if (element->type == NODE_SUBRANGE_TYPE) {
      SubrangeTypeNode *sr_node = (SubrangeTypeNode *)element;
      // lower -> constants
      ConstantValue lower = evaluate_constant(sr_node->lower);
      // upper -> constants
      ConstantValue upper = evaluate_constant(sr_node->upper);
      array_size = upper.value.int_val - lower.value.int_val + 1;
    } else if (element->type == NODE_ENUMERATED_TYPE) {
      // TODO:
    } else if (element->type == NODE_TYPE_IDENTIFIER) {
      // TODO:
    } else {
      printf("era pra quebrar? %s", get_node_type_name(element->type));
      exit(1);
    }
  }

  fprintf(code_gen->output_file, "%s %s[%d]", element_type,
          resolve_type_identifier(t_node->identifier), array_size);

  if (strcmp(element_type, "int") == 0 && !disable_initialization) {
    fprintf(code_gen->output_file, " = {0}");
  }

  fprintf(code_gen->output_file, ";\n");
}

void generate_assignment(CodeGenerator *code_gen, ASTNode *node) {
  AssignmentNode *a = (AssignmentNode *)node;
  const char *id = resolve_variable_identifier(a->target);

  SymbolEntry *s = malloc(sizeof(SymbolEntry));
  if (a->target->type == NODE_IDENTIFIER && s != NULL &&
      s->info.func_info.body != NULL) {
    fprintf(code_gen->output_file, "return ");
  } else {
    fprintf(code_gen->output_file, "%s = ", id);
  }

  generate_expression(code_gen, a->expression, false);
  fprintf(code_gen->output_file, ";\n");
}

void generate_if_statement(CodeGenerator *code_gen, ASTNode *node) {
  IfNode *if_stmt = (IfNode *)node;
  fprintf(code_gen->output_file, "if(");
  generate_expression(code_gen, if_stmt->condition, true);
  fprintf(code_gen->output_file, ") {\n");
  code_gen->indent_level++;
  generate_statement(code_gen, if_stmt->then_stmt);
  code_gen->indent_level--;
  if (if_stmt->else_stmt != NULL) {
    fprintf(code_gen->output_file, "} else {\n");
    code_gen->indent_level++;
    generate_statement(code_gen, if_stmt->else_stmt);
    code_gen->indent_level--;
    fprintf(code_gen->output_file, "}\n");
  } else {
    if (code_gen->indent_level > 0) {
      print_indent(code_gen);
    }
    fprintf(code_gen->output_file, "}\n");
  }
}

void generate_while_statement(CodeGenerator *code_gen, ASTNode *node) {}

void generate_for_statement(CodeGenerator *code_gen, ASTNode *node) {
  ForStmtNode *for_stmt = (ForStmtNode *)node;
  fprintf(code_gen->output_file, "for(");

  SymbolEntry *f_var = malloc(sizeof(SymbolEntry));

  if (f_var->info.var_info.type->type == NODE_SIMPLE_TYPE) {
    SimpleTypeNode *s_t = (SimpleTypeNode *)f_var->info.var_info.type;
    fprintf(code_gen->output_file,
            "%s %s = ", resolve_type_identifier(s_t->type), f_var->name);
  } else if (f_var->info.var_info.type->type == NODE_STRUCTURED_TYPE) {
    StructuredTypeNode *st_t = (StructuredTypeNode *)f_var->info.var_info.type;
    fprintf(code_gen->output_file,
            "%s %s = ", resolve_type_identifier(st_t->type), f_var->name);
  }

  fprintf(code_gen->output_file, "(%s-1);",
          for_stmt->is_downto ? resolve_expression(for_stmt->end_expr)
                              : resolve_expression(for_stmt->start_expr));
  fprintf(code_gen->output_file, for_stmt->is_downto ? " %s > " : " %s < ",
          f_var->name);
  fprintf(code_gen->output_file, "%s;",
          for_stmt->is_downto ? resolve_expression(for_stmt->start_expr)
                              : resolve_expression(for_stmt->end_expr));
  fprintf(code_gen->output_file, for_stmt->is_downto ? " %s--)" : " %s++)",
          f_var->name);
  fprintf(code_gen->output_file, "{\n");

  code_gen->indent_level++;
  generate_statement(code_gen, for_stmt->body);
  code_gen->indent_level--;

  if (code_gen->indent_level > 0) {
    print_indent(code_gen);
  }

  fprintf(code_gen->output_file, "}\n");
}

void generate_repeat_until_statement(CodeGenerator *code_gen, ASTNode *node) {}

void generate_list(CodeGenerator *code_gen, ASTNode *node) {
  ListNode *list = (ListNode *)node;

  while (list) {
    if (list->element) {
      // TODO: generate anything
    }

    list = (ListNode *)list->next;
  }
}

void generate_write(CodeGenerator *code_gen, ASTNode *node, bool line) {
  fprintf(code_gen->output_file, "printf(\"");

  ProcedureCallNode *proc = (ProcedureCallNode *)node;
  ListNode *params = (ListNode *)proc->params;

  while (params) {
    if (params->element) {
      const char *x = resolve_expression(params->element);
      printf("[DEBUG writeln] -> %s - %s\n", x,
             get_node_type_name(params->element->type));
      switch (params->element->type) {
      case NODE_LITERAL: {
        // LiteralNode *l = (LiteralNode *)params->element;
        fprintf(code_gen->output_file, "%s", x);
        break;
      }
      case NODE_ARRAY_ACCESS:
        fprintf(code_gen->output_file, "%%d");
        break;
      case NODE_BINARY_EXPR:
        break;
      case NODE_IDENTIFIER: {
        IdentifierNode *id = (IdentifierNode *)params->element;
        if (id->kind == SYMBOL_VARIABLE) {
          SymbolEntry *id_sym = malloc(sizeof(SymbolEntry));
          if (id_sym->info.var_info.type->type == NODE_SIMPLE_TYPE) {
            SimpleTypeNode *s_t =
                (SimpleTypeNode *)id_sym->info.type_info.definition;
            TypeIdentifierNode *s_t_id = (TypeIdentifierNode *)s_t->type;
            if (s_t_id->kind == SYMBOL_BUILTIN) {
              const char *type_name =
                  resolve_type_identifier((ASTNode *)s_t_id);
              if (strcmp(type_name, "int") == 0) {
                fprintf(code_gen->output_file, "%%d");
                break;
              } else if (strcmp(type_name, "char") == 0) {
                fprintf(code_gen->output_file, "%%c");
                break;
              } else if (strcmp(type_name, "bool") == 0) {
                fprintf(code_gen->output_file, "%%s");
                break;
              } else if (strcmp(type_name, "string") == 0) {
                fprintf(code_gen->output_file, "%%s");
                break;
              }
            }
          }
        }
        break;
      }
      default:
        printf("[DEBUG writeln] -> %s not mapped",
               get_node_type_name(params->element->type));
        break;
      }
    }

    params = (ListNode *)params->next;
    if (params)
      fprintf(code_gen->output_file, " ");
  }

  fprintf(code_gen->output_file, line ? "\\n\"" : "\"");

  ListNode *curr = (ListNode *)proc->params;

  while (curr) {
    if (curr->element && curr->element->type != NODE_LITERAL) {
      const char *x = resolve_expression(curr->element);
      fprintf(code_gen->output_file, "%s", x);
    }
    curr = (ListNode *)curr->next;
    if (curr && curr->element->type != NODE_LITERAL)
      fprintf(code_gen->output_file, ", ");
  }

  fprintf(code_gen->output_file, ")");
}

void generate_read(CodeGenerator *code_gen, ASTNode *node, bool line) {
  fprintf(code_gen->output_file, "scanf(");
  generate_expression(code_gen, node, true);
  fprintf(code_gen->output_file, line ? "\\n\")" : "\")");
}

void generate_proc_call_statement(CodeGenerator *code_gen, ASTNode *node) {
  bool is_function = node->type == NODE_FUNC_CALL;
  const char *func_name = "";
  if (is_function) {
    FunctionCallNode *f_call = (FunctionCallNode *)node;
    func_name = resolve_identifier(f_call->function);
  } else {
    ProcedureCallNode *p_call = (ProcedureCallNode *)node;
    func_name = resolve_identifier(p_call->procedure);
  }

  SymbolEntry *s = malloc(sizeof(SymbolEntry));

  if (s->kind == SYMBOL_BUILTIN) {
    if (strcmp(func_name, "write") == 0) {
      generate_write(code_gen, node, false);
      return;
    } else if (strcmp(func_name, "writeln") == 0) {
      generate_write(code_gen, node, true);
      return;
    } else if (strcmp(func_name, "read") == 0) {
      generate_write(code_gen, node, false);
      return;
    } else if (strcmp(func_name, "readln") == 0) {
      generate_write(code_gen, node, true);
      return;
    }
  } else {
    fprintf(code_gen->output_file, "%s(", func_name);
  }

  int var_params[255] = {0};
  int index = 0;

  if (s && s->info.func_info.params != NULL) {
    ParameterNode *s_params = (ParameterNode *)s->info.func_info.params;
    ListNode *s_params_list = (ListNode *)s_params->params_list;
    while (s_params_list) {
      if (s_params_list->element) {
        FormalParameterSectionNode *p =
            (FormalParameterSectionNode *)s_params_list->element;
        var_params[index] = p->kind == PARAM_VAR;
        index++;
      }
      s_params_list = (ListNode *)s_params_list->next;
    }
  }

  ListNode *params = is_function
                         ? (ListNode *)((FunctionCallNode *)node)->params
                         : (ListNode *)((ProcedureCallNode *)node)->params;

  index = 0;
  while (params) {
    if (params->element) {
      if (var_params[index] == 1)
        fprintf(code_gen->output_file, "&");
      generate_expression(code_gen, params->element, false);
    }

    params = (ListNode *)params->next;
    index++;
    if (params)
      fprintf(code_gen->output_file, ", ");
  }

  fprintf(code_gen->output_file, ")");
}

void generate_statement(CodeGenerator *code_gen, ASTNode *node) {
  if (code_gen->indent_level > 0) {
    print_indent(code_gen);
  }
  switch (node->type) {
  case NODE_ASSIGN_STMT: {
    generate_assignment(code_gen, node);
    break;
  }
  case NODE_LIST:
    generate_list(code_gen, node);
    break;
  case NODE_IF_STMT:
    generate_if_statement(code_gen, node);
    break;
  case NODE_CASE_STMT:
    fprintf(code_gen->output_file, "/* case or case else */\n");
    break;
  case NODE_WHILE_STMT:
    generate_while_statement(code_gen, node);
    break;
  case NODE_REPEAT_STMT:
    generate_repeat_until_statement(code_gen, node);
    break;
  case NODE_FOR_STMT:
    generate_for_statement(code_gen, node);
    break;
  case NODE_IDENTIFIER:
    fprintf(code_gen->output_file, "%s", resolve_identifier(node));
    break;
  case NODE_FUNC_CALL:
  case NODE_PROC_CALL:
    generate_proc_call_statement(code_gen, node);
    fprintf(code_gen->output_file, ";\n");
    break;
  case NODE_GOTO_STMT:
    fprintf(code_gen->output_file, "/* statement list */\n");
    break;
  case NODE_WITH_STMT:
    fprintf(code_gen->output_file, "/* statement list */\n");
    break;
  case NODE_LABELED_STMT:
    fprintf(code_gen->output_file, "/* statement list */\n");
    break;
  default:
    break;
  }
}

void generate_expression(CodeGenerator *code_gen, ASTNode *node, bool plain) {
  printf("[DEBUG generate_expression] node type %s\n",
         get_node_type_name(node->type));
  switch (node->type) {
  case NODE_BINARY_EXPR: {
    BinaryOperationNode *bin_node = (BinaryOperationNode *)node;
    if (bin_node->op == BINOP_IN) {
      fprintf(code_gen->output_file, "((");
      generate_expression(code_gen, bin_node->right, false);
      fprintf(code_gen->output_file, " & (1ULL << ");
      generate_expression(code_gen, bin_node->left, false);
      fprintf(code_gen->output_file, " %% 64)) != 0)");
    } else if (bin_node->op == BINOP_LT) {
      generate_expression(code_gen, bin_node->left, false);
      fprintf(code_gen->output_file, " < ");
      generate_expression(code_gen, bin_node->right, false);
    } else if (bin_node->op == BINOP_LTE) {
      generate_expression(code_gen, bin_node->left, false);
      fprintf(code_gen->output_file, " <= ");
      generate_expression(code_gen, bin_node->right, false);
    } else if (bin_node->op == BINOP_GT) {
      generate_expression(code_gen, bin_node->left, false);
      fprintf(code_gen->output_file, " > ");
      generate_expression(code_gen, bin_node->right, false);
    } else if (bin_node->op == BINOP_GTE) {
      generate_expression(code_gen, bin_node->left, false);
      fprintf(code_gen->output_file, " >= ");
      generate_expression(code_gen, bin_node->right, false);
    } else if (false) {
      // TODO: else if's for lt, lte, gt, gte, and, or, div, mod
    } else if (bin_node->op == BINOP_PLUS) {
      generate_expression(code_gen, bin_node->left, false);
      fprintf(code_gen->output_file, " + ");
      generate_expression(code_gen, bin_node->right, false);
    } else if (bin_node->op == BINOP_TIMES) {
      generate_expression(code_gen, bin_node->left, false);
      fprintf(code_gen->output_file, " * ");
      generate_expression(code_gen, bin_node->right, false);
    } else if (bin_node->op == BINOP_MINUS) {
      generate_expression(code_gen, bin_node->left, false);
      fprintf(code_gen->output_file, " - ");
      generate_expression(code_gen, bin_node->right, false);
    } else if (bin_node->op == BINOP_DIVIDE) {
      generate_expression(code_gen, bin_node->left, false);
      fprintf(code_gen->output_file, " / ");
      generate_expression(code_gen, bin_node->right, false);
    }
    break;
  }
  case NODE_UNARY_EXPR: {
    UnaryOperationNode *u_node = (UnaryOperationNode *)node;
    if (u_node->op == UNOP_MINUS) {
      fprintf(code_gen->output_file, "-");
      generate_expression(code_gen, u_node->operand, false);
    } else if (u_node->op == UNOP_NOT) {
      fprintf(code_gen->output_file, "!");
      generate_expression(code_gen, u_node->operand, false);
    } else if (u_node->op == UNOP_PLUS) {
      fprintf(code_gen->output_file, "+");
      generate_expression(code_gen, u_node->operand, false);
    }
    break;
  }
  case NODE_SET_CONSTRUCTOR: {
    // lower - upper (elemet) / elements - capacity - count
    SetLiteral *sl = (SetLiteral *)node;
    if (sl->count > 0) {
      fprintf(code_gen->output_file, "(0ULL");
      for (int i = 0; i < sl->count; i++) {
        SetElement *se = sl->elements[i];
        if (se->type == SET_ELEMENT_SINGLE) {
          LiteralNode *literal = (LiteralNode *)se->value.single_value;
          fprintf(code_gen->output_file, " | (1ULL << ");
          if (literal->literal_type == LITERAL_INTEGER) {
            fprintf(code_gen->output_file, "%d %% 64", literal->value.int_val);
          } else if (literal->literal_type == LITERAL_REAL) {
            fprintf(code_gen->output_file, "%.2f %% 64",
                    literal->value.real_val);
          } else if (literal->literal_type == LITERAL_BOOLEAN) {
            fprintf(code_gen->output_file, "%s",
                    literal->value.bool_val ? "true" : "false");
          } else if (literal->literal_type == LITERAL_STRING) {
            fprintf(code_gen->output_file,
                    plain ? "%s %% 64" : "make_string(\"%s\") %% 64",
                    literal->value.str_val);
          } else if (literal->literal_type == LITERAL_CHAR) {
            fprintf(code_gen->output_file, plain ? "%c %% 64" : "'%c' %% 64",
                    literal->value.char_val);
          }
          fprintf(code_gen->output_file, ")");
        } else if (se->type == SET_ELEMENT_RANGE) {
          printf("[DEBUG generate expression] - SET LITERAL -> elements %d "
                 "range start: %s - end: %s\n",
                 i, get_node_type_name(se->value.range.start->type),
                 get_node_type_name(se->value.range.end->type));
        }
      }
      fprintf(code_gen->output_file, ")");
    }
    break;
  }
  case NODE_FUNC_CALL: {
    generate_proc_call_statement(code_gen, node);
    break;
  }
  case NODE_LITERAL: {
    LiteralNode *literal = (LiteralNode *)node;
    if (literal->literal_type == LITERAL_INTEGER) {
      fprintf(code_gen->output_file, "%d", literal->value.int_val);
    } else if (literal->literal_type == LITERAL_REAL) {
      fprintf(code_gen->output_file, "%.2f", literal->value.real_val);
    } else if (literal->literal_type == LITERAL_BOOLEAN) {
      fprintf(code_gen->output_file, "%s",
              literal->value.bool_val ? "true" : "false");
    } else if (literal->literal_type == LITERAL_STRING) {
      fprintf(code_gen->output_file, plain ? "%s" : "make_string(\"%s\")",
              literal->value.str_val);
    } else if (literal->literal_type == LITERAL_CHAR) {
      fprintf(code_gen->output_file, plain ? "%c" : "'%c'",
              literal->value.char_val);
    }

    break;
  }
  case NODE_IDENTIFIER: {
    fprintf(code_gen->output_file, "%s", resolve_identifier(node));
    break;
  }
  case NODE_ARRAY_ACCESS: {
    const char *id = resolve_variable_identifier(node);
    fprintf(code_gen->output_file, "%s", id);
    break;
  }
  case NODE_MEMBER_ACCESS: {
    const char *id = resolve_variable_identifier(node);
    fprintf(code_gen->output_file, "%s", id);
    break;
  }
  case NODE_POINTER_DEREF: {
    break;
  }
  case NODE_SET_ELEMENT: {
    break;
  }
  default:
    printf("[DEBUG resolve expression] -> NODE NOT MAPPED - node type name "
           "%s\n",
           get_node_type_name(node->type));
    break;
  }
}
