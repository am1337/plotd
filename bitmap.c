void initBitmap(void)
{/*
  // -- FILE HEADER -- //
  
  // bitmap signature
  bitmap[0] = 'B';
  bitmap[1] = 'M';
  
  // file size
  bitmap[2] = 0x46; // 40 + 14 + 3xPixel
  bitmap[3] = 0xe4;
  bitmap[4] = 0xfc;
  bitmap[5] = 0x05;
  
  int i;
  
  // reserved field (in hex. 00 00 00 00)
  for(i = 6; i < 10; i++) bitmap[i] = 0;
  
  // offset of pixel data inside the image
  for(i = 10; i < 14; i++) bitmap[i] = 0;
  
  // -- BITMAP HEADER -- //
  
  // header size
  bitmap[14] = 40;
  for(i = 15; i < 18; i++) bitmap[i] = 0;
  
  // width of the image
  bitmap[18] = 0x84;	// X=4484
  bitmap[19] = 0x11;
  for(i = 20; i < 22; i++) bitmap[i] = 0;
  
  // height of the image
  bitmap[22] = 0x2c;	// Y=7468
  bitmap[23] = 0x1d;
  for(i = 24; i < 26; i++) bitmap[i] = 0;
  
  // reserved field
  bitmap[26] = 1;
  bitmap[27] = 0;
  
  // number of bits per pixel
  bitmap[28] = 24; // 3 byte
  bitmap[29] = 0;
  
  // compression method (no compression here)
  for(i = 30; i < 34; i++) bitmap[i] = 0;
  
  // size of pixel data
  bitmap[34] = 0x10; // 100423683 bits => 33474561 pixels
  bitmap[35] = 0xe4;
  bitmap[36] = 0xfc;
  bitmap[37] = 0x05;
  
  // horizontal resolution of the image - pixels per meter (2835)
  bitmap[38] = 0;
  bitmap[39] = 0;
  bitmap[40] = 0;
  bitmap[41] = 0;
  
  // vertical resolution of the image - pixels per meter (2835)
  bitmap[42] = 0;
  bitmap[43] = 0;
  bitmap[44] = 0;
  bitmap[45] = 0;
  
  // color pallette information
  for(i = 46; i < 50; i++) bitmap[i] = 0;
  
  // number of important colors
  for(i = 50; i < 54; i++) bitmap[i] = 0;
  
  // -- PIXEL DATA -- //
  for(i = 54; i < IMAGESIZE; i++) bitmap[i] = 0xff;*/
}

void writeBitmap(void) // TODO Change to magickwand and png-output
{
/*  FILE *file;
  int i;
  file = fopen("bitmap.bmp", "w+");
  
  for(i = 0; i < IMAGESIZE; i++)
  {
    fputc(bitmap[i], file);
  }
  fclose(file);
  system("convert bitmap.bmp bitmap.png");
  printf("Image created\n");
  */
}

int initImageIn()
{
  int x,y;
  for(x=0;x<MAX_WIDTH;x++)
  {
    for(y=0;y<MAX_HEIGHT;y++) 
    {
      image_in[x][y]=0;
    }
  }
  return OK;
}

int initImageOut()
{
  int x,y;
  for(x=0;x<MAX_WIDTH;x++)
  {
    for(y=0;y<MAX_HEIGHT;y++) 
    {
      image_out[x][y]=0;
    }
  }
  return OK;
}

int parseImage(void)
{
  int x,y;
  
  MagickBooleanType status;
  MagickWand *magick_wand;
  //PixelWand *color;
  MagickPixelPacket pixel;
  PixelWand **pixels;
  
  MagickWandGenesis();
  magick_wand=NewMagickWand();
  status=MagickReadImage(magick_wand,"image.png");
  
  if (status == MagickFalse)
    printf("ERROR\n");  
  
  size_t width=MagickGetImageWidth(magick_wand);
  size_t height=MagickGetImageHeight(magick_wand);
  
  printf("X:%d, Y:%d\n",width, height);
  int image_width = MAX_WIDTH;
  int image_height = MAX_HEIGHT;
  if(width < MAX_WIDTH)
    image_width=width;
  if(height < MAX_HEIGHT)
    image_height=height;
  //
  PixelIterator* iterator = NewPixelIterator(magick_wand);
  //PixelWand **pixels = PixelGetNextIteratorRow(iterator,&number_wands);
  
  for (y=0; y < image_height; y++)
  //   for (y=0; y < 1; y++)
  {
    pixels=PixelGetNextIteratorRow(iterator,&width);
    for (x=0; x < image_width; x++) 
    {
      PixelGetMagickColor(pixels[x],&pixel);
      //printf("R/G/B %g/%g/%g\n",round(pixel.red),round(pixel.green),round(pixel.blue));
      int real_y= image_height-y-1;
      if (real_y < 0) 
      {
	real_y = 0;
	printf("ERRRORRR\n");
      }
      else
      {
	/*if (round(pixel.red)==0&&round(pixel.green)==0&&round(pixel.blue)==0)
	  image_in[x][real_y]=255;
	if (round(pixel.red)<4095)
	  image_in[x][real_y]=255;*/
	image_in[x][real_y] = 65535 - round(pixel.red);
      }
    }
    PixelSyncIterator(iterator);
  }
  
  PixelSyncIterator(iterator);
  iterator=DestroyPixelIterator(iterator);
  ClearMagickWand(magick_wand);
  
  printf("Parsed bitmap\n");  
  magick_wand=DestroyMagickWand(magick_wand);
  MagickWandTerminus();
   }