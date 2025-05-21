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
    BinaryOperationNode; // Operações binárias (+, -, *, /, div, mod, and, or, etc.)
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

struct SourceLocation {
  int first_line;
  int first_column;
  int last_line;
  int last_column;
  char *file_name;
};

typedef enum {
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

  /* Tipos */
  NODE_CONST_ITEM,
  NODE_SCALAR_TYPE,
  NODE_SUBRANGE_TYPE,
  NODE_TYPE_IDENTIFIER,
  NODE_STRUCTURED_TYPE,
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
  NODE_LITERAL,
  NODE_IDENTIFIER,
  NODE_MEMBER_ACCESS,
  NODE_ARRAY_ACCESS,
  NODE_FUNC_CALL,
  NODE_SET_CONSTRUCTOR,

  /* Auxiliares */

  NODE_FIELD_LIST,
  NODE_PARAMETER,
  NODE_VARIANT_RECORD,
  NODE_LIST,
  NODE_ERROR
} NodeType;

typedef enum {
    SYMBOL_UNKNOWN,       // Ainda não resolvido
    
    // Tipos de identificadores primários
    SYMBOL_VARIABLE,      // Variável
    SYMBOL_CONSTANT,      // Constante
    SYMBOL_PARAMETER,     // Parâmetro de função/procedimento
    SYMBOL_FUNCTION,      // Função
    SYMBOL_PROCEDURE,     // Procedimento
    SYMBOL_TYPE,          // Tipo definido pelo usuário
    
    // Tipos específicos de variáveis
    SYMBOL_FIELD,         // Campo de um record
    SYMBOL_LOCAL_VAR,     // Variável local
    SYMBOL_GLOBAL_VAR,    // Variável global
    
    // Tipos específicos de parâmetros
    SYMBOL_VALUE_PARAM,   // Parâmetro por valor
    SYMBOL_VAR_PARAM,     // Parâmetro por referência (var)
    
    // Tipos específicos para tipos
    SYMBOL_ENUM_VALUE,    // Valor de enumeração
    SYMBOL_LABEL,         // Rótulo (label)
    
    // Para escopos internos
    SYMBOL_PROGRAM,       // Nome do programa
    SYMBOL_UNIT,          // Nome da unit (para Pascal modular)
    
    // Tipos especiais
    SYMBOL_FORWARD_DECL,  // Declaração forward de função/procedimento
    SYMBOL_BUILTIN        // Funções/procedimentos/tipos built-in
} SymbolKind;

typedef struct SymbolEntry {
    char *name;             // Nome do símbolo
    SymbolKind kind;        // Tipo do símbolo
    
    union {
        struct {
            ASTNode *type;  // Tipo da variável/parâmetro/constante
            int offset;     // Offset na stack/frame (para variáveis)
            bool is_ref;    // Se é parâmetro por referência
        } var_info;
        
        struct {
            ASTNode *return_type;     // Tipo de retorno (NULL para void/procedure)
            ASTNode *params;          // Lista de parâmetros
            ASTNode *body;            // Corpo da função
            bool is_forward;          // Se é declaração forward
        } func_info;
        
        struct {
            ASTNode *definition;      // Definição do tipo
            size_t size;              // Tamanho do tipo (em bytes)
        } type_info;
    } info;
    
    int scope_level;        // Nível de escopo para verificação de visibilidade
    SourceLocation location; // Localização da declaração para mensagens de erro
    struct SymbolEntry *next; // Para implementação de lista encadeada na tabela
} SymbolEntry;

struct ASTNode {
  NodeType type;
  SourceLocation location;
  void (*print)(struct ASTNode *,
                int); // Função para imprimir o nó (para debug)
  /*
  int data_type; // tipo dos dados (INTEGER, REAL, STRING, etc.)
  int scope_level; // Nível de escopo para análise de visibilidade
  void *symbol_entry; // ponteiro para entrada na tabela de símbolos
  void *pass_info;  // Informações específicas para diferentes passes
  */
};

