#ifndef MSORT_H_
#define MSORT_H_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <exception>
#include <cstddef>
#include <stdexcept>
#include <deque>
#include <stdio.h>
#include <math.h>

using namespace std;

template<class T, class Comparator>
void mergeSort(deque<T>& toSort, Comparator func,int lt, int rt) {
	if (lt<rt) {
		int m = floor((lt+rt)/2);
		mergeSort(toSort,func,lt,m);
		mergeSort(toSort,func,m+1,rt);

		//merge
		deque<T> temp(rt+1-lt);

		int i = lt, j = m+1, k = 0;
		while (i <= m || j<= rt) {
		  	if (i <= m && (j >rt || func(toSort[i],toSort[j]))) {
		  		temp[k] = toSort[i];
		  		i++;
		  		k++;
		  	}
		  	else {
		  		temp[k] = toSort[j];
		  		j++;
		  		k++;
		  	}
		}
		for (k = 0; k < rt+1-lt; k++) {
			toSort[k+lt] = temp[k];
		}
	}
}

#endif
