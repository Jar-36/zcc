#!/bin/sh
gcc -m32 -c lib.c
flex scanner.l
bison -vdty parser.y
gcc -o zcc lex.yy.c y.tab.c

./zcc test.c
nasm -felf -P macro.inc -P test.inc test.asm
ld -melf_i386 test.o lib.o --dynamic-linker /lib/ld-linux.so.2 -lc