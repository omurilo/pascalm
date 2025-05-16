#ifndef TAC_H
#define TAC_H

#include "types.h"

typedef struct {
  char* temp;
  struct TAC* code;
} ExprResult;

typedef struct TAC {
  char* code;
  struct TAC* next;
} TAC;

ExprResult generate_expr_tac(Expr* e);
TAC* generate_stmt_tac(Stmt* s);
TAC* generate_stmt_list_tac(StmtList* list);
TAC* tac_create(const char* fmt, ...);
TAC* tac_append(TAC* list, TAC* new_code);

void verify_assign_types(Stmt* s);
void tac_print(TAC* code);
char* new_temp();
char* new_label();

#endif
