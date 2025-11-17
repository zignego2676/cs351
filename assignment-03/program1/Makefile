
CC=gcc
CFLAGS=-Wall -Wextra 
RM=rm -f

all: permutations

permutations: permutations.c permutations.h main.c
	$(CC) permutations.c permutations.h main.c $(CFLAGS) -o permutations
clean:
	$(RM) permutations
