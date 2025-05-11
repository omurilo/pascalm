#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

typedef union Data {
  int i;
  bool b;
  char c;
  double f;
  char* s;
} Data;

typedef enum VarType {
  TYPE_INT,
  TYPE_FLOAT,
  TYPE_BOOL,
  TYPE_CHAR,
  TYPE_STRING
} VarType;

typedef struct Value {
  VarType type;
  Data data;
} Value;

typedef struct Symbol {
  char name[11];
  VarType type;
  Data data;
} Symbol;

typedef enum Operation {
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

typedef enum ArithmeticOp {
  AOP_PLUS,
  AOP_MINUS,
  AOP_TIMES,
  AOP_DIVIDE,
  AOP_EXPONENT,
  AOP_UMINUS
} ArithmeticOp;

typedef struct Stmt Stmt;
typedef struct StmtList StmtList;
typedef struct Expr Expr;

typedef enum ExprType {
  EXPR_VAR,
  EXPR_LITERAL,
  EXPR_ARITH,
  EXPR_LOGIC
} ExprType;

struct Expr {
  ExprType type;
  int lineno;
  int col;

  union {
    struct {
      Expr* left;
      Expr* right;
      ArithmeticOp op;
    } arith;

    struct {
      Expr* left;
      Expr* right;
      Operation op;
    } logic;

    const char* var_name;
    Value literal;
    bool uminus;
  };
};

typedef enum StmtType {
  STMT_WRITE,
  STMT_IF,
  STMT_READ,
  STMT_WHILE,
  STMT_ATTRIB
} StmtType;

struct Stmt {
  StmtType type;
  int lineno;
  int col;
  union {
    struct {
      char* var_name;
      Expr* expr;
    } write;

    struct {
      const char* var_name;
    } read;

    struct {
      Expr* cond;
      StmtList* then_block;
      StmtList* else_block;
    } if_stmt;

    struct {
      Expr* cond;
      StmtList* body;
    } while_stmt;

    struct {
      const char* var_name;
      Expr* expr;
    } assign;
  };
};

struct StmtList {
  Stmt* stmt;
  StmtList* next;
};

typedef struct {
  char* temp;
  struct TAC* code;
} ExprResult;

typedef struct TAC {
  char* code;
  struct TAC* next;
} TAC;

#endif
