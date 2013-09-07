#ifndef _DRAW_
#define _DRAW_

#include "config.h"
#include "move.h"
#include "laser.h"
#include "draw.c"

extern int posX;
extern int posY;
extern int stepX;
extern int stepY;

int drawLine(int X1, int Y1, int X2, int Y2, int speed, int power);
int drawCircle(int X, int Y, int radius, int clockwise, int speed, int power);
int drawPieSlice(int X1, int Y1, int X2, int Y2, int X, int Y, float angleStart, float angleStop, int radius, int clockwise, int speed, int power);

#endif //_DRAW_