#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cstddef>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <deque>
#include "maxHeap.h"

using namespace std;

struct hData {
	int degree;
	double intTime;
	double rmvTime;
};

void measureTime(int degr, deque<hData> & toStore);

int main(int argc, char *argv[]) {

	deque<hData> results;

	measureTime(2,results);
	measureTime(3,results);
	measureTime(4,results);
	measureTime(10,results);
	measureTime(20,results);
	measureTime(50,results);
	measureTime(100,results);

	cout<<endl;
	for (unsigned int i =0;i<results.size();i++) {
		cout<<"degree "<<results[i].degree<<endl;
		cout<<"insert "<<scientific<<results[i].intTime<<endl;
		cout<<"remove "<<scientific<<results[i].rmvTime<<endl;
	}

	return 0;
}

void measureTime(int degr, deque<hData> & toStore) {
	srand(time(NULL));
	clock_t start, finish;
	double dur = 0;
	hData tempData;
	tempData.degree = degr;
	intLarge lar;
	MaxHeap<int,intLarge> lHeap(degr,lar);

	for (int i=0;i<10;i++) {
		start = clock();
		for (int j=0;j<10000;j++) {
			lHeap.add(rand()%10000);
		}
		finish = clock();
		dur += (double)(finish - start);
		cout<<"in degree "<<degr<<"insert loop "<<i<<endl;
	}
	dur /= (CLOCKS_PER_SEC * 10);
	tempData.intTime = dur;

	dur = 0;

	for (int i=0;i<10;i++) {
		start = clock();
		for (int j=0;j<10000;j++) {
			lHeap.remove();
		}
		finish = clock();
		dur += (double)(finish - start);
		cout<<"in degree "<<degr<<"remove loop "<<i<<endl;
	}
	dur /= (CLOCKS_PER_SEC * 10);
	tempData.rmvTime = dur;

	toStore.push_front(tempData);
}

/*intLarge lar;

 MaxHeap<int,intLarge> tHeap(3,lar);

 tHeap.add(23);
 tHeap.add(16);
 tHeap.add(17);
 tHeap.add(34);
 tHeap.add(54);
 tHeap.add(66);
 tHeap.add(89);
 tHeap.add(23);
 tHeap.add(90);
 tHeap.add(75);
 tHeap.add(44);
 tHeap.add(99);
 tHeap.add(79);
 tHeap.add(28);

 cout<<"add done"<<endl;
 tHeap.printHeap();

 tHeap.remove();
 cout<<"1 st remove"<<endl;
 tHeap.printHeap();

 tHeap.remove();
 cout<<"2 nd remove"<<endl;
 tHeap.printHeap(); */
