#include "ast.h"
#include <string.h>
#include "../symbol-table/symbol-table.h"

extern ht *HashTable;

SourceLocation create_location(YYLTYPE loc) {
  SourceLocation result;
  result.first_line = loc.first_line;
  result.first_column = loc.first_column;
  result.last_line = loc.last_line;
  result.last_column = loc.last_column;
  result.file_name = strdup(yylloc.file_name);
  return result;
}

char* debug_location(SourceLocation loc) {
  char buffer[100];
  sprintf(buffer, "%d.%d-%d.%d", loc.first_line, loc.first_column, loc.last_line, loc.last_column);
  return strdup(buffer);
};

void print_program_node(ASTNode *node, int indent) {
  ProgramNode *prog = (ProgramNode *)node;
  printf("%*sProgram: %s - at: %s [%s]\n", indent, "", prog->name,
         debug_location(prog->base.location),
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
      switch(current->element->type) {
        case NODE_FUNC_DECL:{
          FuncDeclarationNode *fd = (FuncDeclarationNode*)current->element;
          IdentifierNode* id = (IdentifierNode *)fd->identifier;
          printf("%*s%s\n", indent, "", id->name);
          break;
       }
        case NODE_PROC_DECL: {
          ProcDeclarationNode *pd = (ProcDeclarationNode*)current->element;
          IdentifierNode* id = (IdentifierNode *)pd->identifier;
          printf("%*s%s\n", indent, "", id->name);
          break;
       }
        case NODE_TYPE_DECL: {
          TypeDeclarationNode *td = (TypeDeclarationNode*)current->element;
          TypeIdentifierNode *ti = (TypeIdentifierNode *)td->identifier;
          if (ti->id) {
            IdentifierNode* id = (IdentifierNode *)ti->id;
            printf("%*s%s\n", indent, "", id->name);
          } else {
            printf("%*s%s\n", indent, "", ti->name);
          }
          break;
        }
        case NODE_CONST_DECL: {
          ConstDeclarationNode *cd = (ConstDeclarationNode*)current->element;
          IdentifierNode* id = (IdentifierNode *)cd->identifier;
          printf("%*s%s\n", indent, "", id->name);
          break;
        }
        default: {
          printf("%*sUnknown Identifier Type %s", indent, "", nodeTypeToString(current->element->type));
          break;
        }
      }
    } else {
      printf("%*sprint_list_identifiers: [NULL]\n", indent, "");
    }
    current = (ListNode *)current->next;
  }
}

void print_literal_value(ASTNode *node, int indent) {
  if (node->type != NODE_LITERAL) {
    printf("%*s[WARNING] try print literal value from type: %s\n", indent, "", nodeTypeToString(node->type));
    return;
  };

  LiteralNode *lit = (LiteralNode *)node;
  if (lit->literal_type == LITERAL_STRING) {
    printf("%*sLiteral %s\n", indent, "", lit->value.str_val);
  } else if (lit->literal_type == LITERAL_INTEGER) {
    printf("%*sLiteral %d\n", indent, "", lit->value.int_val);
  } else if (lit->literal_type == LITERAL_REAL) {
    printf("%*sLiteral %.2f\n", indent, "", lit->value.real_val);
  } else if (lit->literal_type == LITERAL_BOOLEAN) {
    printf("%*sLiteral %s\n", indent, "", lit->value.bool_val ? "true" : "false");
  } else if (lit->literal_type == LITERAL_CHAR) {
    printf("%*sLiteral %c\n", indent, "", lit->value.char_val);
  }
}

void print_list_values(ASTNode *node, int indent) {
  ListNode *current = (ListNode *)node;

  while (current) {
    if (current->element) {
      if (current->element->type == NODE_LITERAL) {
        print_literal_value(current->element, indent);
      } else if (current->element->type == NODE_LABEL_DECL) {
        LabelDeclarationNode *d = (LabelDeclarationNode*)current->element;
        print_literal_value(d->value, indent);
      } else {
        printf("%*s(print_list_values) Unknown type: %s\n", indent, "", nodeTypeToString(current->element->type));
      }
    } else {
      printf("%*sprint_list_values [NULL]\n", indent, "");
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
          printf("%*sprint_variable_declaration [NULL]\n", indent, "");
        }
        first += 1;
        new_curr = (ListNode *)new_curr->next;
      }
      printf(")\n");
    } else {
      printf("%*sprint_variable_declaration [NULL]\n", indent, "");
    }
    current = (ListNode *)current->next;
  }
}

