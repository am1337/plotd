// Draw lines and circles

int drawLine(int X1, int Y1, int X2, int Y2, int speed, int power)
{
  int xl, yl, x, y, dx, dy, a, b, e, tmp, stop, bisectrix;
  int ret=0;
  
  printf("Draw line from X:%d Y:%d to X:%d Y:%d\n",X1, Y1, X2, Y2);
  move2pos(X1,Y1,JUMP);  
  
  // based on http://www.cirsovius.de/CPM/Projekte/Artikel/Grafik/LinearAlgorithmus/LineDraw.html
  xl   =  1; 
  yl   =  1;
  x    = X1;  
  y    = Y1;
  stop = X2;
  dx   = X2 - X1;
  dy   = Y2 - Y1;
  bisectrix = 0;
  
  // Spiegelung an Y-Achse
  if (dx < 0)
  {
    dx = -dx;
    xl = -1;
  }
  
  // Spiegelung an X-Achse
  if (dy < 0)
  {
    dy = -dy;
    yl = -1;
  }
  
  // Spiegelung an Winkelhalbierstopr des 1. Quadranten //
  if (dx < dy)
  {
    tmp =  x;  
    x =  y;  
    y = tmp;
    tmp = dx; 
    dx = dy; 
    dy = tmp;
    tmp = xl; 
    xl = yl; 
    yl = tmp;
    stop = Y2;
    bisectrix = 1;
  }
  
  // Hilfsvariablen
  a = dy * 2;
  b = (dx * 2) - a;
  e = a - dx;
  
  // Zeichnen der Geraden
  if(!SIM)
    setLaser(laserPower);
  
  if (bisectrix == 1)
  {
    ret=move2pos(y,x,speed);
    while (x != stop && ret==OK)
    {
      x = x + xl;
      if (e > 0)
      {
	y = y + yl;
	e = e -  b;
      }
      else
      {
	e = e + a;
      }
      move2pos(y,x,speed);
    }
  }
  else
  {
    ret=move2pos(x,y,speed);
    while (x != stop && ret==OK)
    {
      x = x + xl;
      if (e > 0)
      {  
	y = y + yl;
	e = e -  b;
      }
      else
      {
	e = e + a;
      }
      move2pos(x,y,speed);
    }
  }  
  
  setLaser(POW_OFF);
  return OK;
}

int drawCircle(int X, int Y, int radius, int clockwise, int speed, int power)
{      
  int Xnew;
  int Ynew;
  int angle = 0;
  
  Xnew = X + radius;
  Ynew = Y; 
  
  printf("Draw Circe at X:%d Y:%d with R:%d\n",X, Y, radius);
  move2pos(Xnew, Ynew, JUMP);
  
  if(!SIM)
    setLaser(laserPower);
  
  if ( clockwise == TRUE )
  {
    angle = 360 * (ceil(radius/100) + 1);
    while (angle > 0)
    {
      angle--;
      Xnew = X + cos(angle*PI/(180 * (ceil(radius/100) + 1))) * radius;
      Ynew = Y + sin(angle*PI/(180 * (ceil(radius/100) + 1))) * radius;
      move2pos(Xnew, Ynew, speed);
    }
  }
  else
  {
    while (angle < 360 * (ceil(radius/100) + 1))
    {
      angle++;
      Xnew = X + cos(angle*PI/(180 * (ceil(radius/100) + 1))) * radius;
      Ynew = Y + sin(angle*PI/(180 * (ceil(radius/100) + 1))) * radius;
      move2pos(Xnew, Ynew, speed);
    }
  }
  
  setLaser(POW_OFF);
  
  return OK;
}

int drawPieSlice(int X1, int Y1, int X2, int Y2, int X, int Y, float angleStart, float angleStop, int radius, int clockwise, int speed, int power)
{      
  int Xnew;
  int Ynew;
  float angleCurrent;
  
  printf("Draw arc from X:%d Y:%d to X:%d Y:%d start angle %f, stop angle %f, radius %d\n",X1, Y1, X2, Y2, angleStart, angleStop, radius);
  move2pos(X1,Y1,JUMP);
  
  angleCurrent=angleStart;
  
  if ( clockwise == TRUE )
  {
    if(!SIM)
	  setLaser(laserPower);
    if(angleCurrent < angleStop)
	angleCurrent=angleCurrent+(2*PI);
    while (angleCurrent>angleStop)
    {
      angleCurrent=angleCurrent-(0.1/radius);
      Xnew = X + cos(angleCurrent) * radius;
      Ynew = Y + sin(angleCurrent) * radius;
      
      move2pos(Xnew, Ynew, speed);
    }
    setLaser(POW_OFF);
  }
  else
  {
    if(!SIM)
	  setLaser(laserPower);
    if(angleCurrent>angleStop)
	angleCurrent=angleCurrent-(2*PI);
    while (angleCurrent<angleStop)
    {
      angleCurrent=angleCurrent+(0.1/radius);
      Xnew = X + cos(angleCurrent) * radius;
      Ynew = Y + sin(angleCurrent) * radius;
      
      move2pos(Xnew, Ynew, speed);
    }
    setLaser(POW_OFF);
  }
  setLaser(POW_OFF);
  
  return OK;
}

int drawImage() {
  int x,y;
  setLaser(POW_OFF);
  int i=0;
  int last=0;
  int skip_lines=3;
  //for(x=0;x<MAX_WIDTH;x++)
  //for(x=0;x<MAX_WIDTH;x=x+10) // Y-Achse alle X Zeilen resetten, X-Achse muss nicht resettet werden (oder umgekehrt)
  //for(x=(MAX_WIDTH-1);x>=0;x=x-5)   
  //for( x = ( MAX_WIDTH - 1 ); x >= 0; x = x - ( 1 + skip_lines ) )
  for( x = 0; x < MAX_WIDTH; x = x + 1 + skip_lines )
  {
    printf("Line %d\n",x);
    setLaser(POW_OFF);
    i++;
    
    //if(x%2==0)
    if(i%2==0)
    {
      for(y=0;y<MAX_HEIGHT;y++)
      {
	if(image_in[x][y]>0)
	{
	  if(last>0) {
	    move2pos(x, y, manSpeed);
	    setLaser(laserPower);
	  }
	  else
	    move2pos(x, y, JUMP);
	}
	else
	  setLaser(POW_OFF);
	
	last=image_in[x][y];
      }
    }
    else
    {
      for(y=(MAX_HEIGHT-1);y>=0;y--)
      {
	if(image_in[x][y]>0)
	{
	  if(last>0) {
	    move2pos(x, y, manSpeed);
	    setLaser(laserPower);
	  }
	  else
	    move2pos(x, y, JUMP);
	}
	else
	  setLaser(POW_OFF);
	
	last=image_in[x][y];
      }
    }
    last=0;
  }
  setLaser(POW_OFF);
  return OK;
}