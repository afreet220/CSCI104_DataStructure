#ifndef QSORTEDGE_H_
#define QSORTEDGE_H_

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
void QSortEdge(deque<T>& toSort, Comparator func, int lt, int rt) {
	if (lt < rt) {

		int m = lt;

		T piV = toSort[rt];
		for (int i = lt; i < rt; i++) {
			if (func(toSort[i], piV)) {
				T temp = toSort[i];
				toSort[i] = toSort[m];
				toSort[m] = temp;
				m++;
			}
		}
		T tmp = toSort[rt];
		toSort[rt] = toSort[m];
		toSort[m] = tmp;

		QSortEdge(toSort, func, lt, m - 1);
		QSortEdge(toSort, func, m + 1, rt);

	}
}

#endif