void debug_lists(ListNode *node, int indent) {
  if (node->base.type != NODE_LIST) {
    printf("%*s[WARNING] Attempt to print list node with type %s, location: %s\n", indent+4, "", nodeTypeToString(node->base.type), debug_location(node->base.location));
    return;
  }
  printf("%*sTypes: %s - location: %s\n", indent+4, "", nodeTypeToString(node->base.type), debug_location(node->base.location));
  while(node) {
    if (node->element) {
      printf("%*sElement: %s - location: %s\n", indent+4, "", nodeTypeToString(node->element->type), debug_location(node->element->location));
      debug_lists((ListNode*)node->element, indent+5);
    }
    if (node->next) {
      printf("%*sNext: %s - location: %s\n", indent+4, "", nodeTypeToString(node->next->type), debug_location(node->next->location));
      debug_lists((ListNode*)node->next, indent+10);
    }
    node = (ListNode*) node->next;
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
      case NODE_COMPOUND_STMT: {
        printf("%*sNODE_COMPOUND_STMT-> (%s)\n", indent, "", debug_location(current->element->location));
        current->element->print(current->element, indent+2);
        break;
      }
      case NODE_ASSIGN_STMT: {
        printf("%*sNODE_ASSIGN_STMT-> (%s)\n", indent, "", debug_location(current->element->location));
        AssignmentNode *a = (AssignmentNode *)current->element;
        if (a->target->type == NODE_IDENTIFIER) {
          a->target->print(a->target, indent+2);
        }
        a->expression->print(a->expression, indent+2);
        break;
      }
      case NODE_PROC_CALL: {
        printf("%*sNODE_PROC_CALL-> (%s)\n", indent, "", debug_location(current->element->location));
        ProcedureCallNode *proc = (ProcedureCallNode *)current->element;
        if (proc->procedure->type == NODE_IDENTIFIER) {
          proc->procedure->print(proc->procedure, indent+2);
          break;
        }
        proc->base.print((ASTNode *)proc, indent+2);
        break;
      }
      case NODE_IF_STMT: {
        printf("%*sNODE_IF_STMT-> (%s)\n", indent, "", debug_location(current->element->location));
        current->element->print(current->element, indent+2);
        break;
      }
      case NODE_CASE_STMT: {
        printf("%*sNODE_CASE_STMT-> (%s)\n", indent, "", debug_location(current->element->location));
        current->element->print(current->element, indent+2);
        break;
      }
      case NODE_CASE_ITEM: {
        printf("%*sNODE_CASE_ITEM-> (%s)\n", indent, "", debug_location(current->element->location));
        current->element->print(current->element, indent+2);
        break;
      }
      case NODE_CASE_ELSE: {
        printf("%*sNODE_CASE_ELSE-> (%s)\n", indent, "", debug_location(current->element->location));
        current->element->print(current->element, indent+2);
        break;
      }
      case NODE_WHILE_STMT: {
        printf("%*sNODE_WHILE-> (%s)\n", indent, "", debug_location(current->element->location));
        WhileStmtNode *w = (WhileStmtNode *)current->element;
        print_stmt_list(w->body, indent+2);
        break;
      }
      case NODE_REPEAT_STMT: {
        printf("%*sNODE_REPEAT-> (%s)\n", indent, "", debug_location(current->element->location));
        RepeatUntilNode *r = (RepeatUntilNode *)current->element;
        print_stmt_list(r->body, indent+2);
        break;
      }
      case NODE_FOR_STMT: {
        printf("%*sNODE_FOR-> (%s)\n", indent, "", debug_location(current->element->location));
        ForStmtNode *ft = (ForStmtNode *)current->element;
        if (ft->variable->type == NODE_IDENTIFIER) {
          ft->variable->print(ft->variable, indent+2);
        }
        print_stmt_list(ft->body, indent+2);
        break;
      }
      case NODE_WITH_STMT: {
        printf("%*sNODE_WITH-> (%s)\n", indent, "", debug_location(current->element->location));
        current->element->print(current->element, indent+2);
        break;
      }
      case NODE_GOTO_STMT: {
        printf("%*sNODE_GOTO-> (%s)\n", indent, "", debug_location(current->element->location));
        current->element->print(current->element, indent+2);
        break;
      }
      case NODE_IDENTIFIER: {
        printf("%*sNODE_IDENTIFIER-> (%s)\n", indent, "", debug_location(current->element->location));
        print_identifier_node(current->element, indent+2);
        break;
      }
      case NODE_LIST: {
        printf("%*sNODE_LIST-> (%s)\n", indent, "", debug_location(current->element->location));
        print_stmt_list(current->element, indent+2);          
        break;
      }
      case NODE_BINARY_EXPR: {
        printf("%*sNODE_BINARY_EXPR-> (%s)\n", indent, "",debug_location(current->element->location));
        print_binary_operation(current->element, indent+2);
        break;
      }
      default:
        printf("%*sNode Type %s (%s)\n", indent, "", nodeTypeToString(current->element->type), debug_location(current->element->location));
        break;
      }
    } else {
      if (current->next) {
        printf("%*s Element (null) but next -> %s (%s)\n", indent, "", nodeTypeToString(current->next->type), debug_location(current->next->location));
      }
      printf("%*sElement (null), current type: %s (%s)\n", indent, "", nodeTypeToString(current->base.type), debug_location(current->element->location));
    }
    current = (ListNode *)current->next;
  }
}

void print_identifier_node(ASTNode *node, int indent) {
  if (node->type != NODE_IDENTIFIER) {
    printf("WARN: Tentou imprimir NODE_IDENTIFIER, mas o tipo é %s!\n", nodeTypeToString(node->type));
  }
  IdentifierNode *id = (IdentifierNode *)node;
  if (id->name != NULL) {
    printf("%*sIdentificador: %s\n", indent, "", id->name);
  } else {
    printf("%*sIdentificador: <unnamed>\n", indent, "");
  }
}

void print_binary_operation(ASTNode *node, int indent) {
  BinaryOperationNode *expr = (BinaryOperationNode *)node;
  printf("%*sBinary Expression (op: %s)\n", indent, "", binary_op_to_string(expr->operator));
  if (expr->left) {
    if (expr->left->type == NODE_IDENTIFIER) {
      print_identifier_node(expr->left, indent+2);
    } else {
      expr->left->print(expr->left, indent + 2);
    }
  }
  if (expr->right) {
    if (expr->right->type == NODE_IDENTIFIER) {
      print_identifier_node(expr->right, indent+2);
    } else {
      expr->right->print(expr->right, indent + 2);
    }
  }
}

void print_unary_operation(ASTNode *node, int indent) {
  UnaryOperationNode *expr = (UnaryOperationNode *)node;
  printf("%*sUnary Expression (op: %s)\n", indent, "", unary_op_to_string(expr->operator));
  if (expr->operand) {
    expr->operand->print(expr->operand, indent + 2);
  }
}

void print_function_call(ASTNode *node, int indent) {
  FunctionCallNode *fc = (FunctionCallNode*)node;
  printf("%*sNODE_FUNC_CALL->\n", indent, "");
  print_identifier_node(fc->function, indent+2);
  // fc->params->print(fc->params, indent);
  printf("%*sFUNC_CALL_PARAMS->\n", indent+2, "");
  print_stmt_list(fc->params, indent+4);
}

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

ASTNode *create_type_identifier(ASTNode *id, SourceLocation loc) {
  TypeIdentifierNode *typeid =
      (TypeIdentifierNode *)malloc(sizeof(TypeIdentifierNode));
  typeid->base.type = NODE_TYPE_IDENTIFIER;
  typeid->base.location = loc;
  typeid->base.print = print_todo;
  typeid->id = (IdentifierNode *)id;
  typeid->is_base_type = false;

  return (ASTNode *)typeid;
}

ASTNode *create_builtin_type_identifier(char *name, SourceLocation loc) {
  TypeIdentifierNode *typeid =
      (TypeIdentifierNode *)malloc(sizeof(TypeIdentifierNode));
  typeid->base.type = NODE_TYPE_IDENTIFIER;
  typeid->base.location = loc;
  typeid->base.print = print_todo;
  typeid->name = strdup(name);
  typeid->kind = SYMBOL_BUILTIN;
  typeid->is_base_type = true;

  return (ASTNode *)typeid;
}

