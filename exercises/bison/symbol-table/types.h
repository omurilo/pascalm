#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

typedef enum {
  TYPE_INT,
  TYPE_FLOAT,
  TYPE_BOOL,
  TYPE_CHAR,
  TYPE_STRING
} VarType;

typedef struct {
  VarType type;
  union {
    int i;
    bool b;
    char c;
    double f;
    char* s;
  };
} Value;

typedef struct {
  char name[11];
  VarType type;
  union {
    int i;
    double f;
    char c;
    int b;
    char* s;
  };
} Symbol;

typedef enum {
  STMT_WRITE,
  STMT_IF,
  STMT_READ
} StmtType;

typedef struct Stmt {
  StmtType type;
  union {
    struct {
      char* var_name;
      Value literal;
      int is_literal;
    } write;

    struct {
      char* var_name;
    } read;

    struct {
      Value cond;
      struct StmtList* then_block;
      struct StmtList* else_block;
    } if_stmt;
  };
} Stmt;

typedef struct StmtList {
  Stmt* stmt;
  struct StmtList* next;
} StmtList;

#endif
