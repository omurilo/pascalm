#include <assert.h>
#include <string.h>
#include "analyzer.h"

static void analyze_statement(ASTNode *statement, CompilerContext *context);
static ASTNode *analyze_expression(ASTNode *expression,
                                   CompilerContext *context);
static void analyze_record_fields(SymbolEntry *record_type_symbol,
                                  CompilerContext *context);
static void analyze_call_parameters(ASTNode *params, CompilerContext *context);
static void analyze_functions(ASTNode *function, CompilerContext *context);
static void analyze_array_bounds(ASTNode *array_def,
                                 SymbolEntry *array_type_symbol,
                                 CompilerContext *context);

bool need_string_helpers = false;
bool need_set_helpers = false;

static void insert_builtin_types(CompilerContext *context,
                                 SourceLocation location) {
  char *builtin_types[5] = {"integer", "real", "boolean", "char", "string"};

  for (int i = 0; i < 5; i++) {
    ASTNode *result =
        create_builtin_type_identifier(builtin_types[i], location);
    TypeIdentifierNode *tid = (TypeIdentifierNode *)result;
    IdentifierNode *id = (IdentifierNode *)tid->id;

    SymbolEntry *s = create_symbol_entry(
        id->name, SYMBOL_BUILTIN, context->scope_stack->scope_level, location);
    s->info.type_info.definition = result;
    s->info.type_info.fields = NULL;

    id->symbol = s;
    tid->symbol = s;

    context_insert(context, id->name, s);
  }
}

static void insert_builtin_funcs_and_procs(CompilerContext *context,
                                           SourceLocation location) {
  struct builtin_funcs {
    char *name;
    char *type;
    char *param;
  } builtin_funcs[1] = {{.name = "Chr", .type = "char", .param = "integer"}};

  for (int i = 0; i < 1; i++) {
    ASTNode *result =
        create_builtin_identifier(builtin_funcs[i].name, location);
    IdentifierNode *id = (IdentifierNode *)result;
    SymbolEntry *tid_symbol = context_lookup(context, "char");
    SymbolEntry *param_tid_symbol = context_lookup(context, "integer");

    id->kind = SYMBOL_BUILTIN_FUNCTION;

    ASTNode *param_id = create_identifier_node("num", location);
    ASTNode *params_id_list =
        create_parameter_identifier_list_node(NULL, param_id, location);
    ASTNode *params_section_list = create_formal_parameter_section_node(
        PARAM_VALUE, params_id_list,
        param_tid_symbol->info.type_info.definition, NULL, NULL, location);
    ASTNode *params_list =
        create_formal_parameters_list_node(NULL, params_section_list, location);
    ASTNode *param = create_parameters_node(params_list, location);
    ASTNode *block_or_forward = create_forward_declaration_node(location);
    ASTNode *function = create_func_declaration_node(
        result, param, tid_symbol->info.type_info.definition, block_or_forward,
        location);

    analyze_functions(function, context);
  }
}

static ASTNode *get_type_from_literal(ASTNode *literal_node) {
  if (!literal_node || literal_node->type != NODE_LITERAL)
    return NULL;
  LiteralNode *l = (LiteralNode *)literal_node;
  char *type_name;
  switch (l->literal_type) {
  case LITERAL_INTEGER:
    type_name = "integer";
    break;
  case LITERAL_REAL:
    type_name = "real";
    break;
  case LITERAL_BOOLEAN:
    type_name = "boolean";
    break;
  case LITERAL_CHAR:
    type_name = "char";
    break;
  case LITERAL_STRING:
    type_name = "string";
    break;
  default:
    return NULL;
  }
  return create_builtin_type_identifier(type_name, l->base.location);
}

static LiteralType get_literal_type_from_name(const char *name) {
  if (strcmp(name, "integer") == 0) {
    return LITERAL_INTEGER;
  } else if (strcmp(name, "real") == 0) {
    return LITERAL_REAL;
  } else if (strcmp(name, "bool") == 0 || strcmp(name, "boolean") == 0) {
    return LITERAL_BOOLEAN;
  } else if (strcmp(name, "char") == 0) {
    return LITERAL_CHAR;
  } else if (strcmp(name, "string") == 0) {
    return LITERAL_STRING;
  }

  fprintf(stderr, "[WARN] Trying to get literal type from %s\n", name);

  return LITERAL_NIL;
}

static SymbolEntry *resolve_to_type_symbol(ASTNode *type_node,
                                           CompilerContext *context) {
  if (!type_node)
    return NULL;

  if (type_node->type == NODE_IDENTIFIER) {
    IdentifierNode *id = (IdentifierNode *)type_node;
    SymbolEntry *s = context_lookup(context, id->name);
    id->symbol = s;
    return s;
  }

  if (type_node->type == NODE_TYPE_IDENTIFIER) {
    return resolve_to_type_symbol(
        ((ASTNode *)((TypeIdentifierNode *)type_node)->id), context);
  }

  if (type_node->type == NODE_STRUCTURED_TYPE) {
    return resolve_to_type_symbol(((StructuredTypeNode *)type_node)->type,
                                  context);
  }

  if (type_node->type == NODE_SIMPLE_TYPE) {
    return resolve_to_type_symbol(((SimpleTypeNode *)type_node)->type, context);
  }

  if (type_node->type == NODE_ARRAY_ACCESS) {
    return resolve_to_type_symbol(((ArrayAccessNode *)type_node)->array,
                                  context);
  }

  if (type_node->type == NODE_ARRAY_TYPE) {
    return resolve_to_type_symbol(((ArrayTypeNode *)type_node)->type, context);
  }

  if (type_node->type == NODE_SET_TYPE) {
    return resolve_to_type_symbol(((SetTypeNode *)type_node)->type, context);
  }

  if (type_node->type == NODE_SUBRANGE_TYPE) {
    return NULL;
  }

  LOG_DEBUG("The node of kind %s (%d.%d-%d.%d) is not mapped here (%d)",
            get_node_type_name(type_node->type), type_node->location.first_line,
            type_node->location.first_column, type_node->location.last_line,
            type_node->location.last_column, __LINE__);

  return NULL;
}

static ASTNode *resolve_to_actual_type_def(ASTNode *type_node,
                                           CompilerContext *context) {
  if (!type_node)
    return NULL;

  if (type_node->type == NODE_TYPE_IDENTIFIER) {
    IdentifierNode *id = ((TypeIdentifierNode *)type_node)->id;
    if (!id->symbol) {
      id->symbol = context_lookup(context, id->name);
    }
    SymbolEntry *s = id->symbol;
    if (s && s->kind == SYMBOL_TYPE) {
      return resolve_to_actual_type_def(s->info.type_info.definition, context);
    }
  }

  if (type_node->type == NODE_STRUCTURED_TYPE) {
    return ((StructuredTypeNode *)type_node)->type;
  }

  if (type_node->type == NODE_SIMPLE_TYPE) {
    return resolve_to_actual_type_def(((SimpleTypeNode *)type_node)->type,
                                      context);
  }
  return type_node;
}

SymbolEntry *get_primitive_type(SymbolEntry *type_symbol) {
  if (type_symbol && type_symbol->kind == SYMBOL_TYPE_ALIAS) {
    return type_symbol->info.type_info.aliased_type;
  }
  return type_symbol;
}

static bool check_type_compatibility(ASTNode *dest_type, ASTNode *src_type,
                                     CompilerContext *context) {

  ASTNode *dest_def = resolve_to_actual_type_def(dest_type, context);
  ASTNode *src_def = resolve_to_actual_type_def(src_type, context);

  if (!dest_def || !src_def) {
    return false;
  }

  if (dest_def == src_def || dest_def->type == src_def->type) {
    return true;
  }

  switch (dest_def->type) {

  case NODE_TYPE_IDENTIFIER: {
    TypeIdentifierNode *dest_tid = (TypeIdentifierNode *)dest_def;
    // IdentifierNode *dest_id = (IdentifierNode *)dest_tid->id;

    if (src_def->type != NODE_TYPE_IDENTIFIER) {
      break;
    }

    SymbolEntry *dest_symbol = resolve_to_type_symbol(dest_type, context);
    SymbolEntry *src_symbol = resolve_to_type_symbol(src_type, context);

    if (!dest_symbol || !src_symbol)
      return false;

    if (dest_symbol->tag == LITERAL_REAL &&
        src_symbol->tag == LITERAL_INTEGER) {
      return true;
    }

    if (dest_symbol->tag == LITERAL_STRING && src_symbol->tag == LITERAL_CHAR) {
      return true;
    }

    if (dest_symbol->tag == src_symbol->tag) {
      return true;
    }

    break;
  }

  case NODE_SUBRANGE_TYPE: {
    SubrangeTypeNode *dest_sub = (SubrangeTypeNode *)dest_def;
    return check_type_compatibility(dest_sub->upper, src_type, context);
  }

  case NODE_SET_TYPE: {
    if (src_def->type == NODE_TYPE_IDENTIFIER) {
      TypeIdentifierNode *src_tid = (TypeIdentifierNode *)src_def;
      IdentifierNode *src_id = (IdentifierNode *)src_tid->id;
      LOG_DEBUG("tentar buscar algo que define ele como node set type.");
      SymbolEntry *src_symbol = resolve_to_type_symbol(src_type, context);
      LOG_DEBUG("Symbol Name: %s, Symbol Kind? %s", src_symbol->name,
                src_id->name);
    }
    if (src_def->type != NODE_SET_TYPE)
      return false;

    SetTypeNode *dest_set = (SetTypeNode *)dest_def;
    SetTypeNode *src_set = (SetTypeNode *)src_def;

    LOG_DEBUG("problema que não deveria. %s - %s",
              get_node_type_name(dest_set->type->type),
              get_node_type_name(src_set->type->type));

    return check_type_compatibility(dest_set->type, src_set->type, context);
  }

  case NODE_STRUCTURED_TYPE: {
    LOG_DEBUG("NODE_STRUCTURED_TYPE com ? %s",
              get_node_type_name(src_def->type));
    break;
  }
  case NODE_SIMPLE_TYPE: {
    LOG_DEBUG("NODE_SIMPLE_TYPE com ? %s", get_node_type_name(src_def->type));
    break;
  }
  case NODE_RECORD_TYPE:
  case NODE_ARRAY_TYPE:
  case NODE_ENUMERATED_TYPE:
    return false;

  default:
    break;
  }

  return false;
}

