%option noyywrap nounput noinput batch yylineno
%{
#include <stdio.h>
#include <string.h>
#include "final_work.tab.h"
#include "final_work_types.h"

#define SAVE_INTEGER yylval.integer = atoi(yytext)
#define SAVE_NUMBER yylval.number = atof(yytext)
#define SAVE_CHAR yylval.character = yytext[1]
#define SAVE_STRING yylval.string = strdup(yytext)
#define SAVE_BOOLEAN yylval.boolean = strcmp(yytext, "true") ? 1 : 0
#define TOKEN(t) (yylval.token = t)

int yycolumn = 1;

#define YYERROR_VERBOSE 1

#define YY_USER_ACTION do { \
    if (yylloc.last_line < yylineno) \
        yycolumn = 1; \
    yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; \
    yylloc.last_column = yycolumn + (int)yyleng - 1; \
    yycolumn += (int)yyleng; \
} while(0);

int comment_nesting = 0;
%}

DIGIT [0-9]
ALPHA [a-zA-Z\_]
ALPHANUM ({ALPHA}|{DIGIT})
ID {ALPHA}{ALPHANUM}*
UINT {DIGIT}+
REAL {UINT}(\.{UINT})?([eE][+-]{UINT})?
CHAR \'[a-zA-Z]\'
STRING \'([^\\\n]|(\\.))*?\'

%x COMMENT

%%
\{[^}]*\}       {}
"(*"            { BEGIN(COMMENT); comment_nesting = 1; }
<COMMENT>"(*"   { comment_nesting++; }
<COMMENT>"*)"   {
                  if (--comment_nesting == 0) BEGIN(INITIAL);
                }
<COMMENT>[^\n]+ {}
<COMMENT>\n     { yycolumn = 1; }
[ \t]+
[\r\n]+         { yycolumn = 1; }

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
"..."           {return DOTDOTDOT;}
".."            {return DOTDOT;}
"."             {return DOT;}
"^"             {return CARET;}

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
"nil"           { return NIL; }

{CHAR}          {SAVE_CHAR; return CHAR_LITERAL;}
{UINT}          {SAVE_INTEGER; return INTEGER_LITERAL;}
{REAL}          {SAVE_NUMBER; return REAL_LITERAL;}
{ID}            {SAVE_STRING; return IDENTIFIER;}
{STRING}        {SAVE_STRING; return STRING_LITERAL;}

.               { yyerror((const char*)"Illegal input in"); }
%%

int yywrap(void) {
  return 1;
}
