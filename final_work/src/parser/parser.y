%require "3.8.2"

%{
#include <stdlib.h>
#include <string.h>
#include "../commons.h"
#include "../ast/ast.h"
#include "../symbol-table/symbol-table.h"

ASTNode *root = NULL;
extern ht *HashTable;
%}

%define api.location.type {YYLTYPE}
%define parse.assert
%define parse.error verbose
%locations

%union {
  int integer;
  bool boolean;
  char character;
  double number;
  char* string;

  ASTNode* node;

  LiteralNode *lnode;
  ListNode *ltnode;
}

/* Keywords */
%token PROGRAM VAR CONST TYPE LABEL PROCEDURE FUNCTION BEGIN_TOK END IF THEN ELSE NIL WITH FORWARD PACKED
%token WHILE DO FOR TO DOWNTO REPEAT UNTIL CASE OF GOTO
%token INTEGER REAL BOOLEAN CHAR ARRAY RECORD SET FILE_TOK STRING
%token READ WRITE READLN WRITELN

/* Symbols */
%token GT GTE LT LTE NEQ EQ
%token AND OR NOT
%token PLUS MINUS TIMES DIVIDE DIV MOD
%token DOT DOTDOT CARET
%token ASSIGN SEMICOLON COMMA COLON L_PAREN R_PAREN L_BRACE R_BRACE L_BRACKET R_BRACKET

/* Literals */
%token <character> CHAR_LITERAL
%token <integer> INTEGER_LITERAL
%token <number> REAL_LITERAL
%token <boolean> BOOLEAN_LITERAL
%token <string> IDENTIFIER STRING_LITERAL

%type <node> char_literal
%type <node> integer_literal
%type <node> real_literal
%type <node> boolean_literal
%type <node> string_literal


%type <node> pascal_program
%type <node> program_headingopt
%type <node> identifier_list
%type <node> block block1 block2 block3 block4 block5

%type <node> label_declaration
%type <node> constant_declaration
%type <node> type_declaration
%type <node> variable_declaration
%type <node> variableid_list
%type <node> constant
%type <node> proc_and_func_declaration
%type <node> proc_or_func
%type <node> block_or_forward
%type <node> parameters
%type <node> formal_parameter_list
%type <node> formal_parameter_section
%type <node> parameterid_list

%type <node> type
%type <node> simple_type
%type <node> structured_type unpacked_structured_type
%type <node> index_list
%type <node> field_list
%type <node> fixed_part
%type <node> record_field
%type <node> fieldid_list
%type <node> variant_part
%type <node> tag_field
%type <node> variant_list
%type <node> variant
%type <node> case_label_list
%type <node> case_label

%type <node> statement_list
%type <node> statement
%type <node> variable
%type <node> subscript_list
%type <node> case_list
%type <node> case_item
%type <node> case_else
%type <node> for_list
%type <node> expression_list
%type <node> label
%type <node> record_variable_list
%type <node> expression
%type <node> additive_expression
%type <node> multiplicative_expression
%type <node> unary_expression
%type <node> primary_expression
%type <node> element_list element_list_non_empty
%type <node> element

%type <node> constid
%type <node> typeid
%type <node> funcid
%type <node> procid
%type <node> fieldid
%type <node> varid
%type <node> identifier
%type <node> unsigned_integer
%type <node> unsigned_real
%type <node> empty

%left PLUS MINUS
%left TIMES DIVIDE DIV MOD SQRT
%left AND OR
%precedence NEG

%nonassoc GT GTE LT LTE NEQ EQ IN
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%start pascal_program

%%

pascal_program: 
   PROGRAM IDENTIFIER program_headingopt SEMICOLON block DOT {
      $$ = create_program_node($2, $3, $5, create_location(@$));
      root = $$;
   }

program_headingopt:
    L_PAREN identifier_list R_PAREN {
      $$ = create_heading_node($2, create_location(@$));
    }
  | empty 

identifier_list: 
    identifier {
      $$ = create_identifier_list_node($1, create_location(@$));
    }  
  | identifier_list COMMA identifier {
      $$ = append_identifier_list_node($1, $3, create_location(@$));
    }

block:  
    block1 { $$ = $1; } 
  | label_declaration SEMICOLON block1 {
      $$ = add_labels_to_block($3, $1);
    }

block1:  
    block2  { $$ = $1; }
  | constant_declaration SEMICOLON block2 {
    $$ = add_constants_to_block($3, $1);
  }

block2:  
    block3 { $$ = $1; }
  | type_declaration SEMICOLON block3 {
     $$ = add_types_to_block($3, $1);
  }

