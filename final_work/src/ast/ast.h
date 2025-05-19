#ifndef AST_H
#define AST_H

#include "../parser/types.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct ProgramNode ProgramNode; // Raiz da AST, contendo o nome do
                                        // programa e seu bloco principal
typedef struct HeadingNode HeadingNode; // Lista de identificadores de cabeçalho
typedef struct BlockNode BlockNode;     // Contém declarações e o corpo do pr
                                        // grama/procedimento/função
typedef struct UsesNode UsesNode;       // Lista de módulos importados
typedef struct ConstDeclarationNode
    ConstDeclarationNode; // Declaração de constantes
typedef struct TypeDeclarationNode TypeDeclarationNode; // Declaração de tipos
typedef struct VarDeclarationNode VarDeclarationNode; // Declaração de variáveis
typedef struct ProcDeclarationNode
    ProcDeclarationNode; // Declaração de procedimentos
typedef struct FuncDeclarationNode FuncDeclarationNode; // Declaração de funções

typedef struct SimpleTypeNode SimpleTypeNode;      // Tipos simples
/**/ typedef struct ScalarTypeNode ScalarTypeNode; // Tipo escalar (enumerado)
/**/ typedef struct SubrangeTypeNode SubrangeTypeNode; // Tipo de subintervalo
/**/ typedef struct TypeIdentifierNode
    TypeIdentifierNode; // Referência a um tipo identificador
typedef struct StructuredTypeNode StructuredTypeNode; // Tipos estruturados
/**/ typedef struct ArrayTypeNode ArrayTypeNode;      // Tipo array
/**/ typedef struct RecordTypeNode RecordTypeNode;    // Tipo record
/**/ typedef struct SetTypeNode SetTypeNode;          // Tipo set
/**/ typedef struct FileTypeNode FileTypeNode;        // Tipo file
typedef struct PointerTypeNode PointerTypeNode;       // Tipo ponteiro
typedef struct PointerDerefNode PointerDerefNode;

typedef struct CompoundStatementNode
    CompoundStatementNode;                    // Bloco de comandos (begin...end)
typedef struct AssignmentNode AssignmentNode; // Atribuição (:=)
typedef struct ProcedureCallNode ProcedureCallNode; // Chamada de procedimento
typedef struct IfNode IfNode; // Estrutura condicional if-then-else

typedef struct CaseNode CaseNode;           // Estrutura de seleção case
typedef struct CaseLabelNode CaseLabelNode; // Cada label dentro de um case
typedef struct CaseElseNode CaseElseNode;   // Cláusula else do case (extensão)

typedef struct WhileNode WhileNode;   // Laço while
typedef struct RepeatNode RepeatNode; // Laço repeat until
typedef struct ForNode ForNode;       // Laço for
typedef struct WithNode WithNode;     // Estrutura with
typedef struct GotoNode GotoNode;     // Comando goto

typedef struct BinaryOperationNode
    BinaryOperationNode; // Operações binárias (+, -, *, /, div, mod, and, or, et
                         // 
                         //
                         //
                         // .)
typedef struct UnaryOperationNode
    UnaryOperationNode;                 // Operações unárias (-, not, etc.)
typedef struct LiteralNode LiteralNode; // Valores literais
typedef struct IdentifierNode IdentifierNode; // Referência a uma variável
typedef struct MemberAccessNode
    MemberAccessNode; // Acesso a campos (record.field)
typedef struct ArrayAccessNode ArrayAccessNode;   // Acesso a elementos de array
typedef struct FunctionCallNode FunctionCallNode; // Chamada de função
typedef struct SetConstructorNode SetConstructorNode; // Construtor de conjunto

typedef struct LabelDeclarationNode
    LabelDeclarationNode;                   // Declaração de labels
typedef struct FieldListNode FieldListNode; // Lista de campos em um record
typedef struct ParameterNode ParameterNode; // Parâmetro de procedimento/função
typedef struct VariantRecordNode VariantRecordNode; // Record com parte variante

typedef struct ListNode
    ListNode; // Nó genérico para listas (pode ser especializado)
typedef struct ErrorNode ErrorNode; // Nó para representar erros sintáticos

typedef struct ASTNode ASTNode;
typedef struct SourceLocation SourceLocation;

