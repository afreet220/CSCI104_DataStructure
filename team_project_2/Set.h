
// This header file defines the Set class template.

#ifndef _SET_TP_H
#define _SET_TP_H

#include <stdexcept>
#include <set>

using namespace std;

// Set class template

template <class T>
class Set : public std::set<T>
{
public:

  // returns the intersection of two sets
  Set<T> setIntersection(const Set<T>& other) const;
  // returns the union of two sets
  Set<T> setUnion(const Set<T>& other) const;
};


// Set::setIntersection()
//
// This method returns the set of items that are in both 'this' set
// and 'other' set.
template <class T>
Set<T> Set<T>::setIntersection(const Set<T>& other) const
{
  Set<T> newSet;    // an empty new set          

  // for every item in 'this' set
  for (typename std::set<T>::iterator itr = this->begin(); 
       itr != this->end(); itr++)
  {
    if (other.find(*itr) != other.end()) 
    {                         // if the item is also in 'other' set
      newSet.insert(*itr);    // insert the item to newSet     
    }
  }

  return newSet;   // newSet is the intersection of 'this' and 'other'          
}

// Set::setUnion()
//
// This method returns the set of items that are in either 'this' 
// set or 'other' set.
template <class T>
Set<T> Set<T>::setUnion(const Set<T>& other) const
{
  Set<T> newSet(other);   // copy 'other' set to the new set
 
  // for every item in 'this' set
  for (typename std::set<T>::iterator itr = this->begin(); 
       itr != this->end(); itr++)
  {
    if (other.find(*itr) == other.end()) 
    {                         // if the item is not in 'other' set
      newSet.insert(*itr);    // insert the item to newSet     
    }
  }

  return newSet;    // newSet is the union of 'this' and 'other'
}

#endif
