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
Value evaluate_arithmetic_expr(Stmt* stmt);
Value evaluate_logical_expr(Stmt* stmt);
Value evaluate_factor_expr(Stmt* stmt);
void print_value(Value v);
void print_symbol(Symbol s);

Stmt* make_stmt_write_var(char* var_name);
Stmt* make_stmt_write_lit(Value v);
Stmt* make_stmt_read(char* var_name);
Stmt* make_stmt_if(Stmt* cond, StmtList* then_block, StmtList* else_block);
Stmt* make_stmt_while(Stmt* cond, StmtList* body);
Stmt* make_stmt_logical(Stmt* left, Operation op, Stmt* right);
Stmt* make_stmt_arithmetic(Stmt* left, ArithmeticOp op, Stmt* right);
Stmt* make_stmt_factor(Value val, bool minus_unary);
Stmt* make_stmt_factor_var(char* variable);
Stmt* make_stmt_attrib(char* variable, Stmt* value);
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
%token WHILE WHILE_DO WHILE_BEGIN WHILE_END

%token <value> VAL
%token <identifier> VARIABLE
%token <type> TYPE

%token <value> WRITE
%token <identifier> WRITE_ID
%token <identifier> READ

%type <stmt_list> stmt_list
%type <stmt> stmt if_stmt write read while expr_value logical_expr arithmetic_expr factor atrib

/* %type <value> factor */
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
    if_stmt { $$ = $1; }
    | read SEMICOLON { $$ = $1; }
    | write SEMICOLON { $$ = $1; }
    | while SEMICOLON {}
    | atrib SEMICOLON {}


while:
    WHILE logical_expr WHILE_DO WHILE_BEGIN stmt_list WHILE_END {
      $$ = make_stmt_while($2, $5);
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
      $$ = make_stmt_if($3, $7, NULL);
    }
    | IF L_PAREN logical_expr R_PAREN THEN L_CBRACE stmt_list R_CBRACE ELSE L_CBRACE stmt_list R_CBRACE {
      $$ = make_stmt_if($3, $7, $11);
    }

atrib: VARIABLE ATTRIB expr_value {
      $$ = make_stmt_attrib($1, $3);
    }

expr_value:
          arithmetic_expr { $$ = $1; }
          | logical_expr { $$ = $1; }
 
logical_expr:
    arithmetic_expr GT arithmetic_expr {
      $$ = make_stmt_logical($1, OP_GT, $3);
    }
    | arithmetic_expr GTE arithmetic_expr {
        $$ = make_stmt_logical($1, OP_GTE, $3);
      }
    | arithmetic_expr LT arithmetic_expr {
        $$ = make_stmt_logical($1, OP_LT, $3);
      }
    | arithmetic_expr LTE arithmetic_expr {
        $$ = make_stmt_logical($1, OP_LTE, $3);
      }
    | arithmetic_expr EQUALS arithmetic_expr {
        $$ = make_stmt_logical($1, OP_EQUALS, $3);
      }
    | arithmetic_expr DIFF arithmetic_expr {
        $$ = make_stmt_logical($1, OP_DIFF, $3);
      }
    | L_PAREN logical_expr AND logical_expr R_PAREN {
        $$ = make_stmt_logical($2, OP_AND, $4);
      }
    | L_PAREN logical_expr OR logical_expr R_PAREN {
        $$ = make_stmt_logical($2, OP_OR, $4);
      }
    | L_PAREN NOT logical_expr R_PAREN {
        $$ = make_stmt_logical(NULL, OP_NOT, $3);
      }

arithmetic_expr: 
    arithmetic_expr PLUS arithmetic_expr {
      $$ = make_stmt_arithmetic($1, AOP_PLUS, $3);
    }
    | arithmetic_expr MINUS arithmetic_expr  {
      $$ = make_stmt_arithmetic($1, AOP_MINUS, $3);
    }
    | arithmetic_expr TIMES arithmetic_expr  {
      $$ = make_stmt_arithmetic($1, AOP_TIMES, $3);
    }
    | arithmetic_expr DIVIDE arithmetic_expr  {
      $$ = make_stmt_arithmetic($1, AOP_DIVIDE, $3);
    }
    | arithmetic_expr EXPONENT arithmetic_expr {
      $$ = make_stmt_arithmetic($1, AOP_EXPONENT, $3);
    }
    | L_PAREN arithmetic_expr R_PAREN { $$ = $2; }
    | factor { $$ = $1; }

