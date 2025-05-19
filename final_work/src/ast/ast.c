#include "ast.h"
#include <string.h>

SourceLocation create_location(YYLTYPE loc) {
  SourceLocation result;
  result.first_line = loc.first_line;
  result.first_column = loc.first_column;
  result.last_line = loc.last_line;
  result.last_column = loc.last_column;
  result.file_name = strdup(yylloc.file_name);
  return result;
}

void print_program_node(ASTNode *node, int indent) {
  ProgramNode *prog = (ProgramNode *)node;
  printf("%*sProgram: %s - at: %d.%d-%d.%d [%s]\n", indent, "", prog->name,
         prog->base.location.first_line, prog->base.location.first_column,
         prog->base.location.last_line, prog->base.location.last_column,
         prog->base.location.file_name);
  if (prog->heading != NULL) {
    prog->heading->print(prog->heading, indent += 2);
  }
  if (prog->block != NULL) {
    prog->block->print(prog->block, indent += 2);
  }
}

void print_heading(ASTNode *node, int indent) {
  HeadingNode *h = (HeadingNode *)node;
  printf("%*sHeading parameters: (", indent, "");
  ListNode *current = (ListNode *)h->list;
  int first = 1;

  while (current) {
    if (current->element) {
      LiteralNode *lit = (LiteralNode *)current->element;
      if (!first)
        printf(", ");
      printf("%s", lit->value.string);
      first = 0;
    } else {
      printf("[NULL]");
    }
    current = (ListNode *)current->next;
  }
  printf(")\n");
}

void print_block(ASTNode *node, int indent) {
  BlockNode *block = (BlockNode *)node;
  printf("%*sBlock: %d\n", indent, "", block->base.type);

  if (block->labels != NULL) {
    printf("%*sLabels: \n", indent + 2, "");
  }
  if (block->types != NULL) {
    printf("%*sTypes: \n", indent + 2, "");
  }
  if (block->constants != NULL) {
    printf("%*sConstants: \n", indent + 2, "");
  }
  if (block->variables != NULL) {
    printf("%*sVariables: \n", indent + 2, "");
  }
  if (block->procs_funcs != NULL) {
    printf("%*sProcedures e Functions: \n", indent + 2, "");
  }
  if (block->statements != NULL) {
    printf("%*sStatements: \n", indent + 2, "");
  }
}

// void print_binary_expr_node(ASTNode *node, int indent) {
//   BinaryOperationNode *expr = (BinaryOperationNode *)node;
//   printf("%*sBinary Expression (op: %d)\n", indent, "", expr->operator);
//   if (expr->left) {
//     expr->left->print(expr->left, indent + 2);
//   }
//   if (expr->right) {
//     expr->right->print(expr->right, indent + 2);
//   }
// }

ASTNode *create_program_node(char *name, ASTNode *heading, ASTNode *block,
                             SourceLocation loc) {
  ProgramNode *node = (ProgramNode *)malloc(sizeof(ProgramNode));
  node->base.type = NODE_PROGRAM;
  node->base.location = loc;
  node->base.print = print_program_node;
  node->name = strdup(name);
  node->block = block;
  node->heading = heading;
  return (ASTNode *)node;
}

ASTNode *create_block_node(ASTNode *labels, ASTNode *constants, ASTNode *types,
                           ASTNode *variables, ASTNode *procs_funcs,
                           ASTNode *statements, SourceLocation loc) {
  BlockNode *node = (BlockNode *)malloc(sizeof(BlockNode));
  node->base.type = NODE_BLOCK;
  node->base.location = loc;
  node->base.print = print_block;
  node->labels = labels;
  node->types = types;
  node->constants = constants;
  node->variables = variables;
  node->procs_funcs = procs_funcs;
  node->statements = statements;
  return (ASTNode *)node;
}

ASTNode *create_heading_node(ASTNode *list, SourceLocation loc) {
  HeadingNode *node = (HeadingNode *)malloc(sizeof(HeadingNode));
  node->base.type = NODE_HEADING;
  node->base.location = loc;
  node->base.print = print_heading;
  node->list = list;
  return (ASTNode *)node;
}

