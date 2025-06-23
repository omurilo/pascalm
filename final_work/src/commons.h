#ifndef COMMONS_H
#define COMMONS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "parser/types.h"

typedef struct ht ht;
typedef struct ASTNode ASTNode;
typedef struct SourceLocation SourceLocation;
typedef struct SymbolEntry SymbolEntry;

typedef struct CodeGenerator {
  FILE *output_file;
  int indent_level;
  SymbolEntry *current_function;
} CodeGenerator;

typedef enum ParameterKind {
  PARAM_VALUE,     // Parâmetro por valor
  PARAM_VAR,       // Parâmetro por referência (var)
  PARAM_PROCEDURE, // Parâmetro procedural
  PARAM_FUNCTION   // Parâmetro funcional
} ParameterKind;

typedef enum ConstantType {
  CONST_INTEGER,
  CONST_REAL,
  CONST_STRING,
  CONST_CHAR,
  CONST_BOOLEAN,
  CONST_IDENTIFIER,
  CONST_SIGNED_IDENTIFIER
} ConstantType;

typedef struct ConstantValue {
  ConstantType type;
  union {
    int int_val;
    double real_val;
    char *str_val;
    int bool_val;
    char char_val;
  } value;
  bool is_valid;
} ConstantValue;

typedef enum NodeType {
  /* Estrutura do programa */
  NODE_PROGRAM,
  NODE_HEADING,
  NODE_BLOCK,
  NODE_USES,

  /* Declarações */
  NODE_LABEL_DECL,
  NODE_CONST_DECL,
  NODE_TYPE_DECL,
  NODE_VAR_DECL,
  NODE_PROC_DECL,
  NODE_FUNC_DECL,
  NODE_FORWARD_DECL,

  /* Tipos */
  NODE_ENUMERATED_TYPE,
  NODE_SUBRANGE_TYPE,
  NODE_STRUCTURED_TYPE,
  NODE_SIMPLE_TYPE,
  NODE_ARRAY_TYPE,
  NODE_RECORD_TYPE,
  NODE_SET_TYPE,
  NODE_FILE_TYPE,
  NODE_POINTER_TYPE,
  NODE_POINTER_DEREF,

  /* Comandos */
  NODE_COMPOUND_STMT,
  NODE_ASSIGN_STMT,
  NODE_PROC_CALL,
  NODE_IF_STMT,
  NODE_CASE_STMT,
  NODE_CASE_ITEM,
  NODE_CASE_LABEL,
  NODE_CASE_ELSE,
  NODE_WHILE_STMT,
  NODE_REPEAT_STMT,
  NODE_FOR_STMT,
  NODE_WITH_STMT,
  NODE_GOTO_STMT,
  NODE_LABELED_STMT,

  /* Expressões */
  NODE_BINARY_EXPR,
  NODE_UNARY_EXPR,
  NODE_LITERAL,
  NODE_IDENTIFIER,
  NODE_MEMBER_ACCESS,
  NODE_ARRAY_ACCESS,
  NODE_FUNC_CALL,
  NODE_SET_CONSTRUCTOR,
  NODE_CONSTANT,
  NODE_TYPE_IDENTIFIER,

  /* Auxiliares */

  NODE_FIELD_LIST,
  NODE_RECORD_FIELD,
  NODE_INDEX_LIST,
  NODE_PARAMETER,
  NODE_VARIANT_RECORD,
  NODE_VARIANT_LIST,
  NODE_VARIANT_PART,
  NODE_TAG_FIELD,
  NODE_FIXED_PART,
  NODE_FORMAL_PARAM_SECTION,
  NODE_LIST,
  NODE_ERROR,
  NODE_OPERATION,
  NODE_SET_ELEMENT
} NodeType;

