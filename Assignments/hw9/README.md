###Student Information
  + Name: Hao Cui
  + USC Email: hcui@usc.edu
  + USC ID: 1454367516

###Complie Instruction

make 
all executables will be in the repo folder

###Design&Answers
Q4:

First I declare a struct with student name and skill, and then delcare a queue mostly for remeberming order and also a unordered multi map.

In the parsing loop, other then storing data, I also calculate the total skill of all the students

After the loop I divide the total skill with half the total number of students, the result should be the average team skill. Then I use queue to pop out each student struct to get the current, then use multimap lookup finding the average subtract current student's skill, this should be his/her potential teammate's skill, if it can't be found, report failure.

Because both queue/unordered_multimap's access/insert/query are O(N), it should fullfill the requirement.

Q5:

It's two photos in jpg format.
