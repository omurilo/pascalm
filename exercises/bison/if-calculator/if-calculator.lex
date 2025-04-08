DIGIT [0-9]

%{
#include <stdio.h>
#include <string.h>
#include "rpn.tab.h"
%}

%option noyywrap

%%
"+"             {return PLUS;}
"-"             {return MINUS;}
"/"             {return DIVIDE;}
"*"             {return TIMES;}
[a-z]           {yylval.valueInt=(int)(yytext[0])- 97; return VARIABLE; }
"="		{return EQUALS;}
{DIGIT}+(\.{DIGIT}*)? {yylval.value = atof(yytext); return VAL;}
[ \t]           {}
"\n"            {return DONE;}
.               {printf("Error: invlaid lexeme '%s'.\n", yytext); return 0;}

%%
