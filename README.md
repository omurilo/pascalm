# How to test

## Only flex:

```bash
nix-shell -p flex
flex grammar/*.lex
gcc -o lex lex.yy.c -L /nix/store/23izns4pj0mvd8bk8whm5gmxnqv8m2hg-flex-2.6.4/lib/ -lfl
./lex ...
```

## Bison/Flex:

```bash
nix-shell -p flex bison
cd MODULE_DIR
bison -d MODULE_NAME.y -o MODULE_NAME.tab.c
flex DIT_PATH/MODULE_NAME.lex
g++ -o MODULE_NAME lex.yy.c MODULE_NAME.tab.c
./MODULE_NAME < MODULE_NAME.test.txt
```

## Using Make (only bison)

```bash
cd MODULE_DIR
make -f BASE_DIR/Makefile test
```