static bool check_signature_compatibility(ASTNode *expected_param_list,
                                          SymbolEntry *provided_func_symbol,
                                          CompilerContext *context) {
  ListNode *expected_sections =
      expected_param_list
          ? (ListNode *)((ParameterNode *)expected_param_list)->params_list
          : NULL;
  ASTNode *provided_params_node = provided_func_symbol->info.func_info.params;
  ListNode *provided_sections =
      provided_params_node
          ? (ListNode *)((ParameterNode *)provided_params_node)->params_list
          : NULL;

  while (expected_sections && provided_sections) {
    FormalParameterSectionNode *expected =
        (FormalParameterSectionNode *)expected_sections->element;
    FormalParameterSectionNode *provided =
        (FormalParameterSectionNode *)provided_sections->element;

    if (expected->kind != provided->kind) {
      return false;
    }

    if (!check_type_compatibility(expected->type, provided->type, context)) {
      return false;
    }

    ListNode *expected_ids = (ListNode *)expected->identifiers;
    ListNode *provided_ids = (ListNode *)provided->identifiers;
    while (expected_ids && provided_ids) {
      expected_ids = (ListNode *)expected_ids->next;
      provided_ids = (ListNode *)provided_ids->next;
    }
    if (expected_ids != NULL || provided_ids != NULL) {
      return false;
    }

    expected_sections = (ListNode *)expected_sections->next;
    provided_sections = (ListNode *)provided_sections->next;
  }

  if (expected_sections != NULL || provided_sections != NULL) {
    return false;
  }

  return true;
}

static int count_list_nodes(ASTNode *list_node) {
  int count = 0;
  ListNode *current = (ListNode *)list_node;
  while (current) {
    if (current->element) {
      count++;
    }
    current = (ListNode *)current->next;
  }
  return count;
}

static bool get_bounds_from_type(ASTNode *type_node, CompilerContext *context,
                                 DimensionBounds *out_bounds) {
  if (!type_node)
    return false;

  if (type_node->type == NODE_TYPE_IDENTIFIER) {
    IdentifierNode *id = ((TypeIdentifierNode *)type_node)->id;
    SymbolEntry *type_symbol = context_lookup(context, id->name);
    if (type_symbol && type_symbol->kind == SYMBOL_TYPE) {
      return get_bounds_from_type(type_symbol->info.type_info.definition,
                                  context, out_bounds);
    }
    return false;
  }

  if (type_node->type == NODE_SUBRANGE_TYPE) {
    SubrangeTypeNode *sr_node = (SubrangeTypeNode *)type_node;
    ConstantValue lower = evaluate_constant(context, sr_node->lower);
    ConstantValue upper = evaluate_constant(context, sr_node->upper);

    out_bounds->lower = lower.value.int_val;
    out_bounds->upper = upper.value.int_val;
    return true;
  }

  return false;
}

static void analyze_call_parameters(ASTNode *call_args_list,
                                    CompilerContext *context) {
  if (!context->current_function)
    return;

  SymbolEntry *func_symbol = context->current_function;

  if (func_symbol->kind == SYMBOL_BUILTIN ||
      func_symbol->kind == SYMBOL_BUILTIN_FUNCTION) {
    ListNode *call_args = (ListNode *)call_args_list;
    while (call_args) {
      if (call_args->element) {
        analyze_expression(call_args->element, context);
      }
      call_args = (ListNode *)call_args->next;
    }
    return;
  }

  if (func_symbol->info.func_info.params == NULL) {
    if (call_args_list != NULL) {
      yyerrorf(call_args_list->location,
               "Function '%s' expects no arguments, but received some.",
               func_symbol->name);
    }
    return;
  }

  ListNode *current_arg_node = (ListNode *)call_args_list;
  ListNode *current_param_section_node = NULL;

  if (func_symbol->info.func_info.params != NULL) {
    current_param_section_node =
        (ListNode *)((ParameterNode *)func_symbol->info.func_info.params)
            ->params_list;
  }

  while (current_param_section_node) {
    FormalParameterSectionNode *param_section =
        (FormalParameterSectionNode *)current_param_section_node->element;

    ListNode *param_ids = (ListNode *)param_section->identifiers;
    while (param_ids) {
      if (current_arg_node == NULL) {
        yyerrorf(func_symbol->info.func_info.params->location,
                 "Too few arguments in call to '%s'.", func_symbol->name);
        context->has_errors = true;
        return;
      }

      ASTNode *arg_expr = current_arg_node->element;

      if (param_section->kind == PARAM_VAR ||
          param_section->kind == PARAM_VALUE) {
        ASTNode *arg_type = analyze_expression(arg_expr, context);
        if (!check_type_compatibility(param_section->type, arg_type, context)) {
          yyerrorf(arg_expr->location, "Type mismatch for parameter.");
          context->has_errors = true;
        }

        if (param_section->kind == PARAM_VAR &&
            (arg_expr->type == NODE_LITERAL ||
             arg_expr->type == NODE_BINARY_EXPR)) {
          yyerrorf(arg_expr->location,
                   "An L-value (variable) is expected for a VAR parameter.");
          context->has_errors = true;
        }
      } else if (param_section->kind == PARAM_PROCEDURE ||
                 param_section->kind == PARAM_FUNCTION) {
        if (arg_expr->type != NODE_IDENTIFIER) {
          yyerrorf(arg_expr->location,
                   "An identifier of a procedure/function is expected here.");
          context->has_errors = true;
        } else {
          IdentifierNode *arg_id = (IdentifierNode *)arg_expr;
          SymbolEntry *passed_func_symbol =
              context_lookup(context, arg_id->name);

          if (!passed_func_symbol) {
            yyerrorf(arg_expr->location,
                     "Undeclared identifier '%s' passed as a "
                     "procedure/function parameter.",
                     arg_id->name);
          } else {
            SymbolKind expected_kind = (param_section->kind == PARAM_PROCEDURE)
                                           ? SYMBOL_PROCEDURE
                                           : SYMBOL_FUNCTION;
            if (passed_func_symbol->kind != expected_kind) {
              yyerrorf(arg_expr->location,
                       "Parameter kind mismatch. Expected a %s but got a %s.",
                       get_symbol_kind_name(expected_kind),
                       get_symbol_kind_name(passed_func_symbol->kind));
            }

            if (!check_signature_compatibility(param_section->parameters,
                                               passed_func_symbol, context)) {
              yyerrorf(arg_expr->location,
                       "The signature of '%s' does not match the expected "
                       "parameter signature.",
                       passed_func_symbol->name);
              context->has_errors = true;
            }
          }
        }
      }

      param_ids = (ListNode *)param_ids->next;
      current_arg_node = (ListNode *)current_arg_node->next;
    }

    current_param_section_node = (ListNode *)current_param_section_node->next;
  }

  if (current_arg_node != NULL) {
    yyerrorf(current_arg_node->base.location,
             "Too many arguments in call to '%s'.", func_symbol->name);
  }
}

void analyze_labels(ASTNode *label, CompilerContext *context) {
  if (label == NULL)
    return;

  if (label->type != NODE_LIST) {
    ListNode *new_list = xalloc(1, sizeof(ListNode));
    new_list->base.type = NODE_LIST;
    new_list->base.location = label->location;
    new_list->element = label;
    new_list->next = NULL;
    label = (ASTNode *)new_list;
  }

  ListNode *curr = (ListNode *)label;
  while (curr) {
    if (curr->element) {
      LabelDeclarationNode *ld = (LabelDeclarationNode *)curr->element;
      switch (ld->value->type) {
      case NODE_LITERAL: {
        LiteralNode *l = (LiteralNode *)ld->value;
        char id[255];
        if (l->literal_type == LITERAL_INTEGER) {
          sprintf(id, "Label%d", l->value.int_val);
        } else {
          yyerrorf(curr->element->location,
                   "Label cannot to be different from integer val");
          context->has_errors = true;
        }

        SymbolEntry *s = create_symbol_entry(strdup(id), SYMBOL_LABEL,
                                             context->scope_stack->scope_level,
                                             ld->base.location);
        LOG_DEBUG("vamos colocar na symbol table o id %s", id);
        context_insert(context, strdup(id), s);
        break;
      }
      default:
        yyerrorf(curr->element->location, "%s not mapped here (%d)",
                 get_node_type_name(ld->value->type), __LINE__);
        break;
      }
    }

    curr = (ListNode *)curr->next;
  }
}

