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
#include <deque>
#include "Webpage.h"
#include "MySearchList.h"
#include "lib/Set.h"
#include "lib/msort.h"

using namespace std;

MySearchList::MySearchList(string* targetP, map<string, WebPage>* lookUp) {
	currentPage = targetP;
	linkLookUp = lookUp;
}

void MySearchList::updateList(Set<string>& results,int sortingOpt) {
	this->clear();
	rankList.clear();

	Set<string>::iterator It;
	Set<string>::iterator rIt;
	Set<string>::iterator lIt;

	if (sortingOpt == 0) {
		//pageRank handling strats here
		const double totalN = results.size();
		const double startingA = (1.0) / totalN;

		//first build the adjaceny list
		for (It = results.begin(); It != results.end(); It++) {
			rankPage temR;
			temR.rName = *It;
			temR.rankValue = startingA;
			temR.rvReceived = 0;
			Set<string> rankLinks = linkLookUp->at(*It).allOutgoingLinks();
			for (rIt = rankLinks.begin(); rIt != rankLinks.end(); rIt++) {
				for (lIt = results.begin(); lIt != results.end(); lIt++) {
					if (*lIt == *rIt) {
						temR.adjList.push_back(*lIt);
					}
				}
			}
			rankList.push_back(temR);
		}

		//iterative 30 times to get page rank stable

		for (int step = 0; step < 29; step++) {

			//calculate the out weight
			for (unsigned int i = 0; i < rankList.size(); i++) {
				if (rankList[i].adjList.size() == 0) {               //sink case
					double out = rankList[i].rankValue / totalN;
					for (unsigned int j = 0; j < rankList.size(); j++) {
						rankList[j].rvReceived += out;     //??
					}
				} else {                                          //general case
					//outgoing links weight
					double linkN = rankList[i].adjList.size();
					double linkOut = rankList[i].rankValue * (1.0 - restartP)
							/ linkN;
					for (unsigned int j = 0; j < rankList.size(); j++) {
						for (unsigned int k = 0; k < rankList[i].adjList.size();
								k++) {
							if (rankList[i].adjList[k] == rankList[j].rName) {
								rankList[j].rvReceived += linkOut;
							}
						}
					}

					//general distributed weight
					double genOut = rankList[i].rankValue * restartP / totalN;
					for (unsigned int j = 0; j < rankList.size(); j++) {
						rankList[j].rvReceived += genOut;
					}
				}
			}

			//sum up & clear the received value
			for (unsigned int i = 0; i < rankList.size(); i++) {
				rankList[i].rankValue = rankList[i].rvReceived;
				rankList[i].rvReceived = 0;
			}
		}

		//call mergesort
		rankComp rComp;
		mergeSort<rankPage, rankComp>(rankList, rComp, 0, rankList.size() - 1);

		cout << endl << "testing rank" << endl;   //testing rank
		//update output
		for (unsigned int i = 0; i < rankList.size(); i++) {
			QString pLabel = QString::fromStdString(rankList[i].rName);
			QListWidgetItem* toAdd;
			toAdd = new QListWidgetItem(pLabel);
			this->addItem(toAdd);
			//test output to examine with online data
			cout << "name" << rankList[i].rName << "  value   "
					<< rankList[i].rankValue << endl;
		}
	} else {
		//alphabetically sort
		for (It = results.begin(); It != results.end(); It++) {
			QString pLabel = QString::fromStdString(*It);
			QListWidgetItem* toAdd;
			toAdd = new QListWidgetItem(pLabel);
			this->addItem(toAdd);
		}
	}

connect(this,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(resultClicked(QListWidgetItem*)));

}

void MySearchList::resultClicked(QListWidgetItem *item) {
QString selectPage;
selectPage = item->text();
*currentPage = selectPage.toStdString();
}
