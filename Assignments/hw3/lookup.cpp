#include "list.h"
#include "map.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <deque>
#include <iomanip>
#include <exception>
#include <stdexcept>

int main(int argc, char *argv[])
{
  if(argc<2){
    cout<<endl
        <<"provide a filename"<<endl;
    return 1;
  }

  ifstream input;
  input.open(argv[1]);
  if (input.fail()) {
    cout<<endl
        <<"Can't open target file plz start over"<<endl;
    return 1;
  }

  Map<string,string> myMap;

  while (!input.fail())
    {
      string line;  //temporay string to hold each line in the output
      string email;
      string name;
      stringstream pLine;
      char spaceOrTab = 'a';   //char variable to help determine the first white space

      getline(input,line,'\n');
      if (input.fail()) {
	break;
      }

      //1st read of current line
      pLine<<line;

      //this while loop determine the 1st whitespace is space or tab
      while (spaceOrTab != ' ' && spaceOrTab != '\t') {
	if (pLine.peek()==' ' || pLine.peek() == '\t') {
	  spaceOrTab = pLine.peek();
	}
	else {
	  pLine>>spaceOrTab;
	}
      }

      //clear the stringstream and read the current line again
      pLine.str("");
      pLine<<line;

      //space condition
      if (spaceOrTab == ' ') {
	getline(pLine,email,' ');
        //this while loop eats all the whitespace until name
	while (true) {
	  if (pLine.peek()==' '||pLine.peek()=='\t')
	    {
	      pLine.ignore(1);
	    }
	  else {
	    break;
	  }
	}
	getline(pLine,name);
      }

      //tab condition
      if (spaceOrTab == '\t') {
	getline(pLine,email,'\t');
        //this while loop eats all the whitespace until name
        while (true) {
	  if (pLine.peek()==' '||pLine.peek()=='\t')
	    {
	      pLine.ignore(1);
	    }
	  else {
	    break;
	  }
	}
	getline(pLine,name);
      }

      //construcing asscociation
      try {
      myMap.add(email,name);
      }
      catch(runtime_error& e) {
	cout<<e.what()<<endl;
	return 1;
      }
    }

  //the interface
  while (true) {
    string iKey;
    cout<<endl<<"Please enter the email address you want to look up"<<endl;
    getline(cin,iKey,'\n');
    //end condition
    if (iKey == ".") {
      break;
    }
    //finding target with associate key
    try {
    cout<<myMap.get(iKey)<<endl;
    }
    catch(runtime_error& e) {
      cout<<e.what()<<endl;
      continue;
    }
  }

  return 0;
}
