#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

int snakeLenght = 4;
//int snakeYX[0] = 4, snakeYX[1] = 4;
int gameOver = 0;
int snakeYX[2][20];
int fruitYX[2] = {9, 17};
int input = 0;
int keepMove;

void moveSnake(void) {

    if (input != ERR) {
        keepMove = input;
    }

    if (keepMove == KEY_RIGHT) {
        snakeYX[1][0]++;
    }
    else if (keepMove == KEY_LEFT) {
        snakeYX[1][0]--;
    }
    else if (keepMove == KEY_UP) {
        snakeYX[0][0]--;
    }
    else if (keepMove == KEY_DOWN) {
        snakeYX[0][0]++;
    }
}

void fruitCor(void) {
    fruitYX[0] = (rand() %20);
    fruitYX[1] = (rand() %20);
}
int main () {

    snakeYX[1][0] = 4;
    snakeYX[0][0] = 4;

    for (int i = 0; i <= snakeLenght; i++) {
        snakeYX[1][i] = (snakeLenght - i);
    }
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);
    keepMove = KEY_RIGHT;

    while (!gameOver) {
        input = getch();

        refresh();
        for (int i = snakeLenght; i > 0; i--) {
            snakeYX[0][i] = snakeYX[0][i-1];
            snakeYX[1][i] = snakeYX[1][i-1];
        }

        moveSnake();
        mvwaddch(stdscr, snakeYX[0][snakeLenght], snakeYX[1][snakeLenght], ' ');
        mvwaddch(stdscr, snakeYX[0][0], snakeYX[1][0], '*');
        mvwaddch(stdscr, fruitYX[0], fruitYX[1], '@');
        refresh();

        if (snakeYX[0][0] == fruitYX[0] && snakeYX[1][0] == fruitYX[1]) {
            snakeLenght++;
            mvwaddch(stdscr, fruitYX[0], fruitYX[1], ' ');
            refresh();
            fruitCor();
        }
        usleep(100000);

        int i = 0;
        i++;

    }

    getch();
    endwin();

    return 0;
}

