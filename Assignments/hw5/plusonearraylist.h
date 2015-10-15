#ifndef PLUSONEARRAYLIST_H_
#define PLUSONEARRAYLIST_H_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <exception>
#include <cstddef>
#include <stdexcept>
#include "ilist.h"
#include "arraylist.h"

using namespace std;

template <class T>

class PlusOneArrayList : public ArrayList<T>
{
  public:
	PlusOneArrayList();
	virtual ~PlusOneArrayList();
	void resize();
};

template <class T>
PlusOneArrayList<T>:: PlusOneArrayList ()
{

}

template <class T>
PlusOneArrayList<T>:: ~PlusOneArrayList()
{

}


template <class T>
void PlusOneArrayList<T>:: resize()
{
    int oldSize = ArrayList<T>::actualSize;
	T* newArray = new T[oldSize+1];
	for (int i=0;i<oldSize;i++) {
		newArray[i] = ArrayList<T>::storage[i];
	}
	delete [] ArrayList<T>::storage;

	ArrayList<T>::storage = newArray;

	ArrayList<T>::arraySize = oldSize+1;
}





#endif /* PLUSONEARRAYLIST_H_ */
