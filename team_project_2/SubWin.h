
// The header file of the PageWidget class and the AdWidget class.

#ifndef SUB_WIN_H
#define SUB_WIN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QTextDocument>
#include <QTextEdit>
#include <string>
#include <map>

using namespace std;

class PageWidget : public QWidget
{
  Q_OBJECT

public:
  PageWidget(string* currentPage, bool* loggedIn, string* user, 
             map<string, map<string, int> >* lookookup);
  // ~PageWidget();

  void displayPageContent(QListWidgetItem* item);

public slots:
  void pageSelected(QListWidgetItem* item);

private:
  QVBoxLayout* mainLayout; 
  QLabel*      fileLabel;
  QHBoxLayout* contentLayout;
  QTextEdit*   document;
  QVBoxLayout* linkLayout;
  QLabel*      incomingLabel;
  QListWidget* incomingList;
  QLabel*      outgoingLabel;
  QListWidget* outgoingList;

  string*      currentUser;
  string*      currentPage;
  bool*        loggedIn;
  map<string, map<string, int> >* prefLookup;
};

class AdWidget : public QWidget
{
public:
  AdWidget();
  void setAdDisplay(QString qs);

private:
  QVBoxLayout* mainLayout;
  QTextEdit*   adDisplay;
};

class CreateWidget : public QWidget
{
  Q_OBJECT

public:
  CreateWidget(map<std::string, string>*,
               map<string, map<string, int> >*);
  ~CreateWidget();

private slots:
  void createClicked();
  void cancelClicked();
  
private:
  QLabel*      nameLabel;
  QLineEdit*   nameLine;
  QLabel*      passWdLabel;
  QLineEdit*   passWdLine;
  QLabel*      passWdReLabel;
  QLineEdit*   passWdReLine;
  QLabel*      info;
  QPushButton* createButton;
  QPushButton* cancelButton;

  map<std::string, string>*       acctMap;
  map<string, map<string, int> >* prefLookup;
};


class LoginWidget : public QWidget
{
  Q_OBJECT

public:
  LoginWidget(map<std::string, string>*,
              map<string, map<string, int> >*, 
              string*, bool*, QPushButton*, QLabel*);
  ~LoginWidget();

private slots:
  void loginClicked();
  void closeClicked();
  
private:
  QLabel*      nameLabel;
  QLineEdit*   nameLine;
  QLabel*      passWdLabel;
  QLineEdit*   passWdLine;
  QLabel*      info;
  QPushButton* loginButton;
  QPushButton* closeButton;

  string*      currentUser;  
  bool*        login;
  QLabel*      mainUserNameLabel;
  QPushButton* mainLoginButton;

  map<std::string, string>*       acctMap;
  map<string, map<string, int> >* prefLookup;
};

#endif

