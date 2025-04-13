%{
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int yywrap();
int yylex();
void yyerror(const char* str);

double result = 0;
double symb[26];
%}

%union {
  double value;
  bool condition;
  int valueInt;
}

%token <value> VAL
%token <valueInt> VARIABLE
%token ATTRIB
%token IF
%token THEN
%token ELSE
%token L_PAREN
%token R_PAREN
%token L_CBRACE
%token R_CBRACE
%token GT GTE LT LTE DIFF EQUALS
%token SEMICOLON

%type <condition> cond
%type <value> stmt expr factor stmt_list

%left MINUS PLUS
%left TIMES DIVIDE
%precedence NEG

%left OR
%left AND
%left NOT

%define parse.error verbose

%%

progexec:
        stmt
        | stmt progexec

stmt_list:
         stmt {}
         | stmt_list stmt {}

stmt:
    atrib SEMICOLON {}
    | expr SEMICOLON {result = $1;}
    | if_stmt {}

if_stmt:
    IF L_PAREN cond R_PAREN THEN L_CBRACE stmt_list R_CBRACE { if ($3) { $<value>$ = $7; }}
    | IF L_PAREN cond R_PAREN THEN L_CBRACE stmt_list R_CBRACE ELSE L_CBRACE stmt_list R_CBRACE { if ($3) { $<value>$ = $7; } else { $<value>$ = $11; }}
 
atrib: VARIABLE ATTRIB expr { 
     symb[$1] = $3;
     $<value>$ = $3;
  }

cond:
    expr GT factor {$$ = $1 > $3;}
    | expr GTE factor {$$ = $1 >= $3;}
    | expr LT factor {$$ = $1 < $3;}
    | expr LTE factor {$$ = $1 <= $3;}
    | expr EQUALS expr {$$ = $1 == $3;}
    | L_PAREN cond AND cond R_PAREN {$$ = $2 && $4;}
    | L_PAREN cond OR cond R_PAREN {$$ = $2 || $4;}
    | L_PAREN NOT cond R_PAREN {$$ = !$3;}

expr: expr PLUS expr {$$ = $1 + $3;}
    | expr MINUS expr {$$ = $1 - $3;}
    | expr TIMES expr {$$ = $1 * $3;}
    | expr DIVIDE expr {$$ = $1 / $3;}
    | L_PAREN expr R_PAREN {$$ = $2;}
    | factor {$$ = $1;}

factor: VAL {$$ = $1;}
      | MINUS VAL %prec NEG {$$ = -$2;}
      | VARIABLE { $$ = symb[$1]; }
%%

int yywrap( ) {
  return 1;
}

void yyerror(const char* str) {
  fprintf(stderr, "Compiler error: '%s'.\n", str);
}

int main() {
  /*yydebug = 1;*/
  yyparse();
  printf("The answer is %lf\n", result);
  return 0;
}
