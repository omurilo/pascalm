#ifndef CODE_H
#define CODE_H

#include "../ast/ast.h"
#include "../context.h"
#include "../commons.h"

CodeGenerator *create_code_generator(char *output_file);

void generate_program(CodeGenerator *code_gen, CompilerContext *context,
                      ASTNode *node);
void generate_block(CodeGenerator *code_gen, CompilerContext *context,
                    ASTNode *node, bool is_global);
void generate_function(CodeGenerator *code_gen, CompilerContext *context,
                       ASTNode *node);
void generate_type(CodeGenerator *code_gen, CompilerContext *context,
                   ASTNode *node);
void generate_parameters(CodeGenerator *code_gen, CompilerContext *context,
                         ASTNode *node);
void generate_record(CodeGenerator *code_gen, CompilerContext *context,
                     ASTNode *node);
void generate_array(CodeGenerator *code_gen, CompilerContext *context,
                    ASTNode *node, bool disable_initialization);
void generate_statement(CodeGenerator *code_gen, CompilerContext *context,
                        ASTNode *node);
void generate_vars(CodeGenerator *code_gen, CompilerContext *context,
                   ASTNode *node);
void generate_expression(CodeGenerator *code_gen, CompilerContext *context, ASTNode *node);
const char *resolve_expression(CompilerContext *context, ASTNode *node);
const char *resolve_variable_identifier(CompilerContext *context, ASTNode *node);

void generate_string_definition(CodeGenerator *code_gen);
void generate_strings_helper_functions(CodeGenerator *code_gen);
void generate_set_helper_functions(CodeGenerator *code_gen);
void generate_array_helper_functions(CodeGenerator *code_gen);

#endif
