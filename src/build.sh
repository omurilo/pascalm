#!/bin/bash

# Script de build robusto para o compilador PascalM, inspirado em Makefile.
#
# Uso:
#   ./build.sh [comando]
#
# Comandos:
#   all (padrão) - Compila o compilador.
#   test         - Compila e executa um teste rápido.
#   compile-c    - Compila todos os arquivos de teste .pascalm para C e depois para binário.
#   parser       - Força a geração do lexer e do parser.
#   clean        - Limpa todos os artefatos de build.
#
# Variáveis de Ambiente:
#   DEBUG=1        - Ativa flags de debug (-g, sanitizers).
#   VERBOSE=1      - Ativa o modo verboso no compilador e no script.
#   SHOW_WARNINGS=1 - Mostra os warnings do GCC em vez de salvá-los em log.
#   FILE=<path>    - Define o arquivo para o comando 'test'.

# ===========================
# Configuração e Segurança
# ===========================
set -e # Encerra o script se qualquer comando falhar
set -o pipefail # Garante que falhas em pipelines sejam capturadas

# ===========================
# Configuração de Variáveis (com padrões)
# ===========================
CC="${CC:-gcc}"
TEST_DIR="${TEST_DIR:-../examples}" # Assumindo que a pasta tests está no nível de final_work
OUT_DIR="${OUT_DIR:-build/gen}"
BUILD_DIR="${BUILD_DIR:-build}"
TARGET="pascalm"
WARNING_LOG="${BUILD_DIR}/warnings.log"
FILE="${FILE:-$TEST_DIR/complex_parameters/test.pascalm}" # Um teste padrão que deve existir

SRC_DIRS="parser ast semantic-analyzer symbol-table code-generation stdlib utils"
MAIN_SRCS="main.c"
HEADERS=$(for d in $SRC_DIRS; do echo -n "-I$d "; done)

# ===========================
# Cores
# ===========================
COLOR_RESET='\033[0m'
COLOR_GREEN='\033[0;32m'
COLOR_BLUE='\033[0;34m'
COLOR_YELLOW='\033[1;33m'
COLOR_RED='\033[0;31m'
COLOR_CYAN='\033[0;36m'

# ===========================
# Flags de Compilação
# ===========================
CFLAGS="-Wall -Wextra $HEADERS -I."
BFLAGS="-d" # Flags do Bison
PASCALM_FLAGS="-f $FILE"

if [ "$DEBUG" = "1" ]; then
    CFLAGS+=" -g -fsanitize=address -fsanitize=undefined -DDEBUG"
    BUILD_TYPE="Debug"
    BFLAGS+=" -t -Wcounterexamples"
else
    CFLAGS+=" -O2"
    BUILD_TYPE="Release"
    BFLAGS+=" -Wcounterexamples"
fi

if [ "$VERBOSE" = "1" ]; then
    CFLAGS+=" -DVERBOSE_MODE"
    PASCALM_FLAGS+=" -v"
fi

# ===========================
# Controle de Verbosidade
# ===========================
# Silencia a saída ou a exibe, dependendo de SHOW_WARNINGS
if [ "$SHOW_WARNINGS" = "1" ] || [ "$DEBUG" = "1" ]; then
    REDIRECT_CMD=""
else
    # A mágica do 'eval' é necessária para que a string de redirecionamento funcione corretamente
    REDIRECT_CMD=">> $WARNING_LOG 2>&1"
fi

# Função auxiliar para rodar comandos com logging
run() {
    local message=$1
    local command=$2
    printf "${COLOR_CYAN}▶ $message${COLOR_RESET}\n"
    if ! eval "$command $REDIRECT_CMD"; then
        printf "${COLOR_RED}✖ Erro: O comando falhou -> $command${COLOR_RESET}\n"
        exit 1
    fi
}

# ===========================
# Funções de Build
# ===========================

prepare() {
    mkdir -p "$BUILD_DIR" "$OUT_DIR"
    touch "$WARNING_LOG"
}

