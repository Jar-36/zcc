OBJS=zcc.o ctree.o asm.o global.o function.o i386.o

all:
	make zcc.out
	./zcc.out test.c test.asm

zcc.out: $(OBJS)
	make -C libutil
	gcc $(LDFLAGS) -L libutil/ -lutil

clean:
	make -C libutil clean
	-rm -fr *.o
	-rm -fr *.out
	-rm -fr *.a
	-rm -fr *.so
	-rm -fr *.asm

include Makefile.include
