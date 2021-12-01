
CC=gcc
CFLAGS=-Wall -Werror
LFLAGS=

program: main.o
	$(CC) $(CFLAGS) $(LFLAGS) $^ -o $@ 
	$(RM) $<

main.o: main.c
	$(CC) -c $(CFLAGS) $< -o $@
