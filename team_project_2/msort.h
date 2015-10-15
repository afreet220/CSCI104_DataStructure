
// Header of a function template of merge sort

#ifndef _M_SORT_H
#define _M_SORT_H

#include <vector>

using namespace std;

// Merge sort helper function. 'begin' is the index of the leftmost
// element of the sub-array to be sorted and 'end' is the index of the
// element that is one past the rightmost element of the sub-array to
// to be sorted. 
template <class T, class Comparator>
void msort_helper(vector<T>& myList, int begin, int end, Comparator comp)
{
  if ((begin + 1) == end)  // the sub-array has only one element
  {
    return;  // nothing to sort
  }
  else
  {
    int length = end - begin;        // length of the sub-array
    int mid = begin + (length / 2);  // mid-point of the sub-array

    // divide the sub-array into two halves and call the function
    // itself to sort each half separately
    msort_helper(myList, begin, mid, comp);  // sort the left half
    msort_helper(myList, mid, end, comp);    // sort the right half

    int left = begin;   // index of the current element of the left half
    int right = mid;    // index of the current element of the right half
    T tempList[length]; // temporary array to store the merged sorted array

    for (int i = 0; i < length; i++)
    {
      if ((left < mid) && 
	  (right == end || comp(myList[left], myList[right])))
      { 
        // If the left sub-array is not empty and the right sub-array is 
        // empty or the current left element is smaller than the current
        // right element, then copy the current left element to the ith 
        // element of the temporary array.
        tempList[i] = myList[left];   
	left++;      // forward the left index             
      }
      else
      { 
        // Otherwise, copy the current right element to the ith element
        // of the temporary array
        tempList[i] = myList[right];
	right++;     // forward the right index 
      }
    }

    // copy the merged sorted sun-array back to the original array
    for (int i = 0; i < length; i++)
    {
      myList[i + begin] = tempList[i];
    }
  }
  return;
}


template <class T, class Comparator>
void mergeSort(vector<T>& myList, Comparator comp)
{
  msort_helper<T, Comparator>(myList, 0, myList.size(), comp);
}

#endif
