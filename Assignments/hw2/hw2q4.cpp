#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>

using namespace std;

struct Item {
  int val;
  Item* next;
};

//prototypes
void append(Item*& head, int v);
void print(Item* head);
bool isEven (int n);
bool isSquare (int n);
bool isPrime (int n);
void filter(Item* h1,Item*& h2,bool (*f)(int));

int main(int argc, char *argv[])
{
  //check command line  validity 
  if(argc<3){
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

  //declare two list, head1 is the input, head2 is gonna be the filtered one
  Item* head1 = NULL;
  Item* head2 = NULL;   

  //read in all the integers,creating input list
  while (true) {
    int temp;
    Input >> temp;
    if (!Input.fail()) {
      append(head1,temp);
    }
    else {
      break;
    }
  }

  /* cout<<endl<<"list1"<<endl;
     print(head1);*/ 

  //read in user's filter choice
  char choice = 'D';

  stringstream option;

  option << argv[2];

  option >> choice;

  //delcare function pointer
  bool (*fun)(int);
 
  // switch to user's choice
  switch (choice)
    {
    case 'A':
      fun = &isEven;
      filter(head1,head2,fun);
      break;

    case 'B':
      fun = &isSquare;
      filter(head1,head2,fun);
      break;

    case 'C':
      fun = &isPrime;
      filter(head1,head2,fun);
      break;

    default:
      break;
    }

  print(head2);
  
  return 0;
}


void append(Item*& head, int v)
{
  Item* newptr = new Item;
  newptr->val = v;
  newptr->next = NULL;

  if(head == NULL){
    head = newptr;
  }
  else {
    Item* temp = head;
    while (temp->next){
      temp = temp->next;
    }
    temp->next = newptr;
  }
}

void print(Item* head)
{
  Item* temp = head;
  cout<<endl;
  while(temp)  {
    cout<<temp->val<<endl;
    temp = temp->next;
  }
}

bool isEven (int n)
{
  return ((n%2)==0);
}

bool isSquare (int n)
{
  return (sqrt(n)==floor(sqrt(n)));
}

bool isPrime (int n)
{
  if (n > 1) {
    int count = 0;
    for (int i=2;i<n;i++)  {
      if (n%i == 0) {
	count++;
      }
    }
    if (count==0){
      return true;
    }
    else {
      return false;
    }
  }
  else {
    return false;
  }
}

void filter(Item* h1,Item*& h2,bool (*f)(int))
{
  //base case
  if (h1 == NULL) return;
  else {
    int buffer = h1->val;
    if ((*f)(buffer)) {
      append(h2,buffer);
    }
    //recursive call
    filter(h1->next,h2,f);
  }
}



