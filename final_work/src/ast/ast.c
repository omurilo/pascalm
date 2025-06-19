#include "ast.h"
#include <string.h>
#include <assert.h>
#include "../logger.h"

SourceLocation create_location(YYLTYPE loc) {
  SourceLocation result;
  result.first_line = loc.first_line;
  result.first_column = loc.first_column;
  result.last_line = loc.last_line;
  result.last_column = loc.last_column;
  result.file_name = strdup(yylloc.file_name);
  return result;
}

char *debug_location(SourceLocation loc) {
  char buffer[100];
  sprintf(buffer, "%d.%d-%d.%d", loc.first_line, loc.first_column,
          loc.last_line, loc.last_column);
  return strdup(buffer);
};

void print_program_node(ASTNode *node, int indent) {
  ProgramNode *prog = (ProgramNode *)node;
  fprintf(stderr, "%*sProgram: %s - at: %s [%s]\n", indent, "", prog->name,
          debug_location(prog->base.location), prog->base.location.file_name);
  if (prog->heading != NULL) {
    prog->heading->print(prog->heading, indent += 2);
  }
  if (prog->block != NULL) {
    prog->block->print(prog->block, indent += 2);
  }
}

void print_heading(ASTNode *node, int indent) {
  HeadingNode *h = (HeadingNode *)node;
  fprintf(stderr, "%*sHeading parameters: (", indent, "");
  ListNode *current = (ListNode *)h->list;
  int first = 1;

  while (current) {
    if (current->element) {
      IdentifierNode *id = (IdentifierNode *)current->element;
      if (!first)
        fprintf(stderr, ", ");
      fprintf(stderr, "%s", id->name);
      first = 0;
    } else {
      fprintf(stderr, "[NULL]");
    }
    current = (ListNode *)current->next;
  }
  fprintf(stderr, ")\n");
}

void print_list_identifiers(ASTNode *node, int indent) {
  ListNode *current = (ListNode *)node;

  while (current) {
    if (current->element) {
      switch (current->element->type) {
      case NODE_FUNC_DECL: {
        FuncDeclarationNode *fd = (FuncDeclarationNode *)current->element;
        fd->identifier->print(fd->identifier, indent);
        break;
      }
      case NODE_PROC_DECL: {
        FuncDeclarationNode *pd = (FuncDeclarationNode *)current->element;
        pd->identifier->print(pd->identifier, indent);
        break;
      }
      case NODE_TYPE_DECL: {
        // current->element->print(current->element, indent);
        TypeDeclarationNode *td = (TypeDeclarationNode *)current->element;
        td->identifier->print(td->identifier, indent);
        td->type_expr->print(td->type_expr, indent);
        break;
      }
      case NODE_CONST_DECL: {
        ConstDeclarationNode *cd = (ConstDeclarationNode *)current->element;
        cd->identifier->print(cd->identifier, indent);
        break;
      }
      case NODE_IDENTIFIER: {
        current->element->print(current->element, indent);
        break;
      }
      default: {
        fprintf(stderr, "%*sUnknown Identifier Type %s\n", indent, "",
                get_node_type_name(current->element->type));
        break;
      }
      }
    } else {
      fprintf(stderr, "%*sprint_list_identifiers: [NULL]\n", indent, "");
    }
    current = (ListNode *)current->next;
  }
}

void print_literal_value(ASTNode *node, int indent) {
  if (node->type != NODE_LITERAL) {
    fprintf(stderr, "%*s[WARNING] try print literal value from type: %s\n",
            indent, "", get_node_type_name(node->type));
    return;
  };

  LiteralNode *lit = (LiteralNode *)node;
  if (lit->literal_type == LITERAL_STRING) {
    fprintf(stderr, "%*sLiteral %s\n", indent, "", lit->value.str_val);
  } else if (lit->literal_type == LITERAL_INTEGER) {
    fprintf(stderr, "%*sLiteral %d\n", indent, "", lit->value.int_val);
  } else if (lit->literal_type == LITERAL_REAL) {
    fprintf(stderr, "%*sLiteral %.2f\n", indent, "", lit->value.real_val);
  } else if (lit->literal_type == LITERAL_BOOLEAN) {
    fprintf(stderr, "%*sLiteral %s\n", indent, "",
            lit->value.bool_val ? "true" : "false");
  } else if (lit->literal_type == LITERAL_CHAR) {
    fprintf(stderr, "%*sLiteral %c\n", indent, "", lit->value.char_val);
  }
}

void print_types(ASTNode *node, int indent) {
  switch (node->type) {
  case NODE_STRUCTURED_TYPE: {
    StructuredTypeNode *s = (StructuredTypeNode *)node;
    print_types(s->type, indent);
    break;
  }
  case NODE_SIMPLE_TYPE: {
    SimpleTypeNode *s = (SimpleTypeNode *)node;
    print_types(s->type, indent);
    break;
  }
  case NODE_POINTER_TYPE: {
    print_types(node, indent);
    break;
  }
  case NODE_ARRAY_TYPE: {
    ArrayTypeNode *arr = (ArrayTypeNode *)node;
    print_types(arr->type, indent);
    break;
  }
  case NODE_RECORD_TYPE: {
    RecordTypeNode *rt = (RecordTypeNode *)node;
    print_stmt_list(rt->field_list, indent + 2);
    print_stmt_list(rt->variant_part, indent + 2);
    break;
  }
  case NODE_ENUMERATED_TYPE:
    break;
  case NODE_SUBRANGE_TYPE:
    break;
  case NODE_SET_TYPE: {
    SetTypeNode *st = (SetTypeNode *)node;
    print_types(st->type, indent);
    break;
  }
  case NODE_TYPE_IDENTIFIER: {
    TypeIdentifierNode *tid = (TypeIdentifierNode *)node;
    IdentifierNode *id = (IdentifierNode *)tid->id;
    fprintf(stderr, "%*s Type name: %s\n", indent, "", id->name);
    break;
  }
  case NODE_FILE_TYPE:
  default:
    fprintf(stderr, "%*s[WARNING] try print literal value from type: %s\n",
            indent, "", get_node_type_name(node->type));
    break;
  }
}

void print_list_values(ASTNode *node, int indent) {
  ListNode *current = (ListNode *)node;

  while (current) {
    if (current->element) {
      if (current->element->type == NODE_LITERAL) {
        print_literal_value(current->element, indent);
      } else if (current->element->type == NODE_LABEL_DECL) {
        LabelDeclarationNode *d = (LabelDeclarationNode *)current->element;
        print_literal_value(d->value, indent);
      } else {
        fprintf(stderr, "%*s(print_list_values) Unknown type: %s\n", indent, "",
                get_node_type_name(current->element->type));
      }
    } else {
      fprintf(stderr, "%*sprint_list_values [NULL]\n", indent, "");
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
      fprintf(stderr, "%*s(", indent, "");
      int first = 1;
      while (new_curr) {
        if (new_curr->element) {
          IdentifierNode *id = (IdentifierNode *)new_curr->element;
          if (first > 1) {
            fprintf(stderr, ", ");
          }
          fprintf(stderr, "%s", id->name);
        } else {
          fprintf(stderr, "%*sprint_variable_declaration [NULL]\n", indent, "");
        }
        first += 1;
        new_curr = (ListNode *)new_curr->next;
      }
      fprintf(stderr, ")\n");
    } else {
      fprintf(stderr, "%*sprint_variable_declaration [NULL]\n", indent, "");
    }
    current = (ListNode *)current->next;
  }
}

void debug_lists(ListNode *node, int indent) {
  if (node->base.type != NODE_LIST) {
    fprintf(
        stderr,
        "%*s[WARNING] Attempt to print list node with type %s, location: %s\n",
        indent + 4, "", get_node_type_name(node->base.type),
        debug_location(node->base.location));
    return;
  }
  fprintf(stderr, "%*sTypes: %s - location: %s\n", indent + 4, "",
          get_node_type_name(node->base.type),
          debug_location(node->base.location));
  while (node) {
    if (node->element) {
      fprintf(stderr, "%*sElement: %s - location: %s\n", indent + 4, "",
              get_node_type_name(node->element->type),
              debug_location(node->element->location));
      debug_lists((ListNode *)node->element, indent + 5);
    }
    if (node->next) {
      fprintf(stderr, "%*sNext: %s - location: %s\n", indent + 4, "",
              get_node_type_name(node->next->type),
              debug_location(node->next->location));
      debug_lists((ListNode *)node->next, indent + 10);
    }
    node = (ListNode *)node->next;
  }
}

void print_block(ASTNode *node, int indent) {
  BlockNode *block = (BlockNode *)node;
  fprintf(stderr, "%*sBlock:\n", indent, "");

  if (block->labels != NULL) {
    fprintf(stderr, "%*sLabels: \n", indent + 2, "");
    block->labels->print(block->labels, indent + 4);
  }
  if (block->constants != NULL) {
    fprintf(stderr, "%*sConstants: \n", indent + 2, "");
    block->constants->print(block->constants, indent + 4);
  }
  if (block->types != NULL) {
    fprintf(stderr, "%*sTypes: \n", indent + 2, "");
    block->types->print(block->types, indent + 4);
  }
  if (block->variables != NULL) {
    fprintf(stderr, "%*sVariables: \n", indent + 2, "");
    block->variables->print(block->variables, indent + 4);
  }
  if (block->procs_funcs != NULL) {
    fprintf(stderr, "%*sProcedures e Functions: \n", indent + 2, "");
    block->procs_funcs->print(block->procs_funcs, indent + 4);
  }
  if (block->statements != NULL) {
    fprintf(stderr, "%*sStatements: \n", indent + 2, "");
    block->statements->print(block->statements, indent + 4);
  }
}

