%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "types.h"
#include "tac.h"
#include "symbol-table.h"

int yywrap();
int yylex();
extern FILE *yyin;
int yyparse();
void yyerror(const char *str);

%}

%union {
  int ival;
  double fval;
  char cval;
  char* sval;
  bool bval;

  TypeInfo type;
  Field *field_list;
  Param *param_list;

  char** strlist;

  Constant constant;

  Expr* expr;
  Stmt* stmt;
  StmtList* stmt_list;
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

%token <cval> CHAR_LITERAL
%token <ival> INTEGER_LITERAL
%token <sval> STRING_LITERAL
%token <fval> REAL_LITERAL
%token <bval> BOOLEAN_LITERAL
%token <sval> IDENTIFIER

// %type <stmt_list> stmt_list
// %type <stmt> stmt if_stmt write read while atrib
// %type <expr> logical_expr arithmetic_expr expr_value factor_literal factor_var

%type <type> type
%type <field_list> field_decl field_list
%type <param_list> param_list param_seq
// %type <identifier> variable_declaration variable_list
%type <strlist> variable_list
%type <type> primary // refatorar para ser do tipo expr e não typeinfo
%type <constant> constant

%left PLUS MINUS
%left TIMES DIVIDE DIV MOD SQRT
%left AND OR
%precedence NEG
%nonassoc GT GTE LT LTE NEQ EQ IN
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%define parse.error verbose
%locations

%start program

%%

program: 
      PROGRAM IDENTIFIER heading SEMICOLON block DOT { /* tac_print(generate_stmt_list_tac($2));*/ }
;

heading:
  /* empty */
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
      /* empty */ 
    | declarations label_declaration
    | declarations constant_declaration
    | declarations type_declaration 
    | declarations variable_declaration
    | declarations procedure_declaration SEMICOLON
    | declarations function_declaration SEMICOLON
;

label_declaration:
    LABEL unsigned_integer_list SEMICOLON
;

unsigned_integer_list: 
    INTEGER_LITERAL
  | unsigned_integer_list COMMA INTEGER_LITERAL
;

constant_declaration:
  CONST const_assignment_list SEMICOLON 
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
      c.kind = TYPE_INT;
      c.ival = $1;
      $$ = c;
    }
  | REAL_LITERAL {
      Constant c;
      c.kind = TYPE_REAL;
      c.fval = $1;
      $$ = c;
  }
  | STRING_LITERAL {
      Constant c;
      c.kind = TYPE_STRING;
      c.sval = $1;
      $$ = c;
  }
  | IDENTIFIER {
      Constant c;
      c.kind = TYPE_STRING;
      c.id = strdup($1);
      $$ = c;
    }
  | PLUS IDENTIFIER {
      Constant c;
      c.kind = TYPE_STRING;
      c.op = '+';
      c.id = strdup($2);
      $$ = c;
    }
  | MINUS IDENTIFIER {
      Constant c;
      c.kind = TYPE_STRING;
      c.op = '-';
      c.id = strdup($2);
      $$ = c;
    }
;

type_declaration:
    TYPE type_assignment_list SEMICOLON
;

type_assignment_list:
    IDENTIFIER EQ type
  | type_assignment_list SEMICOLON IDENTIFIER EQ type
;

variable_declaration:
    VAR variable_declaration_list SEMICOLON
;

variable_declaration_list:
    variable_list_type
  | variable_declaration_list SEMICOLON variable_list_type
;

variable_list_type: 
    variable_list COLON type {
      TypeInfo t = $3;
      for (int i = 0; $1[i] != NULL; i++) {
        if (add_symbol($1[i], t) == -1) {
          fprintf(stderr, "Error to declare variable %s\n", $1[i]);
        }
        free($1[i]);
      }
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
      TypeInfo tmp;
      tmp.type = TYPE_INT;
      $$ = tmp;
    }
  | STRING {
    TypeInfo tmp;
    tmp.type = TYPE_STRING;
    $$ = tmp;
  }
  | REAL {
    TypeInfo tmp;
    tmp.type = TYPE_REAL;
    $$ = tmp;
  }
  | CHAR {
    TypeInfo tmp;
    tmp.type = TYPE_CHAR;
    $$ = tmp;
  }
  | BOOLEAN {
    TypeInfo tmp;
    tmp.type = TYPE_BOOL;
    $$ = tmp;
  }
  | ARRAY L_BRACKET constant DOTDOT constant R_BRACKET OF type {
      TypeInfo tmp;
      tmp.type = TYPE_ARRAY;
      tmp.arrayInfo.type=$8.type;
      tmp.arrayInfo.low=$3.ival;
      if ($5.kind == TYPE_STRING) {
        // Symbol* s = get_symbol_by_name($5.id);
        // tmp.arrayInfo.high=s->data.i;
      }
      $$ = tmp;
  }
  | RECORD field_list END {
      TypeInfo tmp;
      tmp.type = TYPE_RECORD;
      tmp.recordFields = $2;
      $$ = tmp;
  }
  | IDENTIFIER {
    TypeInfo tmp;
    tmp.type = TYPE_STRING;
  
    // Symbol* s = get_symbol_by_name($1);
    // if (s->skind == KIND_TYPE) {
    //   //TODO: rescue custom type
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
      f->type = &$3;
      f->next = NULL;
      $$=f;
    }