generate_parser() {
    # Gera o parser com Bison se o .y for mais novo que o .c gerado
    if [ "parser/parser.y" -nt "parser/parser.tab.c" ]; then
        run "Gerando parser (bison)" "bison $BFLAGS -o parser/parser.tab.c parser/parser.y"
    fi

    # Gera o lexer com Flex se o .l ou o header do parser for mais novo
    if [ "parser/parser.l" -nt "parser/lex.yy.c" ] || [ "parser/parser.tab.h" -nt "parser/lex.yy.c" ]; then
        run "Gerando lexer (flex)" "flex -o parser/lex.yy.c parser/parser.l"
    fi
}

compile_objects() {
    # Encontra todos os arquivos .c
    ALL_SRCS=$(find $SRC_DIRS -name "*.c")
    ALL_SRCS+=" $MAIN_SRCS"
    
    OBJECTS=""
    for src_file in $ALL_SRCS; do
        obj_file="$BUILD_DIR/${src_file%.c}.o"
        OBJECTS+="$obj_file "
        
        # Cria o subdiretório de build se não existir
        mkdir -p "$(dirname "$obj_file")"
        
        # Compila apenas se o arquivo fonte for mais novo que o objeto
        if [ "$src_file" -nt "$obj_file" ] || ! [ -f "$obj_file" ]; then
            printf "${COLOR_BLUE}⚙️  Compilando $src_file${COLOR_RESET}\n"
            eval "$CC $CFLAGS -c $src_file -o $obj_file $REDIRECT_CMD"
        fi
    done
    # Exporta a lista de objetos para a função de link
    export OBJECTS
}

link_target() {
    printf "${COLOR_CYAN}🔗 Linkando $TARGET${COLOR_RESET}\n"
    eval "$CC $CFLAGS -o $TARGET $OBJECTS $REDIRECT_CMD"
}

build_all() {
    prepare
    generate_parser
    compile_objects
    link_target
    
    printf "${COLOR_GREEN}✔ Build mode: $BUILD_TYPE concluído.${COLOR_RESET}\n"
    if [ "$SHOW_WARNINGS" != "1" ] && [ -s "$WARNING_LOG" ]; then
        printf "${COLOR_YELLOW}⚠️  Warnings foram capturados em $WARNING_LOG. Use SHOW_WARNINGS=1 para vê-los.${COLOR_RESET}\n"
    fi
}

run_test() {
    build_all
    printf "${COLOR_GREEN}🚀 Executando teste com $FILE${COLOR_RESET}\n"
    eval "./$TARGET $PASCALM_FLAGS"
}

compile_pascal_tests() {
    build_all
    find "$TEST_DIR" -name "*.pascalm" | while read -r pascal_file; do
        local c_file="$OUT_DIR/$(basename "${pascal_file%.pascalm}").c"
        local bin_file="$OUT_DIR/$(basename "${pascal_file%.pascalm}")"
        
        run "Gerando C de $pascal_file" "./$TARGET -f $pascal_file -o $c_file"
        run "Compilando binário $bin_file" "$CC $CFLAGS $c_file -o $bin_file"
    done
}

clean() {
    printf "${COLOR_RED}🧹 Limpando o projeto${COLOR_RESET}\n"
    rm -rf "$BUILD_DIR" "$OUT_DIR" "$TARGET" parser/lex.yy.c parser/parser.tab.c parser/parser.tab.h "${TARGET}.dSYM"
    # Não remove o log de warnings por padrão, mas pode ser adicionado se desejado
    # rm -f "$WARNING_LOG"
}

# ===========================
# Ponto de Entrada Principal
# ===========================
CMD=${1:-all} # O comando é o primeiro argumento, ou 'all' se nenhum for passado

case $CMD in
    all)
        build_all
        ;;
    test)
        run_test
        ;;
    compile-c)
        compile_pascal_tests
        ;;
    parser)
        prepare
        # Força a regeração
        rm -f parser/parser.tab.c parser/parser.tab.h parser/lex.yy.c
        generate_parser
        printf "${COLOR_GREEN}✔ Parser e Lexer gerados.${COLOR_RESET}\n"
        ;;
    clean)
        clean
        ;;
    *)
        echo "Comando desconhecido: $CMD"
        echo "Comandos disponíveis: all, test, compile-c, parser, clean"
        exit 1
        ;;
esac
