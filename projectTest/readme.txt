/*
Method: Sort and compare
Step 1  : Sort shuttle and passenger vectors in ascending order.
Step 2  : Assign pointers to index 0 of both vectors
Step 3  : Compare value at both pointers
Step 4a : If values are not =, increment index at smaller value
Step 4b : If values are =, remove both index from vectors and restart at index 0
Step 5  : Repeat Step 2 to 4 until either pointer reaches null then break loop 

Example:
v<P> = a,d,g,y,e --> v<P>.sorted = a,d,e,g,y,(null)
v<S> = q,e,g,i,a --> V<S>.sorted = a,e,g,i,q,(null)

ptrP    vs  ptrS
a           a       ==> paired
d           e       ==> increment ptrP
e           e       ==> paired
d           g       ==> increment ptrP
g           g       ==> paired
d           i       ==> increment ptrP
y           i       ==> increment ptrS
y           q       ==> increment ptrS
y           null    ==> break loop

Concept:
By having the vectors be sorted and incrementing the index of the smaller value,
it ensures that the pointers will always be kept to the smallest unchecked element
of their respective vectors. In terms of time complexity, the best case is Omega(n)
where a match is made at every comparison. the worst case would be if only the last
nodes of both vectors are a match resulting the the algorithm doing a full iteration
of all nodes twice to before hitting null as such the time complexity would be 2n-1
with the order of growth of O(n).
*/