#ifndef ANALYZER_H
#define ANALYZER_H

#include "../commons.h"
#include "../context.h"
#include "../ast/ast.h"

void analyze_semantics(ASTNode *root, CompilerContext *context);
void analyze_variables(ASTNode *variable, CompilerContext *context);
void analyze_labels(ASTNode *label, CompilerContext *context);
void analyze_types(ASTNode *type, CompilerContext *context);
void analyze_constants(ASTNode *constant, CompilerContext *context);
void analyze_functions(ASTNode *function, CompilerContext *context);
void analyze_statements(ASTNode *statement, CompilerContext *context);

ASTNode *analyze_and_get_expression_type(ASTNode *expression,
                                         CompilerContext *context);
bool check_type_compatibility(ASTNode *type, ASTNode *check_type);

#endif
