%require "3.8.2"

%{
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "symbol_table.h"
#include "types.h"
%}

%define api.location.type {YYLTYPE}
%define parse.assert
%define parse.error verbose
%locations

%code requires {
  #include "types.h"
}

%union {
  int ival;
  double fval;
  char cval;
  char* sval;
  bool bval;

  long int integer;
  bool boolean;
  char character;
  double number;
  char* string;

  struct Field *field_list;
  struct Param *param_list;
  struct ArgList *arg_list;

  struct TypeInfo *type;

  char** strlist;

  struct Constant constant;

  struct Expr       *expr;
  struct VarRefExpr *var_ref;
  struct Decl       *decl;
  struct FuncDecl   *func_decl;
  struct TypeDecl   *type_decl;
  struct VarDecl    *var_decl;
  struct ProcDecl   *proc_decl;
  struct ConstDecl  *cons_decl;
  struct LabelDecl  *label_decl;
  struct ProcCall   *proc_call;
}

/* Keywords */
%token PROGRAM VAR CONST TYPE LABEL PROCEDURE FUNCTION BEGIN_TOK END IF THEN ELSE 
%token WHILE DO FOR TO DOWNTO REPEAT UNTIL CASE OF GOTO
%token INTEGER REAL BOOLEAN CHAR ARRAY RECORD SET FILE_TOK STRING
%token READ WRITE READLN WRITELN

/* Symbols */
%token GT GTE LT LTE NEQ EQ
%token AND OR NOT
%token PLUS MINUS TIMES DIVIDE DIV MOD
%token DOT DOTDOT
%token ASSIGN SEMICOLON COMMA COLON L_PAREN R_PAREN L_BRACE R_BRACE L_BRACKET R_BRACKET

%token <character> CHAR_LITERAL
%token <integer> INTEGER_LITERAL
%token <string> STRING_LITERAL
%token <number> REAL_LITERAL
%token <boolean> BOOLEAN_LITERAL
%token <string> IDENTIFIER

%type <long int> INTEGER;
%type <double> REAL;
%type <bool> BOOLEAN;
%type <char> CHAR;
%type <string> STRING;
%type <array> ARRAY;
%type <struct> RECORD;
%type <expr> const_numbers literals term expr procedure_stmt func_call array_access record_access;
%type <var_ref> var_access;
%type <decl> declarations declaration;
%type <func_decl> function_declaration;
%type <type_decl> type_declaration;
%type <var_decl> variable_declaration;
%type <cons_decl> constant_declaration;
%type <label_decl> label_declaration;
%type <proc_decl> procedure_declaration;
%type <proc_call> read write;
%type <arg_list> write_args write_arg;

%type <type> type
%type <field_list> field_decl field_list
%type <param_list> param_list param_seq
%type <strlist> variable_list variable_list_type variable_declaration_list type_assignment_list
%type <constant> constant

%left PLUS MINUS
%left TIMES DIVIDE DIV MOD SQRT
%left AND OR
%precedence NEG
%nonassoc GT GTE LT LTE NEQ EQ IN
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%start program

%%

program: 
      PROGRAM IDENTIFIER heading SEMICOLON block DOT { /* tac_print(generate_stmt_list_tac($2));*/ }
;

heading:
    %empty {}
  |  L_PAREN identifier_list R_PAREN
;

identifier_list:
    IDENTIFIER
  | identifier_list COMMA IDENTIFIER
;

block:
    declarations BEGIN_TOK statement_list END
;

declarations:
    %empty { $$ = NULL; }
  | declarations declaration {}
;

declaration:
    label_declaration { $$ = (struct Decl*)$1; }
  | constant_declaration { $$ = (struct Decl*)$1; }
  | type_declaration { $$ = (struct Decl*)$1; }
  | variable_declaration { $$ = (struct Decl*)$1; }
  | procedure_declaration SEMICOLON { $$ = (struct Decl*)$1; }
  | function_declaration SEMICOLON { $$ = (struct Decl*)$1; }
;

label_declaration:
    LABEL unsigned_integer_list SEMICOLON {
      struct LabelDecl *lb = (LabelDecl*)malloc(sizeof *lb);
      $$ = lb;
    }
;

unsigned_integer_list: 
    INTEGER_LITERAL
  | unsigned_integer_list COMMA INTEGER_LITERAL
;

constant_declaration:
  CONST const_assignment_list SEMICOLON {
      struct ConstDecl *cd = (ConstDecl*)malloc(sizeof *cd);
      $$ = cd;
    }