ASTNode *create_label_declaration_node(ASTNode *value, SourceLocation loc) {
  LabelDeclarationNode *node =
      (LabelDeclarationNode *)malloc(sizeof(LabelDeclarationNode));
  node->base.type = NODE_LABEL_DECL;
  node->base.location = loc;
  node->base.print = print_todo;

  ListNode *label = (ListNode *)malloc(sizeof(ListNode));
  label->base.type = NODE_LIST;
  label->base.location = loc;
  label->base.print = print_todo;
  label->element = value;
  label->next = NULL;

  node->labels = (ASTNode *)label;
  return (ASTNode *)node;
}

ASTNode *create_constant_declaration_node(ASTNode *id, ASTNode *constant,
                                          SourceLocation loc) {
  ConstDeclarationNode *node =
      (ConstDeclarationNode *)malloc(sizeof(ConstDeclarationNode));
  node->base.type = NODE_CONST_DECL;
  node->base.location = loc;
  node->base.print = print_todo;

  ConstItemNode *item = (ConstItemNode *)malloc(sizeof(ConstItemNode));
  item->base.type = NODE_CONST_ITEM;
  item->base.location = loc;
  item->base.print = print_todo;
  item->name = strdup(((LiteralNode *)id)->value.string);
  item->value = constant;

  ListNode *list = (ListNode *)malloc(sizeof(ListNode));
  list->base.type = NODE_LIST;
  list->base.location = loc;
  list->base.print = print_todo;
  list->element = (ASTNode *)item;
  list->next = NULL;

  node->constants = (ASTNode *)list;
  return (ASTNode *)node;
}

ASTNode *create_type_declaration_node(ASTNode *id, ASTNode *constant,
                                      SourceLocation loc) {
  ConstDeclarationNode *node =
      (ConstDeclarationNode *)malloc(sizeof(ConstDeclarationNode));
  node->base.type = NODE_CONST_DECL;
  node->base.location = loc;
  node->base.print = print_todo;

  ConstItemNode *item = (ConstItemNode *)malloc(sizeof(ConstItemNode));
  item->base.type = NODE_CONST_ITEM;
  item->base.location = loc;
  item->base.print = print_todo;
  item->name = strdup(((LiteralNode *)id)->value.string);
  item->value = constant;

  ListNode *list = (ListNode *)malloc(sizeof(ListNode));
  list->base.type = NODE_LIST;
  list->base.location = loc;
  list->base.print = print_todo;
  list->element = (ASTNode *)item;
  list->next = NULL;

  node->constants = (ASTNode *)list;
  return (ASTNode *)node;
}

ASTNode *create_identifier_list_node(ASTNode *element, SourceLocation loc) {
  ListNode *node = (ListNode *)malloc(sizeof(ListNode));
  node->base.type = NODE_LIST;
  node->base.location = loc;
  node->base.print = print_todo;
  node->element = element;
  node->next = NULL;
  return (ASTNode *)node;
}

ASTNode *create_case_stmt_node(ASTNode *expr, ASTNode *elements,
                               ASTNode *else_part, SourceLocation loc) {
  CaseNode *node = (CaseNode *)malloc(sizeof(CaseNode));
  node->base.type = NODE_CASE_STMT;
  node->base.location = loc;
  node->base.print = print_todo;
  node->expr = expr;
  node->elements = elements;
  node->else_part = else_part;
  return (ASTNode *)node;
}

ASTNode *create_case_list_node(ASTNode *element, SourceLocation loc) {
  ListNode *list = (ListNode *)malloc(sizeof(ListNode));
  list->base.type = NODE_LIST;
  list->base.location = loc;
  list->base.print = print_todo;
  list->element = element;
  list->next = NULL;
  return (ASTNode *)list;
}

ASTNode *create_case_element_node(ASTNode *label, ASTNode *stmt,
                                  SourceLocation loc) {
  CaseLabelNode *node = (CaseLabelNode *)malloc(sizeof(CaseLabelNode));
  node->base.type = NODE_CASE_ELEMENT;
  node->base.location = loc;
  node->base.print = print_todo;
  node->label = label;
  node->stmt = stmt;
  return (ASTNode *)node;
}

