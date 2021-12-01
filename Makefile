
CC=gcc
CFLAGS=-I. -Wall -Werror

program: main.o stack.o tree.o
	$(CC) $(CFLAGS) $^ -o $@ 
	$(RM) $^

main.o: main.c stack.c tree.c
	$(CC) -c $(CFLAGS) $< -o $@
