// Functions for moving plotter

void wait4step(int speed) {
  if(speed==JUMP)
    usleep(5000);
  else {  
    if(autoSpeed==FALSE)
      speed=manSpeed;
    
    switch (speed)
    {
      case MEDIUM:
	usleep(25000);
	break;
      case SLOW:
	usleep(50000);	 
	break;
      case XSLOW:
	usleep(100000);
	break;
      case SNAIL:
	usleep(200000);	 
	break;
      case FAST:
      default:
	usleep(5000);
	break;
    }
  }
  // set pixel of bitmap
  int pixel=(((posY*4484)+(posX))*3)+54;
  if (pixel+2 <= IMAGESIZE) {
    if(laserOn==TRUE) {
      bitmap[pixel]=0x00;
      bitmap[pixel+1]=0x00;
      bitmap[pixel+2]=0x00;
    }
    else
      bitmap[pixel+2]=0x00;
  }
}  

int moveDown(int speed) {
  if ((pfio_read_input() & DOWN) == 0)
  {
    if ((stepY + 1) >= ARRAY_SIZE(patternsY))
      stepY = 0;
    else 
      stepY++;
    
    if(!SIM)
      pfio_write_output(patternsX[stepX] + patternsY[stepY]);
    posY--;
    if(!SIM)
      wait4step(speed);
    return OK;
  }
  return ENDPOS;
}

int moveUp(int speed) {
  if ((pfio_read_input() & UP) == 0)
  {
    if (stepY <= 0)
      stepY = ARRAY_SIZE(patternsY) - 1;
    else 
      stepY--;
    
    if(!SIM)
      pfio_write_output(patternsX[stepX] + patternsY[stepY]);
    posY++;
    if(!SIM)
      wait4step(speed);
    return OK;
  }
  return ENDPOS;
}

int moveLeft(int speed) {
  if ((pfio_read_input() & LEFT) == 0)
  {
    if ((stepX + 1) >= ARRAY_SIZE(patternsX))
      stepX = 0;
    else 
      stepX++;
    
    if(!SIM)
      pfio_write_output(patternsX[stepX] + patternsY[stepY]);
    posX--;
    if(!SIM)
      wait4step(speed);
    return OK;
  }
  return ENDPOS;
}

int moveRight(int speed) {
  if ((pfio_read_input() & RIGHT) == 0)
  {
    if (stepX <= 0)
      stepX = ARRAY_SIZE(patternsX) - 1;
    else 
      stepX--;
    
    if(!SIM)
      pfio_write_output(patternsX[stepX] + patternsY[stepY]);
    posX++;
    if(!SIM)
      wait4step(speed);
    return OK;
  }
  return ENDPOS;
}

int moveDownLeft(int speed) {
  if ((pfio_read_input() & DOWN) == 0 && (pfio_read_input() & LEFT) == 0)
  {
    if ((stepY + 1) >= ARRAY_SIZE(patternsY))
      stepY = 0;
    else 
      stepY++;
    
    if ((stepX + 1) >= ARRAY_SIZE(patternsX))
      stepX = 0;
    else 
      stepX++;
    
    if(!SIM)
      pfio_write_output(patternsX[stepX] + patternsY[stepY]);
    posX--;
    posY--;
    if(!SIM)
      wait4step(speed);
    return OK;
  }
  return ENDPOS;
}

int moveDownRight(int speed) {
  if ((pfio_read_input() & DOWN) == 0 && (pfio_read_input() & RIGHT) == 0)
  {
    if ((stepY + 1) >= ARRAY_SIZE(patternsY))
      stepY = 0;
    else 
      stepY++;
    
    if (stepX <= 0)
      stepX = ARRAY_SIZE(patternsX) - 1;
    else 
      stepX--;
    
    if(!SIM)
      pfio_write_output(patternsX[stepX] + patternsY[stepY]);
    posX++;
    posY--;
    if(!SIM)
      wait4step(speed);
    return OK;
  }
  return ENDPOS;
}

int moveUpLeft(int speed) {
  if ((pfio_read_input() & UP) == 0 && (pfio_read_input() & LEFT) == 0)
  {
    if (stepY <= 0)
      stepY = ARRAY_SIZE(patternsY) - 1;
    else 
      stepY--;
    
    if ((stepX + 1) >= ARRAY_SIZE(patternsX))
      stepX = 0;
    else 
      stepX++;
    
    if(!SIM)
      pfio_write_output(patternsX[stepX] + patternsY[stepY]);
    posX--;
    posY++;
    if(!SIM)
      wait4step(speed);
    return OK;
  }
  return ENDPOS;
}

int moveUpRight(int speed) {
  if ((pfio_read_input() & UP) == 0 && (pfio_read_input() & RIGHT) == 0)
  {
    if (stepY <= 0)
      stepY = ARRAY_SIZE(patternsY) - 1;
    else 
      stepY--;
    
    if (stepX <= 0)
      stepX = ARRAY_SIZE(patternsX) - 1;
    else 
      stepX--;
    
    if(!SIM)
      pfio_write_output(patternsX[stepX] + patternsY[stepY]);
    posX++;
    posY++;
    if(!SIM)
      wait4step(speed);
    return OK;
  }
  return ENDPOS;
}

int move2pos(int X, int Y, int speed)
{
  int ret=OK;

  while (posX < X && posY < Y && ret==OK)
    ret=moveUpRight(speed);
  ret=OK;
  while (posX < X && posY > Y && ret==OK)
    ret=moveDownRight(speed);
  ret=OK;
  while (posX > X && posY > Y && ret==OK)
    ret=moveDownLeft(speed);
  ret=OK;
  while (posX > X && posY < Y && ret==OK)
    ret=moveUpLeft(speed);
  ret=OK;
  while (posY > Y && ret==OK)
    ret=moveDown(speed);
  ret=OK;
  while (posY < Y && ret==OK)
    ret=moveUp(speed);
  ret=OK;
  while (posX > X && ret==OK)
    ret=moveLeft(speed);
  ret=OK;
  while (posX < X && ret==OK)
    ret=moveRight(speed);
  ret=OK;
  
  if(X==posX && Y==posY)
    return OK;
  else
    return ENDPOS;
}

int setZero(){
  int ret;
  
  printf("Resetting plotter\n");
  if(!SIM)
  {
    do
    {
      ret = moveDownLeft(JUMP);
    }
    while (ret == OK);
  }
  
  if(!SIM)
  {    
    do
    {
      ret = moveDown(JUMP);
    }
    while (ret == OK);
  }
  
  if(!SIM)
  {	
    do
    {
      ret = moveLeft(JUMP);
    }
    while (ret == OK);
  }
    
  printf("Position 0/0 reached, error was %d/%d\n", posX,posY);
  posX = 0;
  posY = 0;
  
  return OK;
}  

int getMax(){
  int ret;
  
  if(!SIM)
  {
    do
    {
      ret = moveUpRight(FAST);
    }
    while (ret == OK);
  } 
  if(!SIM)
  {
    do
    {
      ret = moveUp(FAST);
    }
    while (ret == OK);
  }
  
  if(!SIM)
  {
    do
    {
      ret = moveRight(FAST);
    }
    while (ret == OK);
  }
  
  printf("Position %d/%d reached\n", posX,posY);
  return OK;
}  

