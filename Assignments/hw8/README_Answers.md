###Student Information
  + Name: Hao Cui
  + USC Email: hcui@usc.edu
  + USC ID: 1454367516

###Complie Instruction

make 
all executables will be in the repo folder

###Design&Answers
Q3: I use mergesort twice seperately, and I use a map to implement lookup, because stl map accessor is O(log(n)), so the whole lookup loop is O(nlog(n))  

Q5: 
For the graph, the number before the comma is degree, after the comma is time in sec.
the degree is in log-scale
What I observered from the graph:
The running time of insert is decreasing as the degree increasing. The running time of remove is first decreasing then increasing as the degree increasing.

For the insert it's becuase the larger the degree, the less overhead to deal with bubble up/trickle up. For remove,at first it's decreasing becuase of the same reason as insert, it need to deal with bubble down/trickle down, but becuase in the bubble/trickle down, it needs to loop through all its children to determine the highest priority, so eventually this process's delay is having more siginificant impact than the less times of trickle down overhead.
