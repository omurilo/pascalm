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
%left MINUS PLUS
%left TIMES DIVIDE
%precedence NEG
%token DONE
%token <valueInt> VARIABLE
%token ATTRIB
%token IF
%token THEN
%token ELSE
%token L_PAREN
%token R_PAREN
%token L_CBRACE
%token R_CBRACE
%token GT
%token GTE
%token LT
%token LTE
%token DIFF
%token EQUALS
%token NOT
%token OR
%token AND

%type <condition> cond
%type <value> stmt expr factor

%define parse.error verbose

%%

progexec: stmt
        | stmt progexec

stmt: atrib DONE { printf("attrib\n"); }
    | expr DONE {printf("expr\n"); result = $1;}
    | if_stmt {}
    | DONE {return 0;}

if_stmt: IF L_PAREN cond R_PAREN THEN L_CBRACE stmt R_CBRACE { if ($3) { printf("cond: %d if: %lf\n", $3, $7); printf("if result: %lf\n", $7); }; return 0; }
    | IF L_PAREN cond R_PAREN THEN L_CBRACE stmt R_CBRACE ELSE L_CBRACE stmt R_CBRACE { printf("cond: %d if: %lf else: %lf\n", $3, $7, $11); if ($3) { printf("if result: %lf\n", $7); return 0; } else { printf("else result: %lf\n", $11); };}
 
atrib: VARIABLE ATTRIB expr { 
     symb[$1] = $3;
     /*result = $3;*/
     printf("variable: %c, %lf\n", $1+97, symb[$1]);
  }

cond: expr GT factor {$$ = $1 > $3; printf("expr gt %lf %lf %d\n", $1, $3, $1 > $3);}
    | expr GTE factor {$$ = $1 >= $3;}
    | expr LT factor {$$ = $1 < $3;}
    | expr LTE factor {$$ = $1 <= $3;}
    | expr EQUALS expr {$$ = $1 == $3;}
    | L_PAREN cond AND cond R_PAREN {$$ = $2 && $4;}
    | L_PAREN cond OR cond R_PAREN {$$ = $2 || $4;}
    | L_PAREN NOT cond R_PAREN {$$ = !$3;}

expr: expr PLUS factor {$$ = $1 + $3; printf("expr plus %lf %lf\n", $1, $3);}
    | expr MINUS factor {$$ = $1 - $3;}
    | expr TIMES factor {$$ = $1 * $3;}
    | expr DIVIDE factor {$$ = $1 / $3;}
    | L_PAREN expr R_PAREN {$$ = $2;}
    | factor {$$ = $1;}

factor: VAL {$$ = $1;}
      | MINUS VAL %prec NEG {$$ = -$2; printf("factor neg %lf\n", $2);}
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
