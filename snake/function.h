#ifndef __FUNCTION_H_
#define __FUNCTION_H_

//game.c
WINDOW * printDot(WINDOW * win,int y, int x, int color);
int play(int difficulty, int height, int width, int startY, int startX);
void fruitCor(int* fruitY,int* fruitX, int height, int width);
void checkBor(void);
void moveSnake(void);

//menus.c
int Leaderboard(int height, int width, int startY, int startX);
int difficultyMenu(int difficultyLvl, int height, int width, int startY, int startX);
void fuckMeUp(int height, int width, int startY, int startX);

#endif
