#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <deque>
#include <exception>
#include <cstddef>
#include <stdexcept>

using namespace std;

template <class T>
struct Item
{
  T value;
  Item<T> *prev, *next;
};

template <class T>
class List
{
  public:
    List ();   // constructor

    ~List ();  // destructor

    int size () const;  // returns the number of elements in the list

    void insert (int position, const T & val);
      /* Inserts val into the list before the given position,
         shifting all later items one position to the right.
         Inserting before 0 makes it the new first element.
         Inserting before size() makes it the new last element.
         Your function should throw an exception if position is
         outside the legal range. */

    void remove (int position);
      /* Removes the item from the given position, shifting all
         later items one position to the left.
         Your function should throw an exception if position is
         outside the legal range. */

    void set (int position, const T & val);
      /* Overwrites the given position with the given value.
         Does not affect any other positions.  
         Your function should throw an exception if position is
         outside the legal range. */

    T& get (int position) const;
      /* Returns the item at the given position.
         Your function should throw an exception if position is
         outside the legal range. */

    private:
      Item<T> *head;
      Item<T> *tail;
      int count;


      /* You may add further private data fields or helper methods if 
         you choose. You should not alter the public signature. */
};

template <class T>
List<T>::List()
{
  count = 0;
  head = NULL;
  tail = NULL;
}

template <class T>
List<T>::~List()
{
}

template <class T>
int List<T>::size() const
{
  return count;
}

template <class T>
void List<T>::insert (int position, const T & val)
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
void List<T>::remove(int position)
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
void List<T>::set(int position,const T & val)
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
T& List<T>::get(int position) const
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

#endif








     




  
  

