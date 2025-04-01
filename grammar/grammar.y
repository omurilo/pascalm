%{
#include <stdio.h>
#include <string.h>

int yywrap();
int yylex();
void yyerror(const char* str);

double result = 0;
int symb[26];
%}

%union {
  double value;
  int valueInt;
}

%token <value> VAL
%token PLUS
%token MINUS
%token DIVIDE
%token TIMES
%token LEFT
%token RIGHT
%token DONE
%token <valueInt> VARIABLE
%token EQUALS

%type <value> stmt expr term factor

%define parse.error verbose

%%

progexec: stmt
        | stmt progexec

stmt: atrib DONE {}
    | expr DONE {result = $1; return 0;}

atrib: VARIABLE EQUALS expr { symb[$1] = $3;}

expr: expr PLUS term {$$ = $1 + $3;}
    | expr MINUS term {$$ = $1 - $3;}
    | term {$$ = $1;}

term: term TIMES factor {$$ = $1 * $3;}
    | term DIVIDE factor {$$ = $1 / $3;}
    | factor {$$ = $1;}

factor: VAL {$$ = $1;}
      | LEFT expr RIGHT {$$ = $2;}
      | VARIABLE { $$ = symb[$1];}
%%

int yywrap( ) {
  return 1;
}

void yyerror(const char* str) {
  fprintf(stderr, "Compiler error: '%s'.\n", str);
}

int main() {
  yyparse();
  printf("The answer is %lf\n", result);
  return 0;
}
