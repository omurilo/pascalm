%require "3.8.2"

%{
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <new>
#include "symbol_table.h"
#include "final_work_types.h"

#define NEW(type, var)                                   \
  do {                                                   \
    var = new(std::nothrow) type();                      \
    if (!var) {                                          \
      yyerror("out of memory");                          \
      YYABORT;                                           \
    }                                                    \
  } while (0)
%}

%define api.location.type {YYLTYPE}
%define parse.assert
%define parse.error verbose
%locations

%code requires {
  #include "final_work_types.h"
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

  Field *field_list;
  Param *param_list;

  TypeInfo *type;

  char** strlist;



  struct Constant *constant;

  Expr              *expr;
  ExprList          *expr_list;
  struct Decl       *decl;
  struct FuncDecl   *func_decl;
  struct TypeDecl   *type_decl;
  struct VarDecl    *var_decl;
  struct ProcDecl   *proc_decl;
  struct ConstDecl  *cons_decl;
  struct LabelDecl  *label_decl;
  struct Block      *block;
  struct Program    *program;

  struct VarList *var_list;
  struct LabelList *label_list;
  struct FuncList *func_list;
  struct ProcList *proc_list;
  struct TypeList *type_list;
  struct ConstList *const_list;
  struct IdentifierList *id_list;

  Stmt      *stmt;
  StmtList  *stmt_list;
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

%type <decl> declarations declaration;
%type <func_decl> function_declaration;
%type <type_decl> type_declaration;
%type <var_decl> variable_declaration;
%type <cons_decl> constant_declaration;
%type <label_decl> label_declaration;
%type <proc_decl> procedure_declaration;


%type <type> type
%type <id_list>  identifier_list heading  

%type <var_list> variable_list variable_list_type variable_declaration_list 
// %type <func_list> 
%type <label_list> unsigned_integer_list
// %type <proc_list> 
%type <const_list> const_assignment_list
%type <type_list> type_assignment_list

%type <constant> const_assignment;

%type <field_list> field_decl field_list
%type <param_list> param_list param_seq
%type <expr_list> expression_list write_args;

%type <expr> expr const_numbers literals term array_access record_access var_access write_arg func_call constant;
%type <stmt_list> statement_list 
%type <stmt> statement for_stmt assign if_stmt while_stmt repeat_stmt case_stmt compound_stmt goto_stmt procedure_stmt read write;

%type <program> program;
%type <block> block;

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
      PROGRAM IDENTIFIER heading SEMICOLON block DOT { 
        Program *prog; NEW(Program, prog);
        prog->block = $5;
        prog->identifier = $2;
        prog->heading = $3;
        $$ = prog;

        print_program($$);
      /* tac_print(generate_stmt_list_tac($2));*/
      }
;

heading:
    %empty {}
  |  L_PAREN identifier_list R_PAREN {
    $$ = $2;
  }
;

identifier_list:
    IDENTIFIER {
      struct IdentifierList *id; NEW(struct IdentifierList, id);
      id->identifier = strdup($1);
      id->next = NULL;

      $$ = id;
      free($1);
    }
  | identifier_list COMMA IDENTIFIER {
      struct IdentifierList *new_node; NEW(struct IdentifierList, new_node);
      new_node->identifier = strdup($3);
      new_node->next = NULL;

      if ($1 == NULL) {
        $$ = new_node;
      } else {
        struct IdentifierList *id = $1;
        while(id->next != NULL) {
          id = id->next;
        }
        id->next = new_node;
        $$ = id;
      }
      free($3);
  }
;

block:
    declarations BEGIN_TOK statement_list END {
      struct Block *bk; NEW(struct Block, bk);
      bk->declarations = $1;
      bk->stmt_list = $3;
      $$ = bk;
    }
;

declarations:
    %empty { $$ = NULL; }
  | declarations declaration {
    if ($1 == NULL) {
      $$ = $2;
    } else {
      struct Decl *temp = $1;
      while(temp->next != NULL) {
        temp = temp->next;
      }
      temp->next = $2;
      $$ = temp;
    }
  }
;

declaration:
    label_declaration { $$ = (struct Decl*)$1; $$->type = LABEL_DECL; }
  | constant_declaration { $$ = (struct Decl*)$1; $$->type = CONST_DECL; }
  | type_declaration { $$ = (struct Decl*)$1; $$->type = TYPE_DECL; }
  | variable_declaration { $$ = (struct Decl*)$1; $$->type = VAR_DECL; }
  | procedure_declaration SEMICOLON { $$ = (struct Decl*)$1; $$->type = PROC_DECL; }
  | function_declaration SEMICOLON { $$ = (struct Decl*)$1; $$->type = FUNC_DECL; }
;

label_declaration:
    LABEL unsigned_integer_list SEMICOLON {
      struct LabelDecl *lb;
			NEW(struct LabelDecl, lb);
      lb->list = $2;
      $$ = lb;
    }
;

unsigned_integer_list: 
    INTEGER_LITERAL {
      struct LabelList *ll; NEW(struct LabelList, ll);
      ll->unsined = $1;
      ll->next = NULL;
      $$ = ll;
    }
  | unsigned_integer_list COMMA INTEGER_LITERAL {
      struct LabelList *new_node; NEW(struct LabelList, new_node);
      new_node->unsined = $3;
      new_node->next = NULL;

      struct LabelList *ll = $1;
      while(ll->next) ll = ll->next;
      ll->next = new_node;
      $$ = $1;
  }
;

constant_declaration:
  CONST const_assignment_list SEMICOLON {
      struct ConstDecl *cd;
			NEW(struct ConstDecl, cd);
      cd->list = $2;
      $$ = cd;
    }

;

const_assignment_list:
      const_assignment {
        struct ConstList *cl; NEW(struct ConstList, cl);
        cl->name = $1->name;
        cl->next = NULL;
        $$ = cl;
      }
    | const_assignment_list SEMICOLON const_assignment {
      struct ConstList *new_node; NEW(struct ConstList, new_node);
      new_node->name = $3->name;
      new_node->next = NULL;

      struct ConstList *cl = $1;
      while(cl->next) cl = cl->next;
      cl->next = new_node;
      $$ = $1;
      free($3);
    }
;

const_assignment: 
    IDENTIFIER EQ constant {
      Constant *c; NEW(Constant, c);
      TypeInfo *t; NEW(TypeInfo, t);
      c->name = strdup($1);
      
      if ($3->type == EXPR_LITERAL) {
        t->type = $3->literal.type;
        if ($3->literal.type == TYPE_INT) {
          c->type = CONST_INT;
          c->value.i_val = $3->literal.i_val;
        } else if ($3->literal.type == TYPE_REAL) {
          c->type = CONST_REAL;
          c->value.f_val = $3->literal.f_val;
        } else if ($3->literal.type == TYPE_STRING) {
          c->type = CONST_STRING;
          c->value.s_val = $3->literal.s_val;
        } else {
          yyerror("Type mismatch on constant definition");
        }
      } else if ($3->type == EXPR_VARIABLE) {
        Symbol *s = get_symbol_by_name($3->var_name);
        t->type = s->type->type;
        if (s->type->type == TYPE_INT) {
          c->type = CONST_INT;
          c->value.i_val = s->value.i_val;
        } else if (s->type->type == TYPE_REAL) {
          c->type = CONST_REAL;
          c->value.f_val = s->value.f_val;
        } else if (s->type->type == TYPE_STRING) {
          c->type = CONST_STRING;
          c->value.s_val = s->value.s_val;
        } else {
          yyerror("Type mismatch on constant definition");
        }
      } else {
        yyerror("Type mismatch on constant definition");
      }

      if (!add_symbol(c->name, SYMBOL_CONST, t, (SymbolValue){0}, NULL, NULL)) {
        fprintf(stderr, "Error to declare variable %s\n", c->name);
      }

      // fprintf(stderr, "vamos colocar na synbol table: %s: %d or  %.2f or %s\n", $1, c->value.i_val, c->value.f_val, c->value.s_val);
      free($3);
      free($1);
    }
;

constant:
    const_numbers {
      $$ = $1;
    }
  | PLUS const_numbers {
      $$ = $2;
    }
  | MINUS const_numbers {
      if ($2->literal.type == TYPE_INT) {
        $2->literal.i_val = -$2->literal.i_val;
      } else {
        $2->literal.f_val = -$2->literal.f_val;
      }

      $$ = $2;
    }
  | IDENTIFIER {
      Symbol *s = get_symbol_by_name($1);
      if (s->kind == SYMBOL_CONST) {
        Expr *e; NEW(Expr, e);
        e->type = EXPR_VARIABLE;
        e->var_name = strdup($1);
        $$ = e;
        free($1);
      }
    }
  | PLUS IDENTIFIER {
      Symbol *s = get_symbol_by_name($2);
      if (s->kind == SYMBOL_CONST) {
        Expr *e; NEW(Expr, e);
        e->type = EXPR_VARIABLE;
        e->var_name = strdup($2);
        $$ = e;
        free($2);
      }
    }
  | MINUS IDENTIFIER {
      Symbol *s = get_symbol_by_name($2);
      if (s->kind == SYMBOL_CONST) {
        Expr *e; NEW(Expr, e);
        e->type = EXPR_VARIABLE;
        e->var_name = strdup($2);
        e->unary.op = AOP_SUB;
        $$ = e;
        free($2);
      }
    }
  | STRING_LITERAL {
      Expr *e; NEW(Expr, e);
      e->type = EXPR_LITERAL;
      e->literal.type = TYPE_STRING;
      e->literal.s_val = strdup($1);
      $$ = e;
      free($1);
    }
;

type_declaration:
    TYPE type_assignment_list SEMICOLON {
      struct TypeDecl *tp;
			NEW(struct TypeDecl, tp);
      tp->list = $2;
      $$ = tp;
      free($2);
    }

;

type_assignment_list:
    IDENTIFIER EQ type {
      struct TypeList *tl; NEW(struct TypeList, tl);
      tl->name = strdup($1);
      tl->next = NULL;
      
      if (!add_symbol(tl->name, SYMBOL_TYPE, $3, (SymbolValue){0}, NULL, NULL)) {
        fprintf(stderr, "Error to declare variable %s\n", tl->name);
      }

      $$ = tl;
      free($1);
    }
  | type_assignment_list SEMICOLON IDENTIFIER EQ type {
      struct TypeList *new_node; NEW(struct TypeList, new_node);
      new_node->name = strdup($3);
      new_node->next = NULL;

      if (!add_symbol(new_node->name, SYMBOL_TYPE, $5, (SymbolValue){0}, NULL, NULL)) {
        fprintf(stderr, "Error to declare variable %s\n", new_node->name);
      }

      if ($1 == NULL) {
        $$ = new_node;
      } else {
        struct TypeList *tl = $1;
        while(tl->next) tl = tl->next;
        tl->next = new_node;

        $$ = $1;
      }
    }
;

variable_declaration:
    VAR variable_declaration_list SEMICOLON {
      struct VarDecl *vd;
			NEW(struct VarDecl, vd);
      vd->list = $2;
      $$ = vd;
    }
;

variable_declaration_list:
    variable_list_type { $$ = $1; }
  | variable_declaration_list SEMICOLON variable_list_type {
    if ($1 == NULL) {
      $$ = $3;
    } else {
      struct VarList *vl = $1;
      while(vl->next != NULL) {
        vl = vl->next;
      }
      vl->next = $3;
      $$ = vl;
    }
  }
;

variable_list_type: 
    variable_list COLON type {
      struct VarList *vl = $1;
      TypeInfo *t = $3;
      
      while(vl) {
        if (!add_symbol(vl->name, SYMBOL_VAR, t, (SymbolValue){0}, NULL, NULL)) {
          fprintf(stderr, "Error to declare variable %s\n", vl->name);
        }
        VarList *temp = vl;
        vl = vl->next;
        free(temp->name);
        free(temp);
      }

      $$ = vl;
    }
;

variable_list:
    IDENTIFIER {
      struct VarList *vl; NEW(struct VarList, vl);
      vl->name = strdup($1);
      vl->next = NULL;
      $$ = vl;
      free($1);
    }
  | variable_list COMMA IDENTIFIER {
      struct VarList *new_node; NEW(struct VarList, new_node);
      new_node->name = strdup($3);
      new_node->next = NULL;

      struct VarList *vl = $1;
      while(vl->next) vl = vl->next;
      vl->next = new_node;
      $$ = vl;
      free($3);
    }
;

type: 
    INTEGER {
      TypeInfo *tmp;
			NEW(TypeInfo, tmp);
      tmp->type = TYPE_INT;
      $$ = tmp;
    }
  | STRING {
      TypeInfo *tmp;
			NEW(TypeInfo, tmp);
      tmp->type = TYPE_STRING;
      $$ = tmp;
  }
  | REAL {
      TypeInfo *tmp;
			NEW(TypeInfo, tmp);
      tmp->type = TYPE_REAL;
      $$ = tmp;
  }
  | CHAR {
      TypeInfo *tmp;
			NEW(TypeInfo, tmp);
      tmp->type = TYPE_CHAR;
      $$ = tmp;
  }
  | BOOLEAN {
      TypeInfo *tmp;
			NEW(TypeInfo, tmp);
      tmp->type = TYPE_BOOL;
      $$ = tmp;
  }
  | ARRAY L_BRACKET constant DOTDOT constant R_BRACKET OF type {
      TypeInfo *tmp;
			NEW(TypeInfo, tmp);
      tmp->type = TYPE_ARRAY;
      tmp->details.array_info.element_type = $8;
      
      switch($3->type) {
        case EXPR_VARIABLE: {
          Symbol *s = get_symbol_by_name($3->var_name);
          if (s->kind == SYMBOL_CONST) {
            if (s->type->type == TYPE_INT) {
              tmp->details.array_info.low = s->value.i_val;
            } else if (s->type->type == TYPE_REAL) {
              tmp->details.array_info.low = s->value.f_val;
            } else {
              yyerror("type mismatch on array limit low");
            }
          }
          break;
        }
        case EXPR_LITERAL:
          if ($3->literal.type == TYPE_INT) {
            tmp->details.array_info.low = $3->literal.i_val;
          } else if ($3->literal.type == TYPE_REAL) {
            tmp->details.array_info.low = $3->literal.f_val;
          } else {
            yyerror("type mismatch on array limit low");
          }
          break;
        default:
          yyerror("type mismatch on array limit low");
      }
      switch($5->type) {
        case EXPR_VARIABLE: {
          Symbol *s = get_symbol_by_name($5->var_name);
          if (s->kind == SYMBOL_CONST) {
            if (s->type->type == TYPE_INT) {
              tmp->details.array_info.high = s->value.i_val;
            } else if (s->type->type == TYPE_REAL) {
              tmp->details.array_info.high = s->value.f_val;
            } else {
              yyerror("type mismatch on array limit low");
            }
          }
          break;
        }
        case EXPR_LITERAL:
          if ($5->literal.type == TYPE_INT) {
            tmp->details.array_info.high = $5->literal.i_val;
          } else if ($5->literal.type == TYPE_REAL) {
            tmp->details.array_info.high = $5->literal.f_val;
          } else {
            yyerror("type mismatch on array limit high");
          }
          break;
        default:
          yyerror("type mismatch on array limit high");
      }
      $$ = tmp;
  }
  | RECORD field_list END {
      TypeInfo *tmp;
			NEW(TypeInfo, tmp);
      tmp->type = TYPE_RECORD;
      tmp->details.record_fields = $2;
      $$ = tmp;
  }
  | IDENTIFIER {
      TypeInfo *tmp;
			NEW(TypeInfo, tmp);
      tmp->type = TYPE_ALIAS;
      tmp->type_name = strdup($1);
  
      Symbol* s = get_symbol_by_name($1);
      tmp->details.alias_of = s->type;

      //TODO: if pascal has enum, how to make the enum info?
  
      // Symbol *s = get_symbol_by_name($1);
      // if (s != NULL && s->skind == SYMBOL_TYPE) {
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
      Field* f;
			NEW(Field, f);
      f->name = strdup($1);
      f->type = $3;
      f->next = NULL;
      $$=f;
    }
;

procedure_declaration:
    PROCEDURE IDENTIFIER L_PAREN param_list R_PAREN SEMICOLON block {
      struct ProcDecl *pd;
			NEW(struct ProcDecl, pd);
      $$ = pd;
    }
;

function_declaration:
    FUNCTION IDENTIFIER L_PAREN param_list R_PAREN COLON type SEMICOLON block {
      struct FuncDecl *fd;
			NEW(struct FuncDecl, fd);
      $$ = fd;
    }
;

param_list:
    %empty { $$ = NULL; }
  | param_seq { $$ = $1; }
;

param_seq:
    IDENTIFIER COLON type { 
      Param* p;
			NEW(Param, p);
      p->name = strdup($1);
      // p->type = lookup_type($3);
      p->next = NULL;
      $$ = p;
    }
  | param_seq SEMICOLON IDENTIFIER COLON type { 
      Param* last = $1;
      while(last->next) last = last->next;
      Param* p;
			NEW(Param, p);
      p->name = strdup($3);
      // p->type = lookup_type($5);
      p->next = NULL;
      last->next = p;
      $$ = $1;
    }
;

statement_list:
    statement {
      StmtList *sl; NEW(StmtList, sl);
      sl->stmt = $1;
      sl->next = NULL;
      $$ = sl;
    }
  | statement_list SEMICOLON statement {
      StmtList *sl = $1;
      while(sl->next) sl = sl->next;
      StmtList *new_stmt; NEW(StmtList, new_stmt);
      new_stmt->stmt = $3;
      new_stmt->next = NULL;
      sl->next = new_stmt;
      $$ = sl;
  }
;

statement:
    assign
  | if_stmt
  | while_stmt
  | for_stmt 
  | repeat_stmt
  | case_stmt
  | compound_stmt
  | procedure_stmt
  | goto_stmt
  | %empty {}
;

assign:
    IDENTIFIER ASSIGN expr {
      Expr *e; NEW(Expr, e);
      e->type = EXPR_VARIABLE;
      e->var_name = strdup($1);

      Stmt *st; NEW(Stmt, st);
      st->type = STMT_ASSIGN;
      st->assign.target = e;
      st->assign.value = $3;
      free($1);
      $$ = st;
    }
  | record_access ASSIGN expr {
      Stmt *st; NEW(Stmt, st);
      st->type = STMT_ASSIGN;
      st->assign.target = $1;
      st->assign.value = $3;
      $$ = st;
    }
  | array_access ASSIGN expr {
      Stmt *st; NEW(Stmt, st);
      st->type = STMT_ASSIGN;
      st->assign.target = $1;
      st->assign.value = $3;
      $$ = st;
    }
;

compound_stmt:
  BEGIN_TOK statement_list END
;

procedure_stmt:
    read {
      $$ = $1;
    }
  | write {
      $$ = $1;
    }
  | IDENTIFIER L_PAREN expression_list R_PAREN {
      Stmt *st; NEW(Stmt, st);
      st->type = STMT_PROC_CALL;
      st->proc_call.proc_name = strdup($1);
      st->proc_call.args = $3;
      $$ = st;
      free($1);
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
    FOR IDENTIFIER ASSIGN expr TO expr DO statement_list {
      struct Stmt *ft;
      NEW(Stmt, ft);
      ft->for_stmt.var = strdup($2);
      ft->for_stmt.downto = false;
      ft->for_stmt.start = $4;
      ft->for_stmt.end = $6;
      ft->for_stmt.body = $8;

      free($2);
      $$ = ft;
    }
  | FOR IDENTIFIER ASSIGN expr DOWNTO expr DO statement_list {
      struct Stmt *ft;
      NEW(Stmt, ft);
      ft->for_stmt.var = strdup($2);
      ft->for_stmt.downto = true;
      ft->for_stmt.start = $4;
      ft->for_stmt.end = $6;
      ft->for_stmt.body = $8;

      free($2);
      $$ = ft;
  }
;

expression_list:
    expr {
      ExprList *el; NEW(ExprList, el);
      el->expr = $1;
      el->next = NULL;
      $$ = el;
    }
  | expression_list COMMA expr {
      ExprList *el; NEW(ExprList, el);
      el->expr = $3;
      el->next = $1;
      $$ = el;
      // TODO: verificar integridade, se não, comparar com field_list
  }
  | %empty {}
;

expr: 
    L_PAREN expr R_PAREN {
      $$ = $2;
    }
  | expr PLUS expr {
      Expr *e;
			NEW(Expr, e);
      e->type   = EXPR_BINARY;
      e->binary.left = $1;
      e->binary.right = $3;
      e->binary.aop = AOP_ADD;
      $$ = e;
    }
  | expr MINUS expr {
      Expr *e;
			NEW(Expr, e);
      e->type   = EXPR_BINARY;
      e->binary.left = $1;
      e->binary.right = $3;
      e->binary.aop = AOP_SUB;
      $$ = e;
   }
  | expr TIMES expr {
      Expr *e;
			NEW(Expr, e);
      e->type   = EXPR_BINARY;
      e->binary.left = $1;
      e->binary.right = $3;
      e->binary.aop = AOP_MUL;
      $$ = e;
    }
  | expr DIVIDE expr {
      Expr *e;
			NEW(Expr, e);
      e->type   = EXPR_BINARY;
      e->binary.left = $1;
      e->binary.right = $3;
      e->binary.aop = AOP_DIV;
      $$ = e;
    }
  | expr DIV expr {
      Expr *e;
			NEW(Expr, e);
      e->type   = EXPR_BINARY;
      e->binary.left = $1;
      e->binary.right = $3;
      e->binary.aop = AOP_DIVR;
      $$ = e;
    }
  | expr MOD expr{
      Expr *e;
			NEW(Expr, e);
      e->type   = EXPR_BINARY;
      e->binary.left = $1;
      e->binary.right = $3;
      e->binary.aop = AOP_MOD;
      $$ = e;
    }
  | expr NEQ expr{
      Expr *e;
			NEW(Expr, e);
      e->type   = EXPR_BINARY;
      e->binary.left = $1;
      e->binary.right = $3;
      e->binary.lop = OP_NEQ;
      $$ = e;
    }
  | expr EQ expr{
      Expr *e;
			NEW(Expr, e);
      e->type   = EXPR_BINARY;
      e->binary.left = $1;
      e->binary.right = $3;
      e->binary.lop = OP_EQ;
      $$ = e;
    }
  | expr LT expr{
      Expr *e;
			NEW(Expr, e);
      e->type   = EXPR_BINARY;
      e->binary.left = $1;
      e->binary.right = $3;
      e->binary.lop = OP_LT;
      $$ = e;
   }
  | expr LTE expr{
      Expr *e;
			NEW(Expr, e);
      e->type   = EXPR_BINARY;
      e->binary.left = $1;
      e->binary.right = $3;
      e->binary.lop = OP_LTE;
      $$ = e;
   }
  | expr GT expr{
      Expr *e;
			NEW(Expr, e);
      e->type   = EXPR_BINARY;
      e->binary.left = $1;
      e->binary.right = $3;
      e->binary.lop = OP_GT;
      $$ = e;
    }
  | expr GTE expr{
      Expr *e;
			NEW(Expr, e);
      e->type   = EXPR_BINARY;
      e->binary.left = $1;
      e->binary.right = $3;
      e->binary.lop = OP_GTE;
      $$ = e;
    }
  | expr OR expr{
      Expr *e;
			NEW(Expr, e);
      e->type   = EXPR_BINARY;
      e->binary.left = $1;
      e->binary.right = $3;
      e->binary.lop = OP_OR;
      $$ = e;
    }
  | expr AND expr{
      Expr *e;
			NEW(Expr, e);
      e->type   = EXPR_BINARY;
      e->binary.left = $1;
      e->binary.right = $3;
      e->binary.lop = OP_AND;
      $$ = e;
    }
  | NOT expr {
      Expr *e;
			NEW(Expr, e);
      e->type = EXPR_UNARY;
      e->unary.operand = $2;
      e->unary.op = AOP_NEG;
      $$ = e;
    }
  | MINUS expr %prec NEG {
      Expr *e;
			NEW(Expr, e);
      e->type = EXPR_UNARY;
      e->unary.operand = $2;
      e->unary.op = AOP_SUB;
      $$ = e;
    }
  | func_call { $$ = $1; }
  | term { $$ = $1; }
;

term:
    literals { $$ = $1; }
  | array_access { $$ = $1; }
  | record_access { $$ = $1; }
  | var_access {  $$ = $1; }
;

var_access:
    IDENTIFIER {
      Expr *e; NEW(Expr, e);
      e->type = EXPR_VARIABLE;
      e->var_name = strdup($1);
      $$ = e;
      free($1);
    }
;

func_call:
    IDENTIFIER L_PAREN expression_list R_PAREN {
      Expr *e;
			NEW(Expr, e);
      e->type   = EXPR_CALL;
      e->call.name = strdup($1);
      e->call.args = $3;
      $$ = e;
      free($1);
    }
  | SQRT L_PAREN expr R_PAREN {
      ExprList *list; NEW(ExprList, list);
      list->expr = $3;
      list->next = NULL;

      Expr *e;
			NEW(Expr, e);
      e->type   = EXPR_CALL;
      e->call.name = strdup("sqrt");
      e->call.args = list;
      $$ = e;
    }
;

array_access:
    IDENTIFIER L_BRACKET expr R_BRACKET {
      Expr *array; NEW(Expr, array);
      array->type = EXPR_VARIABLE;
      array->var_name = strdup($1);

      Expr *e;
			NEW(Expr, e);
      e->type   = EXPR_INDEX;
      e->index.array  = array;
      e->index.index  = $3;
      $$ = e;
      free($1);
    }
  | IDENTIFIER L_BRACKET const_numbers R_BRACKET {
      Expr *array; NEW(Expr, array);
      array->type = EXPR_VARIABLE;
      array->var_name = strdup($1);

      Expr *e;
			NEW(Expr, e);
      e->type   = EXPR_INDEX;
      e->index.array  = array;
      e->index.index  = $3;
      $$ = e;
      free($1);
    }
;

record_access:
    IDENTIFIER DOT IDENTIFIER {
      Expr *record; NEW(Expr, record);
      record->type = EXPR_VARIABLE;
      record->var_name = strdup($1);
      
      Expr *e;
      NEW(Expr, e);
      e->type = EXPR_FIELD;
      e->field.field = strdup($3);
      e->field.record = record;
      $$ = e;
      free($1);
      free($3);
    }
  | array_access DOT IDENTIFIER {
      Expr *e;
      NEW(Expr, e);
      e->type = EXPR_FIELD;
      e->field.field = strdup($3);
      e->field.record = $1;
      $$ = e;
      free($3);
   }
;

literals:
    const_numbers {
      $$ = $1;
    }
  | STRING_LITERAL{
      Expr *e;
      NEW(Expr, e);
      e->type = EXPR_LITERAL;
      e->literal.type = TYPE_STRING;
      e->literal.s_val = strdup($1);
      $$ = e;
      free($1);
    }
  | BOOLEAN_LITERAL{
      Expr *e;
      NEW(Expr, e);
      e->type = EXPR_LITERAL;
      e->literal.type = TYPE_BOOL;
      e->literal.b_val = $1;
      $$ = e;
    }
  | CHAR_LITERAL{
      Expr *e;
      NEW(Expr, e);
      e->type = EXPR_LITERAL;
      e->literal.type = TYPE_CHAR;
      e->literal.c_val = $1;
      $$ = e;
    }
;

const_numbers: 
      INTEGER_LITERAL {
        Expr *e;
        NEW(Expr, e);
        e->type = EXPR_LITERAL;
        e->literal.type = TYPE_INT;
        e->literal.i_val = $1;
        $$ = e;
      }
    | REAL_LITERAL {
        Expr *e;
        NEW(Expr, e);
        e->type = EXPR_LITERAL;
        e->literal.type = TYPE_REAL;
        e->literal.f_val = $1;
        $$ = e;
      }
;

write:
    WRITE L_PAREN write_args R_PAREN {
      Stmt *st; NEW(Stmt, st);
      st->type = STMT_WRITE;
      st->write_stmt.args = $3;
      st->write_stmt.new_line = false;
      $$ = st;
    }
  | WRITELN L_PAREN write_args R_PAREN {
      Stmt *st; NEW(Stmt, st);
      st->type = STMT_WRITE;
      st->write_stmt.args = $3;
      st->write_stmt.new_line = true;
      $$ = st;
    }
  | WRITELN {
      Stmt *st; NEW(Stmt, st);
      st->type = STMT_WRITE;
      st->write_stmt.args = NULL;
      st->write_stmt.new_line = true;
      $$ = st;
    }
;

write_args:
    write_arg {
      ExprList *el; NEW(ExprList, el);
      el->expr = $1;
      el->next = NULL;
      $$ = el;
    }
  | write_args COMMA write_arg {
      ExprList *el; NEW(ExprList, el);
      el->expr = $3;
      el->next = $1;
      $$ = el;
    }
;

write_arg:
    STRING_LITERAL {
      Expr *e;
      NEW(Expr, e);
      e->type = EXPR_LITERAL;
      e->literal.type = TYPE_STRING;
      e->literal.s_val = strdup($1);
      $$ = e;
      free($1);
    }
  | IDENTIFIER COLON INTEGER_LITERAL COLON INTEGER_LITERAL {
      Expr *e; NEW(Expr, e);
      e->type = EXPR_FORMATTED_WRITE;
      e->formatted.var_name = strdup($1);
      e->formatted.width = $3;
      e->formatted.precision = $5;
      $$ = e;
    }
  | IDENTIFIER {
      Expr *e;
      NEW(Expr, e);
      e->type = EXPR_VARIABLE;
      e->var_name = strdup($1);
      $$ = e;
      free($1);
    }
  | record_access {
      $$ = $1;
    }
;

read:
    READ L_PAREN IDENTIFIER R_PAREN {
      Stmt *s;
      NEW(Stmt, s);
      s->type = STMT_READ;
      s->read_stmt.var_name = strdup($3);
      s->read_stmt.new_line = false;
      $$ = s;
      free($3);
    }
  | READLN L_PAREN IDENTIFIER R_PAREN {
      Stmt *s;
      NEW(Stmt, s);
      s->type = STMT_READ;
      s->read_stmt.var_name = strdup($3);
      s->read_stmt.new_line = true;
      $$ = s;
      free($3);
  }
;

%%
