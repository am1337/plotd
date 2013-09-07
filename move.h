#ifndef _MOVE_
#define _MOVE_

#include "config.h"
#include "move.c"

extern int posX;
extern int posY;
extern int stepX;
extern int stepY;

void wait4step(int speed);
int moveDown(int speed);
int moveUp(int speed);
int moveLeft(int speed); 
int moveRight(int speed);
int moveDownLeft(int speed); 
int moveDownRight(int speed);
int moveUpLeft(int speed);
int moveUpRight(int speed);
int move2pos(int X, int Y, int speed);
int setZero();
int getMax();

#endif //_MOVE_