factor: 
      VAL {
        $$ = make_stmt_factor($1, false);
      }
      | MINUS VAL %prec NEG {
        $$ = make_stmt_factor($2, true);
      }
      | VARIABLE {
        $$ = make_stmt_factor_var($1);
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

Symbol* get_symbol_by_name(const char* id) {
  int i = get_symbol_index(id);
  if (i == -1) {
    fprintf(stderr, "foi aqui mesmo, id: %d\n", id);
    fprintf(stderr, "Error: undeclared variable '%s'\n", id);
    exit(1);
  }

  return &symb_table[i];
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

Stmt* make_stmt_if(Stmt* cond, StmtList* then_block, StmtList* else_block) {
  Stmt* s = (Stmt*) malloc(sizeof(Stmt));
  s->type = STMT_IF;
  s->if_stmt.cond = cond;
  s->if_stmt.then_block = then_block;
  s->if_stmt.else_block = else_block;
  return s;
}

Stmt* make_stmt_while(Stmt* cond, StmtList* body) {
  Stmt* s = (Stmt*) malloc(sizeof(Stmt));
  s->type = STMT_WHILE;
  s->while_stmt.cond = cond;
  s->while_stmt.body = body;
  return s;
}

Stmt* make_stmt_logical(Stmt* left, Operation op, Stmt* right) {
  Stmt* s = (Stmt*) malloc(sizeof(Stmt));
  s->type = STMT_LOGICAL;
  s->logical_stmt.left = left;
  s->logical_stmt.right = right;
  s->logical_stmt.op = op;
  return s;
}

Stmt* make_stmt_arithmetic(Stmt* left, ArithmeticOp op, Stmt* right) {
  Stmt* s = (Stmt*) malloc(sizeof(Stmt));
  s->type = STMT_ARITHMETIC;
  s->arithmetic_stmt.left = left;
  s->arithmetic_stmt.right = right;
  s->arithmetic_stmt.op = op;
  return s;
}

Stmt* make_stmt_factor_var(char* variable) {
  Stmt* s = (Stmt*) malloc(sizeof(Stmt));
  s->type = STMT_FACTOR;
  fprintf(stderr, "var_name on factor var %s\n", variable);
  s->factor_stmt.var_name = strdup(variable);
  s->factor_stmt.uminus = false;
  return s;
}

Stmt* make_stmt_factor(Value val, bool minus_unary) {
  Stmt* s = (Stmt*) malloc(sizeof(Stmt));
  s->type = STMT_FACTOR;
  s->factor_stmt.var_name = NULL;
  s->factor_stmt.value = val;
  s->factor_stmt.uminus = minus_unary;
  return s;
}

Stmt* make_stmt_attrib(char* variable, Stmt* value) {
  Stmt* s = (Stmt*) malloc(sizeof(Stmt));
  s->type = STMT_ATTRIB;
  s->attrib_stmt.var_name = strdup(variable);
  s->attrib_stmt.value = value;
  return s;
}

Value evaluate_factor_expr(Stmt* s) {
  Value result;

  fprintf(stderr, "var_name: %s, cmp: %d\n", s->factor_stmt.var_name);
  if (s->factor_stmt.var_name != NULL) {
    Symbol* symb = get_symbol_by_name(s->factor_stmt.var_name);

    result.type = symb->type;

    switch (result.type) {
      case TYPE_INT:
        result.i = symb->i;
        break;
      case TYPE_FLOAT:
        result.f = symb->f;
        break;
      case TYPE_BOOL:
        result.b = symb->b;
        break;
      case TYPE_CHAR:
        result.c = symb->c;
        break;
      default:
        break;
    }
  } else {
    result.type = s->factor_stmt.value.type;

    switch (result.type) {
      case TYPE_INT:
        result.i = s->factor_stmt.uminus ? -s->factor_stmt.value.i : s->factor_stmt.value.i;
        break;
      case TYPE_FLOAT: 
        result.f = s->factor_stmt.uminus ? -s->factor_stmt.value.f : s->factor_stmt.value.f;
        break;
      case TYPE_CHAR:
        result.c = s->factor_stmt.value.c;
        break;
      case TYPE_BOOL:
        result.b = s->factor_stmt.value.b;
        break;
      default:
        break;
    }
  }

  return result;
}

Value evaluate_arithmetic_expr(Stmt* s) {
  double d1, d2;
  int i1, i2;

  Value value;

  if (s->type != STMT_ARITHMETIC) {
    return evaluate_factor_expr(s);
  } 

  if (s->arithmetic_stmt.left != NULL) {
    Value t1 = evaluate_factor_expr(s->arithmetic_stmt.left);
    if (t1.type == TYPE_INT) {
      i1 = t1.i;
    } else {
      d1 = t1.f;
    }
  }

  Value t2 = evaluate_factor_expr(s->arithmetic_stmt.right);
  if (t2.type == TYPE_INT) {
    i2 = t2.i;
  } else {
    d2 = t2.f;
  }
  switch (s->arithmetic_stmt.op) {
    case AOP_PLUS: {
      if (i1 >= 0 && i2 >= 0) {
        value.type = TYPE_INT;
        value.i = i1 + i2;
        return value;
      }
  
      value.type = TYPE_FLOAT;
      value.f = (i1 >= 0 ? (double)i1 : d1) + (i2 >= 0 ? (double)i2 : d2);
      return value;
    }
    case AOP_MINUS: {
      if (i1 >= 0 && i2 >= 0) {
        value.type = TYPE_INT;
        value.i = i1 - i2;
        return value;
      }
      
      value.type = TYPE_FLOAT;
      value.f = (i1 >= 0 ? (double)i1 : d1) - (i2 >= 0 ? (double)i2 : d2);
      return value;
    }
    case AOP_TIMES: {
      if (i1 >= 0 && i2 >= 0) {
        value.type = TYPE_INT;
        value.i = i1 * i2;
        return value;
      }
      
      value.type = TYPE_FLOAT;
      value.f = (i1 >= 0 ? (double)i1 : d1) * (i2 >= 0 ? (double)i2 : d2);
      return value;
    }
    case AOP_DIVIDE: {
      if (i1 >= 0 && i2 >= 0) {
        value.type = TYPE_INT;
        value.i = i1 / i2;
        return value;
      }
      
      value.type = TYPE_FLOAT;
      value.f = (i1 >= 0 ? (double)i1 : d1) / (i2 >= 0 ? (double)i2 : d2);
      return value;
    }
    case AOP_EXPONENT: {
      if (i1 >= 0 && i2 >= 0) {
        value.type = TYPE_INT;
        value.i = pow(i1, i2);
        return value;
      }

      value.type = TYPE_FLOAT;
      value.f = pow((i1 >= 0 ? i1 : d1), (i2 >= 0 ? i2 : d2)); 
      return value;
    }
    case AOP_UMINUS: {
      if (i2 >= 0) {
        value.type = TYPE_INT;
        value.i = -i2;
        return value;
      }

      value.type = TYPE_FLOAT;
      value.f = -d2;
      return value;
    }
    default:
      return value;
  }
  
}

Value evaluate_logical_expr(Stmt* s) {
  Value t1, t2, result;

  result.type == TYPE_BOOL;

  switch (s->logical_stmt.op) {
    case OP_GT: {
      t1 = evaluate_arithmetic_expr(s->logical_stmt.left);
      t2 = evaluate_arithmetic_expr(s->logical_stmt.right);
      if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
        result.b = t1.i > t2.i;
      } else {
        result.b = t1.f > t2.f;
      }
      return result;
    }
    case OP_GTE: {
      t1 = evaluate_arithmetic_expr(s->logical_stmt.left);
      t2 = evaluate_arithmetic_expr(s->logical_stmt.right);
      if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
        result.b = t1.i >= t2.i;
      } else {
        result.b = t1.f >= t2.f;
      }
      return result;
    }
    case OP_LT: {
      t1 = evaluate_arithmetic_expr(s->logical_stmt.left);
      t2 = evaluate_arithmetic_expr(s->logical_stmt.right);
      if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
        result.b = t1.i < t2.i;
      } else {
        result.b = t1.f < t2.f;
      }
      return result;
    }
    case OP_LTE: {
      t1 = evaluate_arithmetic_expr(s->logical_stmt.left);
      t2 = evaluate_arithmetic_expr(s->logical_stmt.right);
      if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
        result.b = t1.i <= t2.i;
      } else {
        result.b = t1.f <= t2.f;
      }
      return result;
    }
    case OP_EQUALS: {
      t1 = evaluate_arithmetic_expr(s->logical_stmt.left);
      t2 = evaluate_arithmetic_expr(s->logical_stmt.right);
      if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
        result.b = t1.i == t2.i;
      } else {
        result.b = t1.f == t2.f;
      }
      return result;
    }
    case OP_DIFF: {
      t1 = evaluate_arithmetic_expr(s->logical_stmt.left);
      t2 = evaluate_arithmetic_expr(s->logical_stmt.right);
      if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
        result.b = t1.i != t2.i;
      } else {
        result.b = t1.f != t2.f;
      }
      return result;
    }
    case OP_AND: {
      t1 = evaluate_logical_expr(s->logical_stmt.left);
      t2 = evaluate_logical_expr(s->logical_stmt.right);
      result.b = t1.b && t2.b;
      return result;
    }
    case OP_OR: {
      t1 = evaluate_logical_expr(s->logical_stmt.left);
      t2 = evaluate_logical_expr(s->logical_stmt.right);
      result.b = t1.b || t2.b;
      return result;
    } 
    case OP_NOT: {
      t2 = evaluate_logical_expr(s->logical_stmt.right);
      result.b = !t2.b;
      return result;
    }
    default:
      return result;
  }
}

