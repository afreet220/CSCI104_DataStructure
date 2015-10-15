/*
 * boolean_eva.cpp
 *
 *  Created on: Feb 26, 2014
 *      Author: Hao
 *
 *      Notice: Please read README.MD, THANK YOU!
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
//#include <array>
#include <exception>
#include <cstddef>
#include <iostream>
#include <iomanip>
#include "ilist.h"
#include "linkedlist.h"
#include "stack.h"

using namespace std;

//global constant for symbols
const int OPEN_PAR = -49;
const int CLOSE_PAR = -59;
const int AND = -89;
const int OR = -78;
const int NEG = -43;
const int INT_TRUE = -35;
const int INT_FALSE = -58;

//struct for variable and its true/false assignment
struct variable {
	int vName;
	int oneZero;
};

int main(int argc, char *argv[]) {
	if (argc < 3) {
		cout << endl << "plz provide filename" << endl;
		return 1;
	}

	//read in variable assignment
	ifstream varInput;
	varInput.open(argv[2]);
	if (varInput.fail()) {
		cout << endl << "Can't open variable assignment file plz start over"
				<< endl;
		return 1;
	}

	LinkedList<variable> varList;
	while (true) {
		variable vTemp;
		varInput >> vTemp.vName;
		if (varInput.fail()) {
			break;
		}
		char tfTemp;
		varInput >> tfTemp;
		if (tfTemp == 'T') {
			vTemp.oneZero = INT_TRUE;
		} else {
			vTemp.oneZero = INT_FALSE;
		}
		varList.insert(varList.size(), vTemp);
	}

	//declare the list to contain the result
	//1 for true, 2 for false, 3 for malform
	LinkedList<int> result;

	//read in formulas
	ifstream formulaInput;
	formulaInput.open(argv[1]);
	if (formulaInput.fail()) {
		cout << endl << "Can't open formula file plz start over" << endl;
		return 1;
	}

	//main loop
	while (!formulaInput.eof()) {

		//declaring things needed for loop
		string inputLine;
		stringstream streamLine;
		LinkedList<int> stackList;
		bool isMalform = false;
		int verdict = -1;

		//general input filtering
		//eat white spaces, translate variables to T/F value,translate symbols to int
		//put translated int into a list later for stack input
		getline(formulaInput, inputLine);
		streamLine << inputLine;

		while (!streamLine.fail()) {
			char peeking;
			peeking = streamLine.peek();
			if (peeking == ' ') {
				streamLine.ignore(1);
			} else if (peeking == '~') {
				stackList.insert(stackList.size(), NEG);
				streamLine.ignore(1);
			} else if (peeking == '(') {
				stackList.insert(stackList.size(), OPEN_PAR);
				streamLine.ignore(1);
			} else if (peeking == ')') {
				stackList.insert(stackList.size(), CLOSE_PAR);
				streamLine.ignore(1);
			} else if (peeking == '&') {
				stackList.insert(stackList.size(), AND);
				streamLine.ignore(1);
			} else if (peeking == '|') {
				stackList.insert(stackList.size(), OR);
				streamLine.ignore(1);
			} else {
				int addToList = -1;
				streamLine >> addToList;
				if (streamLine.fail()) {
					if (streamLine.eof()) {
						break;
					} else {
						isMalform = true;
						break;
					}
				} else {
					bool varNotLegal = true;
					for (int i = 0; i < varList.size(); i++) {
						if (addToList == varList.get(i).vName) {
							varNotLegal = false;
							stackList.insert(stackList.size(),
									varList.get(i).oneZero);
						}
					}
					if (varNotLegal) {
						isMalform = true;
					}
				}
			}
		}     //general filtering done, decoded input into list of ints

		//parsing using stack
		if (!isMalform) {
			Stack<int> iStack;
			while (stackList.size() != 0 && !isMalform) {

				//when hit close parenthesis, deal with the stack
				if (stackList.get(0) == CLOSE_PAR) {
					stackList.remove(0);

					//declaring logic symbol memory and
					//list storing integers pop from stack
					int andOr = -1;
					LinkedList<int> intInPar;

					//determine if the item before close parenthesis is variable
					try {
						intInPar.insert(intInPar.size(), iStack.top());
					} catch (runtime_error& e) {
						isMalform = true;
						break;
					}
					if (iStack.top() != INT_TRUE && iStack.top() != INT_FALSE) {
						isMalform = true;
						break;
					}
					iStack.pop();
					if (iStack.isEmpty()) {
						isMalform = true;
						break;
					}
					//loop to check if negative signs occur
					while (true) {
						if (iStack.top() == NEG) {
							if (intInPar.get(intInPar.size() - 1) == INT_TRUE) {
								intInPar.set(intInPar.size() - 1, INT_FALSE);
							} else {
								intInPar.set(intInPar.size() - 1, INT_TRUE);
							}
							iStack.pop();
							if (iStack.isEmpty()) {
								isMalform = true;
								break;
							}
						} else {
							break;
						}
					}

					//peek And or Or, memory it
					if (iStack.top() != AND && iStack.top() != OR) {
						isMalform = true;
						break;
					}
					andOr = iStack.top();

					//read in two items for each loop,until Open parenthesis hit
					while (!isMalform) {
						try {
							if (iStack.top() == OPEN_PAR) {
								iStack.pop();
								break;
							}
							if (iStack.top() != andOr) {
								isMalform = true;
								break;
							}
							iStack.pop();
							if (iStack.top() == INT_TRUE
									|| iStack.top() == INT_FALSE) {
								intInPar.insert(intInPar.size(), iStack.top());
								iStack.pop();
								//loop to check if negative signs occur
								while (true) {
									if (iStack.top() == NEG) {
										if (intInPar.get(intInPar.size() - 1)
												== INT_TRUE) {
											intInPar.set(intInPar.size() - 1,
													INT_FALSE);
										} else {
											intInPar.set(intInPar.size() - 1,
													INT_TRUE);
										}
										iStack.pop();
										if (iStack.isEmpty()) {
											isMalform = true;
											break;
										}
									} else {
										break;
									}
								}
							} else {
								isMalform = true;
								break;
							}
						} catch (runtime_error& e) {
							isMalform = true;
						}
					}

					//push T/F back into stack
					if (!isMalform) {
						if (andOr == AND) {
							bool andFlag = true;
							for (int i = 0; i < intInPar.size(); i++) {
								if (intInPar.get(i) == INT_FALSE) {
									iStack.push(INT_FALSE);
									andFlag = false;
									break;
								}
							}
							if (andFlag) {
								iStack.push(INT_TRUE);
							}
						} else {
							bool orFlag = true;
							for (int i = 0; i < intInPar.size(); i++) {
								if (intInPar.get(i) == INT_TRUE) {
									iStack.push(INT_TRUE);
									orFlag = false;
									break;
								}
							}
							if (orFlag) {
								iStack.push(INT_FALSE);
							}
						}
					}
				}

				//when close parenthesis not hit, push items to stack
				else {
					iStack.push(stackList.get(0));
					stackList.remove(0);
				}
			}

			//int List is empty now check if there are still
			//negative signs in the stack then store result
			if (!isMalform) {
				try {
					verdict = iStack.top();
					iStack.pop();
				} catch (runtime_error& e) {
					isMalform = true;
				}
				while (!iStack.isEmpty() && !isMalform) {
					if (iStack.top() == NEG) {
						if (verdict == INT_TRUE) {
							verdict = INT_FALSE;
						} else {
							verdict = INT_TRUE;
						}
						iStack.pop();
					} else {
						isMalform = true;
						break;
					}
				}
			}
		}    //done with stack

		//store line T/F value to the result List
		if (isMalform) {
			result.insert(result.size(), 3);
		} else if (verdict == INT_TRUE) {
			result.insert(result.size(), 1);
		} else if (verdict == INT_FALSE) {
			result.insert(result.size(), 2);
		} else {
			//default, means the code fails at this input,hopefully never execute
			result.insert(result.size(), 0);
		}
	}   //done with all lines in the input

	//print result
	cout << right <<endl;
	for (int i = 0; i < result.size(); i++) {
		cout<<"Line "<<setw(3)<<i+1;
		if (result.get(i) == 1) {
			cout <<"   "<< "T" << endl;
		} else if (result.get(i) == 2) {
			cout <<"   "<< "F" << endl;
		} else if (result.get(i) == 3) {
			cout <<"   "<< "Malformed" << endl;
		} else {
			cout <<"   "<< "if this print sth is wrong" << endl;
		}
	}

	return 0;
}
