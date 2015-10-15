##CSCI 104 Project Repository

###Student Information
  + Name: Hao Cui
  + USC Email: hcui@usc.edu
  + USC ID: 1454367516

Please put everything in one folder, 
-qmake project
-qmake
-make
to compile

elements intro:
Boodle is the main cpp file
searchWindow is the search window class
pageWindow is the sub page window class
MySearchList is the class inheri from QListWidget

GUI intro:
for the main window, in the search textfild, use space to seperate words, 
use the raidobutton at the bottom to select AND OR search mode,
click on the search results in list then click GoToPage button to open subwindow

In the subwindow, on the right column, the upper list is outGoing links, click on the link you
want first, then click the goToOutgoingPage button on the top.
The lower list is incoming links, click on the link first, then click the goToIncomingPage button
on the bottom.

General intro:
mainly I use string as the "pointer", all the Qt classes has some sort of internal storage of pointers
that point back to the main data map,set,list.

For Qt, for both windows I use a string pointer to store the user current selection of list, the poiner
is passed into the list class
