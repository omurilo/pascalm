%{
#include <stdio.h>
#include <string.h>
#include "grammar.tab.h"
%}

%option noyywrap

%%
"+"             {return PLUS;}
"-"             {return MINUS;}
"/"             {return DIVIDE;}
"*"             {return TIMES;}
"("             {return LEFT;}
")"             {return RIGHT;}
[a-z]           {yylval.valueInt=(int)(yytext[0])- 97; return VARIABLE; }
"="		{return EQUALS;}
[0-9]+          {yylval.value = atof(yytext); return VAL;}
[0-9]+"."[0-9]+ {yylval.value = atof(yytext); return VAL;}
[ \t]           {}
"\n"            {return DONE;}
.               {printf("Error: invlaid lexeme '%s'.\n", yytext); return 0;}

%%
