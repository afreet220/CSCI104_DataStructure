/*
 * Webpage.cpp
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
#include <cstddef>
#include <stdexcept>
#include <cctype>
#include "Webpage.h"
#include "Set.h"
#include "List.h"

using namespace std;

WebPage::WebPage() {
	name = "";
}

WebPage::WebPage(string filename) {
	name = filename;
	ifstream original;
	original.open(filename.c_str());
	if (original.fail()) {
		throw runtime_error("can't open target page");
	}

	//this while loop check the outgoing links
	while (!original.fail()) {
		string line;
		getline(original, line, '\n');
		if (original.fail()) {
			break;
		}
		stringstream sLine;
		sLine << line;
		while (!sLine.fail()) {
			char toPeek = sLine.peek();
			if (toPeek == '[') {
				string link;
				getline(sLine, link, ']');
				if (sLine.fail()) {
					break;
				} else {
					toPeek = sLine.peek();
					if (toPeek == '(') {
						sLine.ignore(1);
						getline(sLine, link, ')');
						if (sLine.fail()) {
							break;
						} else {
							try {
								outGoing.insert(link);
							} catch (runtime_error& e) {
							}
						}
					} else {
						break;
					}
				}
			} else {
				sLine.ignore(1);
			}
		}
	}
}

WebPage::~WebPage() {
}

void WebPage::addIncomingLink(string start) {
	try {
		inComing.insert(start);
	} catch (exception& e) {
	}
}

Set<string> WebPage::allWords() const {
	Set<string> wordSet;
	ifstream original;
	original.open(name.c_str());

	//declare a string that contains all the characters
	string characters =
			"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890";

	if (original.fail()) {
		throw runtime_error("can't open target page");
	}

	//main loop for producing set for all the words in data
	while (!original.fail()) {
		string line;
		getline(original, line, '\n');
		if (original.fail()) {
			break;
		}

		//remove potential links from string of line
		size_t openB = line.find_first_of("[");
		while (openB != string::npos) {
			line.erase(openB, 1);
			size_t closeB = line.find_first_of("]", openB);
			line.erase(closeB, 1);
			size_t openP = closeB;
			size_t closeP = line.find_first_of(")", openP);
			line.erase(openP, closeP - openP + 1);
			openB = line.find_first_of("[", openP);
		}

		//change all special characters to space
		size_t found = line.find_first_not_of(characters);
		while (found != string::npos) {
			line[found] = ' ';
			found = line.find_first_not_of(characters, found + 1);
		}

		//then read
		stringstream pLine;
		pLine << line;
		while (!pLine.fail()) {
			char isWhite = pLine.peek();
			if (isWhite == ' ') {
				pLine.ignore(1);
			} else {
				string word;
				pLine >> word;
				if (pLine.fail()) {
					break;
				}
				for (size_t i = 0; i < word.size(); i++) {
					char lower = word[i];
					word[i] = tolower(lower);
				}
				try {
					wordSet.insert(word);
				} catch (runtime_error& e) {
				}
			}
		}
	}
	return wordSet;
}

ostream & operator<<(ostream & os, const WebPage & page) {
	ifstream toPrint(page.name.c_str());
	os << toPrint.rdbuf();
	return os;
}

Set<string> WebPage::allOutgoingLinks() const {
	return outGoing;
}

Set<string> WebPage::allIncomingLinks() const {
	return inComing;
}

string WebPage::filename() const {
	return name;
}

bool WebPage::operator<(const WebPage& rhs) {
	return (this->name) < (rhs.name);
}

