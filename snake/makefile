CC=gcc
CFLAGS=-lncurses -Wall

all: snake

snake: snake.o menus.o game.o
	$(CC) snake.o menus.o game.o -o snake $(CFLAGS)

snake.o: snake.c
	$(CC) -c snake.c

menus.o: menus.c
	$(CC) -c menus.c

game.o: game.c
	$(CC) -c game.c

clean:
	rm -f snake.o game.o menus.o snake
