#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <exception>
#include <cstddef>
#include <iostream>
#include "ilist.h"
#include "linkedlist.h"
#include "arraylist.h"
#include "doublingarraylist.h"
#include "plusonearraylist.h"
#include "plustenarraylist.h"

using namespace std;

int main() {

	while (true) {
		cout << endl;
		cout
				<< "Please input an integer to select which list you want to test as following"
				<< endl;
		cout << "1 LinkedList" << endl;
		cout << "2 DoublingArrayList" << endl;
		cout << "3 PlusOneArrayList" << endl;
		cout << "4 PlusTenArrayList" << endl;
		cout << "5 ArrayList" << endl;
		cout << "Enter 0 to exit" << endl;

		int selection;
		cin >> selection;
		cout << endl;

		if (selection == 1) {
			cout << "testing LinkedList" << endl;
			LinkedList<int> testDL;

			cout << "trying insert at the beg" << endl;
			try {
				for (int i = 0; i < 19; i++) {
					testDL.insert(0, i);
				}
			} catch (runtime_error& e) {
				cerr << "I am 1" << endl;
			}

//print
			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			} catch (runtime_error& e) {
				cerr << "I am 2" << endl;
			}

			cout << "trying insert 150 at pos 4" << endl;
			try {
				testDL.insert(4, 150);
			} catch (runtime_error& e) {
			}

//print
			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			} catch (runtime_error& e) {
				cerr << "I am 2" << endl;
			}

			cout << "trying insert 500 at the end" << endl;
			try {
				testDL.insert(testDL.size(), 500);
			} catch (runtime_error& e) {
			}

//print
			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			} catch (runtime_error& e) {
				cerr << "I am 2" << endl;
			}

			cout << "trying remove at the beg" << endl;
			try {
				testDL.remove(0);
			} catch (runtime_error& e) {
				cerr << "I am 3" << endl;
			}

			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			} catch (runtime_error& e) {
				cerr << "I am 4" << endl;
			}

			cout << "trying remove from the end" << endl;
			try {
				testDL.remove(testDL.size() - 1);
			} catch (runtime_error& e) {
				cerr << "I am 5" << endl;
			}

			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			} catch (runtime_error& e) {
				cerr << "I am 6" << endl;
			}

			cout << "trying set the 3rd item to 50" << endl;
			try {
				testDL.set(2, 50);
			} catch (runtime_error& e) {
				cerr << "I am 7" << endl;
			}

			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			}

			catch (runtime_error& e) {
				cerr << "I am 8" << endl;
			}

			cout << "bulk test may take a while" << endl;

			for (int i = 0; i < 50000; i++)
				testDL.insert(0, i);
			for (int i = 0; i < 50000; i++)
				testDL.remove(testDL.size() - 1);

			cout << "bulk test done!" << endl;
			continue;
		}
		/************************************************************/
		else if (selection == 2) {
			cout << "testing DoublingArrayList" << endl;
			DoublingArrayList<int> testDL;

			cout << "trying insert at the beg" << endl;
			try {
				for (int i = 0; i < 19; i++) {
					testDL.insert(0, i);
				}
			} catch (runtime_error& e) {
				cerr << "I am 1" << endl;
			}

//print
			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			} catch (runtime_error& e) {
				cerr << "I am 2" << endl;
			}

			cout << "trying insert 150 at pos 4" << endl;
			try {
				testDL.insert(4, 150);
			} catch (runtime_error& e) {
			}

//print
			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			} catch (runtime_error& e) {
				cerr << "I am 2" << endl;
			}

			cout << "trying insert 500 at the end" << endl;
			try {
				testDL.insert(testDL.size(), 500);
			} catch (runtime_error& e) {
			}

//print
			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			} catch (runtime_error& e) {
				cerr << "I am 2" << endl;
			}

			cout << "trying remove at the beg" << endl;
			try {
				testDL.remove(0);
			} catch (runtime_error& e) {
				cerr << "I am 3" << endl;
			}

			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			} catch (runtime_error& e) {
				cerr << "I am 4" << endl;
			}

			cout << "trying remove from the end" << endl;
			try {
				testDL.remove(testDL.size() - 1);
			} catch (runtime_error& e) {
				cerr << "I am 5" << endl;
			}

			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			} catch (runtime_error& e) {
				cerr << "I am 6" << endl;
			}

			cout << "trying set the 3rd item to 50" << endl;
			try {
				testDL.set(2, 50);
			} catch (runtime_error& e) {
				cerr << "I am 7" << endl;
			}

			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			}

			catch (runtime_error& e) {
				cerr << "I am 8" << endl;
			}

			cout << "bulk test may take a while " << endl;

			for (int i = 0; i < 50000; i++)
				testDL.insert(0, i);
			for (int i = 0; i < 50000; i++)
				testDL.remove(testDL.size() - 1);

			cout << "bulk test done!" << endl;
			continue;
		}
		/*******************************************************/
		else if (selection == 3) {
			cout << "testing PlusOneArrayList" << endl;
			PlusOneArrayList<int> testDL;

			cout << "trying insert at the beg" << endl;
			try {
				for (int i = 0; i < 19; i++) {
					testDL.insert(0, i);
				}
			} catch (runtime_error& e) {
				cerr << "I am 1" << endl;
			}

//print
			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			} catch (runtime_error& e) {
				cerr << "I am 2" << endl;
			}

			cout << "trying insert 150 at pos 4" << endl;
			try {
				testDL.insert(4, 150);
			} catch (runtime_error& e) {
			}

//print
			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			} catch (runtime_error& e) {
				cerr << "I am 2" << endl;
			}

			cout << "trying insert 500 at the end" << endl;
			try {
				testDL.insert(testDL.size(), 500);
			} catch (runtime_error& e) {
			}

