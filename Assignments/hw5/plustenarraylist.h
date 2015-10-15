#ifndef PLUSTENARRAYLIST_H_
#define PLUSTENARRAYLIST_H_

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

class PlusTenArrayList : public ArrayList<T>
{
  public:
	PlusTenArrayList();
	virtual ~PlusTenArrayList();
	void resize();
};

template <class T>
PlusTenArrayList<T>:: PlusTenArrayList ()
{

}

template <class T>
PlusTenArrayList<T>:: ~PlusTenArrayList()
{

}


template <class T>
void PlusTenArrayList<T>:: resize()
{
    int oldSize = ArrayList<T>::arraySize;
	T* newArray = new T[oldSize+10];
	for (int i=0;i<oldSize;i++) {
		newArray[i] = ArrayList<T>::storage[i];
	}
	delete [] ArrayList<T>::storage;

	ArrayList<T>::storage = newArray;

	ArrayList<T>::arraySize = oldSize+10;
}



#endif /* PLUSTENARRAYLIST_H_ */
