
// The implementation of the PageWidget class and the AdWidget 
// class.

#include <iostream>
#include <QString>
#include <QStringList>
#include <QStringListModel>
#include <QLabel>
#include <QVariant>
#include <iostream>
#include <fstream>
#include "webpage.h"
#include "SubWin.h"
#include "project.h"

using namespace std;

// golbal map defined in main.cpp
// extern map<string, WebPage*> pageMap;
// 

PageWidget::PageWidget(string* cPage, bool* in, string* cUser, 
                       map<string, map<string, int> >* lookup)
{
  currentPage = cPage;
  loggedIn = in;
  currentUser = cUser;
  prefLookup = lookup;

  mainLayout = new QVBoxLayout(this); // associated with this objec

  fileLabel = new QLabel("File:");
  contentLayout = new QHBoxLayout;
  document = new QTextEdit;
  linkLayout = new QVBoxLayout;
  incomingLabel = new QLabel("Incoming Links:");
  incomingList = new QListWidget;
  outgoingLabel = new QLabel("Outgoing Links:");
  outgoingList = new QListWidget;

  linkLayout->addWidget(incomingLabel);
  linkLayout->addWidget(incomingList);
  linkLayout->addWidget(outgoingLabel);
  linkLayout->addWidget(outgoingList);

  document->setReadOnly(true);
  contentLayout->addWidget(document);
  contentLayout->addLayout(linkLayout); 
  contentLayout->setStretch(0, 25);
  contentLayout->setStretch(1, 10);
  
  mainLayout->addWidget(fileLabel);
  mainLayout->addLayout(contentLayout);
  this->setLayout(mainLayout);

  QObject::connect(incomingList, SIGNAL(itemClicked(QListWidgetItem *)),
                   this, SLOT(pageSelected(QListWidgetItem *)));
  QObject::connect(outgoingList, SIGNAL(itemClicked(QListWidgetItem *)),
                   this, SLOT(pageSelected(QListWidgetItem *)));
}

void PageWidget::pageSelected(QListWidgetItem* wItem)
{
  if (*loggedIn)
  {
    if (prefLookup->find(*currentUser)->second.find(*currentPage)
        != prefLookup->find(*currentUser)->second.end())
    {
      (prefLookup->find(*currentUser)->second.find(*currentPage)->second)++;  
    }
    else
    {
       prefLookup->find(*currentUser)->second.insert(
			pair<string, int>(*currentPage, 1));
    }
  }     

  displayPageContent(wItem);
}

void PageWidget::displayPageContent(QListWidgetItem* wItem)
{
  QVariant data = wItem->data(0); // get data from the widget item
  QString qs = data.toString();   // convert the data to a QString   
  QString labelText = "File: ";  
  labelText += qs;                // construct a new label text

  string fileName = qs.toStdString();
  WebPage* page = pageMap[fileName];

  (this->fileLabel)->setText(labelText); // replace the old label text
  this->show();

  ifstream inFile(fileName.c_str()); // open the page file
  if (inFile.fail())
  {
    throw runtime_error("Failed to open the web page!");
  }
 
  string line; 
  string fileString;
  while (std::getline(inFile, line)) // read the file one line at a time
  {
    string outString;
    for (unsigned int i = 0; i < line.size(); i++)
    {
      if (line[i] == '[')
      {
        int openBracket = i;
        int closeBracket;
        int openParenthesis;
        int closeParenthesis;
        if (parseLink(line, openBracket, closeBracket, openParenthesis, 
            closeParenthesis)) // if this is the begining of a link 
        {                      // anchor and the file name of the link
          for (int j = openBracket + 1; j < closeBracket; j++)
          {
            outString += line[j];
          }
          i = closeParenthesis;
	  continue;
        }
      }
    
      outString += line[i];
    }
    fileString += outString;
    fileString += "\n";
  }
  
  inFile.close();

  QString pageString = fileString.c_str();  
  document->clear();
  document->setText(pageString);

  Set<WebPage*> outLinkSet = page->allOutgoingLinks();
  QStringList outLink;
  
  Set<WebPage*>::iterator itr = outLinkSet.begin();
  for ( ; itr != outLinkSet.end(); itr++)
  {
    outLink << ((*itr)->filename()).c_str();
  }
  outgoingList->clear();
  outgoingList->addItems(outLink); 

  Set<WebPage*> inLinkSet = page->allIncomingLinks();
  QStringList inLink;
  
  itr = inLinkSet.begin();
  for ( ; itr != inLinkSet.end(); itr++)
  {
    inLink << ((*itr)->filename()).c_str();
  }
  incomingList->clear();
  incomingList->addItems(inLink);  
}

AdWidget::AdWidget()
{
  mainLayout = new QVBoxLayout(this);
  //adLabel = new QLabel("");
  adDisplay = new QTextEdit;  
  //mainLayout->addWidget(adLabel);
  mainLayout->addWidget(adDisplay);
  this->setLayout(mainLayout);
}

//void AdWidget::setAdLabel(QString qs)
void AdWidget::setAdDisplay(QString qs)
{
  QString text = "\nYou have visited\nthe web site of\n";
  adDisplay->setReadOnly(true);
  adDisplay->clear();
  adDisplay->setAlignment(Qt::AlignCenter);
  adDisplay->append(text);
  adDisplay->setAlignment(Qt::AlignCenter);
  adDisplay->append(qs);
}