void analyze_constants(ASTNode *constant, CompilerContext *context) {
  if (constant == NULL)
    return;

  if (constant->type != NODE_LIST) {
    ListNode *new_list = xalloc(1, sizeof(ListNode));
    new_list->base.type = NODE_LIST;
    new_list->base.location = constant->location;
    new_list->element = constant;
    new_list->next = NULL;
    constant = (ASTNode *)new_list;
  }

  ListNode *curr = (ListNode *)constant;
  while (curr) {
    if (curr->element) {
      ConstDeclarationNode *const_node = (ConstDeclarationNode *)curr->element;
      IdentifierNode *id = (IdentifierNode *)const_node->identifier;
      SymbolEntry *s = create_symbol_entry(id->name, SYMBOL_CONSTANT,
                                           context->scope_stack->scope_level,
                                           const_node->base.location);
      s->info.const_info.definition = const_node->const_expr;
      id->symbol = s;

      ConstantValue v = evaluate_constant(context, const_node->const_expr);

      switch (v.type) {
      case CONST_INTEGER:
        s->info.const_info.value =
            create_integer_literal(v.value.int_val, const_node->base.location);
        break;
      case CONST_REAL:
        s->info.const_info.value =
            create_real_literal(v.value.real_val, const_node->base.location);
        break;
      case CONST_STRING:
        s->info.const_info.value =
            create_string_literal(v.value.str_val, const_node->base.location);
        break;
      case CONST_CHAR:
        s->info.const_info.value =
            create_char_literal(v.value.char_val, const_node->base.location);
        break;
      case CONST_BOOLEAN:
        s->info.const_info.value =
            create_boolean_literal(v.value.bool_val, const_node->base.location);
        break;
      default:
        break;
      }

      context_insert(context, id->name, s);
    }

    curr = (ListNode *)curr->next;
  }
}

void analyze_types(ASTNode *types, CompilerContext *context) {
  if (types == NULL)
    return;

  if (types->type != NODE_LIST) {
    ListNode *new_list = xalloc(1, sizeof(ListNode));
    new_list->base.type = NODE_LIST;
    new_list->base.location = types->location;
    new_list->element = types;
    new_list->next = NULL;
    types = (ASTNode *)new_list;
  }

  ListNode *curr = (ListNode *)types;
  while (curr) {
    if (curr->element) {
      TypeDeclarationNode *td = (TypeDeclarationNode *)curr->element;
      TypeIdentifierNode *tid = (TypeIdentifierNode *)td->identifier;
      IdentifierNode *id = (IdentifierNode *)tid->id;
      ASTNode *type_expr_def =
          resolve_to_actual_type_def(td->type_expr, context);

      if (type_expr_def->type == NODE_ENUMERATED_TYPE) {
        EnumeratedTypeNode *enum_type = (EnumeratedTypeNode *)type_expr_def;
        ListNode *list = (ListNode *)enum_type->identifiers_list;

        SymbolEntry *s = create_symbol_entry(id->name, SYMBOL_TYPE,
                                             context->scope_stack->scope_level,
                                             type_expr_def->location);

        s->info.type_info.definition = type_expr_def;
        s->info.type_info.fields = NULL;
        s->info.type_info.aliased_type = NULL;

        context_insert(context, id->name, s);

        id->symbol = s;
        tid->symbol = s;

        while (list) {
          if (list->element) {
            IdentifierNode *e_id = (IdentifierNode *)list->element;

            SymbolEntry *e_symbol = create_symbol_entry(
                e_id->name, SYMBOL_ENUM_VALUE,
                context->scope_stack->scope_level, list->element->location);

            e_symbol->info.type_info.definition = type_expr_def;
            e_symbol->info.type_info.fields = NULL;
            e_symbol->info.type_info.aliased_type = NULL;

            context_insert(context, e_id->name, e_symbol);

            e_id->symbol = e_symbol;
          }
          list = (ListNode *)list->next;
        }
      } else {
        SymbolEntry *s = create_symbol_entry(id->name, tid->kind,
                                             context->scope_stack->scope_level,
                                             td->base.location);

        s->info.type_info.definition = td->type_expr;
        s->info.type_info.fields = NULL;
        s->info.type_info.aliased_type = NULL;

        SymbolEntry *type_expr_symbol =
            resolve_to_type_symbol(type_expr_def, context);
        if (type_expr_symbol && type_expr_symbol->kind == SYMBOL_BUILTIN) {
          ASTNode *l = resolve_to_actual_type_def(
              type_expr_symbol->info.type_info.definition, context);
          SymbolEntry *l_symb = resolve_to_type_symbol(l, context);
          s->info.type_info.aliased_type = create_symbol_entry(
              id->name, SYMBOL_TYPE_ALIAS, context->scope_stack->scope_level,
              td->base.location);
          s->info.type_info.aliased_type->tag =
              get_literal_type_from_name(l_symb->name);
        }

        id->symbol = s;
        tid->symbol = id->symbol;

        LOG_DEBUG("Estamos colocando na tabela de símbolos: %s e o símbolo ki"
                  "nd: %s\n",
                  id->name, get_symbol_kind_name(s->kind));

        context_insert(context, id->name, s);

        if (type_expr_def->type == NODE_RECORD_TYPE) {
          analyze_record_fields(s, context);
        } else if (type_expr_def->type == NODE_ARRAY_TYPE) {
          analyze_array_bounds(type_expr_def, s, context);
        }
      }
    }

    curr = (ListNode *)curr->next;
  }
}

void analyze_variables(ASTNode *variables, CompilerContext *context) {
  if (variables == NULL)
    return;

  if (variables->type != NODE_LIST) {
    ListNode *new_list = xalloc(1, sizeof(ListNode));
    new_list->base.type = NODE_LIST;
    new_list->base.location = variables->location;
    new_list->element = variables;
    new_list->next = NULL;
    variables = (ASTNode *)new_list;
  }

  ListNode *vars = (ListNode *)variables;

  int offset = 0;
  int index = 0;
  while (vars) {
    if (vars->element) {
      VarDeclarationNode *variable = (VarDeclarationNode *)vars->element;
      ListNode *curr = (ListNode *)variable->var_list;
      while (curr) {
        if (curr->element) {
          IdentifierNode *id = (IdentifierNode *)curr->element;
          SymbolEntry *s = create_symbol_entry(
              id->name, SYMBOL_VARIABLE, context->scope_stack->scope_level,
              vars->base.location);

          s->info.var_info.type = variable->type_node;

          ASTNode *def =
              resolve_to_actual_type_def(variable->type_node, context);
          SymbolEntry *def_symbol = resolve_to_type_symbol(def, context);

          if (def_symbol && def_symbol->kind == SYMBOL_BUILTIN &&
              strcmp(def_symbol->name, "string") == 0) {
            need_string_helpers = true;
          }

          if (def && def->type == NODE_ARRAY_TYPE) {
            analyze_array_bounds(def, s, context);
          }

          s->info.var_info.offset = offset + index;
          s->info.var_info.is_ref = false;
          id->symbol = s;
          context_insert(context, id->name, s);
        }

        curr = (ListNode *)curr->next;
        offset++;
      }
    }

    vars = (ListNode *)vars->next;
    index++;
  }
}

static int analyze_parameter_section(FormalParameterSectionNode *param,
                                     CompilerContext *context) {
  if (param == NULL) {
    return 0;
  }

  if (param->kind == PARAM_VALUE || param->kind == PARAM_VAR) {
    ListNode *identifiers = (ListNode *)param->identifiers;
    int id_count = 0;

    while (identifiers) {
      IdentifierNode *id = (IdentifierNode *)identifiers->element;
      if (id) {
        SymbolEntry *s_p = create_symbol_entry(
            id->name, SYMBOL_PARAMETER, context->scope_stack->scope_level,
            param->base.location);
        s_p->info.var_info.is_ref = (param->kind == PARAM_VAR);
        s_p->info.var_info.type = param->type;

        context_insert(context, id->name, s_p);

        ASTNode *def = resolve_to_actual_type_def(param->type, context);

        if (def->type == NODE_ARRAY_TYPE) {
          analyze_array_bounds(def, s_p, context);
        }

        id_count++;
      }
      identifiers = (ListNode *)identifiers->next;
    }
    return id_count;
  }

  if (param->kind == PARAM_FUNCTION || param->kind == PARAM_PROCEDURE) {
    IdentifierNode *func_param_id =
        (IdentifierNode *)((ListNode *)param->identifiers)->element;
    if (!func_param_id)
      return 0;

    SymbolEntry *s_p = create_symbol_entry(
        func_param_id->name,
        (param->kind == PARAM_FUNCTION) ? SYMBOL_FUNCTION : SYMBOL_PROCEDURE,
        context->scope_stack->scope_level, param->base.location);

    s_p->info.func_info.return_type = param->return_type;
    s_p->info.func_info.params = (ASTNode *)param->parameters;

    context_insert(context, func_param_id->name, s_p);
    return 1;
  }

  return 0;
}

