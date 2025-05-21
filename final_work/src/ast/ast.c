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
      IdentifierNode *id = (IdentifierNode *)current->element;
      if (!first)
        printf(", ");
      printf("%s", id->name);
      first = 0;
    } else {
      printf("[NULL]");
    }
    current = (ListNode *)current->next;
  }
  printf(")\n");
}

void print_list_identifiers(ASTNode *node, int indent) {
  ListNode *current = (ListNode *)node;

  while (current) {
    if (current->element) {
      IdentifierNode *id =
          (IdentifierNode *)((TypeDeclarationNode *)current->element)
              ->identifier;
      printf("%*s%s\n", indent, "", id->name);
    } else {
      printf("[NULL]\n");
    }
    current = (ListNode *)current->next;
  }
}

void print_list_values(ASTNode *node, int indent) {
  ListNode *current = (ListNode *)node;

  while (current) {
    if (current->element) {
      LiteralNode *lit =
          (LiteralNode *)((LabelDeclarationNode *)current->element)->value;
      if (lit->literal_type == LITERAL_STRING) {
        printf("%*s%s\n", indent, "", lit->value.str_val);
      } else if (lit->literal_type == LITERAL_INTEGER) {
        printf("%*s%d\n", indent, "", lit->value.int_val);
      } else if (lit->literal_type == LITERAL_REAL) {
        printf("%*s%.2f\n", indent, "", lit->value.real_val);
      } else if (lit->literal_type == LITERAL_BOOLEAN) {
        printf("%*s%s\n", indent, "", lit->value.bool_val ? "true" : "false");
      } else if (lit->literal_type == LITERAL_CHAR) {
        printf("%*s%c\n", indent, "", lit->value.char_val);
      }
    } else {
      printf("[NULL]\n");
    }
    current = (ListNode *)current->next;
  }
}

void print_variable_declaration(ASTNode *node, int indent) {
  ListNode *current = (ListNode *)node;

  while (current) {
    if (current->element) {
      VarDeclarationNode *v_decl = (VarDeclarationNode *)current->element;
      ListNode *new_curr = (ListNode *)v_decl->var_list;
      printf("%*s(", indent, "");
      int first = 1;
      while (new_curr) {
        if (new_curr->element) {
          IdentifierNode *id = (IdentifierNode *)new_curr->element;
          if (first > 1) {
            printf(", ");
          }
          printf("%s", id->name);
        } else {
          printf("[NULL]\n");
        }
        first += 1;
        new_curr = (ListNode *)new_curr->next;
      }
      printf(")\n");
    } else {
      printf("[NULL]\n");
    }
    current = (ListNode *)current->next;
  }
}

void print_block(ASTNode *node, int indent) {
  BlockNode *block = (BlockNode *)node;
  printf("%*sBlock:\n", indent, "");

  if (block->labels != NULL) {
    printf("%*sLabels: \n", indent + 2, "");
    block->labels->print(block->labels, indent + 4);
  }
  if (block->constants != NULL) {
    printf("%*sConstants: \n", indent + 2, "");
    block->constants->print(block->constants, indent + 4);
  }
  if (block->types != NULL) {
    printf("%*sTypes: \n", indent + 2, "");
    block->types->print(block->types, indent + 4);
  }
  if (block->variables != NULL) {
    printf("%*sVariables: \n", indent + 2, "");
    block->variables->print(block->variables, indent + 4);
  }
  if (block->procs_funcs != NULL) {
    printf("%*sProcedures e Functions: \n", indent + 2, "");
    block->procs_funcs->print(block->procs_funcs, indent + 4);
  }
  if (block->statements != NULL) {
    printf("%*sStatements: \n", indent + 2, "");
    block->statements->print(block->statements, indent + 4);
  }
}

