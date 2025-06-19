#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include "../commons.h"
#include "../context.h"

typedef struct ProgramNode ProgramNode; // Raiz da AST, contendo o nome do
                                        // programa e seu bloco principal
typedef struct HeadingNode HeadingNode; // Lista de identificadores de cabeçalho
typedef struct BlockNode BlockNode;     // Contém declarações e o corpo do pr
                                        // grama/procedimento/função
typedef struct UsesNode UsesNode;       // Lista de módulos importados
typedef struct ConstDeclarationNode ConstDeclarationNode; // Declaração de constantes
typedef struct TypeDeclarationNode TypeDeclarationNode; // Declaração de tipos
typedef struct VarDeclarationNode VarDeclarationNode; // Declaração de variáveis
typedef struct FuncDeclarationNode FuncDeclarationNode; // Declaração de funções

typedef struct SimpleTypeNode SimpleTypeNode;      // Tipos simples
/**/ typedef struct EnumeratedTypeNode EnumeratedTypeNode; // Tipo enumerado
/**/ typedef struct SubrangeTypeNode SubrangeTypeNode; // Tipo de subintervalo
/**/ typedef struct TypeIdentifierNode TypeIdentifierNode; // Referência a um tipo identificador
typedef struct StructuredTypeNode StructuredTypeNode; // Tipos estruturados
/**/ typedef struct ArrayTypeNode ArrayTypeNode;      // Tipo array
/**/ typedef struct RecordTypeNode RecordTypeNode;    // Tipo record
/**/ typedef struct SetTypeNode SetTypeNode;          // Tipo set
/**/ typedef struct FileTypeNode FileTypeNode;        // Tipo file
typedef struct PointerTypeNode PointerTypeNode;       // Tipo ponteiro
typedef struct PointerDerefNode PointerDerefNode;

typedef struct CompoundStatementNode CompoundStatementNode;                    // Bloco de comandos (begin...end)
typedef struct AssignmentNode AssignmentNode; // Atribuição (:=)
typedef struct IfNode IfNode; // Estrutura condicional if-then-else
typedef struct LabeledStmtNode LabeledStmtNode;
typedef struct CaseNode CaseNode;           // Estrutura de seleção case
typedef struct CaseItemNode CaseItemNode;
typedef struct CaseLabelNode CaseLabelNode; // Cada label dentro de um case
typedef struct CaseElseNode CaseElseNode;   // Cláusula else do case (extensão)

typedef struct WhileNode WhileNode;   // Laço while
typedef struct WhileStmtNode WhileStmtNode;
typedef struct RepeatUntilNode RepeatUntilNode;
typedef struct ForStmtNode ForStmtNode;       // Laço for
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
typedef struct IndexList IndexList;
typedef struct ErrorNode ErrorNode; // Nó para representar erros sintáticos
typedef struct ElementNode ElementNode;
typedef struct OperationNode OperationNode;

typedef struct RecordFieldNode RecordFieldNode;
typedef struct FieldListNode FieldListNode;
typedef struct FixedPartNode FixedPartNode;
typedef struct TagFieldNode TagFieldNode;
typedef struct VariantPartNode VariantPartNode;
typedef struct VariantListNode VariantListNode;
typedef struct VariantRecordNode VariantRecordNode;

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

struct ParameterNode {
  ASTNode base;
  ASTNode *params_list;
};

typedef struct ParameterIdentifierList {
  ASTNode base;
  ASTNode *params_id_list;
  ASTNode *params_type;
} ParameterIdentifierList;

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
    // int is_lvalue;               // Is this usable as an l-value?
    SymbolEntry *symbol;
};

struct TypeIdentifierNode {
  ASTNode base;
  SymbolKind kind;
  bool is_base_type;
  IdentifierNode *id;
  SymbolEntry *symbol;
};

struct AssignmentNode {
  ASTNode base;
  ASTNode *target;     // Variável alvo (lado esquerdo)
  ASTNode *expression; // Expressão (lado direito) fm
};

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

struct CaseItemNode {
  ASTNode base;
  ASTNode *value_list;
  ASTNode *statement;
};

