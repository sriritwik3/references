# Greedy
## Striver Sheet  
**[Link](https://takeuforward.org/interviews/strivers-sde-sheet-top-coding-interview-problems/)**  
# 1) Minimum number of coins  
Given a value V, if we want to make a change for V Rs, and we have an infinite supply of each of the denominations in Indian currency, i.e., we have an infinite supply of { 1, 2, 5, 10, 20, 50, 100, 500, 1000} valued coins/notes, what is the minimum number of coins and/or notes needed to make the change.  
```cpp
for (int i = n - 1; i >= 0; i--) {
    while (V >= coins[i]) {
      V -= coins[i];
      ans.push_back(coins[i]);
    }
  }
```
TC - O(V), SC - O(1)  

# 2) Job sequencing Problem  

# 3) N meetings in one room  

# 4) Minimum number of platforms required  

# 5) Fractional Knapsack  

# 6) Activity Selection  
