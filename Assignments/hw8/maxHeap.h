#ifndef MAXHEAP_H_
#define MAXHEAP_H_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <exception>
#include <cstddef>
#include <stdexcept>
#include <deque>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

struct intLarge {
	bool operator()(int lhs, int rhs) {
		return lhs > rhs;
	}
};

template<class T, class Comparator>
class MaxHeap {
public:
	MaxHeap(int d, Comparator comp);

	~MaxHeap();

	void add(const T & item);

	const T & peek() const;

	void remove();

	bool isEmpty();

	//test
	T atPos(int pos);
	int sizeNow();
	void printHeap();

private:
	void trickleUp(int pos);
	void trickleDown(int pos);

	deque<T> storage;
	Comparator hComp;
	int deg;
	int dSize;
};

template<class T,class Comparator>
MaxHeap<T,Comparator>::MaxHeap(int d, Comparator comp) {
	deg = d;
	dSize = 0;
	hComp = comp;
}

template<class T,class Comparator>
MaxHeap<T,Comparator>::~MaxHeap() {

}

template<class T, class Comparator>
void MaxHeap<T, Comparator>::add(const T & item) {
     dSize++;
     storage.push_back(item);
     trickleUp(dSize-1);      //different from notes
}

template<class T,class Comparator>
const T & MaxHeap<T,Comparator>::peek() const {
	if (dSize > 0) {
	return storage[0];
	} else {
		throw runtime_error("the heap is empty");
	}
}

template<class T,class Comparator>
void MaxHeap<T,Comparator>::remove() {
      T reSwap = storage[0];
      storage[0] = storage[dSize-1];
      storage[dSize-1] = reSwap;
      dSize--;
      trickleDown(0);
}

template<class T,class Comparator>
bool MaxHeap<T,Comparator>::isEmpty() {
	return dSize == 0;
}

template<class T,class Comparator>
void MaxHeap<T,Comparator>::trickleUp(int pos) {
	int par = floor((pos - 1) / deg);
	if (pos > 0 && hComp(storage[pos],storage[par])) {      //functor >
		T toSwap = storage[pos];
		storage[pos] = storage[par];
		storage[par] = toSwap;
		trickleUp(par);
	}
}

template<class T,class Comparator>
void MaxHeap<T,Comparator>::trickleDown(int pos) {
    if (deg*pos+1 < dSize) {
    	int maxChild = pos*deg+1;
    	for (int i = pos*deg+2;i<=pos*deg+deg;i++) {
    		if (i >= dSize) {
    			break;
    		} else {
    			if (hComp(storage[i],storage[maxChild])) {
    				maxChild = i;
    			}
    		}
    	}
    	if (hComp(storage[maxChild],storage[pos])) {
    		T toSwap = storage[pos];
    		storage[pos] = storage[maxChild];
    		storage[maxChild] = toSwap;
    		trickleDown(maxChild);
    	}
    }
}

//test
template<class T,class Comparator>
T MaxHeap<T,Comparator>::atPos(int pos) {
	return storage[pos];
}

template<class T,class Comparator>
int MaxHeap<T,Comparator>::sizeNow() {
	return dSize;
}

template<class T,class Comparator>
void MaxHeap<T,Comparator>::printHeap() {
	cout<<endl;
	for (int i =0; i<dSize;i++) {
		cout<<storage[i]<<" ";
	}
	cout<<endl;
}

#endif
