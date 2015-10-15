#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

//prototype
void recursive(char* out,char* bank,int lTol,int counter,int dig);
void print(char* outP,int length);

int main(int argc, char *argv[])
{
  //reading letters from commandline, building letter bank
  string letters;
  int space;
  
  if(argc<3){
    cout<<endl
        <<"invaild input"<<endl;
    return 1;
  }

  letters = argv[1];
  space = atoi(argv[2]);

  stringstream characters;
  characters << letters;

  vector<char> initialFlow;
  
  while (true)  {
    char buffer;
    characters.get(buffer);
    if (characters.fail())  {
      break;
    }
    initialFlow.push_back(buffer);
  }

  int total;
  total = initialFlow.size();

  char letterBank[total-1];
  for (int i=0;i<total;i++) {
    letterBank[i] = initialFlow.back();  
    initialFlow.pop_back();
  } 
  //letterbank estabished

  //create the output array
  char output[space-1];

  //calling recursive function
  recursive(output,letterBank,total,0,space);
  
  return 0;
}

//"out" is the output array,"bank" is the letterbank,
//"lTol" is total number of letters in bank,"counter" is the updater,tells which
//digit the recursive calls at
//"dig" is the n from the command line
void recursive(char* out,char* bank,int lTol,int counter,int dig)
{
  //base case: if updater equal to the maximum digits of output,print
  if (counter == dig)  {
    print(out,dig);
    return;
  }
  //recursive case
  else  {
    for (int i=0;i<lTol;i++)  {      
      out[counter] = bank[i];
      counter++;  //update updater
      recursive(out,bank,lTol,counter,dig);
      counter--;  //restore updater
    }
  }
}

// "outP" is the output array, "length" is the array's length
void print(char* outP, int length)
{
  for (int i=0;i<length;i++)  {
    cout<<outP[i];
  }
  cout<<endl;
  return;
}
    
