#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <exception>
#include <cstddef>
#include <stdexcept>
#include <cctype>
#include <stack>
#include "Webpage.h"
#include "lib/List.h"

//testing msort
struct AlphaStrComp {
	bool operator()(const string& lhs, const string& rhs) {
		return lhs < rhs;
	}
};

using namespace std;

int main(int argc, char *argv[]) {

	if (argc < 3) {
		cout << endl << "provide a seedname and outputfile name" << endl;
		return 1;
	}

	//declare stack
	stack<string> workFlow;

	//declare set to store result
	List<string> allPageName;

	ifstream seedFile;
	seedFile.open(argv[1]);
	if (seedFile.fail()) {
		cout << endl << "Can't open target file plz start over" << endl;
		return 1;
	}

	//DFS

	while (!seedFile.fail()) {     //outer loop fetching seed files
		string tName;
		getline(seedFile, tName, '\n');
		if (seedFile.fail()) {
			break;
		}
		workFlow.push(tName);

		while (!workFlow.empty()) {               //stack loop
			string sTop = workFlow.top();
			if (!allPageName.contains(sTop)) {        //only adds to file when it's taken
				int iPos = allPageName.size();        //from stack, a.k.a being explored
				allPageName.insert(iPos, sTop);
			}

			ifstream original;
			original.open(sTop.c_str());
			if (original.fail()) {
				throw runtime_error("can't open target page");
			}

			bool linkFound = false;    //flag to determine if stack.pop() is necessary

			while (!original.fail()) {     //parsing loop
				if (linkFound) {
					break;
				}
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
									if (!allPageName.contains(link)) {
										workFlow.push(link);     //if no seen before
										linkFound = true;        //push to stack,update flag to true
										break;                  //and break the parsing
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
			}                          //parsing loop ends here

			if (!linkFound) {
				workFlow.pop();     //only pop when all links haven been push
			}
		}                 //stack loop ends here
	}               //outer loop ends here

	ofstream toWrite(argv[2]);

	if (toWrite.is_open()) {
		for (int i = 0; i < allPageName.size(); i++) {
			toWrite << allPageName.get(i) << endl;
		}
		toWrite.close();
	} else {
		cout << "unable to open target output file" << endl;
	}

	return 0;
}