typedef enum {
  /* Estrutura do programa */
  NODE_PROGRAM,
  NODE_BLOCK,
  NODE_USES,

  /* Declarações */
  NODE_LABEL_DECL,
  NODE_CONST_DECL,
  NODE_TYPE_DECL,
  NODE_VAR_DECL,
  NODE_PROC_DECL,
  NODE_FUNC_DECL,

  /* Tipos */
  NODE_CONST_ITEM,
  NODE_SCALAR_TYPE,
  NODE_SUBRANGE_TYPE,
  NODE_TYPE_IDENTIFIER,
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
  NODE_CASE_ELEMENT,
  NODE_CASE_ELSE,
  NODE_WHILE_STMT,
  NODE_REPEAT_STMT,
  NODE_FOR_STMT,
  NODE_WITH_STMT,
  NODE_GOTO_STMT,

  /* Expressões */
  NODE_BINARY_EXPR,
  NODE_UNARY_EXPR,
  NODE_INTEGER_LITERAL,
  NODE_REAL_LITERAL,
  NODE_STRING_LITERAL,
  NODE_BOOLEAN_LITERAL,
  NODE_CHAR_LITERAL,
  NODE_NIL_LITERAL,
  NODE_IDENTIFIER,
  NODE_MEMBER_ACCESS,
  NODE_ARRAY_ACCESS,
  NODE_FUNC_CALL,
  NODE_SET_CONSTRUCTOR,

  /* Auxiliares */
  NODE_LIST,
  NODE_ERROR
} NodeType;

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
  void (*print)(struct ASTNode *,
                int); // Função para imprimir o nó (para debug)
};

struct ProgramNode {
  ASTNode base;
  char *name;
  ASTNode *block;
  ASTNode *heading;
};

struct HeadingNode {
  ASTNode base;
  ASTNode *list;
};

struct BlockNode {
  ASTNode base;
  ASTNode *labels;
  ASTNode *types;
  ASTNode *constants;
  ASTNode *variables;
  ASTNode *procs_funcs;
  ASTNode *statements;
};

struct LabelDeclarationNode {
  ASTNode base;
  ASTNode *labels; // ListNode
};

struct ConstDeclarationNode {
  ASTNode base;
  ASTNode *constants; // ListNode
};

struct TypeDeclarationNode {
  ASTNode base;
  ASTNode *types;
};

struct VarDeclarationNode {
  ASTNode base;
  ASTNode *vars;
};

struct ProcDeclarationNode {
  ASTNode base;
  ASTNode *procs;
};

struct FuncDeclarationNode {
  ASTNode base;
  ASTNode *funcs;
};

struct MemberAccessNode {
  ASTNode base;
  ASTNode *record;
  ASTNode *field;
};

struct ArrayAccessNode {
  ASTNode base;
  ASTNode *array;
  ASTNode *subscript_list;
};

struct PointerDerefNode {
  ASTNode base;
  ASTNode *pointer;
};

struct CaseNode {
  ASTNode base;
  ASTNode *expr;
  ASTNode *elements;
  ASTNode *else_part;
};

struct CaseLabelNode {
  ASTNode base;
  ASTNode *label;
  ASTNode *stmt;
};

struct CaseElseNode {
  ASTNode base;
  ASTNode *stmt;
};

typedef struct ConstItemNode {
  ASTNode base;
  char *name;
  ASTNode *value;
  struct ConstItemNode *next;
} ConstItemNode;

typedef struct TypeItemNode {
  ASTNode base;
  char *name;
  ASTNode *value;
  struct TypeItemNode *next;
} TypeItemNode;

struct ListNode {
  ASTNode base;
  ASTNode *element;
  ASTNode *next;
};

struct LiteralNode {
  ASTNode base;
  union {
    int integer;  // Literais inteiros
    double real;  // Literais reais
    char *string; // Literais string
    bool boolean; // Literais booleanos (true, false)
    char character;
    // NULL nil; //TODO: como implementar o literal nil
  } value;
};

SourceLocation create_location(YYLTYPE loc);
ASTNode *create_program_node(char *name, ASTNode *heading, ASTNode *block,
                             SourceLocation loc);
ASTNode *create_block_node(ASTNode *labels, ASTNode *constants, ASTNode *types,
                           ASTNode *variables, ASTNode *procs_funcs,
                           ASTNode *statements, SourceLocation loc);
