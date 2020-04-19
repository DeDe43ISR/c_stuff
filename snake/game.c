#include<ncurses.h>
#include <unistd.h>
#include <stdlib.h>

#define FRUIT_COLOR 1
#define BLACK_COLOR 2
#define TAIL_COLOR 3
#define HEAD_COLOR 4
#define BORDER_COLOR 5

int snakeYX[2][20];
int snakeLenght = 10;
int gameOver = 0;
int fruitYX[2] = {9, 17};
int playerScore = 0;
int input = 0;
int keepMove;

WINDOW * setBox(WINDOW * win, int  color) {
    wattron(win, COLOR_PAIR(color));
    box (win, 0, 0);
    wattroff(win, COLOR_PAIR(color));
    return win;
}

//move the snake according to the keys that are being pressed
void moveSnake(void) {

    //moving the snake location in the array
    for (int i = snakeLenght; i > 0; i--) {
        snakeYX[0][i] = snakeYX[0][i-1];
        snakeYX[1][i] = snakeYX[1][i-1];
    }

    //saving the key only if a key was pressed
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

//moves the snake to the opposite border once he hit a border
void checkBor(int height, int width) {
    
    if (snakeYX[0][0] == (height - 1))
        snakeYX[0][0] = 1;

    else if (snakeYX[0][0] == 0)
        snakeYX[0][0] = (height - 1);

    else if (snakeYX[1][0] >= (width - 1))
        snakeYX[1][0] = 1;

    else if (snakeYX[1][0] == 0)
        snakeYX[1][0] = (width - 1);

}

void fruitCor(int fruitYX[], int height, int width) {
    fruitYX[0] = (rand() % (height - 4));
    fruitYX[1] = (rand() % (width - 2));
}

int play(int difficulty, int height, int width, int startY, int startX) {

    //snake starting point and direction
    snakeYX[1][0] = 20;
    snakeYX[0][0] = 8;
    keepMove = KEY_RIGHT;
    playerScore = 0;

    //game window initialization
    WINDOW * game = newwin(height, width, startY, startX);
    refresh();

/*
    wattron(game, COLOR_PAIR(BORDER_COLOR));
    box (game, 0, 0);
    wattroff(game, COLOR_PAIR(BORDER_COLOR));
*/
    game = setBox(game, BORDER_COLOR);
    keypad(game, TRUE);
    nodelay(game, TRUE);

    //score window initialization
    WINDOW * score = newwin(5, (width/2), (startY - 5), startX);
    refresh();
    box (score, 0, 0);
    mvwprintw(score, 2 , 2, "Score : %d", playerScore);
    wrefresh(score);

    //prints first fruit
    wattron(game, COLOR_PAIR(FRUIT_COLOR));
    mvwaddch(game, fruitYX[0], fruitYX[1], ' ');
    wattroff(game, COLOR_PAIR(FRUIT_COLOR));
    wrefresh(game);

    //making sure game will start on second run
    gameOver = 0;

    while (!gameOver) {

        input = wgetch(game); //getting the key that was pressed

        moveSnake();

        //print the snake and the fruit
        mvwaddch(game, snakeYX[0][snakeLenght], snakeYX[1][snakeLenght], ' ');
        
        wattron(game, COLOR_PAIR(HEAD_COLOR));
        mvwaddch(game, snakeYX[0][0], snakeYX[1][0], ' ');
        wattroff(game, COLOR_PAIR(HEAD_COLOR));

        wattron(game, COLOR_PAIR(TAIL_COLOR));
        mvwaddch(game, snakeYX[0][1], snakeYX[1][1], ' ');
        wattroff(game, COLOR_PAIR(TAIL_COLOR));

        wrefresh(game);

        //increase the snake size if a fruit was eaten
        if (snakeYX[0][0] == fruitYX[0] && snakeYX[1][0] == fruitYX[1]) {
            snakeLenght++;
            playerScore++;

            wattron(game, COLOR_PAIR(TAIL_COLOR));
            mvwaddch(game, fruitYX[0], fruitYX[1], ' ');
            wattroff(game, COLOR_PAIR(TAIL_COLOR));

            fruitCor(fruitYX, height, width);

            wattron(game, COLOR_PAIR(FRUIT_COLOR));
            mvwaddch(game, fruitYX[0], fruitYX[1], ' ');
            wattroff(game, COLOR_PAIR(FRUIT_COLOR));

            wrefresh(game);

            mvwprintw(score, 2, 10, "%d", playerScore);
            wrefresh(score);
        }

        for (int i = 1; i < snakeLenght; i++) {
            if (snakeYX[0][0] == snakeYX[0][i] && snakeYX[1][0] == snakeYX[1][i]) {
                gameOver = 1;
                break;
            }
                
        }

        usleep(difficulty); //make the loop wait for some time
        checkBor(height, width);

        game = setBox(game, BORDER_COLOR);

    }
    delwin(game);
    delwin(score);
    return playerScore;

}