/*
// auxiliar na verificação semântica:
struct BinaryOperationNode {
    ASTNode base;
    int operator;                // Operator type (ADD, SUB, MUL, etc.)
    ASTNode *left;               // Left operand
    ASTNode *right;              // Right operand
    int result_type;             // Result type after operation
    int is_constant;             // Flag if result is constant
};

struct IdentifierNode {
    ASTNode base;
    char *name;                  // Identifier name
    void *symbol_entry;          // Reference to symbol table entry
    int is_lvalue;               // Is this usable as an l-value?
};

void resolve_identifier(ASTNode *node, SymbolTable *table) {
    if (node->type != NODE_IDENTIFIER) return;
    
    IdentifierNode *id = (IdentifierNode *)node;
    SymbolEntry *entry = lookup_symbol(table, id->name);
    
    if (entry) {
        id->kind = entry->kind;
        id->symbol_entry = entry;
    } else {
        // Erro: identificador não declarado
        report_error("Undeclared identifier: %s", id->name);
    }
}

struct VariantRecordNode {
    ASTNode base;
    IdentifierNode *tag_field;   // Tag field name
    TypeIdentifierNode *tag_type;// Tag field type
    ListNode *variants;          // List of variant parts
    int has_runtime_checks;      // Flag if runtime checks are needed
};

// expandir para suportar diferentes tipos
typedef enum {
    LITERAL_INTEGER,
    LITERAL_REAL,
    LITERAL_BOOLEAN,
    LITERAL_STRING,
    LITERAL_CHAR,
    LITERAL_NIL
} LiteralType;

struct LiteralNode {
    ASTNode base;
    LiteralType literal_type;    // Type of literal
    union {
        int int_val;             // Integer value
        double real_val;         // Real value
        int bool_val;            // Boolean value (0/1)
        char *str_val;           // String value
        char char_val;           // Character value
    } value;
};

void check_assignment(ASTNode *target, ASTNode *value) {
    if (target->type == NODE_IDENTIFIER) {
        IdentifierNode *id = (IdentifierNode *)target;
        
        // Verificar se o identificador pode receber um valor
        switch (id->kind) {
            case SYMBOL_VARIABLE:
            case SYMBOL_LOCAL_VAR:
            case SYMBOL_GLOBAL_VAR:
            case SYMBOL_PARAMETER:
            case SYMBOL_VAR_PARAM:
            case SYMBOL_FIELD:
                // OK, pode ser destino de atribuição
                break;
                
            case SYMBOL_CONSTANT:
            case SYMBOL_FUNCTION:
            case SYMBOL_TYPE:
            case SYMBOL_ENUM_VALUE:
                report_error("Cannot assign to %s (not a variable)", 
                             get_symbol_kind_name(id->kind));
                break;
                
            case SYMBOL_UNKNOWN:
                report_error("Identifier not resolved: %s", id->name);
                break;
                
            default:
                report_error("Invalid assignment target");
        }
    }
    // Outras verificações de tipo...
}

// Campos Para Verificação de Escopo em Nós de Declaração

struct VarDeclarationNode {
    ASTNode base;
    ListNode *var_list;          // List of variables
    ASTNode *type_node;          // Type of the variables
    int scope_level;             // Scope level of declaration
    VarDeclarationNode *next;    // Next var declaration
};

// Para implementar o suporte ao tipo string nativo:

struct SimpleTypeNode {
    ASTNode base;
    int type_kind;               // INTEGER, REAL, BOOLEAN, CHAR, STRING, etc.
    union {
        struct {
            int max_length;      // Maximum string length (for string)
        } string;
        // Outros campos específicos para outros tipos
    } info;
};


// flags para indicar quando são necessárias verificações em tempo de execução:

struct ArrayAccessNode {
    ASTNode base;
    ASTNode *array;              // Array being accessed
    ListNode *indices;           // List of indices
    int needs_bounds_check;      // Flag if bounds checking is needed
};

struct PointerDerefNode {
    ASTNode base;
    ASTNode *pointer;            // Pointer being dereferenced
    int needs_nil_check;         // Flag if nil check is needed
};
*/

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
  ASTNode *value;
};