void print_stmt_list(ASTNode *node, int indent) {
  ListNode *current = (ListNode *)node;

  while (current) {
    if (current->element) {
      switch (current->element->type) {
      case NODE_COMPOUND_STMT:{
        printf("%*sNODE_COMPOUND_STMT!\n", indent, "");
        break;
      }
      case NODE_ASSIGN_STMT:{
        printf("%*sNODE_ASSIGN_STMT!\n", indent, "");
        break;
      }
      case NODE_PROC_CALL:{
        printf("%*sNODE_PROC_CALL!\n", indent, "");
        break;
      }
      case NODE_IF_STMT:{
        printf("%*sNODE_IF_STMT!\n", indent, "");
        break;
      }
      case NODE_CASE_STMT:{
        printf("%*sNODE_CASE_STMT!\n", indent, "");
        break;
      }
      case NODE_CASE_ITEM: {
        printf("%*NODE_CASE_ITEM!\n", indent, "");
        break;
      }
      case NODE_CASE_ELSE:{
        printf("%*sNODE_CASE_ELSE!\n", indent, "");
        break;
      }
      case NODE_WHILE_STMT:{
        printf("%*sNODE_WHILE!\n", indent, "");
        break;
      }
      case NODE_REPEAT_STMT:{
        printf("%*sNODE_REPEATE!\n", indent, "");
        break;
      }
      case NODE_FOR_STMT:{
        printf("%*sNODE_FOR!\n", indent, "");
        break;
      }
      case NODE_WITH_STMT:{
        printf("%*sNODE_WITH!\n", indent, "");
        break;
      }
      case NODE_GOTO_STMT:{
        printf("%*sNODE_GOTO!\n", indent, "");
        break;
      }
      case NODE_IDENTIFIER: {
        IdentifierNode *id = (IdentifierNode *)current->element;
        printf("%*sIdentificador: %s\n", indent, "", id->name);
      }
      default:
        printf("%*sUnknown node\n", indent, "");
        break;
      }
    } else {
      printf("[NULL]\n");
    }
    current = (ListNode *)current->next;
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

ASTNode *create_block_node(ASTNode *labels, ASTNode *types, ASTNode *constants,
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
  node->value = value;

  ListNode *list = (ListNode *)malloc(sizeof(ListNode));
  list->base.type = NODE_LIST;
  list->base.location = loc;
  list->base.print = print_list_values;
  list->element = (ASTNode *)node;
  list->next = NULL;

  return (ASTNode *)list;
}

ASTNode *create_constant_declaration_node(ASTNode *id, ASTNode *constant,
                                          SourceLocation loc) {
  ConstDeclarationNode *node =
      (ConstDeclarationNode *)malloc(sizeof(ConstDeclarationNode));
  node->base.type = NODE_CONST_DECL;
  node->base.location = loc;
  node->base.print = print_todo;
  node->identifier = id;
  node->const_expr = constant;

  ListNode *list = (ListNode *)malloc(sizeof(ListNode));
  list->base.type = NODE_LIST;
  list->base.location = loc;
  list->base.print = print_list_identifiers;
  list->element = (ASTNode *)node;
  list->next = NULL;

  return (ASTNode *)list;
}

ASTNode *create_type_declaration_node(ASTNode *id, ASTNode *type,
                                      SourceLocation loc) {
  TypeDeclarationNode *node =
      (TypeDeclarationNode *)malloc(sizeof(TypeDeclarationNode));
  node->base.type = NODE_TYPE_DECL;
  node->base.location = loc;
  node->base.print = print_todo;
  node->identifier = id;
  node->type_expr = type;

  ListNode *list = (ListNode *)malloc(sizeof(ListNode));
  list->base.type = NODE_LIST;
  list->base.location = loc;
  list->base.print = print_list_identifiers;
  list->element = (ASTNode *)node;
  list->next = NULL;

  return (ASTNode *)list;
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

ASTNode *create_case_stmt_node(ASTNode *expr, ASTNode *case_list,
                               ASTNode *else_part, SourceLocation loc) {
  CaseNode *node = (CaseNode *)malloc(sizeof(CaseNode));
  node->base.type = NODE_CASE_STMT;
  node->base.location = loc;
  node->base.print = print_todo;
  node->expr = expr;
  node->case_list = case_list;
  node->else_part = else_part;
  return (ASTNode *)node;
}

ASTNode *create_case_stmt_with_else_node(ASTNode *expression, ASTNode *case_list,
                                         ASTNode *else_part,
                                         SourceLocation loc) {
  return create_case_stmt_node(expression, case_list, else_part, loc);
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

ASTNode *create_case_item_node(ASTNode *value_list, ASTNode *stmt, SourceLocation loc) {
    CaseItemNode *node = (CaseItemNode *)malloc(sizeof(CaseItemNode));
    node->base.type = NODE_CASE_ITEM;
    node->base.location = loc;
    node->base.print = print_todo;
    node->value_list = value_list;
    node->statement = stmt;


    ListNode *list = (ListNode *)malloc(sizeof(ListNode));
    list->base.type = NODE_LIST;
    list->base.location = loc;
    list->base.print = print_todo;
    list->element = (ASTNode *)node;
    list->next = NULL;
    return (ASTNode *)list;
}

ASTNode *create_case_else_node(ASTNode *stmt, SourceLocation loc) {
  CaseElseNode *node = (CaseElseNode *)malloc(sizeof(CaseElseNode));
  node->base.type = NODE_CASE_ELSE;
  node->base.location = loc;
  node->base.print = print_todo;
  node->stmt = stmt;
  return (ASTNode *)node;
};

ASTNode *create_case_label_list(ASTNode* case_label, SourceLocation loc) {
  ListNode *new_list = (ListNode *)malloc(sizeof(ListNode));
  new_list->base.type = NODE_LIST;
  new_list->base.location = loc;
  new_list->base.print = print_todo;
  new_list->element = case_label;
  new_list->next = NULL;
  return (ASTNode *)new_list;
}

ASTNode *create_case_range_node(ASTNode *constant, ASTNode *constant2, SourceLocation loc) {
  // TODO
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
};

ASTNode *create_variable_declaration_node(ASTNode *list, ASTNode *type,
                                          SourceLocation loc) {
  VarDeclarationNode *decl =
      (VarDeclarationNode *)malloc(sizeof(VarDeclarationNode));
  decl->base.type = NODE_VAR_DECL;
  decl->base.location = loc;
  decl->base.print = print_todo;
  decl->var_list = list;
  decl->type_node = type;
  decl->scope_level = 0;

  ListNode *new_list = (ListNode *)malloc(sizeof(ListNode));
  new_list->base.type = NODE_LIST;
  new_list->base.location = loc;
  new_list->base.print = print_variable_declaration;
  new_list->element = (ASTNode *)decl;
  new_list->next = NULL;
  return (ASTNode *)new_list;
};

ASTNode *create_variable_identifier_list_node(ASTNode *id, SourceLocation loc) {
  ListNode *list = (ListNode *)malloc(sizeof(ListNode));
  list->base.type = NODE_LIST;
  list->base.location = loc;
  list->base.print = print_todo;
  list->element = id;
  list->next = NULL;
  return (ASTNode *)list;
};

ASTNode *create_proc_and_func_declarations_node(ASTNode *proc_and_func,
                                                SourceLocation loc) {
  ListNode *node = (ListNode *)malloc(sizeof(ListNode));
  node->base.type = NODE_LIST;
  node->base.location = loc;
  node->base.print = print_list_identifiers;
  node->element = proc_and_func;
  node->next = NULL;
  return (ASTNode *)node;
}

ASTNode *create_proc_declaration_node(ASTNode *id, ASTNode *parameters,
                                      ASTNode *block_or_forward,
                                      SourceLocation loc) {
  ProcDeclarationNode *proc =
      (ProcDeclarationNode *)malloc(sizeof(ProcDeclarationNode));
  proc->base.type = NODE_PROC_DECL;
  proc->base.location = loc;
  proc->base.print = print_todo;
  proc->identifier = id;
  proc->parameters = parameters;
  proc->block_or_forward = block_or_forward;

  return (ASTNode *)proc;
};

ASTNode *create_func_declaration_node(ASTNode *id, ASTNode *parameters,
                                      ASTNode *type, ASTNode *block_or_forward,
                                      SourceLocation loc) {
  FuncDeclarationNode *func =
      (FuncDeclarationNode *)malloc(sizeof(FuncDeclarationNode));
  func->base.type = NODE_FUNC_DECL;
  func->base.location = loc;
  func->base.print = print_todo;
  func->identifier = id;
  func->type = type;
  func->parameters = parameters;
  func->block_or_forward = block_or_forward;

  return (ASTNode *)func;
};

ASTNode *create_stmt_list_node(ASTNode *stmt, SourceLocation loc) {
  ListNode *new_list = (ListNode *)malloc(sizeof(ListNode));
  new_list->base.type = NODE_LIST;
  new_list->base.location = loc;
  new_list->base.print = print_stmt_list;
  new_list->element = stmt;
  new_list->next = NULL;
  return (ASTNode *)new_list;
};

ASTNode *create_array_type_node(ASTNode *list, ASTNode *type,
                                SourceLocation loc) {};
ASTNode *create_assign_node(ASTNode *variable, ASTNode *expression,
                            SourceLocation loc) {};
ASTNode *create_case_of_variant_node(ASTNode *tag_field, ASTNode *variant_list,
                                     SourceLocation loc) {};
ASTNode *create_constant_identifier(ASTNode *identifier, SourceLocation loc) {};
ASTNode *create_constant_literal(ASTNode *literalValue, SourceLocation loc) {};
ASTNode *create_integer_literal(int integer, SourceLocation loc) {
  LiteralNode *node = (LiteralNode *)malloc(sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_todo;
  node->literal_type = LITERAL_INTEGER;
  node->value.int_val = integer;
  return (ASTNode *)node;
};

ASTNode *create_real_literal(double real, SourceLocation loc) {
  LiteralNode *node = (LiteralNode *)malloc(sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_todo;
  node->literal_type = LITERAL_REAL;
  node->value.real_val = real;
  return (ASTNode *)node;
};

ASTNode *create_string_literal(char *string, SourceLocation loc) {
  LiteralNode *node = (LiteralNode *)malloc(sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_todo;
  node->literal_type = LITERAL_STRING;
  node->value.str_val = strdup(string);
  return (ASTNode *)node;
};

ASTNode *create_char_literal(char character, SourceLocation loc) {
  LiteralNode *node = (LiteralNode *)malloc(sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_todo;
  node->literal_type = LITERAL_CHAR;
  node->value.char_val = character;
  return (ASTNode *)node;
};

ASTNode *create_boolean_literal(bool boolean, SourceLocation loc) {
  LiteralNode *node = (LiteralNode *)malloc(sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_todo;
  node->literal_type = LITERAL_BOOLEAN;
  node->value.bool_val = boolean;
  return (ASTNode *)node;
};

ASTNode *create_nil_literal(SourceLocation loc) {
  LiteralNode *node = (LiteralNode *)malloc(sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_todo;
  node->literal_type = LITERAL_NIL;
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
ASTNode *create_for_stmt_node(ASTNode *variable, ASTNode *for_list, ASTNode *body, SourceLocation loc) {
    ForStmtNode *node = (ForStmtNode *)malloc(sizeof(ForStmtNode));
    node->base.type = NODE_FOR_STMT;
    node->base.location = loc;
    node->base.print = print_todo;
    node->variable = variable;
    node->for_list = for_list;
    node->body = body;
    
    // Extrair o is_downto do for_list
    ForListNode *fl = (ForListNode *)for_list;
    node->is_downto = fl->is_downto;
    
    return (ASTNode *)node;
}
ASTNode *create_for_list_node(ASTNode *start, ASTNode *end, bool is_downto, SourceLocation loc) {
    ForListNode *node = (ForListNode *)malloc(sizeof(ForListNode));
    node->base.type = NODE_FOR_LIST;
    node->base.location = loc;
    node->base.print = print_todo;
    node->start_expr = start;
    node->end_expr = end;
    node->is_downto = is_downto;
    return (ASTNode *)node;
}
ASTNode *create_formal_parameters_list_node(ASTNode *list, ASTNode *param,
                                            SourceLocation loc) {};
ASTNode *create_function_param_node(ASTNode *identifier, ASTNode *params,
                                    ASTNode *type, SourceLocation loc) {};
ASTNode *create_goto_label_node(ASTNode *label, SourceLocation loc) {
    GotoNode *node = (GotoNode *)malloc(sizeof(GotoNode));
    node->base.type = NODE_GOTO_STMT;
    node->base.location = loc;
    node->base.print = print_todo;
    node->label = label;
    return (ASTNode *)node;
}
ASTNode *create_if_stmt_node(ASTNode *condition, ASTNode *then_stmt, ASTNode *else_stmt, SourceLocation loc) {
    IfNode *node = (IfNode *)malloc(sizeof(IfNode));
    node->base.type = NODE_IF_STMT;
    node->base.location = loc;
    node->base.print = print_todo;
    node->condition = condition;
    node->then_stmt = then_stmt;
    node->else_stmt = else_stmt;
    return (ASTNode *)node;
}
ASTNode *create_index_list_node(ASTNode *list, ASTNode *type,
                                SourceLocation loc) {};
ASTNode *create_label_stmt_node(ASTNode *label, ASTNode *stmt, SourceLocation loc) {
    LabeledStmtNode *node = (LabeledStmtNode *)malloc(sizeof(LabeledStmtNode));
    node->base.type = NODE_LABELED_STMT;
    node->base.location = loc;
    node->base.print = print_todo;
    node->label = label;
    node->statement = stmt;
    return (ASTNode *)node;
}
ASTNode *create_packed_type(ASTNode *type, SourceLocation loc) {};
ASTNode *create_parameter_identifier_list_node(ASTNode *list, ASTNode *element,
                                               SourceLocation loc) {};
ASTNode *create_parameter_list_types_node(ASTNode *list, ASTNode *type,
                                          SourceLocation loc) {};
ASTNode *create_parameters_node(ASTNode *parameter, SourceLocation loc) {};
ASTNode *create_poniter_type_node(ASTNode *type, SourceLocation loc) {};
ASTNode *create_procedure_call_node(ASTNode *proc, ASTNode *params, SourceLocation loc) {
    ProcedureCallNode *node = (ProcedureCallNode *)malloc(sizeof(ProcedureCallNode));
    node->base.type = NODE_PROC_CALL;
    node->base.location = loc;
    node->base.print = print_todo;
    node->procedure = proc;
    node->params = params;  // Pode ser NULL se não houver parâmetros
    
    // Definir o tipo do identificador como procedimento
    if (proc->type == NODE_IDENTIFIER) {
        IdentifierNode *id = (IdentifierNode *)proc;
        id->kind = SYMBOL_PROCEDURE;  // Será verificado durante análise semântica
    }
    
    return (ASTNode *)node;
}
ASTNode *create_procedure_param_node(ASTNode *identifier, ASTNode *params,
                                     SourceLocation loc) {};
ASTNode *create_record_access_type(ASTNode *identifier, ASTNode *field,
                                   SourceLocation loc) {};
ASTNode *create_record_field_node(ASTNode *field_list, ASTNode *type,
                                  SourceLocation loc) {};
ASTNode *create_record_type_node(ASTNode *field_list, SourceLocation loc) {};
ASTNode *create_repeat_until_stmt_list_node(ASTNode *body, ASTNode *condition, SourceLocation loc) {
    RepeatUntilNode *node = (RepeatUntilNode *)malloc(sizeof(RepeatUntilNode));
    node->base.type = NODE_REPEAT_STMT;
    node->base.location = loc;
    node->base.print = print_todo;
    node->body = body;
    node->condition = condition;
    return (ASTNode *)node;
}
ASTNode *create_set_of_type_node(ASTNode *type, SourceLocation loc) {};
ASTNode *create_simple_type_node(ASTNode *type, SourceLocation loc) {};
ASTNode *create_structure_type_node(ASTNode *type, SourceLocation loc) {};
ASTNode *create_tag_field_node(ASTNode *identifier, ASTNode *type,
                               SourceLocation loc) {};
ASTNode *create_type_identifier(ASTNode *identifier, SourceLocation loc) {};
ASTNode *create_variant_node(ASTNode *label_list, ASTNode *field_list,
                             SourceLocation loc) {};
ASTNode *create_while_stmt_node(ASTNode *condition, ASTNode *body, SourceLocation loc) {
    WhileStmtNode *node = (WhileStmtNode *)malloc(sizeof(WhileStmtNode));
    node->base.type = NODE_WHILE_STMT;
    node->base.location = loc;
    node->base.print = print_todo;
    node->condition = condition;
    node->body = body;
    return (ASTNode *)node;
};

ASTNode *create_with_record_list_node(ASTNode *record_list, ASTNode *body, SourceLocation loc) {
    WithNode *node = (WithNode *)malloc(sizeof(WithNode));
    node->base.type = NODE_WITH_STMT;
    node->base.location = loc;
    node->base.print = print_todo;
    node->record_list = record_list;
    node->body = body;
    return (ASTNode *)node;
}

ASTNode *create_identifier_node(char *name, SourceLocation loc) {
  IdentifierNode *node = (IdentifierNode *)malloc(sizeof(IdentifierNode));

  node->base.type = NODE_IDENTIFIER;
  node->base.location = loc;
  node->base.print = print_todo;
  node->name = strdup(name);
  node->kind = SYMBOL_UNKNOWN;
  node->symbol_entry = NULL;
  return (ASTNode *)node;
};

ASTNode *create_unsigned_integer_node(int integer, SourceLocation loc) {
  LiteralNode *node = (LiteralNode *)malloc(sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_todo;
  node->literal_type = LITERAL_INTEGER;
  node->value.int_val = integer;
  return (ASTNode *)node;
}

ASTNode *create_unsigned_real_node(double real, SourceLocation loc) {
  LiteralNode *node = (LiteralNode *)malloc(sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_todo;
  node->literal_type = LITERAL_REAL;
  node->value.real_val = real;
  return (ASTNode *)node;
}

ASTNode *create_record_variable_list_node(ASTNode *record_var, SourceLocation loc) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    node->base.type = NODE_LIST;
    node->base.location = loc;
    node->base.print = print_todo;
    node->element = record_var;
    node->next = NULL;
    return (ASTNode *)node;;
}

ASTNode *append_case_item(ASTNode *list, ASTNode *case_item, SourceLocation loc) {
    ListNode *head = (ListNode *)list;
    
    if (head) {
        ListNode *cur = head;
        while (cur->next)
            cur = (ListNode *)cur->next;
        cur->next = (ASTNode *)case_item;
        return (ASTNode *)head;
    } else {
        return case_item;
    }
}

ASTNode *append_case_label_list(ASTNode *list, ASTNode *case_label, SourceLocation loc) {
  ListNode *head = (ListNode *)list;
  
  if (head) {
      ListNode *cur = head;
      while (cur->next)
          cur = (ListNode *)cur->next;
      cur->next = (ASTNode *)case_label;
      return (ASTNode *)head;
  } else {
      return case_label;
  }
}

// Adiciona um record à lista de records no with
ASTNode *append_record_variable_list(ASTNode *list, ASTNode *record_var, SourceLocation loc) {
    ListNode *head = (ListNode *)list;
    
    ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
    new_node->base.type = NODE_LIST;
    new_node->base.location = loc;
    new_node->base.print = print_todo;
    new_node->element = record_var;
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

ASTNode *append_label_declaration(ASTNode *list, ASTNode *element,
                                  SourceLocation loc) {

  ListNode *new_node = (ListNode *)create_label_declaration_node(element, loc);

  if (list == NULL) {
    return (ASTNode *)new_node;
  }

  ListNode *current = (ListNode *)list;
  while (current->next != NULL) {
    current = (ListNode *)current->next;
  }

  current->next = (ASTNode *)new_node;
  return list;
}

ASTNode *append_constant_declaration(ASTNode *list, ASTNode *id,
                                     ASTNode *constant, SourceLocation loc) {
  ListNode *new_node =
      (ListNode *)create_constant_declaration_node(id, constant, loc);

  if (list == NULL) {
    return (ASTNode *)new_node;
  }

  ListNode *current = (ListNode *)list;
  while (current->next != NULL) {
    current = (ListNode *)current->next;
  }

  current->next = (ASTNode *)new_node;
  return list;
}

ASTNode *append_type_declaration(ASTNode *list, ASTNode *id, ASTNode *type_expr,
                                 SourceLocation loc) {
  ListNode *new_node =
      (ListNode *)create_type_declaration_node(id, type_expr, loc);

  if (list == NULL) {
    return (ASTNode *)new_node;
  }

  ListNode *current = (ListNode *)list;
  while (current->next != NULL) {
    current = (ListNode *)current->next;
  }

  current->next = (ASTNode *)new_node;
  return list;
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

ASTNode *append_variable_declaration(ASTNode *list, ASTNode *vars,
                                     ASTNode *type, SourceLocation loc) {
  ListNode *new_node =
      (ListNode *)create_variable_declaration_node(vars, type, loc);

  if (list == NULL) {
    return (ASTNode *)new_node;
  }

  ListNode *current = (ListNode *)list;
  while (current->next != NULL) {
    current = (ListNode *)current->next;
  }

  current->next = (ASTNode *)new_node;
  return list;
}
ASTNode *append_variable_identifier_list(ASTNode *list, ASTNode *var_id,
                                         SourceLocation loc) {
  ListNode *new_node =
      (ListNode *)create_variable_identifier_list_node(var_id, loc);

  if (list == NULL) {
    return (ASTNode *)new_node;
  }

  ListNode *current = (ListNode *)list;
  while (current->next != NULL) {
    current = (ListNode *)current->next;
  }

  current->next = (ASTNode *)new_node;
  return list;
}
ASTNode *append_variant_list(ASTNode *list, ASTNode *element,
                             SourceLocation loc) {}
ASTNode *append_stmt_list(ASTNode *list, ASTNode *stmt, SourceLocation loc) {
  ListNode *new_node = (ListNode *)create_stmt_list_node(stmt, loc);

  if (list == NULL) {
    return (ASTNode *)new_node;
  }

  ListNode *current = (ListNode *)list;
  while (current->next != NULL) {
    current = (ListNode *)current->next;
  }

  current->next = (ASTNode *)new_node;
  return list;
}

ASTNode *append_proc_and_func_declarations(ASTNode *list,
                                           ASTNode *proc_and_func,
                                           SourceLocation loc) {
  ListNode *head = (ListNode *)list;

  ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
  new_node->base.type = NODE_LIST;
  new_node->base.location = loc;
  new_node->base.print = print_todo;
  new_node->element = proc_and_func;
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

ASTNode *add_labels_to_block(ASTNode *block, ASTNode *labels) {
  BlockNode *blk = (BlockNode *)block;
  return create_block_node(labels, blk->types, blk->constants, blk->variables,
                           blk->procs_funcs, blk->statements,
                           blk->base.location);
}

ASTNode *add_constants_to_block(ASTNode *block, ASTNode *constants) {
  BlockNode *blk = (BlockNode *)block;
  return create_block_node(blk->labels, blk->types, constants, blk->variables,
                           blk->procs_funcs, blk->statements,
                           blk->base.location);
}

ASTNode *add_types_to_block(ASTNode *block, ASTNode *types) {
  BlockNode *blk = (BlockNode *)block;
  return create_block_node(blk->labels, types, blk->constants, blk->variables,
                           blk->procs_funcs, blk->statements,
                           blk->base.location);
}

ASTNode *add_variables_to_block(ASTNode *block, ASTNode *variables) {
  BlockNode *blk = (BlockNode *)block;
  return create_block_node(blk->labels, blk->types, blk->constants, variables,
                           blk->procs_funcs, blk->statements,
                           blk->base.location);
}

ASTNode *add_procs_funcs_to_block(ASTNode *block, ASTNode *procs_funcs) {
  BlockNode *blk = (BlockNode *)block;
  return create_block_node(blk->labels, blk->types, blk->constants,
                           blk->variables, procs_funcs, blk->statements,
                           blk->base.location);
}

/* UTILS */

ASTNode *get_statements_from_block(ASTNode *block) {
  if (!block)
    return NULL;
  return ((BlockNode *)block)->statements;
}

void print_todo(ASTNode *node, int indent) {
  printf("%*sTODO %d\n", indent, "", node->type);
}

void free_node(ASTNode *node) {
  if (!node)
    return;

  switch (node->type) {
  case NODE_PROGRAM: {
    ProgramNode *prog = (ProgramNode *)node;
    free(prog->name);
    free_node(prog->heading);
    free_node(prog->block);
    break;
  }
  case NODE_HEADING: {
    break;
  }
  case NODE_BLOCK: {
    break;
  }
  case NODE_USES: {
    break;
  }
  case NODE_LABEL_DECL: {
    break;
  }
  case NODE_CONST_DECL: {
    break;
  }
  case NODE_TYPE_DECL: {
    break;
  }
  case NODE_VAR_DECL: {
    break;
  }
  case NODE_PROC_DECL: {
    break;
  }
  case NODE_FUNC_DECL: {
    break;
  }
  case NODE_CONST_ITEM: {
    break;
  }
  case NODE_SCALAR_TYPE: {
    break;
  }
  case NODE_SUBRANGE_TYPE: {
    break;
  }
  case NODE_TYPE_IDENTIFIER: {
    break;
  }
  case NODE_STRUCTURED_TYPE: {
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
  case NODE_ASSIGN_STMT: {
    break;
  }
  case NODE_PROC_CALL: {
    break;
  }
  case NODE_IF_STMT: {
    break;
  }
  case NODE_CASE_STMT: {
    break;
  }
  case NODE_CASE_ITEM: {
    break;
  }
  case NODE_CASE_ELSE: {
    break;
  }
  case NODE_WHILE_STMT: {
    break;
  }
  case NODE_REPEAT_STMT: {
    break;
  }
  case NODE_FOR_STMT: {
    break;
  }
  case NODE_WITH_STMT: {
    break;
  }
  case NODE_GOTO_STMT: {
    break;
  }
  case NODE_BINARY_EXPR: {
    break;
  }
  case NODE_UNARY_EXPR: {
    break;
  }
  case NODE_LITERAL: {
    break;
  }
  case NODE_IDENTIFIER: {
    break;
  }
  case NODE_MEMBER_ACCESS: {
    break;
  }
  case NODE_ARRAY_ACCESS: {
    break;
  }
  case NODE_FUNC_CALL: {
    break;
  }
  case NODE_SET_CONSTRUCTOR: {
    break;
  }
  case NODE_FIELD_LIST: {
    break;
  }
  case NODE_PARAMETER: {
    break;
  }
  case NODE_VARIANT_RECORD: {
    break;
  }
  case NODE_LIST: {
    break;
  }
  case NODE_ERROR: {
    break;
  }
  }

  free(node);
}