void print_stmt_list(ASTNode *node, int indent) {
  ListNode *current = (ListNode *)node;

  while (current) {
    if (current->element) {
      switch (current->element->type) {
      case NODE_COMPOUND_STMT: {
        fprintf(stderr, "%*sNODE_COMPOUND_STMT-> (%s)\n", indent, "",
                debug_location(current->element->location));
        current->element->print(current->element, indent + 2);
        break;
      }
      case NODE_ASSIGN_STMT: {
        fprintf(stderr, "%*sNODE_ASSIGN_STMT-> (%s)\n", indent, "",
                debug_location(current->element->location));
        AssignmentNode *a = (AssignmentNode *)current->element;
        if (a->target->type == NODE_IDENTIFIER) {
          a->target->print(a->target, indent + 2);
        }
        a->expression->print(a->expression, indent + 2);
        break;
      }
      case NODE_PROC_CALL: {
        fprintf(stderr, "%*sNODE_PROC_CALL-> (%s)\n", indent, "",
                debug_location(current->element->location));
        FunctionCallNode *proc = (FunctionCallNode *)current->element;
        if (proc->function->type == NODE_IDENTIFIER) {
          proc->function->print(proc->function, indent + 2);
          break;
        }
        proc->base.print((ASTNode *)proc, indent + 2);
        break;
      }
      case NODE_IF_STMT: {
        fprintf(stderr, "%*sNODE_IF_STMT-> (%s)\n", indent, "",
                debug_location(current->element->location));
        current->element->print(current->element, indent + 2);
        break;
      }
      case NODE_CASE_STMT: {
        fprintf(stderr, "%*sNODE_CASE_STMT-> (%s)\n", indent, "",
                debug_location(current->element->location));
        current->element->print(current->element, indent + 2);
        break;
      }
      case NODE_CASE_ITEM: {
        fprintf(stderr, "%*sNODE_CASE_ITEM-> (%s)\n", indent, "",
                debug_location(current->element->location));
        current->element->print(current->element, indent + 2);
        break;
      }
      case NODE_CASE_ELSE: {
        fprintf(stderr, "%*sNODE_CASE_ELSE-> (%s)\n", indent, "",
                debug_location(current->element->location));
        current->element->print(current->element, indent + 2);
        break;
      }
      case NODE_WHILE_STMT: {
        fprintf(stderr, "%*sNODE_WHILE-> (%s)\n", indent, "",
                debug_location(current->element->location));
        WhileStmtNode *w = (WhileStmtNode *)current->element;
        print_stmt_list(w->body, indent + 2);
        break;
      }
      case NODE_REPEAT_STMT: {
        fprintf(stderr, "%*sNODE_REPEAT-> (%s)\n", indent, "",
                debug_location(current->element->location));
        RepeatUntilNode *r = (RepeatUntilNode *)current->element;
        print_stmt_list(r->body, indent + 2);
        break;
      }
      case NODE_FOR_STMT: {
        fprintf(stderr, "%*sNODE_FOR-> (%s)\n", indent, "",
                debug_location(current->element->location));
        ForStmtNode *ft = (ForStmtNode *)current->element;
        if (ft->variable->type == NODE_IDENTIFIER) {
          ft->variable->print(ft->variable, indent + 2);
        }
        fprintf(stderr, "%*sNODE_FOR_LIST-> (%s)\n", indent + 2, "",
                ft->is_downto ? "downto" : "to");
        fprintf(stderr, "%*sStart Expression\n", indent + 4, "");
        ft->start_expr->print(ft->start_expr, indent + 6);
        fprintf(stderr, "%*sEnd Expression\n", indent + 4, "");
        ft->end_expr->print(ft->end_expr, indent + 6);
        fprintf(stderr, "%*sBody\n", indent + 4, "");
        print_stmt_list(ft->body, indent + 6);
        break;
      }
      case NODE_WITH_STMT: {
        fprintf(stderr, "%*sNODE_WITH-> (%s)\n", indent, "",
                debug_location(current->element->location));
        current->element->print(current->element, indent + 2);
        break;
      }
      case NODE_GOTO_STMT: {
        fprintf(stderr, "%*sNODE_GOTO-> (%s)\n", indent, "",
                debug_location(current->element->location));
        current->element->print(current->element, indent + 2);
        break;
      }
      case NODE_IDENTIFIER: {
        fprintf(stderr, "%*sNODE_IDENTIFIER-> (%s)\n", indent, "",
                debug_location(current->element->location));
        current->element->print(current->element, indent + 2);
        break;
      }
      case NODE_LIST: {
        fprintf(stderr, "%*sNODE_LIST-> (%s)\n", indent, "",
                debug_location(current->element->location));
        print_stmt_list(current->element, indent + 2);
        break;
      }
      case NODE_BINARY_EXPR: {
        fprintf(stderr, "%*sNODE_BINARY_EXPR-> (%s)\n", indent, "",
                debug_location(current->element->location));
        print_binary_operation(current->element, indent + 2);
        break;
      }
      case NODE_LITERAL: {
        fprintf(stderr, "%*sNODE_LITERAL -> (%s)\n", indent, "",
                debug_location(current->element->location));
        print_literal_value(current->element, indent + 2);
        break;
      }
      case NODE_RECORD_FIELD: {
        RecordFieldNode *rf = (RecordFieldNode *)current->element;
        print_types(rf->record_type, indent + 2);
        break;
      }
      case NODE_FIXED_PART: {
        FixedPartNode *fp = (FixedPartNode *)current->element;
        fprintf(stderr, "%*sNODE_FIXED_PART -> (%s)\n", indent, "",
                debug_location(current->element->location));
        print_stmt_list(fp->fields, indent);
        break;
      }
      default:
        fprintf(stderr, "%*sNode Type %s (%s)\n", indent, "",
                get_node_type_name(current->element->type),
                debug_location(current->element->location));
        break;
      }
    } else {
      if (current->next) {
        fprintf(stderr, "%*s Element (null) but next -> %s (%s)\n", indent, "",
                get_node_type_name(current->next->type),
                debug_location(current->next->location));
      }
      fprintf(stderr, "%*sElement (null), current type: %s (%s)\n", indent, "",
              get_node_type_name(current->base.type),
              debug_location(current->element->location));
    }
    current = (ListNode *)current->next;
  }
}

void print_type_identifier_node(ASTNode *node, int indent) {
  if (node->type != NODE_TYPE_IDENTIFIER) {
    fprintf(stderr,
            "WARN: Tentou imprimir NODE_TYPE_IDENTIFIER, mas o tipo é %s!\n",
            get_node_type_name(node->type));
  }

  TypeIdentifierNode *tid = (TypeIdentifierNode *)node;
  tid->id->base.print((ASTNode *)tid->id, indent);
}

void print_identifier_node(ASTNode *node, int indent) {
  if (node->type != NODE_IDENTIFIER) {
    fprintf(stderr, "WARN: Tentou imprimir NODE_IDENTIFIER, mas o tipo é %s!\n",
            get_node_type_name(node->type));
  }

  IdentifierNode *id = (IdentifierNode *)node;
  if (id->name != NULL) {
    fprintf(stderr, "%*sIdentifier: %s\n", indent, "", id->name);
  } else {
    fprintf(stderr, "%*sIdentifier: <unnamed>\n", indent, "");
  }
}

void print_constant_identifier_node(ASTNode *node, int indent) {
  if (node->type != NODE_CONSTANT) {
    fprintf(stderr, "WARN: Tentou imprimir NODE_CONSTANT, mas o tipo é %s!\n",
            get_node_type_name(node->type));
  }

  ConstantNode *constant = (ConstantNode *)node;
  if (constant->identifier != NULL) {
    constant->identifier->print(constant->identifier, indent);
  } else if (constant->value != NULL) {
    constant->value->print(constant->value, indent);
  }
}

void print_member_access_node(ASTNode *node, int indent) {
  if (node->type != NODE_MEMBER_ACCESS) {
    fprintf(stderr,
            "WARN: Tentou imprimir NODE_MEMBER_ACCESS, mas o tipo é %s!\n",
            get_node_type_name(node->type));
  }

  MemberAccessNode *mnode = (MemberAccessNode *)node;
  fprintf(stderr, "%*sMember Access -> Record:\n", indent, "");
  mnode->record->print(mnode->record, indent + 2);
  fprintf(stderr, "%*sMember Access -> Field:\n", indent, "");
  mnode->field->print(mnode->field, indent + 2);
}

void print_array_access_node(ASTNode *node, int indent) {
  if (node->type != NODE_ARRAY_ACCESS) {
    fprintf(stderr,
            "WARN: Tentou imprimir NODE_ARRAY_ACCESS, mas o tipo é %s!\n",
            get_node_type_name(node->type));
  }

  ArrayAccessNode *anode = (ArrayAccessNode *)node;
  anode->array->print(anode->array, indent);
  fprintf(stderr, "%*sIndexes List:\n", indent + 2, "");
  anode->subscript_list->print(anode->subscript_list, indent + 4);
}

void print_case_stmt_node(ASTNode *node, int indent) {
  if (node->type != NODE_CASE_STMT) {
    fprintf(stderr, "WARN: Tentou imprimir NODE_CASE_STMT, mas o tipo é %s!\n",
            get_node_type_name(node->type));
  }

  CaseNode *cnode = (CaseNode *)node;
  fprintf(stderr, "%*sExpression:\n", indent + 2, "");
  cnode->expr->print(cnode->expr, indent + 4);
  fprintf(stderr, "%*sCase List:\n", indent + 2, "");
  cnode->case_list->print(cnode->case_list, indent + 4);
  if (cnode->else_part != NULL) {
    fprintf(stderr, "%*sElse:\n", indent + 2, "");
    cnode->else_part->print(cnode->else_part, indent + 4);
  }
}

void print_binary_operation(ASTNode *node, int indent) {
  BinaryOperationNode *expr = (BinaryOperationNode *)node;
  fprintf(stderr, "%*sBinary Expression (op: %s)\n", indent, "",
          binary_op_to_string(expr->op));
  if (expr->left) {
    fprintf(stderr, "%*sLeft:\n", indent + 2, "");
    expr->left->print(expr->left, indent + 4);
  }
  if (expr->right) {
    fprintf(stderr, "%*sRight:\n", indent + 2, "");
    expr->right->print(expr->right, indent + 4);
  }
}

void print_unary_operation(ASTNode *node, int indent) {
  UnaryOperationNode *expr = (UnaryOperationNode *)node;
  fprintf(stderr, "%*sUnary Expression (op: %s)\n", indent, "",
          unary_op_to_string(expr->op));
  if (expr->operand) {
    expr->operand->print(expr->operand, indent + 2);
  }
}

void print_function_call(ASTNode *node, int indent) {
  FunctionCallNode *fc = (FunctionCallNode *)node;
  fprintf(stderr, "%*sNODE_FUNC_CALL->\n", indent, "");
  print_identifier_node(fc->function, indent + 2);
  // fc->params->print(fc->params, indent);
  fprintf(stderr, "%*sFUNC_CALL_PARAMS->\n", indent + 2, "");
  print_stmt_list(fc->params, indent + 4);
}