ASTNode *create_case_else_node(ASTNode *stmt, SourceLocation loc) {
  CaseElseNode *node = (CaseElseNode *)malloc(sizeof(CaseElseNode));
  node->base.type = NODE_CASE_ELSE;
  node->base.location = loc;
  node->base.print = print_todo;
  node->stmt = stmt;
  return (ASTNode *)node;
}

ASTNode *create_array_access_node(ASTNode *array, ASTNode *subscripts,
                                  SourceLocation loc) {
  ArrayAccessNode *node = (ArrayAccessNode *)malloc(sizeof(ArrayAccessNode));
  node->base.type = NODE_ARRAY_ACCESS;
  node->base.location = loc;
  node->base.print = print_todo;
  node->array = array;
  node->subscript_list = subscripts;
  return (ASTNode *)node;
}

ASTNode *create_record_access_node(ASTNode *record, ASTNode *field,
                                   SourceLocation loc) {
  MemberAccessNode *node = (MemberAccessNode *)malloc(sizeof(MemberAccessNode));
  node->base.type = NODE_MEMBER_ACCESS;
  node->base.location = loc;
  node->base.print = print_todo;
  node->record = record;
  node->field = field;
  return (ASTNode *)node;
}

ASTNode *create_pointer_deref_node(ASTNode *pointer, SourceLocation loc) {
  PointerDerefNode *node = (PointerDerefNode *)malloc(sizeof(PointerDerefNode));
  node->base.type = NODE_POINTER_DEREF;
  node->base.location = loc;
  node->base.print = print_todo;
  node->pointer = pointer;
  return (ASTNode *)node;
}

ASTNode *create_subscript_list_node(ASTNode *expr, SourceLocation loc) {
  ListNode *node = (ListNode *)malloc(sizeof(ListNode));
  node->base.type = NODE_LIST;
  node->base.location = loc;
  node->base.print = print_todo;
  node->element = expr;
  node->next = NULL;
  return (ASTNode *)node;
}

ASTNode *create_proc_and_func_declaration_node(ASTNode *id,
                                               ASTNode *procs_funcs,
                                               SourceLocation loc) {};
ASTNode *create_array_type_node(ASTNode *list, ASTNode *type,
                                SourceLocation loc) {};
ASTNode *create_assign_node(ASTNode *variable, ASTNode *expression,
                            SourceLocation loc) {};
ASTNode *create_case_of_variant_node(ASTNode *tag_field, ASTNode *variant_list,
                                     SourceLocation loc) {};
ASTNode *create_case_stmt_with_else_node(ASTNode *expression, ASTNode *list,
                                         ASTNode *else_part,
                                         SourceLocation loc) {};
