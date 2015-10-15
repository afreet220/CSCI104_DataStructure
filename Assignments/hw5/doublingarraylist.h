#ifndef DOUBLINGARRAYLIST_H_
#define DOUBLINGARRAYLIST_H_

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

class DoublingArrayList : public ArrayList<T>
{
  public:
	DoublingArrayList();
	virtual ~DoublingArrayList();
	void resize();
};

template <class T>
DoublingArrayList<T>:: DoublingArrayList ()
{

}

template <class T>
DoublingArrayList<T>:: ~DoublingArrayList()
{

}


template <class T>
void DoublingArrayList<T>:: resize()
{
    int oldSize = ArrayList<T>::actualSize;
	T* newArray = new T[oldSize*2];
	for (int i=0;i<oldSize;i++) {
		newArray[i] = ArrayList<T>::storage[i];
	}
	delete [] ArrayList<T>::storage;

	ArrayList<T>::storage = newArray;

	newArray = NULL;
	ArrayList<T>::arraySize = oldSize*2;
}

#endif /* DOUBLINGARRAYLIST_H_ */