ASTNode *create_heading_node(ASTNode *list, SourceLocation loc);
ASTNode *create_identifier_list_node(ASTNode *element, SourceLocation loc);
ASTNode *create_case_stmt_node(ASTNode *expr, ASTNode *elements,
                               ASTNode *else_part, SourceLocation loc);
ASTNode *create_case_element_node(ASTNode *label, ASTNode *stmt,
                                  SourceLocation loc);
ASTNode *create_case_else_node(ASTNode *stmt, SourceLocation loc);
ASTNode *create_label_declaration_node(ASTNode *labels, SourceLocation loc);
ASTNode *create_constant_declaration_node(ASTNode *id, ASTNode *constant,
                                          SourceLocation loc);
ASTNode *create_type_declaration_node(ASTNode *id, ASTNode *types,
                                      SourceLocation loc);
ASTNode *create_variable_declaration_node(ASTNode *id, ASTNode *variables,
                                          SourceLocation loc);
ASTNode *create_proc_and_func_declaration_node(ASTNode *id,
                                               ASTNode *procs_funcs,
                                               SourceLocation loc);
ASTNode *create_array_access_node(ASTNode *variable, ASTNode *sub_list,
                                  SourceLocation loc);
ASTNode *create_array_type_node(ASTNode *list, ASTNode *type,
                                SourceLocation loc);
ASTNode *create_assign_node(ASTNode *variable, ASTNode *expression,
                            SourceLocation loc);
ASTNode *create_case_list_node(ASTNode *element, SourceLocation loc);
ASTNode *create_case_of_variant_node(ASTNode *tag_field, ASTNode *variant_list,
                                     SourceLocation loc);
ASTNode *create_case_stmt_with_else_node(ASTNode *expression, ASTNode *list,
                                         ASTNode *else_part,
                                         SourceLocation loc);
ASTNode *create_constant_declaration_node(ASTNode *identifier,
                                          ASTNode *constant,
                                          SourceLocation loc);
ASTNode *create_constant_identifier(ASTNode *identifier, SourceLocation loc);
ASTNode *create_constant_literal(ASTNode *literalValue, SourceLocation loc);
ASTNode *create_integer_literal(int integer, SourceLocation loc);
ASTNode *create_real_literal(double real, SourceLocation loc);
ASTNode *create_string_literal(char *string, SourceLocation loc);
ASTNode *create_char_literal(char character, SourceLocation loc);
ASTNode *create_boolean_literal(bool boolean, SourceLocation loc);
ASTNode *create_constant_signed_identifier(ASTNode *value, char *op,
                                           SourceLocation loc);
ASTNode *create_field_identifier_list_node(ASTNode *list, ASTNode *identifier,
                                           SourceLocation loc);
ASTNode *create_file_of_type_node(ASTNode *type, SourceLocation loc);
ASTNode *create_field_list(ASTNode *fixed, ASTNode *variant,
                           SourceLocation loc);
ASTNode *create_fixed_part_node(ASTNode *fixed, ASTNode *field,
                                SourceLocation loc);
ASTNode *create_for_stmt_node(ASTNode *variable, ASTNode *for_list,
                              ASTNode *stmt, SourceLocation loc);
ASTNode *create_formal_parameters_list_node(ASTNode *list, ASTNode *param,
                                            SourceLocation loc);
ASTNode *create_function_param_node(ASTNode *identifier, ASTNode *params,
                                    ASTNode *type, SourceLocation loc);
ASTNode *create_goto_label_node(ASTNode *label, SourceLocation loc);
ASTNode *create_identifier_node(char *id, SourceLocation loc);
ASTNode *create_if_stmt_node(ASTNode *expression, ASTNode *then_part,
                             ASTNode *else_part, SourceLocation loc);
ASTNode *create_index_list_node(ASTNode *list, ASTNode *type,
                                SourceLocation loc);
ASTNode *create_label_stmt_node(ASTNode *label, ASTNode *stmt,
                                SourceLocation loc);
ASTNode *create_packed_type(ASTNode *type, SourceLocation loc);
ASTNode *create_parameter_identifier_list_node(ASTNode *list, ASTNode *element,
                                               SourceLocation loc);
ASTNode *create_parameter_list_types_node(ASTNode *list, ASTNode *type,
                                          SourceLocation loc);