void execute_stmt(Stmt* s) {
  switch (s->type) {
    case STMT_ARITHMETIC:
      printf("esse é o execute stmt pra arithmetic stmt");
      break;
    case STMT_LOGICAL:
      printf("esse é o execute stmt pra logical stmt");
      break;
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
      if (evaluate_logical_expr(s->if_stmt.cond).b) {
        execute_stmt_list(s->if_stmt.then_block);
      } else if (s->if_stmt.else_block) {
        execute_stmt_list(s->if_stmt.else_block);
      }
      break;
    case STMT_WHILE: {
      while (evaluate_logical_expr(s->while_stmt.cond).b) {
        execute_stmt_list(s->while_stmt.body);
      }
      break;
    }
    case STMT_ATTRIB: {
      int attrib_si = get_symbol_index(s->attrib_stmt.var_name);
      char buffer[256];
      
      if (attrib_si == -1) {
        snprintf(buffer, sizeof(buffer),
          "Undefined declaration of identifier '%s'", s->attrib_stmt.var_name);
        yyerror(buffer);
      }

      Value expr_value;

      if (s->attrib_stmt.value->type == STMT_LOGICAL) {
        expr_value = evaluate_logical_expr(s->attrib_stmt.value);
      } else if (s->attrib_stmt.value->type == STMT_ARITHMETIC){
        expr_value = evaluate_arithmetic_expr(s->attrib_stmt.value);
      } else if (s->attrib_stmt.value->type == STMT_FACTOR) {
        expr_value = evaluate_factor_expr(s->attrib_stmt.value);
      }

      char val_type = expr_value.type;

      switch (symb_table[attrib_si].type) {
        case TYPE_INT:
          if (val_type == TYPE_INT) {
            symb_table[attrib_si].i = expr_value.i;
          } else {
            snprintf(buffer, sizeof(buffer),
                    "Semantic Error: Variable '%s' type mismatch", s->attrib_stmt.var_name);
            yyerror(buffer);
          }
          break;
        case TYPE_BOOL:
          printf("val_type: %d\n", val_type);
          if (val_type == TYPE_BOOL) {
            symb_table[attrib_si].b = expr_value.b;
          } /*else {
            snprintf(buffer, sizeof(buffer),
                    "Semantic Error: Variable '%s' type mismatch", s->attrib_stmt.var_name);
            yyerror(buffer);
          }*/
          break;
        case TYPE_CHAR:
          if (val_type == TYPE_CHAR) {
            symb_table[attrib_si].c = expr_value.c;
          } else {
            snprintf(buffer, sizeof(buffer),
                    "Semantic Error: Variable '%s' type mismatch", s->attrib_stmt.var_name);
            yyerror(buffer);
          }
          break;
        case TYPE_FLOAT:
          if (val_type == TYPE_FLOAT) {
            symb_table[attrib_si].f = expr_value.f;
          } else {
            snprintf(buffer, sizeof(buffer),
                    "Semantic Error: Variable '%s' type mismatch", s->attrib_stmt.var_name);
            yyerror(buffer);
          }
          break;
        default:
          break;
      }
      break;
    }
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
