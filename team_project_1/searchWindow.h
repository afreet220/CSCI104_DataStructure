/*
 * searchWindow.h
 *
 *  Created on: Mar 24, 2014
 *      Author: student
 */

#ifndef SEARCHWINDOW_H_
#define SEARCHWINDOW_H_

#include <iostream>
#include <fstream>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QListWidget>
#include <QRadioButton>
#include <QGroupBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QButtonGroup>
#include "Webpage.h"
#include "lib/List.h"
#include "lib/Set.h"
#include "pageWindow.h"
#include "MySearchList.h"
#include <map>

using namespace std;

class MySearch: public QWidget {
	Q_OBJECT
public:
	MySearch(Set<string> & wordSet, map<string, Set<string> > & wordToPage,
			map<string, WebPage> & wpMap);
	~MySearch();
	QSize sizeHint() const {
		return QSize(500, 400);
	}

private slots:
	void quitClicked();
	void searchClicked();
	void goClicked();    //go to page
	void orClicked();
	void andClicked();
	void alphaClicked();
	void rankClicked();

private:

	int andOr;      //memorry user choice, 0 for OR, 1 for AND, default or
	int sortO;      //memorry user choice, 0 for pageranking sort, 1 for alphabetically sort
	string* cPage;
	MyPage* subWindow;
	Set<string>* allTheWords;
	map<string, Set<string> >* pageWordMap;
	map<string, WebPage>* wpageMap;
	QLineEdit* searchText;
	QPushButton* quitButton;
	QPushButton* searchButton;
	QPushButton* gotoPageButton;
	QButtonGroup* searchOption;
	QButtonGroup* sortingOption;
	QRadioButton* andS;    //and radiobutton
	QRadioButton* orS;     //or radiobutton
	QRadioButton* alphO;    //alphabetically
	QRadioButton* rankO;     //decreasing pagerank values
	MySearchList* resultList;
};

#endif /* SEARCHWINDOW_H_ */
