# Makefile to compile Umix Programming Assignment 2 (pa2) [updated: 1/11/10]

LIBDIR = $(UMIXPUBDIR)/lib
# LIBDIR = $(UMIXROOTDIR)/sys

CC 	= cc 
FLAGS 	= -g -L$(LIBDIR) -lumix2

PA2 =	pa2a pa2b pa2c

pa2:	$(PA2)

pa2a:	pa2a.c aux.h umix.h mykernel2.o
	$(CC) $(FLAGS) -o pa2a pa2a.c mykernel2.o

pa2b:	pa2b.c aux.h umix.h mykernel2.o
	$(CC) $(FLAGS) -o pa2b pa2b.c mykernel2.o

pa2c:	pa2c.c aux.h umix.h mykernel2.o
	$(CC) $(FLAGS) -o pa2c pa2c.c mykernel2.o
lifo:	lifo.c aux.h umix.h mykernel2.o
	$(CC) $(FLAGS) -o lifo lifo.c mykernel2.o

mykernel2.o:	mykernel2.c aux.h sys.h mykernel2.h
	$(CC) $(FLAGS) -c mykernel2.c

clean:
	rm -f *.o $(PA2)
