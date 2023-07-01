OBJS=zcc.o ctree.o asm.o global.o function.o i386.o

.PHONY: all
all:
	make zcc.out
	./zcc.out test.c test.asm
	make test

.PHONY: test
test:
	nasm -felf test.asm
	ld -melf_i386 test.o -o test.out -lc --dynamic-linker /lib/ld-linux.so.2
	./test.out

zcc.out: $(OBJS)
	make -C libutil
	gcc $(LDFLAGS) -L libutil/ -lutil

.PHONY: clean
clean:
	make -C libutil clean
	-rm -fr *.o
	-rm -fr *.out
	-rm -fr *.a
	-rm -fr *.so
	-rm -fr *.asm

include Makefile.include
