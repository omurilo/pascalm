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
  switch (node->kind) {
  case SYMBOL_BUILTIN: {
    if (strcmp(node->name, "char") == 0)
      return "char";
    if (strcmp(node->name, "integer") == 0)
      return "int";
    if (strcmp(node->name, "real") == 0)
      return "double";
    if (strcmp(node->name, "boolean") == 0)
      return "bool";
    if (strcmp(node->name, "string") == 0)
      return "char *";
    return "void";
  }
  case SYMBOL_TYPE:
    return "struct";
  default:
    return "void";
  }
}

const char *resolve_identifier(ASTNode *node) {
  IdentifierNode *id_node = (IdentifierNode *)node;
  return id_node->name;
}

const char *resolve_type_identifier(ASTNode *node) {
  TypeIdentifierNode *type_node = (TypeIdentifierNode *)node;
  printf("[DEBUG] symbol type: %s - ", get_symbol_kind_name(type_node->kind));
  if (type_node->kind == SYMBOL_TYPE || type_node->kind == SYMBOL_UNKNOWN) {
    printf("%s\n", resolve_identifier((ASTNode*)type_node->id));
    return resolve_identifier((ASTNode *)type_node->id);
  }
  printf("%s\n", type_node->name);
  return cast_pascal_to_c_type(type_node);
}

void generate_program(CodeGenerator *code_gen, ASTNode *node) {
  ProgramNode *program = (ProgramNode *)node;

  fprintf(code_gen->output_file, "#include <stdio.h>\n");
  fprintf(code_gen->output_file, "#include <stdlib.h>\n");
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
  /* Types -> block->types */

  ListNode *procs_funcs = (ListNode *)block->procs_funcs;

  while (procs_funcs) {
    if (procs_funcs->element) {
      generate_function(code_gen, procs_funcs->element);
    }

    procs_funcs = (ListNode *)procs_funcs->next;
  }
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
  // TODO: generate code for block declaration -> use block_or_forward->
  // generate_block(code_gen, block_or_forward);
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
              fprintf(code_gen->output_file, "void %s(", resolve_identifier(identifiers->element));
            } else if (param->kind == PARAM_FUNCTION) {
              fprintf(code_gen->output_file, "%s %s(", resolve_type_identifier(param->return_type), resolve_identifier(identifiers->element));
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
