// Implementation of the WebPage class.

#include <fstream>
#include <cctype>
#include <stdexcept>
#include <map>
#include "project.h"
#include "webpage.h"

using namespace std;

// default constructor
WebPage::WebPage()
{
  // constructs nothing
}

// constructor with a given file name
WebPage::WebPage(string filename)
{
  ifstream inFile(filename.c_str()); // check the existence of the file
  if (inFile.fail())
  {  
    string msg = "File " + _fileName + " could not be opened!";
    throw (msg);
  }
  inFile.close();

  _fileName = filename;    // set the file name for the WebPage object
}

// destructor
WebPage::~WebPage()
{  
  if (_wordSet.size())
  {
    _wordSet.clear();  // erase all elements of _wordSet of the object
  }
  if (_incomingLinks.size())
  {
    _incomingLinks.clear();
  }
  if (_outgoingLinks.size())
  {
    _outgoingLinks.clear();
  }
} 

// assignment operator
WebPage& WebPage::operator= (const WebPage& other)
{
  if (this == &other)  // object assigned to itself
  {
    return *this;      // return a reference to the object
  }

  _wordSet = other._wordSet;    // copy the word set to the invoking object
  _fileName = other._fileName;  // copy the file name to ithe nvoking object
  _incomingLinks = other._incomingLinks; // copy incoming links
  _outgoingLinks = other._outgoingLinks; // copy outgoing links

  return *this;  // return a reference to the invoking object
}

// equality operator '=='
bool WebPage::operator==(const WebPage& other)
{
  return (_fileName == other._fileName); // whether the file names of the invoking
}                                        // page and 'other' page are identical

// the << operator that passes the contents of the specified web page 
// to an output stream 
ostream& operator<< (ostream& os, const WebPage& page)
{
  ifstream inFile(page._fileName.c_str());
  if (inFile.fail())
  {
    throw runtime_error("Failed to open the web page!");
  }

  string line;
  while (std::getline(inFile, line))
  {
    string outString;
    for (unsigned int i = 0; i < line.size(); i++)
    {
      if (line[i] == '[')
      {
        int openBracket = i;
        int closeBracket;
        int openParenthesis;
        int closeParenthesis;
        if (parseLink(line, openBracket, closeBracket, openParenthesis, 
            closeParenthesis)) // if this is the begining of a link 
        {                      // anchor and the file name of the link
          for (int j = openBracket + 1; j < closeBracket; j++)
          {
            outString += line[j];
          }
          i = closeParenthesis;
	  continue;
        }
      }
    
      outString += line[i];
    }

    os << outString << endl;
  }
  
  inFile.close();
  
  return os;
}  

// extern std::map<string, WebPage*> pageMap;                        

// This method parses the contents of the file, line by line, of the 
// invoking WebPage. It will do:
// 1. Extracts links from this (the invoking) page and for each linked-to 
//    page, if no WebPage object has been created, one will be created. 
//    And the list of incoming links of the linked-to page will be updated
//    and the list of outgoing links of this page will also be updated.
// 2. Inserts words that this page contains to the wrod set of this page, 
//    including words in anchor text but excluding file names of linked
//    pages.  
void WebPage::parse()
{
  if (_wordSet.size()) // word set is not empty, the page has been parsed
  {
    return;
  }
 
  ifstream inFile(_fileName.c_str());
 
  if (inFile.fail())
  {
    throw runtime_error("Failed to open the web page!");
  }

  string line;
  while (std::getline(inFile, line))
  {
    string pureText; // we will strip '[', ']', and (fileName) from line and
                     // copy the stripped text to pureText; we then extract
                     // words from pureText and insert them to _wordSet
    for (unsigned int i = 0; i < line.size(); i++)
    {
      if (line[i] == '[')
      {
        int openBracket = i;
        int closeBracket;
        int openParenthesis;
        int closeParenthesis;
        if (parseLink(line, openBracket, closeBracket, openParenthesis, 
            closeParenthesis)) // if this is the begining of a pair of a
        {                      // link anchor and the file name of the link
          // get the file name
          string fileName;
          bool insideFileName = false;
  
          for (int j = openParenthesis + 1; j < closeParenthesis; j++)
          {
            if (!insideFileName)
            {
              if (!isspace(line[j]))
              {
                insideFileName = true;
                fileName += line[j];
              }
            }
            else
            {
              if (isspace(line[j]))
              {
                break;
              }
              fileName += line[j];
            }           
          }
          if (pageMap.find(fileName) == pageMap.end()) 
          {                // no <fileName, WebPage*> pair in pageMap yet
            WebPage* wp = new WebPage(fileName);  // create a WebPage object      
            pageMap[fileName] = wp;  // insert the <fileName, WebPage*> pair 
                                     // to pageMap      
          }
          pageMap[fileName]->addIncomingLink(this); // update the incoming links
                                                     // of the link_to page
          this->addOutgoingLink(pageMap[fileName]); // update the outgoing links
                                                     // of this page  
          for (int k = openBracket + 1; k < closeBracket; k++)
          {
            pureText += line[k];  // copy anchor text to pureText
          }
          i = closeParenthesis;  // move i to the position of closing parenthesis
	  continue;              
        }
      }
    
      pureText += line[i];
    }
    
    // extratc words from puretext and insert them the word set of this WebPage
    bool insideAWord = false;
    string word = "";    
    for (unsigned int i = 0; i < pureText.size(); i++)
    {
      char c = pureText[i];   // process a character from the text

      if (isalnum(c))              // if it's an alphanumeric character
      {
        if (!insideAWord)          // if it's not already insdie of a word
        {
          insideAWord = true;
        }
        if (c >= 'A' && c <= 'Z')  // if it's an upper case letter
        {
          c -= ('Z' - 'z');        // convert it to lower case
        }
        word += c;   // add the character to the word 
      }
      else        // the character is not an alphanumeric character
      {           
        if (insideAWord)  // if we are currently inside a word, then
        {                 // we have just moved out of the word
          _wordSet.insert(word);   // add the word to the word set
          insideAWord = false;       // no longer inside a word
          word = "";                 // reset to word to an empty word
        }
      }
    } // end of extracting words from pureText
  } // while loop; get next line from the file

  inFile.close();
}

// allWords()
// returns a set that contains all individual words on the web page; 
// all words are converted to all lowercase and all words in the set 
// are unique, i.e. no duplicate words in the set 
Set<string> WebPage::allWords() const
{
  return _wordSet;
}

// contain()
// returns true if the invoking page contains the given word; returns 
// false otherwise
bool WebPage::contain(string word) const
{
  // if the value returned by find() is not end() of _wordSet, then the
  // word set contains the word; otherwise, the word is not in the set
  return (_wordSet.find(word) != _wordSet.end());
}
  
// Adds a link from start to the current page in the current page's 
// storage.  
void WebPage::addIncomingLink(WebPage* start)
{
  _incomingLinks.insert(start); 
}

// Adds a link from the current page to the target in the current 
// page's storage. 
void WebPage::addOutgoingLink (WebPage* target)
{
  _outgoingLinks.insert(target);
}

