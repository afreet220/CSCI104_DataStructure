CC = g++
CFLAGS = -g -Wall
LDFLAGS =


all : lookup.o
	$(CC) $(CFLAGS) lookup.o -o lookup

lookup.o : list.h map.h lookup.cpp
	$(CC) $(CFLAGS) -c lookup.cpp

clean:
	rm -f lookup *.o *~
