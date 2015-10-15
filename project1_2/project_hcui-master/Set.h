/*
 * Set.h
 *
 *  Created on: Mar 24, 2014
 *      Author: student
 */

#ifndef SET_H_
#define SET_H_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <exception>
#include <cstddef>
#include <stdexcept>
#include <set>

using namespace std;

template<class T>
class Set: public set<T> {
public:

	Set<T> setIntersection(const Set<T> & other) const;
	/* Returns the intersection of the current set with other.
	 That is, returns the set of all items that are both in this
	 and in other. */

	Set<T> setUnion(const Set<T> & other) const;
	/* Returns the union of the current set with other.
	 That is, returns the set of all items that are in this set
	 or in other (or both).
	 The resulting set should not contain duplicates. */
};

template<class T>
Set<T> Set<T>::setIntersection(const Set<T>& other) const {
	Set<T> toReturn;
	typename Set<T>::iterator itA;
	for (itA = this->begin(); itA != this->end(); itA++) {
		typename Set<T>::iterator itB;
		for (itB = other.begin(); itB != other.end(); itB++) {
			if (*itA == *itB) {
				toReturn.insert(*itA);
			}
		}
	}
	return toReturn;
}

template<class T>
Set<T> Set<T>::setUnion(const Set<T>& other) const {
	Set<T> toReturn;
	if (this->size() == 0) {
		toReturn = other;
		return toReturn;
	}
	toReturn = *this;
	typename Set<T>::iterator itA;
	for (itA = this->begin(); itA != this->end(); itA++) {
		typename Set<T>::iterator itB;
		for (itB = other.begin(); itB != other.end(); itB++) {
			if (*itA != *itB) {
				toReturn.insert(*itB);
			}
		}
	}
	return toReturn;
}

#endif /* SET_H_ */
