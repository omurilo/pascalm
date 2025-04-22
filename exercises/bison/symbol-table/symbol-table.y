%{
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "types.h"

int yywrap();
int yylex();
void yyerror(const char* str);
extern FILE* yyin;

int add_symbol(const char* id, VarType type);
int get_symbol_index(const char* id);
void execute_stmt_list(StmtList* list);
void print_value(Value v);
void print_symbol(Symbol s);

Stmt* make_stmt_write_var(char* var_name);
Stmt* make_stmt_write_lit(Value v);
Stmt* make_stmt_read(char* var_name);
Stmt* make_stmt_if(Value cond, StmtList* then_block, StmtList* else_block);
StmtList* make_stmt_list(Stmt* stmt, StmtList* next);
StmtList* append_stmt_list(StmtList* list, Stmt* stmt);

void print_symbol_table();

static Symbol symb_table[100];
static int symb_count = 0;
%}

%union {
  char* identifier;
  char* val;
  int type;
  struct Node *node;

  Value value;
  struct Stmt* stmt;
  struct StmtList* stmt_list;
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

%type <stmt_list> stmt_list
%type <stmt> stmt if_stmt write read

%type <value> arithmetic_expr factor expr_value logical_expr
%type <type> declaration

%left MINUS PLUS
%left TIMES DIVIDE
%right EXPONENT
%precedence NEG

%left AND OR
%left NOT
%nonassoc GT GTE LT LTE DIFF EQUALS

%define parse.error verbose

%%

progexec:
        declarations stmt_list {
          execute_stmt_list($2);
        }
        |
        ;

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
    stmt {
      $$ = make_stmt_list($1, NULL);
    }
    | stmt_list stmt { 
       $$ = make_stmt_list($2, $1);
    } 

stmt:
    write SEMICOLON {
      $$ = $1;
    }
    | atrib SEMICOLON {}
    | if_stmt {
      $$ = $1;
    }
    | read SEMICOLON {
      $$ = $1;
    }

write:
    WRITE_ID {
        $$ = make_stmt_write_var($1);
    }
    | WRITE {
        $$ = make_stmt_write_lit($1);
    }

read:
    READ {
      $$ = make_stmt_read($1);
    }

if_stmt:
    IF L_PAREN logical_expr R_PAREN THEN L_CBRACE stmt_list R_CBRACE {
        $<stmt>$ = make_stmt_if($3, $7, NULL);
    }
  | IF L_PAREN logical_expr R_PAREN THEN L_CBRACE stmt_list R_CBRACE ELSE L_CBRACE stmt_list R_CBRACE {
        $<stmt>$ = make_stmt_if($3, $7, $11);
    }

atrib: VARIABLE ATTRIB expr_value {
        int attrib_si = get_symbol_index($1);
        char buffer[256];
        
        if (attrib_si == -1) {
          snprintf(buffer, sizeof(buffer),
            "Undefined declaration of identifier '%s'", $1);
          yyerror(buffer);
        }

        char val_type = $3.type;

        switch (symb_table[attrib_si].type) {
          case TYPE_INT:
            if (val_type == TYPE_INT) {
              symb_table[attrib_si].i = $3.i;
            } else {
              snprintf(buffer, sizeof(buffer),
                      "Semantic Error: Variable '%s' type mismatch", $1);
              yyerror(buffer);
            }
            break;
          case TYPE_BOOL:
            if (val_type == TYPE_BOOL) {
              symb_table[attrib_si].b = $3.b;
            } else {
              snprintf(buffer, sizeof(buffer),
                      "Semantic Error: Variable '%s' type mismatch", $1);
              yyerror(buffer);
            }
            break;
          case TYPE_CHAR:
            if (val_type == TYPE_CHAR) {
              symb_table[attrib_si].c = $3.c;
            } else {
              snprintf(buffer, sizeof(buffer),
                      "Semantic Error: Variable '%s' type mismatch", $1);
              yyerror(buffer);
            }
            break;
          case TYPE_FLOAT:
            if (val_type == TYPE_FLOAT) {
              symb_table[attrib_si].f = $3.f;
            } else {
              snprintf(buffer, sizeof(buffer),
                      "Semantic Error: Variable '%s' type mismatch", $1);
              yyerror(buffer);
            }
            break;
          default:
            break;
        }
      }

expr_value:
          arithmetic_expr { $$ = $1; }
          | logical_expr { $$ = $1; }
 
logical_expr:
    arithmetic_expr GT arithmetic_expr {
      $$.type = TYPE_BOOL;

      if ($1.type == TYPE_INT && $3.type == TYPE_INT) {
        $$.b = $1.i > $3.i;
      }

      if ($1.type == TYPE_FLOAT || $3.type == TYPE_FLOAT) {
        $$.b = ($1.type == TYPE_INT ? (double)$1.i : $1.f) > ($3.type == TYPE_INT ? (double)$3.i : $3.f);
      }
    }
    | arithmetic_expr GTE arithmetic_expr {
        $$.type = TYPE_BOOL;

        if ($1.type == TYPE_INT && $3.type == TYPE_INT) {
          $$.b = $1.i >= $3.i;
        }

        if ($1.type == TYPE_FLOAT || $3.type == TYPE_FLOAT) {
          $$.b = ($1.type == TYPE_INT ? (double)$1.i : $1.f) >= ($3.type == TYPE_INT ? (double)$3.i : $3.f);
        }
      }
    | arithmetic_expr LT arithmetic_expr {
        $$.type = TYPE_BOOL;

        if ($1.type == TYPE_INT && $3.type == TYPE_INT) {
          $$.b = $1.i < $3.i;
        }

        if ($1.type == TYPE_FLOAT || $3.type == TYPE_FLOAT) {
          $$.b = ($1.type == TYPE_INT ? (double)$1.i : $1.f) < ($3.type == TYPE_INT ? (double)$3.i : $3.f);
        }
      }
    | arithmetic_expr LTE arithmetic_expr {
        $$.type = TYPE_BOOL;

        if ($1.type == TYPE_INT && $3.type == TYPE_INT) {
          $$.b = $1.i <= $3.i;
        }

        if ($1.type == TYPE_FLOAT || $3.type == TYPE_FLOAT) {
          $$.b = ($1.type == TYPE_INT ? (double)$1.i : $1.f) <= ($3.type == TYPE_INT ? (double)$3.i : $3.f);
        }
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
          case TYPE_INT: {
            $$.type = TYPE_INT;
            $$.i = symb.i;
            break;
          }
          case TYPE_FLOAT: {
            $$.type = TYPE_FLOAT;
            $$.f = symb.f;
            break;
          }
          case TYPE_BOOL: {
            $$.type = TYPE_BOOL;
            $$.b = symb.b;
            break;
          }
          case TYPE_CHAR: {
            $$.type = TYPE_CHAR;
            $$.c = symb.c;
            break;
          }
          default:
            break;
        }
      }
