/*
 * List.h
 *
 *  Created on: Mar 24, 2014
 *      Author: student
 */

#ifndef LIST_H_
#define LIST_H_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <exception>
#include <cstddef>
#include <stdexcept>
#include <deque>

using namespace std;

template<class T>
struct Item {
	T value;
	Item<T> *prev, *next;
};

template<class T>
class List {
public:
	List();   // constructor

	List(const List<T> & other);

	~List();  // destructor

	List<T> & operator=(const List<T>& rhs);

	int size() const;  // returns the number of elements in the list

	void insert(int position, const T & val);
	/* Inserts val into the list before the given position,
	 shifting all later items one position to the right.
	 Inserting before 0 makes it the new first element.
	 Inserting before size() makes it the new last element.
	 Your function should throw an exception if position is
	 outside the legal range. */

	void remove(int position);
	/* Removes the item from the given position, shifting all
	 later items one position to the left.
	 Your function should throw an exception if position is
	 outside the legal range. */

	void set(int position, const T & val);
	/* Overwrites the given position with the given value.
	 Does not affect any other positions.
	 Your function should throw an exception if position is
	 outside the legal range. */

	T& get(int position);
	/* Returns the item at the given position.
	 Your function should throw an exception if position is
	 outside the legal range. */

private:
	deque<T> storage;

	/* You may add further private data fields or helper methods if
	 you choose. You should not alter the public signature. */
};

template<class T>
List<T>::List() {
}

template<class T>
List<T>::List(const List<T> & other) {
	this->storage = other.storage;
}

template<class T>
List<T>::~List() {
}

template<class T>
List<T>& List<T>::operator=(const List<T>& rhs) {
	if (this == &rhs)
		return *this;
	this->storage = rhs.storage;
	return *this;
}

template<class T>
int List<T>::size() const {
	return storage.size();
}

template<class T>
void List<T>::insert(int position, const T & val) {
	if (position < 0 || position > size()) {
		throw runtime_error("position is not vaild");
	}

	typename deque<T>::iterator it = storage.begin();
	it = it + position;
	storage.insert(it, val);
}

template<class T>
void List<T>::remove(int position) {
	if (position < 0 || position > (size() - 1)) {
		throw runtime_error("position is not vaild");
	}
	typename deque<T>::iterator it = storage.begin();
	it = it + position;
	storage.erase(it);
}

template<class T>
void List<T>::set(int position, const T & val) {
	if (position < 0 || position > (size() - 1)) {
		throw runtime_error("position is not vaild");
	}
	storage.at(position) = val;
}

template<class T>
T& List<T>::get(int position) {
	if (position < 0 || position > (size() - 1)) {
		throw runtime_error("position is not vaild");
	}
	return storage.at(position);
}

#endif /* LIST_H_ */
