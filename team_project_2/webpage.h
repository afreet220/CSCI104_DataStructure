
// This header file defines the WebPage class.

#ifndef _WEB_PAGE_H
#define _WEB_PAGE_H

#include <iostream>
#include <string>
#include "Set.h"

using namespace std;

// WebPage class

class WebPage 
{
public:

  WebPage();                // default constructor 
  WebPage(string filename); // constructor that initializes the page 
                            // from the given file
  ~WebPage();               // destructor

  // assignment operator
  WebPage& operator= (const WebPage& other);  

  // equality operator '=='
  bool operator==(const WebPage& other);

  // operator we can use to display the contents of a web page 
  friend ostream& operator<< (ostream& os, const WebPage& page);

  // Parses the content of the filename that was passed to the 
  // constructor into the object.
  void parse();

  // Returns a set containing all individual words on the web page.
  Set<string> allWords() const; 

  // Returns true if the page contains the given word; 
  // returns false otherwise.
  bool contain(string word) const;

  // This method returns a list of pointers to all webpages that this 
  // page has links to. 
  Set<WebPage*> allOutgoingLinks() const {return _outgoingLinks;}
   
  // This method returns a list of pointers to all webpages that link 
  // to this page. 
  Set<WebPage*> allIncomingLinks() const {return _incomingLinks;}  
  
  // Adds a link from start to the current page in the current page's 
  // storage.  
  void addIncomingLink(WebPage* start);

  // Adds a link from the current page to the target in the current 
  // page's storage. 
  void addOutgoingLink (WebPage* target);
  
  // Returns the filename from which this page was read.
  string filename() const {return _fileName;};

  // Sets the ranking of the page
  void setRank(float rank)  {_rank = rank;}

  // get the ranking of the page
  float getRank(void) const {return _rank;}

private:

  string        _fileName;  // file name of the web page
  float         _rank;
  Set<string>   _wordSet;   // set of words contained in the web page
  Set<WebPage*> _incomingLinks;  // list of all pointers to webpages
                                      // that contain links to this page

  Set<WebPage*> _outgoingLinks;  // list of all pointers to webpages
                                      // that this page has links to
};

#endif
