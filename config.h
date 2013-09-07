#ifndef _CONFIG_
#define _CONFIG_

#include <unistd.h>
#include <libpiface-1.0/pfio.h>
#include <termios.h>
#include <signal.h>
#include <math.h>
#include <wiringPi.h>

#define SIM 0	// 0 Move Plotter, 1 only simulate

#define PI 3.14159265

#define OK	0
#define ENDPOS	1

#define TRUE	0
#define FALSE	1

#define JUMP	-1
#define FAST	0
#define MEDIUM	1
#define SLOW	2
#define XSLOW	3
#define SNAIL   4

#define POW_OFF	0
#define POW_LOW	355
#define POW_MED	511
#define POW_HI	767
#define POW_MAX	1023

#define STEPS_PER_MM 23.622 // Valid in fullstep mode, double for half-step mode

// Image output
// image size X=4484 x Y=7468 = 33.486.512 pixel
#define PIXEL		33486512
#define IMAGESIZE	100459590 // 54 + 3 * PIXEL
char bitmap[IMAGESIZE];

// left/right is x-axis, down is 0, up is 7460
char patternsX[] 	= 	{0x5, 0x9, 0xa, 0x6}; // fullstep mode
int stepX		=	0;
int posX		=	0;

// up/down is y-axis, left is 0, right is 4506
char patternsY[] 	= 	{0x60, 0xa0, 0x90, 0x50}; // fullstep mode
int stepY		=	0;
int posY		=	0;

int laserPower = 0;	// Power of Laser
int autoSpeed = TRUE;	// If set to true, gcode-file sets speed
int manSpeed = FAST;
int cancel = 0;
int laserOn = FALSE;

// stop sensors:
#define UP	2
#define DOWN	1
#define LEFT	8
#define RIGHT	4

#endif //_CONFIG_