static void analyze_functions(ASTNode *funcs, CompilerContext *context) {
  if (funcs == NULL)
    return;

  if (funcs->type != NODE_LIST) {
    ListNode *new_list = xalloc(1, sizeof(ListNode));
    new_list->base.type = NODE_LIST;
    new_list->base.location = funcs->location;
    new_list->element = funcs;
    new_list->next = NULL;
    funcs = (ASTNode *)new_list;
  }

  ListNode *curr = (ListNode *)funcs;
  while (curr) {
    if (curr->element) {

      FuncDeclarationNode *fd = (FuncDeclarationNode *)curr->element;
      IdentifierNode *id = (IdentifierNode *)fd->identifier;

      SymbolEntry *s = context_lookup(context, id->name);
      if (!s) {
        s = create_symbol_entry(id->name, id->kind,
                                context->scope_stack->scope_level,
                                fd->base.location);
        s->info.func_info.return_type = fd->type;
        s->info.func_info.params = fd->parameters;
        s->info.func_info.body = fd->block_or_forward;
        s->info.func_info.is_forward =
            fd->block_or_forward->type == NODE_FORWARD_DECL;
        context_insert(context, id->name, s);
      }
      id->symbol = s;

      scope_stack_push(context->scope_stack);
      context->current_function = s;

      if (fd->parameters && fd->parameters->type == NODE_PARAMETER) {
        ParameterNode *parameters_node = (ParameterNode *)fd->parameters;
        ListNode *params_list = (ListNode *)parameters_node->params_list;

        while (params_list) {
          if (params_list->element) {
            FormalParameterSectionNode *param_section =
                (FormalParameterSectionNode *)params_list->element;
            analyze_parameter_section(param_section, context);
          }
          params_list = (ListNode *)params_list->next;
        }
      }

      if (fd->block_or_forward && fd->block_or_forward->type == NODE_BLOCK) {
        BlockNode *block = (BlockNode *)fd->block_or_forward;

        if (block->constants)
          analyze_constants(block->constants, context);
        if (block->types)
          analyze_types(block->types, context);
        if (block->variables)
          analyze_variables(block->variables, context);

        if (block->procs_funcs)
          analyze_functions(block->procs_funcs, context);

        analyze_statement(block->statements, context);
      }

      scope_stack_pop(context->scope_stack);
      context->current_function = NULL;
    }
    curr = (ListNode *)curr->next;
  }
}

// void analyze_statement(ASTNode *statement, CompilerContext *context) {
//   switch (statement->type) {
//   case NODE_LITERAL: {
//     break;
//   }
//   case NODE_LABEL_DECL: {
//     analyze_labels(statement, context);
//     break;
//   }
//   case NODE_PROC_DECL:
//   case NODE_FUNC_DECL: {
//     analyze_functions(statement, context);
//     break;
//   }
//   case NODE_FORWARD_DECL: {
//     break;
//   }
//   case NODE_ENUMERATED_TYPE: {
//     break;
//   }
//   case NODE_SUBRANGE_TYPE: {
//     break;
//   }
//   case NODE_STRUCTURED_TYPE: {
//     break;
//   }
//   case NODE_SIMPLE_TYPE: {
//     break;
//   }
//   case NODE_ARRAY_TYPE: {
//     break;
//   }
//   case NODE_RECORD_TYPE: {
//     break;
//   }
//   case NODE_SET_TYPE: {
//     break;
//   }
//   case NODE_FILE_TYPE: {
//     break;
//   }
//   case NODE_POINTER_TYPE: {
//     break;
//   }
//   case NODE_POINTER_DEREF: {
//     break;
//   }
//   case NODE_COMPOUND_STMT: {
//     break;
//   }
//   case NODE_ASSIGN_STMT: {
//     AssignmentNode *ass = (AssignmentNode *)statement;
//     analyze_statement(ass->target, context);
//     analyze_statement(ass->expression, context);
//
//     if (ass->target->type == NODE_IDENTIFIER) {
//       IdentifierNode *id = (IdentifierNode *)ass->target;
//       char err[255];
//       switch (id->kind) {
//       case SYMBOL_VARIABLE:
//       case SYMBOL_LOCAL_VAR:
//       case SYMBOL_GLOBAL_VAR:
//       case SYMBOL_PARAMETER:
//       case SYMBOL_VAR_PARAM:
//       case SYMBOL_FIELD:
//         break;
//       case SYMBOL_FUNCTION:
//         if (context->current_function &&
//             strcmp(context->current_function->name, id->name) != 0) {
//           sprintf(err,
//                   "Only is possible to assign to %s (%s) as a return type
//                   of " "function.", get_symbol_kind_name(id->kind),
//                   id->name);
//           yyerror(err);
//
// context->has_errors = true;           break;
//         }
//         break;
//       case SYMBOL_CONSTANT:
//       case SYMBOL_TYPE:
//       case SYMBOL_ENUM_VALUE:
//       case SYMBOL_PROCEDURE:
//         sprintf(err, "Cannot assign to %s (%s -> not a variable)",
//                 get_symbol_kind_name(id->kind), id->name);
//         yyerror(err);
//
// context->has_errors = true;         break;
//         break;
//       case SYMBOL_UNKNOWN:
//         sprintf(err, "Identifier not resolved: %s", id->name);
//         yyerror(err);
//
// context->has_errors = true;         break;
//         break;
//       default:
//         yyerror("Invalid assignment target");
//
// context->has_errors = true;         break;
//         break;
//       }
//     }
//     break;
//   }
//   case NODE_FUNC_CALL:
//   case NODE_PROC_CALL: {
//     FunctionCallNode *func = (FunctionCallNode *)statement;
//     IdentifierNode *id = (IdentifierNode *)func->function;
//
//     if (id->kind == SYMBOL_BUILTIN) {
//       SymbolEntry *s = context_lookup(context, id->name);
//
//       if (!s) {
//         s = create_symbol_entry(id->name, SYMBOL_BUILTIN, 0,
//                                 func->base.location);
//
//         context_insert(context, id->name, s);
//       }
//
//       s->info.func_info.return_type = NULL;
//       s->info.func_info.params = func->params;
//
//       id->symbol = s;
//     }
//
//     analyze_statement(func->function, context);
//     analyze_statement(func->params, context);
//
//     SymbolEntry *s = context_lookup(context, id->name);
//     id->symbol = s;
//
//     break;
//   }
//   case NODE_IF_STMT: {
//     IfNode *if_stmt = (IfNode *)statement;
//     analyze_statement(if_stmt->condition, context);
//     analyze_statement(if_stmt->then_stmt, context);
//     if (if_stmt->else_stmt != NULL)
//       analyze_statement(if_stmt->else_stmt, context);
//     break;
//   }
//   case NODE_CASE_STMT: {
//     break;
//   }
//   case NODE_CASE_ITEM: {
//     break;
//   }
//   case NODE_CASE_LABEL: {
//     break;
//   }
//   case NODE_CASE_ELSE: {
//     break;
//   }
//   case NODE_WHILE_STMT: {
//     WhileStmtNode *while_stmt = (WhileStmtNode *)statement;
//     analyze_statement(while_stmt->condition, context);
//     analyze_statement(while_stmt->body, context);
//     break;
//   }
//   case NODE_REPEAT_STMT: {
//     RepeatUntilNode *repeat = (RepeatUntilNode *)statement;
//     analyze_statement(repeat->condition, context);
//     analyze_statement(repeat->body, context);
//     break;
//   }
//   case NODE_FOR_STMT: {
//     ForStmtNode *for_stmt = (ForStmtNode *)statement;
//     analyze_statement(for_stmt->start_expr, context);
//     analyze_statement(for_stmt->end_expr, context);
//     analyze_statement(for_stmt->variable, context);
//     analyze_statement(for_stmt->body, context);
//     break;
//   }
//   case NODE_WITH_STMT: {
//     WithNode *wi = (WithNode *)statement;
//     analyze_statement(wi->record_list, context);
//     analyze_statement(wi->body, context);
//     break;
//   }
//   case NODE_GOTO_STMT: {
//     break;
//   }
//   case NODE_LABELED_STMT: {
//     break;
//   }
//   case NODE_BINARY_EXPR: {
//     break;
//   }
//   case NODE_UNARY_EXPR: {
//     break;
//   }
//   case NODE_IDENTIFIER: {
//     IdentifierNode *id_node = (IdentifierNode *)statement;
//     SymbolEntry *entry = context_lookup(context, id_node->name);
//     if (entry == NULL) {
//       char err_msg[256];
//       sprintf(err_msg, "Undeclared identifier '%s'", id_node->name);
//       yyerror(err_msg);
//
// context->has_errors = true;       break;
//     } else {
//       id_node->symbol = entry;
//     }
//     break;
//   }
//   case NODE_MEMBER_ACCESS: {
//     MemberAccessNode *m_node = (MemberAccessNode *)statement;
//     if (context->current_function != NULL) {
//       analyze_statement(m_node->record, context);
//     }
//     break;
//   }
//   case NODE_ARRAY_ACCESS: {
//     ArrayAccessNode *arr = (ArrayAccessNode *)statement;
//     if (context->current_function != NULL) {
//       analyze_statement(arr->subscript_list, context);
//     }
//
//     break;
//   }
//   case NODE_SET_CONSTRUCTOR: {
//     break;
//   }
//   case NODE_TYPE_IDENTIFIER: {
//     TypeIdentifierNode *tid = (TypeIdentifierNode *)statement;
//     IdentifierNode *id = tid->id;
//     if (tid->kind == SYMBOL_TYPE) {
//       analyze_statement((ASTNode *)tid->id, context);
//     }
//     tid->symbol = id->symbol;
//     break;
//   }
//   case NODE_FIELD_LIST: {
//     break;
//   }
//   case NODE_RECORD_FIELD: {
//     break;
//   }
//   case NODE_INDEX_LIST: {
//     break;
//   }
//   case NODE_PARAMETER: {
//     ParameterNode *p = (ParameterNode *)statement;
//     analyze_statement(p->params_list, context);
//     break;
//   }
//   case NODE_VARIANT_RECORD: {
//     break;
//   }
//   case NODE_VARIANT_LIST: {
//     break;
//   }
//   case NODE_VARIANT_PART: {
//     break;
//   }
//   case NODE_TAG_FIELD: {
//     break;
//   }
//   case NODE_FIXED_PART: {
//     break;
//   }
//   case NODE_FORMAL_PARAM_SECTION: {
//     FormalParameterSectionNode *fp = (FormalParameterSectionNode
//     *)statement;
//     // TypeIdentifierNode *t_id = (TypeIdentifierNode *)fp->type; //
//     verificar
//     // os tipos
//
//     switch (fp->kind) {
//     case PARAM_FUNCTION:
//       analyze_statement(fp->parameters, context);
//       analyze_statement(fp->return_type, context);
//       break;
//     case PARAM_PROCEDURE:
//       analyze_statement(fp->parameters, context);
//       break;
//     case PARAM_VAR:
//     case PARAM_VALUE:
//       analyze_statement(fp->type, context);
//       analyze_statement(fp->identifiers, context);
//
//       ListNode *identifiers = (ListNode *)fp->identifiers;
//
//       while (identifiers) {
//         if (identifiers->element) {
//           IdentifierNode *id = (IdentifierNode *)identifiers->element;
//           SymbolEntry *s = context_lookup(context, id->name);
//
//           if (s) {
//             s->info.var_info.is_ref = fp->kind == PARAM_VAR;
//             id->symbol = s;
//           }
//         }
//
//         identifiers = (ListNode *)identifiers->next;
//       }
//
//       analyze_statement(fp->identifiers, context);
//       break;
//     }
//
//     break;
//   }
//   case NODE_LIST: {
//     ListNode *list = (ListNode *)statement;
//     while (list) {
//       if (list->element) {
//         analyze_statement(list->element, context);
//       }
//
//       list = (ListNode *)list->next;
//     }
//     break;
//   }
//   default:
//     printf("%s\n", get_node_type_name(statement->type));
//     break;
//   }
// }

