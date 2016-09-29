CC=gcc
CFLAGS= -std=c99 -c -Wall
LFLAGS=

all: Interpreter.out
	$(CC) $(LFlAGS) Interpreter.o -o test


Interpreter: Interpreter.out
	$(CC) $(CFLAGS) Interpreter.c
