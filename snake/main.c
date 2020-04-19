#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include "function.h"

#define FRUIT_COLOR 1
#define BLACK_COLOR 2
#define TAIL_COLOR 3
#define HEAD_COLOR 4
#define BORDER_COLOR 5

int menuInput = 0;
int yMax, xMax, height, width, startY, startX;
int difficulty = 100000; //default is easy
int highScore = 0, gameScore = 0;
int err = 0;
FILE *highScoreFile;

void checkScore(int gameScore) {
    int allScore[5] = {0};
    int rating, tempScore;
    bool reWrite = false;

    //open highScore.txt file and create one if doesn't exist with current score has highest
    highScoreFile = fopen("highScore.txt","r");
    if (highScoreFile == NULL) {
        highScoreFile = fopen("highScore.txt","w");
        fprintf(highScoreFile, "%d", gameScore);
        fclose(highScoreFile);
    }

    //save all scores to array
    highScoreFile = fopen("highScore.txt","r");
    for (int i = 0; i < 5; i++)
        fscanf(highScoreFile, "%d", &allScore[i]);

    //check if current score is higher and re-write the file if he does
    fclose(highScoreFile);
    for (int i = 0; i < 5; i++) {
        if (gameScore > allScore[i]) {
            reWrite = TRUE;
            rating = i;
            while (i < 4) {
                tempScore = allScore[i+1];
                allScore[i+1] = allScore[i];
                allScore[i+2] = tempScore;
                i++;
            }
            allScore[rating] = gameScore;
        }
    }
    if (reWrite == TRUE) {
        highScoreFile = fopen("highScore.txt","w");

        for (int i = 0; i < 5; i++)
            fprintf(highScoreFile, "%d\n", allScore[i]);

        fclose(highScoreFile);
    }
    if (gameScore > highScore) {
        highScore = gameScore;
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

void mainMenu(void) {
    
    char mainMenuOption[4][15] = {"Start", "Difficulty","Leaderboard", "Exit"};
    int highlight = 0;
    size_t mainMenuLen = sizeof(mainMenuOption)/sizeof(mainMenuOption[0]);  // number of elements in mainMenuoPtion array 
    int onMenu = 1;

    highScoreFile = fopen("highScore.txt","r");
        if (highScoreFile == NULL)
            goto mainMenuInt;

    fscanf(highScoreFile,"%d", &highScore);
    fclose(highScoreFile);

    //mainMenu window initialization
    mainMenuInt:
    setScreen();
    WINDOW * mainMenu = newwin(height, width, startY, startX);
    refresh();
    //box (mainMenu, 0, 0);
    mainMenu = setBox(mainMenu, 5);
    
    wrefresh(mainMenu);
    keypad(mainMenu, TRUE);
    
    //highScore window initialization
    WINDOW * highScoreWin = newwin(5, (width/2), (startY - 5), (startX + (width/2)));
    refresh();
    box (highScoreWin, 0, 0);
    mvwprintw(highScoreWin, 2 , 2, "High Score : %d", highScore);
    wrefresh(highScoreWin);


    while (onMenu) {

        for (int i = 0; i < mainMenuLen; i++) {
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
                    highlight = (mainMenuLen - 1);
                break;

            case (KEY_DOWN):
                highlight++;
                if (highlight == mainMenuLen)
                    highlight = 0;
                break;
            
            case (10):
                switch (highlight) {
                    case (0):
                        delwin(mainMenu);
                        gameScore = play(difficulty, height, width, startY, startX);
                        checkScore(gameScore);
                        goto mainMenuInt;
                        break;
                        
                    case (1):
                        delwin(mainMenu);
                        difficulty = difficultyMenu(difficulty, height, width, startY, startX);
                        goto mainMenuInt;
                    
                    case (2):
                        delwin(mainMenu);
                        err = Leaderboard(height, width, startY, startX);
                        goto mainMenuInt;

                    case (3):
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

    start_color();
    init_pair(FRUIT_COLOR, COLOR_RED, COLOR_RED);
    init_pair(BLACK_COLOR, COLOR_BLACK, COLOR_BLACK);
    init_pair(TAIL_COLOR, COLOR_GREEN, COLOR_GREEN);
    init_pair(HEAD_COLOR, COLOR_BLUE, COLOR_BLUE);
    init_pair(BORDER_COLOR, COLOR_MAGENTA, COLOR_MAGENTA);

    mainMenu();

    endwin();

    return 0;
}
