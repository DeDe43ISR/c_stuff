#ifndef __GAME_H_
#define __GAME_H_

void play(int difficulty, int height, int width, int startY, int startX);
void fruitCor(int* fruitY,int* fruitX, int height, int width);
void checkBor(void);
void moveSnake(void);

#endif
