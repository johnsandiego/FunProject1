CC=gcc
CFLAGS= -std=c99 -c -Wall
LFLAGS=

all: Interpreter.o
	$(CC) $(LFlAGS) Interpreter.o -o test


Interpreter: Interpreter.o
	$(CC) $(CFLAGS) Interpreter.c
