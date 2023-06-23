OBJS=zcc.o ctree.o asm.o

all:
	#gcc zcc.c
	#for CLION CONFIGURE
	make zcc.out
	./zcc.out

zcc.out: $(OBJS)
	make -C libutil
	gcc $(LDFLAGS) -L libutil/ -lutil

clean:
	make -C libutil clean
	-rm -fr *.o
	-rm -fr *.out
	-rm -fr *.a
	-rm -fr *.so

include Makefile.include
