OBJS=zcc.o

.PHONY: all
all:
	make zcc.out
	./zcc.out

zcc.out: $(OBJS)
	gcc $(LDFLAGS) -L libutil/ -lutil

.PHONY: clean
clean:
	-rm -fr *.o
	-rm -fr *.out
	-rm -fr *.a
	-rm -fr *.so
	-rm -fr *.asm

include Makefile.include
