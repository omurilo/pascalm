#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdio.h>

typedef struct YYLTYPE {
  int first_line;
  int first_column;
  int last_line;
  int last_column;
  char *file_name;
} YYLTYPE;

#undef yywrap
int yywrap(void);
int yylex();
int yyparse();

extern FILE *yyin;
extern YYLTYPE yylloc;

extern void yyerror(const char *msg);
const char *describeType(const struct TypeInfo *type);
const char *getTypeString(const struct TypeInfo *type);

// typedef struct Stmt Stmt;
// typedef struct StmtList StmtList;
// typedef struct Expr Expr;
// typedef struct TypeInfo TypeInfo;
// typedef struct Field Field;
// typedef struct Param Param;
//
typedef union Data {
  long int i;
  bool b;
  char c;
  double f;
  char *s;
} Data;

struct Field {
  char *name;
  struct TypeInfo *type;
  struct Field *next;
};

typedef enum {
  KIND_INT,
  KIND_CHAR,
  KIND_ARRAY,
  KIND_RECORD,
  KIND_REAL,
  KIND_STRING,
  KIND_CUSTOM,
  KIND_BOOL,
  KIND__COUNT
} TypeKind;

static const char * const KindNames[KIND__COUNT] = {
    [KIND_INT]    = "integer",
    [KIND_CHAR]   = "char",
    [KIND_ARRAY]  = "array",
    [KIND_RECORD] = "record",
    [KIND_REAL]   = "real",
    [KIND_STRING] = "string",
    [KIND_CUSTOM] = "custom",
    [KIND_BOOL]   = "boolean"
};

struct TypeInfo {
  TypeKind kind;
  char *custom;
  union {
    struct {
      int low, high;
      struct TypeInfo *type;
    } arrayInfo;
    struct Field *recordFields;
  };
};

struct Param {
  char *name;
  struct TypeInfo type;
  struct Param *next;
};

typedef enum { SKIND_VAR, SKIND_TYPE, SKIND_FUNC, SKIND_PROC } SymbolKind;
typedef struct Symbol {
  char *name;
  SymbolKind skind;
  struct TypeInfo *type;
  Data data;
  struct Param *params;
  struct Symbol *next;
} Symbol;

// struct Expr {
//   ExprType type;
//   int lineno;
//   int col;
//
//   union {
//     struct {
//       Expr *left;
//       Expr *right;
//       ArithmeticOp op;
//     } arith;
//
//     struct {
//       Expr *left;
//       Expr *right;
//       Operation op;
//     } logic;
//
//     const char *var_name;
//     // Value literal;
//     bool uminus;
//   };
// };
//
// typedef enum StmtType {
//   STMT_WRITE,
//   STMT_IF,
//   STMT_READ,
//   STMT_WHILE,
//   STMT_ASSIGN,
//   STMT_FUNC,
//   STMT_PROC
// } StmtType;
//
// struct Stmt {
//   StmtType type;
//   int lineno;
//   int col;
//   union {
//     struct {
//       char *var_name;
//       Expr *expr;
//     } write;
//
//     struct {
//       const char *var_name;
//     } read;
//
//     struct {
//       Expr *cond;
//       StmtList *then_block;
//       StmtList *else_block;
//     } if_stmt;
//
//     struct {
//       Expr *cond;
//       StmtList *body;
//     } while_stmt;
//
//     struct {
//       const char *var_name;
//       Expr *expr;
//     } assign;
//   };
// };
//
// struct StmtList {
//   Stmt *stmt;
//   StmtList *next;
// };
//

typedef struct Decl {
} Decl;

typedef enum {
  EXPR_ADD,
  EXPR_SUB,
  EXPR_MUL,
  EXPR_DIV,
  EXPR_DIVR,
  EXPR_MOD,
  EXPR_SQRT,
  EXPR_EQ,
  EXPR_NEQ,
  EXPR_LT,
  EXPR_LTE,
  EXPR_GT,
  EXPR_GTE,
  EXPR_AND,
  EXPR_OR,
  EXPR_NOT,
  EXPR_UMINUS,
  EXPR_INT,
  EXPR_REAL,
  EXPR_CHAR,
  EXPR_BOOL,
  EXPR_STR,
  EXPR_ID,
  EXPR_VAR,
  EXPR_ARRCL,
  EXPR_ARRCE,
  EXPR_FUNC,
  EXPR_RCD,
  EXPR_ARCD,
  EXPR_PROC
} ExprKind;

typedef struct Expr {
  ExprKind kind;
  struct Expr *left;
  struct Expr *right;
  long int integer;
  double number;
  char character;
  char *string;
  bool boolean;
  struct Expr *expr;
  struct VarRefExpr *var_ref;
  const char *method;
  struct Expr *list;
  char *record;
  struct ProcCall *proc;
} Expr;

typedef struct VarRefExpr {
  char *string;
} VarRefExpr;

typedef struct LabelDecl {
} LabelDecl;
typedef struct FuncDecl {
} FuncDecl;
typedef struct ProcDecl {
} ProcDecl;
typedef struct TypeDecl {
  char **list;
} TypeDecl;
typedef struct VarDecl {
  char **list;
} VarDecl;
typedef struct ConstDecl {
} ConstDecl;
typedef struct ArgList {
  char *string;
  int width;
  int length;
  struct Expr *expr;
  struct VarRefExpr *var;
  struct ArgList *next;
} ArgList;

typedef struct ProcCall {
  char *method;
  struct ArgList *list;
  struct VarRefExpr *var;
} ProcCall;

typedef enum { C_INTEGER, C_STRING, C_REAL, C_ID } ConstKind;

typedef struct Constant {
  ConstKind kind;
  char op;
  char *id;
  int ival;
  double fval;
  char *sval;
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
