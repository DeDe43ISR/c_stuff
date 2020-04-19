#ifndef __FUNCTION_H_
#define __FUNCTION_H_

//menu.c
int Leaderboard(int height, int width, int startY, int startX);
int difficultyMenu(int difficultyLvl, int height, int width, int startY, int startX);

//game.c
int play(int difficulty, int height, int width, int startY, int startX);
void fruitCor(int* fruitY,int* fruitX, int height, int width);
void checkBor(void);
void moveSnake(void);
WINDOW * setBox(WINDOW * win, int color);

#endif
