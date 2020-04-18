CC=gcc
CFLAGS=-lncurses -Wall

all: snake

snake: snake.o menus.o
	$(CC) snake.o menus.o -o snake $(CFLAGS)

snake.c: snake.c
	$(CC) $(CFLAGS) -c snake.c

menus.c: menus.c
	$(CC) $(CFLAGS) -c menus.c

clean:
	rm -f snake.o menus.o snake
