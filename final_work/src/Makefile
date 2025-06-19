CC ?= gcc
CFLAGS ?= -Wall -g -fsanitize=address -fsanitize=undefined -Wextra
FILE ?=../tests/complex-test.pascalm

all: pascal

pascal: parser/lex.yy.c parser/parser.tab.c ast/ast.c semantic-analyzer/analyzer.c symbol-table/symbol-table.c code-generation/code.c code-generation/utils.c context.c main.c
	$(CC) $(CFLAGS) -o $@ $^

parser/lex.yy.c: parser/parser.l parser/parser.tab.h semantic-analyzer/analyzer.h symbol-table/symbol-table.h ast/ast.h code-generation/code.h context.h
	flex -o $@ $^ 

parser/parser.tab.c parser/parser.tab.h: parser/parser.y
	bison -o $@ -d $< 

.PHONY: test
test: pascal
	./pascal $(FILE)

clean:
	rm -f *.o parser/lex.yy.c parser/parser.tab.c parser/parser.tab.h pascal
	rm -rf pascal.dSYM
