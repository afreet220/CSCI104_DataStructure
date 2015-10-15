
// Implementation of helper functions for the CS104 project.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <map>
#include <vector>
#include <cmath>
#include "Set.h"
#include "myVector.h"
#include "webpage.h"
#include "project.h"
#include "comparator.h"
#include "msort.h"

using namespace std;

// file names to WebPage* mapping
map<string, WebPage*>            pageMap;  
// words to WebPage* mapping
map<string, Set<WebPage*> >      wordMap; 
// bid keys to bids and company names mapping
map<string, std::vector<AdBid> > adMap; 
// account names to pass words mapping                                       
// map<string, string>              acctMap;
// account names to preference mapping
// map<string, map<string, int> >   prefMap;

// This function extracts data web pages listed in the specifed file.
bool extractWebPageData(char* inFileName)
{
  ifstream inFile(inFileName);  
  if (inFile.fail())
  {
    cout << "Failed to open file " << inFileName << "!" << endl;
    return 0;
  }

  string fileName;

  // go throught the input data file and for each file listed in 
  // the data file create a WebPage object and then insert the
  // <fileName, pointer_to_WebPage_object> pair to pageMap
  while (std::getline(inFile, fileName))
  {
    // check to see whether there is already an entry in pageMap
    if (pageMap.find(fileName) == pageMap.end())   // no entry yet
    {                
      WebPage* wp = new WebPage(fileName);  // create a WebPage object and
                                            // initialize its name     
      pageMap[fileName] = wp;  // add an entry to the map with fileName as
                               // its key and set the pointer to its WebPage
                               // object as the data associated with the key
    }    
  }

  inFile.close();  // close the file

  // iterate through pageMap and parse every page; the parsing will
  // extract the information of outgoing links and incoming links,
  // it will also generatethe the word set for each page
  std::map<string, WebPage*>::iterator mItr;
  for (mItr = pageMap.begin(); mItr != pageMap.end(); mItr++)
  {
    ((*mItr).second)->parse();
  }

  return 1;
}

// This function extracts advertiser information from the pecifed file.
bool extractAdData(char* fileName)
{
  ifstream inFile(fileName);  
  if (inFile.fail())
  {
    cout << "Failed to open file " << fileName << "!" << endl;
    return 0;
  }

  int num;

  inFile >> num;

  for (int i = 0; i < num; i++)
  {
    string key;
    float  bid;

    inFile >> key >> bid;

    for (unsigned int i = 0; i < key.size(); i++)
    {
      char c = key[i];

      if (c >= 'A' && c <= 'Z')  // if it's an upper case letter
      {
        c -= ('Z' - 'z');        // convert it to lower case
	key[i] = c;
      }
    }
      
    string line;
    string company = "";
    getline(inFile, line);

    int size = (int) line.size();
    int start, end;

    for (start = 0; start < size; start++)
    {
      if (!isspace(line[start]))
      {
        break;
      }
    }

    for (end = size - 1; end >= 0; end--)
    {
      if (!isspace(line[end]))
      {
        break;
      }
    }

    for (int i = start; i <= end; i++)
    {
      company += line[i];
    }

    // cout << key << " " << bid << " #" << company << "#" << endl;

    AdBid ab;
    ab.bid = bid;
    ab.compName = company;

    adMap[key].push_back(ab);
  }

  inFile.close();



  return 1;
}

// This function parses a link of the [anchor text](file_name_of_link)
// format. Ii returns true if the link is in a valid format. It returns
// false if the link is not in a valid format. If the format of the
// link is valid, the function also passes back the positions of the
// open bracket, the close bracket, the open parenthesis, and the close
// parenthesis. 
bool parseLink(const string& line, int& openBracket, int& closeBracket, 
               int& openParenthesis, int& closeParenthesis)
{
  closeBracket = openBracket;
  openParenthesis = openBracket;
  closeParenthesis = openBracket;
 
  bool result = false;
  bool inBracket = true;
  bool inParenthesis = false;

  for (unsigned int i = openBracket + 1; i < line.size(); i++)
  {
    if (line[i] == '[')
    {
      if (inBracket)      // still inside the leading pair of brackets
      {
        break;  // not a valid link
      }
    }
    else if (line[i] == ']')  
    {
      if (inBracket)      // inside the leading pair of brackets
      {
        closeBracket = i; // found the close bracket
	inBracket = false;
      }
    }
    else if (line[i] == '(')  
    {
      if (!inBracket)       // outside the leading pair of brackets
      {
        if (inParenthesis)  // but inside the following pair of
        {                   // parentheses
          break;            // not allowed
        }
        else
        {
          openParenthesis = i; // found the open parenthesis
          inParenthesis = true;
        }
      }
    }
    else if (line[i] == ')')
    {
      if (inParenthesis)
      {
        closeParenthesis = i;    // found the close parenthesis
        inParenthesis = false; 
        result = true;
        break; 
      } 
    }
  }

  if (result)  // have found a pair of brackets and a pair of 
  {            // parentheses
    if ((openParenthesis - closeBracket) != 1)
    {
      result = false;   // there is at least one character between 
    }                   // the close bracket and the close parenthesis 
    else if ((closeBracket - openBracket) <= 1) // empty anchor text
    {
      result = false;
    }
    else if ((closeParenthesis - openParenthesis) <= 1) // empty link
    {
      result = false; 
    }

    if (result)
    {
      int i;
      for (i = openBracket + 1; i < closeBracket; i++)
      {
        if (!isspace(line[i]))
        {
          break;    // there is at least on non-space character
        }           // in the anchor test
      }
      if (i == closeBracket)  // all characters of the anchor text
      {                       // are space characters
        result = false; 
      }
    }

    if (result)
    {
      int i;

      for (i = openParenthesis + 1; i < closeParenthesis; i++)
      {
        if (!isspace(line[i]))
        {
          break;    // there is at least on non-space character in
        }           // the file name of the link      
      }
      if (i == closeParenthesis)  // all characters of the file name
      {                       // of the link are space characters
        result = false; 
      }
    }         
  }
    
  return result;
}


