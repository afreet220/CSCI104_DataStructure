
// The implementation of the MainWin class.

#include <QApplication>
#include <QString>
#include <QStringList>
#include <QStringListModel>
#include <QVariant>
#include <iostream>
#include <fstream>
#include "webpage.h"
#include "MainWin.h"
#include "project.h"
#include "myVector.h"
#include "comparator.h"
#include "msort.h"

// golbal map defined in main.cpp
// extern std::map<string, WebPage*> pageMap;

MainWin::MainWin(map<string, string>* accountMap,
                 map<string, map<string, int> >* prefMap)
{
  mainLayout = new QVBoxLayout;

  // setup the grid layout and make it fill the window
  centerWidget  = new QWidget(this);
  centerWidget->setLayout(mainLayout);
  this->setCentralWidget(centerWidget);

  firstLayout = new QHBoxLayout;
  userLabel = new QLabel("Current User: None ");
  createAccButton = new QPushButton("Create Acc.");
  loginButton = new QPushButton("Log In");
  firstLayout->addStretch();
  firstLayout->addWidget(userLabel);
  firstLayout->addWidget(createAccButton);
  firstLayout->addWidget(loginButton);

  secondLayout = new QHBoxLayout; 

  queryLayout = new QVBoxLayout;
  promptLabel = new QLabel("Enter words of query:"); 
  queryEdit = new QLineEdit;
  selectionLayout = new QHBoxLayout;

  queryTypeLabel = new QLabel("Conjunc:");
  queryTypeCombo = new QComboBox();
  queryTypeCombo->addItem("AND");
  queryTypeCombo->addItem("OR");
  sortingTypeLabel = new QLabel("  Sort by:");
  sortingTypeCombo = new QComboBox();
  sortingTypeCombo->addItem("Rank");
  sortingTypeCombo->addItem("Alpha.");
  searchButton = new QPushButton("Go");
  selectionLayout->addWidget(queryTypeLabel);
  selectionLayout->addWidget(queryTypeCombo);
  selectionLayout->addWidget(sortingTypeLabel);
  selectionLayout->addWidget(sortingTypeCombo);
  selectionLayout->addStretch();
  selectionLayout->addWidget(searchButton); 

  pageListWidget = new QListWidget;

  exitLayout = new QHBoxLayout;
  exitButton = new QPushButton("Quit");
  exitLayout->addStretch();
  exitLayout->addWidget(exitButton);
  
  // queryLayout->addWidget(promptLabel);
  queryLayout->addWidget(promptLabel);
  queryLayout->addWidget(queryEdit);
  queryLayout->addLayout(selectionLayout);
  queryLayout->addWidget(pageListWidget);
  queryLayout->addLayout(exitLayout);

  adListWidget = new QListWidget;

  secondLayout->addLayout(queryLayout);
  secondLayout->addWidget(adListWidget);
  secondLayout->setStretch(0, 25);
  secondLayout->setStretch(1, 15);

  mainLayout->addLayout(firstLayout);
  mainLayout->addLayout(secondLayout);

  _currentPage = new string;
  _currentUser = new string;
  _queryType = AND;
  _sortingType = RANK;
  _loggedIn = false;
  acctMap = accountMap;
  prefLookup = prefMap;
  
  // pageWindow = new PageWidget(this);
  pageWindow = new PageWidget(_currentPage, &_loggedIn, _currentUser,
                              prefLookup);

  pageWindow->setGeometry(810, 150, 600, 480); 
  pageWindow->setWindowTitle("Page Viewer");

  adWindow = NULL;
  createWindow = NULL;
  loginWindow = NULL;

  // connect the query type combo box with query type setting method
  QObject::connect(queryTypeCombo, SIGNAL(currentIndexChanged(int)),
                   this, SLOT(setQueryType(int)));

  // connect the sorting type combo box with sorting type setting method
  QObject::connect(sortingTypeCombo, SIGNAL(currentIndexChanged(int)),
                   this, SLOT(setSortingType(int)));

  // connect the Go button with doSearch() method
  QObject::connect(searchButton, SIGNAL(clicked()),
                   this, SLOT(doSearch()));

  // qApp is a global pointer to THE application for quiting for
  // application 
  QObject::connect(exitButton, SIGNAL(clicked()),
                   this, SLOT(quit())); 

  // connect the signal sent by the pageList widget with the display
  // page window slot
  QObject::connect(pageListWidget, SIGNAL(itemClicked(QListWidgetItem *)),
                   this, SLOT(displayPageWindow(QListWidgetItem *)));

  // connect the signal sent by the adList widget with the display
  // ad window slot
  QObject::connect(adListWidget, SIGNAL(itemClicked(QListWidgetItem *)),
                   this, SLOT(displayAdWindow(QListWidgetItem *)));

  QObject::connect(createAccButton, SIGNAL(clicked()),
                   this, SLOT(createClicked()));

  QObject::connect(loginButton, SIGNAL(clicked()),
                   this, SLOT(loginClicked()));
}