ASTNode *create_program_node(char *name, ASTNode *heading, ASTNode *block,
                             SourceLocation loc) {
  ProgramNode *node = calloc(1, sizeof(ProgramNode));
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
  BlockNode *node = calloc(1, sizeof(BlockNode));
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
  HeadingNode *node = calloc(1, sizeof(HeadingNode));
  node->base.type = NODE_HEADING;
  node->base.location = loc;
  node->base.print = print_heading;
  node->list = list;
  return (ASTNode *)node;
}

ASTNode *create_label_declaration_node(ASTNode *value, SourceLocation loc) {
  LabelDeclarationNode *node = calloc(1, sizeof(LabelDeclarationNode));
  node->base.type = NODE_LABEL_DECL;
  node->base.location = loc;
  node->base.print = print_todo;
  node->value = value;

  ListNode *list = calloc(1, sizeof(ListNode));
  list->base.type = NODE_LIST;
  list->base.location = loc;
  list->base.print = print_list_values;
  list->element = (ASTNode *)node;
  list->next = NULL;

  return (ASTNode *)list;
}

ASTNode *create_constant_declaration_node(ASTNode *identifier,
                                          ASTNode *constant,
                                          SourceLocation loc) {
  ConstDeclarationNode *node = calloc(1, sizeof(ConstDeclarationNode));
  node->base.type = NODE_CONST_DECL;
  node->base.location = loc;
  node->base.print = print_todo;
  node->identifier = identifier;
  node->const_expr = constant;

  ListNode *list = calloc(1, sizeof(ListNode));
  list->base.type = NODE_LIST;
  list->base.location = loc;
  list->base.print = print_list_identifiers;
  list->element = (ASTNode *)node;
  list->next = NULL;

  return (ASTNode *)list;
}

ASTNode *create_type_declaration_node(ASTNode *identifier, ASTNode *type,
                                      SourceLocation loc) {
  TypeDeclarationNode *node = calloc(1, sizeof(TypeDeclarationNode));
  node->base.type = NODE_TYPE_DECL;
  node->base.location = loc;
  node->base.print = print_list_identifiers;
  node->identifier = identifier;
  node->type_expr = type;

  ListNode *list = calloc(1, sizeof(ListNode));
  list->base.type = NODE_LIST;
  list->base.location = loc;
  list->base.print = print_list_identifiers;
  list->element = (ASTNode *)node;
  list->next = NULL;

  return (ASTNode *)list;
}

ASTNode *create_type_identifier(ASTNode *id, SourceLocation loc) {
  TypeIdentifierNode *typeid = calloc(1, sizeof(TypeIdentifierNode));
  typeid->base.type = NODE_TYPE_IDENTIFIER;
  typeid->base.location = loc;
  typeid->base.print = print_type_identifier_node;
  typeid->id = (IdentifierNode *)id;
  typeid->kind = SYMBOL_TYPE;
  typeid->is_base_type = false;

  return (ASTNode *)typeid;
}

ASTNode *create_builtin_type_identifier(char *name, SourceLocation loc) {
  TypeIdentifierNode *typeid = calloc(1, sizeof(TypeIdentifierNode));
  typeid->base.type = NODE_TYPE_IDENTIFIER;
  typeid->base.location = loc;
  typeid->base.print = print_type_identifier_node;
  typeid->kind = SYMBOL_BUILTIN;

  IdentifierNode *id = (IdentifierNode*)create_identifier_node(strdup(name), loc);
  id->kind = SYMBOL_BUILTIN;

  typeid->id = id;
  typeid->is_base_type = true;

  return (ASTNode *)typeid;
}

ASTNode *create_builtin_identifier(char *name, SourceLocation loc) {
  IdentifierNode *built = calloc(1, sizeof(IdentifierNode));
  built->base.type = NODE_IDENTIFIER;
  built->base.location = loc;
  built->base.print = print_identifier_node;
  built->name = strdup(name);
  built->kind = SYMBOL_BUILTIN;

  return (ASTNode *)built;
}

ASTNode *create_identifier_list_node(ASTNode *element, SourceLocation loc) {
  ListNode *node = calloc(1, sizeof(ListNode));
  node->base.type = NODE_LIST;
  node->base.location = loc;
  node->base.print = print_list_identifiers;
  node->element = element;
  node->next = NULL;
  return (ASTNode *)node;
}

ASTNode *create_case_stmt_node(ASTNode *expr, ASTNode *case_list,
                               ASTNode *else_part, SourceLocation loc) {
  CaseNode *node = calloc(1, sizeof(CaseNode));
  node->base.type = NODE_CASE_STMT;
  node->base.location = loc;
  node->base.print = print_case_stmt_node;
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
  ListNode *list = calloc(1, sizeof(ListNode));
  list->base.type = NODE_LIST;
  list->base.location = loc;
  list->base.print = print_list_identifiers;
  list->element = element;
  list->next = NULL;
  return (ASTNode *)list;
}

ASTNode *create_case_item_node(ASTNode *value_list, ASTNode *stmt,
                               SourceLocation loc) {
  CaseItemNode *node = calloc(1, sizeof(CaseItemNode));
  node->base.type = NODE_CASE_ITEM;
  node->base.location = loc;
  node->base.print = print_todo;
  node->value_list = value_list;
  node->statement = stmt;

  ListNode *list = calloc(1, sizeof(ListNode));
  list->base.type = NODE_LIST;
  list->base.location = loc;
  list->base.print = print_list_identifiers;
  list->element = (ASTNode *)node;
  list->next = NULL;
  return (ASTNode *)list;
}

ASTNode *create_case_else_node(ASTNode *stmt, SourceLocation loc) {
  CaseElseNode *node = calloc(1, sizeof(CaseElseNode));
  node->base.type = NODE_CASE_ELSE;
  node->base.location = loc;
  node->base.print = print_todo;
  node->stmt = stmt;
  return (ASTNode *)node;
};

ASTNode *create_case_label_list(ASTNode *case_label, SourceLocation loc) {
  ListNode *new_list = calloc(1, sizeof(ListNode));
  new_list->base.type = NODE_LIST;
  new_list->base.location = loc;
  new_list->base.print = print_list_identifiers;
  new_list->element = case_label;
  new_list->next = NULL;
  return (ASTNode *)new_list;
}

ASTNode *create_constant_range_node(ASTNode *constant1, ASTNode *constant2,
                                    SourceLocation loc) {
  // TODO: In a semantic analysis, the type of lower and upper must be equal
  SubrangeTypeNode *node = calloc(1, sizeof(SubrangeTypeNode));
  node->base.type = NODE_SUBRANGE_TYPE;
  node->base.location = loc;
  node->base.print = print_todo;
  node->lower = constant1;
  node->upper = constant2;

  return (ASTNode *)node;
}

ASTNode *create_array_access_node(ASTNode *array, ASTNode *subscripts,
                                  SourceLocation loc) {
  ArrayAccessNode *node = calloc(1, sizeof(ArrayAccessNode));
  node->base.type = NODE_ARRAY_ACCESS;
  node->base.location = loc;
  node->base.print = print_array_access_node;
  node->array = array;
  node->subscript_list = subscripts;
  return (ASTNode *)node;
}

ASTNode *create_record_access_node(ASTNode *record, ASTNode *field,
                                   SourceLocation loc) {
  // TODO: verificar se existe antes de acessar
  MemberAccessNode *node = calloc(1, sizeof(MemberAccessNode));
  node->base.type = NODE_MEMBER_ACCESS;
  node->base.location = loc;
  node->base.print = print_member_access_node;
  node->record = record;
  node->field = field;

  return (ASTNode *)node;
}

ASTNode *create_pointer_deref_node(ASTNode *pointer, SourceLocation loc) {
  PointerDerefNode *node = calloc(1, sizeof(PointerDerefNode));
  node->base.type = NODE_POINTER_DEREF;
  node->base.location = loc;
  node->base.print = print_todo;
  node->pointer = pointer;
  return (ASTNode *)node;
}

ASTNode *create_subscript_list_node(ASTNode *expr, SourceLocation loc) {
  ListNode *node = calloc(1, sizeof(ListNode));
  node->base.type = NODE_LIST;
  node->base.location = loc;
  node->base.print = print_list_identifiers;
  node->element = expr;
  node->next = NULL;
  return (ASTNode *)node;
};

ASTNode *create_variable_declaration_node(ASTNode *list, ASTNode *type,
                                          SourceLocation loc) {
  VarDeclarationNode *decl = calloc(1, sizeof(VarDeclarationNode));
  decl->base.type = NODE_VAR_DECL;
  decl->base.location = loc;
  decl->base.print = print_variable_declaration;
  decl->var_list = list;
  decl->type_node = type;
  decl->scope_level = 0;

  ListNode *new_list = calloc(1, sizeof(ListNode));
  new_list->base.type = NODE_LIST;
  new_list->base.location = loc;
  new_list->base.print = print_variable_declaration;
  new_list->element = (ASTNode *)decl;
  new_list->next = NULL;
  return (ASTNode *)new_list;
};

ASTNode *create_variable_identifier_list_node(ASTNode *id, SourceLocation loc) {
  ListNode *list = calloc(1, sizeof(ListNode));

  list->base.type = NODE_LIST;
  list->base.location = loc;
  list->base.print = print_list_identifiers;
  list->element = id;
  list->next = NULL;
  return (ASTNode *)list;
};

ASTNode *create_proc_and_func_declarations_node(ASTNode *proc_and_func,
                                                SourceLocation loc) {
  ListNode *node = calloc(1, sizeof(ListNode));
  node->base.type = NODE_LIST;
  node->base.location = loc;
  node->base.print = print_list_identifiers;
  node->element = proc_and_func;
  node->next = NULL;
  return (ASTNode *)node;
}

ASTNode *create_proc_declaration_node(ASTNode *identifier, ASTNode *parameters,
                                      ASTNode *block_or_forward,
                                      SourceLocation loc) {
  FuncDeclarationNode *proc = calloc(1, sizeof(FuncDeclarationNode));
  proc->base.type = NODE_PROC_DECL;
  proc->base.location = loc;
  proc->base.print = print_todo;
  proc->identifier = identifier;
  proc->parameters = parameters;
  proc->block_or_forward = block_or_forward;
  proc->type = NULL;

  return (ASTNode *)proc;
};

ASTNode *create_func_declaration_node(ASTNode *identifier, ASTNode *parameters,
                                      ASTNode *type, ASTNode *block_or_forward,
                                      SourceLocation loc) {
  FuncDeclarationNode *func = calloc(1, sizeof(FuncDeclarationNode));
  func->base.type = NODE_FUNC_DECL;
  func->base.location = loc;
  func->base.print = print_todo;
  func->identifier = identifier;
  func->type = type;
  func->parameters = parameters;
  func->block_or_forward = block_or_forward;

  return (ASTNode *)func;
};

