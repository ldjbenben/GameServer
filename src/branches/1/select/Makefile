VERSION =
objects = tcpcli$(VERSION).o strcliselect.o unp.o readline.o wraplib.o wrapstdio.o wrapunix.o wrapsock.o error.o
CC = gcc
EXE = tcpcli$(VERSION)
CFLAGS = -Wall -g

server:$(objects)
	$(CC) $(CFLAGS) -o $(EXE) $(objects)

tcpcli$(VERSION).o:tcpcli$(VERSION).c
	$(CC) $(CFLAGS) -c tcpcli$(VERSION).c -I ../lib
	
strcliselect.o:strcliselect.c ../lib/unp.h
	$(CC) $(CFLAGS) -c strcliselect.c  -I ../lib

unp.o:../lib/unp.c ../lib/unp.h
	$(CC) $(CFLAGS) -c ../lib/unp.c

readline.o:../lib/readline.c ../lib/unp.h
	$(CC) $(CFLAGS) -c ../lib/readline.c

wraplib.o:../lib/wraplib.c ../lib/unp.h
	$(CC) $(CFLAGS) -c ../lib/wraplib.c

wrapstdio.o:../lib/wrapstdio.c ../lib/unp.h
	$(CC) $(CFLAGS) -c ../lib/wrapstdio.c

wrapunix.o:../lib/wrapunix.c ../lib/unp.h
	$(CC) $(CFLAGS) -c ../lib/wrapunix.c

wrapsock.o:../lib/wrapsock.c ../lib/unp.h
	$(CC) $(CFLAGS) -c ../lib/wrapsock.c

error.o:../lib/error.c ../lib/unp.h
	$(CC) $(CFLAGS) -c ../lib/error.c