block3:  
    block4 { $$ = $1; }
  | variable_declaration SEMICOLON block4 {
      $$ = add_variables_to_block($3, $1);
    }

block4:  
    block5 { $$ = $1; }
  | proc_and_func_declaration SEMICOLON block5 {
      $$ = add_procs_funcs_to_block($3, $1);
    }

block5:  
    BEGIN_TOK statement_list END {
      $$ = create_block_node(NULL, NULL, NULL, NULL, NULL, $2, create_location(@$));
    }

label_declaration:  
    LABEL unsigned_integer { $$ = create_label_declaration_node($2, create_location(@$)); }
  | label_declaration COMMA unsigned_integer {
      $$ = append_label_declaration($1, $3, create_location(@$));
    }  

constant_declaration:  
    CONST constid EQ constant {
      $$ = create_constant_declaration_node($2, $4, create_location(@$));
    }
  | constant_declaration SEMICOLON  identifier EQ constant {
      $$ = append_constant_declaration($1, $3, $5, create_location(@$));
    }  

type_declaration:  
    TYPE typeid EQ type { $$ = create_type_declaration_node($2, $4, create_location(@$)); }
  | type_declaration SEMICOLON typeid EQ type {
      $$ = append_type_declaration($1, $3, $5, create_location(@$));
    } 

variable_declaration:  
    VAR variableid_list COLON type { $$ = create_variable_declaration_node($2, $4, create_location(@$)); }
  | variable_declaration SEMICOLON variableid_list COLON type {
      $$ = append_variable_declaration($1, $3, $5, create_location(@$));
    }

variableid_list:  
    identifier  { $$ = create_variable_identifier_list_node($1, create_location(@$)); }
  | variableid_list COMMA identifier {
      $$ = append_variable_identifier_list($1, $3, create_location(@$));
    }

constant:  
    integer_literal {
      $$ = create_constant_literal($1, create_location(@$));
    }
  | real_literal {
      $$ = create_constant_literal($1, create_location(@$));
    }
  | string_literal {
      $$ = create_constant_literal($1, create_location(@$));
    }
  | constid { $$ = create_constant_identifier($1, create_location(@$)); }
  | PLUS constid { $$ = create_constant_signed_identifier($2, "+", create_location(@$)); }
  | MINUS constid { $$ = create_constant_signed_identifier($2, "-", create_location(@$)); }

type:  
    simple_type {
      $$ = create_simple_type_node($1, create_location(@$));
    }
  | structured_type {
      $$ = create_structure_type_node($1, create_location(@$));
    }
  | CARET typeid {
      $$ = create_pointer_type_node($2, create_location(@$));
    }  // pointer type

simple_type:  
    L_PAREN  identifier_list R_PAREN { $$ = create_enumerated_type_node($2, create_location(@$)); }
  | constant DOTDOT constant {
      $$ = create_constant_range_node($1, $3, create_location(@$));
    }
  | typeid {
      $$ = $1;
    }

structured_type:
    unpacked_structured_type {
      $$ = $1;
    }
    | PACKED unpacked_structured_type {
      $$ = create_packed_type($2, create_location(@$));
    }

unpacked_structured_type:
      ARRAY L_BRACKET index_list R_BRACKET OF type {
        $$ = create_array_type_node($3, $6, create_location(@$));
      }
    | RECORD field_list END {
        $$ = create_record_type_node($2, create_location(@$));
      }
    | SET OF simple_type {
        $$ = create_set_of_type_node($3, create_location(@$));
      }
    | FILE_TOK {
        $$ = create_file_of_type_node(NULL, create_location(@$));
      }
    | FILE_TOK OF type {
        $$ = create_file_of_type_node($3, create_location(@$));
      }

index_list:
    simple_type { 
      $$ = create_index_list_start($1, create_location(@$)); 
    }
  | index_list COMMA simple_type {
      $$ = append_index_to_list($1, $3, create_location(@$));
    }

field_list:  
    fixed_part { $$ = create_field_list($1, NULL, create_location(@$)); }  
  | fixed_part SEMICOLON variant_part { $$ = create_field_list($1, $3, create_location(@$)); }
  | variant_part { $$ = create_field_list(NULL, $1, create_location(@$)); } 

fixed_part:  
    record_field { $$ = create_fixed_part_node(NULL, $1, create_location(@$)); }
  | fixed_part SEMICOLON record_field { $$ = create_fixed_part_node($1, $3, create_location(@$)); }

record_field: 
    empty 
  | fieldid_list COLON type { $$ = create_record_field_node($1, $3, create_location(@$)); }

