%{
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "types.h"
#include <stdarg.h>

int yywrap();
int yylex();
void yyerror(const char* str);
extern FILE* yyin;

int add_symbol(const char* id, VarType type);
int get_symbol_index(const char* id);
TAC* execute_stmt_list(StmtList* list);
Value evaluate_arithmetic_expr(Expr* expr);
Value evaluate_logical_expr(Expr* expr);
Value evaluate_factor_expr(Expr* expr);
void print_value(Value v);
void print_symbol(Symbol s);

Stmt* make_stmt_read(char* var_name);
Stmt* make_stmt_if(Expr* cond, StmtList* then_block, StmtList* else_block);
Stmt* make_stmt_while(Expr* cond, StmtList* body);
Stmt* make_stmt_attrib(char* var_name, Expr* expr);
Stmt* make_stmt_write(char* var_name, Expr* expr);

StmtList* make_stmt_list(Stmt* stmt, StmtList* next);
StmtList* append_stmt_list(StmtList* list, Stmt* stmt);

Expr* make_literal_expr(VarType type, Value val, bool uminus);
Expr* make_var_expr(char* name);
Expr* make_arith_expr(Expr* left, Expr* right, ArithmeticOp op);
Expr* make_logic_expr(Expr* left, Expr* right, Operation op);

ExprResult generate_expr_tac(Expr* e);
TAC* generate_stmt_tac(Stmt* s);
TAC* generate_stmt_list_tac(StmtList* list);
TAC* tac_create(const char* fmt, ...);
TAC* tac_append(TAC* list, TAC* new_code);

void tac_print(TAC* code);
void print_symbol_table();

void print_expr(Expr* e);

char* new_temp();
char* new_label();

static Symbol symb_table[100];
static int symb_count = 0;

int temp_count = 0;
int label_count = 0;
%}

