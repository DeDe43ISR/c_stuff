CC=gcc
CFLAGS=-lncurses -Wall

all: snake

snake: snake.o menus.o
	$(CC) snake.o menus.o -o snake $(CFLAGS)

snake.o: snake.c
	$(CC) -c snake.c

menus.o: menus.c
	$(CC) -c menus.c

clean:
	rm -f snake.o menus.o snake
