#ifndef CODE_H
#define CODE_H

#include "../ast/ast.h"

CodeGenerator* create_code_generator(char* output_file);

void generate_program(CodeGenerator *code_gen, ASTNode *node);
void generate_function(CodeGenerator *code_gen, ASTNode *node);
void generate_type(CodeGenerator *code_gen, ASTNode *node);
void generate_parameters(CodeGenerator *code_gen, ASTNode *node);
void generate_block(CodeGenerator *code_gen, ASTNode *node);

#endif
