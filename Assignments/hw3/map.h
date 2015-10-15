#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <deque>
#include <exception>
#include <stdexcept>
#include <cstddef>
#include "list.h"

using namespace std;

template <class keyType, class valueType>
struct Content
{
  keyType keyy;
  valueType target;
};

template <class keyType, class valueType>
class Map
{
  public:
    Map ();  // constructor for a new empty map

    ~Map (); // destructor

    int size () const; // returns the number of key-value pairs

    void add (const keyType & key, const valueType & value); 
      /* Adds a new association between the given key and the given value.
         If the key already has an association, it should throw an exception.
      */

    void remove (const keyType & key);
     /* Removes the association for the given key.
        If the key has no association, it should throw an exception. */

    valueType& get (const keyType & key) const;
     /* Returns the value associated with the given key.
        If the key has no association, it should throw an exception. */

  private:
    List<Content<keyType,valueType> > internalStorage;
     /* You should store all of your associations inside one list.
        It is part of your assignment to figure out what types you 
        should store in that list.
        (Hint: you may need to add an additional definition.) */

     /* If you like, you can add further data fields and private
        helper methods.
        In particular, a 'find' function could be useful, which
        will find the index in the list at which a given key sits. */
};

template <class keyType,class valueType>
Map<keyType,valueType>::Map()
{
}

template <class keyType,class valueType>
Map<keyType,valueType>::~Map()
{
}

template <class keyType,class valueType>
int Map<keyType,valueType>::size () const
{
  return internalStorage.size();
}

template <class keyType,class valueType>
void Map<keyType,valueType>:: add (const keyType & key, const valueType & value)
{
  Content<keyType,valueType> newT;
  keyType buf;
  for (int i=0;i<size();i++) {
    newT = internalStorage.get(i);
    buf = newT.keyy;
    if (buf == key) {
      throw runtime_error("There are duplicate emails in input");
    }
  }
  newT.keyy = key;
  newT.target = value;
  internalStorage.insert(size(),newT);
}

template <class keyType,class valueType>
void Map<keyType,valueType>::remove (const keyType & key)
{
  keyType buf;
  Content<keyType,valueType> tmp;
  int toDelete = -1;
  bool toThrow = true;
  for (int i=0;i<size();i++) {
    tmp = internalStorage.get(i);
    buf = tmp.keyy;
    if (buf == key) {
      toThrow = false;
      toDelete = i;
      break;
    }
  }
  if (toThrow) {
    throw runtime_error("Can't find the user with input Email");
  }
  internalStorage.remove(toDelete);
}

template <class keyType,class valueType>
valueType& Map<keyType,valueType>::get (const keyType & key) const
{
  keyType buf;
  Content<keyType,valueType> tmp;
  int toGet = -1;
  bool toThrow = true;
  for (int i=0;i<size();i++) {
    tmp = internalStorage.get(i);
    buf = tmp.keyy;
    if (buf == key) {
      toThrow = false;
      toGet = i;
      break;
    }
  }

  if (toThrow) {
    throw runtime_error("Can't find the user with input Email");
  }

  return internalStorage.get(toGet).target;
}

#endif











  