ASTNode *create_forward_declaration_node(SourceLocation loc) {
  ASTNode *node = calloc(1, sizeof(ASTNode));
  node->type = NODE_FORWARD_DECL;
  node->location = loc;
  node->print = print_todo;
  return node;
}

ASTNode *create_stmt_list_node(ASTNode *stmt, SourceLocation loc) {
  ListNode *new_list = calloc(1, sizeof(ListNode));
  new_list->base.type = NODE_LIST;
  new_list->base.location = loc;
  new_list->base.print = print_stmt_list;
  new_list->element = stmt;
  new_list->next = NULL;
  return (ASTNode *)new_list;
};

ASTNode *create_array_type_node(ASTNode *list, ASTNode *type,
                                SourceLocation loc) {
  ArrayTypeNode *node = calloc(1, sizeof(ArrayTypeNode));
  node->base.type = NODE_ARRAY_TYPE;
  node->base.location = loc;
  node->base.print = print_todo;
  node->index_list = list;
  node->type = type;

  return (ASTNode *)node;
};

ASTNode *create_assign_node(ASTNode *variable, ASTNode *expression,
                            SourceLocation loc) {
  AssignmentNode *node = calloc(1, sizeof(AssignmentNode));
  node->base.type = NODE_ASSIGN_STMT;
  node->base.location = loc;
  node->base.print = print_todo;
  node->target = variable;
  node->expression = expression;

  return (ASTNode *)node;
};

ASTNode *create_case_of_variant_node(ASTNode *tag_field, ASTNode *variant_list,
                                     SourceLocation loc) {
  VariantPartNode *part = calloc(1, sizeof(VariantPartNode));
  part->base.type = NODE_VARIANT_PART;
  part->base.location = loc;
  part->base.print = print_todo;
  part->tag_field = tag_field;
  part->variant_list = variant_list;

  return (ASTNode *)part;
};

ASTNode *create_constant_identifier(ASTNode *identifier, SourceLocation loc) {
  ConstantNode *node = calloc(1, sizeof(ConstantNode));
  node->base.type = NODE_CONSTANT;
  node->base.location = loc;
  node->base.print = print_constant_identifier_node;
  node->const_type = CONST_IDENTIFIER;
  node->is_literal = false;
  node->identifier = identifier;

  return (ASTNode *)node;
};

ASTNode *create_constant_literal(ASTNode *literalValue, SourceLocation loc) {
  ConstantNode *node = calloc(1, sizeof(ConstantNode));
  node->base.type = NODE_CONSTANT;
  node->base.location = loc;
  node->base.print = print_constant_identifier_node;
  node->value = literalValue;
  node->is_literal = true;

  LiteralNode *lvalue = (LiteralNode *)literalValue;

  switch (lvalue->literal_type) {
  case LITERAL_REAL:
    node->const_type = CONST_REAL;
    break;
  case LITERAL_INTEGER:
    node->const_type = CONST_INTEGER;
    break;
  case LITERAL_STRING:
    node->const_type = CONST_STRING;
    break;
  case LITERAL_CHAR:
    node->const_type = CONST_CHAR;
    break;
  case LITERAL_BOOLEAN:
    node->const_type = CONST_BOOLEAN;
    break;
  default:
    free(node);
    return NULL;
  }

  return (ASTNode *)node;
};

