#include "analyser.h"

void analyze_labels(ListNode *labels, CompilerContext *context) {
  ListNode *curr = labels;

  while (curr) {
    if (curr->element) {
    }

    curr = (ListNode *)curr->next;
  }
}

void analyze_constants(ListNode *constants, CompilerContext *context) {
  ListNode *curr = constants;

  while (curr) {
    if (curr->element) {
    }

    curr = (ListNode *)curr->next;
  }
}

void analyze_types(ListNode *types, CompilerContext *context) {
  ListNode *curr = types;

  while (curr) {
    if (curr->element) {
    }

    curr = (ListNode *)curr->next;
  }
}

void analyze_variables(ListNode *variables, CompilerContext *context) {
  ListNode *curr = variables;

  while (curr) {
    if (curr->element) {
    }

    curr = (ListNode *)curr->next;
  }
}

void analyze_procs_and_funcs(ListNode *procs_and_funcs,
                             CompilerContext *context) {
  ListNode *curr = procs_and_funcs;

  while (curr) {
    if (curr->element) {
    }

    curr = (ListNode *)curr->next;
  }
}

void analyze_statements(ListNode *statements, CompilerContext *context) {
  ListNode *curr = statements;

  while (curr) {
    if (curr->element) {
    }

    curr = (ListNode *)curr->next;
  }
}

void analyze_semantics(ASTNode *root_node, CompilerContext *curr_context) {
  ProgramNode *program = (ProgramNode *)root_node;
  BlockNode *block = (BlockNode *)program->block;
  ListNode *types = (ListNode *)block->types;
  ListNode *variables = (ListNode *)block->variables;
  ListNode *procs_funcs = (ListNode *)block->procs_funcs;
  ListNode *labels = (ListNode *)block->labels;
  ListNode *constants = (ListNode *)block->constants;
  ListNode *statements = (ListNode *)block->statements;

  analyze_labels(labels, curr_context);
  analyze_constants(constants, curr_context);
  analyze_types(types, curr_context);
  analyze_variables(variables, curr_context);
  analyze_procs_and_funcs(procs_funcs, curr_context);
  analyze_statements(statements, curr_context);
}