struct CaseLabelNode {
  ASTNode base;
  ASTNode *lower;
  ASTNode *upper;
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
    ASTNode *start_expr;    // Expressão inicial
    ASTNode *end_expr;      // Expressão final
    ASTNode *body;          // Statement a executar
    bool is_downto;         // true se for downto, false se for to
};

struct FunctionCallNode {
  ASTNode base;
  ASTNode *function;
  ASTNode *params;
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

typedef struct ConstantNode {
    ASTNode base;
    ASTNode *value;
    ASTNode *identifier;
    ConstantType const_type;
    bool is_literal;
    char *sign;
} ConstantNode;

struct EnumeratedTypeNode {
  ASTNode base;
  ASTNode *identifiers_list;
};

struct SubrangeTypeNode {
  ASTNode base;
  ASTNode *upper;
  ASTNode *lower;
};

struct SimpleTypeNode {
  ASTNode base;
  ASTNode *type;
};

struct StructuredTypeNode {
  ASTNode base;
  bool is_packed;
  ASTNode * type;
};

struct ArrayTypeNode {
    ASTNode base;
    ASTNode *index_list;
    ASTNode *type; //TODO(Semantic Analysis): all index list node must have the same type?
};

struct RecordTypeNode {
    ASTNode base;
    ASTNode *field_list;
    ASTNode *variant_part;
};

typedef enum {
    SET_ELEMENT_SINGLE,  // valor único
    SET_ELEMENT_RANGE    // range (a..b)
} SetElementType;

typedef struct {
    ASTNode base;
    SetElementType type;
    union {
        ASTNode* single_value;
        struct {
            ASTNode* start;
            ASTNode* end;
        } range;
    } value;
} SetElement;

typedef struct {
    ASTNode base;
    SetElement** elements;
    int count;
    int capacity;
} SetLiteral;

struct SetTypeNode {
    ASTNode base;
    ASTNode *type;
};

struct FileTypeNode {
    ASTNode base;
    ASTNode *type;
};

struct PointerTypeNode {
    ASTNode base;
    ASTNode *type;
};

struct BinaryOperationNode {
  ASTNode base;
  BinaryOperator op;
  ASTNode *left;
  ASTNode *right;
};

struct UnaryOperationNode {
  ASTNode base;
  UnaryOperator op;
  ASTNode *operand;
};

struct RecordFieldNode {
  ASTNode base;
  ASTNode *field_list;
  ASTNode *record_type;
};

struct FieldListNode {
  ASTNode base;
  ASTNode *fixed_part;
  ASTNode *variant_part;
};

struct FixedPartNode {
  ASTNode base;
  ASTNode *fields;
  int field_count;
};

struct TagFieldNode {
  ASTNode base;
  ASTNode *field;
  ASTNode *tag_type;
};

struct VariantPartNode {
  ASTNode base;
  ASTNode *tag_field;
  ASTNode *variant_list;
};

struct VariantListNode {
  ASTNode base;
  ASTNode *variants;
  int variant_count;
};

struct VariantRecordNode {
  ASTNode base;
  ASTNode *case_labels;
  ASTNode *field_list;
};

struct ElementNode {
  ASTNode base;
  ASTNode *lower;
  ASTNode *upper;
};

/* Estrutura para uma seção de parâmetros formais */
typedef struct {
    ASTNode base;
    ParameterKind kind;
    ASTNode* identifiers;    // Lista de identificadores
    ASTNode* type;          // Tipo dos parâmetros (para PARAM_VALUE e PARAM_VAR)
    ASTNode* parameters;    // Parâmetros do proc/func (para PARAM_PROCEDURE e PARAM_FUNCTION)
    ASTNode* return_type;   // Tipo de retorno (apenas para PARAM_FUNCTION)
} FormalParameterSectionNode;

struct ListNode {
  ASTNode base;
  ASTNode *element;
  ASTNode *next;
};

struct IndexList {
  ASTNode base;
  ASTNode **indexes;
  int count;
  int capacity;
};

struct OperationNode {
  ASTNode base;
  char *op;
  int precedence;
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
ASTNode *create_case_else_node(ASTNode *stmt, SourceLocation loc);
ASTNode *create_case_item_node(ASTNode *value_list, ASTNode *stmt, SourceLocation loc);
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
ASTNode *create_forward_declaration_node(SourceLocation loc);
ASTNode *create_array_access_node(ASTNode *variable, ASTNode *sub_list,
                                  SourceLocation loc);
ASTNode *create_array_type_node(ASTNode *list, ASTNode *type,
                                SourceLocation loc);
ASTNode *create_assign_node(ASTNode *variable, ASTNode *expression,
                            SourceLocation loc);
ASTNode *create_case_list_node(ASTNode *element, SourceLocation loc);
ASTNode *create_case_range_node(ASTNode* constant, ASTNode *constant2, SourceLocation loc);
ASTNode *create_case_of_variant_node(ASTNode *tag_field, ASTNode *variant_list,
                                     SourceLocation loc);
ASTNode *create_case_stmt_with_else_node(ASTNode *expression, ASTNode *list,
                                         ASTNode *else_part,
                                         SourceLocation loc);
ASTNode *create_case_label_list(ASTNode* case_label, SourceLocation loc);
ASTNode *create_constant_declaration_node(ASTNode *identifier,
                                          ASTNode *constant,
                                          SourceLocation loc);
ASTNode *create_constant_range_node(ASTNode *constant1, ASTNode *constant2, SourceLocation loc);
ASTNode *create_function_call_node(ASTNode *id, ASTNode *params, SourceLocation loc);
ASTNode *create_constant_identifier(ASTNode *identifier, SourceLocation loc);
ASTNode *create_constant_literal(ASTNode *literalValue, SourceLocation loc);
ASTNode *create_relational_op(char *op, SourceLocation loc);
ASTNode *create_multiplicative_node(char *op, SourceLocation Loc);
ASTNode *create_binary_expression(ASTNode *left, BinaryOperator op,
                                    ASTNode *right, SourceLocation loc);
ASTNode *create_unary_expression(UnaryOperator unary_op, ASTNode *operand,
                                 SourceLocation loc);
ASTNode *create_integer_literal(int integer, SourceLocation loc);
ASTNode *create_real_literal(double real, SourceLocation loc);
ASTNode *create_string_literal(char *string, SourceLocation loc);
ASTNode *create_char_literal(char character, SourceLocation loc);
ASTNode *create_boolean_literal(bool boolean, SourceLocation loc);
ASTNode *create_nil_literal(SourceLocation loc);
ASTNode *create_constant_signed_identifier(ASTNode *value, const char *sign,
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
ASTNode *create_for_list_node(ASTNode *start, ASTNode *end, bool is_downto, SourceLocation loc);
ASTNode *create_formal_parameters_list_node(ASTNode *list, ASTNode *param,
                                            SourceLocation loc);
ASTNode *create_goto_label_node(ASTNode *label, SourceLocation loc);
ASTNode *create_identifier_node(char *id, SourceLocation loc);
ASTNode *create_if_stmt_node(ASTNode *expression, ASTNode *then_part,
                             ASTNode *else_part, SourceLocation loc);
ASTNode *create_index_list_start(ASTNode *first_index, SourceLocation loc);
ASTNode *create_label_stmt_node(ASTNode *label, ASTNode *stmt,
                                SourceLocation loc);
ASTNode *create_packed_type(ASTNode *type, SourceLocation loc);
ASTNode *create_parameter_identifier_list_node(ASTNode *list, ASTNode *element,
                                               SourceLocation loc);
ASTNode* create_formal_parameter_section_node(ParameterKind kind, ASTNode* identifiers, ASTNode* type,
                                             ASTNode* parameters, ASTNode* return_type, SourceLocation loc);
ASTNode *create_parameters_node(ASTNode *parameter, SourceLocation loc);
ASTNode *create_pointer_deref_node(ASTNode *pointer, SourceLocation loc);
ASTNode *create_pointer_type_node(ASTNode *type, SourceLocation loc);
ASTNode *create_procedure_call_node(ASTNode *identifier, ASTNode *expr_list,
                                    SourceLocation loc);
ASTNode *create_record_access_node(ASTNode *identifier, ASTNode *field,
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
ASTNode *create_enumerated_type_node(ASTNode *identiiers_list, SourceLocation loc);
ASTNode *create_subscript_list_node(ASTNode *expr, SourceLocation loc);
ASTNode *create_tag_field_node(ASTNode *identifier, ASTNode *type,
                               SourceLocation loc);
ASTNode *create_type_identifier(ASTNode *identifier, SourceLocation loc);
ASTNode *create_builtin_type_identifier(char *type, SourceLocation loc);
ASTNode *create_builtin_identifier(char *i, SourceLocation loc);
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
ASTNode *create_set_literal(SourceLocation loc);
ASTNode *create_set_literal_with_element(ASTNode *element, SourceLocation loc);
ASTNode *add_element_to_set_literal(ASTNode* set_literal, ASTNode *element, SourceLocation loc);
ASTNode *create_set_element(ASTNode *expr, SourceLocation loc);
ASTNode *create_set_range_element(ASTNode* const1, ASTNode *const2, SourceLocation loc);
ASTNode *create_expression_list(ASTNode *element, SourceLocation loc);
ASTNode *append_expression_list(ASTNode *list, ASTNode *element, SourceLocation loc);
ASTNode *append_case_list_node(ASTNode *list, ASTNode *element,
                               SourceLocation loc);
ASTNode *append_case_label_list(ASTNode *list, ASTNode *case_label, SourceLocation loc);
ASTNode *append_case_item(ASTNode *list, ASTNode *case_item, SourceLocation loc);
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
ASTNode *append_index_to_list(ASTNode *list, ASTNode *element, SourceLocation loc);
ASTNode *create_record_variable_list_node(ASTNode *record_var, SourceLocation loc);
ASTNode *append_stmt_list(ASTNode *list, ASTNode *stmt, SourceLocation loc);
ASTNode *append_proc_and_func_declarations(ASTNode* list, ASTNode* proc_and_func, SourceLocation loc);
ASTNode *append_record_variable_list(ASTNode *list, ASTNode *record_var, SourceLocation loc);
ASTNode *add_labels_to_block(ASTNode *block, ASTNode *proc_funcs);
ASTNode *add_constants_to_block(ASTNode *block, ASTNode *constants);
ASTNode *add_types_to_block(ASTNode *block, ASTNode *types);
ASTNode *add_variables_to_block(ASTNode *block, ASTNode *variables);
ASTNode *add_procs_funcs_to_block(ASTNode *block, ASTNode *proc_funcs);

/* UTILS */
ASTNode *update_identifier_node_kind(ASTNode *id, SymbolKind);
ASTNode *get_statements_from_block(ASTNode *block);
void free_node(ASTNode *node);
void print_todo(ASTNode *node, int indent);
void print_program_node(ASTNode *node, int indent);
void print_identifier_node(ASTNode *node, int indent);
void print_stmt_list(ASTNode *node, int indent);
void print_binary_operation(ASTNode *node, int indent);
void print_unary_operation(ASTNode *node, int indent);
const char* get_node_type_name(NodeType type);
const char* binary_op_to_string(BinaryOperator op);
const char* unary_op_to_string(UnaryOperator op);
const char* get_symbol_kind_name(SymbolKind symb);
void check_params(ASTNode *id, ASTNode *params);
const char* get_literal_type_name(LiteralType type);
const char *get_param_kind_name(ParameterKind kind);
// void print_binary_expr_node(ASTNode *node, int indent);
// void print_heading(ASTNode *node, int indent);
ConstantValue evaluate_constant(CompilerContext *context, ASTNode *const_node);
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
cases de análise:

typedef struct Visitor {
    void (*visit_program)(Visitor *self, ProgramNode *node);
    void (*visit_block)(Visitor *self, BlockNode *node);
    // Funções para todos os tipos de nós
    void *context;  // Contexto de visita
} Visitor;
};

*/