;

const_assignment_list:
      const_assignment
    | const_assignment_list SEMICOLON const_assignment 
;

const_assignment: 
    IDENTIFIER EQ constant {
      fprintf(stderr, "vamos colocar na synbol table: %s: %d\n", $1, $3.ival);
    }
;

constant:
    INTEGER_LITERAL {
      Constant c;
      c.kind = C_INTEGER;
      c.ival = $1;
      $$ = c;
    }
  | REAL_LITERAL {
      Constant c;
      c.kind = C_REAL;
      c.fval = $1;
      $$ = c;
  }
  | STRING_LITERAL {
      Constant c;
      c.kind = C_STRING;
      c.sval = $1;
      $$ = c;
  }
  | IDENTIFIER {
      Constant c;
      c.kind = C_ID;
      c.id = strdup($1);
      $$ = c;
    }
  | PLUS IDENTIFIER {
      Constant c;
      c.kind = C_ID;
      c.op = '+';
      c.id = strdup($2);
      $$ = c;
    }
  | MINUS IDENTIFIER {
      Constant c;
      c.kind = C_ID;
      c.op = '-';
      c.id = strdup($2);
      $$ = c;
    }
;

type_declaration:
    TYPE type_assignment_list SEMICOLON {
      struct TypeDecl *tp = (TypeDecl*)malloc(sizeof *tp);
      tp->list = $2;
      $$ = tp;
      free($2);
    }

;

type_assignment_list:
    IDENTIFIER EQ type {
      if (add_symbol($1, SKIND_TYPE, $3) == -1) {
        fprintf(stderr, "Error to declare variable %s\n", $1);
      }
      $$[0] = strdup($1);
      $$[1] = NULL;
      free($1);
    }
  | type_assignment_list SEMICOLON IDENTIFIER EQ type {
      int i;
      for (i = 0; $1[i] != NULL; i++);
      if (add_symbol($3, SKIND_TYPE, $5) == -1) {
        fprintf(stderr, "Error to declare variable %s\n", $3);
      }
      $1[i] = strdup($3);
      $1[1+1] = NULL;
      free($3);
      $$ = $1;
    }
;

variable_declaration:
    VAR variable_declaration_list SEMICOLON {
      struct VarDecl *vd = (VarDecl*)malloc(sizeof *vd);
      vd->list = $2;
      $$ = vd;
    }
;

variable_declaration_list:
    variable_list_type { $$ = $1; }
  | variable_declaration_list SEMICOLON variable_list_type {
    int i;
    for (i = 0; $1[i] != NULL; i++);
    int j = 0;
    $$ = (char**)malloc(i * sizeof(char*));
    $$ = $1;
    while($3[j] != NULL) {
      char** tmp = (char**)realloc($$, (i+2) * sizeof(char*));
      tmp[i+j] = $3[j];
      tmp[i+j+1] = NULL;
      j++;
      $$ = tmp;
    }
  }
;

variable_list_type: 
    variable_list COLON type {
      TypeInfo *t = $3;
      for (int i = 0; $1[i] != NULL; i++) {
        if (add_symbol($1[i], SKIND_VAR, t) == -1) {
          fprintf(stderr, "Error to declare variable %s\n", $1[i]);
        }
        free($1[i]);
      }
      $$ = $1;
      free($1);
    }
;

variable_list:
    IDENTIFIER {
      char** l = (char**)malloc(2*sizeof(char**));
      l[0] = strdup($1);
      l[1] = NULL;
      $$ = l;
    }
  | variable_list COMMA IDENTIFIER {
      int i;
      for (i = 0; $1[i] != NULL; i++);
      char** tmp = (char**)realloc($1, (i+2) * sizeof(char*));
      tmp[i] = strdup($3);
      tmp[i+1] = NULL;
      $$ = tmp;
    }
;

