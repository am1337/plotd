// set Laser output

int setLaser(int power){
  if(power==POW_OFF)
    laserOn=FALSE;
  else
    laserOn=TRUE;
  pwmWrite (1, power) ;
  return OK;
}
