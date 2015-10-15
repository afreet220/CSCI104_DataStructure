#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cstddef>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <deque>
#include <map>
#include "msort.h"

using namespace std;

//struct for student
struct Stu {
	string sName;
	int rGrade;
};

//functor
struct intComp {
	bool operator()(int lhs, int rhs) {
		return lhs < rhs;
	}
};

struct stuComp {
	bool operator()(const Stu & lhs,const Stu & rhs) {
		return lhs.rGrade < rhs.rGrade;
	}
};

int main(int argc, char *argv[]) {
	if (argc < 2) {
		cout << endl << "plz provide input" << endl;
		return 1;
	}

	ifstream mData;
	mData.open(argv[1]);
	if (mData.fail()) {
		cout << endl << "Can't open target file plz start over" << endl;
		return 1;
	}

	deque<int> aGradeList;
	deque<Stu> stuList;
	bool failFlag = false;

	mData.ignore(256,'\n');

	while (true) {
		string fLine;
		getline(mData, fLine, '\n');
		stringstream lStream;
		lStream << fLine;
		Stu tempS;
		getline(lStream, tempS.sName, ' ');

		//if reach the avaibable grade line
		if (isdigit(tempS.sName[0])) {
			stringstream numS;
			numS << tempS.sName;
			int toPush;
			numS >> toPush;
			aGradeList.push_back(toPush);
			break;
		} else {
			lStream >> tempS.rGrade;
			stuList.push_back(tempS);
		}
	}

	while (true) {
		int toPush;
		mData >> toPush;
		if (mData.fail()) {
			break;
		}
        aGradeList.push_back(toPush);
	}

	intComp iComp;
	mergeSort<int,intComp>(aGradeList,iComp,0,aGradeList.size()-1);

	deque<Stu> sortedStu = stuList;
	stuComp sComp;
	mergeSort<Stu,stuComp>(sortedStu,sComp,0,sortedStu.size()-1);

	map<string,int> lookUpMap;

	for (unsigned int i=0;i<sortedStu.size();i++) {
		if (aGradeList[i] < sortedStu[i].rGrade) {
			failFlag = true;
			break;
		} else {
		   /*	for (unsigned int j=0;j<stuList.size();j++) {
				if (sortedStu[i].rGrade == stuList[j].rGrade && stuList[j].aGrade != 0) {
					stuList[j].aGrade = aGradeList[i];
					break;
				}
			} */
			lookUpMap.insert(pair<string,int>(sortedStu[i].sName,aGradeList[i]));
		}
	}

	cout<<endl;

	if (failFlag) {
		cout<<"It's impossible to assign grade"<<endl;
	} else {
		for (unsigned int i=0;i<stuList.size();i++) {
			cout<<stuList[i].sName<<" "<<lookUpMap.at(stuList[i].sName)<<endl;
		}
	}

	cout<<endl;

	return 0;
}
