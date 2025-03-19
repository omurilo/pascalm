```bash
nix-shell -p flex
flex grammar/*.lex
gcc -o lex lex.yy.c -L /nix/store/23izns4pj0mvd8bk8whm5gmxnqv8m2hg-flex-2.6.4/lib/ -lfl
./lex ...
```
