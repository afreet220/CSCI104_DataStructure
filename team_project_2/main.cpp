
// The main() function of the CS104 project.

#include <QApplication>
#include <iostream>
#include <fstream>
#include "MainWin.h"
#include "project.h"
#include "webpage.h"

using namespace std;
 
int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  if (argc < 4)
  {
    cout << "Usage: program_name page_list_file ad_list_file billing_file " 
         << endl;
    return 1;
  }

  if (!extractWebPageData(argv[1]))
  {
    cout << "Failed to extract data from web pages listed in "
         << argv[1] << endl;
    return 1;
  }

  if (!extractAdData(argv[2]))
  {
    cout << "Failed to extract advertiser information from"
         << argv[2] << endl;
    return 1;
  }

  map<string, string> acctMap; 
  map<string, map<string, int> > prefMap;
 
  loadAcctInfo(acctMap, prefMap);

  MainWin mainWindow(&acctMap, &prefMap);
 
  // mainWindoe.setCentralWidget();
  mainWindow.setGeometry(250, 150, 560, 380); 
  mainWindow.setWindowTitle("Web Page Query");
  mainWindow.show();

  return app.exec();
}