//print
			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			} catch (runtime_error& e) {
				cerr << "I am 2" << endl;
			}

			cout << "trying remove at the beg" << endl;
			try {
				testDL.remove(0);
			} catch (runtime_error& e) {
				cerr << "I am 3" << endl;
			}

			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			} catch (runtime_error& e) {
				cerr << "I am 4" << endl;
			}

			cout << "trying remove from the end" << endl;
			try {
				testDL.remove(testDL.size() - 1);
			} catch (runtime_error& e) {
				cerr << "I am 5" << endl;
			}

			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			} catch (runtime_error& e) {
				cerr << "I am 6" << endl;
			}

			cout << "trying set the 3rd item to 50" << endl;
			try {
				testDL.set(2, 50);
			} catch (runtime_error& e) {
				cerr << "I am 7" << endl;
			}

			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			}

			catch (runtime_error& e) {
				cerr << "I am 8" << endl;
			}

			cout << "bulk test may take a while" << endl;

			for (int i = 0; i < 50000; i++)
				testDL.insert(0, i);
			for (int i = 0; i < 50000; i++)
				testDL.remove(testDL.size() - 1);

			cout << "bulk test done!" << endl;
			continue;
		}
		/********************************************************/
		else if (selection == 4) {
			cout << "testing PlusTenArrayList" << endl;
			PlusTenArrayList<int> testDL;

			cout << "trying insert at the beg" << endl;
			try {
				for (int i = 0; i < 19; i++) {
					testDL.insert(0, i);
				}
			} catch (runtime_error& e) {
				cerr << "I am 1" << endl;
			}

//print
			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			} catch (runtime_error& e) {
				cerr << "I am 2" << endl;
			}

			cout << "trying insert 150 at pos 4" << endl;
			try {
				testDL.insert(4, 150);
			} catch (runtime_error& e) {
			}

//print
			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			} catch (runtime_error& e) {
				cerr << "I am 2" << endl;
			}

			cout << "trying insert 500 at the end" << endl;
			try {
				testDL.insert(testDL.size(), 500);
			} catch (runtime_error& e) {
			}

//print
			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			} catch (runtime_error& e) {
				cerr << "I am 2" << endl;
			}

			cout << "trying remove at the beg" << endl;
			try {
				testDL.remove(0);
			} catch (runtime_error& e) {
				cerr << "I am 3" << endl;
			}

			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			} catch (runtime_error& e) {
				cerr << "I am 4" << endl;
			}

			cout << "trying remove from the end" << endl;
			try {
				testDL.remove(testDL.size() - 1);
			} catch (runtime_error& e) {
				cerr << "I am 5" << endl;
			}

			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			} catch (runtime_error& e) {
				cerr << "I am 6" << endl;
			}

			cout << "trying set the 3rd item to 50" << endl;
			try {
				testDL.set(2, 50);
			} catch (runtime_error& e) {
				cerr << "I am 7" << endl;
			}

			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			}

			catch (runtime_error& e) {
				cerr << "I am 8" << endl;
			}

			cout << "bulk test may take a while " << endl;

			for (int i = 0; i < 50000; i++)
				testDL.insert(0, i);
			for (int i = 0; i < 50000; i++)
				testDL.remove(testDL.size() - 1);

			cout << "bulk test done!" << endl;
			continue;
		}
		/*************************************************************/
		else if (selection == 5) {
			cout << "testing ArrayList" << endl;
			ArrayList<int> testDL;

			cout << "trying insert at the beg" << endl;
			try {
				for (int i = 0; i < 19; i++) {
					testDL.insert(0, i);
				}
			} catch (runtime_error& e) {
				cerr << "I am 1" << endl;
			}

			//print
			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			} catch (runtime_error& e) {
				cerr << "I am 2" << endl;
			}

			cout << "trying insert 150 at pos 4" << endl;
			try {
				testDL.insert(4, 150);
			} catch (runtime_error& e) {
			}

			//print
			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			} catch (runtime_error& e) {
				cerr << "I am 2" << endl;
			}

			cout << "trying insert 500 at the end" << endl;
			try {
				testDL.insert(testDL.size(), 500);
			} catch (runtime_error& e) {
			}

			//print
			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			} catch (runtime_error& e) {
				cerr << "I am 2" << endl;
			}

			cout << "trying remove at the beg" << endl;
			try {
				testDL.remove(0);
			} catch (runtime_error& e) {
				cerr << "I am 3" << endl;
			}

			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			} catch (runtime_error& e) {
				cerr << "I am 4" << endl;
			}

			cout << "trying remove from the end" << endl;
			try {
				testDL.remove(testDL.size() - 1);
			} catch (runtime_error& e) {
				cerr << "I am 5" << endl;
			}

			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			} catch (runtime_error& e) {
				cerr << "I am 6" << endl;
			}

			cout << "trying set the 3rd item to 50" << endl;
			try {
				testDL.set(2, 50);
			} catch (runtime_error& e) {
				cerr << "I am 7" << endl;
			}

			try {
				for (int i = 0; i < testDL.size(); i++) {
					cout << testDL.get(i) << " ";
				}
				cout << endl;
			}

			catch (runtime_error& e) {
				cerr << "I am 8" << endl;
			}

			cout << "bulk test may take a while " << endl;

			for (int i = 0; i < 50000; i++)
				testDL.insert(0, i);
			for (int i = 0; i < 50000; i++)
				testDL.remove(testDL.size() - 1);

			cout << "bulk test done!" << endl;
			continue;
		} else if (selection == 0) {
			break;
		} else {
			cout << "please input integers from 0 to 4,sorry for the troubles"
					<< endl;
			continue;
		}
	}

	return 0;
}