type: 
    INTEGER {
      TypeInfo *tmp = (TypeInfo*)malloc(sizeof *tmp);
      tmp->kind = KIND_INT;
      $$ = tmp;
    }
  | STRING {
      TypeInfo *tmp = (TypeInfo*)malloc(sizeof *tmp);
      tmp->kind = KIND_STRING;
      $$ = tmp;
  }
  | REAL {
      TypeInfo *tmp = (TypeInfo*)malloc(sizeof *tmp);
      tmp->kind = KIND_REAL;
      $$ = tmp;
  }
  | CHAR {
      TypeInfo *tmp = (TypeInfo*)malloc(sizeof *tmp);
      tmp->kind = KIND_CHAR;
      $$ = tmp;
  }
  | BOOLEAN {
      TypeInfo *tmp = (TypeInfo*)malloc(sizeof *tmp);
      tmp->kind = KIND_BOOL;
      $$ = tmp;
  }
  | ARRAY L_BRACKET constant DOTDOT constant R_BRACKET OF type {
      TypeInfo *tmp = (TypeInfo*)malloc(sizeof *tmp);
      tmp->kind = KIND_ARRAY;
      tmp->arrayInfo.type=$8;
      tmp->arrayInfo.low=$3.ival;
      if ($5.kind == C_STRING) {
        // Symbol* s = get_symbol_by_name($5.id);
        // tmp.arrayInfo.high=s->data.i;
      }
      $$ = tmp;
  }
  | RECORD field_list END {
      TypeInfo *tmp = (TypeInfo*)malloc(sizeof *tmp);
      tmp->kind = KIND_RECORD;
      tmp->recordFields = $2;
      $$ = tmp;
  }
  | IDENTIFIER {
      TypeInfo *tmp = (TypeInfo*)malloc(sizeof *tmp);
      tmp->kind = KIND_CUSTOM;
      tmp->custom = $1;
  
      // Symbol *s = get_symbol_by_name($1);
      // if (s != NULL && s->skind == SKIND_TYPE) {
      //   printf("Tipo custom: %s at line %d col %d\n", s->name, yylloc.first_line, yylloc.first_column);
      //   printf("Tipo do %s: %s\n", s->name, describeType(s->type));
      // }
      $$ = tmp;
    }
;

field_list:
    field_decl SEMICOLON { $$ = $1; }
  | field_list field_decl SEMICOLON { 
      Field* last = $1;
      while(last->next) last = last->next;
      last->next = $2;
      $$ = $1;
    }
;

field_decl:
    IDENTIFIER COLON type {
      Field* f = (Field*)malloc(sizeof(Field));
      f->name = strdup($1);
      f->type = $3;
      f->next = NULL;
      $$=f;
    }
;

procedure_declaration:
    PROCEDURE IDENTIFIER L_PAREN param_list R_PAREN SEMICOLON block {
      struct ProcDecl *pd = (ProcDecl*)malloc(sizeof *pd);
      $$ = pd;
    }
;

function_declaration:
    FUNCTION IDENTIFIER L_PAREN param_list R_PAREN COLON type SEMICOLON block {
      struct FuncDecl *fd = (FuncDecl*)malloc(sizeof *fd);
      $$ = fd;
    }
;

param_list:
    %empty { $$ = NULL; }
  | param_seq { $$ = $1; }
;

param_seq:
    IDENTIFIER COLON type { 
      Param* p = (Param*)malloc(sizeof(Param));
      p->name = strdup($1);
      // p->type = lookup_type($3);
      p->next = NULL;
      $$ = p;
    }
  | param_seq SEMICOLON IDENTIFIER COLON type { 
      Param* last = $1;
      while(last->next) last = last->next;
      Param* p = (Param*)malloc(sizeof(Param));
      p->name = strdup($3);
      // p->type = lookup_type($5);
      p->next = NULL;
      last->next = p;
      $$ = $1;
    }
;

statement_list:
    statement
  | statement_list SEMICOLON statement
;

statement:
    assign
  | if_stmt
  | while_stmt
  | for_stmt 
  | repeat_stmt
  | case_stmt
  | compound_stmt
  // | func_call
  | procedure_stmt
  | goto_stmt
  | %empty {}
;

assign:
    IDENTIFIER ASSIGN expr
  | record_access ASSIGN expr
  | array_access ASSIGN expr
;

compound_stmt:
  BEGIN_TOK statement_list END
;

procedure_stmt:
    read {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind = EXPR_PROC;
      e->proc = $1;
      $$ = e;
    }
  | write {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind = EXPR_PROC;
      e->proc = $1;
      $$ = e;
    }
  | IDENTIFIER L_PAREN expression_list R_PAREN {
      struct ProcCall *proc = (ProcCall*)malloc(sizeof *proc);
      proc->method = $1;
      proc->list = $<arg_list>3;
  
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind = EXPR_PROC;
      e->proc = proc;
      $$ = e;
  }
;