ASTNode *create_constant_identifier(ASTNode *identifier, SourceLocation loc) {};
ASTNode *create_constant_literal(ASTNode *literalValue, SourceLocation loc) {};
ASTNode *create_integer_literal(int integer, SourceLocation loc) {
  LiteralNode *node = (LiteralNode *)malloc(sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_todo;
  node->value.integer = integer;
  return (ASTNode *)node;
};
ASTNode *create_real_literal(double real, SourceLocation loc) {
  LiteralNode *node = (LiteralNode *)malloc(sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_todo;
  node->value.real = real;
  return (ASTNode *)node;
};
ASTNode *create_string_literal(char *string, SourceLocation loc) {
  LiteralNode *node = (LiteralNode *)malloc(sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_todo;
  node->value.string = string;
  return (ASTNode *)node;
};
ASTNode *create_char_literal(char character, SourceLocation loc) {
  LiteralNode *node = (LiteralNode *)malloc(sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_todo;
  node->value.character = character;
  return (ASTNode *)node;
};
ASTNode *create_boolean_literal(bool boolean, SourceLocation loc) {
  LiteralNode *node = (LiteralNode *)malloc(sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_todo;
  node->value.boolean = boolean;
  return (ASTNode *)node;
};
ASTNode *create_constant_signed_identifier(ASTNode *value, char *op,
                                           SourceLocation loc) {};
ASTNode *create_field_identifier_list_node(ASTNode *list, ASTNode *identifier,
                                           SourceLocation loc) {};
ASTNode *create_file_of_type_node(ASTNode *type, SourceLocation loc) {};
ASTNode *create_field_list(ASTNode *fixed, ASTNode *variant,
                           SourceLocation loc) {};
ASTNode *create_fixed_part_node(ASTNode *fixed, ASTNode *field,
                                SourceLocation loc) {};
ASTNode *create_for_stmt_node(ASTNode *variable, ASTNode *for_list,
                              ASTNode *stmt, SourceLocation loc) {};
ASTNode *create_formal_parameters_list_node(ASTNode *list, ASTNode *param,
                                            SourceLocation loc) {};
ASTNode *create_function_param_node(ASTNode *identifier, ASTNode *params,
                                    ASTNode *type, SourceLocation loc) {};
ASTNode *create_goto_label_node(ASTNode *label, SourceLocation loc) {};
ASTNode *create_if_stmt_node(ASTNode *expression, ASTNode *then_part,
                             ASTNode *else_part, SourceLocation loc) {};
ASTNode *create_index_list_node(ASTNode *list, ASTNode *type,
                                SourceLocation loc) {};
ASTNode *create_label_stmt_node(ASTNode *label, ASTNode *stmt,
                                SourceLocation loc) {};
ASTNode *create_packed_type(ASTNode *type, SourceLocation loc) {};
ASTNode *create_parameter_identifier_list_node(ASTNode *list, ASTNode *element,
                                               SourceLocation loc) {};
ASTNode *create_parameter_list_types_node(ASTNode *list, ASTNode *type,
                                          SourceLocation loc) {};
ASTNode *create_parameters_node(ASTNode *parameter, SourceLocation loc) {};
ASTNode *create_poniter_type_node(ASTNode *type, SourceLocation loc) {};
ASTNode *create_procedure_call_node(ASTNode *identifier, ASTNode *expr_list,
                                    SourceLocation loc) {};
ASTNode *create_procedure_param_node(ASTNode *identifier, ASTNode *params,
                                     SourceLocation loc) {};
ASTNode *create_record_access_type(ASTNode *identifier, ASTNode *field,
                                   SourceLocation loc) {};
ASTNode *create_record_field_node(ASTNode *field_list, ASTNode *type,
                                  SourceLocation loc) {};
ASTNode *create_record_type_node(ASTNode *field_list, SourceLocation loc) {};
ASTNode *create_repeat_until_stmt_list_node(ASTNode *list, ASTNode *expression,
                                            SourceLocation loc) {};
ASTNode *create_set_of_type_node(ASTNode *type, SourceLocation loc) {};
ASTNode *create_simple_type_node(ASTNode *type, SourceLocation loc) {};
ASTNode *create_stmt_list_node(ASTNode *stmt_list, SourceLocation loc) {};
ASTNode *create_structure_type_node(ASTNode *type, SourceLocation loc) {};
ASTNode *create_tag_field_node(ASTNode *identifier, ASTNode *type,
                               SourceLocation loc) {};
ASTNode *create_type_identifier(ASTNode *identifier, SourceLocation loc) {};
ASTNode *create_variable_declaration_node(ASTNode *list, ASTNode *type,
                                          SourceLocation loc) {};
ASTNode *create_variant_node(ASTNode *label_list, ASTNode *field_list,
                             SourceLocation loc) {};
ASTNode *create_while_stmt_node(ASTNode *expr, ASTNode *stmt,
                                SourceLocation loc) {};
ASTNode *create_with_record_list_node(ASTNode *record_var_list, ASTNode *stmt,
                                      SourceLocation loc) {};

ASTNode *create_identifier_node(char *id, SourceLocation loc) {
  LiteralNode *node = (LiteralNode *)malloc(sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_todo;
  node->value.string = strdup(id);
  return (ASTNode *)node;
}

ASTNode *create_unsigned_integer_node(int integer, SourceLocation loc) {
  LiteralNode *node = (LiteralNode *)malloc(sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_todo;
  node->value.integer = integer;
  return (ASTNode *)node;
}

ASTNode *create_unsigned_real_node(double real, SourceLocation loc) {
  LiteralNode *node = (LiteralNode *)malloc(sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_todo;
  node->value.real = real;
  return (ASTNode *)node;
}

/* APPENDS */
ASTNode *append_identifier_list_node(ASTNode *list, ASTNode *element,
                                     SourceLocation loc) {
  ListNode *head = (ListNode *)list;

  ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
  new_node->base.type = NODE_LIST;
  new_node->base.location = loc;
  new_node->base.print = print_todo;
  new_node->element = element;
  new_node->next = NULL;

  if (head) {
    ListNode *cur = head;
    while (cur->next)
      cur = (ListNode *)cur->next;
    cur->next = (ASTNode *)new_node;
    return (ASTNode *)head;
  } else {
    return (ASTNode *)new_node;
  }
}

ASTNode *append_label_declaration(ASTNode *label, ASTNode *element,
                                  SourceLocation loc) {
  LabelDeclarationNode *head = (LabelDeclarationNode *)label;

  ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
  new_node->base.type = NODE_LIST;
  new_node->base.location = loc;
  new_node->base.print = print_todo;
  new_node->element = element;
  new_node->next = NULL;

  if (head) {
    ListNode *cur = (ListNode *)head->labels;
    while (cur->next)
      cur = (ListNode *)cur->next;
    cur->next = (ASTNode *)new_node;
    return (ASTNode *)head;
  } else {
    LabelDeclarationNode *labelDecl =
        (LabelDeclarationNode *)malloc(sizeof(LabelDeclarationNode));
    labelDecl->base.type = NODE_LABEL_DECL;
    labelDecl->base.location = loc;
    labelDecl->base.print = print_todo;
    labelDecl->labels = (ASTNode *)new_node;
    return (ASTNode *)labelDecl;
  }
}

ASTNode *append_constant_declaration(ASTNode *decl, ASTNode *id,
                                     ASTNode *constant, SourceLocation loc) {
  ConstDeclarationNode *head = (ConstDeclarationNode *)decl;

  ConstItemNode *item = (ConstItemNode *)malloc(sizeof(ConstItemNode));
  item->base.type = NODE_CONST_ITEM;
  item->base.location = loc;
  item->base.print = print_todo;
  item->name = strdup(((LiteralNode *)id)->value.string);
  item->value = constant;

  ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
  new_node->base.type = NODE_LIST;
  new_node->base.location = loc;
  new_node->base.print = print_todo;
  new_node->element = (ASTNode *)item;
  new_node->next = NULL;

  if (head) {
    ListNode *cur = (ListNode *)head->constants;
    while (cur->next)
      cur = (ListNode *)cur->next;
    cur->next = (ASTNode *)new_node;
    return (ASTNode *)head;
  } else {
    ConstDeclarationNode *cDecl =
        (ConstDeclarationNode *)malloc(sizeof(ConstDeclarationNode));
    cDecl->base.type = NODE_LABEL_DECL;
    cDecl->base.location = loc;
    cDecl->base.print = print_todo;
    cDecl->constants = (ASTNode *)new_node;
    return (ASTNode *)cDecl;
  }
}

ASTNode *append_type_declaration(ASTNode *decl, ASTNode *id, ASTNode *type,
                                 SourceLocation loc) {
  TypeDeclarationNode *head = (TypeDeclarationNode *)decl;

  TypeItemNode *item = (TypeItemNode *)malloc(sizeof(TypeItemNode));
  item->base.type = NODE_SCALAR_TYPE; // TODO DEFINITION OF SIMPLES/STRUCTURED/;
  item->base.location = loc;
  item->base.print = print_todo;
  item->name = strdup(((LiteralNode *)id)->value.string);
  item->value = type;

  ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
  new_node->base.type = NODE_LIST;
  new_node->base.location = loc;
  new_node->base.print = print_todo;
  new_node->element = (ASTNode *)item;
  new_node->next = NULL;

  if (head) {
    ListNode *cur = (ListNode *)head->types;
    while (cur->next)
      cur = (ListNode *)cur->next;
    cur->next = (ASTNode *)new_node;
    return (ASTNode *)head;
  } else {
    TypeDeclarationNode *cDecl =
        (TypeDeclarationNode *)malloc(sizeof(TypeDeclarationNode));
    cDecl->base.type = NODE_LABEL_DECL;
    cDecl->base.location = loc;
    cDecl->base.print = print_todo;
    cDecl->types = (ASTNode *)new_node;
    return (ASTNode *)cDecl;
  }
}

ASTNode *append_subscript_list_node(ASTNode *list, ASTNode *expr,
                                    SourceLocation loc) {
  ListNode *head = (ListNode *)list;

  ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
  new_node->base.type = NODE_LIST;
  new_node->base.location = loc;
  new_node->base.print = print_todo;
  new_node->element = expr;
  new_node->next = NULL;

  if (head) {
    ListNode *cur = head;
    while (cur->next)
      cur = (ListNode *)cur->next;
    cur->next = (ASTNode *)new_node;
    return (ASTNode *)head;
  } else {
    return (ASTNode *)new_node;
  }
}

ASTNode *append_case_list_node(ASTNode *list, ASTNode *expr,
                               SourceLocation loc) {
  ListNode *head = (ListNode *)list;

  ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
  new_node->base.type = NODE_LIST;
  new_node->base.location = loc;
  new_node->base.print = print_todo;
  new_node->element = expr;
  new_node->next = NULL;

  if (head) {
    ListNode *cur = head;
    while (cur->next)
      cur = (ListNode *)cur->next;
    cur->next = (ASTNode *)new_node;
    return (ASTNode *)head;
  } else {
    return (ASTNode *)new_node;
  }
}

ASTNode *append_variable_declaration(ASTNode *list, ASTNode *id, ASTNode *vars,
                                     SourceLocation loc) {}
ASTNode *append_variable_identifiers_list(ASTNode *list, ASTNode *var_id,
                                          SourceLocation loc) {}
ASTNode *append_variant_list(ASTNode *list, ASTNode *element,
                             SourceLocation loc) {}
ASTNode *append_stmt_list(ASTNode *list, ASTNode *stmt, SourceLocation loc) {}

ASTNode *add_constant_to_block(ASTNode *block, ASTNode *constants) {
  if (!block)
    return NULL;
  BlockNode *block_node = (BlockNode *)block;
  block_node->constants = constants;
  return (ASTNode *)block_node;
}

ASTNode *add_type_to_block(ASTNode *block, ASTNode *types) {
  if (!block)
    return NULL;
  BlockNode *block_node = (BlockNode *)block;
  block_node->types = types;
  return (ASTNode *)block_node;
}

ASTNode *add_variable_to_block(ASTNode *block, ASTNode *variables) {
  if (!block)
    return NULL;
  BlockNode *block_node = (BlockNode *)block;
  block_node->variables = variables;
  return (ASTNode *)block_node;
}

ASTNode *add_proc_func_to_block(ASTNode *block, ASTNode *procs_funcs) {
  if (!block)
    return NULL;
  BlockNode *block_node = (BlockNode *)block;
  block_node->procs_funcs = procs_funcs;
  return (ASTNode *)block_node;
}

/* UTILS */

ASTNode *get_statements_from_block(ASTNode *block) {
  if (!block)
    return NULL;
  return ((BlockNode *)block)->statements;
}

void print_todo(ASTNode *node, int indent) {
  printf("%*sTODO print element", indent, "");
}

void free_node(ASTNode *node) {
  if (!node)
    return;

  switch (node->type) {
  case NODE_PROGRAM: {
    ProgramNode *prog = (ProgramNode *)node;
    free(prog->name);
    free_node(prog->block);
    break;
  }
  case NODE_CASE_ELEMENT: {
    break;
  }
  case NODE_CASE_ELSE: {
    break;
  }
  case NODE_BINARY_EXPR: {
    // BinaryOperationNode *expr = (BinaryOperationNode *)node;
    // free_node(expr->left);
    // free_node(expr->right);
    break;
  }
  }

  free(node);
}
