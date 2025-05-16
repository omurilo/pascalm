#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdio.h>

void yyerror(const char *str);
typedef struct Stmt Stmt;
typedef struct StmtList StmtList;
typedef struct Expr Expr;
typedef struct TypeInfo TypeInfo;
typedef struct Field Field;
typedef struct Param Param;

typedef union Data {
  int i;
  bool b;
  char c;
  double f;
  char *s;
} Data;

typedef enum VarType {
  TYPE_INT,
  TYPE_REAL,
  TYPE_BOOL,
  TYPE_CHAR,
  TYPE_RECORD,
  TYPE_ARRAY,
  TYPE_STRING
} VarType;

struct Field {
  char *name;
  TypeInfo *type;
  struct Field *next;
};

struct TypeInfo {
  VarType type;
  Data data;
  union {
    struct {
      int low, high;
      VarType type;
    } arrayInfo;
    Field *recordFields;
  };
};

struct Param {
  char *name;
  TypeInfo type;
  struct Param *next;
};

typedef enum { KIND_VAR, KIND_TYPE, KIND_FUNC, KIND_PROC } SymbolKind;

typedef struct Symbol {
  char *name;
  SymbolKind skind;
  VarType type;
  Data data;
  Param *params;
  struct Symbol *next;
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
} Operation;

typedef enum ArithmeticOp {
  AOP_PLUS,
  AOP_MINUS,
  AOP_TIMES,
  AOP_DIVIDE,
  AOP_UMINUS
} ArithmeticOp;

typedef enum ExprType {
  EXPR_VAR,
  EXPR_LITERAL,
  EXPR_ARITH,
  EXPR_LOGIC,
} ExprType;

struct Expr {
  ExprType type;
  int lineno;
  int col;

  union {
    struct {
      Expr *left;
      Expr *right;
      ArithmeticOp op;
    } arith;

    struct {
      Expr *left;
      Expr *right;
      Operation op;
    } logic;

    const char *var_name;
    // Value literal;
    bool uminus;
  };
};

typedef enum StmtType {
  STMT_WRITE,
  STMT_IF,
  STMT_READ,
  STMT_WHILE,
  STMT_ASSIGN,
  STMT_FUNC,
  STMT_PROC
} StmtType;

struct Stmt {
  StmtType type;
  int lineno;
  int col;
  union {
    struct {
      char *var_name;
      Expr *expr;
    } write;

    struct {
      const char *var_name;
    } read;

    struct {
      Expr *cond;
      StmtList *then_block;
      StmtList *else_block;
    } if_stmt;

    struct {
      Expr *cond;
      StmtList *body;
    } while_stmt;

    struct {
      const char *var_name;
      Expr *expr;
    } assign;
  };
};

struct StmtList {
  Stmt *stmt;
  StmtList *next;
};

typedef struct Constant {
  VarType kind;
  char op;
  char* id;
  int ival;
  double fval;
  char* sval;
} Constant;

// int add_symbol(const char *id, VarType type);
// int get_symbol_index(const char *id);
// void print_value(Value v);
// void print_symbol(Symbol s);
// void print_expr(Expr *e);
//
// Value evaluate_arithmetic_expr(Expr *expr);
// Value evaluate_logical_expr(Expr *expr);
// Value evaluate_factor_expr(Expr *expr);
//
// Stmt *make_stmt_read(char *var_name);
// Stmt *make_stmt_if(Expr *cond, StmtList *then_block, StmtList *else_block);
// Stmt *make_stmt_while(Expr *cond, StmtList *body);
// Stmt *make_stmt_attrib(char *var_name, Expr *expr);
// Stmt *make_stmt_write(char *var_name, Expr *expr);
//
// StmtList *make_stmt_list(Stmt *stmt, StmtList *next);
// StmtList *append_stmt_list(StmtList *list, Stmt *stmt);
//
// Expr *make_literal_expr(VarType type, Value val, bool uminus);
// Expr *make_var_expr(char *name);
// Expr *make_arith_expr(Expr *left, Expr *right, ArithmeticOp op);
// Expr *make_logic_expr(Expr *left, Expr *right, Operation op);
//
// void print_symbol_table();
#endif
