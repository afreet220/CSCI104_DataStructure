#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{

  int totalN;
  int* numWords;

  if(argc<2){
    cout<<endl
        <<"provide a filename"<<endl;
    return 1;
  }

  ifstream Input;
  Input.open(argv[1]);
  if (Input.fail()) {
    cout<<endl
        <<"Can't open target file plz start over"<<endl;
    return 1;
  }

  Input>>totalN;
  numWords = new int[totalN-1];

  Input.ignore(100,'\n');
  
  for (int i=0;i<totalN;i++)  {
    int count=0;
    string Line;
    getline(Input,Line,'\n');
    stringstream lineS;
    lineS << Line;
    while (true) {
      string buffer;
      lineS>>buffer;
      if (lineS.fail())  {
        break;
      }
      count++;
    }   
    numWords[i] = count;
  }

  for (int i=0;i<totalN;i++)  {
    cout<<numWords[totalN-1-i]<<endl;
  }

  return 0;
}
