MainWin::~MainWin()
{
  std::map<string, WebPage*>::iterator mItr;  
  for (mItr = pageMap.begin(); mItr != pageMap.end(); mItr++)
  {
    delete (*mItr).second;
  } 

  // destroy the existing adList
  if (adList.size())
  {
    for (int i = 0; i < (int) adList.size(); i++)
    {
      delete adList[i];
    }
    adList.clear();
  }

  delete _currentPage;
  delete _currentUser;
} 

void MainWin::setQueryType(int i)
{
  if (i == 0)
  {
    _queryType = AND;
  }
  else if (i == 1)
  {
    _queryType = OR;
  } 
}

void MainWin::setSortingType(int i)
{
  if (i == 0)
  {
    _sortingType = RANK;
  }
  else if (i == 1)
  {
    _sortingType = ALPH;  
  }
}



void MainWin::doSearch()
{
  if (pageWindow)
  {
    pageWindow->close();
    delete pageWindow;
    pageWindow = NULL;
  }
  if (adWindow)
  {
    adWindow->close();
    delete adWindow;
    adWindow = NULL;
  }

  QString input = queryEdit->text();
  Set<string> wordSet = getQueryWordSet(input.toStdString());

  if (wordSet.size() == 0)  // if the query word list is empty
  {
    adListWidget->clear();
    pageListWidget->clear();
    return;
  }

  adListWidget->clear();

  // destroy the existing adList
  if (adList.size())
  {
    for (int i = 0; i < (int) adList.size(); i++)
    {
      delete adList[i];
    }
    adList.clear();
  }
    
  // get a new advertiser list
  adList = getAdList(wordSet);
  
  if (adList.size())  // if the advertiser list is not empty
  {
#if 0    // for testing only
    for (unsigned int i = 0; i < adList.size(); i++)
    {
      if (i == 0)
        cout << endl;
      cout << adList[i]->compName << " " << adList[i]->bid << endl;
    } 
#endif    // testing

    QStringList adListString;
    for (unsigned int i = 0; i <adList.size(); i++)
    {
      adListString << (adList[i]->compName).c_str();
    }

    adListWidget->addItems(adListString); 
  }

  updateWordMap(wordSet);

  Set<WebPage *> pageSet;
  if (_queryType == AND)
  {
    pageSet = getIntersectionOfPages(wordSet);    
  }
  else if (_queryType == OR)
  {
    pageSet = getUnionOfPages(wordSet);
  }

  if (!pageSet.size())
  {
    pageListWidget->clear(); 
    return;
  }
    
  myVector<WebPage*> pageArray;

  Set<WebPage *>::iterator itr = pageSet.begin();
  for (; itr != pageSet.end(); itr++)
  {
    pageArray.push_back(*itr);
  }
   
  expandPageList(pageArray);

  std::vector<prefPage> prefList; 
  std::vector<WebPage*> temp;

  if (_sortingType == ALPH)
  {
    PageNameComparator comp;
    mergeSort<WebPage*>(pageArray, comp); 
  }
  else if (_sortingType == RANK)
  {
    if (_loggedIn)  //personal preference overwrite starts here
    {
      // construct preference page list
      std::vector<WebPage*>::iterator itr;
      for (itr = pageArray.begin(); itr != pageArray.end(); itr++)
      {
        if (prefLookup->find(*_currentUser)->second.find((*itr)->filename())
	    != prefLookup->find(*_currentUser)->second.end()) 
        {
	  prefPage pfToAdd;
	  pfToAdd.name = (*itr)->filename();
	  pfToAdd.score = 
            prefLookup->find(*_currentUser)->second.find((*itr)->filename())->second;
	  prefList.push_back(pfToAdd);
        }
      }

      //remove preference page from normal rank page list
      for (unsigned int i = 0; i < pageArray.size(); i++)
      {
         unsigned int j = 0;
         for (; j < prefList.size(); j++)
         {
           if (prefList[j].name == (pageArray[i])->filename())
             break;
         }

         if (j == prefList.size())
         {
           temp.push_back(pageArray[i]);
         }                             
      }

      if (prefList.size())
      {
        prefComparator pComp;
        mergeSort<prefPage>(prefList, pComp);
      }
    }   
 
    if (temp.size())
    {
      pageArray.clear();
      for (unsigned int i = 0; i < temp.size(); i++)
      {
         pageArray.push_back(temp[i]);
      }
    }
    
    PageRankComparator comp;
    mergeSort<WebPage*>(pageArray, comp); 
  }

  QStringList pageListString;

  if (_loggedIn && prefList.size())
  {
    for (unsigned int i = 0; i < prefList.size(); i++)
    {
       pageListString << prefList[i].name.c_str();
    }
    if (temp.size())
    {
      for (unsigned int i = 0; i < pageArray.size(); i++)
      {
        pageListString << (pageArray[i]->filename()).c_str();
      }
    }
  }         
  else
  {
    for (unsigned int i = 0; i < pageArray.size(); i++)
    {
      pageListString << (pageArray[i]->filename()).c_str();
    }
  }

  pageListWidget->clear(); 
  pageListWidget->addItems(pageListString);  
}


