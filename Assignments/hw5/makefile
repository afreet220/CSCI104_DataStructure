CC = g++
CFLAGS = -g -Wall
LDFLAGS =

.PHONY: all boolean_eva speed_test arraylist_test

all: boolean_eva speed_test arraylist_test

boolean_eva : boolean_eva.o
	$(CC) $(CFLAGS) boolean_eva.o -o boolean_eva

boolean_eva.o : ilist.h linkedlist.h stack.h boolean_eva.cpp
	$(CC) $(CFLAGS) -c boolean_eva.cpp

speed_test : speed_test.o
	$(CC) $(CFLAGS) speed_test.o -o speed_test
	
speed_test.o : ilist.h linkedlist.h arraylist.h doublingarraylist.h plusonearraylist.h plustenarraylist.h speed_test.cpp
	$(CC) $(CFLAGS) -c speed_test.cpp
	
arraylist_test : arraylist_test.o
	$(CC) $(CFLAGS) arraylist_test.o -o arraylist_test

arraylist_test.o : ilist.h linkedlist.h arraylist.h doublingarraylist.h plusonearraylist.h plustenarraylist.h arraylist_test.cpp
	$(CC) $(CFLAGS) -c arraylist_test.cpp
	
clean:
	rm -f arraylist_test speed_test boolean_eva *.o *~
