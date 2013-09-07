#ifndef _GCODE_
#define _GCODE_

#include "config.h"
#include "gcode.c"

extern int posX;
extern int posY;
extern int stepX;
extern int stepY;

int readGCodeFile(char* input);

#endif //_GCODE_