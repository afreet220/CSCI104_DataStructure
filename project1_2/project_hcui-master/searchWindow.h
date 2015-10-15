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
#include "List.h"
#include "Set.h"
#include "pageWindow.h"
#include "MySearchList.h"
#include <map>

using namespace std;

class MySearch: public QWidget {
	Q_OBJECT
public:
	MySearch(QWidget* Parent = NULL);
	~MySearch();
	QSize sizeHint() const {
		return QSize(500, 400);
	}
	void passIn(Set<string> & wordSet, map<string, Set<string> > & wordToPage,
			map<string, WebPage> & wpMap);

private slots:
	void quitClicked();
	void searchClicked();
	void goClicked();    //go to page
	void orClicked();
	void andClicked();

private:

	int andOr;      //memorry user choice, 0 for OR, 1 for AND, default or
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
	QRadioButton* andS;    //and radiobutton
	QRadioButton* orS;     //or radiobutton
	MySearchList* resultList;
};

#endif /* SEARCHWINDOW_H_ */
