# Target Sum  
**[Link](https://takeuforward.org/data-structure/target-sum-dp-21/)**  
We are given an array ‘ARR’ of size ‘N’ and a number ‘Target’. Our task is to build an expression from the given array where we can place a ‘+’ or ‘-’ sign in
front of an integer. We want to place a sign in front of every integer of the array and get our required target.
We need to count the number of ways in which we can achieve our required target.  

## Solution  
This can be modified to the problem count subsets with sum (totalSum - target)/2.  
Let's split the given array into S1 and S2. S1 be the elements with positive sign and S2 with negative sign.  
S1 + S2 = totalSum.
S1 - S2 = target.  
==> S2  = (totalSum - target)/2.  
