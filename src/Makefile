# Fiddle Makefile
# Just for testing

CC=gcc

CFLAGS=-c -g -Wall -Wextra -O2

%.o: %.c fiddle.h
	$(CC) $(CFLAGS) -o $@ $<

all: vector.o scanner.o
	@echo "Done!"

.PHONY: all

clean:
	rm -f *.o

.PHONY: clean

# Dependencies
vector.o: vector.h vector.c
scanner.o: scanner.h scanner.c
