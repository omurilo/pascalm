DIGIT [0-9]
ALPHA [a-zA-Z\_]
ALPHANUM ({ALPHA}|{DIGIT})
ID {ALPHA}{ALPHANUM}*
UINT {DIGIT}+
EXPONENT e[+-]?{UINT}
NUMBER ({UINT}(\.{UINT})?|{UINT}?\.{UINT}){EXPONENT}?
CHAR \'[a-zA-Z]\'

%{
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "ast-stmts.tab.h"

#define YY_USER_ACTION \
    yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = YYCOLUMN; \
    yylloc.last_column = YYCOLUMN + yyleng - 1;

int YYCOLUMN = 1;

void yyerror(char *message);

%}

%option noyywrap

%x STR
%x W
%x R
%x W_S

%%

"+"             {YY_USER_ACTION; return PLUS;}
"-"             {YY_USER_ACTION; return MINUS;}
"/"             {YY_USER_ACTION; return DIVIDE;}
"*"             {YY_USER_ACTION; return TIMES;}
"if"            {YY_USER_ACTION; return IF;}
"then"          {YY_USER_ACTION; return THEN;}
"else"          {YY_USER_ACTION; return ELSE;}
"("             {YY_USER_ACTION; return L_PAREN;}
")"             {YY_USER_ACTION; return R_PAREN;}
"{"             {YY_USER_ACTION; return L_CBRACE;}
"}"             {YY_USER_ACTION; return R_CBRACE;}
">="|"=>"       {YY_USER_ACTION; return GTE;}
"<="|"=<"       {YY_USER_ACTION; return LTE;}
">"             {YY_USER_ACTION; return GT;}
"<"             {YY_USER_ACTION; return LT;}
"="             {YY_USER_ACTION; return EQUALS;}
"<>"            {YY_USER_ACTION; return DIFF;}
"NOT"           {YY_USER_ACTION; return NOT;}
"OR"            {YY_USER_ACTION; return OR;}
"AND"           {YY_USER_ACTION; return AND;}
":="            {YY_USER_ACTION; return ATTRIB;}
";"             {YY_USER_ACTION; return SEMICOLON;}
"^"             {YY_USER_ACTION; return EXPONENT;}
"boolean"       {YY_USER_ACTION; yylval.type = TYPE_BOOL; return TYPE;}
"int"           {YY_USER_ACTION; yylval.type = TYPE_INT; return TYPE;}
"float"         {YY_USER_ACTION; yylval.type = TYPE_FLOAT; return TYPE;}
"char"          {YY_USER_ACTION; yylval.type = TYPE_CHAR; return TYPE;}

{CHAR}          {YY_USER_ACTION; yylval.value.type = TYPE_CHAR; yylval.value.data.c = yytext[1]; return VAL;}
[0-9]+          {YY_USER_ACTION; yylval.value.type = TYPE_INT; yylval.value.data.i = atoi(yytext); return VAL;}
{NUMBER}        {YY_USER_ACTION; yylval.value.type = TYPE_FLOAT; yylval.value.data.f = atof(yytext); return VAL;}
"false"|"true"  {YY_USER_ACTION; yylval.value.type = TYPE_BOOL; yylval.value.data.b = strcmp(yytext, "true"); return VAL;}

"while" { YY_USER_ACTION; return WHILE; }
"do" { YY_USER_ACTION; return WHILE_DO; }
"begin" { YY_USER_ACTION; return WHILE_BEGIN; }
"end" { YY_USER_ACTION; return WHILE_END; }

{ID} { 
  YY_USER_ACTION; 
  if (yyleng > 10) {
    fprintf(stderr, "\033[1;31mThe variable '%s' has more than 10 characters, lexing error.\033[0m\n", yytext);
    exit(1);
  }
  yylval.identifier = strdup(yytext);
  return VARIABLE;
}

"write"\( { YY_USER_ACTION; BEGIN(W); }
<W>{ID} {
  YY_USER_ACTION; 
  yylval.identifier = yytext;
  yyinput();
  BEGIN(INITIAL);
  return WRITE_ID;
}
<W>{NUMBER} {
  YY_USER_ACTION; 
  yylval.value.type = TYPE_FLOAT;
  yylval.value.data.f = atof(yytext);
}
<W>{CHAR} { YY_USER_ACTION; yylval.value.type = TYPE_CHAR; yylval.value.data.c = yytext[1]; }
<W>[\'\"]?\) {
  YY_USER_ACTION; 
  BEGIN(INITIAL);
  return WRITE;
}
<W>\"  { YY_USER_ACTION; BEGIN(W_S); }
<W_S>[^\"\n]* {
  YY_USER_ACTION; 
  yylval.value.type = TYPE_STRING;
  yylval.value.data.s = strdup(yytext);
  BEGIN(W);
}

"read"\(\"  { YY_USER_ACTION; BEGIN(R); }
<R>{ID}   { YY_USER_ACTION; yylval.identifier = strdup(yytext); }
<R>\"\)     { YY_USER_ACTION; BEGIN(INITIAL); return READ; }


[ \t]
[\n(\r\n)]      { YY_USER_ACTION; YYCOLUMN = 1; yylineno++; }
.               { YY_USER_ACTION; YYCOLUMN += yyleng; yyerror((char*)"Illegal input"); }

%%

void yyerror(char *message) {
   fprintf(stderr, "Error: \"%s\" in line %d. Token = %s\n",
           message, yylineno, yytext);
   exit(1);
}
