# Makefile
VERSION = 3.02
CC      = /usr/bin/gcc
OBJ	 = troposcatter.o
CFLAGS  = -Wall -ggdb
LDFLAGS = -lm `pkg-config --cflags --libs gtk+-2.0`
PRG 	= troposcatter

all: $(OBJ)
	$(CC) $(CFLAGS) -o $(PRG) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)

clean:
	rm -f $(PRG) *~ *.o a.out
