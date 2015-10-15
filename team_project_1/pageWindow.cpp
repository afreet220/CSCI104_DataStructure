/*
 * pageWindow.cpp
 *
 *  Created on: Mar 25, 2014
 *      Author: student
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <exception>
#include <cstddef>
#include <stdexcept>
#include <cctype>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTextBrowser>
#include <QString>
#include "searchWindow.h"
#include "MySearchList.h"
#include "lib/Set.h"
#include "lib/List.h"
#include "Webpage.h"
#include <map>

using namespace std;

MyPage::MyPage(string initialPage, map<string, WebPage>* pgMap) {
	webpMap = pgMap;
	currentOut = new string;
	currentIn = new string;

	currentPage = new QTextBrowser;
	outgoingL = new MySearchList(currentOut, pgMap);
	incomingL = new MySearchList(currentIn, pgMap);
	goButton = new QPushButton("&GoToThisOutGoingLink");
	inButton = new QPushButton("&GoToThisInComingLink");

	QHBoxLayout* mLayout = new QHBoxLayout;
	QVBoxLayout* rLayout = new QVBoxLayout;

	rLayout->addWidget(goButton);
	rLayout->addWidget(outgoingL);
	rLayout->addWidget(incomingL);
	rLayout->addWidget(inButton);

	mLayout->addWidget(currentPage);
	mLayout->addLayout(rLayout);

	setLayout(mLayout);

	updateMainP(initialPage);

	Set < string > showOut = pgMap->at(initialPage).allOutgoingLinks();
	Set < string > showIn = pgMap->at(initialPage).allIncomingLinks();

	outgoingL->updateList(showOut, 1);
	incomingL->updateList(showIn, 1);

	connect(goButton, SIGNAL(clicked()), this, SLOT(outClicked()));
	connect(inButton, SIGNAL(clicked()), this, SLOT(inClicked()));

}

MyPage::~MyPage() {
	delete currentOut;
	delete currentIn;
}

void MyPage::updateMainP(string mPage) {

	currentPage->clear();

	ifstream sourceF;
	cout << endl << "trying to open " << mPage << endl;  //debug
	sourceF.open(mPage.c_str());

	if (sourceF.fail()) {
		cout << endl << "can't open target page" << endl;
	} else {
		QString thePage;

		while (!sourceF.fail()) {
			string line;
			getline(sourceF, line, '\n');
			if (sourceF.fail()) {
				break;
			}

			//remove potential links from string of line
			size_t openB = line.find_first_of("[");

			//case for if the line has no links
			if (openB == string::npos) {
				line.append(1, '\n');
				QString Qline = QString::fromStdString(line);
				thePage.append(Qline);
			} else {

				//this while loop erase [] and link ()
				while (openB != string::npos) {
					line.erase(openB, 1);
					size_t closeB = line.find_first_of("]", openB);
					line.erase(closeB, 1);
					size_t openP = closeB;
					size_t closeP = line.find_first_of(")", openP);
					line.erase(openP, closeP - openP + 1);
					openB = line.find_first_of("[", openP);
				}

				line.append(1, '\n');
				QString Qline = QString::fromStdString(line);
				thePage.append(Qline);
			}

		}

		currentPage->setText(thePage);
	}
}

void MyPage::outClicked() {
	try {
		updateMainP (*currentOut);
		Set < string > showOut = webpMap->at(*currentOut).allOutgoingLinks();
		Set < string > showIn = webpMap->at(*currentOut).allIncomingLinks();

		outgoingL->updateList(showOut, 1);
		incomingL->updateList(showIn, 1);
	} catch (exception & e) {
	}
}

void MyPage::inClicked() {
	try {
		updateMainP (*currentIn);
		Set < string > showOut = webpMap->at(*currentIn).allOutgoingLinks();
		Set < string > showIn = webpMap->at(*currentIn).allIncomingLinks();

		outgoingL->updateList(showOut, 1);
		incomingL->updateList(showIn, 1);
	} catch (exception & e) {
	}
}