%%

int add_symbol(const char* id, VarType type) {
  if (symb_count >= 100) {
    fprintf(stderr, "Error: max number of identifiers is 100!\n");
    return -1;
  }

  for (int i = 0; i < symb_count; i++) {
    if (strcmp(symb_table[i].name, id) == 0) {
      return i;
    }
  }

  Symbol* sym = &symb_table[symb_count];
  strncpy(sym->name, id, sizeof(sym->name) - 1);
  sym->type = type;
  sym->name[sizeof(sym->name)-1] = '\0';
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

StmtList* make_stmt_list(Stmt* stmt, StmtList* list) {
  StmtList* new_node = (StmtList*) malloc(sizeof(StmtList));
  new_node->stmt = stmt;
  new_node->next = NULL;

  if (list == NULL) {
    return new_node;
  }

  StmtList* tail = list;
  while (tail->next != NULL) {
    tail = tail->next;
  }

  tail->next = new_node;
  return list;
}

Stmt* make_stmt_write_var(char* var_name) {
  Stmt* s = (Stmt*) malloc(sizeof(Stmt));
  s->type = STMT_WRITE;
  s->write.var_name = strdup(var_name);
  s->write.is_literal = 0;
  return s;
}

Stmt* make_stmt_write_lit(Value literal) {
  Stmt* s = (Stmt*) malloc(sizeof(Stmt));
  s->type = STMT_WRITE;
  s->write.literal = literal;
  s->write.is_literal = 1;
  return s;
}

Stmt* make_stmt_read(char* var_name) {
  Stmt* s = (Stmt*) malloc(sizeof(Stmt));
  s->type = STMT_READ;
  s->read.var_name = var_name;
  return s;
}

Stmt* make_stmt_if(Value cond, StmtList* then_block, StmtList* else_block) {
  Stmt* s = (Stmt*) malloc(sizeof(Stmt));
  s->type = STMT_IF;
  s->if_stmt.cond = cond;
  s->if_stmt.then_block = then_block;
  s->if_stmt.else_block = else_block;
  return s;
}

void execute_stmt(Stmt* s) {
  switch (s->type) {
    case STMT_WRITE:
      if (s->write.is_literal) {
          print_value(s->write.literal);
      } else {
          int i = get_symbol_index(s->write.var_name);
          if (i == -1) {
            fprintf(stderr, "Error: undeclared variable '%s'\n", s->write.var_name);
            exit(1);
          }

          print_symbol(symb_table[i]);
      }
      break;
    case STMT_READ: {
      int read_si = add_symbol(s->read.var_name, TYPE_STRING);

      if (read_si == -1) {
        fprintf(stderr, "Error to declare variable '%s'\n", s->read.var_name);
        exit(1);
      }

      Symbol* read_symb = &symb_table[read_si];

      if (read_symb->s == NULL) {
        read_symb->s = (char*) calloc(100, sizeof(char));
        if (!read_symb->s) {
          fprintf(stderr, "Error on allocate memory to variable '%s'\n", read_symb->name);
          exit(1);
        }
      }

      if (fgets(read_symb->s, 100, stdin) == NULL) {
        fprintf(stderr, "Error on read value for '%s'\n", read_symb->name);
        exit(1); 
      }

      read_symb->s[strcspn(read_symb->s, "\n")] = '\0';
      break;
    }
    case STMT_IF:
      if (s->if_stmt.cond.b) {
          execute_stmt_list(s->if_stmt.then_block);
      } else if (s->if_stmt.else_block) {
          execute_stmt_list(s->if_stmt.else_block);
      }
      break;
  }
}

void execute_stmt_list(StmtList* list) {
  while (list) {
    execute_stmt(list->stmt);
    list = list->next;
  }
}

void print_symbol(Symbol symb) {
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
      break;
  }
}

void print_value(Value v) {
  switch (v.type) {
    case TYPE_FLOAT:
      printf("%.2f\n", v.f);
      break;
    case TYPE_CHAR:
      printf("%c\n", v.c);
      break;
    case TYPE_STRING:
      printf("%s\n", v.s);
      free(v.s);
      break;
    default:
      fprintf(stderr, "Erro: tipo de valor desconhecido\n");
      break;
  }
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
