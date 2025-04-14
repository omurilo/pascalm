%{
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_BOOL,
    TYPE_CHAR
} VarType;

typedef struct {
    char name[11];
    VarType type;
    union {
      int i;
      double f;
      char c;
      int b;
    };
} Symbol;

int yywrap();
int yylex();
void yyerror(const char* str);
int add_symbol(const char* id, VarType type);
int get_symbol_index(const char* id);

static Symbol symb_table[100];
static int symb_count = 0;
%}

%union {
  bool condition;
  char* identifier;
  char* val;
  int type;

  struct {
    int type;
    union {
      int i;
      bool b;
      char c;
      double f;
    };
  } value;
}


%token ATTRIB
%token IF
%token THEN
%token ELSE
%token L_PAREN
%token R_PAREN
%token L_CBRACE
%token R_CBRACE
%token GT GTE LT LTE DIFF EQUALS
%token SEMICOLON

%token <value> VAL
%token <identifier> VARIABLE
%token <type> TYPE

%token <val> WRITE
%token <identifier> READ


%type <condition> logical_expr
%type <value> stmt arithmetic_expr factor stmt_list expr_value
%type <type> declaration

%left MINUS PLUS
%left TIMES DIVIDE
%precedence NEG

%left OR
%left AND
%left NOT

%define parse.error verbose

%%

progexec:
        declarations stmt
        | declarations stmt progexec

declarations:
            | declarations declaration

declaration:
  TYPE VARIABLE SEMICOLON {
    if (add_symbol($2, (VarType)$1) == -1) {
      yerror("Error on variable declaration");
    }
    free($2);
  }

stmt_list:
         stmt
         | stmt_list stmt 

stmt:
    atrib SEMICOLON {}
    | arithmetic_expr SEMICOLON {}
    | if_stmt {}

if_stmt:
    IF L_PAREN logical_expr R_PAREN THEN L_CBRACE stmt_list R_CBRACE { 
      if ($3) {
        $<value>$ = $7;
              }
    }
    | IF L_PAREN logical_expr R_PAREN THEN L_CBRACE stmt_list R_CBRACE ELSE L_CBRACE stmt_list R_CBRACE {
      if ($3) { 
        $<value>$ = $7;
              } else {
        $<value>$ = $11;
              }
    }

atrib: VARIABLE ATTRIB expr_value {
     int si = get_symbol_index($1);
     if (si != -1) {
      Symbol symb = symb_table[si];
      val_type = $3.type;

      switch (symb.type) {
        case TYPE_INT:
          if (val_type == TYPE_INT) {
            symb_table[si].i = $3.i;
          } else {
            yyerror("Semantic Error: Variable '%s' type mismatch", $1);
          }
          break;
        case TYPE_BOOL:
          if (val_type == TYPE_BOOL) {
            symb_table[si].b = $3.b;
          } else {
            yyerror("Semantic Error: Variable '%s' type mismatch", $1);
          }
          break;
        case TYPE_CHAR:
          if (val_type == TYPE_CHAR) {
            symb_table[si].c = $3.c;
          } else {
            yyerror("Semantic Error: Variable '%s' type mismatch", $1);
          }
          break;
        case TYPE_FLOAT:
          if (val_type == TYPE_FLOAT) {
            symb_table[si].f = $3.f;
          } else {
            yyerror("Semantic Error: Variable '%s' type mismatch", $1);
          }
          break;
      }
     } else {
      fprintf(stderr, "Undefined declaration of identifier '%s'", $1);
      exit(1);
     }
  }

expr_value:
          arithmetic_expr { $$ = $1; }
          | logical_expr { $$ = $1; }
 
logical_expr:
    arithmetic_expr GT arithmetic_expr {
      $$.type = TYPE_BOOL;
      $$.b = $1.i > $3.i;
    }
    | arithmetic_expr GTE arithmetic_expr {
        $$.type = TYPE_BOOL;
        $$.b = $1.i >= $3.i;
      }
    | arithmetic_expr LT arithmetic_expr {
        $$.type = TYPE_BOOL;
        $$.b = $1.i < $3.i;
      }
    | arithmetic_expr LTE arithmetic_expr {
        $$.type = TYPE_BOOL;
        $$.b = $1.i <= $3.i;
      }
    | arithmetic_expr EQUALS arithmetic_expr {
        $$.type = TYPE_BOOL;
        $$.b = ($1.type == TYPE_FLOAT || $3.type == TYPE_FLOAT)
               ? (double)$1.i == (double)$3.i
               : $1.i == $3.i;
      }
    | L_PAREN logical_expr AND logical_expr R_PAREN {
        $$.type = TYPE_BOOL;
        $$.b = $2.b && $4.b;
      }
    | L_PAREN logical_expr OR logical_expr R_PAREN {
        $$.type = TYPE_BOOL;
        $$.b = $2.b || $4.b;
      }
    | L_PAREN NOT logical_expr R_PAREN {
      $$.type = TYPE_BOOL;
      $$.b = !$3.b;
    }

arithmetic_expr: 
    arithmetic_expr PLUS arithmetic_expr {$$ = $1 + $3;}
    | arithmetic_expr MINUS arithmetic_expr {$$ = $1 - $3;}
    | arithmetic_expr TIMES arithmetic_expr {$$ = $1 * $3;}
    | arithmetic_expr DIVIDE arithmetic_expr {$$ = $1 / $3;}
    | L_PAREN arithmetic_expr R_PAREN {$$ = $2;}
    | factor {$$ = $1;}

factor: 
      VAL {$$ = $1;}
      | MINUS VAL %prec NEG {$$ = -$2;}
      | VARIABLE {
        int si = get_symbol_index($1);
        if (si == -1) {
          fprintf(stderr, "Error: undeclared variable '%s'\n", $1);
          exit(1);
        }

        Symbol symb = symb_table[si];
                printf("%d\n", symb.c);

        if (symb.type == TYPE_INT) $$ = symb.i;
        if (symb.type == TYPE_BOOL) $$ = symb.b;
        if (symb.type == TYPE_CHAR) $$ = (char)symb.c;
        if (symb.type == TYPE_FLOAT) $$ = symb.f;

        printf("variable: %c\n", symb.c);
      }
%%

int yywrap( ) {
  return 1;
}

void yyerror(const char* str) {
  fprintf(stderr, "Compiler error: '%s'.\n", str);
}

int add_symbol(const char* id, VarType type) { //isso eu usei o chatGPT pra gerar pra mim
  if (symb_count >= 100) {
    fprintf(stderr, "Error: max number of identifiers is 100!\n");
    return -1;
  }

  for (int i = 0; i < symb_count; i++) {
    if (strcmp(symb_table[i].name, id) == 0) {
      return i;
    }
  }

  strncpy(symb_table[symb_count].name, id, 10);
  symb_table[symb_count].name[10] = '\0';
  symb_table[symb_count].type = type;
  return symb_count++;
}

int get_symbol_index(const char* id) {
    for (int i = 0; i < symb_count; i++) {
        if (strcmp(symb_table[i].name, id) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
  yyparse();
  return 0;
}
