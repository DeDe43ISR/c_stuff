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

void menu(void) {
    
    char menuOption[2][10] = {"Start", "Difficulty"};
    int highlight = 0;
    int onMenu = 1;

    //menu window initialization
    setScreen();
    WINDOW * menu = newwin(height, width, startY, startX);
    refresh();
    box (menu, 0, 0);
    wrefresh(menu);
    keypad(menu, TRUE);

    while (onMenu) {


        for (int i = 0; i < 2; i++) {
            if (i == highlight)
                wattron(menu, A_REVERSE);

            mvwprintw(menu, (height/2 + i), (width/2 - 12) ,menuOption[i]);
            wattroff(menu, A_REVERSE);
        }
        wrefresh(menu);

        input = wgetch(menu); //getting the key that was pressed

        switch (input) {
            case (KEY_UP):
                highlight--;
                if (highlight == -1)
                    highlight = 1;
                break;

            case (KEY_DOWN):
                highlight++;
                if (highlight == 2)
                    highlight = 0;
                break;
            
            case (10):
                switch (highlight) {
                    case (0):
                        delwin(menu);
                        onMenu = 0;
                        break;
                }
        }
        wrefresh(menu);
    }

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

    menu();

    //game window initialization
    setScreen();
    WINDOW * game = newwin(height, width, startY, startX);
    refresh();
    box (game, 0, 0);
    keypad(game, TRUE);
    nodelay(game, TRUE);

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