fieldid_list:  
    fieldid { $$ = create_field_identifier_list_node(NULL, $1, create_location(@$)); }
  | fieldid_list COMMA fieldid { $$ = create_field_identifier_list_node($1, $3, create_location(@$)); }  

variant_part: 
    CASE tag_field OF variant_list { $$ = create_case_of_variant_node($2, $4, create_location(@$)); }

tag_field: 
    typeid { $$ = create_tag_field_node(NULL, $1, create_location(@$)); }
  | identifier COLON typeid { $$ = create_tag_field_node($1, $3, create_location(@$)); }

variant_list:  
    variant { $$ = append_variant_list(NULL, $1, create_location(@$)); }
  | variant_list SEMICOLON variant {
      $$ = append_variant_list($1, $3, create_location(@$));
    } 

variant: 
    empty 
  | case_label_list COLON L_PAREN field_list R_PAREN {
      $$ = create_variant_node($1, $4, create_location(@$));
    }

proc_and_func_declaration:  
    proc_or_func { $$ = create_proc_and_func_declarations_node($1, create_location(@$)); }
  | proc_and_func_declaration SEMICOLON proc_or_func {
      $$ = append_proc_and_func_declarations($1, $3, create_location(@$));
    }

proc_or_func:  
    PROCEDURE procid parameters SEMICOLON block_or_forward { /* identifier of func/proc declaration */ 
      $$ = create_proc_declaration_node($2, $3, $5, create_location(@$));
    }
  | FUNCTION funcid parameters COLON typeid SEMICOLON block_or_forward {
      $$ = create_func_declaration_node($2, $3, $5, $7, create_location(@$));
    }

block_or_forward:  
    block { $$ = $1; }
  | FORWARD  { $$ = create_forward_declaration_node(create_location(@$)); }

parameters:  
   L_PAREN formal_parameter_list R_PAREN { $$ = create_parameters_node($2, create_location(@$)); }

formal_parameter_list:  
    formal_parameter_section { $$ = create_formal_parameters_list_node(NULL, $1, create_location(@$)); }
  | formal_parameter_list SEMICOLON formal_parameter_section {
      $$ = create_formal_parameters_list_node($1, $3, create_location(@$));
    }

formal_parameter_section:
    parameterid_list COLON typeid { 
        $$ = create_formal_parameter_section_node(PARAM_VALUE, $1, $3, NULL, NULL, create_location(@$)); 
      }
    | VAR parameterid_list COLON typeid { 
        $$ = create_formal_parameter_section_node(PARAM_VAR, $2, $4, NULL, NULL, create_location(@$)); 
      }
    | PROCEDURE identifier parameters { 
        ASTNode* single_id = create_parameter_identifier_list_node(NULL, $2, create_location(@2));
        $$ = create_formal_parameter_section_node(PARAM_PROCEDURE, single_id, NULL, $3, NULL, create_location(@$)); 
      }
    | FUNCTION identifier parameters COLON typeid { 
        ASTNode* single_id = create_parameter_identifier_list_node(NULL, $2, create_location(@2));
        $$ = create_formal_parameter_section_node(PARAM_FUNCTION, single_id, NULL, $3, $5, create_location(@$)); 
      }

parameterid_list:  
    identifier  { $$ = create_parameter_identifier_list_node(NULL, $1, create_location(@$)); }
  | parameterid_list COMMA identifier  { 
      $$ = create_parameter_identifier_list_node($1, $3, create_location(@$));
    }

statement_list:  
    statement { $$ = create_stmt_list_node($1, create_location(@$)); }
  | statement_list SEMICOLON statement { $$ = append_stmt_list($1, $3, create_location(@$)); }  

statement:  
    empty  
  | variable ASSIGN expression { $$ = create_assign_node($1, $3, create_location(@$)); }
  | BEGIN_TOK statement_list END  { $$ = create_stmt_list_node($2, create_location(@$)); }
  | IF expression THEN statement %prec LOWER_THAN_ELSE { $$ = create_if_stmt_node($2, $4, NULL, create_location(@$)); }
  | IF expression THEN statement ELSE statement { $$ = create_if_stmt_node($2, $4, $6, create_location(@$)); }
  | CASE expression OF case_list END { $$ = create_case_stmt_node($2, $4, NULL, create_location(@$)); }
  | CASE expression OF case_list SEMICOLON case_else END { $$ = create_case_stmt_with_else_node($2, $4, $6, create_location(@$)); }
  | WHILE expression DO statement { $$ = create_while_stmt_node($2, $4, create_location(@$)); }
  | REPEAT statement_list UNTIL expression { $$ = create_repeat_until_stmt_list_node($2, $4, create_location(@$)); }
  | FOR varid ASSIGN for_list DO statement { $$ = create_for_stmt_node($2, $4, $6, create_location(@$)); }
  | procid { $$ = $1; }
  | procid L_PAREN expression_list R_PAREN { $$ = create_procedure_call_node($1, $3, create_location(@$)); } 
  | GOTO label { $$ = create_goto_label_node($2, create_location(@$)); }
  | WITH record_variable_list DO statement { $$ = create_with_record_list_node($2, $4, create_location(@$)); }
  | label COLON statement { $$ = create_label_stmt_node($1, $3, create_location(@$)); }

