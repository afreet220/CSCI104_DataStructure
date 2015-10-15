#ifndef STACK_H_
#define STACK_H_

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
class Stack : private ArrayList<T>

{
 public:
  // add appropriate constructors and destructors
  Stack();
  virtual ~Stack();

  bool isEmpty() const;
  /* returns whether the stack contains any elements */

  void push(const T& val);
  /* adds a value to the top of the stack */

  void pop();
  /* deletes the top value from the stack */

  T const & top() const;
  /* returns the top value on the stack */
};

template <class T>
Stack<T>::Stack()
{
}

template <class T>
Stack<T>::~Stack()
{
}

template <class T>
bool Stack<T>::isEmpty() const
{
	if (ArrayList<T>::size() == 0)
	{
		return true;
	}
	else {
		return false;
	}
}

template <class T>
void Stack<T>::push(const T& val)
{
	ArrayList<T>::insert(ArrayList<T>::size(),val);
}

template <class T>
void Stack<T>::pop()
{
	ArrayList<T>::remove(ArrayList<T>::size()-1);
}

template <class T>
T const & Stack<T>::top() const
{
    return ArrayList<T>::get(ArrayList<T>::size()-1);
}

#endif /* STACK_H_ */
