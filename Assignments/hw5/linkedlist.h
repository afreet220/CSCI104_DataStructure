#ifndef LINKEDLIST_H
#define LINKEDLIST_H

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
struct Item
{
  T value;
  Item<T> *prev, *next;
};

template <class T>
class LinkedList : public IList<T>
{
  public:
    LinkedList ();   // constructor
    virtual ~LinkedList ();  // destructor
    int size () const;  // returns the number of elements in the list
    void insert (int position, const T & val);
    void remove (int position);
    void set (int position, const T & val);
    T& get (int position);
    T const & get(int position) const;

    private:
      Item<T> *head;
      Item<T> *tail;
      int count;


      /* You may add further private data fields or helper methods if
         you choose. You should not alter the public signature. */
};

template <class T>
LinkedList<T>::LinkedList()
{
  count = 0;
  head = NULL;
  tail = NULL;
}

template <class T>
LinkedList<T>::~LinkedList()
{
}

template <class T>
int LinkedList<T>::size() const
{
  return count;
}

template <class T>
void LinkedList<T>::insert (int position, const T & val)
{
  Item<T>* nItem = new Item<T>();
  nItem->value = val;
  nItem->prev = NULL;
  nItem->next = NULL;

  if (position <0 || position > size()) {
    throw runtime_error("position is not vaild");
  }

  if (count == 0) {
    head = tail = nItem;
    count++;
  }
  else if (position == 0) {
    nItem->next = head;
    head->prev = nItem;
    head = nItem;
    count++;
  }
  else if (position == size()) {
    tail->next = nItem;
    nItem->prev = tail;
    tail = nItem;
    count++;
  }
  else {
    Item<T>* tmp = head;
    for (int i=0;i<position;i++) {
      tmp = tmp->next;
    }
    nItem->next = tmp;
    nItem->prev = tmp->prev;
    tmp->prev->next = nItem;
    tmp->prev = nItem;
    tmp = NULL;
    delete tmp;
    count++;
  }
}

template <class T>
void LinkedList<T>::remove(int position)
{
  if (position <0 || position > (size()-1)) {
    throw  runtime_error("position is not vaild");
  }

  if (count == 1) {
    head = NULL;
    tail = NULL;
    count--;
  }
  else if (position == 0) {
    head = head->next;
    head->prev = NULL;
    count--;
  }
  else if (position == count-1) {
    tail = tail->prev;
    tail->next = NULL;
    count--;
  }
  else {
    Item<T>* tmp = head;
    for (int i=0;i<position;i++) {
      tmp = tmp->next;
    }
    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    delete tmp;
    count--;
  }
}

template <class T>
void LinkedList<T>::set(int position,const T & val)
{
  if (position <0 || position > (size()-1)) {
    throw  runtime_error("position is not vaild");
  }

  Item<T>* tmp = head;
  for (int i=0;i<position;i++) {
    tmp = tmp->next;
  }
  tmp->value = val;
  tmp = NULL;
  delete tmp;
}

template <class T>
T& LinkedList<T>::get(int position)
{
  if (position <0 || position > (size()-1)) {
    throw  runtime_error("position is not vaild");
  }

  Item<T>* tmp = head;
  for (int i=0;i<position;i++) {
    tmp = tmp->next;
  }
  return tmp->value;
}

template <class T>
T const & LinkedList<T>::get(int position) const
{
  if (position <0 || position > (size()-1)) {
    throw  runtime_error("position is not vaild");
  }

  Item<T>* tmp = head;
  for (int i=0;i<position;i++) {
    tmp = tmp->next;
  }
  return tmp->value;
}






#endif /* LINKEDLIST_H_ */
