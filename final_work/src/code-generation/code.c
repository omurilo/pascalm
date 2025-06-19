#include "code.h"
#include "../logger.h"

CodeGenerator *create_code_generator(char *output_file) {
  CodeGenerator *code_gen = calloc(1, sizeof(CodeGenerator));

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
  IdentifierNode *id = (IdentifierNode *)node->id;
  switch (node->kind) {
  case SYMBOL_BUILTIN: {
    if (strcmp(id->name, "char") == 0)
      return "char";
    if (strcmp(id->name, "integer") == 0)
      return "int";
    if (strcmp(id->name, "real") == 0)
      return "double";
    if (strcmp(id->name, "boolean") == 0)
      return "bool";
    if (strcmp(id->name, "string") == 0)
      return "string";
    return "void";
  }
  case SYMBOL_TYPE:
    LOG_ERROR("struct\n\n\n");
    return "struct";
  default:
    LOG_ERROR("void (%d.%d-%d.%d)\n\n\n", node->base.location.first_line,
              node->base.location.first_column, node->base.location.last_line,
              node->base.location.last_column);
    return "void";
  }
}

const char *resolve_identifier(ASTNode *node) {
  IdentifierNode *id_node = (IdentifierNode *)node;
  return id_node->name;
}

const char *resolve_type_identifier(ASTNode *node) {
  if (node->type == NODE_IDENTIFIER)
    return resolve_identifier(node);

  TypeIdentifierNode *type_node = (TypeIdentifierNode *)node;
  if (type_node->kind == SYMBOL_TYPE) {
    return resolve_identifier((ASTNode *)type_node->id);
  }
  return cast_pascal_to_c_type(type_node);
}

void generate_program(CodeGenerator *code_gen, CompilerContext *context,
                      ASTNode *node) {
  ProgramNode *program = (ProgramNode *)node;

  fprintf(code_gen->output_file, "#include <stdio.h>\n");
  fprintf(code_gen->output_file, "#include <stdlib.h>\n");
  fprintf(code_gen->output_file, "#include <string.h>\n");
  fprintf(code_gen->output_file, "#include <stdbool.h>\n\n");

  generate_string_definition(code_gen);

  generate_block(code_gen, context, program->block, true);

  print_indent(code_gen);
  fprintf(code_gen->output_file, "return 0;\n");
  code_gen->indent_level--;
  fprintf(code_gen->output_file, "}\n");
}

void generate_block(CodeGenerator *code_gen, CompilerContext *context,
                    ASTNode *node, bool is_global) {
  BlockNode *block = (BlockNode *)node;

  ListNode *types = (ListNode *)block->types;
  while (types) {
    if (types->element) {
      generate_type(code_gen, context, types->element);
    }

    types = (ListNode *)types->next;
    if (!types)
      fprintf(code_gen->output_file, "\n");
  }

  ListNode *vars = (ListNode *)block->variables;
  while (vars) {
    if (vars->element) {
      generate_vars(code_gen, context, vars->element);
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
      generate_function(code_gen, context, procs_funcs->element);
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
      generate_statement(code_gen, context, statements->element);
    }

    statements = (ListNode *)statements->next;
  }
}