ASTNode *create_integer_literal(int integer, SourceLocation loc) {
  LiteralNode *node = calloc(1, sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_literal_value;
  node->literal_type = LITERAL_INTEGER;
  node->value.int_val = integer;
  return (ASTNode *)node;
};

ASTNode *create_real_literal(double real, SourceLocation loc) {
  LiteralNode *node = calloc(1, sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_literal_value;
  node->literal_type = LITERAL_REAL;
  node->value.real_val = real;
  return (ASTNode *)node;
};

ASTNode *create_string_literal(char *string, SourceLocation loc) {
  LiteralNode *node = calloc(1, sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_literal_value;
  node->literal_type = LITERAL_STRING;
  node->value.str_val = strdup(string);
  return (ASTNode *)node;
};

ASTNode *create_char_literal(char character, SourceLocation loc) {
  LiteralNode *node = calloc(1, sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_literal_value;
  node->literal_type = LITERAL_CHAR;
  node->value.char_val = character;
  return (ASTNode *)node;
};

ASTNode *create_boolean_literal(bool boolean, SourceLocation loc) {
  LiteralNode *node = calloc(1, sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_literal_value;
  node->literal_type = LITERAL_BOOLEAN;
  node->value.bool_val = boolean;
  return (ASTNode *)node;
};

ASTNode *create_nil_literal(SourceLocation loc) {
  LiteralNode *node = calloc(1, sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_literal_value;
  node->literal_type = LITERAL_NIL;
  return (ASTNode *)node;
};

ASTNode *create_constant_signed_identifier(ASTNode *identifier,
                                           const char *sign,
                                           SourceLocation loc) {
  ConstantNode *node = calloc(1, sizeof(ConstantNode));
  node->base.type = NODE_CONSTANT;
  node->base.location = loc;
  node->base.print = print_constant_identifier_node;
  node->const_type = CONST_SIGNED_IDENTIFIER;
  node->is_literal = false;
  node->identifier = identifier;
  node->sign = strdup(sign);

  return (ASTNode *)node;
};

ASTNode *create_field_identifier_list_node(ASTNode *list, ASTNode *identifier,
                                           SourceLocation loc) {
  if (identifier == NULL) {
    return list;
  }

  ListNode *new_node = calloc(1, sizeof(ListNode));
  new_node->base.type = NODE_LIST;
  new_node->base.location = loc;
  new_node->base.print = print_list_identifiers;
  new_node->element = identifier;
  new_node->next = NULL;

  if (list == NULL) {
    return (ASTNode *)new_node;
  }

  ListNode *current = (ListNode *)list;
  while (current->next != NULL) {
    current = (ListNode *)current->next;
  }

  current->next = (ASTNode *)new_node;

  return list;
};

ASTNode *create_file_of_type_node(ASTNode *type, SourceLocation loc) {
  FileTypeNode *node = calloc(1, sizeof(FileTypeNode));
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
  FieldListNode *node = calloc(1, sizeof(FieldListNode));
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

  ListNode *new_node = calloc(1, sizeof(ListNode));
  new_node->base.type = NODE_LIST;
  new_node->base.location = loc;
  new_node->base.print = print_list_identifiers;
  new_node->element = field;
  new_node->next = NULL;

  if (fixed == NULL) {
    FixedPartNode *node = calloc(1, sizeof(FixedPartNode));

    node->base.type = NODE_FIXED_PART;
    node->base.location = loc;
    node->base.print = print_todo;
    node->fields = (ASTNode *)new_node;
    node->field_count = 1;

    return (ASTNode *)node;
  }

  FixedPartNode *cf = (FixedPartNode *)fixed;
  ListNode *current = (ListNode *)cf->fields;
  while (current->next != NULL) {
    current = (ListNode *)current->next;
  }

  current->next = (ASTNode *)new_node;
  cf->field_count++;
  return (ASTNode *)cf;
};

ASTNode *create_for_stmt_node(ASTNode *variable, ASTNode *for_stmt,
                              ASTNode *body, SourceLocation loc) {
  ForStmtNode *node = (ForStmtNode *)for_stmt;
  node->base.type = NODE_FOR_STMT;
  node->base.location = loc;
  node->variable = variable;
  node->body = body;

  return (ASTNode *)node;
};

ASTNode *create_for_list_node(ASTNode *start, ASTNode *end, bool is_downto,
                              SourceLocation loc) {
  ForStmtNode *node = calloc(1, sizeof(ForStmtNode));
  node->base.type = NODE_FOR_STMT;
  node->base.location = loc;
  node->base.print = print_todo;
  node->start_expr = start;
  node->end_expr = end;
  node->is_downto = is_downto;
  return (ASTNode *)node;
};

ASTNode *create_formal_parameters_list_node(ASTNode *list, ASTNode *param,
                                            SourceLocation loc) {
  if (param == NULL) {
    return list;
  }

  ListNode *new_node = calloc(1, sizeof(ListNode));
  new_node->base.type = NODE_LIST;
  new_node->base.location = loc;
  new_node->base.print = print_list_identifiers;
  new_node->element = param;
  new_node->next = NULL;

  if (list == NULL) {
    return (ASTNode *)new_node;
  }

  ListNode *current = (ListNode *)list;
  while (current->next != NULL) {
    current = (ListNode *)current->next;
  }

  current->next = (ASTNode *)new_node;
  return list;
};

ASTNode *create_function_call_node(ASTNode *func, ASTNode *params,
                                   SourceLocation loc) {
  FunctionCallNode *node = calloc(1, sizeof(FunctionCallNode));
  node->base.type = NODE_FUNC_CALL;
  node->base.location = loc;
  node->base.print = print_function_call;
  node->function = func;
  node->params = params; // Pode ser NULL se não houver parâmetros

  return (ASTNode *)node;
};

ASTNode *create_goto_label_node(ASTNode *label, SourceLocation loc) {
  GotoNode *node = calloc(1, sizeof(GotoNode));
  node->base.type = NODE_GOTO_STMT;
  node->base.location = loc;
  node->base.print = print_todo;
  node->label = label;
  return (ASTNode *)node;
};

ASTNode *create_if_stmt_node(ASTNode *condition, ASTNode *then_stmt,
                             ASTNode *else_stmt, SourceLocation loc) {
  IfNode *node = calloc(1, sizeof(IfNode));
  node->base.type = NODE_IF_STMT;
  node->base.location = loc;
  node->base.print = print_todo;
  node->condition = condition;
  node->then_stmt = then_stmt;
  node->else_stmt = else_stmt;
  return (ASTNode *)node;
};

ASTNode *create_index_list_start(ASTNode *first_index, SourceLocation loc) {
  IndexList *new_list = calloc(1, sizeof(IndexList));
  new_list->base.type = NODE_INDEX_LIST;
  new_list->base.location = loc;
  new_list->base.print = print_todo;
  new_list->indexes = calloc(1, sizeof(ASTNode **));
  new_list->indexes[0] = first_index;
  new_list->count = 1;
  new_list->capacity = 1;
  return (ASTNode *)new_list;
};

ASTNode *create_label_stmt_node(ASTNode *label, ASTNode *stmt,
                                SourceLocation loc) {
  LabeledStmtNode *node = calloc(1, sizeof(LabeledStmtNode));
  node->base.type = NODE_LABELED_STMT;
  node->base.location = loc;
  node->base.print = print_todo;
  node->label = label;
  node->statement = stmt;
  return (ASTNode *)node;
}

ASTNode *create_enumerated_type_node(ASTNode *identifiers_list,
                                     SourceLocation loc) {
  EnumeratedTypeNode *node = calloc(1, sizeof(EnumeratedTypeNode));
  node->base.type = NODE_ENUMERATED_TYPE;
  node->base.location = loc;
  node->base.print = print_types;
  node->identifiers_list = identifiers_list;
  return (ASTNode *)node;
};

ASTNode *create_packed_type(ASTNode *type, SourceLocation loc) {
  StructuredTypeNode *node = calloc(1, sizeof(StructuredTypeNode));
  node->base.type = NODE_STRUCTURED_TYPE;
  node->base.location = loc;
  node->base.print = print_types;
  node->type = type;
  node->is_packed = true;
  return (ASTNode *)node;
};

ASTNode *create_parameter_identifier_list_node(ASTNode *list, ASTNode *element,
                                               SourceLocation loc) {
  if (element == NULL) {
    return list;
  }

  ListNode *new_node = calloc(1, sizeof(ListNode));
  new_node->base.type = NODE_LIST;
  new_node->base.location = loc;
  new_node->base.print = print_list_identifiers;
  new_node->element = element;
  new_node->next = NULL;

  if (list == NULL) {
    return (ASTNode *)new_node;
  }

  ListNode *current = (ListNode *)list;
  while (current->next != NULL) {
    current = (ListNode *)current->next;
  }

  current->next = (ASTNode *)new_node;
  return list;
};

ASTNode *
create_formal_parameter_section_node(ParameterKind kind, ASTNode *identifiers,
                                     ASTNode *type, ASTNode *parameters,
                                     ASTNode *return_type, SourceLocation loc) {
  FormalParameterSectionNode *node =
      calloc(1, sizeof(FormalParameterSectionNode));
  node->base.type = NODE_FORMAL_PARAM_SECTION;
  node->base.location = loc;
  node->base.print = print_todo;
  node->kind = kind;
  node->identifiers = identifiers;
  node->type = type;
  node->parameters = parameters;
  node->return_type = return_type;

  return (ASTNode *)node;
};

ASTNode *create_parameters_node(ASTNode *parameters_list, SourceLocation loc) {
  ParameterNode *node = calloc(1, sizeof(ParameterNode));
  node->base.type = NODE_PARAMETER;
  node->base.location = loc;
  node->base.print = print_todo;
  node->params_list = parameters_list;

  return (ASTNode *)node;
};

ASTNode *create_pointer_type_node(ASTNode *type, SourceLocation loc) {
  PointerTypeNode *node = calloc(1, sizeof(PointerTypeNode));
  node->base.type = NODE_POINTER_TYPE;
  node->base.location = loc;
  node->base.print = print_types;
  node->type = type;
  return (ASTNode *)node;
};

ASTNode *create_procedure_call_node(ASTNode *proc, ASTNode *params,
                                    SourceLocation loc) {
  FunctionCallNode *node = calloc(1, sizeof(FunctionCallNode));
  node->base.type = NODE_PROC_CALL;
  node->base.location = loc;
  node->base.print = print_todo;
  node->function = proc;
  node->params = params; // Pode ser NULL se não houver parâmetros

  return (ASTNode *)node;
}

ASTNode *create_record_field_node(ASTNode *field_list, ASTNode *type,
                                  SourceLocation loc) {
  RecordFieldNode *record = calloc(1, sizeof(RecordFieldNode));
  record->base.type = NODE_RECORD_FIELD;
  record->base.location = loc;
  record->base.print = print_todo;
  record->field_list = field_list;
  record->record_type = type;

  return (ASTNode *)record;
};

ASTNode *create_record_type_node(ASTNode *field_list, SourceLocation loc) {
  RecordTypeNode *node = calloc(1, sizeof(RecordTypeNode));
  node->base.type = NODE_RECORD_TYPE;
  node->base.location = loc;
  node->base.print = print_types;
  node->field_list = field_list;
  return (ASTNode *)node;
};

ASTNode *create_repeat_until_stmt_list_node(ASTNode *body, ASTNode *condition,
                                            SourceLocation loc) {
  RepeatUntilNode *node = calloc(1, sizeof(RepeatUntilNode));
  node->base.type = NODE_REPEAT_STMT;
  node->base.location = loc;
  node->base.print = body->print;
  node->body = body;
  node->condition = condition;
  return (ASTNode *)node;
};

ASTNode *create_set_of_type_node(ASTNode *type, SourceLocation loc) {
  SetTypeNode *node = calloc(1, sizeof(SetTypeNode));
  node->base.type = NODE_SET_TYPE;
  node->base.location = loc;
  node->base.print = print_types;
  node->type = type;
  return (ASTNode *)node;
};

ASTNode *create_simple_type_node(ASTNode *type, SourceLocation loc) {
  SimpleTypeNode *node = calloc(1, sizeof(SimpleTypeNode));
  node->base.type = NODE_SIMPLE_TYPE;
  node->base.location = loc;
  node->base.print = print_types;
  node->type = type;

  return (ASTNode *)node;
};

ASTNode *create_structure_type_node(ASTNode *type, SourceLocation loc) {
  StructuredTypeNode *node = calloc(1, sizeof(StructuredTypeNode));
  node->base.type = NODE_STRUCTURED_TYPE;
  node->base.location = loc;
  node->base.print = print_types;
  node->type = type;
  node->is_packed = false;

  return (ASTNode *)node;
};

ASTNode *create_tag_field_node(ASTNode *identifier, ASTNode *type,
                               SourceLocation loc) {
  TagFieldNode *tag = calloc(1, sizeof(TagFieldNode));
  tag->base.type = NODE_TAG_FIELD;
  tag->base.location = loc;
  tag->base.print = print_todo;
  tag->field = identifier;
  tag->tag_type = type;

  return (ASTNode *)tag;
};

ASTNode *create_variant_node(ASTNode *label_list, ASTNode *field_list,
                             SourceLocation loc) {
  VariantRecordNode *node = calloc(1, sizeof(VariantRecordNode));
  node->base.type = NODE_VARIANT_RECORD;
  node->base.location = loc;
  node->base.print = print_todo;
  node->case_labels = label_list;
  node->field_list = field_list;

  return (ASTNode *)node;
};

ASTNode *create_while_stmt_node(ASTNode *condition, ASTNode *body,
                                SourceLocation loc) {
  WhileStmtNode *node = calloc(1, sizeof(WhileStmtNode));
  node->base.type = NODE_WHILE_STMT;
  node->base.location = loc;
  node->base.print = print_todo;
  node->condition = condition;
  node->body = body;
  return (ASTNode *)node;
};

ASTNode *create_with_record_list_node(ASTNode *record_list, ASTNode *body,
                                      SourceLocation loc) {
  WithNode *node = calloc(1, sizeof(WithNode));
  node->base.type = NODE_WITH_STMT;
  node->base.location = loc;
  node->base.print = print_todo;
  node->record_list = record_list;
  node->body = body;
  return (ASTNode *)node;
}

ASTNode *create_identifier_node(char *name, SourceLocation loc) {
  IdentifierNode *node = calloc(1, sizeof(IdentifierNode));

  node->base.type = NODE_IDENTIFIER;
  node->base.location = loc;
  node->base.print = print_identifier_node;
  node->name = strdup(name);
  node->kind = SYMBOL_UNKNOWN;

  return (ASTNode *)node;
};

ASTNode *create_unsigned_integer_node(int integer, SourceLocation loc) {
  LiteralNode *node = calloc(1, sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_literal_value;
  node->literal_type = LITERAL_INTEGER;
  node->value.int_val = integer;
  return (ASTNode *)node;
};

ASTNode *create_unsigned_real_node(double real, SourceLocation loc) {
  LiteralNode *node = calloc(1, sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.location = loc;
  node->base.print = print_literal_value;
  node->literal_type = LITERAL_REAL;
  node->value.real_val = real;
  return (ASTNode *)node;
};

ASTNode *create_record_variable_list_node(ASTNode *record_var,
                                          SourceLocation loc) {
  ListNode *node = calloc(1, sizeof(ListNode));
  node->base.type = NODE_LIST;
  node->base.location = loc;
  node->base.print = print_list_identifiers;
  node->element = record_var;
  node->next = NULL;
  return (ASTNode *)node;
};

ASTNode *append_case_item(ASTNode *list, ASTNode *case_item,
                          SourceLocation loc) {
  if (case_item == NULL) {
    return list;
  }

  case_item->location = loc;

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
};

ASTNode *append_case_label_list(ASTNode *list, ASTNode *case_label,
                                SourceLocation loc) {
  if (case_label == NULL) {
    return list;
  }

  case_label->location = loc;

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
};

// Adiciona um record à lista de records no with
ASTNode *append_record_variable_list(ASTNode *list, ASTNode *record_var,
                                     SourceLocation loc) {
  if (record_var == NULL) {
    return list;
  }

  ListNode *head = (ListNode *)list;

  ListNode *new_node = calloc(1, sizeof(ListNode));
  new_node->base.type = NODE_LIST;
  new_node->base.location = loc;
  new_node->base.print = print_list_identifiers;
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
};

ASTNode *create_expression_list(ASTNode *element, SourceLocation loc) {
  ListNode *node = calloc(1, sizeof(ListNode));
  node->base.type = NODE_LIST;
  node->base.location = loc;
  node->base.print = print_list_identifiers;
  node->element = element;
  node->next = NULL;
  return (ASTNode *)node;
};

/* APPENDS */
ASTNode *append_expression_list(ASTNode *list, ASTNode *element,
                                SourceLocation loc) {
  if (element == NULL) {
    return list;
  }

  ListNode *head = (ListNode *)list;

  ListNode *new_node = calloc(1, sizeof(ListNode));
  new_node->base.type = NODE_LIST;
  new_node->base.location = loc;
  new_node->base.print = print_list_identifiers;
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
};

ASTNode *append_identifier_list_node(ASTNode *list, ASTNode *element,
                                     SourceLocation loc) {
  if (element == NULL) {
    return list;
  }

  ListNode *head = (ListNode *)list;

  ListNode *new_node = calloc(1, sizeof(ListNode));
  new_node->base.type = NODE_LIST;
  new_node->base.location = loc;
  new_node->base.print = print_list_identifiers;
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
};

ASTNode *append_label_declaration(ASTNode *list, ASTNode *element,
                                  SourceLocation loc) {
  if (element == NULL) {
    return list;
  }

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
};

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
};

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
};

ASTNode *append_subscript_list_node(ASTNode *list, ASTNode *expr,
                                    SourceLocation loc) {
  if (expr == NULL) {
    return list;
  }

  ListNode *new_node = (ListNode *)create_subscript_list_node(expr, loc);

  if (list == NULL) {
    return (ASTNode *)new_node;
  }

  ListNode *cur = (ListNode *)list;
  while (cur->next != NULL) {
    cur = (ListNode *)cur->next;
  }

  cur->next = (ASTNode *)new_node;
  return list;
};

ASTNode *append_case_list_node(ASTNode *list, ASTNode *expr,
                               SourceLocation loc) {
  if (expr == NULL) {
    return list;
  }

  ListNode *head = (ListNode *)list;

  ListNode *new_node = calloc(1, sizeof(ListNode));
  new_node->base.type = NODE_LIST;
  new_node->base.location = loc;
  new_node->base.print = print_list_identifiers;
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
};

ASTNode *create_set_literal(SourceLocation loc) {
  SetLiteral *node = calloc(1, sizeof(SetLiteral));
  node->base.type = NODE_SET_CONSTRUCTOR;
  node->base.location = loc;
  node->base.print = print_todo;
  node->elements = NULL;
  node->capacity = 0;
  node->count = 0;

  return (ASTNode *)node;
};

ASTNode *create_set_literal_with_element(ASTNode *element, SourceLocation loc) {
  SetLiteral *node = calloc(1, sizeof(SetLiteral));
  node->base.type = NODE_SET_CONSTRUCTOR;
  node->base.location = loc;
  node->base.print = print_todo;
  node->elements = calloc(1, sizeof(SetElement *));
  node->elements[0] = (SetElement *)element;
  node->capacity = 1;
  node->count = 1;

  return (ASTNode *)node;
};

ASTNode *add_element_to_set_literal(ASTNode *set_literal, ASTNode *element,
                                    SourceLocation loc) {
  element->location = loc;

  SetLiteral *node = (SetLiteral *)set_literal;
  if (node->count >= node->capacity) {
    node->capacity *= 2;
    node->elements =
        realloc(node->elements, node->capacity * sizeof(ASTNode *));
  }
  node->elements[node->count++] = (SetElement *)element;
  return (ASTNode *)node;
};

ASTNode *create_set_element(ASTNode *expr, SourceLocation loc) {
  SetElement *element = calloc(1, sizeof(SetElement));
  element->base.type = NODE_SET_ELEMENT;
  element->base.location = loc;
  element->base.print = print_todo;
  element->type = SET_ELEMENT_SINGLE;
  element->value.single_value = expr;

  return (ASTNode *)element;
};

ASTNode *create_set_range_element(ASTNode *const1, ASTNode *const2,
                                  SourceLocation loc) {
  SetElement *element = calloc(1, sizeof(SetElement));
  element->base.type = NODE_SET_ELEMENT;
  element->base.location = loc;
  element->base.print = print_todo;
  element->type = SET_ELEMENT_RANGE;
  element->value.range.start = const1;
  element->value.range.end = const2;

  return (ASTNode *)element;
};

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
};

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
};

ASTNode *append_variant_list(ASTNode *list, ASTNode *element,
                             SourceLocation loc) {
  if (element == NULL) {
    return list;
  }

  ListNode *new_node = calloc(1, sizeof(ListNode));
  new_node->base.type = NODE_LIST;
  new_node->base.location = loc;
  new_node->base.print = print_list_identifiers;
  new_node->element = element;
  new_node->next = NULL;

  if (list == NULL) {
    VariantListNode *vlist = calloc(1, sizeof(VariantListNode));

    vlist->base.type = NODE_VARIANT_LIST;
    vlist->base.location = loc;
    vlist->base.print = print_todo;
    vlist->variants = (ASTNode *)new_node;
    vlist->variant_count = 1;

    return (ASTNode *)vlist;
  }

  VariantListNode *clist = (VariantListNode *)list;
  ListNode *current = (ListNode *)clist->variants;

  while (current->next != NULL) {
    current = (ListNode *)current->next;
  }

  current->next = (ASTNode *)new_node;
  clist->variant_count++;

  return list;
};

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
};

ASTNode *append_proc_and_func_declarations(ASTNode *list,
                                           ASTNode *proc_and_func,
                                           SourceLocation loc) {
  if (proc_and_func == NULL) {
    return list;
  }

  ListNode *head = (ListNode *)list;

  ListNode *new_node = calloc(1, sizeof(ListNode));
  new_node->base.type = NODE_LIST;
  new_node->base.location = loc;
  new_node->base.print = print_list_identifiers;
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
};

ASTNode *add_labels_to_block(ASTNode *block, ASTNode *labels) {
  BlockNode *blk = (BlockNode *)block;
  return create_block_node(labels, blk->types, blk->constants, blk->variables,
                           blk->procs_funcs, blk->statements,
                           blk->base.location);
};

ASTNode *add_constants_to_block(ASTNode *block, ASTNode *constants) {
  BlockNode *blk = (BlockNode *)block;
  return create_block_node(blk->labels, blk->types, constants, blk->variables,
                           blk->procs_funcs, blk->statements,
                           blk->base.location);
};

ASTNode *add_types_to_block(ASTNode *block, ASTNode *types) {
  BlockNode *blk = (BlockNode *)block;
  return create_block_node(blk->labels, types, blk->constants, blk->variables,
                           blk->procs_funcs, blk->statements,
                           blk->base.location);
};

ASTNode *add_variables_to_block(ASTNode *block, ASTNode *variables) {
  BlockNode *blk = (BlockNode *)block;
  return create_block_node(blk->labels, blk->types, blk->constants, variables,
                           blk->procs_funcs, blk->statements,
                           blk->base.location);
};

ASTNode *add_procs_funcs_to_block(ASTNode *block, ASTNode *procs_funcs) {
  BlockNode *blk = (BlockNode *)block;
  return create_block_node(blk->labels, blk->types, blk->constants,
                           blk->variables, procs_funcs, blk->statements,
                           blk->base.location);
};

ASTNode *append_index_to_list(ASTNode *list, ASTNode *new_index,
                              SourceLocation loc) {
  new_index->location = loc;

  IndexList *curr_list = (IndexList *)list;
  if (curr_list->count >= curr_list->capacity) {
    curr_list->capacity *= 2;
    curr_list->indexes =
        realloc(curr_list->indexes, curr_list->capacity * sizeof(ASTNode *));
  }
  curr_list->indexes[curr_list->count++] = new_index;
  return list;
};

ASTNode *create_binary_expression(ASTNode *left, BinaryOperator op,
                                  ASTNode *right, SourceLocation loc) {
  BinaryOperationNode *node = calloc(1, sizeof(BinaryOperationNode));
  node->base.type = NODE_BINARY_EXPR;
  node->base.location = loc;
  node->base.print = print_binary_operation;
  node->left = left;
  node->op = op;
  node->right = right;

  return (ASTNode *)node;
};

ASTNode *create_unary_expression(UnaryOperator unary_op, ASTNode *operand,
                                 SourceLocation loc) {
  UnaryOperationNode *node = calloc(1, sizeof(UnaryOperationNode));
  node->base.type = NODE_UNARY_EXPR;
  node->base.location = loc;
  node->base.print = print_unary_operation;
  node->operand = operand;
  node->op = unary_op;

  return (ASTNode *)node;
};

/* UTILS */
ASTNode *update_identifier_node_kind(ASTNode *id, SymbolKind symb_kind) {
  IdentifierNode *id_node = (IdentifierNode *)id;
  id_node->kind = symb_kind;

  return (ASTNode *)id_node;
};

ASTNode *get_statements_from_block(ASTNode *block) {
  if (!block)
    return NULL;
  return ((BlockNode *)block)->statements;
};

const char *get_literal_type_name(LiteralType type) {
  switch (type) {
  case LITERAL_INTEGER:
    return "LITERAL_INTEGER";
  case LITERAL_REAL:
    return "LITERAL_REAL";
  case LITERAL_BOOLEAN:
    return "LITERAL_BOOLEAN";
  case LITERAL_STRING:
    return "LITERAL_STRING";
  case LITERAL_CHAR:
    return "LITERAL_CHAR";
  case LITERAL_NIL:
    return "LITERAL_NIL";
  default:
    return "UNKNOWN_LITERAL";
  }
}

const char *binary_op_to_string(BinaryOperator op) {
  switch (op) {
  case BINOP_LT:
    return "<";
  case BINOP_LTE:
    return "<=";
  case BINOP_EQ:
    return "=";
  case BINOP_NEQ:
    return "<>";
  case BINOP_GTE:
    return ">=";
  case BINOP_GT:
    return ">";
  case BINOP_PLUS:
    return "+";
  case BINOP_MINUS:
    return "-";
  case BINOP_OR:
    return "or";
  case BINOP_TIMES:
    return "*";
  case BINOP_DIVIDE:
    return "/";
  case BINOP_DIV:
    return "div";
  case BINOP_MOD:
    return "mod";
  case BINOP_AND:
    return "and";
  case BINOP_IN:
    return "in";
  default:
    return "unknown";
  }
};

const char *unary_op_to_string(UnaryOperator op) {
  switch (op) {
  case UNOP_PLUS:
    return "+";
  case UNOP_MINUS:
    return "-";
  case UNOP_NOT:
    return "not";
  default:
    return "unknown";
  }
};

const char *get_node_type_name(NodeType type) {
  switch (type) {
  case NODE_PROGRAM:
    return "NODE_PROGRAM";
  case NODE_HEADING:
    return "NODE_HEADING";
  case NODE_BLOCK:
    return "NODE_BLOCK";
  case NODE_USES:
    return "NODE_USES";

  case NODE_LABEL_DECL:
    return "NODE_LABEL_DECL";
  case NODE_CONST_DECL:
    return "NODE_CONST_DECL";
  case NODE_TYPE_DECL:
    return "NODE_TYPE_DECL";
  case NODE_VAR_DECL:
    return "NODE_VAR_DECL";
  case NODE_PROC_DECL:
    return "NODE_PROC_DECL";
  case NODE_FUNC_DECL:
    return "NODE_FUNC_DECL";
  case NODE_FORWARD_DECL:
    return "NODE_FORWARD_DECL";

  case NODE_ENUMERATED_TYPE:
    return "NODE_ENUMERATED_TYPE";
  case NODE_SUBRANGE_TYPE:
    return "NODE_SUBRANGE_TYPE";
  case NODE_TYPE_IDENTIFIER:
    return "NODE_TYPE_IDENTIFIER";
  case NODE_STRUCTURED_TYPE:
    return "NODE_STRUCTURED_TYPE";
  case NODE_SIMPLE_TYPE:
    return "NODE_SIMPLE_TYPE";
  case NODE_ARRAY_TYPE:
    return "NODE_ARRAY_TYPE";
  case NODE_RECORD_TYPE:
    return "NODE_RECORD_TYPE";
  case NODE_SET_TYPE:
    return "NODE_SET_TYPE";
  case NODE_FILE_TYPE:
    return "NODE_FILE_TYPE";
  case NODE_POINTER_TYPE:
    return "NODE_POINTER_TYPE";
  case NODE_POINTER_DEREF:
    return "NODE_POINTER_DEREF";

  case NODE_COMPOUND_STMT:
    return "NODE_COMPOUND_STMT";
  case NODE_ASSIGN_STMT:
    return "NODE_ASSIGN_STMT";
  case NODE_PROC_CALL:
    return "NODE_PROC_CALL";
  case NODE_IF_STMT:
    return "NODE_IF_STMT";
  case NODE_CASE_STMT:
    return "NODE_CASE_STMT";
  case NODE_CASE_ITEM:
    return "NODE_CASE_ITEM";
  case NODE_CASE_LABEL:
    return "NODE_CASE_LABEL";
  case NODE_CASE_ELSE:
    return "NODE_CASE_ELSE";
  case NODE_WHILE_STMT:
    return "NODE_WHILE_STMT";
  case NODE_REPEAT_STMT:
    return "NODE_REPEAT_STMT";
  case NODE_FOR_STMT:
    return "NODE_FOR_STMT";
  case NODE_WITH_STMT:
    return "NODE_WITH_STMT";
  case NODE_GOTO_STMT:
    return "NODE_GOTO_STMT";
  case NODE_LABELED_STMT:
    return "NODE_LABELED_STMT";

  case NODE_BINARY_EXPR:
    return "NODE_BINARY_EXPR";
  case NODE_UNARY_EXPR:
    return "NODE_UNARY_EXPR";
  case NODE_LITERAL:
    return "NODE_LITERAL";
  case NODE_IDENTIFIER:
    return "NODE_IDENTIFIER";
  case NODE_MEMBER_ACCESS:
    return "NODE_MEMBER_ACCESS";
  case NODE_ARRAY_ACCESS:
    return "NODE_ARRAY_ACCESS";
  case NODE_FUNC_CALL:
    return "NODE_FUNC_CALL";
  case NODE_SET_CONSTRUCTOR:
    return "NODE_SET_CONSTRUCTOR";
  case NODE_CONSTANT:
    return "NODE_CONSTANT";

  case NODE_FIELD_LIST:
    return "NODE_FIELD_LIST";
  case NODE_RECORD_FIELD:
    return "NODE_RECORD_FIELD";
  case NODE_INDEX_LIST:
    return "NODE_INDEX_LIST";
  case NODE_PARAMETER:
    return "NODE_PARAMETER";
  case NODE_VARIANT_RECORD:
    return "NODE_VARIANT_RECORD";
  case NODE_VARIANT_LIST:
    return "NODE_VARIANT_LIST";
  case NODE_VARIANT_PART:
    return "NODE_VARIANT_PART";
  case NODE_TAG_FIELD:
    return "NODE_TAG_FIELD";
  case NODE_FIXED_PART:
    return "NODE_FIXED_PART";
  case NODE_FORMAL_PARAM_SECTION:
    return "NODE_FORMAL_PARAM_SECTION";
  case NODE_LIST:
    return "NODE_LIST";
  case NODE_ERROR:
    return "NODE_ERROR";
  case NODE_OPERATION:
    return "NODE_OPERATION";
  case NODE_SET_ELEMENT:
    return "NODE_SET_ELEMENT";

  default:
    return "UNKNOWN_NODETYPE";
  }
};

const char *get_symbol_kind_name(SymbolKind symb) {
  switch (symb) {
  case SYMBOL_UNKNOWN:
    return "SYMBOL_UNKNOWN";
  case SYMBOL_VARIABLE:
    return "SYMBOL_VARIABLE";
  case SYMBOL_CONSTANT:
    return "SYMBOL_CONSTANT";
  case SYMBOL_PARAMETER:
    return "SYMBOL_PARAMETER";
  case SYMBOL_FUNCTION:
    return "SYMBOL_FUNCTION";
  case SYMBOL_PROCEDURE:
    return "SYMBOL_PROCEDURE";
  case SYMBOL_TYPE:
    return "SYMBOL_TYPE";
  case SYMBOL_FIELD:
    return "SYMBOL_FIELD";
  case SYMBOL_LOCAL_VAR:
    return "SYMBOL_LOCAL_VAR";
  case SYMBOL_GLOBAL_VAR:
    return "SYMBOL_GLOBAL_VAR";
  case SYMBOL_VALUE_PARAM:
    return "SYMBOL_VALUE_PARAM";
  case SYMBOL_VAR_PARAM:
    return "SYMBOL_VAR_PARAM";
  case SYMBOL_ENUM_VALUE:
    return "SYMBOL_ENUM_VALUE";
  case SYMBOL_LABEL:
    return "SYMBOL_LABEL";
  case SYMBOL_PROGRAM:
    return "SYMBOL_PROGRAM";
  case SYMBOL_UNIT:
    return "SYMBOL_UNIT";
  case SYMBOL_FORWARD_DECL:
    return "SYMBOL_FORWARD_DECL";
  case SYMBOL_BUILTIN:
    return "SYMBOL_BUILTIN";
  default:
    return "UNKNOWN_SYMBOL_NAME";
  }
}

void print_todo(ASTNode *node, int indent) {
  fprintf(stderr, "%*sTODO %s\n", indent, "", get_node_type_name(node->type));
};

const char *get_param_kind_name(ParameterKind kind) {
  switch (kind) {
  case PARAM_VAR:
    return "PARAM_VAR";
  case PARAM_VALUE:
    return "PARAM_VALUE";
  case PARAM_PROCEDURE:
    return "PARAM_PROCEDURE";
  case PARAM_FUNCTION:
    return "PARAM_FUNCTION";
  default:
    return "UNKNOWN_PARAM";
  }
}

ConstantValue evaluate_constant(CompilerContext *context, ASTNode *const_node) {
  ConstantValue result = {
      .type = CONST_INTEGER, .is_valid = false, .value = {.int_val = 0}};

  if (const_node->type != NODE_CONSTANT) {
    result.is_valid = false;
    return result;
  }

  ConstantNode *node = (ConstantNode *)const_node;

  switch (node->const_type) {
  case CONST_INTEGER:
    result.type = CONST_INTEGER;
    result.value.int_val = ((LiteralNode *)node->value)->value.int_val;
    result.is_valid = true;
    break;

  case CONST_REAL:
    result.type = CONST_REAL;
    result.value.real_val = ((LiteralNode *)node->value)->value.real_val;
    result.is_valid = true;
    break;

  case CONST_STRING:
    result.type = CONST_STRING;
    result.value.str_val = ((LiteralNode *)node->value)->value.str_val;
    result.is_valid = true;
    break;

  case CONST_CHAR:
    result.type = CONST_CHAR;
    result.value.char_val = ((LiteralNode *)node->value)->value.char_val;
    result.is_valid = true;
    break;

  case CONST_BOOLEAN:
    result.type = CONST_BOOLEAN;
    result.value.bool_val = ((LiteralNode *)node->value)->value.bool_val;
    result.is_valid = true;
    break;

  case CONST_IDENTIFIER:
  case CONST_SIGNED_IDENTIFIER: {
    IdentifierNode *id = (IdentifierNode *)node->identifier;
    SymbolEntry *entry = context_lookup(context, id->name);

    if (!entry || entry->kind != SYMBOL_CONSTANT) {
      fprintf(stderr, "Constant of identifier: %s is not declared", id->name);
      exit(1);
    }

    result = evaluate_constant(context, entry->info.const_info.value);

    if (node->const_type == CONST_SIGNED_IDENTIFIER && node->sign &&
        strcmp(node->sign, "-") == 0) {

      if (result.type == CONST_INTEGER) {
        result.value.int_val = -result.value.int_val;
      } else if (result.type == CONST_REAL) {
        result.value.real_val = -result.value.real_val;
      } else {
        yyerror("Cannot apply sign to non-numeric constant");
        exit(1);
      }
    }
    break;
  }
  }
  return result;
}

void free_node(ASTNode *node) {
  if (node == NULL) {
    return;
  }
  LOG_TRACE("Freeing node %p of type", (void *)node);
  assert(node->type >= 0 && node->type <= NODE_SET_ELEMENT);

  switch (node->type) {
  case NODE_PROGRAM: {
    ProgramNode *prog = (ProgramNode *)node;
    free(prog->name);
    free_node(prog->heading);
    free_node(prog->block);
    free(prog);
    break;
  }
  case NODE_HEADING: {
    HeadingNode *heading = (HeadingNode *)node;
    free_node(heading->list);
    free(heading);
    break;
  }
  case NODE_BLOCK: {
    BlockNode *block = (BlockNode *)node;
    free_node(block->labels);
    free_node(block->types);
    free_node(block->constants);
    free_node(block->variables);
    free_node(block->procs_funcs);
    free_node(block->statements);
    free(block);
    break;
  }
  case NODE_USES: {
    free(node);
    break;
  }
  case NODE_LABEL_DECL: {
    LabelDeclarationNode *label = (LabelDeclarationNode *)node;
    free_node(label->value);
    free(label);
    break;
  }
  case NODE_CONST_DECL: {
    ConstDeclarationNode *constant = (ConstDeclarationNode *)node;
    free_node(constant->const_expr);
    free_node(constant->identifier);
    free(constant);
    break;
  }
  case NODE_TYPE_DECL: {
    TypeDeclarationNode *type = (TypeDeclarationNode *)node;
    free_node(type->identifier);
    free_node(type->type_expr);
    free(type);
    break;
  }
  case NODE_VAR_DECL: {
    VarDeclarationNode *vars = (VarDeclarationNode *)node;
    fprintf(stderr,
            "[VAR_DECL] VarDeclarationNode %p — var_list=%p type_node=%p\n",
            (void *)vars, (void *)vars->var_list, (void *)vars->type_node);
    free_node(vars->type_node);
    free_node(vars->var_list);
    free(vars);
    break;
  }
  case NODE_PROC_DECL: {
    FuncDeclarationNode *proc = (FuncDeclarationNode *)node;
    free_node(proc->identifier);
    free_node(proc->block_or_forward);
    free_node(proc->parameters);
    free(proc);
    break;
  }
  case NODE_FUNC_DECL: {
    FuncDeclarationNode *func = (FuncDeclarationNode *)node;
    free_node(func->parameters);
    free_node(func->block_or_forward);
    free_node(func->type);
    free(func);
    break;
  }
  case NODE_ENUMERATED_TYPE: {
    EnumeratedTypeNode *en = (EnumeratedTypeNode *)node;
    free_node(en->identifiers_list);
    free(en);
    break;
  }
  case NODE_SUBRANGE_TYPE: {
    SubrangeTypeNode *sub = (SubrangeTypeNode *)node;
    free_node(sub->lower);
    free_node(sub->upper);
    free(sub);
    break;
  }
  case NODE_TYPE_IDENTIFIER: {
    TypeIdentifierNode *tid = (TypeIdentifierNode *)node;
    free_node((ASTNode *)tid->id);
    free(tid);
    break;
  }
  case NODE_STRUCTURED_TYPE: {
    StructuredTypeNode *st = (StructuredTypeNode *)node;
    free_node(st->type);
    free(st);
    break;
  }
  case NODE_ARRAY_TYPE: {
    ArrayTypeNode *arr = (ArrayTypeNode *)node;
    free_node(arr->type);
    free_node(arr->index_list);
    free(arr);
    break;
  }
  case NODE_RECORD_TYPE: {
    RecordTypeNode *r = (RecordTypeNode *)node;
    free_node(r->field_list);
    free_node(r->variant_part);
    free(r);
    break;
  }
  case NODE_SET_TYPE: {
    SetTypeNode *s = (SetTypeNode *)node;
    free_node(s->type);
    free(s);
    break;
  }
  case NODE_FILE_TYPE: {
    FileTypeNode *f = (FileTypeNode *)node;
    free_node(f->type);
    free(f);
    break;
  }
  case NODE_POINTER_TYPE: {
    PointerTypeNode *pt = (PointerTypeNode *)node;
    free_node(pt->type);
    free(pt);
    break;
  }
  case NODE_POINTER_DEREF: {
    PointerDerefNode *pd = (PointerDerefNode *)node;
    free_node(pd->pointer);
    free(pd);
    break;
  }
  case NODE_COMPOUND_STMT: {
    free(node);
    break;
  }
  case NODE_ASSIGN_STMT: {
    AssignmentNode *a = (AssignmentNode *)node;
    free_node(a->expression);
    free_node(a->target);
    free(a);
    break;
  }
  case NODE_PROC_CALL: {
    FunctionCallNode *pc = (FunctionCallNode *)node;
    free_node(pc->function);
    free_node(pc->params);
    free(pc);
    break;
  }
  case NODE_IF_STMT: {
    IfNode *ifn = (IfNode *)node;
    free_node(ifn->else_stmt);
    free_node(ifn->then_stmt);
    free_node(ifn->condition);
    free(ifn);
    break;
  }
  case NODE_CASE_STMT: {
    CaseNode *cn = (CaseNode *)node;
    free_node(cn->case_list);
    free_node(cn->else_part);
    free_node(cn->expr);
    free(cn);
    break;
  }
  case NODE_CASE_ITEM: {
    CaseItemNode *ci = (CaseItemNode *)node;
    free_node(ci->statement);
    free_node(ci->value_list);
    free(ci);
    break;
  }
  case NODE_CASE_ELSE: {
    CaseElseNode *ce = (CaseElseNode *)node;
    free_node(ce->stmt);
    free(ce);
    break;
  }
  case NODE_WHILE_STMT: {
    WhileStmtNode *wl = (WhileStmtNode *)node;
    free_node(wl->condition);
    free_node(wl->body);
    free(wl);
    break;
  }
  case NODE_REPEAT_STMT: {
    RepeatUntilNode *rp = (RepeatUntilNode *)node;
    free_node(rp->condition);
    free_node(rp->body);
    free(rp);
    break;
  }
  case NODE_FOR_STMT: {
    ForStmtNode *ft = (ForStmtNode *)node;
    free_node(ft->body);
    free_node(ft->end_expr);
    free_node(ft->start_expr);
    free_node(ft->variable);
    free(ft);
    break;
  }
  case NODE_WITH_STMT: {
    WithNode *wn = (WithNode *)node;
    free_node(wn->body);
    free_node(wn->record_list);
    free(wn);
    break;
  }
  case NODE_GOTO_STMT: {
    GotoNode *gt = (GotoNode *)node;
    free_node(gt->label);
    free(gt);
    break;
  }
  case NODE_BINARY_EXPR: {
    BinaryOperationNode *bp = (BinaryOperationNode *)node;
    free_node(bp->left);
    free_node(bp->right);
    free(bp);
    break;
  }
  case NODE_UNARY_EXPR: {
    UnaryOperationNode *up = (UnaryOperationNode *)node;
    free_node(up->operand);
    free(up);
    break;
  }
  case NODE_LITERAL: {
    LiteralNode *l = (LiteralNode *)node;
    free(l);
    break;
  }
  case NODE_IDENTIFIER: {
    IdentifierNode *id = (IdentifierNode *)node;
    free(id->name);
    free(id);
    break;
  }
  case NODE_MEMBER_ACCESS: {
    MemberAccessNode *mc = (MemberAccessNode *)node;
    free_node(mc->field);
    free_node(mc->record);
    free(mc);
    break;
  }
  case NODE_ARRAY_ACCESS: {
    ArrayAccessNode *ac = (ArrayAccessNode *)node;
    free_node(ac->array);
    free_node(ac->subscript_list);
    free(ac);
    break;
  }
  case NODE_FUNC_CALL: {
    FunctionCallNode *fc = (FunctionCallNode *)node;
    free_node(fc->params);
    free_node(fc->function);
    free(fc);
    break;
  }
  case NODE_SET_CONSTRUCTOR: {
    SetLiteral *sl = (SetLiteral *)node;
    for (int i = 0; i < sl->count; i++) {
      free_node((ASTNode *)sl->elements[i]);
    }
    free(sl->elements);
    free(sl);
    break;
  }
  case NODE_FORWARD_DECL: {
    free(node);
    break;
  }
  case NODE_SIMPLE_TYPE: {
    SimpleTypeNode *st = (SimpleTypeNode *)node;
    free_node(st->type);
    free(st);
    break;
  }
  case NODE_CASE_LABEL: {
    CaseLabelNode *cl = (CaseLabelNode *)node;
    free_node(cl->upper);
    free_node(cl->lower);
    free(cl);
    break;
  }
  case NODE_LABELED_STMT: {
    LabeledStmtNode *lb = (LabeledStmtNode *)node;
    free_node(lb->label);
    free_node(lb->statement);
    free(lb);
    break;
  }
  case NODE_CONSTANT: {
    ConstantNode *c = (ConstantNode *)node;
    free_node(c->value);
    free_node(c->identifier);
    free(c);
    break;
  }
  case NODE_RECORD_FIELD: {
    RecordFieldNode *rf = (RecordFieldNode *)node;
    free_node(rf->field_list);
    free_node(rf->record_type);
    free(rf);
    break;
  }
  case NODE_INDEX_LIST: {
    IndexList *idx = (IndexList *)node;
    for (int i = 0; i < idx->count; i++) {
      free_node(idx->indexes[i]);
    }
    free(idx->indexes);
    free(idx);
    break;
  }
  case NODE_VARIANT_LIST: {
    VariantListNode *vl = (VariantListNode *)node;
    free_node(vl->variants);
    free(vl);
    break;
  }
  case NODE_VARIANT_PART: {
    VariantPartNode *vp = (VariantPartNode *)node;
    free_node(vp->variant_list);
    free_node(vp->tag_field);
    free(vp);
    break;
  }
  case NODE_TAG_FIELD: {
    TagFieldNode *tf = (TagFieldNode *)node;
    free_node(tf->field);
    free_node(tf->tag_type);
    free(tf);
    break;
  }
  case NODE_FIXED_PART: {
    FixedPartNode *fp = (FixedPartNode *)node;
    free_node(fp->fields);
    free(fp);
    break;
  }
  case NODE_FORMAL_PARAM_SECTION: {
    FormalParameterSectionNode *fp = (FormalParameterSectionNode *)node;
    free_node(fp->type);
    free_node(fp->parameters);
    free_node(fp->return_type);
    free_node(fp->identifiers);
    free(fp);
    break;
  }
  case NODE_OPERATION: {
    free(node);
    break;
  }
  case NODE_SET_ELEMENT: {
    SetElement *st = (SetElement *)node;
    free(st);
    break;
  }
  case NODE_FIELD_LIST: {
    FieldListNode *fl = (FieldListNode *)node;
    free_node(fl->variant_part);
    free_node(fl->fixed_part);
    free(fl);
    break;
  }
  case NODE_PARAMETER: {
    ParameterNode *p = (ParameterNode *)node;
    free_node(p->params_list);
    free(p);
    break;
  }
  case NODE_VARIANT_RECORD: {
    VariantRecordNode *vr = (VariantRecordNode *)node;
    free_node(vr->field_list);
    free_node(vr->case_labels);
    free(vr);
    break;
  }
  case NODE_LIST: {
    ListNode *l = (ListNode *)node;
    while (l) {
      LOG_TRACE("Freeing ListNode %p — element=%p next=%p\n",(void *)l, (void *)l->element, (void *)l->next);

      if (l->element != NULL) {
        free_node(l->element);
      } else {
        LOG_ERROR("[WARN] ListNode %p has NULL element\n", (void *)l);
      }

      ListNode *next = (ListNode *)l->next;
      free(l);
      l = next;
    }
    break;
  }
  case NODE_ERROR: {
    free(node);
    break;
  }
  default:
    LOG_ERROR("[FATAL] Tipo desconhecido ou não tratado no free_node: %d\n", node->type);
    abort();
  }
};
