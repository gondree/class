CC      = gcc
CFLAGS  = -Wall
LDFLAGS = 
VPATH  += src

LIBS = lib/libcomb.a lib/libcomb.so
BINS = combtest combtest-0 combtest-1 combtest-2
OBJS = lucas.o bell.o clist.o

.PHONY: all clean install uninstall

all: $(BINS)

clean:
	rm -f *.o *.s *.i $(LIBS) $(BINS)


#
# Rules for BINS
#



#
# Rules for LIBS
#



#
# Rules for Object files, pre-processor output, assembly
#



#
# install and uninstall targets
#

install: /usr/lib/libcomb.so

/usr/lib/libcomb.so: lib/libcomb.so
	sudo install $< $@ -m 0444

uninstall:
	sudo rm -f /usr/lib/libcomb.so

#
# Dependencies
#
combtest.o combtest.i combtest.s: combtest.c include/bell.h \
    include/combinatorics.h include/lucas.h include/clist.h
lucas.o lucas.i lucas.s: lucas.c include/lucas.h include/combinatorics.h
bell.o bell.i bell.s: bell.c include/bell.h include/combinatorics.h
clist.o clist.i clist.s: clist.c include/clist.h include/combinatorics.h
