/*
 * pageWindow.h
 *
 *  Created on: Mar 25, 2014
 *      Author: student
 */

#ifndef PAGEWINDOW_H_
#define PAGEWINDOW_H_

#include <iostream>
#include <fstream>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QListWidget>
#include <QRadioButton>
#include <QGroupBox>
#include <QListWidgetItem>
#include <QLabel>
#include <QTextBrowser>
#include "Webpage.h"
#include "List.h"
#include "Set.h"
#include "pageWindow.h"
#include "MySearchList.h"
#include <map>

using namespace std;

class MyPage: public QWidget {
	Q_OBJECT
public:
	MyPage(string initialPage, map<string, WebPage>* pgMap);
	QSize sizeHint() const {
		return QSize(750, 750);
	}
	~MyPage();
	void updateMainP(string mPage);

private slots:
	void outClicked();
	void inClicked();

private:
	map<string, WebPage>* webpMap;
	string* currentOut;
	string* currentIn;
	QTextBrowser* currentPage;
	MySearchList* outgoingL;
	MySearchList* incomingL;
	QPushButton* goButton;           //outgoing button
	QPushButton* inButton;           //incoming button

};

#endif /* PAGEWINDOW_H_ */
