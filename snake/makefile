#I Will Make You Happy :)

CC=gcc
CFLAGS=-lncurses -Wall -Wextra -g3 -fsanitize=address -fno-omit-frame-pointer -lasan
OUT_DIR=./bin

all: directories snake

directories:
	mkdir -p $(OUT_DIR)

snake: main.o menus.o game.o
	$(CC) $(OUT_DIR)/main.o $(OUT_DIR)/menus.o $(OUT_DIR)/game.o -o $(OUT_DIR)/snake $(CFLAGS)

main.o: main.c
	$(CC) -c main.c -o $(OUT_DIR)/main.o

menus.o: menus.c
	$(CC) -c menus.c -o $(OUT_DIR)/menus.o

game.o: game.c
	$(CC) -c game.c -o $(OUT_DIR)/game.o

clean:
	rm -rf $(OUT_DIR)
