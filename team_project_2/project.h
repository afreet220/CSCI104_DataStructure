
// Header file for some of the helper functions for the CS104 
// project.

#ifndef _PROJECT_H
#define _PROJECT_H

#include <vector>
#include "Set.h"
#include "webpage.h"
#include "myVector.h"

struct AdBid
{
  float bid;
  string compName;
};

extern std::map<string, WebPage*>       pageMap; 
extern std::map<string, Set<WebPage*> > wordMap; 
extern map<string, std::vector<AdBid> > adMap;
//extern map<string, string>              acctMap;
//extern map<string, map<string, int> >   prefMap;

// Extracts data from web pages listed in the specifed file.
bool extractWebPageData(char* fileName);

// Extracts advertiser information from the specified file.
bool extractAdData(char* filename);

// This function parses a link of the [anchor text](file_name_of_link)
// format.
bool parseLink(const string& line, int& openBracket, int& closeBracket, 
               int& openParenthseis, int& closeParenthesis);

// Extracts words from a query command line
Set<string> getQueryWordSet(string line);

// Updates the global data structure wordMap that maps words
// to sets of pointers that point to web pages the contain the
// words.
void updateWordMap(Set<string>& wordSet);

// Gets the intersection of the page sets of query words.
Set<WebPage *> getIntersectionOfPages(Set<string>& wordSet);

// Get the union of the page sets of query words.
Set<WebPage *> getUnionOfPages(Set<string>& wordSet);

void expandPageList(myVector<WebPage*>& pageList);

void computeRanks(std::vector<WebPage*>& pageList);

std::vector<AdBid *> getAdList(Set<string>);

void loadAcctInfo(map<string, string>& acctMap,
                  map<string, map<string, int> >& prefMap);

#endif
