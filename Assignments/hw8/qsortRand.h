#ifndef QSORTRAND_H_
#define QSORTRAND_H_

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

template<class T, class Comparator>
void QSortRand(deque<T>& toSort, Comparator func, int lt, int rt) {
	if (lt < rt) {

		srand(time(NULL));

		int m = lt;

		int rDom = rand() % (rt - lt) + lt;

		T piV = toSort[rDom];

		//swap the random pivot with the right end
		toSort[rDom] = toSort[rt];
		toSort[rt] = piV;

		for (int i = lt; i < rt; i++) {
			if (func(toSort[i], piV)) {
				T temp = toSort[i];
				toSort[i] = toSort[m];
				toSort[m] = temp;
				m++;
			}
		}

		toSort[rt] = toSort[m];
		toSort[m] = piV;

		QSortEdge(toSort, func, lt, m - 1);
		QSortEdge(toSort, func, m + 1, rt);

	}
}

#endif
