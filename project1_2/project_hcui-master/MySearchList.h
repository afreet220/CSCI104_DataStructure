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
#include "Set.h"

using namespace std;

class MySearchList: public QListWidget {
	Q_OBJECT
public:
	MySearchList(string* targetP);     //targetP points to main widget's internal memory
	void updateList(Set<string>& results);

private slots:
	void resultClicked(QListWidgetItem *item);     //select the page

private:

	string* currentPage;
	QListWidget* resultList;
};

#endif /* MYSEARCHLIST_H_ */
