#ifndef FINAL_WORK_TYPES_H
#define FINAL_WORK_TYPES_H

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

typedef struct Expr Expr;
typedef struct ExprList ExprList;
typedef struct Stmt Stmt;
typedef struct StmtList StmtList;
typedef struct TypeInfo TypeInfo;
typedef struct Field Field;
typedef struct Param Param;
typedef struct Symbol Symbol;

const char *describeType(TypeInfo *type);
const char *getTypeString(TypeInfo *type);
void print_program(struct Program *prog);

typedef enum {
  TYPE_INT,
  TYPE_REAL,
  TYPE_BOOL,
  TYPE_CHAR,
  TYPE_STRING,
  TYPE_ARRAY,
  TYPE_RECORD,
  TYPE_ALIAS,
  TYPE_ENUM,
  TYPE__COUNT
} VarType;

static const char *const TypeNames[TYPE__COUNT] = {
    [TYPE_INT] = "integer",   [TYPE_REAL] = "real",     [TYPE_BOOL] = "boolean",
    [TYPE_CHAR] = "char",     [TYPE_STRING] = "string", [TYPE_ARRAY] = "array",
    [TYPE_RECORD] = "record", [TYPE_ALIAS] = "alias",   [TYPE_ENUM] = "enum"};

struct TypeInfo {
  VarType type;
  char *type_name; // Nome do tipo definido pelo usuário (se aplicável)
  union {
    struct {
      int low, high;
      struct TypeInfo *element_type;
    } array_info;
    struct Field *record_fields;
    struct {
      char **identifiers;
      int count;
    } enum_info;
    struct TypeInfo *alias_of; // Referência ao tipo original no caso de alias
  } details;
};

struct Field {
  char *name;
  TypeInfo *type;
  Field *next;
};

struct Param {
  char *name;
  TypeInfo *type;
  Param *next;
};

struct ExprList {
  Expr *expr;
  ExprList *next;
};

typedef enum {
  FUNC_DECL,
  PROC_DECL,
  LABEL_DECL,
  TYPE_DECL,
  VAR_DECL,
  CONST_DECL
} DeclType;

typedef struct Decl {
  DeclType type;
  struct Decl *next;
} Decl;
typedef struct LabelDecl {
  struct LabelList *list;
} LabelDecl;
typedef struct FuncDecl {
  struct FuncList *list;
} FuncDecl;
typedef struct ProcDecl {
  struct ProcList *list;
} ProcDecl;
typedef struct TypeDecl {
  struct TypeList *list;
} TypeDecl;
typedef struct VarDecl {
  struct VarList *list;
} VarDecl;
typedef struct ConstDecl {
  struct ConstList *list;
} ConstDecl;

typedef struct LabelList {
  long int unsined;
  struct LabelList *next;
} LabelList;
typedef struct FuncList {
  char *name;
  struct FuncList *next;
} FuncList;
typedef struct ProcList {
  char *name;
  struct ProcList *next;
} ProcList;
typedef struct TypeList {
  char *name;
  struct TypeList *next;
} TypeList;
typedef struct ConstList {
  char *name;
  struct ConstList *next;
} ConstList;
typedef struct VarList {
  char *name;
  struct VarList *next;
} VarList;
typedef struct IdentifierList {
  char *identifier;
  struct IdentifierList *next;
} IdentifierList;

typedef enum {
  AOP_ADD,
  AOP_SUB,
  AOP_MUL,
  AOP_DIV,
  AOP_NEG,
  AOP_MOD,
  AOP_DIVR
} ArithmeticOp;

typedef enum {
  OP_EQ,
  OP_NEQ,
  OP_LT,
  OP_LTE,
  OP_GT,
  OP_GTE,
  OP_AND,
  OP_OR
} LogicalOp;

typedef enum {
  EXPR_LITERAL,
  EXPR_VARIABLE,
  EXPR_BINARY,
  EXPR_UNARY,
  EXPR_CALL,
  EXPR_INDEX,
  EXPR_FIELD,
  EXPR_FORMATTED_WRITE
} ExprType;

struct Expr {
  ExprType type;
  union {
    struct {
      ArithmeticOp op;
      Expr *operand;
    } unary;
    struct {
      Expr *left;
      union {
        ArithmeticOp aop;
        LogicalOp lop;
      };
      Expr *right;
    } binary;
    struct {
      char *name;
      ExprList *args;
    } call;
    struct {
      Expr *array;
      Expr *index;
    } index;
    struct {
      Expr *record;
      char *field;
    } field;
    struct {
      VarType type;
      union {
        int i_val;
        double f_val;
        bool b_val;
        char c_val;
        char *s_val;
      };
    } literal;
    struct {
      char *var_name;
      int width;
      int precision;
    } formatted;
    char *var_name;
  };
};

typedef enum {
  STMT_ASSIGN,
  STMT_IF,
  STMT_WHILE,
  STMT_FOR,
  STMT_REPEAT,
  STMT_CASE,
  STMT_READ,
  STMT_WRITE,
  STMT_PROC_CALL
} StmtType;

struct Stmt {
  StmtType type;
  union {
    struct {
      Expr *target;
      Expr *value;
    } assign;
    struct {
      Expr *condition;
      StmtList *then_branch;
      StmtList *else_branch;
    } if_stmt;
    struct {
      Expr *condition;
      StmtList *body;
    } while_stmt;
    struct {
      char *var;
      Expr *start;
      Expr *end;
      bool downto;
      StmtList *body;
    } for_stmt;
    struct {
      Expr *condition;
      StmtList *body;
    } repeat_stmt;
    struct {
      Expr *expression;
      // Implementar estrutura para casos
    } case_stmt;
    struct {
      char *var_name;
      bool new_line;
    } read_stmt;
    struct {
      ExprList *args;
      bool new_line;
    } write_stmt;
    struct {
      char *proc_name;
      ExprList *args;
    } proc_call;
  };
};

struct StmtList {
  Stmt *stmt;
  StmtList *next;
};

typedef enum {
  SYMBOL_VAR,
  SYMBOL_CONST,
  SYMBOL_TYPE,
  SYMBOL_FUNC,
  SYMBOL_PROC
} SymbolKind;

typedef union {
  int i_val;
  double f_val;
  bool b_val;
  char c_val;
  char *s_val;
} SymbolValue;

struct Symbol {
  char *name;
  SymbolKind kind;
  TypeInfo *type;
  SymbolValue value;
  Param *params;
  Symbol *next;
};

typedef enum { CONST_INT, CONST_REAL, CONST_STRING } ConstType;

typedef struct Constant {
  char *name;
  ConstType type;
  union {
    int i_val;
    double f_val;
    char *s_val;
  } value;
} Constant;

typedef struct Program {
  char *identifier;
  struct IdentifierList *heading;
  struct Block *block;
} Program;

typedef struct Block {
  Decl *declarations;
  StmtList *stmt_list;
} Block;

#endif // !FINAL_WORK_TYPES
