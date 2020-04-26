#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "function.h"

#define FRUIT_COLOR 1
#define BLACK_COLOR 2
#define TAIL_COLOR 3
#define HEAD_COLOR 4
#define BORDER_COLOR 5

int menuInput = 0;
int yMax, xMax, height, width, startY, startX;
int difficulty = 40000; //default is easy
int highScore = 0, gameScore = 0;
int err = 0;
char nick[10];
FILE *highScoreFile;

WINDOW * setBox(WINDOW * win) {
    wattron(win, COLOR_PAIR(BORDER_COLOR));
    box (win, 0, 0);
    wattroff(win, COLOR_PAIR(BORDER_COLOR));
    return win;
}

void checkScore(int gameScore, char *gameNick) {
    int allScore[5] = {0};
    char allNicks[5][10];
    char tempString[10];
    int rating, tempScore;
    bool reWrite = false;

    //open highScore.txt file and create one if doesn't exist with current score has highest
    highScoreFile = fopen("highScore.txt","r");
    if (highScoreFile == NULL) {
        highScoreFile = fopen("highScore.txt","w");
        fprintf(highScoreFile, "%s : %d\n",gameNick ,gameScore);
        for (int i = 0; i < 4;i++)
            fprintf(highScoreFile, "bavner : 0\n");

        fclose(highScoreFile);
        return;
    }

    //save all scores to array
    highScoreFile = fopen("highScore.txt","r");
    for (int i = 0; i < 5; i++) {
        fscanf(highScoreFile, "%s : %d\n",allNicks[i], &allScore[i]);
    }

    fclose(highScoreFile);
    //check if current score is higher and re-write the file if he does
    for (int i = 0; i < 5; i++) {
        if (gameScore > allScore[i]) {
            reWrite = TRUE;
            rating = i;
            for (int k = 4; k > rating; k--) {
                allScore[k] = allScore[k-1];
                strcpy(tempString, allNicks[k-1]);
                strcpy(allNicks[k], tempString);
            }
            allScore[rating] = gameScore;
            i = 5;
        }
    }
    if (reWrite == TRUE) {
        highScoreFile = fopen("highScore.txt","w");

        for (int i = 0; i < 5; i++)
            fprintf(highScoreFile, "%s : %d\n",allNicks[i], allScore[i]);

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
    size_t mainMenuLen = sizeof(mainMenuOption)/sizeof(mainMenuOption[0]);  // number of elements in mainMenuoOption array 
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
    mainMenu = setBox(mainMenu);
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

            case ('&'):
                delwin(mainMenu);
                fuckMeUp(height, width, startY, startX);
                goto mainMenuInt;

            
            case (10):
                switch (highlight) {
                    case (0):
                        echo();
                        wclear(mainMenu);
                        mainMenu = setBox(mainMenu);
                        mvwprintw(mainMenu, (height/2), (width/2 - 12) , "Please enter nick : ");
                        wrefresh(mainMenu);
                        mvwgetstr(mainMenu, (height/2), (width/2 + 8),nick);
                        noecho();
                        delwin(mainMenu);
                        gameScore = play(difficulty, height, width, startY, startX);
                        checkScore(gameScore, nick);
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
