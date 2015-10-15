/*
 * searchWindow.cpp
 *
 *  Created on: Mar 24, 2014
 *      Author: student
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <exception>
#include <cstdlib>
#include <cctype>
#include <cstddef>
#include <stdexcept>
#include <cctype>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QString>
#include "MySearchList.h"
#include "searchWindow.h"
#include "Set.h"
#include "List.h"
#include <map>

using namespace std;

MySearch::MySearch(QWidget* parent) {
	subWindow = NULL;
	andOr = 0;

	cPage = new string;
	quitButton = new QPushButton("&Quit");
	searchButton = new QPushButton("&Search");
	gotoPageButton = new QPushButton("&GoToPage");
	searchOption = new QButtonGroup;
	andS = new QRadioButton("&AND Search");
	orS = new QRadioButton("&OR Search");
	searchText = new QLineEdit;
	resultList = new MySearchList(cPage);

	searchOption->addButton(orS);
	searchOption->addButton(andS);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	QHBoxLayout* searchLayout = new QHBoxLayout;
	QHBoxLayout* buttonLayout = new QHBoxLayout;
	searchLayout->addWidget(searchText);
	searchLayout->addWidget(searchButton);
	buttonLayout->addWidget(orS);
	buttonLayout->addWidget(andS);
	buttonLayout->addWidget(gotoPageButton);
	buttonLayout->addWidget(quitButton);
	mainLayout->addLayout(searchLayout);
	mainLayout->addWidget(resultList);
	mainLayout->addLayout(buttonLayout);

	connect(quitButton, SIGNAL(clicked()), this, SLOT(quitClicked()));
	connect(searchButton, SIGNAL(clicked()), this, SLOT(searchClicked()));
	connect(gotoPageButton, SIGNAL(clicked()), this, SLOT(goClicked()));
	connect(andS, SIGNAL(clicked()), this, SLOT(andClicked()));
	connect(orS, SIGNAL(clicked()), this, SLOT(orClicked()));

	setLayout(mainLayout);

}

MySearch::~MySearch() {
	delete cPage;
}

void MySearch::passIn(Set<string> & wordSet,
		map<string, Set<string> > & wordToPage, map<string, WebPage> & wpMap) {
	allTheWords = &wordSet;
	pageWordMap = &wordToPage;
	wpageMap = &wpMap;
}

void MySearch::quitClicked() {
	//handle the subWindow
	if (subWindow) {
		subWindow->close();
	}
	delete subWindow;
	close();
}

void MySearch::searchClicked() {

	//this->resultList->clear();
	string searchLine = searchText->text().toStdString();
	stringstream sLine;
	sLine << searchLine;

	Set<string> wordsInSearch;   //set store the words in search input
	Set<string> resultPages;     //set store the search results

	//parse the input
	while (true) {
		string tempName;
		sLine >> tempName;
		if (sLine.fail()) {
			break;
		}
		for (size_t i = 0; i < tempName.size(); i++) {
			char lower = tempName[i];
			tempName[i] = tolower(lower);
		}
		if (allTheWords->find(tempName) != allTheWords->end()) {
			try {
				wordsInSearch.insert(tempName);
			} catch (runtime_error& e) {
				cout << e.what() << endl;
			}
		}
	}

	//produce the resultpages
	Set<string>::iterator sIt;
	for (sIt = wordsInSearch.begin(); sIt != wordsInSearch.end(); sIt++) {
		if (andOr == 0) {
			resultPages = resultPages.setUnion(pageWordMap->at(*sIt));
		} else {
			//this if bracket handle the starting set of AND case
			if (resultPages.size() == 0) {
				resultPages = resultPages.setUnion(pageWordMap->at(*sIt));
			}
			resultPages = resultPages.setIntersection(pageWordMap->at(*sIt));
		}
	}

	resultList->updateList(resultPages);

}

void MySearch::goClicked() {
	//handle the last page
	if (subWindow) {
		subWindow->close();
	}
	delete subWindow;

	subWindow = new MyPage(*cPage, wpageMap);
	subWindow->show();
}

void MySearch::orClicked() {
	andOr = 0;
}

void MySearch::andClicked() {
	andOr = 1;
}

