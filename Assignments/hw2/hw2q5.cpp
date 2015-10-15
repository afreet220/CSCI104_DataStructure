#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <deque>

using namespace std;

//global constant 
const int CHAR_TO_INT = 65;
const int FourC = 4;

//prototype
bool recursive(int solRay[],deque<int>& nation,int** Relate,int cTotal);

int main(int argc, char *argv[])
{
  //check command line  validity 
  if(argc<2){
    cout<<endl
        <<"Invalid input"<<endl;
    return 1;
  }

  //check if input file can be opened
  ifstream Input;
  Input.open(argv[1]);
  if (Input.fail()) {
    cout<<endl
        <<"can't open target file plz start over"<<endl;
    return 1;
  }

  int Tcount;
  int Trow;
  int Tcol;

  Input>>Tcount>>Trow>>Tcol;

  //encoding map into integers represting countries
  int Map[Trow][Tcol];

  for (int i=0;i<Trow;i++) {
    for (int j=0;j<Tcol;j++) {
      char buffer;
      Input>>buffer;
      Map[i][j] = buffer - CHAR_TO_INT;
    }
  }

  //declare double pointer for relation chart
  int** Relation;

  //allocate memory for relation chart
  Relation = new int*[Tcount];

  for (int i=0;i<Tcount;i++) {
    Relation[i] = new int[Tcount];
  }
  
  //initialize the chart
  for (int i=0;i<Tcount;i++) {
    for (int j=0;j<Tcount;j++) {
      Relation[i][j]=0;
    }
  }

  //checking adjacent relationship,mapping it into relation chart
  //from observation, only checking left and up is sufficient
  for (int i=0;i<Trow;i++) {
    for (int j=0;j<Tcol;j++) {
      //checking west
      if (i!=0) {
	if (Map[i-1][j] != Map[i][j]) {
	  Relation[Map[i-1][j]][Map[i][j]]=1;
	  Relation[Map[i][j]][Map[i-1][j]]=1;
	}
      }
      //checking north
      if (j!=0) {
	if (Map[i][j-1] != Map[i][j]) {
	  Relation[Map[i][j-1]][Map[i][j]]=1;
	  Relation[Map[i][j]][Map[i][j-1]]=1;
	}
      }
    }
  }
  
  //declare array for solution
  int solution[Tcount];

  //initialization 
  for (int i=0;i<Tcount;i++) {
    solution[i]=-1;
  }

  //working streamline for countries
  deque<int> country;
  
  for (int i=0;i<Tcount;i++) {
    country.push_back(i);
  }

  //recursive call to find solution
  recursive(solution,country,Relation,Tcount);

  //printing solution
  cout<<endl;
  for (int i=0;i<Tcount;i++) {
    char printC = i+CHAR_TO_INT;
    cout<<printC<<" "<<solution[i]+1<<endl;
    }

  //deallocating memorry
  for (int i=0;i<Tcount;i++) {
    delete [] Relation[i];
  }
  delete [] Relation; 

  return 0;
}

//recursive function
//arguments are 1. solution array 2. countries for workflow
//3. relation chart 4. total # of countries
bool recursive(int solRay[],deque<int>& nation,int** Relate,int cTotal)
{
  //base case, when workflow is empty
  if (nation.size()==0) {
    return true;
  }
  else {
    bool success = false;      //logic definer
    int wkingCon;              //current working country

    //pick a country from workflow
    wkingCon = nation.back();
    nation.pop_back();

    //a temporary array for avaiable colors
    int* color;
    color = new int[FourC];
    for (int i=0;i<FourC;i++) {
      color[i]=0;
    }

    //marking used color from adjacent countries
    for (int i=0;i<cTotal;i++){
      if (Relate[wkingCon][i]==1) {
	if (solRay[i]!=-1) {
	  int buf;
	  buf = solRay[i];
	  color[buf]=1;
	}
      }
    }

    //filling color if can
    for (int i=0;i<FourC;i++) {
      if (color[i]==0) {
	solRay[wkingCon]=i;  //update solution array
        //recursive call**********************
	if(recursive(solRay,nation,Relate,cTotal)) {
        //************************************
        delete [] color;
        return true;
	}
	else {
	  solRay[wkingCon]=-1;  //backtracking
	}
      }
    }
    nation.push_back(wkingCon);   //backtracking
    delete [] color;
    return false;
  }
}

