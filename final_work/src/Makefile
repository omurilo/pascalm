CC      ?= gcc
FILE    ?= ../tests/complex-test.pascalm

DEBUG ?= 0

ifeq ($(DEBUG), 1)
    CFLAGS = -Wall -Wextra -g -fsanitize=address -fsanitize=undefined -DVERBOSE_MODE
    BUILD_TYPE = Debug
		BFLAGS = -t -d
else
    CFLAGS = -Wall -Wextra -O2
    BUILD_TYPE = Release
		BFLAGS = -d
endif

SRC_DIRS = parser ast semantic-analyzer symbol-table code-generation
BUILD_DIR = build

# Incluindo explicitamente os arquivos do parser
PARSER_SRCS = parser/parser.tab.c parser/lex.yy.c
SRCS = $(wildcard $(addsuffix /*.c, $(SRC_DIRS))) main.c context.c $(PARSER_SRCS)

OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

TARGET = pascalm

all: $(TARGET)
	@echo "Build mode: $(BUILD_TYPE)"

$(TARGET): $(OBJS) | parser
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^

# Compilação dos objetos
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Dependências explícitas para parser.tab.h
$(BUILD_DIR)/main.o: parser/parser.tab.h
$(BUILD_DIR)/parser/parser.tab.o: parser/parser.tab.h
$(BUILD_DIR)/parser/lex.yy.o: parser/parser.tab.h
$(BUILD_DIR)/context.o: parser/parser.tab.h

# Regras para gerar lexer e parser
parser: parser/lex.yy.c parser/parser.tab.c parser/parser.tab.h

parser/lex.yy.c: parser/parser.l parser/parser.tab.h
	flex -o $@ $<

parser/parser.tab.c parser/parser.tab.h: parser/parser.y
	bison $(BFLAGS) -o parser/parser.tab.c $<

.PHONY: test
test: $(TARGET)
	./$(TARGET) -f $(FILE)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET) parser/lex.yy.c parser/parser.tab.c parser/parser.tab.h
	rm -rf $(TARGET).dSYM
