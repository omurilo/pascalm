CC = gcc
CFLAGS = -Wall -g

all: pascal

pascal: parser/lex.yy.c parser/parser.tab.c ast/ast.c symbol-table/symbol-table.c code-generation/code.c  main.c
	$(CC) $(CFLAGS) -o $@ $^

parser/lex.yy.c: parser/parser.l parser/parser.tab.h ast/ast.h code-generation/code.h
	flex -o $@ $^ 

parser/parser.tab.c parser/parser.tab.h: parser/parser.y
	bison -o $@ -d $< 

.PHONY: test
test: pascal
	./pascal $(FILE)

clean:
	rm -f *.o parser/lex.yy.c parser/parser.tab.c parser/parser.tab.h pascal
	rm -rf pascal.dSYM