%union {
  int type;
  char* identifier;
  char* val;

  Value value;
  Expr* expr;
  Stmt* stmt;
  StmtList* stmt_list;
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
%type <stmt> stmt if_stmt write read while atrib
%type <expr> logical_expr arithmetic_expr expr_value factor_literal factor_var

%type <type> declaration

%left MINUS PLUS
%left TIMES DIVIDE
%right EXPONENT
%precedence NEG

%left AND OR
%left NOT
%nonassoc GT GTE LT LTE DIFF EQUALS

%define parse.error verbose
%locations

%%

progexec:
        declarations stmt_list {
          tac_print(execute_stmt_list($2));
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
    WHILE L_PAREN logical_expr R_PAREN WHILE_DO WHILE_BEGIN stmt_list WHILE_END {
      $$ = make_stmt_while($3, $7);
      $$->lineno = @1.first_line;
      $$->col = @1.first_column;
    }

write:
    WRITE_ID {
        $$ = make_stmt_write($1, NULL);
        $$->lineno = @1.first_line;
        $$->col = @1.first_column;
    }
    | WRITE {
        Expr* e = (Expr*) malloc(sizeof(Expr));
        e->type = EXPR_LITERAL;
        e->literal = $1;
        $$ = make_stmt_write(NULL, e);
        $$->lineno = @1.first_line;
        $$->col = @1.first_column;
    }

read:
    READ {
      $$ = make_stmt_read($1);
      $$->lineno = @1.first_line;
      $$->col = @1.first_column;
    }

if_stmt:
    IF L_PAREN logical_expr R_PAREN THEN L_CBRACE stmt_list R_CBRACE {
      $$ = make_stmt_if($3, $7, NULL);
      $$->lineno = @1.first_line;
      $$->col = @1.first_column;
    }
    | IF L_PAREN logical_expr R_PAREN THEN L_CBRACE stmt_list R_CBRACE ELSE L_CBRACE stmt_list R_CBRACE {
      $$ = make_stmt_if($3, $7, $11);
      $$->lineno = @1.first_line;
      $$->col = @1.first_column;
    }

atrib: VARIABLE ATTRIB expr_value {
      $$ = make_stmt_attrib($1, $3);
      $$->lineno = @1.first_line;
      $$->col = @1.first_column;
    }

expr_value:
          arithmetic_expr { $$ = $1; }
          | logical_expr { $$ = $1; }
 
logical_expr:
    arithmetic_expr GT arithmetic_expr {
      $$ = make_logic_expr($1, $3, OP_GT);
      $$->lineno = @1.first_line;
      $$->col = @1.first_column;
    }
    | arithmetic_expr GTE arithmetic_expr {
        $$ = make_logic_expr($1, $3, OP_GTE);
        $$->lineno = @1.first_line;
        $$->col = @1.first_column;
      }
    | arithmetic_expr LT arithmetic_expr {
        $$ = make_logic_expr($1, $3, OP_LT);
        $$->lineno = @1.first_line;
        $$->col = @1.first_column;
      }
    | arithmetic_expr LTE arithmetic_expr {
        $$ = make_logic_expr($1, $3, OP_LTE);
        $$->lineno = @1.first_line;
        $$->col = @1.first_column;
      }
    | arithmetic_expr EQUALS arithmetic_expr {
        $$ = make_logic_expr($1, $3, OP_EQUALS);
        $$->lineno = @1.first_line;
        $$->col = @1.first_column;
      }
    | arithmetic_expr DIFF arithmetic_expr {
        $$ = make_logic_expr($1, $3, OP_DIFF);
        $$->lineno = @1.first_line;
        $$->col = @1.first_column;
      }
    | L_PAREN logical_expr AND logical_expr R_PAREN {
        $$ = make_logic_expr($2, $4, OP_AND);
        $$->lineno = @1.first_line;
        $$->col = @1.first_column;
      }
    | L_PAREN logical_expr OR logical_expr R_PAREN {
        $$ = make_logic_expr($2, $4, OP_OR);
        $$->lineno = @1.first_line;
        $$->col = @1.first_column;
      }
    | L_PAREN NOT logical_expr R_PAREN {
        $$ = make_logic_expr(NULL, $3, OP_NOT);
        $$->lineno = @1.first_line;
        $$->col = @1.first_column;
      }

arithmetic_expr: 
    arithmetic_expr PLUS arithmetic_expr {
      $$ = make_arith_expr($1, $3, AOP_PLUS);
      $$->lineno = @1.first_line;
      $$->col = @1.first_column;
    }
    | arithmetic_expr MINUS arithmetic_expr  {
      $$ = make_arith_expr($1, $3, AOP_MINUS);
      $$->lineno = @1.first_line;
      $$->col = @1.first_column;
    }
    | arithmetic_expr TIMES arithmetic_expr  {
      $$ = make_arith_expr($1, $3, AOP_TIMES);
      $$->lineno = @1.first_line;
      $$->col = @1.first_column;
    }
    | arithmetic_expr DIVIDE arithmetic_expr  {
      $$ = make_arith_expr($1, $3, AOP_DIVIDE);
      $$->lineno = @1.first_line;
      $$->col = @1.first_column;
    }
    | arithmetic_expr EXPONENT arithmetic_expr {
      $$ = make_arith_expr($1, $3, AOP_EXPONENT);
      $$->lineno = @1.first_line;
      $$->col = @1.first_column;
    }
    | L_PAREN arithmetic_expr R_PAREN { $$ = $2; }
    | factor_literal { $$ = $1; }
    | factor_var { $$ = $1; }

factor_literal: 
      VAL {
        $$ = make_literal_expr($1.type, $1, false);
        $$->lineno = @1.first_line;
        $$->col = @1.first_column;
      }
      | MINUS VAL %prec NEG {
        $$ = make_literal_expr($2.type, $2, true);
        $$->lineno = @1.first_line;
        $$->col = @1.first_column;
      }

factor_var:
      VARIABLE {
        $$ = make_var_expr($1);
        $$->lineno = @1.first_line;
        $$->col = @1.first_column;
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

Stmt* make_stmt_write(char* var_name, Expr* expr) {
  Stmt* s = (Stmt*) malloc(sizeof(Stmt));
  s->type = STMT_WRITE;
  if (var_name != NULL) {
    s->write.var_name = strdup(var_name);
  }
  s->write.expr = expr;
  return s;
}

Stmt* make_stmt_read(char* var_name) {
  Stmt* s = (Stmt*) malloc(sizeof(Stmt));
  s->type = STMT_READ;
  s->read.var_name = strdup(var_name);
  return s;
}

Stmt* make_stmt_if(Expr* cond, StmtList* then_block, StmtList* else_block) {
  Stmt* s = (Stmt*) malloc(sizeof(Stmt));
  s->type = STMT_IF;
  s->if_stmt.cond = cond;
  s->if_stmt.then_block = then_block;
  s->if_stmt.else_block = else_block;
  return s;
}

Stmt* make_stmt_while(Expr* cond, StmtList* body) {
  Stmt* s = (Stmt*) malloc(sizeof(Stmt));
  s->type = STMT_WHILE;
  s->while_stmt.cond = cond;
  s->while_stmt.body = body;
  return s;
}

Expr* make_literal_expr(VarType type, Value val, bool uminus) {
  Expr* e = (Expr*) malloc(sizeof(Expr));
  memset(e, 0, sizeof(Expr));

  e->type = EXPR_LITERAL;
  e->uminus = uminus;
  e->literal.type = type;

  switch (type) {
    case TYPE_BOOL:
      e->literal.data.b = val.data.b;
      break;
    case TYPE_INT:
      e->literal.data.i = val.data.i;
      break;
    case TYPE_CHAR:
      e->literal.data.c = val.data.c;
      break;
    case TYPE_FLOAT:
      e->literal.data.f = val.data.f;
      break;
    case TYPE_STRING:
      e->literal.data.s = strdup(val.data.s);
      break;
    default:
      break;
  }
  return e;
}

Expr* make_var_expr(char* name) {
  Expr* e = (Expr*) malloc(sizeof(Expr));
  e->type = EXPR_VAR;
  e->var_name = strdup(name);
  return e;
}

Expr* make_arith_expr(Expr* left, Expr* right, ArithmeticOp op) {
  Expr* e = (Expr*) malloc(sizeof(Expr));
  e->type = EXPR_ARITH;
  e->arith.left = left;
  e->arith.right = right;
  e->arith.op = op;
  return e;
}

Expr* make_logic_expr(Expr* left, Expr* right, Operation op) {
  Expr* e = (Expr*) malloc(sizeof(Expr));
  e->type = EXPR_LOGIC;
  e->logic.left = left;
  e->logic.right = right;
  e->logic.op = op;
  return e;
}

Stmt* make_stmt_attrib(char* variable, Expr* expr) {
  Stmt* s = (Stmt*) malloc(sizeof(Stmt));
  s->type = STMT_ATTRIB;
  s->assign.var_name = strdup(variable);
  s->assign.expr = expr;
  return s;
}

Value evaluate_factor_expr(Expr* e) {
  Value result;

  if (e->type == EXPR_VAR && e->var_name != NULL && strlen(e->var_name) > 0) {
    Symbol* symb = get_symbol_by_name(e->var_name);

    result.type = symb->type;

    switch (result.type) {
      case TYPE_INT:
        result.data.i = symb->data.i;
        break;
      case TYPE_FLOAT:
        result.data.f = symb->data.f;
        break;
      case TYPE_BOOL:
        result.data.b = symb->data.b;
        break;
      case TYPE_CHAR:
        result.data.c = symb->data.c;
        break;
      default:
        break;
    }
  } else if (e->type == EXPR_LITERAL) {
    result = e->literal;
  } else {
    fprintf(stderr,
      "Erro: expressão inesperada em evaluate_factor_expr\n"
      "  Tipo da expressão: %d\n"
      "  Ponteiro da expressão: %p\n"
      "  var_name: %s\n"
      "  literal.type: %d\n"
      "  line: %d and column: %d\n",
      e->type,
      (void*)e,
      e->var_name ? e->var_name : "(null)",
      e->literal.type,
      e->lineno,
      e->col
    );
    exit(1);
  }

  return result;
}

Value evaluate_arithmetic_expr(Expr* e) {
  Value value;

  if (e->type != EXPR_ARITH) {
    return evaluate_factor_expr(e);
  } 

  Value t1 = e->arith.left != NULL ? evaluate_arithmetic_expr(e->arith.left) : value;
  Value t2 = evaluate_arithmetic_expr(e->arith.right);
  
  switch (e->arith.op) {
    case AOP_PLUS: {
      if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
        value.type = TYPE_INT;
        value.data.i = t1.data.i + t2.data.i;
        return value;
      }
  
      value.type = TYPE_FLOAT;
      value.data.f = (t1.type == TYPE_INT ? (double)t1.data.i : t1.data.f) + (t2.type == TYPE_INT ? (double)t2.data.i : t2.data.f);
      return value;
    }
    case AOP_MINUS: {
      if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
        value.type = TYPE_INT;
        value.data.i = t1.data.i - t2.data.i;
        return value;
      }
      
      value.type = TYPE_FLOAT;
      value.data.f = (t1.type == TYPE_INT ? (double)t1.data.i : t1.data.f) - (t2.type == TYPE_INT ? (double)t2.data.i : t2.data.f);
      return value;
    }
    case AOP_TIMES: {
      if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
        value.type = TYPE_INT;
        value.data.i = t1.data.i * t2.data.i;
        return value;
      }
      
      value.type = TYPE_FLOAT;
      value.data.f = (t1.type == TYPE_INT ? (double)t1.data.i : t1.data.f) * (t2.type == TYPE_INT ? (double)t2.data.i : t2.data.f);
      return value;
    }
    case AOP_DIVIDE: {
      if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
        value.type = TYPE_INT;
        value.data.i = t1.data.i / t2.data.i;
        return value;
      }
      
      value.type = TYPE_FLOAT;
      value.data.f = (t1.type == TYPE_INT ? (double)t1.data.i : t1.data.f) / (t2.type == TYPE_INT ? (double)t2.data.i : t2.data.f);
      return value;
    }
    case AOP_EXPONENT: {
      if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
        value.type = TYPE_INT;
        value.data.i = pow(t1.data.i, t2.data.i);
        return value;
      }

      value.type = TYPE_FLOAT;
      value.data.f = pow((t1.type == TYPE_INT ? (double)t1.data.i : t1.data.f), (t2.type == TYPE_INT ? (double)t2.data.i : t2.data.f)); 
      return value;
    }
    case AOP_UMINUS: {
      if (t2.type == TYPE_INT) {
        value.type = TYPE_INT;
        value.data.i = -t2.data.i;
        return value;
      }

      value.type = TYPE_FLOAT;
      value.data.f = -t2.data.i;
      return value;
    }
    default:
      return value;
  }
  
}