static ASTNode *analyze_expression(ASTNode *expression,
                                   CompilerContext *context) {
  if (!expression)
    return NULL;

  switch (expression->type) {
  case NODE_SUBRANGE_TYPE: {
    LOG_DEBUG("COMO QUE CHEGA ATÉ AQUI ESSE NEGÓCIO? ");
    expression->result_type = expression;
    return expression->result_type;
    break;
  }
  case NODE_IDENTIFIER: {
    IdentifierNode *id = (IdentifierNode *)expression;
    if (id->symbol == NULL) {
      id->symbol = context_lookup(context, id->name);
    }

    if (id->symbol == NULL) {
      for (int i = context->with_stack_top - 1; i >= 0; i--) {
        ASTNode *with_record_symbol = context->with_stack[i];
        SymbolEntry *record_type_symbol =
            resolve_to_type_symbol(with_record_symbol->result_type, context);

        if (record_type_symbol && record_type_symbol->info.type_info.fields) {
          SymbolEntry *field_symbol = context_lookup_field(
              record_type_symbol->info.type_info.fields, id->name);

          if (field_symbol) {
            id->symbol = field_symbol;
            id->with_node = with_record_symbol;
            break;
          }
        }
      }
    }

    if (id->symbol == NULL) {
      yyerrorf(id->base.location, "Undeclared identifier '%s'", id->name);

      context->has_errors = true;
      break;
    }

    switch (id->symbol->kind) {
    case SYMBOL_VARIABLE:
    case SYMBOL_PARAMETER:
    case SYMBOL_FIELD:
      expression->result_type = id->symbol->info.var_info.type;
      break;
    case SYMBOL_ENUM_VALUE: {
      expression->result_type = id->symbol->info.type_info.definition;
      break;
    }
    case SYMBOL_CONSTANT:
      expression->result_type =
          analyze_expression(id->symbol->info.const_info.value, context);
      break;
    case SYMBOL_FUNCTION:
      expression->result_type = id->symbol->info.func_info.return_type;
      break;
    default:
      yyerrorf(id->base.location,
               "Identifier '%s' cannot be used in an expression.", id->name);
      expression->result_type = NULL;
      break;
    }
    return expression->result_type;
  }
  case NODE_LITERAL: {
    expression->result_type = get_type_from_literal(expression);
    return expression->result_type;
  }
  case NODE_FORMAL_PARAM_SECTION: {
    FormalParameterSectionNode *fp = (FormalParameterSectionNode *)expression;
    if (fp->kind == PARAM_VAR || fp->kind == PARAM_VALUE) {
      expression->result_type = fp->type;
    } else {
      expression->result_type = fp->return_type;
    }

    return expression->result_type;
  }
  case NODE_ARRAY_ACCESS: {
    ArrayAccessNode *a_node = (ArrayAccessNode *)expression;
    ASTNode *array_base_type = analyze_expression(a_node->array, context);
    ASTNode *array_def = resolve_to_actual_type_def(array_base_type, context);

    if (array_def && array_def->type == NODE_ARRAY_TYPE) {
      ASTNode *element_type = ((ArrayTypeNode *)array_def)->type;

      expression->result_type = element_type;
      return expression->result_type;
    } else if (array_def && array_def->type == NODE_SIMPLE_TYPE) {
      ASTNode *element_type = ((SimpleTypeNode *)array_def)->type;

      expression->result_type = element_type;
      return expression->result_type;
    }
    return NULL;
  }
  case NODE_MEMBER_ACCESS: {
    MemberAccessNode *m_node = (MemberAccessNode *)expression;
    ASTNode *record_expr_type = analyze_expression(m_node->record, context);

    if (!record_expr_type) {
      yyerrorf(m_node->base.location,
               "Could not determine the type of the record variable.");
      context->has_errors = true;
      break;
    }

    SymbolEntry *record_type_symbol =
        resolve_to_type_symbol(record_expr_type, context);

    if (!record_type_symbol || !record_type_symbol->info.type_info.fields) {
      yyerrorf(m_node->base.location,
               "Attempt to access a field on a non-record type.");
      context->has_errors = true;
      break;
    }

    IdentifierNode *field_id = (IdentifierNode *)m_node->field;
    SymbolEntry *field_symbol = context_lookup_field(
        record_type_symbol->info.type_info.fields, field_id->name);

    if (!field_symbol) {
      yyerrorf(expression->location,
               "Field '%s' not found in record type '%s'.", field_id->name,
               record_type_symbol->name);
      context->has_errors = true;
      break;
    }

    // analyze_expression(field_id, context)

    field_id->symbol = field_symbol;
    expression->result_type = field_symbol->info.var_info.type;
    return expression->result_type;
  }
  case NODE_UNARY_EXPR: {
    UnaryOperationNode *u_op = (UnaryOperationNode *)expression;

    ASTNode *operand_type = analyze_expression(u_op->operand, context);
    if (operand_type == NULL) {
      LOG_DEBUG("colocando result type = NULL (%d)", __LINE__);
      expression->result_type = NULL;
      return NULL;
    }

    SymbolEntry *operand_type_symbol =
        resolve_to_type_symbol(operand_type, context);
    if (operand_type_symbol == NULL) {
      yyerrorf(
          u_op->base.location,
          "Could not determine the type of the operand for unary operator.");
      expression->result_type = NULL;
      return NULL;
    }

    switch (u_op->op) {
    case UNOP_NOT:
      if (strcmp(operand_type_symbol->name, "boolean") != 0) {
        yyerrorf(u_op->base.location,
                 "Operator 'NOT' requires a BOOLEAN expression.");
      }
      expression->result_type =
          create_builtin_type_identifier("boolean", u_op->base.location);
      break;

    case UNOP_PLUS:
    case UNOP_MINUS:
      if (strcmp(operand_type_symbol->name, "integer") != 0 &&
          strcmp(operand_type_symbol->name, "real") != 0) {
        yyerrorf(u_op->base.location,
                 "Unary '+' or '-' requires a numeric expression.");
      }
      expression->result_type = operand_type;
      break;
    }
    return expression->result_type;
  }
  case NODE_BINARY_EXPR: {
    BinaryOperationNode *bin_op = (BinaryOperationNode *)expression;
    ASTNode *left_type = analyze_expression(bin_op->left, context);
    ASTNode *right_type = analyze_expression(bin_op->right, context);
    switch (bin_op->op) {
    case BINOP_IN:
    case BINOP_OR:
    case BINOP_AND:
    case BINOP_GT:
    case BINOP_GTE:
    case BINOP_LT:
    case BINOP_LTE:
    case BINOP_EQ: {
      SymbolEntry *boolean = context_lookup(context, "boolean");
      expression->result_type = boolean->info.type_info.definition;
      break;
    }
    case BINOP_PLUS: {
      ASTNode *l_def = resolve_to_actual_type_def(left_type, context);
      ASTNode *r_def = resolve_to_actual_type_def(right_type, context);

      if (l_def && r_def && l_def->type == r_def->type &&
          l_def->type == NODE_SET_TYPE) {
        expression->result_type = l_def;
        break;
      }

      SymbolEntry *l_symb = resolve_to_type_symbol(left_type, context);
      SymbolEntry *r_symb = resolve_to_type_symbol(right_type, context);

      const char *r_name = r_symb->tag != LITERAL_NIL
                               ? cast_from_literal_type_name(r_symb->tag)
                               : r_symb->name;
      const char *l_name = l_symb->tag != LITERAL_NIL
                               ? cast_from_literal_type_name(l_symb->tag)
                               : l_symb->name;

      if (l_symb && r_symb) {
        bool l_is_real = strcmp(l_name, "real") == 0;
        bool r_is_real = strcmp(r_name, "real") == 0;
        bool l_is_int = strcmp(l_name, "integer") == 0;
        bool r_is_int = strcmp(r_name, "integer") == 0;
        bool l_is_char = strcmp(l_name, "char") == 0;
        bool r_is_char = strcmp(r_name, "char") == 0;
        bool l_is_string = strcmp(l_name, "string") == 0;
        bool r_is_string = strcmp(r_name, "string") == 0;

        if (l_is_real || r_is_real) {
          SymbolEntry *real = context_lookup(context, "real");
          expression->result_type = real->info.type_info.definition;
        } else if (l_is_int && r_is_int) {
          SymbolEntry *integer = context_lookup(context, "integer");
          expression->result_type = integer->info.type_info.definition;
        } else if ((l_is_string || l_is_char) && (r_is_string || r_is_char)) {
          SymbolEntry *string = context_lookup(context, "string");
          expression->result_type = string->info.type_info.definition;
        } else {
          LOG_DEBUG("colocando result type = NULL (%d)", __LINE__);
          expression->result_type = NULL;
        }
      } else {
        LOG_DEBUG("colocando result type = NULL (%d)", __LINE__);
        expression->result_type = NULL;
      }

      LOG_DEBUG("colocando result type = NULL (%d)", __LINE__);
      break;
    }
    case BINOP_MINUS:
    case BINOP_DIVIDE:
    case BINOP_DIV:
    case BINOP_MOD:
    case BINOP_TIMES: {
      ASTNode *l_def = resolve_to_actual_type_def(left_type, context);
      ASTNode *r_def = resolve_to_actual_type_def(right_type, context);

      if (l_def && r_def && l_def->type == r_def->type &&
          l_def->type == NODE_SET_TYPE) {
        expression->result_type = l_def;
        break;
      }

      SymbolEntry *l_symb = resolve_to_type_symbol(left_type, context);
      SymbolEntry *r_symb = resolve_to_type_symbol(right_type, context);

      if (!l_symb || !r_symb) {
        LOG_DEBUG("colocando result type = NULL (%d)", __LINE__);
        expression->result_type = NULL;
        break;
      }

      const char *r_name = r_symb != NULL && r_symb->tag != LITERAL_NIL
                               ? cast_from_literal_type_name(r_symb->tag)
                               : r_symb->name;
      const char *l_name = r_symb != NULL && l_symb->tag != LITERAL_NIL
                               ? cast_from_literal_type_name(l_symb->tag)
                               : l_symb->name;

      if (l_symb && r_symb) {
        bool l_is_real = strcmp(l_name, "real") == 0;
        bool r_is_real = strcmp(r_name, "real") == 0;
        bool l_is_int = strcmp(l_name, "integer") == 0;
        bool r_is_int = strcmp(r_name, "integer") == 0;

        if (l_is_real || r_is_real) {
          expression->result_type =
              create_builtin_type_identifier("real", bin_op->base.location);
        } else if (l_is_int && r_is_int) {
          expression->result_type =
              create_builtin_type_identifier("integer", bin_op->base.location);
        } else {
          LOG_DEBUG("colocando result type = NULL (%d)", __LINE__);
          expression->result_type = NULL;
        }
      } else {
        LOG_DEBUG("colocando result type = NULL (%d)", __LINE__);
        expression->result_type = NULL;
      }

      break;
    }
    default:
      LOG_DEBUG("colocando result type = NULL (%d)", __LINE__);
      expression->result_type = NULL;
      break;
    }
    return expression->result_type;
  }
  case NODE_FUNC_CALL: {
    FunctionCallNode *f = (FunctionCallNode *)expression;
    IdentifierNode *id = (IdentifierNode *)f->function;
    SymbolEntry *id_symbol = context_lookup(context, id->name);

    if (!id_symbol || (id_symbol->kind != SYMBOL_FUNCTION &&
                       id_symbol->kind != SYMBOL_BUILTIN_FUNCTION)) {
      yyerrorf(id->base.location, "Identifier '%s' is not a function.",
               id->name);
      expression->result_type = NULL;
      return NULL;
    }

    id->symbol = id_symbol;

    context->current_function = id_symbol;
    analyze_call_parameters(f->params, context);
    context->current_function = NULL;

    expression->result_type = id_symbol->info.func_info.return_type;
    return expression->result_type;
  }
  case NODE_LIST: {
    ListNode *list = (ListNode *)expression;
    while (list) {
      if (list->element)
        analyze_expression(list->element, context);
      list = (ListNode *)list->next;
    }
    return NULL;
  }
  case NODE_TYPE_IDENTIFIER: {
    TypeIdentifierNode *tid = (TypeIdentifierNode *)expression;
    IdentifierNode *id = (IdentifierNode *)tid->id;
    if (tid->kind == SYMBOL_BUILTIN && strcmp(id->name, "string") == 0) {
      need_string_helpers = true;
    }
    break;
  }
  case NODE_ARRAY_TYPE: {
    ArrayTypeNode *array = (ArrayTypeNode *)expression;
    SymbolEntry *array_type_symbol =
        resolve_to_type_symbol(array->type, context);
    expression->result_type = array_type_symbol->info.type_info.definition;

    return expression->result_type;
  }
  case NODE_SET_CONSTRUCTOR: {
    SetLiteral *sl = (SetLiteral *)expression;
    ASTNode *base_type_node = NULL;

    if (sl->count > 0) {
      SetElement *first_element = (SetElement *)sl->elements[0];

      if (first_element->type == SET_ELEMENT_SINGLE) {
        if (first_element->value.single_value->type == NODE_LITERAL) {

          base_type_node =
              get_type_from_literal(first_element->value.single_value);
        } else {
          SymbolEntry *range_start_symbol =
              resolve_to_type_symbol(first_element->value.range.start, context);
          base_type_node = range_start_symbol->info.type_info.definition;
        }
      } else {
        SymbolEntry *range_start_symbol =
            resolve_to_type_symbol(first_element->value.range.start, context);
        base_type_node = range_start_symbol->info.type_info.definition;
        LOG_DEBUG("Base type node não existiu! SET_ELEMENT_RANGE %s",
                  range_start_symbol->name);
      }
    } else {
      LOG_DEBUG("Veio nulo porque o sl->count não é maior que 0");
      expression->result_type = NULL;
      return expression->result_type;
    }

    if (!base_type_node) {
      return NULL;
    }

    ASTNode *set_type_node =
        create_set_of_type_node(base_type_node, expression->location);

    expression->result_type = set_type_node;

    return expression->result_type;
  }
  case NODE_ENUMERATED_TYPE: {
    expression->result_type = expression;
    return expression->result_type;
    break;
  }
  default:
    return NULL;
  }
  return NULL;
}

