#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

int snakeLenght = 1;
int gameOver = 0;
int snakeYX[2][20];
int fruitYX[2] = {9, 17};
int playerScore = 0;
int input = 0;
int keepMove;
int yMax, xMax, height, width, startY, startX;

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
//setting the game window according to the terminal
void setScreen (void) {
    getmaxyx(stdscr, yMax, xMax);
    height = yMax/2;
    width = xMax/2;
    startY = yMax/4;
    startX = xMax/4;

    if ((height % 2) != 0)
        height--;

    if ((width % 2) != 0)
        width--;

}
//moves the snake to the opposite border once he hit a border
void checkBor(void) {
    
    if (snakeYX[0][0] == (height - 1))
        snakeYX[0][0] = 1;

    else if (snakeYX[0][0] == 0)
        snakeYX[0][0] = (height - 1);

    else if (snakeYX[1][0] >= (width - 1))
        snakeYX[1][0] = 1;

    else if (snakeYX[1][0] == 0)
        snakeYX[1][0] = (width - 1);

}

void fruitCor(void) {
    fruitYX[0] = (rand() %height);
    fruitYX[1] = (rand() %width);
}

int main () {

    //snake starting point and direction
    snakeYX[1][0] = 20;
    snakeYX[0][0] = 8;
    keepMove = KEY_RIGHT;

    //ncurses initialization
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    //game window initialization
    setScreen();
    WINDOW * game = newwin(height, width, startY, startX);
    refresh();
    box (game, 0, 0);

    keypad(game, TRUE);

    //start the game only after the player pressed a key
    mvwprintw(game, height/2, (width/2 - 12) ,"Press any key to start");
    input = wgetch(game);
        if (input != ERR ){
            nodelay(game, TRUE);
            //wrefresh(game);
            werase(game);
            box (game, 0, 0);
            wrefresh(game);
        }

    //score window initialization
    setScreen();
    WINDOW * score = newwin(5, (width/2), (startY - 5), startX);
    refresh();
    box (score, 0, 0);
    mvwprintw(score, 2 , 2, "Score : %d", playerScore);
    wrefresh(score);

    mvwaddch(game, fruitYX[0], fruitYX[1], '@');

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
            fruitCor();
            mvwaddch(game, fruitYX[0], fruitYX[1], '@');
            wrefresh(game);
            wrefresh(score);
        }

        usleep(100000); //make the loop wait for some time
        checkBor();
        box (game, 0, 0); // fixing the borders

    }

    endwin(); //

    return 0;
}