// Extract words from a query command line
Set<string> getQueryWordSet(string line)
{
  Set<string> wordSet;
  bool insideAWord = false;
  string word = "";

  for (unsigned int i = 0; i < line.size(); i++)
  {
    char c = line[i];

    if (isalnum(c))         // if it's an alphanumeric character
    {
      if (!insideAWord)     // if it's not already insdie of a word
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
      if (insideAWord)  // if we have been inside a word, then
      {                 // we have just moved out of the word

         wordSet.insert(word);   // add the word to the word set
      }
      insideAWord = false;       // no longer inside a word
      word = "";                 // reset to word to an empty word
    }
  } 
  
  if ((insideAWord) && word.size())
  {
    wordSet.insert(word);
  }

  return wordSet;
}  

// update the global data structure wordMap which maps a word to
// the set of pointers point to web pages the contain the word
void updateWordMap(Set<string>& wordSet)
{
  std::set<string>::iterator wordItr;
  for (wordItr = wordSet.begin(); wordItr != wordSet.end(); wordItr++) 
  {
    string word = *wordItr;

    if (wordMap.find(word) == wordMap.end())
    {
      Set<WebPage*> pageSet;

      std::map<string, WebPage*>::iterator mapItr;
      for (mapItr = pageMap.begin(); mapItr != pageMap.end(); mapItr++)
      {
        WebPage* pagePtr = (*mapItr).second;
        if (pagePtr->contain(word))
        {
          pageSet.insert(pagePtr);
        }
      }
      wordMap[word] = pageSet;
    }
  }
} 

// take the page set of each query word and get the intersection of
// all sets, the result is a set of pages that contains all of the 
// query ords

Set<WebPage *> getIntersectionOfPages(Set<string>& wordSet)
{
  Set<WebPage*> webPageSet;

  std::set<string>::iterator itr = wordSet.begin();
  if (itr != wordSet.end())
  {
    webPageSet = wordMap[*itr];
  
    for (itr++; itr != wordSet.end(); itr++)
    {
      webPageSet = wordMap[*itr].setIntersection(webPageSet);
    }
  }
   
  return webPageSet;   
}

// take the page set of each query word and get the union of all
// sets, the result is a set of pages that contains at least one
// one of the query words

Set<WebPage *> getUnionOfPages(Set<string>& wordSet)
{
  Set<WebPage*> webPageSet;

  std::set<string>::iterator itr;
  for (itr = wordSet.begin(); itr != wordSet.end(); itr++) 
  {
    webPageSet = wordMap[*itr].setUnion(webPageSet);
  }
   
  return webPageSet;  
}

void expandPageList(myVector<WebPage*>& pageList)
{
  myVector<WebPage*> temp = pageList;

  for (unsigned int i = 0; i < temp.size(); i++)
  {
    WebPage* page = temp[i];
    Set<WebPage*> links = page->allOutgoingLinks();
    Set<WebPage*>::iterator itr;
    
    // add pages that have a link to this page to the list
    for (itr = links.begin(); itr != links.end(); itr++)
    {
      if (!pageList.contains(*itr))  // if it is not already
      {                              // in the list
        pageList.push_back(*itr);
      }
    }
  
    links = page->allIncomingLinks();

    // add pages that this page has a link to to the list    
    for (itr = links.begin(); itr != links.end(); itr++)
    {
      if (!pageList.contains(*itr))  // if it is not already 
      {                              // in the list
        pageList.push_back(*itr);
      }
    } 
  }         
}

// given a list of web pages, compute the rank of each page on
// the list

