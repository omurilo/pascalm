CC = gcc
CFLAGS = -Wall -g

all: pascal

pascal: parser/lex.yy.c parser/parser.tab.c ast/ast.c symbol-table/symbol-table.c main.c
	$(CC) $(CFLAGS) -o $@ $^

parser/lex.yy.c: parser/parser.l parser/parser.tab.h ast/ast.h
	flex -o $@ $^ 

parser/parser.tab.c parser/parser.tab.h: parser/parser.y
	bison -o $@ -d $< 

clean:
	rm -f *.o parser/lex.yy.c parser/parser.tab.c parser/parser.tab.h pascal
	rm -rf pascal.dSYM
