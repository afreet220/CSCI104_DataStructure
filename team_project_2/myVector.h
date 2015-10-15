
// This header file defines the myVector class template.
// We define this class mainly because we want to have
// the contains() method, so that we can check whether
// a file name has alreay been inserted to the vector 
// and if yes, the file has been parsed.

#ifndef _MY_VECTOR_H
#define _MY_VECTOR_H

#include <vector>

using namespace std;

// myVector class template

template <class T>
class myVector : public std::vector<T>
{
public:

  // Checks whether this vector contains an element of the value
  // specified by the argument
  bool contains(T value);
};

// myValue::contains()
// This method returns true if THIS vector contains an element of
// the specified value; otherwise, it returns false
template <class T>
bool myVector<T>::contains(T value) 
{
  // for every item in 'this' set
  for (typename std::vector<T>::iterator itr = this->begin(); 
       itr != this->end(); itr++)
  {
    if (*itr == value)    // found a match
    {                        
      return true;   
    }
  }

  return false;   // no match was found       
}

#endif
