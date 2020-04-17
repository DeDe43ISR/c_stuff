#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

int snakeLenght = 4;
int gameOver = 0;
int snakeYX[2][20];
int fruitYX[2] = {9, 17};
int input = 0;
int keepMove;
int yMax, xMax;

void moveSnake(void) {

    for (int i = snakeLenght; i > 0; i--) {
        snakeYX[0][i] = snakeYX[0][i-1];
        snakeYX[1][i] = snakeYX[1][i-1];
    }

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

void checkBor(void) {
    
    if (snakeYX[0][0] == (yMax/2))
        snakeYX[0][0] = 0;

    else if (snakeYX[0][0] == 0)
        snakeYX[0][0] = (yMax/2);

    else if (snakeYX[1][0] == (xMax/2))
        snakeYX[1][0] = 0;

    else if (snakeYX[1][0] == 0)
        snakeYX[1][0] = (xMax/2);

}

void fruitCor(void) {
    fruitYX[0] = (rand() %20);
    fruitYX[1] = (rand() %20);
}

int main () {

    //snake starting point
    snakeYX[1][0] = 20;
    snakeYX[0][0] = 8;

    initscr();
    noecho();
    cbreak();
    getmaxyx(stdscr, yMax, xMax);
    WINDOW * win = newwin(yMax/2, xMax/2, yMax/4, xMax/4);
    refresh();
    box (win, 0, 0);

    keypad(win, TRUE);
    nodelay(win, TRUE);
    scrollok(win, TRUE);
    keepMove = KEY_RIGHT;

    while (!gameOver) {
        input = wgetch(win);


        moveSnake();
        mvwaddch(win, snakeYX[0][snakeLenght], snakeYX[1][snakeLenght], ' ');
        mvwaddch(win, snakeYX[0][0], snakeYX[1][0], '*');
        mvwaddch(win, fruitYX[0], fruitYX[1], '@');
        wrefresh(win);

        if (snakeYX[0][0] == fruitYX[0] && snakeYX[1][0] == fruitYX[1]) {
            snakeLenght++;
            mvwaddch(win, fruitYX[0], fruitYX[1], ' ');
            wrefresh(win);
            fruitCor();
        }
        usleep(100000);
        checkBor();
        box (win, 0, 0);

    }

    getch();
    endwin();

    return 0;
}