static void analyze_statement(ASTNode *statement, CompilerContext *context) {
  if (!statement)
    return;

  switch (statement->type) {
  case NODE_FORWARD_DECL:
  case NODE_LITERAL:
  case NODE_IDENTIFIER:
    break;
  case NODE_CASE_STMT: {
    CaseNode *case_node = (CaseNode *)statement;
    ListNode *case_list = (ListNode *)case_node->case_list;

    ASTNode *result_type = analyze_expression(case_node->expr, context);
    SymbolEntry *result_type_symbol =
        resolve_to_type_symbol(result_type, context);

    while (case_list) {
      if (case_list->element) {
        CaseItemNode *item = (CaseItemNode *)case_list->element;
        ListNode *value_list = (ListNode *)item->value_list;

        while (value_list) {
          if (value_list->element) {
            ConstantNode *const_node = (ConstantNode *)value_list->element;
            if (!const_node->is_literal) {
              IdentifierNode *id = (IdentifierNode *)const_node->identifier;
              SymbolEntry *id_symbol = context_lookup(context, id->name);

              switch (const_node->const_type) {
              case CONST_INTEGER: {
                if (strcmp(result_type_symbol->name, "integer") != 0) {
                  yyerrorf(const_node->base.location,
                           "Incompatible type for case item.");
                }
                break;
              }
              case CONST_REAL: {
                if (strcmp(result_type_symbol->name, "real") != 0) {
                  yyerrorf(const_node->base.location,
                           "Incompatible type for case item.");
                }
                break;
              }
              case CONST_STRING: {
                if (strcmp(result_type_symbol->name, "string") != 0) {
                  yyerrorf(const_node->base.location,
                           "Incompatible type for case item.");
                }
                break;
              }
              case CONST_CHAR: {
                if (strcmp(result_type_symbol->name, "char") != 0) {
                  yyerrorf(const_node->base.location,
                           "Incompatible type for case item.");
                }
                break;
              }
              case CONST_BOOLEAN: {
                if (strcmp(result_type_symbol->name, "boolean") != 0) {
                  yyerrorf(const_node->base.location,
                           "Incompatible type for case item.");
                }
                break;
              }
              default:
                break;
              }
            } else {
              switch (const_node->const_type) {
              case CONST_INTEGER: {
                if (strcmp(result_type_symbol->name, "integer") != 0) {
                  yyerrorf(const_node->base.location,
                           "Incompatible type for case item.");
                }
                break;
              }
              case CONST_REAL: {
                if (strcmp(result_type_symbol->name, "real") != 0) {
                  yyerrorf(const_node->base.location,
                           "Incompatible type for case item.");
                }
                break;
              }
              case CONST_STRING: {
                if (strcmp(result_type_symbol->name, "string") != 0) {
                  yyerrorf(const_node->base.location,
                           "Incompatible type for case item.");
                }
                break;
              }
              case CONST_CHAR: {
                if (strcmp(result_type_symbol->name, "char") != 0) {
                  yyerrorf(const_node->base.location,
                           "Incompatible type for case item.");
                }
                break;
              }
              case CONST_BOOLEAN: {
                if (strcmp(result_type_symbol->name, "boolean") != 0) {
                  yyerrorf(const_node->base.location,
                           "Incompatible type for case item.");
                }
                break;
              }
              default:
                break;
              }
            }
          }

          value_list = (ListNode *)value_list->next;
        }

        analyze_statement(item->statement, context);
      }

      case_list = (ListNode *)case_list->next;
    }

    if (case_node->else_part)
      analyze_statement(case_node->else_part, context);
    break;
  }
  case NODE_CASE_ELSE: {
    CaseElseNode *case_else = (CaseElseNode *)statement;
    analyze_statement(case_else->stmt, context);
    break;
  }
  case NODE_ASSIGN_STMT: {
    AssignmentNode *ass = (AssignmentNode *)statement;
    if (ass->target->type == NODE_IDENTIFIER) {
      IdentifierNode *target_id = (IdentifierNode *)ass->target;

      if (context->current_function &&
          strcmp(context->current_function->name, target_id->name) == 0) {

        ASTNode *return_type =
            context->current_function->info.func_info.return_type;
        ASTNode *expr_type = analyze_expression(ass->expression, context);
        if (!check_type_compatibility(return_type, expr_type, context)) {
          yyerrorf(ass->base.location,
                   "Incompatible type for function return value.");
          context->has_errors = true;
        }
        break;
      }
    }

    ASTNode *target_type = analyze_expression(ass->target, context);
    ASTNode *expr_type = analyze_expression(ass->expression, context);

    if (!check_type_compatibility(target_type, expr_type, context)) {
      yyerrorf(ass->base.location, "Type mismatch in assignment.");

      context->has_errors = true;
      break;
    }
    break;
  }
  case NODE_FOR_STMT: {
    ForStmtNode *for_stmt = (ForStmtNode *)statement;
    analyze_expression(for_stmt->start_expr, context);
    analyze_expression(for_stmt->end_expr, context);
    analyze_expression(for_stmt->variable, context);
    analyze_statement(for_stmt->body, context);
    break;
  }
  case NODE_IF_STMT: {
    IfNode *if_stmt = (IfNode *)statement;
    ASTNode *cond_type = analyze_expression(if_stmt->condition, context);
    SymbolEntry *cond_type_sym = resolve_to_type_symbol(cond_type, context);

    if (cond_type_sym == NULL || strcmp(cond_type_sym->name, "boolean") != 0) {
      yyerrorf(if_stmt->condition->location,
               "A boolean expression is required for an IF condition.");
    }

    analyze_statement(if_stmt->then_stmt, context);
    analyze_statement(if_stmt->else_stmt, context);
    break;
  }
  case NODE_BLOCK: {
    BlockNode *block = (BlockNode *)statement;
    scope_stack_push(context->scope_stack);
    if (block->constants)
      analyze_constants(block->constants, context);
    if (block->types)
      analyze_types(block->types, context);
    if (block->variables)
      analyze_variables(block->variables, context);
    if (block->procs_funcs)
      analyze_functions(block->procs_funcs, context);
    analyze_statement(block->statements, context);
    scope_stack_pop(context->scope_stack);
    break;
  }
  case NODE_LIST: {
    ListNode *list = (ListNode *)statement;
    while (list) {
      analyze_statement(list->element, context);
      list = (ListNode *)list->next;
    }
    break;
  }
  case NODE_WHILE_STMT: {
    WhileStmtNode *while_stmt = (WhileStmtNode *)statement;
    ASTNode *cond_type = analyze_expression(while_stmt->condition, context);
    SymbolEntry *cond_type_sym = resolve_to_type_symbol(cond_type, context);

    if (cond_type_sym == NULL || strcmp(cond_type_sym->name, "boolean") != 0) {
      yyerror("A boolean expression is required for an WHILE condition.");
    }

    analyze_statement(while_stmt->body, context);
    break;
  }
  case NODE_PROC_CALL: {
    FunctionCallNode *func = (FunctionCallNode *)statement;
    IdentifierNode *id = (IdentifierNode *)func->function;
    SymbolEntry *s = context_lookup(context, id->name);

    if (id->kind == SYMBOL_BUILTIN) {
      if (!s) {
        s = create_symbol_entry(id->name, SYMBOL_BUILTIN_FUNCTION, 0,
                                func->base.location);

        context_insert(context, id->name, s);
      }

      s->info.func_info.return_type = NULL;
      s->info.func_info.params = func->params;
      s->info.func_info.body = NULL;

      id->symbol = s;
    }

    if (!s || (s->kind != SYMBOL_PROCEDURE && s->kind != SYMBOL_BUILTIN && s->kind != SYMBOL_BUILTIN_FUNCTION)) {
      yyerrorf(id->base.location, "Identifier '%s' is not a procedure. (%s)",
               id->name, get_symbol_kind_name(s->kind));
      break;
    }

    id->symbol = s;

    context->current_function = s;
    analyze_call_parameters(func->params, context);
    context->current_function = NULL;

    break;
  }
  case NODE_REPEAT_STMT: {
    RepeatUntilNode *repeat_stmt = (RepeatUntilNode *)statement;
    ASTNode *cond_type = analyze_expression(repeat_stmt->condition, context);
    SymbolEntry *cond_type_sym = resolve_to_type_symbol(cond_type, context);

    if (cond_type_sym == NULL || strcmp(cond_type_sym->name, "boolean") != 0)
      yyerror("A boolean expression is required for an REPEAT condition.");

    analyze_statement(repeat_stmt->body, context);

    break;
  }
  case NODE_FUNC_DECL:
  case NODE_PROC_DECL: {
    analyze_functions(statement, context);
    break;
  }
  case NODE_CONST_DECL: {
    analyze_constants(statement, context);
    break;
  }
  case NODE_TYPE_DECL: {
    analyze_types(statement, context);
    break;
  }
  case NODE_VAR_DECL: {
    analyze_variables(statement, context);
    break;
  }
  case NODE_PARAMETER: {
    ParameterNode *param = (ParameterNode *)statement;
    analyze_expression(param->params_list, context);
    break;
  }
  case NODE_WITH_STMT: {
    WithNode *with_node = (WithNode *)statement;

    ListNode *current_rec_var_node = (ListNode *)with_node->record_list;
    int pushed_records = 0;

    while (current_rec_var_node) {
      ASTNode *rec_var_expr = current_rec_var_node->element;

      ASTNode *type_node = analyze_expression(rec_var_expr, context);
      SymbolEntry *type_symbol = resolve_to_type_symbol(type_node, context);

      if (type_symbol && type_symbol->info.type_info.fields) {
        with_stack_push(context, rec_var_expr);
        pushed_records++;
      } else {
        yyerrorf(rec_var_expr->location,
                 "Variable in WITH statement is not a record type.");
        context->has_errors = true;
      }

      current_rec_var_node = (ListNode *)current_rec_var_node->next;
    }

    analyze_statement(with_node->body, context);

    for (int i = 0; i < pushed_records; i++) {
      with_stack_pop(context);
    }

    break;
  }
  case NODE_LABELED_STMT: {
    LabeledStmtNode *lb_stmt = (LabeledStmtNode *)statement;
    analyze_expression(lb_stmt->label, context);
    analyze_statement(lb_stmt->statement, context);
    break;
  }
  case NODE_GOTO_STMT: {
    GotoNode *got = (GotoNode *)statement;
    LiteralNode *l = (LiteralNode *)got->label;
    char id[255];
    if (l->literal_type == LITERAL_INTEGER) {
      sprintf(id, "Label%d", l->value.int_val);
    } else {
      yyerrorf(statement->location,
               "Label cannot to be different from integer val");
      context->has_errors = true;
    }

    SymbolEntry *got_symbol = context_lookup(context, id);

    if (!got_symbol) {
      yyerrorf(statement->location, "Undefined goto %s label", id);
      context->has_errors = true;
    }

    analyze_expression(got->label, context);

    break;
  }
  default:
    yyerrorf(statement->location,
             "O tipo %s não foi mapeado no analyze_statement",
             get_node_type_name(statement->type));
    break;
  }
}

