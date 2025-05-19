#include "final_work.tab.h"
#include "final_work_types.h"
#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *msg) {
  fprintf(stderr, "Error: %s at %d.%d-%d.%d\n", msg, yylloc.first_line,
          yylloc.first_column, yylloc.last_line, yylloc.last_column);
}

int main(int argc, char **argv) {
  if (argc > 1) {
    yylloc.file_name = argv[1];
    yyin = fopen(argv[1], "r");
    if (!yyin) {
      perror("Error open file");
      return 1;
    }
  } else {
    yyin = stdin;
    yylloc.file_name = (char *)"stdin";
  }
  yylloc.first_column = 1;
  yylloc.first_line = 1;
  yylloc.last_column = 1;
  yylloc.last_line = 1;

  yyparse();

  if (yyin != stdin) {
    fclose(yyin);
  }

  return 0;
}

const char *getTypeString(TypeInfo *type) {
  if (type->type >= 0 && type->type < TYPE__COUNT) {
    return TypeNames[type->type];
  }
  return "unknown";
}

const char *describeType(TypeInfo *type) {
  switch (type->type) {
  case TYPE_ARRAY: {
    static char buf[64];
    snprintf(buf, sizeof buf, "array of %s",
             getTypeString(type->details.array_info.element_type));
    return buf;
  }
  case TYPE_RECORD:
    static char buf[128];
    snprintf(buf, sizeof buf, "record\nfields:");
    for (struct Field *it = type->details.record_fields; it != NULL;
         it = it->next) {
      snprintf(buf, sizeof buf, "%s\n %s of type %s", buf, it->name,
               getTypeString(it->type));
    };
    return buf;
  default:
    return getTypeString(type);
  }
}

// void print_symbol(Symbol *s) {
//   switch (s->kind) {
//     case SYMBOL_VAR:
//       printf("Symbol Var name %s - type info: %s", s->name, describeType(s->type));
//       break;
//     case SYMBOL_CONST:
//     case SYMBOL_TYPE:
//     case SYMBOL_FUNC:
//     case SYMBOL_PROC:
//       break;
//     default:
//       printf("unknown symbol type");
//   }
// }
//
// void print_indent(int level) {
//   for (int i = 0; i < level; i++) {
//     printf("|  ");
//   }
// }
//
// void print_expr(Expr *expr, int indent_level) {
//   if (!expr)
//     return;
//
//   print_indent(indent_level);
//   switch (expr->type) {
//     case EXPR_LITERAL:
//       printf("Literal Expression:");
//       break;
//     case EXPR_VARIABLE: {
//       printf("Variable Expression: %s\n", expr->var_name);
//       Symbol *s = get_symbol_by_name(expr->var_name);
//       print_symbol(s);
//       break;
//     }
//     case EXPR_BINARY:
//     //   printf("Arithmetic Expression:\n");
//     //   print_expr(expr->u.bin.left, indent_level + 1);
//     //   printf("Operator: %d\n", expr->u.bin.aop);
//     //   print_expr(expr->u.bin.right, indent_level + 1);
//       break;
//     case EXPR_UNARY:
//     //   printf("Logical Expression:\n");
//     //   print_expr(expr->u.bin.left, indent_level + 1);
//     //   printf("Operator: %d\n", expr->u.bin.op);
//     //   print_expr(expr->u.bin.right, indent_level + 1);
//       break;
//     case EXPR_CALL:
//     //   printf("Function Call: %s\n", expr->u.call.name);
//     //   print_expr_list(expr->u.call.args, indent_level + 1);
//       break;
//     case EXPR_INDEX:
//       break;
//     case EXPR_FIELD:
//       break;
//     case EXPR_FORMATTED_WRITE:
//       break;
//     default:
//       printf("Unknown Expression Type\n");
//       break;
//   }
// }
//
// void print_expr_list(ExprList *expr_list, int indent_level) {
//   while (expr_list) {
//     print_expr(expr_list->expr, indent_level);
//     expr_list = expr_list->next;
//   }
// }
//
// void print_stmt(Stmt *stmt, int indent_level) {
//   if (!stmt)
//     return;
//
//   print_indent(indent_level);
//   switch (stmt->type) {
//   case STMT_ASSIGN: {
//     printf("Assign Statement:\n");
//     print_expr(stmt->assign.target, indent_level + 1);
//     print_expr(stmt->assign.value, indent_level + 1);
//     break;
//                     }
//   case STMT_IF:
//     printf("If Statement:\n");
//     // print_expr(stmt->u.if_stmt.condition, indent_level + 1);
//     // print_stmt_list(stmt->u.if_stmt.then_branch, indent_level + 1);
//     // print_stmt_list(stmt->u.if_stmt.else_branch, indent_level + 1);
//     break;
//   case STMT_WHILE:
//     printf("While Statement:\n");
//     // print_expr(stmt->u.while_stmt.condition, indent_level + 1);
//     // print_stmt_list(stmt->u.while_stmt.body, indent_level + 1);
//     break;
//   case STMT_FOR:
//     printf("For Statement:\n");
//     // print_expr(stmt->u.for_stmt.start, indent_level + 1);
//     // print_expr(stmt->u.for_stmt.end, indent_level + 1);
//     // printf("Direction: %s\n", stmt->u.for_stmt.downto ? "Downto" : "To");
//     // print_stmt_list(stmt->u.for_stmt.body, indent_level + 1);
//     break;
//   case STMT_REPEAT:
//     printf("Repeat Statement:\n");
//     // print_expr(stmt->u.repeat_stmt.condition, indent_level + 1);
//     // print_stmt_list(stmt->u.repeat_stmt.body, indent_level + 1);
//     break;
//   case STMT_CASE:
//     printf("Case Statement:\n");
//     // print_expr(stmt->u.case_stmt.expression, indent_level + 1);
//     // Imprimir casos omitido
//     break;
//   case STMT_READ:
//     printf("Read Statement:\n");
//     // printf("Variable: %s\n", stmt->u.read_stmt.var_name);
//     break;
//   case STMT_WRITE:
//     printf("Write Statement:\n");
//     // print_expr_list(stmt->u.write_stmt.args, indent_level + 1);
//     break;
//   case STMT_PROC_CALL: {
//     printf("Procedure Call:\n");
//     printf("Procedure: %s\n", stmt->proc_call.proc_name);
//     // print_expr_list(stmt->u.proc_call.args, indent_level + 1);
//     break;
//                        }
//   default:
//     printf("Unknown Statement Type\n");
//     break;
//   }
// }
//
// void print_stmt_list(StmtList *stmt_list, int indent_level) {
//   while (stmt_list) {
//     print_stmt(stmt_list->stmt, indent_level);
//     stmt_list = stmt_list->next;
//   }
// }
//
// void print_declarations(struct Decl *decl, int ident_level) {
//   while (decl != NULL) {
//     print_indent(ident_level);
//     printf("Decl Type %d\n", decl->type);
//
//     switch (decl->type) {
//       case LABEL_DECL:
//         break;
//       case CONST_DECL:
//         break;
//       case TYPE_DECL:
//         break;
//       case VAR_DECL:
//         break;
//       case PROC_DECL:
//         break;
//       case FUNC_DECL:
//         break;
//     }
//
//     decl = decl->next; // <- ESSENCIAL
//   }
// }
//
// void print_program(struct Program *prog) {
//   if (!prog)
//     return;
//
//   printf("| Programa %s\n", prog->identifier);
//   for (struct IdentifierList *id = prog->heading; id != NULL; id = id->next) {
//     printf("(");
//     printf("%s,", id->identifier);
//     printf(")\n");
//   }
//   print_declarations(prog->block->declarations, 1);
//   print_stmt_list(prog->block->stmt_list, 1);
// }