variable:  
    varid { $$ = $1; }
  | variable L_BRACKET subscript_list R_BRACKET { $$ = create_array_access_node($1, $3, create_location(@$)); }  
  | variable DOT fieldid { $$ = create_record_access_node($1, $3, create_location(@$)); }
  | variable CARET { $$ = create_pointer_deref_node($1, create_location(@$)); } 

subscript_list:
    expression { 
        $$ = create_subscript_list_node($1, create_location(@$)); 
    }
  | subscript_list COMMA expression { 
        $$ = append_subscript_list_node($1, $3, create_location(@$)); 
    }

case_list:
    case_item { $$ = $1; }
  | case_list SEMICOLON case_item { 
      $$ = append_case_item($1, $3, create_location(@$)); 
    }

case_item:
    case_label_list COLON statement { 
      $$ = create_case_item_node($1, $3, create_location(@$)); 
    }

case_label_list:
    case_label { $$ = create_case_label_list($1, create_location(@$)); }
  | case_label_list COMMA case_label { 
      $$ = append_case_label_list($1, $3, create_location(@$)); 
    }

case_label:
    constant { $$ = $1; }
  | constant DOTDOT constant { 
      $$ = create_constant_range_node($1, $3, create_location(@$)); 
    }

case_else:
    ELSE statement SEMICOLON {
      $$ = create_case_else_node($2, create_location(@$));
    }

for_list:
    expression TO expression { 
      $$ = create_for_list_node($1, $3, false, create_location(@$)); 
    }
  | expression DOWNTO expression { 
      $$ = create_for_list_node($1, $3, true, create_location(@$)); 
    }  


expression_list:  
    expression { $$ = create_expression_list($1, create_location(@$)); }
  | expression_list COMMA expression { $$ = append_expression_list($1, $3, create_location(@$)); }

label:  
   unsigned_integer { $$ = $1; }

record_variable_list:
    variable { $$ = create_record_variable_list_node($1, create_location(@$)); }
  | record_variable_list COMMA variable { 
      $$ = append_record_variable_list($1, $3, create_location(@$)); 
    } 

expression: 
    expression LT additive_expression { 
      $$ = create_binary_expression($1, BINOP_LT, $3, create_location(@$)); 
    }
  | expression LTE additive_expression { 
      $$ = create_binary_expression($1, BINOP_LTE, $3, create_location(@$)); 
    }
  | expression EQ additive_expression { 
      $$ = create_binary_expression($1, BINOP_EQ, $3, create_location(@$)); 
    }
  | expression NEQ additive_expression { 
      $$ = create_binary_expression($1, BINOP_NEQ, $3, create_location(@$)); 
    }
  | expression GTE additive_expression { 
      $$ = create_binary_expression($1, BINOP_GTE, $3, create_location(@$)); 
    }
  | expression GT additive_expression { 
      $$ = create_binary_expression($1, BINOP_GT, $3, create_location(@$)); 
    }
  | additive_expression { $$ = $1; }

additive_expression: 
    additive_expression PLUS multiplicative_expression { 
      $$ = create_binary_expression($1, BINOP_PLUS, $3, create_location(@$)); 
    }
  | additive_expression MINUS multiplicative_expression { 
      $$ = create_binary_expression($1, BINOP_MINUS, $3, create_location(@$)); 
    }
  | additive_expression OR multiplicative_expression { 
      $$ = create_binary_expression($1, BINOP_OR, $3, create_location(@$)); 
    }
  | multiplicative_expression { $$ = $1; }

multiplicative_expression: 
    multiplicative_expression TIMES unary_expression { 
      $$ = create_binary_expression($1, BINOP_TIMES, $3, create_location(@$)); 
    }
  | multiplicative_expression DIVIDE unary_expression { 
      $$ = create_binary_expression($1, BINOP_DIVIDE, $3, create_location(@$)); 
    }
  | multiplicative_expression DIV unary_expression { 
      $$ = create_binary_expression($1, BINOP_DIV, $3, create_location(@$)); 
    }
  | multiplicative_expression MOD unary_expression { 
      $$ = create_binary_expression($1, BINOP_MOD, $3, create_location(@$)); 
    }
  | multiplicative_expression AND unary_expression { 
      $$ = create_binary_expression($1, BINOP_AND, $3, create_location(@$)); 
    }
  | multiplicative_expression IN unary_expression { 
      $$ = create_binary_expression($1, BINOP_IN, $3, create_location(@$)); 
    }
  | unary_expression { $$ = $1; }