static void analyze_array_bounds(ASTNode *array_def,
                                 SymbolEntry *array_type_symbol,
                                 CompilerContext *context) {
  ArrayTypeNode *array = (ArrayTypeNode *)array_def;
  IndexList *index_list = (IndexList *)array->index_list;

  array_type_symbol->info.var_info.num_dimensions = index_list->count;
  array_type_symbol->info.var_info.dimensions = xalloc(
      array_type_symbol->info.var_info.num_dimensions, sizeof(DimensionBounds));

  for (int i = 0; i < index_list->count; i++) {
    ASTNode *element = index_list->indexes[i];
    if (element->type == NODE_SUBRANGE_TYPE) {
      SubrangeTypeNode *sr_node = (SubrangeTypeNode *)element;
      ConstantValue lower = evaluate_constant(context, sr_node->lower);
      ConstantValue upper = evaluate_constant(context, sr_node->upper);
      DimensionBounds dim = {
          .lower = lower.value.int_val,
          .upper = upper.value.int_val,
      };
      array_type_symbol->info.var_info.dimensions[i].lower = dim.lower;
      array_type_symbol->info.var_info.dimensions[i].upper = dim.upper;
    } else if (element->type == NODE_ENUMERATED_TYPE) {
      EnumeratedTypeNode *enum_node = (EnumeratedTypeNode *)element;
      int count = count_list_nodes(enum_node->identifiers_list);

      if (count > 0) {
        array_type_symbol->info.var_info.dimensions[i].lower = 0;
        array_type_symbol->info.var_info.dimensions[i].upper = count - 1;
      } else {
        yyerrorf(element->location,
                 "Enumerated type used as array index cannot be empty.");
        context->has_errors = true;
      }
    } else if (element->type == NODE_TYPE_IDENTIFIER) {
      DimensionBounds resolved_bounds;
      if (get_bounds_from_type(element, context, &resolved_bounds)) {
        array_type_symbol->info.var_info.dimensions[i].lower =
            resolved_bounds.lower;
        array_type_symbol->info.var_info.dimensions[i].upper =
            resolved_bounds.upper;
      } else {
        yyerrorf(element->location,
                 "Type identifier '%s' cannot be resolved to a valid "
                 "array index range.",
                 ((TypeIdentifierNode *)element)->id->name);
        context->has_errors = true;
      }
    } else {
      yyerrorf(element->location, "era pra quebrar? %s",
               get_node_type_name(element->type));

      context->has_errors = true;
      break;
    }
  }
}

