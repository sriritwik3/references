# Partition Equal Subset Sum  
**[Link](https://takeuforward.org/data-structure/partition-equal-subset-sum-dp-15/)**  
We are given an array ‘ARR’ with N positive integers. We need to find if we can partition the array into two subsets such that
the sum of elements of each subset is equal to the other.  
If we can partition, return true else return false  

## Solution  
Same as the previous problem but with a slight modification.  
If the total sum is odd, return false.  
Else check whether a subsequence of sum total_sum/2 exists.  