void MainWin::displayPageWindow(QListWidgetItem* wItem)
{
  if (!pageWindow)
  {
    pageWindow = new PageWidget(_currentPage, &_loggedIn, _currentUser,
                                prefLookup);

    pageWindow->setGeometry(840, 150, 600, 480); 
    pageWindow->setWindowTitle("Page Viewer");
    pageWindow->show();
  }

  QVariant data = wItem->data(0); // get data from the widget item
  QString qs = data.toString();   // convert the data to a QString   
  *_currentPage = qs.toStdString();

  if (_loggedIn)
  {
    if (prefLookup->find(*_currentUser)->second.find(*_currentPage)
        != prefLookup->find(*_currentUser)->second.end())
    {
      (prefLookup->find(*_currentUser)->second.find(*_currentPage)->second)++;  
    }
    else
    {
       prefLookup->find(*_currentUser)->second.insert(
			pair<string, int>(*_currentPage, 1));
    }
  }     

  pageWindow->displayPageContent(wItem);
}

void MainWin::displayAdWindow(QListWidgetItem* wItem)
{
  if (!adWindow)
  {
    adWindow = new AdWidget;

    adWindow->setGeometry(250, 580, 170, 170); 
    adWindow->setWindowTitle("Info");
  }

  adWindow->show();
  QVariant data = wItem->data(0); // get data from the widget item
  QString qs = data.toString();   // convert the data to a QString 
  
  // display advertiser info to the ad window
  adWindow->setAdDisplay(qs);

  // adjust the balance of the advertiser
  string compName = qs.toStdString();
  float bid = 0.0;

  for (int i = 0; i < (int) adList.size(); i++)
  {
    if (compName == adList[i]->compName)
    {
      bid = adList[i]->bid;
      break;
    }
  }
   
  if (balance.find(compName) == balance.end())
  {
    balance[compName] = bid;    
  }
  else
  {
    balance[compName] += bid;
  }
}

