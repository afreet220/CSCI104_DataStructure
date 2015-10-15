##CSCI 104 HW5 Repository

###Student Information
  + Name: Hao Cui
  + USC Email: hcui@usc.edu
  + USC ID: 1454367516

boolean_eva.cpp is my main cpp file for question 7. 

makefile will produce all three executable, boolean_eva,speed_test,arraylist_test,in current folder

I included my own two test files, test_formula.txt and test_var.txt, just in case

My strategy for question 7:

**********This is long if you don't have problems understanding my code just ignore it****************

I use the int approach in suggestion 2

Before main, I declare a bunch of golbal constant that corresponding to all the symbols

And I also declare a struct "variable" that contain each assigment variable's name and T/F value

In main, first I read from the assignment file, use a list<variable> to store all variable info

Then for each line of formula file, I first do a general filter loop

In this loop I eat whitespaces, change variables to T/F value, and mark

malformed if unassign variable occur. I store the filtered infos into a list<int>

Then I do a second loop, pop ints from list<int> at the beginning into stack, if I hit close parenthesis, deal with the stack

For each parenthesis bracket, I frist check if the first int popped is variable. And then I peek and memorry

the next symbol, and or or. And then I use a while loop to read in two items within each loop, store all the

T/F value into a temporal list, and check if symbols are identical with the memory one, also mark malform if

any illegal form occur. When I hit open prenthesis, I use the temporal list along with the and/or symbol to

determine T/F value of the parenthesis bracket. After it's determined I push it back to the stack.

When the list<int> is empty, check if there are still negative signs left in the stack(I also check negative

everytime I encounter a variabe during previous section). After each line is done, I store the final result

into a list<int>, where 123 means T/F/Malformed. After all lines done I print the result.