ASTNode *create_parameters_node(ASTNode *parameter, SourceLocation loc);
ASTNode *create_pointer_deref_node(ASTNode *pointer, SourceLocation loc);
ASTNode *create_poniter_type_node(ASTNode *type, SourceLocation loc);
ASTNode *create_procedure_call_node(ASTNode *identifier, ASTNode *expr_list,
                                    SourceLocation loc);
ASTNode *create_procedure_param_node(ASTNode *identifier, ASTNode *params,
                                     SourceLocation loc);
ASTNode *create_record_access_node(ASTNode *identifier, ASTNode *field,
                                   SourceLocation loc);
ASTNode *create_record_access_type(ASTNode *identifier, ASTNode *field,
                                   SourceLocation loc);
ASTNode *create_record_field_node(ASTNode *field_list, ASTNode *type,
                                  SourceLocation loc);
ASTNode *create_record_type_node(ASTNode *field_list, SourceLocation loc);
ASTNode *create_repeat_until_stmt_list_node(ASTNode *list, ASTNode *expression,
                                            SourceLocation loc);
ASTNode *create_set_of_type_node(ASTNode *type, SourceLocation loc);
ASTNode *create_simple_type_node(ASTNode *type, SourceLocation loc);
ASTNode *create_stmt_list_node(ASTNode *stmt_list, SourceLocation loc);
ASTNode *create_structure_type_node(ASTNode *type, SourceLocation loc);
ASTNode *create_subscript_list_node(ASTNode *expr, SourceLocation loc);
ASTNode *create_tag_field_node(ASTNode *identifier, ASTNode *type,
                               SourceLocation loc);
ASTNode *create_type_identifier(ASTNode *identifier, SourceLocation loc);
ASTNode *create_unsigned_integer_node(int integer, SourceLocation loc);
ASTNode *create_unsigned_real_node(double real, SourceLocation loc);
ASTNode *create_variable_declaration_node(ASTNode *list, ASTNode *type,
                                          SourceLocation loc);
ASTNode *create_variant_node(ASTNode *label_list, ASTNode *field_list,
                             SourceLocation loc);
ASTNode *create_while_stmt_node(ASTNode *expr, ASTNode *stmt,
                                SourceLocation loc);
ASTNode *create_with_record_list_node(ASTNode *record_var_list, ASTNode *stmt,
                                      SourceLocation loc);

/* APPENDING */
ASTNode *append_case_list_node(ASTNode *list, ASTNode *element,
                               SourceLocation loc);
ASTNode *append_subscript_list_node(ASTNode *list, ASTNode *element,
                                    SourceLocation loc);
ASTNode *append_identifier_list_node(ASTNode *list, ASTNode *element,
                                     SourceLocation loc);
ASTNode *append_label_declaration(ASTNode *list, ASTNode *label,
                                  SourceLocation loc);
ASTNode *append_constant_declaration(ASTNode *list, ASTNode *id,
                                     ASTNode *constant, SourceLocation loc);
ASTNode *append_type_declaration(ASTNode *list, ASTNode *id, ASTNode *type,
                                 SourceLocation loc);
ASTNode *append_variable_declaration(ASTNode *list, ASTNode *id, ASTNode *vars,
                                     SourceLocation loc);
ASTNode *append_variable_identifiers_list(ASTNode *list, ASTNode *var_id,
                                          SourceLocation loc);
ASTNode *append_variant_list(ASTNode *list, ASTNode *element,
                             SourceLocation loc);
ASTNode *append_stmt_list(ASTNode *list, ASTNode *stmt, SourceLocation loc);
ASTNode *add_constant_to_block(ASTNode *block, ASTNode *constants);
ASTNode *add_type_to_block(ASTNode *block, ASTNode *types);
ASTNode *add_variable_to_block(ASTNode *block, ASTNode *variables);
ASTNode *add_proc_func_to_block(ASTNode *block, ASTNode *proc_funcs);

/* UTILS */
ASTNode *get_statements_from_block(ASTNode *block);
void free_node(ASTNode *node);
void print_todo(ASTNode *node, int indent);
void print_program_node(ASTNode *node, int indent);
// void print_binary_expr_node(ASTNode *node, int indent);
// void print_heading(ASTNode *node, int indent);
#endif