Value evaluate_logical_expr(Expr* e) {
  Value t1, t2, result;

  result.type = TYPE_BOOL;

  switch (e->logic.op) {
    case OP_GT: {
      t1 = evaluate_arithmetic_expr(e->logic.left);
      t2 = evaluate_arithmetic_expr(e->logic.right);
      if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
        result.data.b = t1.data.i > t2.data.i;
      } else {
        result.data.b = t1.data.f > t2.data.f;
      }
      return result;
    }
    case OP_GTE: {
      t1 = evaluate_arithmetic_expr(e->logic.left);
      t2 = evaluate_arithmetic_expr(e->logic.right);
      if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
        result.data.b = t1.data.i >= t2.data.i;
      } else {
        result.data.b = t1.data.f >= t2.data.f;
      }
      return result;
    }
    case OP_LT: {
      t1 = evaluate_arithmetic_expr(e->logic.left);
      t2 = evaluate_arithmetic_expr(e->logic.right);
      if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
        result.data.b = t1.data.i < t2.data.i;
      } else {
        result.data.b = t1.data.f < t2.data.f;
      }
      return result;
    }
    case OP_LTE: {
      t1 = evaluate_arithmetic_expr(e->logic.left);
      t2 = evaluate_arithmetic_expr(e->logic.right);
      if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
        result.data.b = t1.data.i <= t2.data.i;
      } else {
        result.data.b = t1.data.f <= t2.data.f;
      }
      return result;
    }
    case OP_EQUALS: {
      t1 = evaluate_arithmetic_expr(e->logic.left);
      t2 = evaluate_arithmetic_expr(e->logic.right);
      if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
        result.data.b = t1.data.i == t2.data.i;
      } else {
        result.data.b = t1.data.f == t2.data.f;
      }
      return result;
    }
    case OP_DIFF: {
      t1 = evaluate_arithmetic_expr(e->logic.left);
      t2 = evaluate_arithmetic_expr(e->logic.right);
      if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
        result.data.b = t1.data.i != t2.data.i;
      } else {
        result.data.b = t1.data.f != t2.data.f;
      }
      return result;
    }
    case OP_AND: {
      t1 = evaluate_logical_expr(e->logic.left);
      t2 = evaluate_logical_expr(e->logic.right);
      result.data.b = t1.data.b && t2.data.b;
      return result;
    }
    case OP_OR: {
      t1 = evaluate_logical_expr(e->logic.left);
      t2 = evaluate_logical_expr(e->logic.right);
      result.data.b = t1.data.b || t2.data.b;
      return result;
    } 
    case OP_NOT: {
      t2 = evaluate_logical_expr(e->logic.right);
      result.data.b = !t2.data.b;
      return result;
    }
    default:
      return result;
  }
}