ASTNode *create_builtin_identifier(char *name, SourceLocation loc) {
  IdentifierNode *built = (IdentifierNode *)malloc(sizeof(IdentifierNode));
  built->base.type = NODE_IDENTIFIER;
  built->base.location = loc;
  built->base.print = print_identifier_node;
  built->name = strdup(name);
  built->kind = SYMBOL_PROCEDURE;
  return (ASTNode *)built;
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

ASTNode *create_case_stmt_with_else_node(ASTNode *expression,
                                         ASTNode *case_list, ASTNode *else_part,
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

ASTNode *create_case_item_node(ASTNode *value_list, ASTNode *stmt,
                               SourceLocation loc) {
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

ASTNode *create_case_label_list(ASTNode *case_label, SourceLocation loc) {
  ListNode *new_list = (ListNode *)malloc(sizeof(ListNode));
  new_list->base.type = NODE_LIST;
  new_list->base.location = loc;
  new_list->base.print = print_todo;
  new_list->element = case_label;
  new_list->next = NULL;
  return (ASTNode *)new_list;
}

ASTNode *create_constant_range_node(ASTNode *constant1, ASTNode *constant2,
                                    SourceLocation loc) {
  // TODO: In a semantic analysis, the type of lower and upper must be equal
  SubrangeTypeNode *node = (SubrangeTypeNode *)malloc(sizeof(SubrangeTypeNode));
  node->base.type = NODE_SUBRANGE_TYPE;
  node->base.location = loc;
  node->base.print = print_todo;
  node->lower = constant1;
  node->upper = constant2;

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
  // TODO: verificar se existe antes de acessar
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
  decl->base.print = print_variable_declaration;
  decl->var_list = list;
  decl->type_node = type;
  decl->scope_level = 0;

  ListNode *curr = (ListNode *)list;
  int offset = 0;
  while (curr) {
    if (curr->element) {
      IdentifierNode *id_node = (IdentifierNode *)curr->element;
      id_node->kind = SYMBOL_VARIABLE;
      SymbolEntry *symb = ht_get(HashTable, id_node->symbol_entry_key);
      symb->kind = SYMBOL_VARIABLE;
      symb->info.var_info.type = type;
      symb->info.var_info.offset = offset;
      symb->scope_level = decl->scope_level;

      ht_set(HashTable, symb->name, symb);
      offset += 1;
    }
    curr = (ListNode *)curr->next;
  }

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

  IdentifierNode *id_node = (IdentifierNode *)id;
  SymbolEntry *symb = ht_get(HashTable, id_node->symbol_entry_key);
  symb->info.func_info.return_type = NULL;
  symb->info.func_info.params = parameters;

  if (block_or_forward->type == NODE_FORWARD_DECL) {
    symb->info.func_info.is_forward = true;
  } else {
    symb->info.func_info.body = block_or_forward;
  }

  ht_set(HashTable, symb->name, symb);

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

  IdentifierNode *id_node = (IdentifierNode *)id;
  SymbolEntry *symb = ht_get(HashTable, id_node->symbol_entry_key);
  symb->info.func_info.return_type = type;
  symb->info.func_info.params = parameters;

  if (block_or_forward->type == NODE_FORWARD_DECL) {
    symb->info.func_info.is_forward = true;
  } else {
    symb->info.func_info.body = block_or_forward;
  }

  ht_set(HashTable, symb->name, symb);

  return (ASTNode *)func;
};

ASTNode *create_forward_declaration_node(SourceLocation loc) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = NODE_FORWARD_DECL;
  node->location = loc;
  node->print = print_todo;
  return node;
}

ASTNode *create_stmt_list_node(ASTNode *stmt, SourceLocation loc) {
  ListNode *new_list = (ListNode *)malloc(sizeof(ListNode));
  new_list->base.type = NODE_LIST;
  new_list->base.location = loc;
  new_list->base.print = print_stmt_list;
  new_list->element = stmt;
  new_list->next = NULL;
  return (ASTNode *)new_list;
};

ASTNode *create_expression_range_node(ASTNode *expression1,
                                      ASTNode *expression2,
                                      SourceLocation loc) {
  // TODO: In Semantic analysis, the expressions must match types
  ElementNode *element = (ElementNode *)malloc(sizeof(ElementNode));
  element->base.type = NODE_SET_CONSTRUCTOR;
  element->base.location = loc;
  element->base.print = print_todo;
  element->lower = expression1;
  element->upper = expression2;

  return (ASTNode *)element;
}

ASTNode *create_array_type_node(ASTNode *list, ASTNode *type,
                                SourceLocation loc) {
  ArrayTypeNode *node = (ArrayTypeNode *)malloc(sizeof(ArrayTypeNode));
  node->base.type = NODE_ARRAY_TYPE;
  node->base.location = loc;
  node->base.print = print_todo;
  node->index_list = list;
  node->type = type;

  return (ASTNode *)node;
};

ASTNode *create_assign_node(ASTNode *variable, ASTNode *expression,
                            SourceLocation loc) {
  AssignmentNode *node = (AssignmentNode*)malloc(sizeof(AssignmentNode));
  node->base.type = NODE_ASSIGN_STMT;
  node->base.location = loc;
  node->base.print = print_todo;
  node->target = variable;
  node->expression = expression;

  return (ASTNode *)node;
};

ASTNode *create_case_of_variant_node(ASTNode *tag_field, ASTNode *variant_list,
                                     SourceLocation loc) {
  VariantPartNode *part = (VariantPartNode*)malloc(sizeof(VariantPartNode));
  part->base.type = NODE_VARIANT_PART;
  part->base.location = loc;
  part->base.print = print_todo;
  part->tag_field = tag_field;
  part->variant_list = variant_list;

  return (ASTNode *)part;
};

ASTNode *create_constant_identifier(ASTNode *identifier, SourceLocation loc) {
  ConstantNode *node = (ConstantNode*)malloc(sizeof(ConstantNode));
  node->base.type = NODE_CONST_IDENTIFIER;
  node->base.location = loc;
  node->base.print = print_todo;
  node->is_literal = false;
  node->identifier = identifier;

  if (identifier->type == NODE_IDENTIFIER) {
    IdentifierNode *id = (IdentifierNode *)identifier;
    id->kind = SYMBOL_CONSTANT;
  }

  return (ASTNode *)node;
};

ASTNode *create_constant_literal(ASTNode *literalValue, SourceLocation loc) {
  ConstantNode *node = (ConstantNode*)malloc(sizeof(ConstantNode));
  node->base.type = NODE_CONST_IDENTIFIER;
  node->base.location = loc;
  node->base.print = print_todo;
  node->value = literalValue;
  node->is_literal = true;

  return (ASTNode *)node;
};

ASTNode *create_integer_literal(int integer, SourceLocation loc) {
  LiteralNode *node = (LiteralNode *)malloc(sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_literal_value;
  node->literal_type = LITERAL_INTEGER;
  node->value.int_val = integer;
  return (ASTNode *)node;
};

ASTNode *create_real_literal(double real, SourceLocation loc) {
  LiteralNode *node = (LiteralNode *)malloc(sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_literal_value;
  node->literal_type = LITERAL_REAL;
  node->value.real_val = real;
  return (ASTNode *)node;
};

ASTNode *create_string_literal(char *string, SourceLocation loc) {
  LiteralNode *node = (LiteralNode *)malloc(sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_literal_value;
  node->literal_type = LITERAL_STRING;
  node->value.str_val = strdup(string);
  return (ASTNode *)node;
};

ASTNode *create_char_literal(char character, SourceLocation loc) {
  LiteralNode *node = (LiteralNode *)malloc(sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_literal_value;
  node->literal_type = LITERAL_CHAR;
  node->value.char_val = character;
  return (ASTNode *)node;
};

ASTNode *create_boolean_literal(bool boolean, SourceLocation loc) {
  LiteralNode *node = (LiteralNode *)malloc(sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_literal_value;
  node->literal_type = LITERAL_BOOLEAN;
  node->value.bool_val = boolean;
  return (ASTNode *)node;
};

ASTNode *create_nil_literal(SourceLocation loc) {
  LiteralNode *node = (LiteralNode *)malloc(sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_literal_value;
  node->literal_type = LITERAL_NIL;
  return (ASTNode *)node;
};

ASTNode *create_constant_signed_identifier(ASTNode *identifier, const char *sign,
                                           SourceLocation loc) {
  ConstantNode *node = (ConstantNode*)malloc(sizeof(ConstantNode));
  node->base.type = NODE_CONST_IDENTIFIER;
  node->base.location = loc;
  node->base.print = print_todo;
  node->is_literal = false;
  node->identifier = identifier;
  node->sign = strdup(sign);

  if (identifier->type == NODE_IDENTIFIER) {
    IdentifierNode *id = (IdentifierNode *)identifier;
    id->kind = SYMBOL_CONSTANT;
  }

  return (ASTNode *)node;
};

ASTNode *create_field_identifier_list_node(ASTNode *list, ASTNode *identifier,
                                           SourceLocation loc) {
  if (identifier == NULL) {
    return list;
  }

  ListNode *new_node = (ListNode*)malloc(sizeof(ListNode));
  new_node->base.type = NODE_LIST;
  new_node->base.location = loc;
  new_node->base.print = print_todo;
  new_node->element = identifier;
  new_node->next = NULL;

  if (list == NULL) {
    return (ASTNode *)new_node;
  }
  
  ListNode *current = (ListNode *)list;
  while(current->next != NULL) {
    current = (ListNode *)current->next;
  }

  current->next = (ASTNode *)new_node;

  return list;
};

ASTNode *create_file_of_type_node(ASTNode *type, SourceLocation loc) {
  FileTypeNode *node = (FileTypeNode *)malloc(sizeof(FileTypeNode));
  node->base.type = NODE_FILE_TYPE;
  node->base.location = loc;
  node->base.print = print_todo;
  if (type == NULL) {
    ASTNode *builtin = create_builtin_type_identifier("char", loc);
    ASTNode *simple_type = create_simple_type_node(builtin, loc);
    node->type = simple_type;
  } else {
    node->type = type;
  }
  return (ASTNode *)node;
};
ASTNode *create_field_list(ASTNode *fixed, ASTNode *variant,
                           SourceLocation loc) {
  FieldListNode *node = (FieldListNode*)malloc(sizeof(FieldListNode));
  node->base.type = NODE_FIELD_LIST;
  node->base.location = loc;
  node->base.print = print_todo;
  node->fixed_part = fixed;
  node->variant_part = variant;

  return (ASTNode *)node;
};

ASTNode *create_fixed_part_node(ASTNode *fixed, ASTNode *field,
                                SourceLocation loc) {
  if (field == NULL && fixed != NULL) {
    return fixed;
  }

  ListNode *new_node = (ListNode*)malloc(sizeof(ListNode));
  new_node->base.type = NODE_LIST;
  new_node->base.location = loc;
  new_node->base.print = print_todo;
  new_node->element = field;
  new_node->next = NULL;

  if (fixed == NULL) {
    FixedPartNode *node = (FixedPartNode*)malloc(sizeof(FixedPartNode));
    
    node->base.type = NODE_FIXED_PART;
    node->base.location = loc;
    node->base.print = print_todo;
    node->fields = (ASTNode *)new_node;
    node->field_count = 1;
    
    return (ASTNode*)node;
  }
    
    FixedPartNode *cf = (FixedPartNode *)fixed;
    ListNode *current = (ListNode *)cf->fields;
    while (current->next != NULL) {
      current = (ListNode*)current->next;
    }

    current->next = (ASTNode *)new_node;
    cf->field_count++;
    return (ASTNode*)cf;
};

ASTNode *create_for_stmt_node(ASTNode *variable, ASTNode *for_list,
                              ASTNode *body, SourceLocation loc) {
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
ASTNode *create_for_list_node(ASTNode *start, ASTNode *end, bool is_downto,
                              SourceLocation loc) {
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
                                            SourceLocation loc) {
  if (param == NULL) {
    return list;
  }

  ListNode *new_node = (ListNode*)malloc(sizeof(ListNode));
  new_node->base.type = NODE_LIST;
  new_node->base.location = loc;
  new_node->base.print = print_todo;
  new_node->element = param;
  new_node->next = NULL;

  if (list == NULL) {
    return (ASTNode*)new_node;
  }
    
  ListNode *current = (ListNode *)list;
  while (current->next != NULL) {
    current = (ListNode*)current->next;
  }

  current->next = (ASTNode *)new_node;
  return list;
};

ASTNode *create_function_call_node(ASTNode *func, ASTNode *params,
                                   SourceLocation loc) {
  FunctionCallNode *node =
      (FunctionCallNode *)malloc(sizeof(FunctionCallNode));
  node->base.type = NODE_FUNC_CALL;
  node->base.location = loc;
  node->base.print = print_function_call;
  node->function = func;
  node->params = params; // Pode ser NULL se não houver parâmetros

  if (func->type == NODE_IDENTIFIER) {
    IdentifierNode *id = (IdentifierNode *)func;
    id->kind = SYMBOL_FUNCTION; // Será verificado durante análise semântica
  }

  return (ASTNode *)node;
};

ASTNode *create_goto_label_node(ASTNode *label, SourceLocation loc) {
  GotoNode *node = (GotoNode *)malloc(sizeof(GotoNode));
  node->base.type = NODE_GOTO_STMT;
  node->base.location = loc;
  node->base.print = print_todo;
  node->label = label;
  return (ASTNode *)node;
};

ASTNode *create_if_stmt_node(ASTNode *condition, ASTNode *then_stmt,
                             ASTNode *else_stmt, SourceLocation loc) {
  IfNode *node = (IfNode *)malloc(sizeof(IfNode));
  node->base.type = NODE_IF_STMT;
  node->base.location = loc;
  node->base.print = print_todo;
  node->condition = condition;
  node->then_stmt = then_stmt;
  node->else_stmt = else_stmt;
  return (ASTNode *)node;
};
 
ASTNode *create_index_list_start(ASTNode *first_index, SourceLocation loc) {
  IndexList *new_list = (IndexList *)malloc(sizeof(IndexList));
  new_list->base.type = NODE_INDEX_LIST;
  new_list->base.location = loc;
  new_list->base.print = print_todo;
  new_list->indexes = (ASTNode **)malloc(sizeof(ASTNode**));
  new_list->indexes[0] = first_index;
  new_list->count = 1;
  new_list->capacity = 1;
  return (ASTNode *)new_list;
};

ASTNode *create_label_stmt_node(ASTNode *label, ASTNode *stmt,
                                SourceLocation loc) {
  LabeledStmtNode *node = (LabeledStmtNode *)malloc(sizeof(LabeledStmtNode));
  node->base.type = NODE_LABELED_STMT;
  node->base.location = loc;
  node->base.print = print_todo;
  node->label = label;
  node->statement = stmt;
  return (ASTNode *)node;
}

ASTNode *create_enumerated_type_node(ASTNode *identifiers_list, SourceLocation loc){
  EnumeratedTypeNode *node = (EnumeratedTypeNode*)malloc(sizeof(EnumeratedTypeNode));
  node->base.type = NODE_ENUMERATED_TYPE;
  node->base.location = loc;
  node->base.print = print_todo;
  node->identifiers_list = identifiers_list;
  return (ASTNode *)node;
}

ASTNode *create_packed_type(ASTNode *type, SourceLocation loc) {
  StructuredTypeNode *node = (StructuredTypeNode *)malloc(sizeof(StructuredTypeNode));
  node->base.type = NODE_STRUCTURED_TYPE;
  node->base.location = loc;
  node->base.print = print_todo;
  node->type = type;
  node->is_packed = true;
  return (ASTNode *)node;
};

ASTNode *create_parameter_identifier_list_node(ASTNode *list, ASTNode *element,
                                               SourceLocation loc) {
  if (element == NULL) {
    return list;
  }

  ListNode *new_node = (ListNode*)malloc(sizeof(ListNode));
  new_node->base.type = NODE_LIST;
  new_node->base.location = loc;
  new_node->base.print = print_todo;
  new_node->element = element;
  new_node->next = NULL;

  if (list == NULL) {
    return (ASTNode *)new_node;
  }

  ListNode *current = (ListNode *)list;
  while(current->next != NULL) {
    current = (ListNode*)current->next;
  }

  current->next = (ASTNode*)new_node;
  return list;
};

ASTNode* create_formal_parameter_section_node(ParameterKind kind, ASTNode* identifiers, ASTNode* type,
                                             ASTNode* parameters, ASTNode* return_type, SourceLocation loc) {
  FormalParameterSectionNode* node = (FormalParameterSectionNode*)malloc(sizeof(FormalParameterSectionNode));
  node->base.type = NODE_FORMAL_PARAM_SECTION;
  node->base.location = loc;
  node->base.print = print_todo;
  node->kind = kind;
  node->identifiers = identifiers;
  node->type = type;
  node->parameters = parameters;
  node->return_type = return_type;
  
  return (ASTNode*)node;
}

ASTNode *create_parameters_node(ASTNode *parameters_list, SourceLocation loc) {
  ParameterNode *node = (ParameterNode*)malloc(sizeof(ParameterNode));
  node->base.type = NODE_PARAMETER;
  node->base.location = loc;
  node->base.print = print_todo;
  node->params_list = parameters_list;

  return (ASTNode *)node;
};

ASTNode *create_pointer_type_node(ASTNode *type, SourceLocation loc) {
  PointerTypeNode *node = (PointerTypeNode *)malloc(sizeof(PointerTypeNode));
  node->base.type = NODE_POINTER_TYPE;
  node->base.location = loc;
  node->base.print = print_todo;
  node->type = type;
  return (ASTNode *)node;
};

ASTNode *create_procedure_call_node(ASTNode *proc, ASTNode *params,
                                    SourceLocation loc) {
  ProcedureCallNode *node =
      (ProcedureCallNode *)malloc(sizeof(ProcedureCallNode));
  node->base.type = NODE_PROC_CALL;
  node->base.location = loc;
  node->base.print = print_todo;
  node->procedure = proc;
  node->params = params; // Pode ser NULL se não houver parâmetros

  // Definir o tipo do identificador como procedimento
  if (proc->type == NODE_IDENTIFIER) {
    IdentifierNode *id = (IdentifierNode *)proc;
    id->kind = SYMBOL_PROCEDURE; // Será verificado durante análise semântica
  }

  return (ASTNode *)node;
}

ASTNode *create_record_field_node(ASTNode *field_list, ASTNode *type,
                                  SourceLocation loc) {
  RecordFieldNode *record = (RecordFieldNode*)malloc(sizeof(RecordFieldNode));
  record->base.type = NODE_RECORD_FIELD;
  record->base.location = loc;
  record->base.print = print_todo;
  record->field_list = field_list;
  record->record_type = type;
  
  return (ASTNode *)record;
};

ASTNode *create_record_type_node(ASTNode *field_list, SourceLocation loc) {
  RecordTypeNode *node = (RecordTypeNode *)malloc(sizeof(RecordTypeNode));
  node->base.type = NODE_RECORD_TYPE;
  node->base.location = loc;
  node->base.print = print_todo;
  node->field_list = field_list;
  return (ASTNode *)node;
};

ASTNode *create_repeat_until_stmt_list_node(ASTNode *body, ASTNode *condition,
                                            SourceLocation loc) {
  RepeatUntilNode *node = (RepeatUntilNode *)malloc(sizeof(RepeatUntilNode));
  node->base.type = NODE_REPEAT_STMT;
  node->base.location = loc;
  node->base.print = body->print;
  node->body = body;
  node->condition = condition;
  return (ASTNode *)node;
}

ASTNode *create_set_of_type_node(ASTNode *type, SourceLocation loc) {
  SetTypeNode *node = (SetTypeNode *)malloc(sizeof(SetTypeNode));
  node->base.type = NODE_SET_TYPE;
  node->base.location = loc;
  node->base.print = print_todo;
  node->type = type;
  return (ASTNode *)node;
};
ASTNode *create_simple_type_node(ASTNode *type, SourceLocation loc) {
  SimpleTypeNode *node = (SimpleTypeNode*)malloc(sizeof(SimpleTypeNode));
  node->base.type = NODE_SIMPLE_TYPE;
  node->base.location = loc;
  node->base.print = print_todo;
  node->type = type;

  return (ASTNode *)node;
};

ASTNode *create_structure_type_node(ASTNode *type, SourceLocation loc) {
  StructuredTypeNode *node = (StructuredTypeNode*)malloc(sizeof(StructuredTypeNode));
  node->base.type = NODE_STRUCTURED_TYPE;
  node->base.location = loc;
  node->base.print = print_todo;
  node->type = type;

  return (ASTNode *)node;
};

ASTNode *create_tag_field_node(ASTNode *identifier, ASTNode *type,
                               SourceLocation loc) {
  TagFieldNode *tag = (TagFieldNode *)malloc(sizeof(TagFieldNode));
  tag->base.type = NODE_TAG_FIELD;
  tag->base.location = loc;
  tag->base.print = print_todo;
  tag->field = identifier;
  tag->tag_type = type;

  return (ASTNode *)tag;
};

ASTNode *create_variant_node(ASTNode *label_list, ASTNode *field_list,
                             SourceLocation loc) {
  VariantRecordNode *node = (VariantRecordNode *)malloc(sizeof(VariantRecordNode));
  node->base.type = NODE_VARIANT_RECORD;
  node->base.location = loc;
  node->base.print = print_todo;
  node->case_labels = label_list;
  node->field_list = field_list;

  return (ASTNode *)node;
};

ASTNode *create_while_stmt_node(ASTNode *condition, ASTNode *body,
                                SourceLocation loc) {
  WhileStmtNode *node = (WhileStmtNode *)malloc(sizeof(WhileStmtNode));
  node->base.type = NODE_WHILE_STMT;
  node->base.location = loc;
  node->base.print = print_todo;
  node->condition = condition;
  node->body = body;
  return (ASTNode *)node;
};

ASTNode *create_with_record_list_node(ASTNode *record_list, ASTNode *body,
                                      SourceLocation loc) {
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

  SymbolEntry *s = create_symbol_entry(name, SYMBOL_UNKNOWN, -1, loc);
  const char *key = ht_set(HashTable, s->name, s);

  node->base.type = NODE_IDENTIFIER;
  node->base.location = loc;
  node->base.print = print_identifier_node;
  node->name = strdup(name);
  node->kind = SYMBOL_UNKNOWN;
  node->symbol_entry_key = key;
  return (ASTNode *)node;
};

ASTNode *create_unsigned_integer_node(int integer, SourceLocation loc) {
  LiteralNode *node = (LiteralNode *)malloc(sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_literal_value;
  node->literal_type = LITERAL_INTEGER;
  node->value.int_val = integer;
  return (ASTNode *)node;
}

ASTNode *create_unsigned_real_node(double real, SourceLocation loc) {
  LiteralNode *node = (LiteralNode *)malloc(sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_literal_value;
  node->literal_type = LITERAL_REAL;
  node->value.real_val = real;
  return (ASTNode *)node;
}

ASTNode *create_record_variable_list_node(ASTNode *record_var,
                                          SourceLocation loc) {
  ListNode *node = (ListNode *)malloc(sizeof(ListNode));
  node->base.type = NODE_LIST;
  node->base.location = loc;
  node->base.print = print_todo;
  node->element = record_var;
  node->next = NULL;
  return (ASTNode *)node;
}

ASTNode *append_case_item(ASTNode *list, ASTNode *case_item,
                          SourceLocation loc) {
  if (case_item == NULL) {
    return list;
  }

  ListNode *head = (ListNode *)list;

  if (head) {
    ListNode *cur = head;
    while (cur->next)
      cur = (ListNode *)cur->next;
    cur->next = (ASTNode *)case_item;
    return list;
  } else {
    return case_item;
  }
}

ASTNode *append_case_label_list(ASTNode *list, ASTNode *case_label,
                                SourceLocation loc) {
  if (case_label == NULL) {
    return list;
  }

  ListNode *head = (ListNode *)list;

  if (head) {
    ListNode *cur = head;
    while (cur->next)
      cur = (ListNode *)cur->next;
    cur->next = (ASTNode *)case_label;
    return list;
  } else {
    return case_label;
  }
}

// Adiciona um record à lista de records no with
ASTNode *append_record_variable_list(ASTNode *list, ASTNode *record_var,
                                     SourceLocation loc) {
  if (record_var == NULL) {
    return list;
  }

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
    return list;
  }
    
  return (ASTNode *)new_node;
}

ASTNode *create_expression_list(ASTNode *element,
                                SourceLocation loc) {
  ListNode *node = (ListNode *)malloc(sizeof(ListNode));
  node->base.type = NODE_LIST;
  node->base.location = loc;
  node->base.print = print_todo;
  node->element = element;
  node->next = NULL;
  return (ASTNode *)node;

}

/* APPENDS */
ASTNode *append_expression_list(ASTNode *list, ASTNode *element,
                                SourceLocation loc) {
  if (element == NULL) {
    return list;
  }

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
    return list;
  }

  return (ASTNode *)new_node;
}

ASTNode *append_identifier_list_node(ASTNode *list, ASTNode *element,
                                     SourceLocation loc) {
  if (element == NULL) {
    return list;
  }

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
    return list;
  }

  return (ASTNode *)new_node;
}

ASTNode *append_label_declaration(ASTNode *list, ASTNode *element,
                                  SourceLocation loc) {
  if (element == NULL) {
    return list;
  }

  ListNode *new_node = (ListNode *)create_label_declaration_node(element, loc);

  if (list == NULL) {
    return (ASTNode *)new_node;
  }

  ListNode *current = (ListNode*)list;
  while (current->next != NULL) {
    current = (ListNode *)current->next;
  }

  current->next = (ASTNode *)new_node;
  return list;
}

ASTNode *append_constant_declaration(ASTNode *list, ASTNode *id,
                                     ASTNode *constant, SourceLocation loc) {
  if (id == NULL || constant == NULL) {
    return list;
  }

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
  if (id == NULL || type_expr == NULL) {
    return list;
  }

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
  if (expr == NULL) {
    return list;
  }

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
    return list;
  }

  return (ASTNode *)new_node;
}

ASTNode *append_case_list_node(ASTNode *list, ASTNode *expr,
                               SourceLocation loc) {
  if (expr == NULL) {
    return list;
  }

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
    return list;
  }

  return (ASTNode *)new_node;
}

ASTNode *create_set_literal(SourceLocation loc) {
  SetLiteral *node = (SetLiteral *)malloc(sizeof(SetLiteral));
  node->base.type = NODE_SET_CONSTRUCTOR;
  node->base.location = loc;
  node->base.print = print_todo;
  node->elements = NULL;
  node->capacity = 0;
  node->count = 0;

  return (ASTNode *)node;
}

ASTNode *create_set_literal_with_element(ASTNode *element, SourceLocation loc){
  SetLiteral *node = (SetLiteral *)malloc(sizeof(SetLiteral));
  node->base.type = NODE_SET_CONSTRUCTOR;
  node->base.location = loc;
  node->base.print = print_todo;
  node->elements = (SetElement **)malloc(sizeof(SetElement*));
  node->elements[0] = (SetElement *)element;
  node->capacity = 1;
  node->count = 1;

  return (ASTNode *)node;
}

ASTNode *add_element_to_set_literal(ASTNode* set_literal, ASTNode *element, SourceLocation loc){
  SetLiteral *node = (SetLiteral *)set_literal;
  if (node->count >= node->capacity) {
      node->capacity *= 2;
      node->elements = realloc(
        node->elements, 
        node->capacity * sizeof(ASTNode*)
      );
  }
  node->elements[node->count++] = (SetElement*) element;
  return (ASTNode *)node;
}

ASTNode *create_set_element(ASTNode *expr, SourceLocation loc) {
  SetElement *element = (SetElement *)malloc(sizeof(SetElement));
  element->base.type = NODE_SET_ELEMENT;
  element->base.location = loc;
  element->base.print = print_todo;
  element->type = SET_ELEMENT_SINGLE;
  element->value.single_value = expr;

  return (ASTNode *)element;
}

ASTNode *create_set_range_element(ASTNode* const1, ASTNode *const2, SourceLocation loc) {
  SetElement *element = (SetElement *)malloc(sizeof(SetElement));
  element->base.type = NODE_SET_ELEMENT;
  element->base.location = loc;
  element->base.print = print_todo;
  element->type = SET_ELEMENT_RANGE;
  element->value.range.start = const1;
  element->value.range.end = const2;

  return (ASTNode *)element;
}

ASTNode *append_variable_declaration(ASTNode *list, ASTNode *vars,
                                     ASTNode *type, SourceLocation loc) {
  if (vars == NULL || type == NULL) {
    return list;
  }

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
  if (var_id == NULL) {
    return list;
  }

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
                             SourceLocation loc) {
  if (element == NULL) {
    return list;
  }

  ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
  new_node->base.type = NODE_LIST;
  new_node->base.location = loc;
  new_node->base.print = print_todo;
  new_node->element = element;
  new_node->next = NULL;

  if (list == NULL) {
    VariantListNode *vlist = (VariantListNode *)malloc(sizeof(VariantListNode));
    
    vlist->base.type = NODE_VARIANT_LIST;
    vlist->base.location = loc;
    vlist->base.print = print_todo;
    vlist->variants = (ASTNode *)new_node;
    vlist->variant_count = 1;
    
    return (ASTNode *)vlist;
  }

  VariantListNode *clist = (VariantListNode*)list;
  ListNode *current = (ListNode*) clist->variants;

  while (current->next != NULL) {
    current = (ListNode *)current->next;
  }

  current->next = (ASTNode*) new_node;
  clist->variant_count++;

  return list;
}

ASTNode *append_stmt_list(ASTNode *list, ASTNode *stmt, SourceLocation loc) {
  if (stmt == NULL) {
    return list;
  }

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
  if (proc_and_func == NULL) {
    return list;
  }

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
    return list;
  }

    return (ASTNode *)new_node;
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

ASTNode *append_index_to_list(ASTNode* list, ASTNode* new_index, SourceLocation loc) {
  IndexList *curr_list = (IndexList *)list;
  if (curr_list->count >= curr_list->capacity) {
        curr_list->capacity *= 2;
        curr_list->indexes = realloc(
            curr_list->indexes, 
            curr_list->capacity * sizeof(ASTNode*)
        );
    }
    curr_list->indexes[curr_list->count++] = new_index;
    return list;
}

ASTNode *create_binary_expression(ASTNode *left, BinaryOperator op,
                                    ASTNode *right, SourceLocation loc) {
  BinaryOperationNode *node = (BinaryOperationNode *)malloc(sizeof(BinaryOperationNode));
  node->base.type = NODE_BINARY_EXPR;
  node->base.location = loc;
  node->base.print = print_binary_operation;
  node->left = left;
  node->operator = op;
  node->right = right;

  return (ASTNode*)node;
}
ASTNode *create_unary_expression(UnaryOperator unary_op, ASTNode *operand,
                                 SourceLocation loc) {
  UnaryOperationNode *node = (UnaryOperationNode *)malloc(sizeof(UnaryOperationNode));
  node->base.type = NODE_UNARY_EXPR;
  node->base.location = loc;
  node->base.print = print_unary_operation;
  node->operand = operand;
  node->operator = unary_op;

  return (ASTNode*)node;
}

/* UTILS */

ASTNode *update_identifier_node_kind(ASTNode *id, SymbolKind symb_kind,
                                     bool update_symbol) {
  IdentifierNode *id_node = (IdentifierNode *)id;
  id_node->kind = symb_kind;
  if (update_symbol) {
    SymbolEntry *symb = ht_get(HashTable, id_node->symbol_entry_key);
    symb->kind = symb_kind;
    ht_set(HashTable, symb->name, symb);
  }

  return (ASTNode *)id_node;
}

ASTNode *get_statements_from_block(ASTNode *block) {
  if (!block)
    return NULL;
  return ((BlockNode *)block)->statements;
}

const char* binary_op_to_string(BinaryOperator op) {
    switch (op) {
        case BINOP_LT: return "<";
        case BINOP_LTE: return "<=";
        case BINOP_EQ: return "=";
        case BINOP_NEQ: return "<>";
        case BINOP_GTE: return ">=";
        case BINOP_GT: return ">";
        case BINOP_PLUS: return "+";
        case BINOP_MINUS: return "-";
        case BINOP_OR: return "or";
        case BINOP_TIMES: return "*";
        case BINOP_DIVIDE: return "/";
        case BINOP_DIV: return "div";
        case BINOP_MOD: return "mod";
        case BINOP_AND: return "and";
        case BINOP_IN: return "in";
        default: return "unknown";
    }
}

const char* unary_op_to_string(UnaryOperator op) {
    switch (op) {
        case UNOP_PLUS: return "+";
        case UNOP_MINUS: return "-";
        case UNOP_NOT: return "not";
        default: return "unknown";
    }
}

const char* nodeTypeToString(NodeType type) {
    switch (type) {
      case NODE_PROGRAM: return "NODE_PROGRAM";
      case NODE_HEADING: return "NODE_HEADING";
      case NODE_BLOCK: return "NODE_BLOCK";
      case NODE_USES: return "NODE_USES";

      case NODE_LABEL_DECL: return "NODE_LABEL_DECL";
      case NODE_CONST_DECL: return "NODE_CONST_DECL";
      case NODE_TYPE_DECL: return "NODE_TYPE_DECL";
      case NODE_VAR_DECL: return "NODE_VAR_DECL";
      case NODE_PROC_DECL: return "NODE_PROC_DECL";
      case NODE_FUNC_DECL: return "NODE_FUNC_DECL";
      case NODE_FORWARD_DECL: return "NODE_FORWARD_DECL";

      case NODE_ENUMERATED_TYPE: return "NODE_ENUMERATED_TYPE";
      case NODE_SUBRANGE_TYPE: return "NODE_SUBRANGE_TYPE";
      case NODE_TYPE_IDENTIFIER: return "NODE_TYPE_IDENTIFIER";
      case NODE_STRUCTURED_TYPE: return "NODE_STRUCTURED_TYPE";
      case NODE_SIMPLE_TYPE: return "NODE_SIMPLE_TYPE";
      case NODE_ARRAY_TYPE: return "NODE_ARRAY_TYPE";
      case NODE_RECORD_TYPE: return "NODE_RECORD_TYPE";
      case NODE_SET_TYPE: return "NODE_SET_TYPE";
      case NODE_FILE_TYPE: return "NODE_FILE_TYPE";
      case NODE_POINTER_TYPE: return "NODE_POINTER_TYPE";
      case NODE_POINTER_DEREF: return "NODE_POINTER_DEREF";

      case NODE_COMPOUND_STMT: return "NODE_COMPOUND_STMT";
      case NODE_ASSIGN_STMT: return "NODE_ASSIGN_STMT";
      case NODE_PROC_CALL: return "NODE_PROC_CALL";
      case NODE_IF_STMT: return "NODE_IF_STMT";
      case NODE_CASE_STMT: return "NODE_CASE_STMT";
      case NODE_CASE_ITEM: return "NODE_CASE_ITEM";
      case NODE_CASE_LABEL: return "NODE_CASE_LABEL";
      case NODE_CASE_ELSE: return "NODE_CASE_ELSE";
      case NODE_WHILE_STMT: return "NODE_WHILE_STMT";
      case NODE_REPEAT_STMT: return "NODE_REPEAT_STMT";
      case NODE_FOR_STMT: return "NODE_FOR_STMT";
      case NODE_FOR_LIST: return "NODE_FOR_LIST";
      case NODE_WITH_STMT: return "NODE_WITH_STMT";
      case NODE_GOTO_STMT: return "NODE_GOTO_STMT";
      case NODE_LABELED_STMT: return "NODE_LABELED_STMT";

      case NODE_BINARY_EXPR: return "NODE_BINARY_EXPR";
      case NODE_UNARY_EXPR: return "NODE_UNARY_EXPR";
      case NODE_LITERAL: return "NODE_LITERAL";
      case NODE_IDENTIFIER: return "NODE_IDENTIFIER";
      case NODE_MEMBER_ACCESS: return "NODE_MEMBER_ACCESS";
      case NODE_ARRAY_ACCESS: return "NODE_ARRAY_ACCESS";
      case NODE_FUNC_CALL: return "NODE_FUNC_CALL";
      case NODE_SET_CONSTRUCTOR: return "NODE_SET_CONSTRUCTOR";
      case NODE_CONST_IDENTIFIER: return "NODE_CONST_IDENTIFIER";

      case NODE_FIELD_LIST: return "NODE_FIELD_LIST";
      case NODE_RECORD_FIELD: return "NODE_RECORD_FIELD";
      case NODE_INDEX_LIST: return "NODE_INDEX_LIST";
      case NODE_PARAMETER: return "NODE_PARAMETER";
      case NODE_VARIANT_RECORD: return "NODE_VARIANT_RECORD";
      case NODE_VARIANT_LIST: return "NODE_VARIANT_LIST";
      case NODE_VARIANT_PART: return "NODE_VARIANT_PART";
      case NODE_TAG_FIELD: return "NODE_TAG_FIELD";
      case NODE_FIXED_PART: return "NODE_FIXED_PART";
      case NODE_FORMAL_PARAM_SECTION: return "NODE_FORMAL_PARAM_SECTION";
      case NODE_LIST: return "NODE_LIST";
      case NODE_ERROR: return "NODE_ERROR";
      case NODE_OPERATION: return "NODE_OPERATION";
      case NODE_SET_ELEMENT: return "NODE_SET_ELEMENT";

      default: return "UNKNOWN_NODETYPE";
    }
}

void print_todo(ASTNode *node, int indent) {
  printf("%*sTODO %s\n", indent, "", nodeTypeToString(node->type));
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
  case NODE_ENUMERATED_TYPE: {
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
    printf("NODE_PROC_CALL id: %d", NODE_PROC_CALL);
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
    printf("NODE_FUNC_CALL id: %d", NODE_FUNC_CALL);
    break;
  }
  case NODE_SET_CONSTRUCTOR: {
    break;
  }
  case NODE_FORWARD_DECL:
  case NODE_SIMPLE_TYPE:
  case NODE_CASE_LABEL:
  case NODE_FOR_LIST:
  case NODE_LABELED_STMT:
  case NODE_CONST_IDENTIFIER:
  case NODE_RECORD_FIELD:
  case NODE_INDEX_LIST:
  case NODE_VARIANT_LIST:
  case NODE_VARIANT_PART:
  case NODE_TAG_FIELD:
  case NODE_FIXED_PART:
  case NODE_FORMAL_PARAM_SECTION:
  case NODE_OPERATION:
  case NODE_SET_ELEMENT:
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
