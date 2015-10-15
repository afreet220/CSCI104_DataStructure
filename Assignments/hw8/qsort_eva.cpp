#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <exception>
#include <cstddef>
#include <iostream>
#include <iomanip>
#include <deque>
#include <ctime>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "qsortRand.h"
#include "qsortEdge.h"

using namespace std;

//functor
struct intComp {
	bool operator()(int lhs, int rhs) {
		return ((lhs < rhs) || (lhs == rhs));
	}
};

//prototypes
void tMixed(deque<int> & toMix, int mixTimes);

void measureTime(const deque<int> & toTest, map<string, double> & toStore,
		int mixTimes);

int main() {
	deque<int> testList;
	map<string, double> results;

	for (int i = 0; i < 9999; i++) {
		testList.push_back(i);
	}

	cout << "at 75" << endl;

	measureTime(testList, results, 0);

	cout << "at 79" << endl;

	deque<int> mixedList = testList;

	cout << "at 83" << endl;

	tMixed(mixedList, 50);
	measureTime(mixedList, results, 50);
	mixedList = testList;

	cout << "at 85" << endl;

	tMixed(mixedList, 100);
	measureTime(mixedList, results, 100);
	mixedList = testList;

	cout << "at 91" << endl;

	tMixed(mixedList, 300);
	measureTime(mixedList, results, 300);
	mixedList = testList;

	cout << "at 97" << endl;

	tMixed(mixedList, 500);
	measureTime(mixedList, results, 500);
	mixedList = testList;

	cout << "at 103" << endl;

	tMixed(mixedList, 1000);
	measureTime(mixedList, results, 1000);
	mixedList = testList;

	cout << "at 109" << endl;

	tMixed(mixedList, 2000);
	measureTime(mixedList, results, 2000);
	mixedList = testList;

	cout << "at 115" << endl;

	tMixed(mixedList, 5000);
	measureTime(mixedList, results, 5000);
	mixedList = testList;

	cout << "at 121" << endl;

	tMixed(mixedList, 10000);
	measureTime(mixedList, results, 10000);
	mixedList = testList;

	cout << "at 126" << endl;

	tMixed(mixedList, 20000);
	measureTime(mixedList, results, 20000);
	mixedList = testList;

	cout << "at 133" << endl;

	map<string, double>::iterator mIt;

	cout << endl;

	for (mIt = results.begin(); mIt != results.end(); mIt++) {
		cout << mIt->first << " " << scientific << mIt->second << endl;
	}

	return 0;
}

void tMixed(deque<int> & toMix, int mixTimes) {
	for (int i = 0; i < mixTimes; i++) {
		srand(time(NULL));
		int first = rand() % (toMix.size());
		int second = rand() % (toMix.size());
		while (first == second) {
			second = rand() % (toMix.size());
		}
		int toSwap = toMix[first];
		toMix[first] = toMix[second];
		toMix[second] = toSwap;
	}
}

void measureTime(const deque<int> & toTest, map<string, double> & toStore,
		int mixTimes) {
	clock_t start, finish;
	double dur = 0;

	for (int i = 0; i < 10; i++) {
		deque<int> testing = toTest;
		intComp iComp;
		start = clock();
		QSortEdge(testing, iComp, 0, toTest.size() - 1);
		finish = clock();
		dur += (double) (finish - start);
		cout << "in " << mixTimes << "t edgeloop " << i << "done!" << endl;
	}

	dur /= (CLOCKS_PER_SEC * 10);
	stringstream toInsert;
	toInsert << "QEdge_" << mixTimes;
	toStore.insert(pair<string, double>(toInsert.str(), dur));

	dur = 0;

	for (int i = 0; i < 10; i++) {
		deque<int> testing = toTest;
		intComp iComp;
		start = clock();
		QSortRand(testing, iComp, 0, toTest.size() - 1);
		finish = clock();
		dur += (double) (finish - start);
		cout << "in " << mixTimes << "t randloop " << i << "done!" << endl;
	}

	dur /= (CLOCKS_PER_SEC * 10);
	toInsert.str("");
	toInsert << "QRand_" << mixTimes;
	toStore.insert(pair<string, double>(toInsert.str(), dur));
}

/*if (argc < 2) {
 cout << endl << "plz provide filename to write output" << endl;
 return 1;
 }

 deque<int> testOne;
 testOdne.push_back(14);
 testOne.push_back(24);
 testOne.push_back(51);
 testOne.push_back(67);
 testOne.push_back(88);
 testOne.push_back(31);
 testOne.push_back(47);
 testOne.push_back(96);
 testOne.push_back(75);

 deque<int> testTwo = testOne;

 intComp iComp;

 QSortEdge<int,intComp>(testOne,iComp,0,testOne.size()-1);
 QSortRand<int,intComp>(testTwo,iComp,0,testTwo.size()-1);

 cout<<endl;
 for (unsigned int i =0; i<testOne.size();i++) {
 cout<<testOne[i]<<" ";
 }
 cout<<endl;
 for (unsigned int i =0; i<testOne.size();i++) {
 cout<<testTwo[i]<<" ";
 }
 cout<<endl;  */
