CC=gcc
CFLAGS=-Wall
INCLUDES=-L/usr/local/lib/ -lpiface-1.0 -lm -lwiringPi -lwiringPiDev -lpthread -lMagickWand -lMagickCore

plotd: plotd.c
	$(CC) `Wand-config --cflags --cppflags` $(CFLAGS) $(INCLUDES) -o plotd plotd.c `Wand-config --ldflags --libs`

clean:
	rm *.o
