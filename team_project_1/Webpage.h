/*
 * Webpage.h
 *
 *  Created on: Mar 24, 2014
 *      Author: student
 */

#ifndef WEBPAGE_H_
#define WEBPAGE_H_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <exception>
#include <cstddef>
#include <stdexcept>
#include "lib/Set.h"
#include "lib/List.h"

using namespace std;

class WebPage {
public:
	WebPage();
	WebPage(string filename);
	~WebPage();

	Set<string> allWords() const;

	friend ostream & operator<<(ostream & os, const WebPage & page);

	Set<string> allOutgoingLinks() const;

	Set<string> allIncomingLinks() const;

	string filename() const;

	bool operator<(const WebPage& rhs);    //comparator

	void addIncomingLink(string start);

private:

	string name;
	Set<string> inComing;
	Set<string> outGoing;
};

#endif /* WEBPAGE_H_ */
