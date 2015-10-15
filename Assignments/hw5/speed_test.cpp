#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <exception>
#include <cstddef>
#include <iostream>
#include <ctime>
#include "ilist.h"
#include "linkedlist.h"
#include "arraylist.h"
#include "doublingarraylist.h"
#include "plusonearraylist.h"
#include "plustenarraylist.h"
//#include "map.h"

using namespace std;

double MeasureFrontInsertTime(IList<int> * list, int insertCount = 50000)
{
    double time = 0.0;
    // time measurement code goes here
    clock_t start,finish;

    start = clock();
    for(int i = 0; i < insertCount; ++i) list->insert(0, i);
    finish = clock();

    time = (double)(finish - start);
    time /= CLOCKS_PER_SEC;
    return time;
}

double MeasureBackInsertTime(IList<int> * list, int insertCount = 50000)
{
    double time = 0.0;
    // time measurement code goes here
    clock_t start,finish;

    start = clock();
    for(int i = 0; i < insertCount; ++i) list->insert(i, i);
    finish = clock();

    time = (double)(finish-start);
    time /= CLOCKS_PER_SEC;
    return time;
}

int main()
{
    double frontTime = 0.0, backTime = 0.0;
    IList<int> ** lists = new IList<int>*[8];

    // feel free to pass some argument to your constructor or just leave it to the default constructor
    lists[0] = new LinkedList<int>;          // front insert
    lists[1] = new LinkedList<int>;          // back  insert
    lists[2] = new PlusOneArrayList<int>;    // front insert
    lists[3] = new PlusOneArrayList<int>;    // back  insert
    lists[4] = new PlusTenArrayList<int>;    // front insert
    lists[5] = new PlusTenArrayList<int>;    // back  insert
    lists[6] = new DoublingArrayList<int>;   // front insert
    lists[7] = new DoublingArrayList<int>;   // back  insert

    for (int i = 0; i < 8; i += 2)
    {
        frontTime = MeasureFrontInsertTime(lists[i]);
        backTime  = MeasureBackInsertTime (lists[i + 1]);

        // cout the duration in seconds
        cout<<endl;
        cout<<"in test loop "<<i<<" "<<i+1<<endl;
        cout<<"front time "<<scientific<<frontTime<<endl;
        cout<<"back time "<<scientific<<backTime<<endl;

        // release: you can optionally measure delete (removing all items) duration
        delete lists[i];
        delete lists[i + 1];
    }
    delete [] lists;
    return 0;
}