typedef enum SymbolKind {
  SYMBOL_UNKNOWN, // Ainda não resolvido

  // Tipos de identificadores primários
  SYMBOL_VARIABLE,  // Variável
  SYMBOL_CONSTANT,  // Constante
  SYMBOL_PARAMETER, // Parâmetro de função/procedimento
  SYMBOL_FUNCTION,  // Função
  SYMBOL_PROCEDURE, // Procedimento
  SYMBOL_TYPE,      // Tipo definido pelo usuário
  SYMBOL_TYPE_ALIAS, // 

  // Tipos específicos de variáveis
  SYMBOL_FIELD,      // Campo de um record
  SYMBOL_LOCAL_VAR,  // Variável local
  SYMBOL_GLOBAL_VAR, // Variável global

  // Tipos específicos de parâmetros
  SYMBOL_VALUE_PARAM, // Parâmetro por valor
  SYMBOL_VAR_PARAM,   // Parâmetro por referência (var)

  // Tipos específicos para tipos
  SYMBOL_ENUM_VALUE, // Valor de enumeração
  SYMBOL_LABEL,      // Rótulo (label)

  // Para escopos internos
  SYMBOL_PROGRAM, // Nome do programa
  SYMBOL_UNIT,    // Nome da unit (para Pascal modular)

  // Tipos especiais
  SYMBOL_FORWARD_DECL, // Declaração forward de função/procedimento
  SYMBOL_BUILTIN,       // Funções/procedimentos/tipos built-in
  SYMBOL_BUILTIN_FUNCTION
} SymbolKind;

typedef enum BinaryOperator {
  // Relacionais
  BINOP_LT,  // <
  BINOP_LTE, // <=
  BINOP_EQ,  // =
  BINOP_NEQ, // <>
  BINOP_GTE, // >=
  BINOP_GT,  // >

  // Aditivos
  BINOP_PLUS,  // +
  BINOP_MINUS, // -
  BINOP_OR,    // or

  // Multiplicativos
  BINOP_TIMES,  // *
  BINOP_DIVIDE, // /
  BINOP_DIV,    // div
  BINOP_MOD,    // mod
  BINOP_AND,    // and
  BINOP_IN      // in
} BinaryOperator;

// Operadores unários
typedef enum UnaryOperator {
  UNOP_PLUS,  // +
  UNOP_MINUS, // -
  UNOP_NOT    // not
} UnaryOperator;

struct SourceLocation {
  int first_line;
  int first_column;
  int last_line;
  int last_column;
  char *file_name;
};

struct ASTNode {
  NodeType type;
  SourceLocation location;
  void (*print)(struct ASTNode *, int);
  ASTNode* result_type;
  // Função para imprimir o nó (para debug)
  /*
  int data_type; // tipo dos dados (INTEGER, REAL, STRING, etc.)
  int scope_level; // Nível de escopo para análise de visibilidade
  void *symbol_entry; // ponteiro para entrada na tabela de símbolos
  void *pass_info;  // Informações específicas para diferentes passes
  */
};

typedef enum {
    LITERAL_INTEGER,
    LITERAL_REAL,
    LITERAL_BOOLEAN,
    LITERAL_STRING,
    LITERAL_CHAR,
    LITERAL_NIL
} LiteralType;

typedef struct {
  int lower;
  int upper;
} DimensionBounds;

struct SymbolEntry {
  char *name;
  SymbolKind kind;
  const char *key;
  LiteralType tag;

  union {
    struct {
      ASTNode *type;
      int offset;
      bool is_ref;
      DimensionBounds *dimensions;
      int num_dimensions;
    } var_info;

    struct {
      ASTNode *return_type;
      ASTNode *params;
      ASTNode *body;
      bool is_forward;
    } func_info;

    struct {
      ASTNode *definition;
      size_t size;
      ht* fields;
      SymbolEntry *aliased_type;
    } type_info;

    struct {
      ASTNode* definition;
      ASTNode* value;
    } const_info;
  } info;

  int scope_level;
  SourceLocation location;
  SymbolEntry *next;
};

#endif
