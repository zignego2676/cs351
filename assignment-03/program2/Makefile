
CC=gcc
CFLAGS=-lm -Wall -Wextra 

all: coinflips 

coinflips: coinflips.c coinflips.h main.c
	$(CC) coinflips.c coinflips.h main.c $(CFLAGS) -o coinflips
clean:
	rm coinflips
