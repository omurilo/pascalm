DIGIT [0-9]
ALPHA [a-zA-Z\_]
ALPHANUM ({ALPHA}|{DIGIT})
ID {ALPHA}{ALPHANUM}*
UINT {DIGIT}+
REAL {UINT}(\.{UINT})?([eE][+-]{UINT})?
CHAR \'[a-zA-Z]\'
STRING \'([^\\\n]|(\\.))*?\'
COMMENTS \(\*([^*]|\*+[^*)])*\*+\)|\{[^}]*\}

%{
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "final_work.tab.h"

%}

%option noyywrap

%%
"+"             {return PLUS;}
"-"             {return MINUS;}
"/"             {return DIVIDE;}
"*"             {return TIMES;}
"("             {return L_PAREN;}
")"             {return R_PAREN;}
"{"             {return L_BRACE;}
"}"             {return R_BRACE;}
"["             {return L_BRACKET;}
"]"             {return R_BRACKET;}
">="            {return GTE;}
"<="            {return LTE;}
">"             {return GT;}
"<"             {return LT;}
"="             {return EQ;}
"<>"            {return NEQ;}
":="            {return ASSIGN;}
","             {return COMMA;}
":"             {return COLON;}
";"             {return SEMICOLON;}
".."            {return DOTDOT;}
"."             {return DOT;}

"program"       { return PROGRAM; }
"var"           { return VAR; }
"const"         { return CONST; }
"type"          { return TYPE; }
"label"         { return LABEL; }
"procedure"     { return PROCEDURE; }
"function"      { return FUNCTION; }
"begin"         { return BEGIN_TOK; }
"end"           { return END; }
"if"            { return IF; }
"then"          { return THEN; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"do"            { return DO; }
"for"           { return FOR; }
"to"            { return TO; }
"downto"        { return DOWNTO; }
"repeat"        { return REPEAT; }
"until"         { return UNTIL; }
"case"          { return CASE; }
"of"            { return OF; }
"goto"          { return GOTO; }
"array"         { return ARRAY; }
"record"        { return RECORD; }
"set"           { return SET; }
"file"          { return FILE_TOK; }
"integer"       { return INTEGER; }
"real"          { return REAL; }
"boolean"       { return BOOLEAN; }
"string"        { return STRING; }
"char"          { return CHAR; }
"not"           { return NOT; }
"and"           { return AND; }
"or"            { return OR; }
"div"           { return DIV; }
"mod"           { return MOD; }
"write"         { return WRITE; }
"writeln"       { return WRITELN; }
"read"          { return READ; }
"readln"        { return READLN; }

"false"|"true"  {yylval.bval = strcmp(yytext, "true"); return BOOLEAN_LITERAL;}
{CHAR}          {yylval.cval = yytext[1]; return CHAR_LITERAL;}
{UINT}          {yylval.ival = atoi(yytext); return INTEGER_LITERAL;}
{REAL}          {yylval.fval = atof(yytext); return REAL_LITERAL;}
{ID}            {yylval.sval = strdup(yytext); return IDENTIFIER;}
{STRING}        {yylval.sval = strdup(yytext); return STRING_LITERAL;}

[ \t]
[\n(\r\n)]      { yylineno++; }
{COMMENTS}      {}
.               { yyerror((const char*)"Illegal input in"); }
%%

void yyerror(const char *message) {
   fprintf(stderr, "Error: \"%s\" in line %d. Token = %s\n",
           message, yylineno, yytext);
   exit(1);
}
