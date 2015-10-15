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
#include "lib/Set.h"
#include "lib/List.h"
#include <map>

using namespace std;

MySearch::MySearch(Set<string> & wordSet,
		map<string, Set<string> > & wordToPage, map<string, WebPage> & wpMap) {

	subWindow = NULL;
	andOr = 0;
	rankO = 0;
	allTheWords = &wordSet;
	pageWordMap = &wordToPage;
	wpageMap = &wpMap;

	cPage = new string;
	quitButton = new QPushButton("&Quit");
	searchButton = new QPushButton("&Search");
	gotoPageButton = new QPushButton("&GoToPage");
	searchOption = new QButtonGroup;
	sortingOption = new QButtonGroup;
	andS = new QRadioButton("&AND Search");
	orS = new QRadioButton("&OR Search");
	alphO = new QRadioButton("&AlphaSort");
	rankO = new QRadioButton("&RankSort");
	searchText = new QLineEdit;
	resultList = new MySearchList(cPage, wpageMap);

	searchOption->addButton(orS);
	searchOption->addButton(andS);
	sortingOption->addButton(rankO);
	sortingOption->addButton(alphO);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	QHBoxLayout* searchLayout = new QHBoxLayout;
	QHBoxLayout* buttonLayout = new QHBoxLayout;
	QHBoxLayout* midbLayout = new QHBoxLayout;
	QHBoxLayout* bottomLayout = new QHBoxLayout;
	searchLayout->addWidget(searchText);
	searchLayout->addWidget(searchButton);
	buttonLayout->addWidget(orS);
	buttonLayout->addWidget(andS);
	midbLayout->addWidget(rankO);
	midbLayout->addWidget(alphO);
	bottomLayout->addWidget(gotoPageButton);
	bottomLayout->addWidget(quitButton);
	mainLayout->addLayout(searchLayout);
	mainLayout->addWidget(resultList);
	mainLayout->addLayout(buttonLayout);
	mainLayout->addLayout(midbLayout);
	mainLayout->addLayout(bottomLayout);

	connect(quitButton, SIGNAL(clicked()), this, SLOT(quitClicked()));
	connect(searchButton, SIGNAL(clicked()), this, SLOT(searchClicked()));
	connect(gotoPageButton, SIGNAL(clicked()), this, SLOT(goClicked()));
	connect(andS, SIGNAL(clicked()), this, SLOT(andClicked()));
	connect(orS, SIGNAL(clicked()), this, SLOT(orClicked()));
	connect(rankO, SIGNAL(clicked()), this, SLOT(rankClicked()));
	connect(alphO, SIGNAL(clicked()), this, SLOT(alphaClicked()));

	setLayout(mainLayout);

}

MySearch::~MySearch() {
	delete cPage;
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
		if (andOr == 0) {    //or case, only vaid input goes in
			if (allTheWords->find(tempName) != allTheWords->end()) {
				try {
					wordsInSearch.insert(tempName);
				} catch (runtime_error& e) {
					cout << e.what() << endl;
				}
			}
		} else {     //and case, all input goes in
			try {
				wordsInSearch.insert(tempName);
			} catch (runtime_error& e) {
				cout << e.what() << endl;
			}
		}
	}

	//produce the resultpages
	Set<string>::iterator sIt;
	try {            //this try block filter out invalid input if in AND case
		for (sIt = wordsInSearch.begin(); sIt != wordsInSearch.end(); sIt++) {
			if (andOr == 0) {
				resultPages = resultPages.setUnion(pageWordMap->at(*sIt));
			} else {
				//this if bracket handle the starting set of AND case
				if (resultPages.size() == 0) {
					resultPages = resultPages.setUnion(pageWordMap->at(*sIt));
				}
				resultPages = resultPages.setIntersection(
						pageWordMap->at(*sIt));
			}
		}
	} catch (exception& e) {
		cout << endl << "can't find input in database" << endl;
	}

	//extend results for hw7
	Set<string> extendedPages;
	extendedPages = resultPages;
	for (sIt = resultPages.begin(); sIt != resultPages.end(); sIt++) {
		extendedPages = extendedPages.setUnion(
				wpageMap->at(*sIt).allOutgoingLinks());
		extendedPages = extendedPages.setUnion(
				wpageMap->at(*sIt).allIncomingLinks());
	}

	resultList->updateList(extendedPages, sortO);

}

void MySearch::goClicked() {
	//handle the last page
	if (subWindow) {
		subWindow->close();
	}
	delete subWindow;
	try {
		subWindow = new MyPage(*cPage, wpageMap);
		subWindow->show();
	} catch (exception & e) {
		cout << endl << "can't produce subwindow" << endl;
	}
}

void MySearch::orClicked() {
	andOr = 0;
}

void MySearch::andClicked() {
	andOr = 1;
}

void MySearch::alphaClicked() {
	sortO = 1;
}

void MySearch::rankClicked() {
	sortO = 0;
}