void computeRanks(vector<WebPage*>& pageList)
{
  int n = pageList.size();
  std::map<WebPage*, int> indexMap; 

  for (int i = 0; i < n; i++)
  {
    indexMap[pageList[i]] = i;
  }

  float* M = new float[n * n];  // n x n matrix

  // assign (0.15/n) to every entry of M
  for (int i = 0; i < (n * n); i++)
  {
    M[i] = (0.15 / n);
  }

  // compute the values of entries of M using the Google
  // PageRank flormular
  for (int j = 0; j < n; j++)
  {
    WebPage* page = pageList[j];
    Set<WebPage*> outgoingLinks = page->allOutgoingLinks();
    int linkCount = outgoingLinks.size();

    if (!linkCount)  // no outgoing link
    {
      // add (0.85/n) to all entries in the jth column
      for (int row = 0; row < n; row++) 
      {
        M[(n * row) + j] += (0.85 / n);
      }
    }
    else
    {
      // add (0.85/linkCount) to all (index_of_linked_page, j) 
      // entries 
     
      for (Set<WebPage*>::iterator itr = outgoingLinks.begin();
           itr != outgoingLinks.end(); itr++)
      {
        // need to get the index of the linked page in pageList
        int index = indexMap[*itr]; 
        M[(index * n) + j] += (0.85 / linkCount); 
      }
    }
  }

  float* X = new float[n]; 

  // initial values in the X vector
  for (int i = 0; i < n; i++)
  {
    X[i] = 1.0 / n;
  } 

  // solve the (M * X = X) linear system using the interative 
  // method, iterate 30 times
  float* tempX = new float[n];
  // float* prevX = new float[n]; 
  for (int times = 0; times < 30; times++)
  {
    for (int i = 0; i < n; i++)
    {
      tempX[i] = 0.0; 
      for (int j = 0; j < n; j++)
      {
        tempX[i] += (M[(i * n) + j] * X[j]); 
      }
    }

    for (int i = 0; i < n; i++)
    {
      X[i] = tempX[i];
    }
  }

#if 0
  float total = 0.0;  
  cout << "X:    ";
  for (int i = 0; i < n; i++)
  {
    cout << " " << X[i];
    total += X[i];
  }
  cout << endl;
  cout << "Total = " << total << endl;
#endif

  // set page ranks 
  for (int i = 0; i < n; i++)
  {
    (pageList[i])->setRank(X[i]);
  }

  delete [] M;
  delete [] X;
  delete [] tempX;
}

std::vector<AdBid*> getAdList(Set<string> wordSet)
{
  std::vector<AdBid *> adList;

  std::set<string>::iterator wItr;
  for (wItr = wordSet.begin(); wItr != wordSet.end(); wItr++) 
  {
    // check to see if there are bids for the word
    if (adMap.find(*wItr) != adMap.end())  // yes
    {
      std::vector<AdBid>::iterator aItr;
      for (aItr = adMap[*wItr].begin(); aItr != adMap[*wItr].end(); 
           aItr++)
      {
        // check to see if the company already in adList
        int position = 0;
        for ( ; position < (int) adList.size(); position++)
        {
          if (adList[position]->compName == (*aItr).compName)
          {
            break;
          }
        }
     
        if (position != (int) adList.size()) // already in
        {                                   
          // check to see if the bid for this word is higher than the 
          // bid that is already in adList and if yes, replace it
          if (aItr->bid > adList[position]->bid)
          {
            adList[position]->bid = aItr->bid;
          } 
        }
        else  // not already in adList
        {
          AdBid* ab = new AdBid;
          ab->bid = aItr->bid;
          ab->compName = aItr->compName;

          adList.push_back(ab);
        }
      }
    }                
  }   

  if (adList.size() != 0)
  {
    AdComparator adComp;
    mergeSort<AdBid*>(adList, adComp);
  }

  return adList;
}

void loadAcctInfo(map<string, string>& acctMap,
                  map<string, map<string, int> >& prefMap)
{
  // loading user list
  ifstream acctData;
  acctData.open("personal/account_data.txt");

  if (!acctData.fail()) {
    while (true) {
      string dLine;
      getline(acctData, dLine, '\n');
      if (acctData.fail()) {
        break;
      }
      stringstream dlStream;
      dlStream << dLine;
      string tName;
      string tPass;
      getline(dlStream, tName, ' ');
      getline(dlStream, tPass, ' ');
      acctMap.insert(pair<string, string>(tName, tPass));
    }
  }

  //loading user preference
  map<string, string>::iterator actIt;
  for (actIt = acctMap.begin(); actIt != acctMap.end(); 
       actIt++) {
    ifstream acctPref;
    string forOpen = "personal/";
    forOpen.append(actIt->first);
    forOpen.append(".txt");
    acctPref.open(forOpen.c_str());

    map<string, int> pScoreMap;

    if (!acctPref.fail()) {
      while (true) {
        string dataLine;
        getline(acctPref, dataLine, '\n');
        if (acctPref.fail()) {
          break;
        }
        stringstream dlineStream;
        dlineStream << dataLine;
        string pageName;
        getline(dlineStream, pageName, ' ');

        int pgScore;

        dlineStream >> pgScore;
        pScoreMap.insert(pair<string, int>(pageName, pgScore));
      }
    } else {
      cout << endl << "There's a coruption with " << actIt->first
           << "'s preference data" << endl;
    }

    prefMap.insert(pair<string, map<string, int> >(actIt->first, pScoreMap));
  }
}