void MainWin::mainWinExit()
{
  QString arg = qApp->arguments().at(3);
  ofstream outFile(arg.toStdString().c_str());
  if (outFile.fail())
  {
    cout << "Failed to open file " << arg.toStdString() << "!" << endl;
  }
  else
  {
    std::map<std::string, float>::iterator itr;
    for (itr = balance.begin(); itr != balance.end(); itr++)
    {
      outFile << (*itr).first << endl;
      outFile << "$" << (*itr).second << endl << endl;
    } 
    outFile.close();       
  }


  if (pageWindow)
  {
    pageWindow->close();
    delete pageWindow;
  }
  if (adWindow)
  {
    adWindow->close();
    delete adWindow;
  }
  if (createWindow)
  {
    createWindow->close();
    delete createWindow;
  }
  if (loginWindow)
  {
    loginWindow->close();
    delete loginWindow;
  }

  //write to folder personal with user&preference data
  remove("personal/account_data.txt");
  ofstream actData;
  actData.open("personal/account_data.txt");
  map<string, string>::iterator actIt;

  if (actData.fail()) {
    cout << "Failure to write personal data to HD" << endl;
  } else {
    for (actIt = acctMap->begin(); actIt != acctMap->end(); actIt++) {
      actData << actIt->first << " " << actIt->second << " " << endl;

      string uScoreFileName = "personal/";          
      uScoreFileName.append(actIt->first);
      uScoreFileName.append(".txt");
      remove(uScoreFileName.c_str());
      ofstream uScoreData;
      uScoreData.open(uScoreFileName.c_str());

      if (!uScoreData.fail()) {
        map<string, int>::iterator preIt;
        for (preIt = prefLookup->find(actIt->first)->second.begin();
	     preIt != prefLookup->find(actIt->first)->second.end();
             preIt++) {
          uScoreData << preIt->first << " " << preIt->second << endl;
        }
      }
      uScoreData.close();
    }
    actData.close();
  }
}

void MainWin::quit()
{
  mainWinExit();
  qApp->quit();
}

void MainWin::closeEvent(QCloseEvent* event)
{
  mainWinExit();
  QMainWindow::closeEvent(event);
}

void MainWin::createClicked()
{
  if (createWindow)
  {
    createWindow->close();
    delete createWindow;
  }

  createWindow = new CreateWidget(acctMap, prefLookup);
  createWindow->setGeometry(450, 580, 280, 200); 
  createWindow->setWindowTitle("Create Account");  
  createWindow->show();    
}

void MainWin::loginClicked()
{
  if (_loggedIn)  //currently logged in
  {
    QString userName = "Current User: None ";
    QString logText = "Log In";
  
    userLabel->setText(userName);
    loginButton->setText(logText);

    // to do
    // Set<string> forCLeanup;
    // resultList->updateList(forCLeanup, 1);   //clear the result li

    if (pageWindow)
    {
      pageWindow->close();
      delete pageWindow;
      pageWindow = NULL;
    }
    if (adWindow)
    {
      adWindow->close();
      delete adWindow;
      adWindow = NULL;
    }
    if (createWindow)
    {
      createWindow->close();
      delete createWindow;
      createWindow = NULL;
    }
    if (loginWindow)
    {
      loginWindow->close();
      delete loginWindow;
      loginWindow = NULL;
    }

    _loggedIn = false;   
  }
  else          // currently logged out
  { 

    if (pageWindow)
    {
      pageWindow->close();
      delete pageWindow;
      pageWindow = NULL;
    }
    if (adWindow)
    {
      adWindow->close();
      delete adWindow;
      adWindow = NULL;
    }
    if (createWindow)
    {
      createWindow->close();
      delete createWindow;
      createWindow = NULL;
    }
    if (loginWindow)
    {
      loginWindow->close();
      delete loginWindow;
      loginWindow = NULL;
    }

    loginWindow = new LoginWidget(acctMap, prefLookup, _currentUser,
                                  &_loggedIn, loginButton, userLabel);
    loginWindow->setGeometry(450, 580, 280, 160); 
    loginWindow->setWindowTitle("Log In");  
    loginWindow->show();                                      
  }        
}

  
  

  