;

procedure_declaration:
    PROCEDURE IDENTIFIER L_PAREN param_list R_PAREN SEMICOLON block
;

function_declaration:
    FUNCTION IDENTIFIER L_PAREN param_list R_PAREN COLON type SEMICOLON block
;

param_list:
  { $$ = NULL; }
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
  | procedure_stmt
  | goto_stmt
  | /* empty */
;

assign:
    IDENTIFIER ASSIGN expression
  | IDENTIFIER DOT IDENTIFIER ASSIGN expression
  | IDENTIFIER L_BRACKET expression R_BRACKET ASSIGN expression
  | IDENTIFIER L_BRACKET expression R_BRACKET DOT IDENTIFIER ASSIGN expression
;

procedure_stmt:
    IDENTIFIER L_PAREN expression_list R_PAREN
  | read
  | write
;

compound_stmt:
  BEGIN_TOK statement_list END
;

if_stmt:
    IF expression THEN statement %prec LOWER_THAN_ELSE
  | IF expression THEN statement ELSE statement
;

case_stmt:
  CASE expression OF case_list END
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
  REPEAT statement_list UNTIL expression
;

goto_stmt:
  GOTO INTEGER_LITERAL
;

while_stmt:
  WHILE expression DO statement
;

for_stmt:
    FOR IDENTIFIER ASSIGN expression TO expression DO statement
  | FOR IDENTIFIER ASSIGN expression DOWNTO expression DO statement
;

expression_list:
    expression
  | expression_list COMMA expression
;

expression:
    simple_expr
  | simple_expr relational_op simple_expr
;

primary:
    IDENTIFIER {
      TypeInfo tmp;
      tmp.type = TYPE_STRING;
      tmp.data.s = $1;
      $$ = tmp;
      // TODO: criado o tipo para var
    }
  | INTEGER_LITERAL {
      TypeInfo tmp;
      tmp.type = TYPE_INT;
      tmp.data.i = $1;
      $$ = tmp;
    }
  | REAL_LITERAL {
      TypeInfo tmp;
      tmp.type = TYPE_REAL;
      tmp.data.f = $1;
      $$ = tmp;
    }
  | CHAR_LITERAL {
      TypeInfo tmp;
      tmp.type = TYPE_CHAR;
      tmp.data.c = $1;
      $$ = tmp;
    }
  | STRING_LITERAL {
      TypeInfo tmp;
      tmp.type = TYPE_STRING;
      tmp.data.s = $1;
      $$ = tmp;
    }
  | BOOLEAN_LITERAL {
      TypeInfo tmp;
      tmp.type = TYPE_BOOL;
      tmp.data.b = $1;
      $$ = tmp;
    }
  | L_PAREN expression R_PAREN {
    $$ = $<type>2;
  } 

postfix:
    primary
  | postfix DOT IDENTIFIER
  | postfix L_BRACKET expression R_BRACKET
  | IDENTIFIER L_PAREN expression_list R_PAREN

simple_expr:
    term
  | simple_expr add_op term
;

term:
    factor
  | term mul_op factor
;

factor:
    postfix
  | NOT factor
  | PLUS factor
  | MINUS factor %prec NEG
;

relational_op:
    EQ
  | NEQ
  | GT
  | GTE
  | LT
  | LTE
;

add_op:
    PLUS
  | MINUS
  | OR
;

mul_op:
    TIMES
  | DIVIDE
  | AND
;

write:
    WRITE L_PAREN write_args R_PAREN
  | WRITELN L_PAREN write_args R_PAREN {
    printf("\n");
  }
  | WRITELN {
    printf("\n");
  }
;

write_args:
    write_arg
  | write_args COMMA write_arg
;

write_arg:
    STRING_LITERAL { printf("%s", $1); }
    | IDENTIFIER COLON INTEGER_LITERAL COLON INTEGER_LITERAL {
        printf(" [FORMAT: %s:%d:%d] ", $1, $3, $5);
    }
    | IDENTIFIER {
        Symbol* s = get_symbol_by_name($1);
        if (s->type == TYPE_INT) {
          printf(" [INTEGER: %d] ", s->data.i);
        } else if (s->type == TYPE_REAL) {
          printf(" [REAL: %.2f] ", s->data.f);
        } else if (s->type == TYPE_CHAR) {
          printf(" [CHAR: %c] ", s->data.c);
        } else if (s->type == TYPE_BOOL) {
          printf(" [BOOL: %s] ", s->data.b ? "true" : "false");
        } else {
          printf(" [VARIAVEL: %s] ", $1);
        }
    }
    | IDENTIFIER DOT IDENTIFIER
;

read:
    READ L_PAREN IDENTIFIER R_PAREN {
    }
;

literal:
    const_numbers
  | STRING_LITERAL
  | BOOLEAN_LITERAL
  | CHAR_LITERAL
;

const_numbers: 
      INTEGER_LITERAL
    | REAL_LITERAL
;

%%

int yywrap( ) {
  return 1;
}

int main(int argc, char** argv) {
  if (argc > 1) {
      yyin = fopen(argv[1], "r");
      if (!yyin) {
        perror("Error open file");
        return 1;
      }
    } else {
      yyin = stdin;
    }

    yyparse();

    if (yyin != stdin) {
        fclose(yyin);
    }

    return 0;
}
