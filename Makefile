
CC=gcc
CFLAGS=-I. -Wall -Werror
LFLAGS=

program: main.o stack.o tree.o
	$(CC) $(CFLAGS) $(LFLAGS) $^ -o $@ 
	$(RM) $^

main.o: main.c stack.c tree.c
	$(CC) -c $(CFLAGS) $< -o $@
