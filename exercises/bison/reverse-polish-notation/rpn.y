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
%token DONE
%token <valueInt> VARIABLE
%token EQUALS

%type <value> stmt expr factor

%define parse.error verbose

%%

progexec: stmt
        | stmt progexec

stmt: atrib DONE {}
    | expr DONE {result = $1; return 0;}

atrib: VARIABLE EQUALS expr { symb[$1] = $3; result = $3; printf("%lf\n", result); }

expr: expr factor PLUS {$$ = $1 + $2;}
    | expr factor MINUS {$$ = $1 - $2;}
    | expr factor TIMES {$$ = $1 * $2;}
    | expr factor DIVIDE {$$ = $1 / $2;}
    | factor {$$ = $1;}

factor: VAL {$$ = $1;}
      | VARIABLE { $$ = symb[$1]; }
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
