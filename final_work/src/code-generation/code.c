#include "code.h"
#include "../symbol-table/symbol-table.h"

extern ht *HashTable;

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
  printf("[DEBUG - cast] node type -> %s : node kind -> %s - name:",
         get_node_type_name(node->base.type), get_symbol_kind_name(node->kind));
  switch (node->kind) {
  case SYMBOL_BUILTIN: {
    printf("%s\n", node->name);
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
    printf("void\n\n\n");
    return "void";
  }
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

void generate_program(CodeGenerator *code_gen, ASTNode *node) {
  ProgramNode *program = (ProgramNode *)node;

  fprintf(code_gen->output_file, "#include <stdio.h>\n");
  fprintf(code_gen->output_file, "#include <stdlib.h>\n");
  fprintf(code_gen->output_file, "#include <string.h>\n");
  fprintf(code_gen->output_file, "#include <stdbool.h>\n\n");

  /*
   struct ProgramNode {
    ASTNode base;
    char *name;
    ASTNode *block;
    ASTNode *heading;
  };

  struct HeadingNode {
    ASTNode base;
    ASTNode *list;
  };

  struct BlockNode {
    ASTNode base;
    ASTNode *labels;
    ASTNode *types;
    ASTNode *constants;
    ASTNode *variables;
    ASTNode *procs_funcs;
    ASTNode *statements;
  }
   */

  BlockNode *block = (BlockNode *)program->block;

  fprintf(code_gen->output_file, "typedef struct {\n");
  fprintf(code_gen->output_file, "    unsigned char length;\n");
  fprintf(code_gen->output_file, "    char data[255];\n");
  fprintf(code_gen->output_file, "} string;\n\n");

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

  fprintf(code_gen->output_file, "string make_string(const char* c_str) {\n");
  fprintf(code_gen->output_file, "    string ps;\n");
  fprintf(code_gen->output_file, "    ps.length = strlen(c_str);\n");
  fprintf(code_gen->output_file, "    if(ps.length > 255) ps.length = 255;\n");
  fprintf(code_gen->output_file, "    strncpy(ps.data, c_str, ps.length);\n");
  fprintf(code_gen->output_file, "    return ps;\n");
  fprintf(code_gen->output_file, "}\n\n");

  fprintf(code_gen->output_file,
          "string concat_string(string s1, string s2) {\n");
  fprintf(code_gen->output_file, "    string result;\n");
  fprintf(code_gen->output_file,
          "    result.length = s1.length + s2.length;\n");
  fprintf(code_gen->output_file,
          "    if(result.length > 255) result.length = 255;\n");
  fprintf(code_gen->output_file,
          "    memcpy(result.data, s1.data, s1.length);\n");
  fprintf(code_gen->output_file, "    memcpy(result.data + s1.length, s2.data, "
                                 "result.length - s1.length);\n");
  fprintf(code_gen->output_file, "    return result;\n");
  fprintf(code_gen->output_file, "}\n\n");

  ListNode *procs_funcs = (ListNode *)block->procs_funcs;
  while (procs_funcs) {
    if (procs_funcs->element) {
      generate_function(code_gen, procs_funcs->element);
    }

    procs_funcs = (ListNode *)procs_funcs->next;
  }

  fprintf(code_gen->output_file, "int main() {\n");
  code_gen->indent_level++;

  ListNode *statements = (ListNode *)block->statements;
  while (statements) {
    if (statements->element) {
      generate_statement(code_gen, statements->element);
    }

    statements = (ListNode *)statements->next;
  }

  print_indent(code_gen);
  fprintf(code_gen->output_file, "return 0;\n");
  code_gen->indent_level--;
  fprintf(code_gen->output_file, "}\n");
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
    PointerTypeNode *pt_node = (PointerTypeNode *)v_node->type_node;
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
    s = ht_get(HashTable, resolve_identifier(func->identifier));
    fprintf(code_gen->output_file, "%s %s(",
            resolve_type_identifier(func->type), s->name);
    block_or_forward = func->block_or_forward;
    params = func->parameters;
  } else {
    s = ht_get(HashTable, resolve_identifier(proc->identifier));
    fprintf(code_gen->output_file, "void %s(", s->name);
    block_or_forward = proc->block_or_forward;
    params = proc->parameters;
  }

  generate_parameters(code_gen, params);

  if (block_or_forward->type == NODE_FORWARD_DECL) {
    fprintf(code_gen->output_file, ");\n\n");
    free_node(params);
    free_node(block_or_forward);
    return;
  }

  fprintf(code_gen->output_file, "){\n");
  code_gen->indent_level++;
  generate_statement(code_gen, block_or_forward);
  code_gen->indent_level--;
  fprintf(code_gen->output_file, "}\n\n");

  free_node(params);
  free_node(block_or_forward);
}

void generate_parameters(CodeGenerator *code_gen, ASTNode *node) {
  ParameterNode *params = (ParameterNode *)node;
  ListNode *params_list = (ListNode *)params->params_list;

  while (params_list) {
    if (params_list->element) {
      FormalParameterSectionNode *param =
          (FormalParameterSectionNode *)params_list->element;
      ListNode *identifiers = (ListNode *)param->identifiers;
      while (identifiers) {
        if (identifiers->element) {
          if (param->kind == PARAM_VALUE) {
            fprintf(code_gen->output_file, "%s %s",
                    resolve_type_identifier(param->type),
                    resolve_identifier(identifiers->element));
          } else if (param->kind == PARAM_VAR) {
            fprintf(code_gen->output_file, "%s *%s",
                    resolve_type_identifier(param->type),
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
    }
    // TODO: add another simple type possibilities
    break;
  }
  case NODE_STRUCTURED_TYPE: {
    StructuredTypeNode *s_node = (StructuredTypeNode *)type_node->type_expr;
    if (s_node->type->type == NODE_RECORD_TYPE) {
      generate_record(code_gen, node);
      break;
    } else if (s_node->type->type == NODE_SET_TYPE) {
      SetTypeNode *set = (SetTypeNode *)s_node->type;
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

    } else if (element->type == NODE_TYPE_IDENTIFIER) {

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

void generate_statement(CodeGenerator *code_gen, ASTNode *node) {}
