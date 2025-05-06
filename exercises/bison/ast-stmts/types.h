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
  OP_GT,
  OP_GTE,
  OP_LT,
  OP_LTE,
  OP_EQUALS,
  OP_DIFF,
  OP_AND,
  OP_OR,
  OP_NOT
} Operation;

typedef enum {
  AOP_PLUS,
  AOP_MINUS,
  AOP_TIMES,
  AOP_DIVIDE,
  AOP_EXPONENT,
  AOP_UMINUS
} ArithmeticOp;

typedef enum {
  STMT_WRITE,
  STMT_IF,
  STMT_READ,
  STMT_WHILE,
  STMT_LOGICAL,
  STMT_ARITHMETIC,
  STMT_FACTOR,
  STMT_ATTRIB
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
      struct Stmt* cond;
      struct StmtList* then_block;
      struct StmtList* else_block;
    } if_stmt;

    struct {
      struct Stmt* cond;
      struct StmtList* body;
    } while_stmt;

    struct {
      struct Stmt* left;
      struct Stmt* right;
      Operation op;
    } logical_stmt;

    struct {
      struct Stmt* left;
      struct Stmt* right;
      ArithmeticOp op;
    } arithmetic_stmt;

    struct {
      char* var_name;
      Value value;
      bool uminus;
    } factor_stmt;

    struct {
      char* var_name;
      Stmt* value;
    } attrib_stmt;
  };
} Stmt;

typedef struct StmtList {
  Stmt* stmt;
  struct StmtList* next;
} StmtList;

#endif
