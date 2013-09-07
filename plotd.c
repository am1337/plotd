#include "plotd.h"
#include "config.h"

int getInputChar()
{
  struct termios oldt, newt;
  int input;    
  tcgetattr( STDIN_FILENO, &oldt );
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO );
  tcsetattr( STDIN_FILENO, TCSANOW, &newt );
  input = getchar();
  tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
  return input;
}

int manualControl(void)
{
  int input;
  
  do
  {
    printf("\n");
    input = getInputChar();
    
    switch (input)
    {
      case 'w':
	moveUp(JUMP);
	break;
      case 'x':
	moveDown(JUMP);
	break;
      case 'd':
	moveRight(JUMP);	 
	break;
      case 'a':
	moveLeft(JUMP);
	break;
 
      case 'z':
	setZero(JUMP);	 
	break;
      case 'm':
	getMax(JUMP);
	break;
      case 'p':
	printf("Current position X:%d, Y:%d\n",posX,posY);
	break;
      case 'r':
	printf("Parsing input.nc\n");
	readGCodeFile("input.nc");
	break;
  
      case 'l':
	do {
	  printf("Set laser output power to:\n");
	  printf("1) low\n");
	  printf("2) medium (default)\n");
	  printf("3) high\n");
	  printf("4) maximum\n");
	  input=getInputChar();
	}
	while (input<'1'||input>'4');
	if(input=='4')
	{
	  laserPower=POW_MAX;
	  printf("Setting laser to maximum output power\n");
	}
	else if(input=='3')
	{
	  laserPower=POW_HI;
	  printf("Setting laser to high output power\n");
	}
	else if(input=='2')
	{
	  laserPower=POW_MED;
	  printf("Setting laser to medium output power\n");
	}
	else
	{
	  laserPower=POW_LOW;
	  printf("Setting laser to low output power\n");
	}
	break;
	
      case 's':
	do {
	  printf("Set speed to:\n");
	  printf("0) auto (default)\n");
	  printf("1) SNAIL\n");
	  printf("2) XSLOW\n");
	  printf("3) SLOW\n");
	  printf("4) MEDIUM\n");
	  printf("5) FAST\n");
	  input=getInputChar();
	}
	while (input<'0'||input>'5');
	
	if(input=='5')
	{
	  autoSpeed=FALSE;
	  manSpeed = FAST;
	  printf("Setting speed to FAST\n");
	}
	else if(input=='4')
	{
	  autoSpeed=FALSE;
	  manSpeed = MEDIUM;
	  printf("Setting speed to MEDIUM\n");
	}
	else if(input=='3')
	{
	  autoSpeed=FALSE;
	  manSpeed = SLOW;
	  printf("Setting speed to SLOW\n");
	}
	else if(input=='2')
	{
	  autoSpeed=FALSE;
	  manSpeed = XSLOW;
	  printf("Setting speed to XSLOW\n");
	}
	else if(input=='1')
	{
	  autoSpeed=FALSE;
	  manSpeed = SNAIL;
	  printf("Setting speed to SNAIL\n");
	}
	else
	{
	  autoSpeed=TRUE;
	  printf("Setting speed to auto\n");
	}
	break;
	
      case 'q':
	exit(0);
	break;
      default:
	printf("available functions:\n");
	printf("w		move up\n");
	printf("x		move down\n");
	printf("d		move right\n");
	printf("a		move left\n");
	printf("z		move to pos 0/0 and reset step counter\n");
	printf("m		move to max position\n");
	printf("l		set power of laser\n");
	printf("s		set speed\n");
	printf("p		print current position\n");
	printf("r 		read and plot file\n");
	printf("h		show this help\n");
	printf("q		quit\n");
	break;
    }
    setLaser(POW_OFF);
    pfio_write_output(0x00);
  }
  while (input != 'q');
	 
	 return OK;
}

void sigfunc(int sig)
{
  if(sig != SIGINT)
    return;
  else
  {
    if (cancel == 0)
    {
      cancel = 1;
      printf("press ctrl+c again to end program\n");
    }
    else
    {
      printf("Thanks for flying plotd\n");
      setLaser(POW_OFF);
      pfio_write_output(0x00);
      pfio_deinit();
      exit (0);
    }
  }
}

int main(void)
{
  // init IOs
  signal(SIGINT,sigfunc);
  if (pfio_init() < 0)
    exit(-1);
  
  // init PWM
  if (wiringPiSetup () == -1)
    exit (1);
  pinMode (1, PWM_OUTPUT);
  laserPower = POW_MED;
  
  setZero(JUMP);
  
  printf("plotd: daemon ready\n");
  manualControl();
  
  pfio_write_output(0x00);
  pfio_deinit();
  return 0;
}
