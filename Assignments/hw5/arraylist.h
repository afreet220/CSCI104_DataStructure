#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <exception>
#include <cstddef>
#include <stdexcept>
#include "ilist.h"

using namespace std;

template <class T>

class ArrayList : public IList<T>
{
  public:
	ArrayList();
    virtual ~ArrayList ();
    int size () const;
    virtual void insert (int position, const T & val);
    void remove (int position);
    void set (int position, const T & val);
    T& get (int position);
    T const & get (int position) const;

  protected:
    virtual void resize();
    T* storage;
    int actualSize;
    int arraySize;
};

template <class T>
ArrayList<T>::ArrayList()
{
	arraySize = 10;
	storage = new T[arraySize];
	actualSize = 0;
}

template <class T>
ArrayList<T>::~ArrayList()
{
	delete [] storage;
}

template <class T>
int ArrayList<T>:: size() const
{
	return actualSize;
}

template <class T>
void ArrayList<T>::insert (int position, const T & val)
{
	if (position<0||position>actualSize) {
		throw runtime_error ("position not valid");
	}
	if (actualSize==0) {
		storage[0] = val;
		actualSize++;
	}
	else {
	  //T memoOne,memoTwo;
	  //memoOne = storage[position];
	  //storage[position] = val;
	  //actualSize++;
	  for (int i=actualSize;i>position;i--) {
	    storage[i] = storage[i-1];
	  }
	  storage[position] = val;
	  actualSize++;
	}
	if (actualSize == arraySize) {
      resize();
	}
}

template <class T>
void ArrayList<T>:: remove(int position)
{
	if (position<0||position>actualSize-1) {
		throw runtime_error ("remove position invalid");
	}
	if (position == actualSize - 1) {
		actualSize--;
	}
	else {
      //actualSize--;
	  for (int i=position;i<=actualSize-position-1;i++) {
		storage[i] = storage[i+1];
	  }
	  actualSize--;
	}
}

template <class T>
void ArrayList<T>:: set(int position,const T & val)
{
	if (position<0||position>actualSize-1) {
		throw runtime_error ("set value position invalid");
	}
	storage[position] = val;
}

template <class T>
T& ArrayList<T>:: get(int position)
{
	if (position<0||position>actualSize-1) {
		throw runtime_error ("get value position invalid");
	}
    return storage[position];
}

template <class T>
T const & ArrayList<T>:: get(int position) const
{
	if (position<0||position>actualSize-1) {
		throw runtime_error ("get value position invalid");
	}
	return storage[position];
}

template <class T>
void ArrayList<T>:: resize()
{
    int oldSize = actualSize;
	T* newArray = new T[oldSize*2];
	for (int i=0;i<oldSize;i++) {
		newArray[i] = storage[i];
	}
	delete [] storage;

	storage = newArray;

	newArray = NULL;
	arraySize = oldSize*2;
}

#endif /* ARRAYLIST_H_ */
