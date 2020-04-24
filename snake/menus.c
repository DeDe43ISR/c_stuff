#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include "main.h"

int difficultyMenu(int difficultyLvl, int height, int width, int startY, int startX) {
    
    int onMenu = 1;
    int input;
    int highlight = 0;
    char difficultyOption[3][10] = {"Easy", "Hard", "GG"};
    size_t difficultyMenuLen = sizeof(difficultyOption)/sizeof(difficultyOption[0]);

    WINDOW * difficultyMenuWin = newwin(height, width, startY, startX);
    refresh();
    difficultyMenuWin = setBox(difficultyMenuWin);
    wrefresh(difficultyMenuWin);
    keypad(difficultyMenuWin, TRUE);
    while (onMenu) {

        for (int i = 0; i < difficultyMenuLen; i++) {
            if (i == highlight)
                wattron(difficultyMenuWin, A_REVERSE);

            mvwprintw(difficultyMenuWin, (height/2 + i), (width/2 - 12) ,difficultyOption[i]);
            wattroff(difficultyMenuWin, A_REVERSE);
        }
        wrefresh(difficultyMenuWin);

        input = wgetch(difficultyMenuWin); //getting the key that was pressed

        switch (input) {
            case (KEY_UP):
                highlight--;
                if (highlight == -1)
                    highlight = (difficultyMenuLen - 1);
                break;

            case (KEY_DOWN):
                highlight++;
                if (highlight == difficultyMenuLen)
                    highlight = 0;
                break;
            
            case (10):
                switch (highlight) {
                    case (0):
                        return 40000;
                        delwin(difficultyMenuWin);
                        onMenu = 0;
                        break;
                        
                    case (1):
                        return 10000;
                        delwin(difficultyMenuWin);
                        onMenu = 0;
                        break;

                    case (2):
                        return 1000;
                        delwin(difficultyMenuWin);
                        onMenu = 0;
                        break;
            }
        }
    }
    wrefresh(difficultyMenuWin);
    return 10000; //return default value to remove compiler warnings
}

int Leaderboard(int height, int width, int startY, int startX) {
    
    FILE *scoreFile;
    int printScore, input;
    int highlight = 0, onMenu = 1;
    char leaderBoardOption[2][15] = {"Delete Data", "Back"};
    size_t leaderBoardMenuLen = sizeof(leaderBoardOption)/sizeof(leaderBoardOption[0]);

    WINDOW * leaderboardWin = newwin(height, width, startY, startX);
    refresh();
    leaderboardWin = setBox(leaderboardWin);
    wrefresh(leaderboardWin);
    keypad(leaderboardWin, TRUE);

    scoreFile = fopen("highScore.txt", "r");
    if (scoreFile == NULL) {
        mvwprintw(leaderboardWin, (height/2), (width/2 - 12), "No High Score File..¯\\_(-_-)_/¯");
        wrefresh(leaderboardWin);
        input = wgetch(leaderboardWin); //getting the key that was pressed
        return 1;
    }

    mvwprintw(leaderboardWin, 3, (width/2 - 8), "LeaderBoard");

    for(int i = 1;fscanf(scoreFile, "%d\n", &printScore) != EOF;i++) {
        mvwprintw(leaderboardWin, (4 + i), (width/2 - 5), "%d : %d", i, printScore);
    }
    
    while (onMenu) {
        for (int i = 0; i < 2; i++) {
            if (i == highlight)
                wattron(leaderboardWin, A_REVERSE);

            mvwprintw(leaderboardWin, (height - 5 + i), (width - 15) ,leaderBoardOption[i]);
            wattroff(leaderboardWin, A_REVERSE);
        }
        wrefresh(leaderboardWin);
        input = wgetch(leaderboardWin); //getting the key that was pressed

        switch (input) {
            case (KEY_UP):
                highlight--;
                if (highlight == -1)
                    highlight = (leaderBoardMenuLen - 1);
                break;

            case (KEY_DOWN):
                highlight++;
                if (highlight == leaderBoardMenuLen)
                    highlight = 0;
                break;
            
            case (10):
                switch (highlight) {
                    case (0):
                        remove("highScore.txt");
                        delwin(leaderboardWin);
                        onMenu = 0;
                        break;
                        
                    case (1):
                        delwin(leaderboardWin);
                        onMenu = 0;
                        break;
            }
        }
    }
    delwin(leaderboardWin);

}

void fuckMeUp(int height, int width, int startY, int startX) {

    int running = 1;

    WINDOW *  fuckMeUpWin = newwin(height, width, startY, startX);
    refresh();
    fuckMeUpWin = setBox(fuckMeUpWin);
    wrefresh(fuckMeUpWin);

    while (running) {
        bkgd(COLOR_PAIR(rand() % 5));
        refresh();
        wbkgd(fuckMeUpWin, COLOR_PAIR(rand() % 5));
        wrefresh(fuckMeUpWin);
        usleep(100000);
    }
}
