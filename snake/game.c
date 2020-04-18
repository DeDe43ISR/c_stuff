#include<ncurses.h>
#include <unistd.h>
#include <stdlib.h>

int snakeYX[2][20];
int snakeLenght = 10;
int gameOver = 0;
int fruitYX[2] = {9, 17};
int playerScore = 0;
int input = 0;
int keepMove;

//move the snake according to the keys that are being pressed
void moveSnake(void) {

    //moving the snake location in the arrey
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

void play(int difficulty, int height, int width, int startY, int startX) {

    //snake starting point and direction
    snakeYX[1][0] = 20;
    snakeYX[0][0] = 8;
    keepMove = KEY_RIGHT;

    //game window initialization
    WINDOW * game = newwin(height, width, startY, startX);
    refresh();
    box (game, 0, 0);
    keypad(game, TRUE);
    nodelay(game, TRUE);

    //score window initialization
    WINDOW * score = newwin(5, (width/2), (startY - 5), startX);
    refresh();
    box (score, 0, 0);
    mvwprintw(score, 2 , 2, "Score : %d", playerScore);
    wrefresh(score);

    //prints first fruit
    mvwaddch(game, fruitYX[0], fruitYX[1], '@');

    //making sure game will start on second run
    gameOver = 0;

    while (!gameOver) {

        input = wgetch(game); //getting the key that was pressed

        moveSnake();

        //print the snake and the fruit
        mvwaddch(game, snakeYX[0][snakeLenght], snakeYX[1][snakeLenght], ' ');
        mvwaddch(game, snakeYX[0][0], snakeYX[1][0], '*');
//        mvwprintw(game, snakeYX[0][0], snakeYX[1][0], "%d", snakeYX[1][0]);
        wrefresh(game);

        //increase the snake size if a fruit was eaten
        if (snakeYX[0][0] == fruitYX[0] && snakeYX[1][0] == fruitYX[1]) {
            snakeLenght++;
            playerScore++;
            mvwaddch(game, fruitYX[0], fruitYX[1], ' ');
            mvwprintw(score, 2, 10, "%d", playerScore);
            fruitCor(fruitYX, height, width);
            mvwaddch(game, fruitYX[0], fruitYX[1], '@');
            wrefresh(game);
            wrefresh(score);
        }

        for (int i = 1; i < snakeLenght; i++) {
            if (snakeYX[0][0] == snakeYX[0][i] && snakeYX[1][0] == snakeYX[1][i]) {
                gameOver = 1;
                playerScore = 0;
                break;
            }
                
        }

        usleep(difficulty); //make the loop wait for some time
        checkBor(height, width);
        box (game, 0, 0); // fixing the borders

    }
        delwin(game);
        delwin(score);

}
