CC = gcc
CFLAGS = -std=c99 -Wall -pedantic

all: list.o

list.o: list.c
	$(CC) $(CFLAGS) -c list.c -o list.o

clean:
	rm -i list.o 