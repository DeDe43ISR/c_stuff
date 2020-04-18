#include <ncurses.h>

int difficultyMenu(int difficultyLvl, int height, int width, int startY, int startX) {
    
    int onMenu = 1;
    int input;
    int highlight = 0;
    char difficultyOption[3][10] = {"Easy", "Hard", "GG"};

    WINDOW * difficultyMenuWin = newwin(height, width, startY, startX);
    refresh();
    box (difficultyMenuWin, 0, 0);
    wrefresh(difficultyMenuWin);
    keypad(difficultyMenuWin, TRUE);
    while (onMenu) {

        for (int i = 0; i < 3; i++) {
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
                        return 100000;
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

void Leaderboard(int height, int width, int startY, int startX) {
    
    int scorevariable;
    int oonMenu = 1;
    int inputa;
    int hhighlight = 0;
    char Score[3][10] = {"whatever", "asd", "asdasd"};

    WINDOW * LeaderboardWin = newwin(height, width, startY, startX);
    refresh();
    box (LeaderboardWin, 0, 0);
    wrefresh(LeaderboardWin);
    keypad(LeaderboardWin, TRUE);
    while (oonMenu) {

        for (int i = 0; i < 3; i++) {
            if (i == hhighlight)
                wattron(LeaderboardWin, A_REVERSE);

            mvwprintw(LeaderboardWin, (height/2 + i), (width/2 - 12) ,Score[i]);
            wattroff(LeaderboardWin, A_REVERSE);
        }
        wrefresh(LeaderboardWin);

        inputa = wgetch(LeaderboardWin); //getting the key that was pressed

        switch (inputa) {
            case (KEY_UP):
                hhighlight--;
                if (hhighlight == -1)
                    hhighlight = 2;
                break;

            case (KEY_DOWN):
                hhighlight++;
                if (hhighlight == 3)
                    hhighlight = 0;
                break;

            case (10):
                switch (hhighlight) {
                    case (0):
//                        return 100000;
                        delwin(LeaderboardWin);
                        oonMenu = 0;
                        break;

                    case (1):
//                        return 10000;
                        delwin(LeaderboardWin);
                        oonMenu = 0;
                        break;

                    case (2):
//                        return 1000;
                        delwin(LeaderboardWin);
                        oonMenu = 0;
                        break;
            }
        }
    }
    wrefresh(LeaderboardWin);
}

