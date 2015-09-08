# Fiddle Makefile
# Just for testing

CC=gcc

CFLAGS=-c -g -Wall -Wextra -DDEBUG -O2

OBJS=utils.o vector.o scanner.o parser.o

%.o: %.c fiddle.h
	$(CC) $(CFLAGS) -o $@ $<

all: $(OBJS)
	@echo "Done!"

.PHONY: all

clean:
	rm -f *.o

.PHONY: clean

# Dependencies
utils.o: utils.c
vector.o: vector.h vector.c
scanner.o: vector.h scanner.h scanner.c
parser.o: vector.h scanner.h ast.h parser.h parser.c
