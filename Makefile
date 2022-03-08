CFLAGS = -O3
CC = gcc

all: sieve

sieve: sieve.c
	$(CC) -o $< sieve.c $(CFLAGS)

clean:
	 rm sieve
	 rm gcd