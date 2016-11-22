all: PThreadHW.c
	gcc -std=c99 -w -o thread PThreadHW.c -lpthread
