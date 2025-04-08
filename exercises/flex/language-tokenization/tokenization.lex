DELIM ,|;|:|\.
OP_REL <|>|=|(>=)|(<=)|(=>)|(=<)|(<>)
OP_ARI \+|\-|\*|\/|"SQR"|"SQRT"|"SIN"|"COS"|"TAN"
RES "Begin"|"End"|"For"|"Do"|"If"|"Then"|"Else"|"Elseif"|"Endif"|"While"|"Repeat"|"Until"
TYPE "Integer"|"Real"|"Float"|"Double"|"Char"|"String"|"Boolean"
BOOLEAN "True"|"False"
DIG [0-9]
NUMBER (-?{DIG}+([eE]-?{DIG}+)?)|(-?{DIG}*\.{DIG}+([eE]-?{DIG}+)?)
STRING [a-zA-Z0-9]
FUN ^[\_]{STRING}+
VAR ^[\$]{STRING}+
TEXT \"({STRING}[ \t]*)+\"
CHAR \'{STRING}+\'
NAME {STRING}+
COMMENT #.*#

%{
  #include <stdio.h>
  #include <string.h>

  FILE *out ;

  int column = 1;
  int expecting_semicolon = 0;
%}

%option yylineno
%option noyywrap

%x TYPED
%x LEXING_ERROR

%%
{NUMBER} { 
    printf("Number: %s\n", yytext); 
    column += yyleng;
}
{RES} { 
    printf("Reserved functions %s\n", yytext); 
    column += yyleng;
}
{TYPE} { 
    printf("Type: %s at column %d\n", yytext, column); 
    column += yyleng;
    BEGIN(TYPED); 
    expecting_semicolon = 1;
}
<TYPED>{NUMBER} { 
    printf("Typed Number: %s at column %d\n", yytext, column); 
    column += yyleng; 
}
<TYPED>{BOOLEAN} { 
    printf("Typed Boolean: %s at column %d\n", yytext, column); 
    column += yyleng; 
}
<TYPED>{TEXT} { 
    printf("Typed Text: %s at column %d\n", yytext, column); 
    column += yyleng; 
}
<TYPED>{CHAR} { 
    if (yytext[1] >= '0' && yytext[1] <= '9') {  // Se for um número
        int num = atoi(&yytext[1]);  // Converte a string numérica em um inteiro
        printf("Typed Char: '%c' (%d) at column %d\n", (char)atoi(&yytext[1]), num, column); 
    } else {  // Caso contrário, é um caractere simples
        printf("Typed Char: '%c' (%d) at column %d\n", yytext[1], yytext[1], column);
    }
    column += yyleng; 
}
<TYPED>{NAME} { 
    printf("Typed Name: %s at column %d\n", yytext, column); 
    column += yyleng; 
}
<TYPED>{FUN} { 
    printf("Typed Function: %s at column %d\n", yytext, column); 
    column += yyleng; 
}
<TYPED>{VAR} { 
    printf("Typed Variable: %s at column %d\n", yytext, column); 
    column += yyleng; 
}
<TYPED>[=] { 
    printf("Typed Equal: %s at column %d\n", yytext, column); 
    column += yyleng;
}
<TYPED>[;] { 
    printf("Typed final expression: %s\n\n", yytext); 
    column += yyleng;
    expecting_semicolon = 0;  // Não esperamos mais ponto e vírgula
    BEGIN(INITIAL); 
}
<TYPED>[ \t] { column += yyleng; }
<TYPED>\n {
  if (expecting_semicolon) {
    printf("\033[31mErro: Falta o ponto e vírgula ';' após a expressão.\033[0m\n");
    printf("\033[33mPosição: Linha %d, Coluna %d\033[0m\n", yylineno-1, column);
    BEGIN(INITIAL); 
  }
  column = 1;
}
{BOOLEAN} { 
    printf("Boolean: %s\n", yytext); 
    column += yyleng;
}
{FUN} { 
    printf("Func: %s\n", yytext); 
    column += yyleng;
}
{VAR} { 
    printf("Variable: %s\n", yytext); 
    column += yyleng;
}
{TEXT} { 
    printf("Text: %s\n", yytext); 
    column += yyleng;
}
{OP_ARI} { 
    printf("Op Aritimético: %s\n", yytext); 
    column += yyleng;
}
{OP_REL} { 
    printf("Op Relacional: %s\n", yytext); 
    column += yyleng;
}
{NAME} { 
    printf("Name: %s\n", yytext); 
    column += yyleng;
}
{COMMENT} { 
    printf("Comment: %s\n", yytext); 
    column += yyleng;
}
{DELIM} { 
    printf("Delimitador: %s\n", yytext); 
    column += yyleng;
}
[ \t] { 
    column += yyleng; 
}
\n { 
    column = 1;
}
[ \t\n(\r\n)]+
. { 
  BEGIN(LEXING_ERROR);
  yyless(1);
}
<LEXING_ERROR>.+  { 
  column = yyleng;
  printf("\033[31mErro: Caractere inválido '%s' encontrado.\033[0m\n", yytext-1);
  printf("\033[33mPosição: Linha %d, Coluna %d\033[0m\n", yylineno, column-1);
  exit(1);
}
%%

int main(int argc, char **argv) {
  yyin = fopen(argv[1], "r");
  yylex();
  fclose(yyin);
  return 0;
}