if_stmt:
    IF expr THEN statement %prec LOWER_THAN_ELSE
  | IF expr THEN statement ELSE statement
;

case_stmt:
  CASE expr OF case_list END
;

case_list:
    case_list case_elem
  | case_elem
;

case_elem:
    INTEGER_LITERAL COLON statement SEMICOLON
  | ELSE
  | procedure_stmt SEMICOLON
;

repeat_stmt:
  REPEAT statement_list UNTIL expr
;

goto_stmt:
  GOTO INTEGER_LITERAL
;

while_stmt:
  WHILE expr DO statement
;

for_stmt:
    FOR IDENTIFIER ASSIGN expr TO expr DO statement
  | FOR IDENTIFIER ASSIGN expr DOWNTO expr DO statement
;

expression_list:
    expr
  | expression_list COMMA expr
  | %empty {}
;

expr: 
    L_PAREN expr R_PAREN {
      $$ = $2;
    }
  | expr PLUS expr {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_ADD;
      e->left   = $1;
      e->right  = $3;
      $$ = e;
  }
  | expr MINUS expr {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_SUB;
      e->left   = $1;
      e->right  = $3;
      $$ = e;
  }
  | expr TIMES expr {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_MUL;
      e->left   = $1;
      e->right  = $3;
      $$ = e;
  }
  | expr DIVIDE expr {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_DIV;
      e->left   = $1;
      e->right  = $3;
      $$ = e;
  }
  | expr DIV expr {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_DIVR;
      e->left   = $1;
      e->right  = $3;
      $$ = e;
  }
  | expr MOD expr{
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_MOD;
      e->left   = $1;
      e->right  = $3;
      $$ = e;
  }
  | expr NEQ expr{
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_NEQ;
      e->left   = $1;
      e->right  = $3;
      $$ = e;
  }
  | expr EQ expr{
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_EQ;
      e->left   = $1;
      e->right  = $3;
      $$ = e;
  }
  | expr LT expr{
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_LT;
      e->left   = $1;
      e->right  = $3;
      $$ = e;
  }
  | expr LTE expr{
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_LTE;
      e->left   = $1;
      e->right  = $3;
      $$ = e;
  }
  | expr GT expr{
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_GT;
      e->left   = $1;
      e->right  = $3;
      $$ = e;
  }
  | expr GTE expr{
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_GTE;
      e->left   = $1;
      e->right  = $3;
      $$ = e;
  }
  | expr OR expr{
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_OR;
      e->left   = $1;
      e->right  = $3;
      $$ = e;
  }
  | expr AND expr{
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_AND;
      e->left   = $1;
      e->right  = $3;
      $$ = e;
  }
  | NOT expr {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_NOT;
      e->left   = NULL;
      e->right  = $2;
      $$ = e;
  }
  | MINUS expr %prec NEG {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_UMINUS;
      e->left   = NULL;
      e->right  = $2;
      $$ = e;
  }
  | func_call { $$ = $1; }
  | term { $$ = $1; }
;

term:
    literals { $$ = $1; }
  | IDENTIFIER {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_ID;
      e->string = $1;
      $$ = e;
  }
  | array_access { $$ = $1; }
  | record_access { $$ = $1; }
  | var_access {
    struct Expr *e = (Expr*)malloc(sizeof *e);
    e->kind = EXPR_VAR;
    e->var_ref = $1;
    $$ = e;
  }
;

var_access:
    IDENTIFIER {
      struct VarRefExpr *vr = (VarRefExpr*)malloc(sizeof *vr);
      vr->string = $1;
      $$ = vr;
      // TODO: adicionar o ponteiro da symbol_table
    }
;

func_call:
    IDENTIFIER L_PAREN expression_list R_PAREN {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_FUNC;
      e->string = $1;
      e->list = $<expr>3;
      $$ = e;
    }
  | SQRT L_PAREN expr R_PAREN {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_SQRT;
      e->right  = $3;
      e->method = "sqrt";
      $$ = e;
  }
;

array_access:
    IDENTIFIER L_BRACKET expr R_BRACKET {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_ARRCE;
      e->string = $1;
      e->expr = $3;
      $$ = e;
    }
  | IDENTIFIER L_BRACKET INTEGER_LITERAL R_BRACKET {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_ARRCL;
      e->string = $1;
      e->integer = $3;
      $$ = e;
  }
;