struct ConstDeclarationNode {
  ASTNode base;
  ASTNode *identifier;
  ASTNode *const_expr;
};

struct TypeDeclarationNode {
  ASTNode base;
  ASTNode *identifier;
  ASTNode *type_expr;
};

struct VarDeclarationNode {
    ASTNode base;
    ASTNode *var_list;          // List of variables
    ASTNode *type_node;          // Type of the variables
    int scope_level;             // Scope level of declaration
};

struct ProcDeclarationNode {
  ASTNode base;
  ASTNode *identifier;
  ASTNode *parameters;
  ASTNode *block_or_forward;
};

struct FuncDeclarationNode {
  ASTNode base;
  ASTNode *identifier;
  ASTNode *parameters;
  ASTNode *type;
  ASTNode *block_or_forward;
};

struct IdentifierNode {
    ASTNode base;
    char *name;                  // Identifier name
    SymbolKind kind;             // Inicialmente SYMBOL_UNKNOWN
    void *symbol_entry;          // Reference to symbol table entry
    // int is_lvalue;               // Is this usable as an l-value?
};

struct AssignmentNode {
  ASTNode base;
    ASTNode *target;     // Variável alvo (lado esquerdo)
    ASTNode *expression; // Expressão (lado direito) fm
}

struct IfNode {
    ASTNode base;
    ASTNode *condition;     // Expressão de condição
    ASTNode *then_stmt;     // Statement a executar se verdadeiro
    ASTNode *else_stmt;     // Statement a executar se falso (pode ser NULL)
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
  ASTNode *case_list;
  ASTNode *else_part;
};

struct CaseLabelNode {
  ASTNode base;
  ASTNode *valie_list;
  ASTNode *label;
  ASTNode *stmt;
};

struct CaseElseNode {
  ASTNode base;
  ASTNode *stmt;
};

struct WhileStmtNode {
    ASTNode base;
    ASTNode *condition;     // Expressão de condição
    ASTNode *body;          // Statement a executar enquanto verdadeiro
};

struct RepeatUntilNode {
    ASTNode base;
    ASTNode *body;          // Lista de statements a executar
    ASTNode *condition;     // Condição para sair do loop
};

struct ForStmtNode {
    ASTNode base;
    ASTNode *variable;      // Variável de controle
    ASTNode *for_list;      // Informações do intervalo (inicial, final, step)
    ASTNode *body;          // Statement a executar
    bool is_downto;         // true se for downto, false se for to
};

struct ForListNode {
    ASTNode base;
    ASTNode *start_expr;    // Expressão inicial
    ASTNode *end_expr;      // Expressão final
    bool is_downto;         // true se for downto, false se for to
};

struct ProcedureCallNode {
    ASTNode base;
    ASTNode *procedure;     // Identificador do procedimento
    ASTNode *params;        // Lista de parâmetros (pode ser NULL)
};

struct GotoNode {
    ASTNode base;
    ASTNode *label;         // Rótulo de destino
};

struct WithNode {
    ASTNode base;
    ASTNode *record_list;   // Lista de variáveis record
    ASTNode *body;          // Statement a executar
};

struct LabeledStmtNode {
    ASTNode base;
    ASTNode *label;         // Rótulo
    ASTNode *statement;     // Statement
};


struct ListNode {
  ASTNode base;
  ASTNode *element;
  ASTNode *next;
};

typedef enum {
    LITERAL_INTEGER,
    LITERAL_REAL,
    LITERAL_BOOLEAN,
    LITERAL_STRING,
    LITERAL_CHAR,
    LITERAL_NIL
} LiteralType;

