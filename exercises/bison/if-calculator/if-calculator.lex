DIGIT [0-9]

%{
#include <stdio.h>
#include <string.h>
#include "if-calculator.tab.h"
%}

%option noyywrap

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
":="		        {return ATTRIB;}
";"             {return SEMICOLON;}
[a-z]           {yylval.valueInt=(int)(yytext[0])- 97; return VARIABLE; }
{DIGIT}+(\.{DIGIT}*)? {yylval.value = atof(yytext); return VAL;}
[ \t\n(\r\n)]   {}
.               {printf("Error: invlaid lexeme '%s'.\n", yytext); return 0;}

%%
