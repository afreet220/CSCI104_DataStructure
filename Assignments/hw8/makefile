CC = g++
CFLAGS = -g -Wall
LDFLAGS =

.PHONY: all qsort_eva grade_asign heap_eva

all: qsort_eva grade_asign heap_eva

qsort_eva : qsort_eva.o
	$(CC) $(CFLAGS) qsort_eva.o -o qsort_eva

qsort_eva.o : qsortEdge.h qsortRand.h qsort_eva.cpp
	$(CC) $(CFLAGS) -c qsort_eva.cpp

grade_asign : grade_asign.o
	$(CC) $(CFLAGS) grade_asign.o -o grade_asign
	
grade_asign.o : msort.h grade_asign.cpp
	$(CC) $(CFLAGS) -c grade_asign.cpp
	
heap_eva : heap_eva.o
	$(CC) $(CFLAGS) heap_eva.o -o heap_eva
	
heap_eva.o : heap_eva.cpp maxHeap.h
	$(CC) $(CFLAGS) -c heap_eva.cpp		
	
clean:
	rm -f qsort_eva grade_asign heap_eva *.o *~