struct LiteralNode {
    ASTNode base;
    LiteralType literal_type;    // Type of literal
    union {
        int int_val;             // Integer value
        double real_val;         // Real value
        int bool_val;            // Boolean value (0/1)
        char *str_val;           // String value
        char char_val;           // Character value
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
ASTNode *create_variable_identifier_list_node(ASTNode *identifier, SourceLocation loc);
ASTNode *create_proc_and_func_declarations_node(ASTNode* procs_and_funcs, SourceLocation loc);
ASTNode *create_proc_declaration_node(ASTNode *id,
    ASTNode *parameters,
                                               ASTNode *block_or_forward,
                                               SourceLocation loc);
ASTNode *create_func_declaration_node(ASTNode *id,
     ASTNode *parameters, ASTNode *type, ASTNode *block_or_forward,
                                               SourceLocation loc);
ASTNode *create_array_access_node(ASTNode *variable, ASTNode *sub_list,
                                  SourceLocation loc);
ASTNode *create_array_type_node(ASTNode *list, ASTNode *type,
                                SourceLocation loc);
ASTNode *create_assign_node(ASTNode *variable, ASTNode *expression,
                            SourceLocation loc);
ASTNode *create_case_list_node(ASTNode *element, SourceLocation loc);
ASTNode *create_case_range_node(ASTNode* constant, ASTNode *constant, SourceLocation loc);
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
ASTNode *create_nil_literal(SourceLocation loc);
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
ASTNode *create_stmt_list_node(ASTNode *stmt, SourceLocation loc);
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
ASTNode *append_variable_declaration(ASTNode *list, ASTNode *vars, ASTNode *type,
                                     SourceLocation loc);
ASTNode *append_variable_identifier_list(ASTNode *list, ASTNode *var_id,
                                          SourceLocation loc);
ASTNode *append_variant_list(ASTNode *list, ASTNode *element,
                             SourceLocation loc);
ASTNode *append_stmt_list(ASTNode *list, ASTNode *stmt, SourceLocation loc);
ASTNode *append_proc_and_func_declarations(ASTNode* list, ASTNode* proc_and_func, SourceLocation loc);
ASTNode *add_labels_to_block(ASTNode *block, ASTNode *proc_funcs);
ASTNode *add_constants_to_block(ASTNode *block, ASTNode *constants);
ASTNode *add_types_to_block(ASTNode *block, ASTNode *types);
ASTNode *add_variables_to_block(ASTNode *block, ASTNode *variables);
ASTNode *add_procs_funcs_to_block(ASTNode *block, ASTNode *proc_funcs);

/* UTILS */
ASTNode *get_statements_from_block(ASTNode *block);
void free_node(ASTNode *node);
void print_todo(ASTNode *node, int indent);
void print_program_node(ASTNode *node, int indent);
// void print_binary_expr_node(ASTNode *node, int indent);
// void print_heading(ASTNode *node, int indent);
#endif

/*
//  funções auxiliares para facilitar o trabalho com a AST:
ASTNode* clone_ast_node(ASTNode *node);  // Função para clonar um nó (útil para otimizações)

// Funções de verificação semântica
int check_type_compatibility(ASTNode *left_type, ASTNode *right_type, int context);
int is_assignment_valid(ASTNode *left, ASTNode *right);
void verify_array_bounds(ArrayAccessNode *node);
void verify_case_labels(CaseNode *node);
int is_constant_expression(ASTNode *expr);

*/

/**
// Implemente funções de limpeza para cada tipo de nó
// Considere o uso de um sistema de garbage collection ou referência contada


// Estrutura de Visitante:
// Implementar um padrão visitante para percorrer a AST, facilitando diferentes 
ases de análise:

typedef struct Visitor {
    void (*visit_program)(Visitor *self, ProgramNode *node);
    void (*visit_block)(Visitor *self, BlockNode *node);
    // Funções para todos os tipos de nós
    void *context;  // Contexto de visita
} Visitor;
};

*/
