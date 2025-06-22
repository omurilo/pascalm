#include "../commons.h"

void generate_string_definition(CodeGenerator *code_gen) {
  // definição do tipo `string`
  fprintf(code_gen->output_file, "typedef struct {\n");
  fprintf(code_gen->output_file, "    unsigned char length;\n");
  fprintf(code_gen->output_file, "    char data[255];\n");
  fprintf(code_gen->output_file, "} string;\n\n");
  fprintf(code_gen->output_file, "string make_string(const char* c_str);\n");
  fprintf(code_gen->output_file,
          "string concat_string(string s1, string s2);\n\n");
}

void generate_strings_helper_functions(CodeGenerator *code_gen) {
  // função para criar uma string
  fprintf(code_gen->output_file, "string make_string(const char* c_str) {\n");
  fprintf(code_gen->output_file, "    string ps;\n");
  fprintf(code_gen->output_file, "    ps.length = strlen(c_str);\n");
  fprintf(code_gen->output_file, "    if(ps.length > 255) ps.length = 255;\n");
  fprintf(code_gen->output_file, "    strncpy(ps.data, c_str, ps.length);\n");
  fprintf(code_gen->output_file, "    return ps;\n");
  fprintf(code_gen->output_file, "}\n\n");

  // função para concatenar duas strings
  fprintf(code_gen->output_file,
          "string concat_string(string s1, string s2) {\n");
  fprintf(code_gen->output_file, "    string result;\n");
  fprintf(code_gen->output_file,
          "    result.length = s1.length + s2.length;\n");
  fprintf(code_gen->output_file,
          "    if(result.length > 255) result.length = 255;\n");
  fprintf(code_gen->output_file,
          "    memcpy(result.data, s1.data, s1.length);\n");
  fprintf(code_gen->output_file, "    memcpy(result.data + s1.length, s2.data, "
                                 "result.length - s1.length);\n");
  fprintf(code_gen->output_file, "    return result;\n");
  fprintf(code_gen->output_file, "}\n\n");
}

void generate_set_helper_functions(CodeGenerator *code_gen) {
  // Função para verificar se set está vazio
  fprintf(code_gen->output_file, "int set_is_empty(unsigned long long s) {\n");
  fprintf(code_gen->output_file, "    return s == 0ULL;\n");
  fprintf(code_gen->output_file, "}\n\n");

  // Função para incluir elemento no set
  fprintf(
      code_gen->output_file,
      "unsigned long long set_include(unsigned long long s, int element) {\n");
  fprintf(code_gen->output_file, "    return s | (1ULL << element %% 64);\n");
  fprintf(code_gen->output_file, "}\n\n");

  // Função para excluir elemento do set
  fprintf(
      code_gen->output_file,
      "unsigned long long set_exclude(unsigned long long s, int element) {\n");
  fprintf(code_gen->output_file, "    return s & ~(1ULL << element %% 64);\n");
  fprintf(code_gen->output_file, "}\n\n");

  // Função para imprimir set (debug)
  fprintf(code_gen->output_file, "void print_set(unsigned long long s) {\n");
  fprintf(code_gen->output_file, "    fprintf(\"[\");\n");
  fprintf(code_gen->output_file, "    int first = 1;\n");
  fprintf(code_gen->output_file, "    for(int i = 0; i < 64; i++) {\n");
  fprintf(code_gen->output_file, "        if(s & (1ULL << i %% 64)) {\n");
  fprintf(code_gen->output_file, "            if(!first) fprintf(\", \");\n");
  fprintf(code_gen->output_file,
          "            fprintf(\"%%llu\", (1ULL << i %% 64));\n");
  fprintf(code_gen->output_file, "            first = 0;\n");
  fprintf(code_gen->output_file, "        }\n");
  fprintf(code_gen->output_file, "    }\n");
  fprintf(code_gen->output_file, "    fprintf(\"]\\n\");\n");
  fprintf(code_gen->output_file, "}\n\n");
}

void generate_array_helper_functions(CodeGenerator *code_gen) {
  fprintf(code_gen->output_file, "void check_array_bounds(int index, int low, "
                                 "int high, const char* array_name) {\n");
  fprintf(code_gen->output_file, "    if(index < low || index > high) {\n");
  fprintf(code_gen->output_file,
          "        fprintf(\"Array index out of bounds: %%d not in "
          "[%%d..%%d] for array %%s\\n\",\n");
  fprintf(code_gen->output_file,
          "                index, low, high, array_name);\n");
  fprintf(code_gen->output_file, "        exit(1);\n");
  fprintf(code_gen->output_file, "    }\n");
  fprintf(code_gen->output_file, "}\n\n");
}
