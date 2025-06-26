#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdio.h>

typedef struct YYLTYPE {
  int first_line;
  int first_column;
  int last_line;
  int last_column;
  char *file_name;
} YYLTYPE;

#undef yywrap
int yywrap(void);
extern int yyparse();
extern int yylex();
extern FILE *yyin;
extern YYLTYPE yylloc;

extern void yyerror(const char *msg);

char *process_string_literal(char *text);

#endif
