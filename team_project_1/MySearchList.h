/*
 * MySearchList.h
 *
 *  Created on: Mar 26, 2014
 *      Author: student
 */

#ifndef MYSEARCHLIST_H_
#define MYSEARCHLIST_H_

#include <QListWidget>
#include <QListWidgetItem>
#include <QString>
#include <string>
#include <deque>
#include "Webpage.h"
#include "lib/Set.h"

using namespace std;

const double restartP = 0.15;

//struct for pagerank
struct rankPage {
	string rName;
	double rankValue;
	double rvReceived;
	deque<string> adjList;
};

//page rank functor for comparing rankPage
struct rankComp {
	bool operator() (const rankPage & lhs, const rankPage & rhs) {
		return lhs.rankValue > rhs.rankValue;
	}
};

//alpha functor for comparing rankPage
//This one is not used in this HW since STL set default order does alpha ordering already
struct alphaComp {
	bool operator() (const rankPage & lhs,const rankPage & rhs) {
		return lhs.rName < rhs. rName;
	}
};


class MySearchList: public QListWidget {
	Q_OBJECT
public:
	MySearchList(string* targetP,map<string, WebPage>* lookUp);     //targetP points to main widget's internal memory
	void updateList(Set<string>& results,int sortingOpt);

private slots:
	void resultClicked(QListWidgetItem *item);     //select the page

private:

	deque<rankPage> rankList;        //hw7 rankList
	string* currentPage;
	map<string, WebPage>* linkLookUp;
	QListWidget* resultList;
};

#endif /* MYSEARCHLIST_H_ */
