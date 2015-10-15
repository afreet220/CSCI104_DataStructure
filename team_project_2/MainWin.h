
// The header file of the MainWin class.

#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QComboBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QTextEdit>
#include <string>
#include <map>
#include "SubWin.h"
#include "project.h"
#include "myVector.h"

using namespace std;

enum queryType {
  AND,
  OR
};

enum sortingType {
  RANK,
  ALPH
};

class MainWin : public QMainWindow 
{
  Q_OBJECT

public: 
  MainWin(map<string, string>*,
          map<string, map<string, int> >*);   
  ~MainWin();

protected:
  void closeEvent(QCloseEvent* event);

private slots:
  void createClicked();
  void loginClicked();
  void doSearch();
  void setQueryType(int i);
  void setSortingType(int i);
  void displayPageWindow(QListWidgetItem* item);
  void displayAdWindow(QListWidgetItem* item);
  void mainWinExit();
  void quit();

private:
  QVBoxLayout*  mainLayout;
  QHBoxLayout*  firstLayout;
  QLabel*       userLabel;
  QPushButton*  createAccButton;
  QPushButton*  loginButton;
  QHBoxLayout*  secondLayout; 
  QLabel*       promptLabel;
  QVBoxLayout*  queryLayout;
  QLineEdit*    queryEdit;
  QHBoxLayout*  selectionLayout;
  QLabel*       queryTypeLabel;
  QComboBox*    queryTypeCombo;
  QLabel*       sortingTypeLabel;
  QComboBox*    sortingTypeCombo;
  QPushButton*  searchButton; 
  QListWidget*  pageListWidget;
  QHBoxLayout*  exitLayout;
  QPushButton*  exitButton;
  QListWidget*  adListWidget;
  QWidget*      centerWidget;
  PageWidget*   pageWindow;
  AdWidget*     adWindow;
  CreateWidget* createWindow;
  LoginWidget*  loginWindow;

  string*      _currentPage;
  string*      _currentUser;
  queryType    _queryType;
  sortingType  _sortingType;
  bool         _loggedIn;  

  std::vector<AdBid*>             adList;
  std::map<std::string, float>    balance; 
  map<string, string>*            acctMap;
  map<string, map<string, int> >* prefLookup;
};

#endif