CreateWidget::CreateWidget(map<std::string, string>* aMap,
                           map<string, map<string, int> >* pLookup)
{
  nameLabel = new QLabel("Enter User Name:");
  nameLabel->setFixedWidth(120);
  nameLabel->setAlignment(Qt::AlignRight);
  nameLine =new QLineEdit;
  passWdLabel = new QLabel("Enter Password:");
  passWdLabel->setFixedWidth(120);
  passWdLabel->setAlignment(Qt::AlignRight);
  passWdLine = new QLineEdit;
  passWdReLabel = new QLabel("Confirm Password:");
  passWdReLabel->setFixedWidth(120);
  passWdReLabel->setAlignment(Qt::AlignRight);
  passWdReLine = new QLineEdit;
  info = new QLabel;
  createButton = new QPushButton("Create Account");
  cancelButton = new QPushButton("Close");

  passWdLine->setEchoMode(QLineEdit::Password);
  passWdReLine->setEchoMode(QLineEdit::Password);

  QVBoxLayout* mainLayout = new QVBoxLayout;
  QHBoxLayout* firstLine = new QHBoxLayout;
  QHBoxLayout* secondLine = new QHBoxLayout;
  QHBoxLayout* thirdLine = new QHBoxLayout;
  QHBoxLayout* buttonLine = new QHBoxLayout;

  firstLine->addWidget(nameLabel);
  firstLine->addWidget(nameLine);

  secondLine->addWidget(passWdLabel);
  secondLine->addWidget(passWdLine);

  thirdLine->addWidget(passWdReLabel);
  thirdLine->addWidget(passWdReLine);

  buttonLine->addStretch();
  buttonLine->addWidget(createButton);
  buttonLine->addWidget(cancelButton);

  mainLayout->addLayout(firstLine);
  mainLayout->addLayout(secondLine);
  mainLayout->addLayout(thirdLine);
  // mainLayout->addStretch();
  mainLayout->addWidget(info);
  mainLayout->addLayout(buttonLine);

  acctMap = aMap;
  prefLookup = pLookup;

  connect(createButton, SIGNAL(clicked()), this, SLOT(createClicked()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));

  setLayout(mainLayout);
}

CreateWidget::~CreateWidget() { } 

void CreateWidget::createClicked()
{
  string name = nameLine->text().toStdString();
  string passWd = passWdLine->text().toStdString();
  string passWdRe = passWdReLine->text().toStdString();

  if (acctMap->find(name) != acctMap->end()) 
  {
    info->setText("Account with this name already exists!");
  } 
  else if (passWd != passWdRe) 
  {
    info->setText("The passwords entered do not match!");
  } 
  else if (name == "account_data" || name == "N/A" || name == "None") 
  {
    info->setText("Sorry this name is resevered.");
  } 
  else 
  {
    acctMap->insert(pair<string, string>(name, passWd));
    map<string, int> newSMap;
    prefLookup->insert(pair<string, map<string, int> >(name, newSMap));
    QString msg = ("Account ");
    msg += nameLine->text();
    msg += (" created.");
    //info->setText("Account created!");
    info->setText(msg);
    nameLine->clear();
    passWdLine->clear();
    passWdReLine->clear();
  }
}

void CreateWidget::cancelClicked()
{
  this->close();
} 

LoginWidget::LoginWidget(map<std::string, string>* aMap,
                         map<string, map<string, int> >* pLookup,
                         string* user, bool* in, QPushButton* inOutButton,
                         QLabel* userInfo)
{
  nameLabel = new QLabel("Enter User Name:");
  nameLabel->setFixedWidth(120);
  nameLabel->setAlignment(Qt::AlignRight);
  nameLine =new QLineEdit;
  passWdLabel = new QLabel("Enter Password:");
  passWdLabel->setFixedWidth(120);
  passWdLabel->setAlignment(Qt::AlignRight);
  passWdLine = new QLineEdit;
  info = new QLabel;
  loginButton = new QPushButton("Log In");
  closeButton = new QPushButton("Close");

  passWdLine->setEchoMode(QLineEdit::Password);

  QVBoxLayout* mainLayout = new QVBoxLayout;
  QHBoxLayout* firstLine = new QHBoxLayout;
  QHBoxLayout* secondLine = new QHBoxLayout;
  QHBoxLayout* buttonLine = new QHBoxLayout;

  firstLine->addWidget(nameLabel);
  firstLine->addWidget(nameLine);

  secondLine->addWidget(passWdLabel);
  secondLine->addWidget(passWdLine);

  buttonLine->addStretch();
  buttonLine->addWidget(loginButton);
  buttonLine->addWidget(closeButton);

  mainLayout->addLayout(firstLine);
  mainLayout->addLayout(secondLine);
  mainLayout->addStretch();
  mainLayout->addWidget(info);
  mainLayout->addLayout(buttonLine);

  acctMap = aMap;
  prefLookup = pLookup;
  currentUser = user;
  login = in;
  mainUserNameLabel = userInfo;
  mainLoginButton = inOutButton;

  connect(loginButton, SIGNAL(clicked()), this, SLOT(loginClicked()));
  connect(closeButton, SIGNAL(clicked()), this, SLOT(closeClicked()));

  setLayout(mainLayout);
}

LoginWidget::~LoginWidget() { }


void LoginWidget::loginClicked() 
{ 
  QString userNameQS = nameLine->text();
  string userName = userNameQS.toStdString();
  string passWd = passWdLine->text().toStdString();

  if (acctMap->find(userName) == acctMap->end()) 
  {
    info->setText("Account doesn't exist!");
  }
  else if (passWd != acctMap->find(userName)->second) 
  {
    info->setText("Password doesn't match!");
  } 
  else 
  {
    *currentUser = userName;
    info->setText("");
    QString userInfo  = "Current User: ";
    userInfo += userNameQS;
    userInfo += "  ";
    // cout << mainUserNameLabel << endl;
    // cout << userInfo.toStdString() << endl;
    mainUserNameLabel->setText(userInfo);
    mainLoginButton->setText("Log Out");
    *login = true;
    this->close();
  }
}

void LoginWidget::closeClicked() 
{ 
  this->close();
}

