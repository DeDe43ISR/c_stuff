#include <ncurses.h>

#define FRUIT_COLOR 1
#define BLACK_COLOR 2
#define TAIL_COLOR 3
#define HEAD_COLOR 4
#define BORDER_COLOR 5

int yMax, xMax, height, width, startY, startX;

WINDOW * setBox(WINDOW * win) {
    wattron(win, COLOR_PAIR(BORDER_COLOR));
    box (win, 0, 0);
    wattroff(win, COLOR_PAIR(BORDER_COLOR));
    return win;
}

WINDOW * printDot(WINDOW * win, int y, int x, int color) {
        wattron(win, COLOR_PAIR(color));
        mvwaddch(win, y, x,' ');
        wattroff(win, COLOR_PAIR(color));
        return win;
}

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

void play(int height, int width, int startY, int startX) {
    int field[40][20];
    int playing = 1;

    //game window initialization
    WINDOW * gameWin = newwin(height, width, startY, startX);
    refresh();
    game = setBox(gameWin);
    keypad(game, TRUE);
    nodelay(game, TRUE);

    while (playing) {
        
        gameWin = printDot(gameWin, snakeYX[0][0], snakeYX[1][0], HEAD_COLOR);


        usleep(100000);
    }
}
int main () {

    //ncurses initialization
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    //set colors
    start_color();
    init_pair(FRUIT_COLOR, COLOR_RED, COLOR_RED);
    init_pair(BLACK_COLOR, COLOR_BLACK, COLOR_BLACK);
    init_pair(TAIL_COLOR, COLOR_GREEN, COLOR_GREEN);
    init_pair(HEAD_COLOR, COLOR_BLUE, COLOR_BLUE);
    init_pair(BORDER_COLOR, COLOR_MAGENTA, COLOR_MAGENTA);

    endwin();

}
