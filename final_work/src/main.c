#include "ast/ast.h"
#include "parser/types.h"
#include "parser/parser.tab.h"
#include "code-generation/code.h"
#include "semantic-analyzer/analyzer.h"
#include "context.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "logger.h"

extern struct ASTNode *root;

void yyerror(const char *msg) {
  LOG_ERROR("%s:%d.%d-%d.%d: error: %s\n",
            yylloc.file_name ? yylloc.file_name : "input", yylloc.first_line,
            yylloc.first_column, yylloc.last_line, yylloc.last_column, msg);
}

int main(int argc, char **argv) {
  char *filename = NULL;
  char *output = "./output.c";
  int print_ast = 0;
  int semantic = 1;
  int generate_code = 1;
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--print-ast") == 0) {
      print_ast = 1;
    } else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
      output = argv[i + 1];
      i += 1;
    } else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0) {
      filename = argv[i + 1];
      i += 1;
    } else if (strcmp(argv[i], "-d") == 0 ||
               strcmp(argv[i], "--dry-run") == 0) {
      generate_code = 0;
      LOG_ERROR("Generation Code Disabled");
    } else if (strcmp(argv[i], "-s") == 0 ||
               strcmp(argv[i], "--no-semantic") == 0) {
      semantic = 0;
      LOG_ERROR("Semantic Analysis Disabled");
    } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      printf("Uso: %s [-v|--print-ast] [-f|--file "
             "arquivo.pascalm|arquivo.pascalm] [-o|--output "
             "arquivo.c]\n",
             argv[0]);
      return 0;
    } else {
      filename = argv[i];
    }
  }

  if (filename != NULL) {
    yyin = fopen(filename, "r");
    if (!yyin) {
      perror("Error open file");
      return 1;
    }
    yylloc.file_name = strdup(filename);
  } else {
    yyin = stdin;
    yylloc.file_name = strdup((char *)"stdin");
  }
  yylloc.first_column = 1;
  yylloc.first_line = 1;
  yylloc.last_column = 1;
  yylloc.last_line = 1;

  yyparse();

  if (yyin != stdin) {
    fclose(yyin);
  }

  CompilerContext *context = context_create();
  if (context == NULL) {
    yyerror("OUT OF MEMORY");
    return 1;
  }

  if (root) {
    LOG_TRACE("AST construída com sucesso:\n");
    if (print_ast == 1)
      root->print(root, 0);
    if (semantic) {
      analyze_semantics(root, context);
    }
    if (generate_code) {
      LOG_TRACE("Iniciando etapada de geração de código...");
      CodeGenerator *code_gen = create_code_generator(output);
      generate_program(code_gen, context, root);
      fclose(code_gen->output_file);
    }
    free((void *)yylloc.file_name);
    free_node(root);
    root = NULL;
  }

  context_destroy(context);
  return 0;
}
