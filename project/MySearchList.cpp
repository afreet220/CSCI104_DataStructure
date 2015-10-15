/*
 * MySearchList.cpp
 *
 *  Created on: Mar 26, 2014
 *      Author: student
 */

#include <QListWidget>
#include <QListWidgetItem>
#include <QString>
#include <string>
#include "MySearchList.h"
#include "Set.h"

using namespace std;

MySearchList::MySearchList(string* targetP) {
	currentPage = targetP;
}

void MySearchList::updateList(Set<string>& results) {
	this->clear();

	Set<string>::iterator It;

	for (It = results.begin(); It != results.end(); It++) {
		QString pLabel = QString::fromStdString(*It);
		QListWidgetItem* toAdd;
		toAdd = new QListWidgetItem(pLabel);
		this->addItem(toAdd);
	}

	connect(this,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(resultClicked(QListWidgetItem*)));

}

void MySearchList::resultClicked(QListWidgetItem *item) {
	QString selectPage;
	selectPage = item->text();
	*currentPage = selectPage.toStdString();
}
