// parse gcode files

int setSpeed(float f)
{
  if (f >= 40)
    return FAST;
  if (f >= 30)
    return MEDIUM;
  if (f >= 20)
    return SLOW;
  if (f >= 10)
    return XSLOW;
  return SNAIL;
return FAST;
}

int readGCodeFile(char* input)
{
  FILE *file;
  char *stringX;
  char *stringY;
  char *stringI;
  char *stringJ;
  char *stringF;
  char line[500];
  char delimiter[] = " ";
  char delimiterF[] = "F";
  // char *ptr;
  char *substring;
  float ftmp=0;
  int X;
  int Y;
  int I;
  int J;
  int rX;
  int rY;
  int Xold=0;
  int Yold=0;
  int clockwise;
  file = fopen(input,"r");
  char *ret;
  int radius;
  int speed = FAST; // set to SLOW etc, whatever is neccessary TODO depends on F value
  //int i=0;
    
  initImageOut();
    
  do
  {
    if (cancel == 1) {
      cancel = 0;
      break;
    }
    
  /*  if (i%100==0)
    {
      setZero(JUMP);
      i=1;
    }*/
    
    ret = fgets(line,499,file);
    // TODO While-Schleife die alle Werte ausliest und zuordnet anstatt xyzi-Reihenfolge hardcoded
    
    if(strncmp(line, "G0 ", 3) == 0)
    {
      stringX = strtok(line, delimiter);
      stringX = strtok(NULL, delimiter);
      stringY = strtok(NULL, delimiter);
      // get X
      substring = &stringX[1];
      ftmp = atof(substring);
      X = ftmp * STEPS_PER_MM;
      // get Y
      substring = &stringY[1];
      ftmp = atof(substring);
      Y = ftmp * STEPS_PER_MM;
      
      printf("Jump to X:%d Y:%d\n",X,Y);
  move2pos(X,Y,JUMP);
  Xold=X;
  Yold=Y;
   //   i++;
    }
    if(strncmp(line, "G1 F", 4) == 0)
    {
      stringF = strtok(line, delimiter);
      stringF = strtok(NULL, delimiter);
      // get F
      substring = &stringF[1];
      ftmp = atof(substring);
      speed=setSpeed(ftmp);
    //  i++;
    }
    if(strncmp(line, "G1F", 3) == 0)
    {
      stringF = strtok(line, delimiterF);
      stringF = strtok(NULL, delimiterF);
      // get F
      substring = &stringF[0];
      ftmp = atof(substring);
      speed=setSpeed(ftmp);
     // i++;
    }
    if(strncmp(line, "G01", 3) == 0 || strncmp(line, "G1  ", 4) == 0)
    {
      stringX = strtok(line, delimiter);
      stringX = strtok(NULL, delimiter);
      stringY = strtok(NULL, delimiter);
      // get X
      substring = &stringX[1];
      ftmp = atof(substring);
      X = ftmp * STEPS_PER_MM;
      // get Y	
      substring = &stringY[1];
      ftmp = atof(substring);
      Y = ftmp * STEPS_PER_MM;
      
      drawLine(Xold, Yold, X, Y, speed, 0);
      
      Xold=X;
      Yold=Y;
    //  i++;
    }
    if(strncmp(line, "G02", 3) == 0 || strncmp(line, "G03", 3) == 0 )
    {
      if (strncmp(line, "G02", 3) == 0)
	clockwise = TRUE;
      else
	clockwise = FALSE;
      stringX = strtok(line, delimiter);
      stringX = strtok(NULL, delimiter);
      stringY = strtok(NULL, delimiter);
      stringI = strtok(NULL, delimiter);
      stringJ = strtok(NULL, delimiter);
      // get X
      substring = &stringX[1];
      ftmp = atof(substring);
      X = ftmp * STEPS_PER_MM;
      // get Y	
      substring = &stringY[1];
      ftmp = atof(substring);
      Y = ftmp * STEPS_PER_MM;
      // get I
      substring = &stringI[1];
      ftmp = atof(substring);
      I = ftmp * STEPS_PER_MM;
      // get J	
      substring = &stringJ[1];
      ftmp = atof(substring);
      J = ftmp * STEPS_PER_MM;

      radius = hypot(I, J);
      
      rX = Xold+I;
      rY = Yold+J;
 
      // TEST ANFANG
      float angleStart=0;
      float angleStop=0;
      
  //    printf("PieSlice X/Y 1:%d/%d 2:%d/%d r:%d/%d radius:%d richtung:%d\n",Xold, Yold, X, Y, rX, rY, radius, clockwise);
  /*    if (Xold>rX)
	printf("rechts\n");
      else if (Xold==rX)
	printf("mitte\n");
      else
	printf("links\n");
      
      if (Yold>rY)
	printf("oben\n");
      else if (Yold==rY)
	printf("mitte\n");
      else
	printf("unten\n");*/
      
 //     if (Xold>=rX && Yold>=rY)
   //   {
//	printf("EK Seg1 (oben rechts)\n");
	int dX=Xold-rX;
	int dY=Yold-rY;
/*	printf("dX=%d\n",dX);
	printf("dY=%d\n",dY);
	printf("TEST %f\n",atan2(dY,dX));*/
	angleStart=atan2(dY,dX);
	//printf("winkel: %f\n",angleStart * 360 / (2 * M_PI));
 //     }
      dX=X-rX;
      dY=Y-rY;
      angleStop=atan2(dY,dX);
      //printf("winkel: %f\n",angleStop * 360 / (2 * M_PI));
      
 /*     if (X>rX)
	printf("rechts\n");
      else if (X==rX)
	printf("mitte\n");
      else
	printf("links\n");
      
      if (Y>rY)
	printf("oben\n");
      else if (Y==rY)
	printf("mitte\n");
      else
	printf("unten\n");            
   */   
      // TEST ENDE
      drawPieSlice(Xold, Yold, X, Y, rX, rY, angleStart, angleStop, radius, clockwise, speed, 0);
      
      Xold=X;
      Yold=Y;  
    //  i++;
    }
  }
  while(ret != NULL);
  
  setZero(JUMP);
  printf("Plot finished\n");
  //writeBitmap();
  
  return OK;
}