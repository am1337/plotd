CC=gcc
CFLAGS=-Wall
INCLUDES=-L/usr/local/lib/ -lpiface-1.0 -lm -lwiringPi -lwiringPiDev -lpthread

plotd: plotd.c
	$(CC) $(CFLAGS) $(INCLUDES) -o plotd plotd.c 

clean:
	rm *.o
