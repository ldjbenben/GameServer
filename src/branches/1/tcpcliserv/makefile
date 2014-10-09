objects = tcpserv01.o str_echo.o unp.o signal.o sigchldwait.o readline.o wrapstdio.o wrapunix.o wrapsock.o error.o
CC = gcc
EXE = tcpserv01
CFLAGS = -Wall -g

server:$(objects)
	$(CC) $(CFLAGS) -o $(EXE) $(objects)

tcpserv01.o:tcpserv01.c
	$(CC) $(CFLAGS) -c tcpserv01.c -I ../lib
	
str_echo.o:../lib/str_echo.c ../lib/unp.h
	$(CC) $(CFLAGS) -c ../lib/str_echo.c

unp.o:../lib/unp.c ../lib/unp.h
	$(CC) $(CFLAGS) -c ../lib/unp.c
	
signal.o:../lib/signal.c ../lib/unp.h
	$(CC) $(CFLAGS) -c ../lib/signal.c
	
sigchldwait.o:sigchldwait.c ../lib/unp.h
	$(CC) $(CFLAGS) -c sigchldwait.c  -I ../lib

readline.o:../lib/readline.c ../lib/unp.h
	$(CC) $(CFLAGS) -c ../lib/readline.c

wrapstdio.o:../lib/wrapstdio.c ../lib/unp.h
	$(CC) $(CFLAGS) -c ../lib/wrapstdio.c

wrapunix.o:../lib/wrapunix.c ../lib/unp.h
	$(CC) $(CFLAGS) -c ../lib/wrapunix.c

wrapsock.o:../lib/wrapsock.c ../lib/unp.h
	$(CC) $(CFLAGS) -c ../lib/wrapsock.c

error.o:../lib/error.c ../lib/unp.h
	$(CC) $(CFLAGS) -c ../lib/error.c
	
clean:
	rm ./$(EXE) $(objects)