unary_expression: 
    PLUS unary_expression { 
      $$ = create_unary_expression(UNOP_PLUS, $2, create_location(@$)); 
    }
  | MINUS unary_expression %prec NEG { 
      $$ = create_unary_expression(UNOP_MINUS, $2, create_location(@$)); 
    }
  | NOT unary_expression %prec NEG { 
      $$ = create_unary_expression(UNOP_NOT, $2, create_location(@$)); 
    }
  | primary_expression { $$ = $1; }

primary_expression:  
    variable { $$ = $1; }
  | unsigned_integer { $$ = $1; }
  | unsigned_real { $$ = $1; }
  | string_literal { $$ = $1; }
  | NIL {
      $$ = create_nil_literal(create_location(@$));
    }
  | funcid L_PAREN expression_list R_PAREN {
      $$ = create_function_call_node($1, $3, create_location(@$));
    }
  | L_BRACKET element_list R_BRACKET { $$ = $2; }
  | L_PAREN expression R_PAREN { $$ = $2; } 

element_list:
    empty { 
      $$ = create_set_literal(create_location(@$)); 
    }
  | element_list_non_empty { 
      $$ = $1; 
    }

element_list_non_empty:
    element { 
      $$ = create_set_literal_with_element($1, create_location(@$)); 
    }
  | element_list_non_empty COMMA element {
      $$ = add_element_to_set_literal($1, $3, create_location(@$));
    }

element:
    expression { 
      $$ = create_set_element($1, create_location(@$)); 
    }
  | expression DOTDOT expression {
      $$ = create_set_range_element($1, $3, create_location(@$));
    }

constid:  
   identifier  {
      $$ = update_identifier_node_kind($1, SYMBOL_CONSTANT, true);
   }

typeid:
    CHAR { $$ = create_builtin_type_identifier("char", create_location(@$)); }
  | BOOLEAN { $$ = create_builtin_type_identifier("boolean", create_location(@$)); }
  | INTEGER { $$ = create_builtin_type_identifier("integer", create_location(@$)); }
  | REAL { $$ = create_builtin_type_identifier("real", create_location(@$)); }
  | STRING { $$ = create_builtin_type_identifier("string", create_location(@$)); }
  | identifier {
      ASTNode *typeId = update_identifier_node_kind($1, SYMBOL_TYPE, true);
      $$ = create_type_identifier(typeId, create_location(@$));
    }

funcid: 
  identifier  { 
    $$ = update_identifier_node_kind($1, SYMBOL_FUNCTION, true);
  }

procid:  
  identifier { 
    $$ = update_identifier_node_kind($1, SYMBOL_PROCEDURE, true);
  }
  | WRITE { $$ = create_builtin_identifier("write", create_location(@$)); }
  | WRITELN { $$ = create_builtin_identifier("writeln", create_location(@$)); }
  | READ { $$ = create_builtin_identifier("read", create_location(@$)); }
  | READLN { $$ = create_builtin_identifier("readln", create_location(@$)); }

fieldid:  
  identifier { 
    $$ = update_identifier_node_kind($1, SYMBOL_FIELD, true);
  }

varid: 
  identifier {
    $$ = update_identifier_node_kind($1, SYMBOL_VARIABLE, true);
  }

identifier:
   IDENTIFIER { $$ = create_identifier_node($1, create_location(@$)); }

unsigned_integer:
    INTEGER_LITERAL {
      $$ = create_unsigned_integer_node($1, create_location(@$));
    }

unsigned_real:
    REAL_LITERAL {
      $$ = create_unsigned_real_node($1, create_location(@$));
    }

integer_literal:
    INTEGER_LITERAL {
      $$ = create_integer_literal($1, create_location(@$));
    }

real_literal:
    REAL_LITERAL {
      $$ = create_real_literal($1, create_location(@$));
    }

string_literal:
    STRING_LITERAL {
      $$ = create_string_literal($1, create_location(@$));
    }

char_literal:
    CHAR_LITERAL {
      $$ = create_char_literal($1, create_location(@$));
    }

boolean_literal:
    BOOLEAN_LITERAL {
      $$ = create_boolean_literal($1, create_location(@$));
    }

empty: { $$ = NULL; }

