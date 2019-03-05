CC = gcc
CFLAGS = -Wall -std=c99

all: test

test: test.c
	$(CC) $(CFLAGS) -o test test.c

clean:
	rm *.o test
