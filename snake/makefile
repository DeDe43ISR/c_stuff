CC=gcc
CFLAGS=-lncurses -Wall

all: snake

snake: main.o menus.o game.o
	$(CC) main.o menus.o game.o -o snake $(CFLAGS)

main.o: main.c
	$(CC) -c main.c

menus.o: menus.c
	$(CC) -c menus.c

game.o: game.c
	$(CC) -c game.c

clean:
	rm -f main.o game.o menus.o snake
