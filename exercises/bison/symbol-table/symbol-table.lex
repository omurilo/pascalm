DIGIT [0-9]
ID [a-zA-Z][0-9a-zA-Z\_]*
NUMBER {DIGIT}+(\.{DIGIT}*)?

%{
#include <stdio.h>
#include <string.h>
#include "symbol-table.tab.h"

enum {
  TYPE_INT,
  TYPE_FLOAT,
  TYPE_BOOL,
  TYPE_CHAR
};
%}

%option noyywrap

%x STR
%x W
%x R

%%

"+"             {return PLUS;}
"-"             {return MINUS;}
"/"             {return DIVIDE;}
"*"             {return TIMES;}
"if"            {return IF;}
"then"          {return THEN;}
"else"          {return ELSE;}
"("             {return L_PAREN;}
")"             {return R_PAREN;}
"{"             {return L_CBRACE;}
"}"             {return R_CBRACE;}
">="            {return GTE;}
"<="            {return LTE;}
">"             {return GT;}
"<"             {return LT;}
"="             {return EQUALS;}
"<>"            {return DIFF;}
"NOT"           {return NOT;}
"OR"            {return OR;}
"AND"           {return AND;}
":="            {return ATTRIB;}
";"             {return SEMICOLON;}
"boolean"       {yylval.type = TYPE_BOOL; return TYPE;}
"int"           {yylval.type = TYPE_INT; return TYPE;}
"float"         {yylval.type = TYPE_FLOAT; return TYPE;}
"char"          {yylval.type = TYPE_CHAR; return TYPE;}

"'"[a-zA-Z]"'"  {yylval.value.type = TYPE_CHAR; yylval.value.c = yytext[1]; return VAL;}
{NUMBER}        {yylval.value.type = TYPE_FLOAT; yylval.value.f = atof(yytext); return VAL;}
[0-9]+          {yylval.value.type = TYPE_INT; yylval.value.i = atoi(yytext); return VAL;}

{ID} { 
  if (yyleng > 10) {
    fprintf(stderr, "\033[1;31mThe variable '%s' has more than 10 characters, lexing error.\033[0m\n", yytext);
    exit(1);
  }
  yylval.identifier = strdup(yytext);
  return VARIABLE;
}


"write"\(\" BEGIN(W);
<W>[^\"\n]*
<W>\"\) {
  BEGIN(INITIAL);
  yylval.val = yytext;
  return WRITE;
}

"write"\(\' BEGIN(W);
<W>[^ \'\n]*
<W>\'\) {
  BEGIN(INITIAL);
  yylval.val = yytext;
  return WRITE;
}

"write"\({ID}\) {
  yylval.identifier = yytext;
  return WRITE;
}

"write"\({NUMBER}\) {
  yylval.val = yytext;
  return WRITE;
}

"read"\({ID}\)    {yylval.identifier = yytext; return READ;}
[ \t\n(\r\n)]   {}
.               {printf("Error: invlaid lexeme '%s'.\n", yytext); return 0;}

%%