void print_indent(int level) {
  for (int i = 0; i < level; ++i) printf("  ");
}

void print_var_list(VarList *list, int indent_level) {
  while (list) {
    print_indent(indent_level);
    printf("Variable: %s\n", list->name);
    list = list->next;
  }
}

void print_declarations(Decl *decl, int indent_level) {
  while (decl) {
    print_indent(indent_level);
    printf("Declaration Type: %d\n", decl->type);
    switch (decl->type) {
      case VAR_DECL:
        print_var_list(((VarDecl *)decl)->list, indent_level + 1);
        break;
      case CONST_DECL:
        // Implementar print de constantes se necessário
        break;
      case TYPE_DECL:
        // Implementar print de tipos se necessário
        break;
      case FUNC_DECL:
        // Implementar print de funções se necessário
        break;
      case PROC_DECL:
        // Implementar print de procedimentos se necessário
        break;
      case LABEL_DECL:
        // Implementar print de labels se necessário
        break;
    }
    decl = decl->next;
  }
}

void print_stmt_list(StmtList *list, int indent_level) {
  while (list) {
    print_indent(indent_level);
    printf("Statement Type: %d\n", list->stmt->type);
    list = list->next;
  }
}

void print_block(Block *block, int indent_level) {
  print_indent(indent_level);
  printf("Block:\n");
  if (block->declarations) {
    print_indent(indent_level + 1);
    printf("Declarations:\n");
    print_declarations(block->declarations, indent_level + 2);
  }
  if (block->stmt_list) {
    print_indent(indent_level + 1);
    printf("Statements:\n");
    print_stmt_list(block->stmt_list, indent_level + 2);
  }
}

void print_identifier_list(IdentifierList *list, int indent_level) {
  while (list) {
    print_indent(indent_level);
    printf("Identifier: %s\n", list->identifier);
    list = list->next;
  }
}

void print_program(Program *prog) {
  printf("Program: %s\n", prog->identifier);
  if (prog->heading) {
    printf("Heading:\n");
    print_identifier_list(prog->heading, 1);
  }
  if (prog->block) {
    printf("Block:\n");
    print_block(prog->block, 1);
  }
}
