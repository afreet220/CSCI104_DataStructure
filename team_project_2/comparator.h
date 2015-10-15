
// Header file of comparator definitions.

#ifndef _COMPARATOR_H
#define _COMPARATOR_H

#include <string>

using namespace std;

//struct for preference page
struct prefPage {
  string name;
  int score;
};

//preference socre functor for comparing preference page
struct prefComparator {
  bool operator()(const prefPage & lhs, const prefPage & rhs) 
  {
    return lhs.score > rhs.score;
  }
};

// integer comparator
struct IntComparator
{
  bool operator()(const int& fisrt, const int& second)
  {
    return (fisrt < second);
  }
};

// string aslphabetical comparator
struct StrAlphComparator
{
  bool operator()(const string& fisrt, const string& second)
  {
    return (fisrt < second);
  }
};

// string length comparator
struct StrLengthComparator
{
  bool operator()(const string& fisrt, const string& second)
  {
    return (fisrt.size() < second.size());
  }
};

// web page name comparator
struct PageNameComparator
{
  bool operator()(WebPage* page1, WebPage* page2)
  {
    return (page1->filename() < page2->filename());
  }
};

// web page ranking comparator
struct PageRankComparator
{
  bool operator()(WebPage* page1, WebPage* page2)
  {
    return (page1->getRank() > page2->getRank());
  }
};

// advertiser comparator
struct AdComparator
{
  bool operator()(AdBid* ad1, AdBid* ad2)
  {
    if (ad1->bid > ad2->bid)
    {
      return true;
    }
    else if (ad1->bid == ad2->bid)
    {
      if (ad1->compName < ad2->compName)
      {
        return true;
      }
    }
    return false;
  }
};

#endif