record_access:
    IDENTIFIER DOT IDENTIFIER {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_RCD;
      e->string = $3;
      e->record = $1;
      $$ = e;
    }
  | array_access DOT IDENTIFIER {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_ARCD;
      e->string = $3;
      e->expr = $1;
      $$ = e;
  }
;

literals:
    const_numbers {
      $$ = $1;
    }
  | STRING_LITERAL{
        struct Expr *e = (Expr*)malloc(sizeof *e);
        e->kind   = EXPR_STR;
        e->string = $1;
        $$ = e;
      }

  | BOOLEAN_LITERAL{
        struct Expr *e = (Expr*)malloc(sizeof *e);
        e->kind   = EXPR_BOOL;
        e->boolean = $1;
        $$ = e;
      }

  | CHAR_LITERAL{
        struct Expr *e = (Expr*)malloc(sizeof *e);
        e->kind   = EXPR_CHAR;
        e->character = $1;
        $$ = e;
      }

;

const_numbers: 
      INTEGER_LITERAL {
        struct Expr *e = (Expr*)malloc(sizeof *e);
        e->kind   = EXPR_INT;
        e->integer = $1;
        $$ = e;
      }
    | REAL_LITERAL {
        struct Expr *e = (Expr*)malloc(sizeof *e);
        e->kind   = EXPR_REAL;
        e->number = $1;
        $$ = e;
      }
;

write:
    WRITE L_PAREN write_args R_PAREN {
      struct ProcCall *proc = (ProcCall*)malloc(sizeof *proc);
      proc->method = "write";
      proc->list = $3;
      $$ = proc;
    }
  | WRITELN L_PAREN write_args R_PAREN {
      struct ProcCall *proc = (ProcCall*)malloc(sizeof *proc);
      proc->method = "writeln";
      proc->list = $3;
      $$ = proc;
  }
  | WRITELN {
      struct ProcCall *proc = (ProcCall*)malloc(sizeof *proc);
      proc->method = "writeln";
      proc->list = NULL;
      $$ = proc;
  }
;

write_args:
    write_arg { $$ = $1; }
  | write_args COMMA write_arg {
    $1->next = $3;
  }
;

write_arg:
    STRING_LITERAL {
      struct ArgList *ag = (ArgList*)malloc(sizeof *ag);
      ag->next = NULL;
      ag->string = $1;
      $$ = ag;
    }
    | IDENTIFIER COLON INTEGER_LITERAL COLON INTEGER_LITERAL {
        // printf(" [FORMAT: %s:%d:%d] ", $1, $3, $5);
        struct VarRefExpr *vr = (VarRefExpr*)malloc(sizeof *vr);
        vr->string = $1;


        struct ArgList *ag = (ArgList*)malloc(sizeof *ag);
        ag->next = NULL;
        ag->var = vr;
        ag->width = $3;
        ag->length = $5;
        $$ = ag;
    }
    | IDENTIFIER {
        // Symbol* s = get_symbol_by_name($1);
        // if (s->type == TYPE_INT) {
        //   printf(" [INTEGER: %d] ", s->data.i);
        // } else if (s->type == TYPE_REAL) {
        //   printf(" [REAL: %.2f] ", s->data.f);
        // } else if (s->type == TYPE_CHAR) {
        //   printf(" [CHAR: %c] ", s->data.c);
        // } else if (s->type == TYPE_BOOL) {
        //   printf(" [BOOL: %s] ", s->data.b ? "true" : "false");
        // } else {
        //   printf(" [VARIAVEL: %s] ", $1);
        // }

        struct VarRefExpr *vr = (VarRefExpr*)malloc(sizeof *vr);
        vr->string = $1;

        struct ArgList *ag = (ArgList*)malloc(sizeof *ag);
        ag->next = NULL;
        ag->var = vr;
        $$ = ag;
    }
    | record_access {
        struct ArgList *ag = (ArgList*)malloc(sizeof *ag);
        ag->next = NULL;
        ag->expr = $1;
        $$ = ag;
    }
;

read:
    READ L_PAREN IDENTIFIER R_PAREN {
      struct ProcCall *proc = (ProcCall*)malloc(sizeof *proc);
      proc->method = "read";
      proc->var = $<var_ref>3;
      $$ = proc;
    }
  | READLN L_PAREN IDENTIFIER R_PAREN {
      struct ProcCall *proc = (ProcCall*)malloc(sizeof *proc);
      proc->method = "readln";
      proc->var = $<var_ref>3;
      $$ = proc;

      // TODO: adicionar ref a var $3 da symbol_table
  }
;

%%