static void analyze_record_fields(SymbolEntry *record_type_symbol,
                                  CompilerContext *context) {
  ASTNode *result_type = resolve_to_actual_type_def(
      record_type_symbol->info.type_info.definition, context);
  if (!result_type || result_type->type != NODE_RECORD_TYPE)
    return;

  RecordTypeNode *r_node = (RecordTypeNode *)result_type;

  if (r_node->field_list) {
    FixedPartNode *fp =
        (FixedPartNode *)((FieldListNode *)r_node->field_list)->fixed_part;
    VariantPartNode *vp =
        (VariantPartNode *)((FieldListNode *)r_node->field_list)->variant_part;
    if (fp) {
      ListNode *field_decls = (ListNode *)fp->fields;
      while (field_decls) {
        RecordFieldNode *field_decl = (RecordFieldNode *)field_decls->element;
        ListNode *ids = (ListNode *)field_decl->field_list;
        while (ids) {
          IdentifierNode *id = (IdentifierNode *)ids->element;
          SymbolEntry *field_symbol = create_symbol_entry(
              id->name, SYMBOL_FIELD, record_type_symbol->scope_level + 1,
              id->base.location);
          field_symbol->info.var_info.type = field_decl->record_type;
          field_symbol->info.var_info.is_ref = false;
          field_symbol->info.var_info.offset = 0;
          context_insert_field(context, record_type_symbol, field_symbol);
          id->symbol = field_symbol;
          ids = (ListNode *)ids->next;

          SymbolEntry *field_type_symbol =
              resolve_to_type_symbol(field_decl->record_type, context);
          if (field_type_symbol->kind == SYMBOL_BUILTIN &&
              strcmp(field_type_symbol->name, "string") == 0) {
            need_string_helpers = true;
          }
        }
        field_decls = (ListNode *)field_decls->next;
      }
    }
    if (vp) {
      TagFieldNode *tag = (TagFieldNode *)vp->tag_field;
      IdentifierNode *tag_id = (IdentifierNode *)tag->field;

      SymbolEntry *tag_symbol = create_symbol_entry(
          tag_id->name, SYMBOL_FIELD, record_type_symbol->scope_level + 1,
          tag_id->base.location);
      tag_symbol->info.var_info.type = tag->tag_type;
      tag_symbol->info.var_info.is_ref = false;
      context_insert_field(context, record_type_symbol, tag_symbol);
      tag_id->symbol = tag_symbol;

      VariantListNode *v_list_node = (VariantListNode *)vp->variant_list;
      ListNode *variants = (ListNode *)v_list_node->variants;
      int variant_index = 0;

      while (variants) {
        if (!variants->element)
          break;

        VariantRecordNode *v_rec_node = (VariantRecordNode *)variants->element;
        ListNode *case_labels = (ListNode *)v_rec_node->case_labels;
        ConstantNode *xma = (ConstantNode *)case_labels->element;

        char variant_name_buffer[100];
        sprintf(variant_name_buffer, "variant_%s",
                ((IdentifierNode *)xma->identifier)->name);

        tag_symbol->info.var_info.offset = variant_index;
        v_rec_node->name = strdup(variant_name_buffer);

        if (v_rec_node->field_list) {
          FieldListNode *fl_node = (FieldListNode *)v_rec_node->field_list;
          FixedPartNode *fp_node = (FixedPartNode *)fl_node->fixed_part;
          ListNode *field_decls = (ListNode *)fp_node->fields;

          if (fp_node && fp_node->field_count > 0) {
            while (field_decls) {
              if (!field_decls->element)
                break;
              RecordFieldNode *field_decl =
                  (RecordFieldNode *)field_decls->element;
              ListNode *ids = (ListNode *)field_decl->field_list;
              while (ids) {
                if (!ids->element)
                  break;
                IdentifierNode *id = (IdentifierNode *)ids->element;
                SymbolEntry *field_symbol = create_symbol_entry(
                    id->name, SYMBOL_FIELD,
                    record_type_symbol->scope_level + 1 + variant_index,
                    id->base.location);
                field_symbol->info.var_info.type = field_decl->record_type;
                field_symbol->info.var_info.is_ref = false;
                field_symbol->info.var_info.offset = 0;

                char access_prefix[200];
                sprintf(access_prefix, "data.%s.", v_rec_node->name);
                field_symbol->info.var_info.variant_access_prefix =
                    strdup(access_prefix);

                context_insert_field(context, record_type_symbol, field_symbol);
                id->symbol = field_symbol;
                ids = (ListNode *)ids->next;

                SymbolEntry *field_type_symbol =
                    resolve_to_type_symbol(field_decl->record_type, context);
                if (field_type_symbol->kind == SYMBOL_BUILTIN &&
                    strcmp(field_type_symbol->name, "string") == 0) {
                  need_string_helpers = true;
                }
              }
              field_decls = (ListNode *)field_decls->next;
            }
          }
          variants = (ListNode *)variants->next;
          variant_index++;
        }
      }
    }
  }
}

void analyze_semantics(ASTNode *root_node, CompilerContext *context) {
  if (!root_node) {
    LOG_ERROR("AST root is NULL. Aborting analysis.");
    return;
  }

  LOG_TRACE("Iniciando Análise Semântica...");

  ProgramNode *program = (ProgramNode *)root_node;
  if (!program->block) {
    LOG_ERROR("Program block is NULL. Aborting analysis.");
    return;
  }
  BlockNode *block = (BlockNode *)program->block;

  LOG_TRACE("Passagem 1: Coletando declarações de topo...");
  /* ADDING BUILTIN TYPES TO GLOBAL CONTEXT */
  insert_builtin_types(context, program->base.location);
  if (block->labels) {
    analyze_labels(block->labels, context);
  }

  if (block->constants) {
    analyze_constants(block->constants, context);
  }

  if (block->types) {
    analyze_types(block->types, context);
  }

  if (block->variables) {
    analyze_variables(block->variables, context);
  }

  insert_builtin_funcs_and_procs(context, program->base.location);
  if (block->procs_funcs) {
    analyze_functions(block->procs_funcs, context);
  }

  if (block->statements) {
    analyze_statement(block->statements, context);
  }

  program->need_string_helpers = need_string_helpers;
  program->need_set_helpers = need_set_helpers;

  LOG_TRACE("Análise Semântica concluída.");
}
