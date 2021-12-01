
CC=gcc
CFLAGS=-I. -Wall -Werror
LFLAGS=

program: main.o stack.o
	$(CC) $(CFLAGS) $(LFLAGS) $^ -o $@ 
	$(RM) $^

main.o: main.c stack.c
	$(CC) -c $(CFLAGS) $< -o $@