void generate_vars(CodeGenerator *code_gen, CompilerContext *context,
                   ASTNode *node) {
  VarDeclarationNode *v_node = (VarDeclarationNode *)node;

  ASTNode **identifiers = calloc(1, sizeof(ASTNode **));

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

  TypeIdentifierNode *c_type = calloc(1, sizeof(TypeIdentifierNode));
  IdentifierNode *c_type_id = calloc(1, sizeof(IdentifierNode));

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
      LOG_ERROR("[DEBUG variables] -> NODE_SET_TYPE");
      if (code_gen->indent_level > 0) {
        print_indent(code_gen);
      }
      for (int i = 0; i < index; i++) {
        fprintf(code_gen->output_file, "unsigned long long %s = 0ULL;\n",
                resolve_identifier(identifiers[i]));
      }
      break;
    } else if (st_node->type->type == NODE_ARRAY_TYPE) {
      TypeDeclarationNode *t_node = calloc(1, sizeof(TypeDeclarationNode));
      c_type->kind = SYMBOL_TYPE;
      for (int i = 0; i < index; i++) {
        c_type->id = (IdentifierNode *)identifiers[i];
        t_node->type_expr = v_node->type_node;
        t_node->identifier = (ASTNode *)c_type;
        generate_array(code_gen, context, (ASTNode *)t_node, false);
      }

      return;
    } else if (st_node->type->type == NODE_FILE_TYPE) {
      break;
    }

    break;
  }
  case NODE_SIMPLE_TYPE: {
    SimpleTypeNode *s_node = (SimpleTypeNode *)v_node->type_node;
    if (s_node->type->type == NODE_TYPE_IDENTIFIER) {
      c_type = (TypeIdentifierNode *)s_node->type;
      c_type_id = (IdentifierNode *)c_type->id;

      for (int i = 0; i < index; i++) {
        if (code_gen->indent_level > 0) {
          print_indent(code_gen);
        }

        fprintf(code_gen->output_file, "%s %s",
                resolve_type_identifier(s_node->type),
                resolve_identifier(identifiers[i]));

        if (c_type->kind == SYMBOL_BUILTIN) {
          if (strcmp(c_type_id->name, "integer") == 0) {

            fprintf(code_gen->output_file, " = 0");
          } else if (strcmp(c_type_id->name, "boolean") == 0) {
            fprintf(code_gen->output_file, " = false");
          }
        } else if (c_type->kind == SYMBOL_TYPE) {
          SymbolEntry *s = context_lookup(context, c_type_id->name);
          if (s->info.type_info.definition->type == NODE_STRUCTURED_TYPE) {
            StructuredTypeNode *sym_t_node =
                (StructuredTypeNode *)s->info.type_info.definition;
            if (sym_t_node->type->type == NODE_SET_TYPE) {
              fprintf(code_gen->output_file, " = 0ULL");
            } else if (sym_t_node->type->type == NODE_RECORD_TYPE) {
              fprintf(code_gen->output_file, " = {0}");
            }
          } else if (s->info.type_info.definition->type == NODE_SIMPLE_TYPE) {
            LOG_ERROR("NODE_SIMPLE_TYPE\n");
          } else {
            LOG_ERROR("NODE_POINTER_TYPE\n");
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
}

void generate_function(CodeGenerator *code_gen, CompilerContext *context,
                       ASTNode *node) {
  FuncDeclarationNode *func = (FuncDeclarationNode *)node;
  IdentifierNode *id = (IdentifierNode *)func->identifier;
  SymbolEntry *current_function = id->symbol;

  if (node->type == NODE_FUNC_DECL) {
    fprintf(code_gen->output_file, "%s %s(",
            resolve_type_identifier(func->type), id->name);
  } else {
    fprintf(code_gen->output_file, "void %s(", id->name);
  }

  code_gen->current_function = current_function;

  generate_parameters(code_gen, context, func->parameters);

  if (func->block_or_forward->type == NODE_FORWARD_DECL) {
    fprintf(code_gen->output_file, ");\n\n");
    return;
  }

  fprintf(code_gen->output_file, "){\n");
  code_gen->indent_level++;

  generate_block(code_gen, context, func->block_or_forward, false);

  code_gen->indent_level--;
  fprintf(code_gen->output_file, "}\n\n");

  code_gen->current_function = NULL;
}

void generate_parameters(CodeGenerator *code_gen, CompilerContext *context,
                         ASTNode *node) {
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
            generate_parameters(code_gen, context, param->parameters);
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

void generate_type(CodeGenerator *code_gen, CompilerContext *context,
                   ASTNode *node) {
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
      generate_record(code_gen, context, node);
      break;
    } else if (s_node->type->type == NODE_SET_TYPE) {
      fprintf(code_gen->output_file, "typedef unsigned long long %s;\n",
              resolve_type_identifier(type_node->identifier));
    } else if (s_node->type->type == NODE_ARRAY_TYPE) {
      fprintf(code_gen->output_file, "typedef ");
      generate_array(code_gen, context, node, true);
      break;
    } else if (s_node->type->type == NODE_FILE_TYPE) {
      fprintf(code_gen->output_file, "// generate file\n");
      break;
    }
    break;
  }
  case NODE_POINTER_TYPE:
  default:
    LOG_ERROR("[DEBUG - generate type] %s node type\n",
              get_node_type_name(type_node->type_expr->type));
    break;
  }
}

void generate_record(CodeGenerator *code_gen, CompilerContext *context,
                     ASTNode *node) {
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

void generate_array(CodeGenerator *code_gen, CompilerContext *context,
                    ASTNode *node, bool disable_initialization) {
  TypeDeclarationNode *t_node = (TypeDeclarationNode *)node;
  StructuredTypeNode *s_node = (StructuredTypeNode *)t_node->type_expr;
  ArrayTypeNode *a_node = (ArrayTypeNode *)s_node->type;

  // type
  const char *element_type = calloc(1, sizeof(char));
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
      ConstantValue lower = evaluate_constant(context, sr_node->lower);
      // upper -> constants
      ConstantValue upper = evaluate_constant(context, sr_node->upper);
      array_size = upper.value.int_val - lower.value.int_val + 1;
    } else if (element->type == NODE_ENUMERATED_TYPE) {
      // TODO:
    } else if (element->type == NODE_TYPE_IDENTIFIER) {
      // TODO:
    } else {
      LOG_ERROR("era pra quebrar? %s", get_node_type_name(element->type));
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

void generate_assignment(CodeGenerator *code_gen, CompilerContext *context,
                         ASTNode *node) {
  AssignmentNode *a = (AssignmentNode *)node;

  IdentifierNode *target_id = NULL;
  if (a->target->type == NODE_IDENTIFIER) {
    target_id = (IdentifierNode *)a->target;
  } else if (a->target->type == NODE_MEMBER_ACCESS) {
    // Para p.name, o alvo final é 'name', mas o tipo vem de 'p'
    // A lógica de tipo aqui pode ficar complexa, vamos simplificar por agora
  }

  // Se for um tipo que precisa de cópia profunda (record/string), use memcpy
  bool is_struct_assignment = false;
  if (target_id && target_id->symbol) {
    // Aqui você precisaria de uma função que analisa o tipo do símbolo
    // e retorna se é um record ou sua string.
    // if (is_record_type(target_id->symbol->info.var_info.type)) {
    //     is_struct_assignment = true;
    // }
  }

  if (is_struct_assignment) {
    fprintf(code_gen->output_file, "memcpy(&");
    generate_expression(code_gen, context, a->target); // Gera p->name
    fprintf(code_gen->output_file, ", &");
    generate_expression(code_gen, context, a->expression); // Gera name
    fprintf(code_gen->output_file, ", sizeof(");
    generate_expression(code_gen, context,
                        a->target); // Gera o tipo para o sizeof
    fprintf(code_gen->output_file, "));\n");
  } else {
    generate_expression(code_gen, context, a->target);
    fprintf(code_gen->output_file, " = ");
    generate_expression(code_gen, context, a->expression);
    fprintf(code_gen->output_file, ";\n");
  }
}

void generate_if_statement(CodeGenerator *code_gen, CompilerContext *context,
                           ASTNode *node) {
  IfNode *if_stmt = (IfNode *)node;
  fprintf(code_gen->output_file, "if(");
  generate_expression(code_gen, context, if_stmt->condition);
  fprintf(code_gen->output_file, ") {\n");
  code_gen->indent_level++;
  generate_statement(code_gen, context, if_stmt->then_stmt);
  code_gen->indent_level--;
  if (if_stmt->else_stmt != NULL) {
    fprintf(code_gen->output_file, "} else {\n");
    code_gen->indent_level++;
    generate_statement(code_gen, context, if_stmt->else_stmt);
    code_gen->indent_level--;
    fprintf(code_gen->output_file, "}\n");
  } else {
    if (code_gen->indent_level > 0) {
      print_indent(code_gen);
    }
    fprintf(code_gen->output_file, "}\n");
  }
}

void generate_while_statement(CodeGenerator *code_gen, CompilerContext *context,
                              ASTNode *node) {}

void generate_for_statement(CodeGenerator *code_gen, CompilerContext *context,
                            ASTNode *node) {
  ForStmtNode *for_stmt = (ForStmtNode *)node;
  IdentifierNode *id = (IdentifierNode *)for_stmt->variable;

  fprintf(code_gen->output_file, "for (%s = ", id->name);
  generate_expression(code_gen, context,
                      for_stmt->start_expr); // Gera o valor inicial

  if (for_stmt->is_downto) {
    generate_expression(code_gen, context, for_stmt->end_expr);
    fprintf(code_gen->output_file, "; %s--)", id->name); // Decremento
  } else {
    // Lógica para TO
    fprintf(code_gen->output_file, "; %s <= ", id->name); // Condição com <=
    generate_expression(code_gen, context, for_stmt->end_expr);
    fprintf(code_gen->output_file, "; %s++)", id->name); // Incremento
  }

  fprintf(code_gen->output_file, " {\n");

  code_gen->indent_level++;
  generate_statement(code_gen, context, for_stmt->body);
  code_gen->indent_level--;

  print_indent(code_gen);
  fprintf(code_gen->output_file, "}\n");
}

void generate_repeat_until_statement(CodeGenerator *code_gen,
                                     CompilerContext *context, ASTNode *node) {}

void generate_list(CodeGenerator *code_gen, CompilerContext *context,
                   ASTNode *node) {
  ListNode *list = (ListNode *)node;

  while (list) {
    if (list->element) {
      // TODO: generate anything
    }

    list = (ListNode *)list->next;
  }
}

void generate_write(CodeGenerator *code_gen, CompilerContext *context,
                    ASTNode *node, bool line) {
  fprintf(code_gen->output_file, "printf(\"");

  FunctionCallNode *proc = (FunctionCallNode *)node;
  ListNode *params = (ListNode *)proc->params;

  while (params) {
    if (params->element) {
      switch (params->element->type) {
      case NODE_LITERAL: {
        LiteralNode *literal = (LiteralNode *)params->element;
        if (literal->literal_type == LITERAL_INTEGER) {
          fprintf(code_gen->output_file, "%d", literal->value.int_val);
        } else if (literal->literal_type == LITERAL_REAL) {
          fprintf(code_gen->output_file, "%.2f", literal->value.real_val);
        } else if (literal->literal_type == LITERAL_BOOLEAN) {
          fprintf(code_gen->output_file, "%s",
                  literal->value.bool_val ? "true" : "false");
        } else if (literal->literal_type == LITERAL_STRING) {
          fprintf(code_gen->output_file, "%s", literal->value.str_val);
        } else if (literal->literal_type == LITERAL_CHAR) {
          fprintf(code_gen->output_file, "%c", // : "'%c' %% 64",
                  literal->value.char_val);
        }
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
          SymbolEntry *id_sym = id->symbol;
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
        LOG_ERROR("[DEBUG writeln] -> %s not mapped",
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
      generate_expression(code_gen, context, curr->element);
    }
    curr = (ListNode *)curr->next;
    if (curr && curr->element->type != NODE_LITERAL)
      fprintf(code_gen->output_file, ", ");
  }

  fprintf(code_gen->output_file, ")");
}

void generate_read(CodeGenerator *code_gen, CompilerContext *context,
                   ASTNode *node, bool line) {
  fprintf(code_gen->output_file, "scanf(");
  generate_expression(code_gen, context, node);
  fprintf(code_gen->output_file, line ? "\\n\")" : "\")");
}

void generate_proc_call_statement(CodeGenerator *code_gen,
                                  CompilerContext *context, ASTNode *node) {
  FunctionCallNode *f_call = (FunctionCallNode *)node;
  IdentifierNode *id = (IdentifierNode *)f_call->function;
  SymbolEntry *s = context_lookup(context, id->name);

  if (s->kind == SYMBOL_BUILTIN) {
    if (strcmp(id->name, "write") == 0) {
      generate_write(code_gen, context, node, false);
      return;
    } else if (strcmp(id->name, "writeln") == 0) {
      generate_write(code_gen, context, node, true);
      return;
    } else if (strcmp(id->name, "read") == 0) {
      generate_write(code_gen, context, node, false);
      return;
    } else if (strcmp(id->name, "readln") == 0) {
      generate_write(code_gen, context, node, true);
      return;
    }
  } else {
    fprintf(code_gen->output_file, "%s(", id->name);
  }

  int var_params[255] = {0};
  int index = 0;

  if (s && s->info.func_info.params != NULL &&
      s->info.func_info.params->type == NODE_PARAMETER) {
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

  ListNode *params = (ListNode *)((FunctionCallNode *)node)->params;

  index = 0;
  while (params) {
    if (params->element) {
      if (params->element->type == NODE_LITERAL &&
          ((LiteralNode *)params->element)->literal_type == LITERAL_STRING) {
        LiteralNode *l = (LiteralNode *)params->element;
        fprintf(code_gen->output_file, "make_string(\"%s\")", l->value.str_val);
      } else {
        if (var_params[index] == 1)
          fprintf(code_gen->output_file, "&");
        generate_expression(code_gen, context, params->element);
      }
    }

    params = (ListNode *)params->next;
    index++;
    if (params)
      fprintf(code_gen->output_file, ", ");
  }

  fprintf(code_gen->output_file, ")");
}

void generate_statement(CodeGenerator *code_gen, CompilerContext *context,
                        ASTNode *node) {
  if (code_gen->indent_level > 0) {
    print_indent(code_gen);
  }
  switch (node->type) {
  case NODE_ASSIGN_STMT: {
    generate_assignment(code_gen, context, node);
    break;
  }
  case NODE_LIST:
    generate_list(code_gen, context, node);
    break;
  case NODE_IF_STMT:
    generate_if_statement(code_gen, context, node);
    break;
  case NODE_CASE_STMT:
    fprintf(code_gen->output_file, "/* case or case else */\n");
    break;
  case NODE_WHILE_STMT:
    generate_while_statement(code_gen, context, node);
    break;
  case NODE_REPEAT_STMT:
    generate_repeat_until_statement(code_gen, context, node);
    break;
  case NODE_FOR_STMT:
    generate_for_statement(code_gen, context, node);
    break;
  case NODE_IDENTIFIER:
    generate_expression(code_gen, context, node);
    break;
  case NODE_FUNC_CALL:
  case NODE_PROC_CALL:
    generate_proc_call_statement(code_gen, context, node);
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

void generate_expression(CodeGenerator *code_gen, CompilerContext *context,
                         ASTNode *node) {
  if (!node)
    return;

  switch (node->type) {
  case NODE_IDENTIFIER: {
    IdentifierNode *id = (IdentifierNode *)node;
    fprintf(code_gen->output_file, "%s", id->name);
    break;
  }
  case NODE_BINARY_EXPR: {
    BinaryOperationNode *bin_op = (BinaryOperationNode *)node;
    if (bin_op->op == BINOP_IN) {
      fprintf(code_gen->output_file, "((");
      generate_expression(code_gen, context, bin_op->right);
      fprintf(code_gen->output_file, " & (1ULL << (");
      generate_expression(code_gen, context, bin_op->left);
      fprintf(code_gen->output_file, " %% 64))) != 0");
      fprintf(code_gen->output_file, ")");
    } else {
      fprintf(code_gen->output_file, "(");
      generate_expression(code_gen, context, bin_op->left);
      fprintf(code_gen->output_file, " %s ", binary_op_to_string(bin_op->op));
      generate_expression(code_gen, context, bin_op->right);
      fprintf(code_gen->output_file, ")");
    }
    break;
  }
  case NODE_UNARY_EXPR: {
    UnaryOperationNode *u_node = (UnaryOperationNode *)node;
    fprintf(code_gen->output_file, "%s", unary_op_to_string(u_node->op));
    generate_expression(code_gen, context, u_node->operand);
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
                    "\"%s\" %% 64", //: "make_string(\"%s\") %% 64",
                    literal->value.str_val);
          } else if (literal->literal_type == LITERAL_CHAR) {
            fprintf(code_gen->output_file, "'%c' %% 64", // : "'%c' %% 64",
                    literal->value.char_val);
          }
          fprintf(code_gen->output_file, ")");
        } else if (se->type == SET_ELEMENT_RANGE) {
          LOG_ERROR("[DEBUG generate expression] - SET LITERAL -> elements %d "
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
    generate_proc_call_statement(code_gen, context, node);
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
      fprintf(code_gen->output_file, "\"%s\"", // : "make_string(\"%s\")",
              literal->value.str_val);
    } else if (literal->literal_type == LITERAL_CHAR) {
      fprintf(code_gen->output_file, "'%c'", // : "'%c'",
              literal->value.char_val);
    }

    break;
  }
  case NODE_ARRAY_ACCESS: {
    ArrayAccessNode *a_node = (ArrayAccessNode *)node;
    IdentifierNode *array_id = (IdentifierNode *)a_node->array;
    SymbolEntry *array_symbol = array_id->symbol;

    if (!array_symbol) {
      LOG_ERROR("The array symbol doenst exists");
    }

    generate_expression(code_gen, context, a_node->array);

    ListNode *subscript_expr_list = (ListNode *)a_node->subscript_list;
    int dimension_index = 0;

    while (subscript_expr_list) {
      int lower_bound =
          array_symbol->info.var_info.dimensions[dimension_index].lower;

      fprintf(code_gen->output_file, "[");

      generate_expression(code_gen, context, subscript_expr_list->element);

      if (lower_bound > 0) {
        fprintf(code_gen->output_file, " - %d", lower_bound);
      } else if (lower_bound < 0) {
        fprintf(code_gen->output_file, " + %d", -lower_bound);
      }

      fprintf(code_gen->output_file, "]");

      dimension_index++;
      subscript_expr_list = (ListNode *)subscript_expr_list->next;
    }
    break;
  }
  case NODE_MEMBER_ACCESS: {
    MemberAccessNode *m_node = (MemberAccessNode *)node;
    LOG_ERROR("\t[NODE_MEMBER_ACCESS]  %s - identifider: %s\n\n",
              get_node_type_name(m_node->record->type),
              resolve_identifier(m_node->field));
    if (m_node->record->type == NODE_IDENTIFIER) {

      IdentifierNode *record_id = (IdentifierNode *)m_node->record;

      SymbolEntry *record_symbol = record_id->symbol;

      generate_expression(code_gen, context, m_node->record);

      if (record_symbol != NULL && record_symbol->info.var_info.is_ref) {
        fprintf(code_gen->output_file, "->");
      } else {
        fprintf(code_gen->output_file, ".");
      }
    } else if (m_node->record->type == NODE_MEMBER_ACCESS) {
      MemberAccessNode *m = (MemberAccessNode *)m_node->record;
      IdentifierNode *id = (IdentifierNode *)m->record;

      generate_expression(code_gen, context, m_node->record);
      SymbolEntry *record_symbol = id->symbol;

      if (record_symbol != NULL && record_symbol->info.var_info.is_ref) {
        fprintf(code_gen->output_file, "->");
      } else {
        fprintf(code_gen->output_file, ".");
      }
    } else if (m_node->record->type == NODE_ARRAY_ACCESS) {
      ArrayAccessNode *arr = (ArrayAccessNode *)m_node->record;
      IdentifierNode *id = (IdentifierNode *)arr->array;

      SymbolEntry *record_symbol = id->symbol;
      // LOG_ERROR("Tem symbol aqui será? %p, %s - %s\n", (void* )record_symbol,get_node_type_name(arr->array->type),resolve_identifier(m_node->field));

      generate_expression(code_gen, context, m_node->record);

      if (record_symbol != NULL && record_symbol->info.var_info.is_ref) {
        fprintf(code_gen->output_file, "->");
      } else {
        fprintf(code_gen->output_file, ".");
      }
    }
    generate_expression(code_gen, context, m_node->field);
    break;
  }
  case NODE_POINTER_DEREF: {
    break;
  }
  case NODE_SET_ELEMENT: {
    break;
  }
  default:
    LOG_ERROR(
        "[DEBUG resolve expression] -> NODE NOT MAPPED - node type name %s\n",
        get_node_type_name(node->type));
    break;
  }
}
