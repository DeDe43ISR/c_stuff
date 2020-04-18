#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include "function.h"

int menuInput = 0;
int yMax, xMax, height, width, startY, startX;
int difficulty = 100000; //default is easy
int highScore = 0;
FILE *highScoreFile;




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

void mainMenu(void) {
    
    char mainMenuOption[3][11] = {"Start", "Difficulty", "Exit"};
    int highlight = 0;
    int onMenu = 1;

    highScoreFile = fopen("highScore.txt","r");
        if (highScoreFile == NULL)
            goto mainMenuInt;

    fscanf(highScoreFile,"1 : %d", &highScore);
    fclose(highScoreFile);

    //mainMenu window initialization
    mainMenuInt:
    setScreen();
    WINDOW * mainMenu = newwin(height, width, startY, startX);
    refresh();
    box (mainMenu, 0, 0);
    wrefresh(mainMenu);
    keypad(mainMenu, TRUE);
    
    //highScore window initialization
    WINDOW * highScoreWin = newwin(5, (width/2), (startY - 5), (startX + (width/2)));
    refresh();
    box (highScoreWin, 0, 0);
    mvwprintw(highScoreWin, 2 , 2, "Score : %d", highScore);
    wrefresh(highScoreWin);


    while (onMenu) {

        for (int i = 0; i < 3; i++) {
            if (i == highlight)
                wattron(mainMenu, A_REVERSE);

            mvwprintw(mainMenu, (height/2 + i), (width/2 - 12) ,mainMenuOption[i]);
            wattroff(mainMenu, A_REVERSE);
        }
        wrefresh(mainMenu);

        menuInput = wgetch(mainMenu); //getting the key that was pressed

        switch (menuInput) {
            case (KEY_UP):
                highlight--;
                if (highlight == -1)
                    highlight = 2;
                break;

            case (KEY_DOWN):
                highlight++;
                if (highlight == 3)
                    highlight = 0;
                break;
            
            case (10):
                switch (highlight) {
                    case (0):
                        delwin(mainMenu);
                        play(difficulty, height, width, startY, startX);
                        goto mainMenuInt;
                        break;
                        
                    case (1):
                        delwin(mainMenu);
                        difficulty = difficultyMenu(difficulty, height, width, startY, startX);
                        goto mainMenuInt;

                    case (2):
                        delwin(mainMenu);
                        onMenu = 0;
                        refresh();
                        endwin();
                        break;
                }
        }

    }

}

int main () {

    //ncurses initialization
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    mainMenu();

    endwin();

    return 0;
}
