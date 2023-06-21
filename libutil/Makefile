OBJS=util.o

default:
	make libutil.a

libutil.a: $(OBJS)
	$(AR) $(ARFLAGS)

clean:
	-rm -fr *.o
	-rm -fr *.out
	-rm -fr *.a
	-rm -fr *.so

include ../Makefile.include