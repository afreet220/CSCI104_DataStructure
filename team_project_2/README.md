##CSCI 104 Team Project Repository

###Student Information
**Developer 1**:
  + Name: Hao Cui
  + USC Email: hcui@usc.edu
  + USC ID: 1454367516

**Developer 2**:
  + Name: Julia Lin
  + USC Email: julialin@usc.edu
  + USC ID: 8250121446

A .pro file and a Makefile are already included; thus, the command to compile the project is simply 'make'. The name of the executable is ./team_project_130, and to use the provided data to run the program, you can use to command "./team_project_130 ./data/index.txt ./data/ad.txt bill.txt".

For step 2 we chose to implement personalization.

Goal:
Account creation, log in/out.
Output pages in the order of user's page preference as priority.
Account info memory on hard drive.

The create account and log in buttons are located in the upper right. After setting an account and password, which will be recorded in a text file under the 'personal' folder, the user can then login to his/her account. While logged into an account, the pages that the user clicked on more often will be displayed higher up (ranked higher) the next time the search takes place. The user's preference is also recorded in text files under the 'personal' folder.

______________________

Implementation details:
in main.cpp:
Added in file reading part, load in all existing account/password into a map<string,string>, and then read in each user's preference data into another map<string, map<string,int> >. pointers point back to these two map were passed into the Qt main window constructor

in mainwindow :
create/log in/log out buttons added
user status added ( QLabel)
one bool to determine if login/out
one string to memory current user name
two pointers point back to main for account/preference lookup

in quit SLOT, add in write data part, store account/preference into personal/ folder
in go to page SLOT, add in code updating user preference page score

in create account window:
This is a Qt object for account creation. Existing account checking implemeted.
Constructor receives pointer pointed back to account lookup map

in login window:
This is a Qt object for account log in. password checking implemented.
Constructor receives pointer pointed back to account lookup map, current user string
In the login slot, update mainWindow's login status, current user

in result list:
(This is a customized QtListWidget. It's used both for the mainWindow's result list and pagewindow's outgoing and incoming list. )

Add in necessary pointer, in the constructor to build connections for account info lookup.
Add in a struct and a functor for user preference page sorting.

Basically before doing the regular pagerank sorting, use a loop to traverse the result set and copy whatever pages that user has visited before into a new list. Call merge sort on this list. Then filter out these pages from the regular result set. Then proceed to normal pagerank sorting. In the output, add preference pages first with visit times as priority then unvisited pages with normal page rank ordering.

in page content window:
(This is the sub window)
Add in necessary pointer,in the constructor to build connections for account/preference info lookup.
In the SLOTS, if user visit pages from the outgoing/incoming list, update the user page preference score.
