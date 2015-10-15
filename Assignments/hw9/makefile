CC = g++
CFLAGS = -g -Wall
LDFLAGS =

.PHONY: all qsort_eva grade_asign heap_eva

all: rb_test team_forming

rb_test : rb_test.o
	$(CC) $(CFLAGS) rb_test.o -o rb_test

rb_test.o : rbbst.h bst.h rb_test.cpp
	$(CC) $(CFLAGS) -c rb_test.cpp	

team_forming : team_forming.cpp
	$(CC) $(CFLAGS) -std=c++11 team_forming.cpp -o team_forming 	
	
clean:
	rm -f rb_test team_forming *.o *~