void execute_stmt(Stmt* s) {
  switch (s->type) {
    case STMT_WRITE:
      if (!s->write.var_name) {
          // print_value(s->write.expr->literal);
      } else {
          int i = get_symbol_index(s->write.var_name);
          if (i == -1) {
            fprintf(stderr, "Error: undeclared variable '%s' at line: %d and column: %d\n", s->write.var_name, s->lineno, s->col);
            exit(1);
          }

          // print_symbol(symb_table[i]);
      }
      break;
    case STMT_READ: {
      int read_si = add_symbol(s->read.var_name, TYPE_STRING);

      if (read_si == -1) {
        fprintf(stderr, "Error to declare variable '%s' at line: %d and column: %d\n", s->read.var_name, s->lineno, s->col);
        exit(1);
      }

      Symbol* read_symb = &symb_table[read_si];

      if (read_symb->data.s == NULL) {
        read_symb->data.s = (char*) calloc(100, sizeof(char));
        if (!read_symb->data.s) {
          fprintf(stderr, "Error on allocate memory to variable '%s' at line: %d and column: %d\n", read_symb->name, s->lineno, s->col);
          exit(1);
        }
      }

      // if (fgets(read_symb->data.s, 100, stdin) == NULL) {
      //   fprintf(stderr, "Error on read value for '%s' at line: %d and column: %d\n", read_symb->name, s->lineno, s->col);
      //   exit(1); 
      // }
      //
      // read_symb->data.s[strcspn(read_symb->data.s, "\n")] = '\0';
      // break;
    }
    case STMT_IF:
      if (evaluate_logical_expr(s->if_stmt.cond).data.b) {
        execute_stmt_list(s->if_stmt.then_block);
      } else if (s->if_stmt.else_block) {
        execute_stmt_list(s->if_stmt.else_block);
      }
      break;
    case STMT_WHILE: {
      while (evaluate_logical_expr(s->while_stmt.cond).data.b) {
        execute_stmt_list(s->while_stmt.body);
      }
      break;
    }
    case STMT_ATTRIB: {
      int attrib_si = get_symbol_index(s->assign.var_name);
      char buffer[256];
      
      if (attrib_si == -1) {
        snprintf(buffer, sizeof(buffer),
          "Undefined declaration of identifier '%s' at line: %d and column: %d", s->assign.var_name, s->lineno, s->col);
        yyerror(buffer);
      }

      Value expr_value;

      if (s->assign.expr->type == EXPR_LOGIC) {
        expr_value = evaluate_logical_expr(s->assign.expr);
      } else if (s->assign.expr->type == EXPR_ARITH){
        expr_value = evaluate_arithmetic_expr(s->assign.expr);
      } else if (s->assign.expr->type == EXPR_VAR || s->assign.expr->type == EXPR_LITERAL) {
        expr_value = evaluate_factor_expr(s->assign.expr);
      }

      int val_type = expr_value.type;

      switch (symb_table[attrib_si].type) {
        case TYPE_INT:
          if (val_type == TYPE_INT) {
            symb_table[attrib_si].data.i = expr_value.data.i;
          } else {
            snprintf(buffer, sizeof(buffer),
                    "Semantic Error: Variable '%s' type mismatch at line: %d and column: %d", s->assign.var_name, s->lineno, s->col);
            yyerror(buffer);
          }
          break;
        case TYPE_BOOL:
          if (val_type == TYPE_BOOL) {
            symb_table[attrib_si].data.b = expr_value.data.b;
          } else {
            snprintf(buffer, sizeof(buffer),
                    "Semantic Error: Variable '%s' type mismatch at line: %d and column: %d", s->assign.var_name, s->lineno, s->col);
            yyerror(buffer);
          }
          break;
        case TYPE_CHAR:
          if (val_type == TYPE_CHAR) {
            symb_table[attrib_si].data.c = expr_value.data.c;
          } else {
            snprintf(buffer, sizeof(buffer),
                    "Semantic Error: Variable '%s' type mismatch at line: %d and column: %d", s->assign.var_name, s->lineno, s->col);
            yyerror(buffer);
          }
          break;
        case TYPE_FLOAT:
          if (val_type == TYPE_FLOAT) {
            symb_table[attrib_si].data.f = expr_value.data.f;
          } else if (val_type == TYPE_INT) {
            symb_table[attrib_si].data.f = (double)expr_value.data.i;
          } else {
            snprintf(buffer, sizeof(buffer),
                    "Semantic Error: Variable '%s' type mismatch at line: %d and column: %d", s->assign.var_name, s->lineno, s->col);
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

void verify_assign_types(Stmt* s) {
  int attrib_si = get_symbol_index(s->assign.var_name);
  char buffer[256];
  
  if (attrib_si == -1) {
    snprintf(buffer, sizeof(buffer),
      "Undefined declaration of identifier '%s' at line: %d and column: %d", s->assign.var_name, s->lineno, s->col);
    yyerror(buffer);
  }

  Value expr_value;

  if (s->assign.expr->type == EXPR_LOGIC) {
    expr_value = evaluate_logical_expr(s->assign.expr);
  } else if (s->assign.expr->type == EXPR_ARITH){
    expr_value = evaluate_arithmetic_expr(s->assign.expr);
  } else if (s->assign.expr->type == EXPR_VAR || s->assign.expr->type == EXPR_LITERAL) {
    expr_value = evaluate_factor_expr(s->assign.expr);
  }

  int val_type = expr_value.type;

  switch (symb_table[attrib_si].type) {
    case TYPE_INT:
      if (val_type != TYPE_INT) {
         snprintf(buffer, sizeof(buffer),
         "Semantic Error: Variable '%s' type mismatch at line: %d and column: %d", s->assign.var_name, s->lineno, s->col);
        yyerror(buffer);
      }
      break;
    case TYPE_BOOL:
      if (val_type != TYPE_BOOL) {
        snprintf(buffer, sizeof(buffer),
                "Semantic Error: Variable '%s' type mismatch at line: %d and column: %d", s->assign.var_name, s->lineno, s->col);
        yyerror(buffer);
      }
      break;
    case TYPE_CHAR:
      if (val_type != TYPE_CHAR) {
        snprintf(buffer, sizeof(buffer),
                "Semantic Error: Variable '%s' type mismatch at line: %d and column: %d", s->assign.var_name, s->lineno, s->col);
        yyerror(buffer);
      }
      break;
    case TYPE_FLOAT:
      if (val_type != TYPE_FLOAT && val_type != TYPE_INT) {
        snprintf(buffer, sizeof(buffer),
                "Semantic Error: Variable '%s' type mismatch at line: %d and column: %d", s->assign.var_name, s->lineno, s->col);
        yyerror(buffer);
      }
      break;
    default:
      break;
  }
}

TAC* execute_stmt_list(StmtList* list) {
  return generate_stmt_list_tac(list);
  // while (list) {
  //   execute_stmt(list->stmt);
  //   list = list->next;
  // }
}

ExprResult generate_expr_tac(Expr* e) {
  ExprResult res = {NULL, NULL};

  if (e->type == EXPR_ARITH) {
    ExprResult left = generate_expr_tac(e->arith.left);
    ExprResult right;
    char* temp = new_temp();
    char op;
    char buffer[128];

    switch (e->arith.op) {
      case AOP_PLUS: op = '+'; break;
      case AOP_MINUS: op = '-'; break;
      case AOP_TIMES: op = '*'; break;
      case AOP_DIVIDE: op = '/'; break;
      case AOP_UMINUS: op = '-'; break;
      case AOP_EXPONENT: op = '^'; break;
      default: op = '?'; break;
    }

    if (e->arith.op == AOP_UMINUS) {
      snprintf(buffer, sizeof(buffer), "%s = -%s", temp, left.temp);
      res.code = left.code;
    } else {
      right = generate_expr_tac(e->arith.right);
      snprintf(buffer, sizeof(buffer), "%s = %s %c %s", temp, left.temp, op, right.temp);
      res.code = tac_append(left.code, right.code);
    }

    TAC* instr = tac_create(buffer);
    res.temp = temp;
    res.code = tac_append(res.code, instr);
    return res;
  }

  if (e->type == EXPR_LOGIC) {
    ExprResult left = generate_expr_tac(e->logic.left);
    ExprResult right;
    char* temp = new_temp();
    const char* op;
    char buffer[128];

    switch (e->logic.op) {
      case OP_GT: op = ">"; break;
      case OP_GTE: op = ">="; break;
      case OP_LT: op = "<"; break;
      case OP_LTE: op = "<="; break;
      case OP_EQUALS: op = "=="; break;
      case OP_DIFF: op = "!="; break;
      case OP_OR: op = "||"; break;
      case OP_AND: op = "&&"; break;
      case OP_NOT: op = "!"; break;
      default: op = "?"; break;
    }

    if (e->logic.op == OP_NOT) {
      snprintf(buffer, sizeof(buffer), "%s = !%s", temp, left.temp);
      res.code = left.code;
    } else {
      right = generate_expr_tac(e->logic.right);
      snprintf(buffer, sizeof(buffer), "%s = %s %s %s", temp, left.temp, op, right.temp);
      res.code = tac_append(left.code, right.code);
    }

    TAC* instr = tac_create(buffer);
    res.temp = temp;
    res.code = tac_append(res.code, instr);
    return res;
  }

  if (e->type == EXPR_LITERAL) {
    char* temp = new_temp();
    char buffer[64];

    switch (e->literal.type) {
      case TYPE_INT:
        snprintf(buffer, sizeof(buffer), "%s = %d", temp, e->literal.data.i);
        break;
      case TYPE_FLOAT:
        snprintf(buffer, sizeof(buffer), "%s = %.2f", temp, e->literal.data.f);
        break;
      case TYPE_BOOL:
        snprintf(buffer, sizeof(buffer), "%s = %d", temp, e->literal.data.b);
        break;
      case TYPE_CHAR:
        snprintf(buffer, sizeof(buffer), "%s = %c", temp, e->literal.data.c);
        break;
      case TYPE_STRING:
        snprintf(buffer, sizeof(buffer), "%s = %s", temp, e->literal.data.s);
        break;
    }

    res.temp = temp;
    res.code = tac_create(buffer);
    return res;
  }

  if (e->type == EXPR_VAR) {
    res.temp = strdup(e->var_name);
    res.code = NULL;
    return res;
  }

  return res;
}

TAC* generate_stmt_tac(Stmt* s) {
  if (s->type == STMT_ATTRIB) {
    verify_assign_types(s);

    ExprResult rhs = generate_expr_tac(s->assign.expr);
    TAC* code = rhs.code;
    char buffer[128];
    snprintf(buffer, sizeof(buffer), "%s = %s", s->assign.var_name, rhs.temp);
    code = tac_append(code, tac_create(buffer));
    return code;
  }

  if (s->type == STMT_WHILE) {
    char* label_start = new_label();
    char* label_end = new_label();

    TAC* code = tac_create("%s:", label_start);
    ExprResult cond = generate_expr_tac(s->while_stmt.cond);
    code = tac_append(code, cond.code);

    char buffer[128];
    snprintf(buffer, sizeof(buffer), "ifFalse %s goto %s", cond.temp, label_end);
    code = tac_append(code, tac_create(buffer));

    TAC* body_code = generate_stmt_list_tac(s->while_stmt.body);
    code = tac_append(code, body_code);

    snprintf(buffer, sizeof(buffer), "goto %s", label_start);
    code = tac_append(code, tac_create(buffer));

    snprintf(buffer, sizeof(buffer), "%s:", label_end);
    code = tac_append(code, tac_create(buffer));

    return code;
  }

  if (s->type == STMT_IF) {
    ExprResult cond = generate_expr_tac(s->if_stmt.cond);
    char* label_else = new_label();
    char* label_end = new_label();

    char buffer[128];
    TAC* code = cond.code;
    snprintf(buffer, sizeof(buffer), "ifFalse %s goto %s", cond.temp, label_else);
    code = tac_append(code, tac_create(buffer));

    TAC* then_code = generate_stmt_list_tac(s->if_stmt.then_block);
    code = tac_append(code, then_code);

    snprintf(buffer, sizeof(buffer), "goto %s", label_end);
    code = tac_append(code, tac_create(buffer));

    snprintf(buffer, sizeof(buffer), "%s:", label_else);
    code = tac_append(code, tac_create(buffer));

    if (s->if_stmt.else_block) {
      TAC* else_code = generate_stmt_list_tac(s->if_stmt.else_block);
      code = tac_append(code, else_code);
    }

    snprintf(buffer, sizeof(buffer), "%s:", label_end);
    code = tac_append(code, tac_create(buffer));

    return code;
  }

  if (s->type == STMT_WRITE) {
    ExprResult val;
    if (s->write.var_name) {
      Expr* e = (Expr*) malloc(sizeof(Expr));
      e->type = EXPR_VAR;
      e->var_name = strdup(s->write.var_name);
      val = generate_expr_tac(e);
    } else {
      val = generate_expr_tac(s->write.expr);
    }
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "print %s", val.temp);
    TAC* code = val.code;
    code = tac_append(code, tac_create(buffer));

    return code;
  }

  if (s->type == STMT_READ) {
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "read %s", s->read.var_name);

    TAC* code = tac_create(buffer);

    return code;
  }

  return NULL;
}

TAC* generate_stmt_list_tac(StmtList* list) {
  TAC* code = NULL;
  while (list) {
    TAC* stmt_code = generate_stmt_tac(list->stmt);
    code = tac_append(code, stmt_code);
    list = list->next;
  }
  return code;
}

TAC* tac_create(const char* fmt, ...) {
  TAC* tac = (TAC*)malloc(sizeof(TAC));
  char buffer[256];

  va_list args;
  va_start(args, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);

  tac->code = strdup(buffer);
  tac->next = NULL;
  return tac;
}

TAC* tac_append(TAC* list, TAC* new_code) {
  if (!list) return new_code;
  TAC* curr = list;
  while (curr->next) curr = curr->next;
  curr->next = new_code;
  return list;
}

void tac_print(TAC* code) {
  while (code) {
    printf("%s\n", code->code);
    code = code->next;
  }
}

void print_symbol(Symbol symb) {
  switch (symb.type) {
    case TYPE_INT:
      printf("%d\n", symb.data.i);
      break;
    case TYPE_FLOAT:
      printf("%.2f\n", symb.data.f);
      break;
    case TYPE_BOOL:
     printf("%s\n", symb.data.b == 1 ? "true" : "false");
      break;
    case TYPE_CHAR:
      printf("%c\n", symb.data.c);
      break;
    case TYPE_STRING:
      printf("%s\n", symb.data.s);
      break;
  }
}

void print_value(Value v) {
  switch (v.type) {
    case TYPE_INT:
      printf("%d\n", v.data.i);
      break;
    case TYPE_FLOAT:
      printf("%.2f\n", v.data.f);
      break;
    case TYPE_CHAR:
      printf("%c\n", v.data.c);
      break;
    case TYPE_STRING:
      printf("%s\n", v.data.s);
      break;
    case TYPE_BOOL:
      printf("%s\n", v.data.b == 1 ? "true" : "false");
      break;
    default:
      printf("Erro: tipo de valor desconhecido\n");
      break;
  }
}

char* new_temp() {
  char buffer[16];
  snprintf(buffer, sizeof(buffer), "t%d", temp_count++);
  return strdup(buffer);
}

char* new_label() {
    char buf[20];
    sprintf(buf, "L%d", label_count++);
    return strdup(buf);
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

void print_expr(Expr* e) {
  if (!e) {
    fprintf(stderr, "Expr: NULL\n");
    return;
  }

  fprintf(stderr, "Expr type: %d\n", e->type);

  switch (e->type) {
    case EXPR_LITERAL:
      fprintf(stderr, "  Literal type: %d\n", e->literal.type);
      switch (e->literal.type) {
        case TYPE_INT:
          fprintf(stderr, "  Literal int: %d\n", e->literal.data.i);
          break;
        case TYPE_FLOAT:
          fprintf(stderr, "  Literal float: %.2f\n", e->literal.data.f);
          break;
        case TYPE_BOOL:
          fprintf(stderr, "  Literal bool: %s\n", e->literal.data.b ? "true" : "false");
          break;
        case TYPE_CHAR:
          fprintf(stderr, "  Literal char: %c\n", e->literal.data.c);
          break;
        case TYPE_STRING:
          fprintf(stderr, "  Literal string: %s\n", e->literal.data.s);
          break;
      }
      break;

    case EXPR_VAR:
      fprintf(stderr, "  Variable name: %s\n", e->var_name);
      break;

    case EXPR_ARITH:
      fprintf(stderr, "  Arith op: %d\n", e->arith.op);
      fprintf(stderr, "  Left:\n");
      print_expr(e->arith.left);
      if (e->arith.right) {
        fprintf(stderr, "  Right:\n");
        print_expr(e->arith.right);
      }
      break;

    case EXPR_LOGIC:
      fprintf(stderr, "  Logic op: %d\n", e->logic.op);
      fprintf(stderr, "  Left:\n");
      print_expr(e->logic.left);
      if (e->logic.right) {
        fprintf(stderr, "  Right:\n");
        print_expr(e->logic.right);
      }
      break;

    default:
      fprintf(stderr, "  (Unknown expression type)\n");
      break;
  }
}
