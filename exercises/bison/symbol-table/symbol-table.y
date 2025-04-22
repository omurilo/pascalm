%{
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_BOOL,
    TYPE_CHAR,
    TYPE_STRING
} VarType;

typedef struct {
    char name[11];
    VarType type;
    union {
      int i;
      double f;
      char c;
      int b;
      char* s;
    };
} Symbol;

int yywrap();
int yylex();
void yyerror(const char* str);
extern FILE* yyin;

int add_symbol(const char* id, VarType type);
int get_symbol_index(const char* id);

static Symbol symb_table[100];
static int symb_count = 0;
%}

%union {
  char* identifier;
  char* val;
  int type;
  struct Node *node;

  struct {
    int type;
    union {
      int i;
      bool b;
      char c;
      double f;
      char* s;
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
%token EXPONENT

%token <value> VAL
%token <identifier> VARIABLE
%token <type> TYPE

%token <value> WRITE
%token <identifier> WRITE_ID
%token <identifier> READ

%type <value> stmt arithmetic_expr factor stmt_list expr_value logical_expr
%type <type> declaration

%left MINUS PLUS
%left TIMES DIVIDE
%right EXPONENT
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
      fprintf(stderr, "Error to declare variables");
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
    | write SEMICOLON {}
    | READ SEMICOLON {
      int si = add_symbol($1, TYPE_STRING);

      if (si == -1) {
        fprintf(stderr, "Error: undeclared variable '%s'\n", $1);
        exit(1);
      }

      Symbol* symb = &symb_table[si];

      if (symb->s == NULL) {
        symb->s = (char*) calloc(100, sizeof(char));
        if (!symb->s) {
          fprintf(stderr, "Error on allocate memory to variable '%s'\n", symb->name);
          exit(1);
        }
      }

      if (fgets(symb->s, 100, stdin) == NULL) {
        fprintf(stderr, "Error on read value for '%s'\n", symb->name);
        exit(1); 
      }

      symb->s[strcspn(symb->s, "\n")] = '\0';
    }

write:
     WRITE_ID {
      int si = get_symbol_index($1);
      if (si == -1) {
        fprintf(stderr, "Error: undeclared variable '%s'\n", $1);
        exit(1);
      }

      Symbol symb = symb_table[si];
      switch (symb.type) {
        case TYPE_INT:
          printf("%d\n", symb.i);
          break;
        case TYPE_FLOAT:
          printf("%.2f\n", symb.f);
          break;
        case TYPE_BOOL:
          printf("%s\n", symb.b == 1 ? "true" : "false");
          break;
        case TYPE_CHAR:
          printf("%c\n", symb.c);
          break;
        case TYPE_STRING:
          printf("%s\n", symb.s);
      }
     }
     | WRITE {
        switch ($1.type) {
          case TYPE_FLOAT:
            printf("%.2f\n", $1.f);
            break;
          case TYPE_CHAR:
            printf("%c\n", $1.c);
            break;
          case TYPE_STRING:
            printf("%s\n", $1.s);
            free($1.s);
            break;
        }
      }

if_stmt:
    IF L_PAREN logical_expr R_PAREN THEN L_CBRACE stmt_list R_CBRACE { 
      if ($3.b) {
        $<value>$ = $7;
              }
    }
    | IF L_PAREN logical_expr R_PAREN THEN L_CBRACE stmt_list R_CBRACE ELSE L_CBRACE stmt_list R_CBRACE {
      if ($3.b) { 
        $<value>$ = $7;
              } else {
        $<value>$ = $11;
              }
    }

atrib: VARIABLE ATTRIB expr_value {
     int si = get_symbol_index($1);
     char buffer[256];
     if (si != -1) {
      Symbol symb = symb_table[si];
      char val_type = $3.type;

      switch (symb.type) {
        case TYPE_INT:
          if (val_type == TYPE_INT) {
            symb_table[si].i = $3.i;
          } else {
            snprintf(buffer, sizeof(buffer),
                    "Semantic Error: Variable '%s' type mismatch", $1);
            yyerror(buffer);
          }
          break;
        case TYPE_BOOL:
          if (val_type == TYPE_BOOL) {
            symb_table[si].b = $3.b;
          } else {
            snprintf(buffer, sizeof(buffer),
                    "Semantic Error: Variable '%s' type mismatch", $1);
            yyerror(buffer);
          }
          break;
        case TYPE_CHAR:
          if (val_type == TYPE_CHAR) {
            symb_table[si].c = $3.c;
          } else {
            snprintf(buffer, sizeof(buffer),
                    "Semantic Error: Variable '%s' type mismatch", $1);
            yyerror(buffer);
          }
          break;
        case TYPE_FLOAT:
          if (val_type == TYPE_FLOAT) {
            symb_table[si].f = $3.f;
          } else {
            snprintf(buffer, sizeof(buffer),
                    "Semantic Error: Variable '%s' type mismatch", $1);
            yyerror(buffer);
          }
          break;
      }
     } else {
      snprintf(buffer, sizeof(buffer),
              "Undefined declaration of identifier '%s'", $1);
      yyerror(buffer);
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

        if ($1.type == TYPE_INT && $3.type == TYPE_INT) {
          $$.b = $1.i == $3.i;
        }

        if ($1.type == TYPE_FLOAT || $3.type == TYPE_FLOAT) {
          $$.b = ($1.type == TYPE_INT ? (double)$1.i : $1.f) == ($3.type == TYPE_INT ? (double)$3.i : $3.f);
        }
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
    arithmetic_expr PLUS arithmetic_expr {
      if ($1.type == TYPE_INT && $3.type == TYPE_INT) {
        $$.type = TYPE_INT;
        $$.i = $1.i + $3.i;
      } else {
        $$.type = TYPE_FLOAT;
        $$.f = ($1.type == TYPE_INT ? (double)$1.i : $1.f) + ($3.type == TYPE_INT ? (double)$3.i : $3.f);
      }
    }
    | arithmetic_expr MINUS arithmetic_expr  {
      if ($1.type == TYPE_INT && $3.type == TYPE_INT) {
        $$.type = TYPE_INT;
        $$.i = $1.i - $3.i;
      } else {
        $$.type = TYPE_FLOAT;
        $$.f = ($1.type == TYPE_INT ? (double)$1.i : $1.f) - ($3.type == TYPE_INT ? (double)$3.i : $3.f);
      }
    }
    | arithmetic_expr TIMES arithmetic_expr  {
      if ($1.type == TYPE_INT && $3.type == TYPE_INT) {
        $$.type = TYPE_INT;
        $$.i = $1.i * $3.i;
      } else {
        $$.type = TYPE_FLOAT;
        $$.f = ($1.type == TYPE_INT ? (double)$1.i : $1.f) * ($3.type == TYPE_INT ? (double)$3.i : $3.f);
      }
    }
    | arithmetic_expr DIVIDE arithmetic_expr  {
      if ($1.type == TYPE_INT && $3.type == TYPE_INT) {
        $$.type = TYPE_INT;
        $$.i = $1.i / $3.i;
      } else {
        $$.type = TYPE_FLOAT;
        $$.f = ($1.type == TYPE_INT ? (double)$1.i : $1.f) / ($3.type == TYPE_INT ? (double)$3.i : $3.f); 
      }
    }
    | arithmetic_expr EXPONENT arithmetic_expr {
      if ($1.type == TYPE_INT && $3.type == TYPE_INT) {
        $$.type = TYPE_INT;
        $$.i = pow($1.i, $3.i);
      } else {
        $$.type = TYPE_FLOAT;
        $$.f = pow(($1.type == TYPE_INT ? (double)$1.i : $1.f), ($3.type == TYPE_INT ? (double)$3.i : $3.f));
      }
    }
    | L_PAREN arithmetic_expr R_PAREN {$$ = $2;}
    | factor {$$ = $1;}

factor: 
      VAL {$$ = $1;}
      | MINUS VAL %prec NEG {
        $$.type = $2.type;
        if ($2.type == TYPE_INT) {
          $$.i = -$2.i;
        } else {
          $$.f = -$2.f;
        }
      }
      | VARIABLE {
        int si = get_symbol_index($1);
        if (si == -1) {
          fprintf(stderr, "Error: undeclared variable '%s'\n", $1);
          exit(1);
        }

        Symbol symb = symb_table[si];
  
        switch (symb.type) {
          case TYPE_INT:
            $$.type = TYPE_INT;
            $$.i = symb.i;
            break;
          case TYPE_FLOAT:
            $$.type = TYPE_FLOAT;
            $$.f = symb.f;
            break;
          case TYPE_BOOL:
            $$.type = TYPE_BOOL;
            $$.b = symb.b;
            break;
          case TYPE_CHAR:
            $$.type = TYPE_CHAR;
            $$.c = symb.c;
            break;
        }
      }
%%

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

int yywrap( ) {
  return 1;
}

void yyerror(const char* str) {
  fprintf(stderr, "Compiler error: '%s'.\n", str);
  exit(1);
}

int main(int argc, char** argv) {
  if (argc > 1) {
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "Error on open file");
        return 1;
    }
  }

  yyparse();
  return 0;
}
