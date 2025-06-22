#ifndef ANALYZER_H
#define ANALYZER_H

#include "../commons.h"
#include "../logger.h"
#include "../context.h"
#include "../ast/ast.h"
#include "../memory.h"

void analyze_semantics(ASTNode *root, CompilerContext *context);

#endif
