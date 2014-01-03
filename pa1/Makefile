# Makefile to compile Umix Programming Assignment 1 (pa1) [updated: 1/11/10]

LIBDIR = $(UMIXPUBDIR)/lib
# LIBDIR = $(UMIXROOTDIR)/sys

CC 	= cc 
FLAGS 	= -g -L$(LIBDIR) -lumix1

PA1 =	pa1a pa1b pa1c pa1d pa1e pa1f

pa1:	$(PA1)

pa1a:	pa1a.c aux.h umix.h mykernel1.o
	$(CC) $(FLAGS) -o pa1a pa1a.c mykernel1.o

pa1b:	pa1b.c aux.h umix.h mykernel1.o
	$(CC) $(FLAGS) -o pa1b pa1b.c mykernel1.o

pa1c:	pa1c.c aux.h umix.h mykernel1.o
	$(CC) $(FLAGS) -o pa1c pa1c.c mykernel1.o

pa1d:	pa1d.c aux.h umix.h mykernel1.o
	$(CC) $(FLAGS) -o pa1d pa1d.c mykernel1.o

pa1e:	pa1e.c aux.h umix.h mykernel1.o
	$(CC) $(FLAGS) -o pa1e pa1e.c mykernel1.o

pa1f:	pa1f.c aux.h umix.h mykernel1.o
	$(CC) $(FLAGS) -o pa1f pa1f.c mykernel1.o

mykernel1.o:	mykernel1.c aux.h sys.h mykernel1.h
	$(CC) $(FLAGS) -c mykernel1.c

clean:
	rm -f *.o $(PA1)
