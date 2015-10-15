#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <exception>
#include <cstddef>
#include <stdexcept>
#include <cctype>
#include "searchWindow.h"
#include "Webpage.h"
#include "Set.h"
#include "List.h"
#include <map>
#include <QApplication>

using namespace std;

void printSetS(const Set<string> & toPrint);

int main(int argc, char *argv[]) {

	//start here
	if (argc < 2) {
		cout << endl << "provide a filename" << endl;
		return 1;
	}

	ifstream mainData;
	mainData.open(argv[1]);
	if (mainData.fail()) {
		cout << endl << "Can't open target file plz start over" << endl;
		return 1;
	}

	//create the list for webpages, also the map connects webpage names and List index
	map<string, WebPage> allPages;
	map<string, WebPage>::iterator mIt;

	while (!mainData.fail()) {
		string pName;
		getline(mainData, pName, '\n');
		if (mainData.fail()) {
			break;
		}
		WebPage temPage(pName);
		try {
			allPages.insert(pair<string, WebPage>(pName, temPage));
		} catch (exception& e) {
			cout << e.what() << endl;
		}
	}

	//produce incoming links for all webpages
	for (mIt = allPages.begin(); mIt != allPages.end(); mIt++) {
		Set<string>::iterator ssIt;
		Set<string> forAddLink = mIt->second.allOutgoingLinks();
		for (ssIt = forAddLink.begin(); ssIt != forAddLink.end(); ssIt++) {
			allPages[*ssIt].addIncomingLink(mIt->first);
		}
	}

	//  creating the set of all distinct words in webpages
	Set<string> everyWords;
	for (mIt = allPages.begin(); mIt != allPages.end(); mIt++) {
		everyWords = everyWords.setUnion(mIt->second.allWords());
	}

	//creating the map connects each word with its related pages
	map<string, Set<string> > wordPageMap;
	Set<string>::iterator wIt;
	for (wIt = everyWords.begin(); wIt != everyWords.end(); wIt++) {
		Set<string> setToInsert;
		for (mIt = allPages.begin(); mIt != allPages.end(); mIt++) {
			Set<string> setToEva = mIt->second.allWords();
			if (setToEva.find(*wIt) != setToEva.end()) {
				setToInsert.insert(mIt->second.filename());
			}
		}
		wordPageMap.insert(pair<string, Set<string> >(*wIt, setToInsert));
	}

	QApplication app(argc, argv);
	MySearch sWindow;
	sWindow.passIn(everyWords, wordPageMap, allPages);
	sWindow.show();
	return app.exec();
	return 0;
}

void printSetS(const Set<string> & toPrint) {
	Set<string>::iterator it;
	for (it = toPrint.begin(); it != toPrint.end(); it++) {
		cout << *it << endl;
	}
	cout << endl;
}
