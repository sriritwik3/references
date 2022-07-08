# Unbounded Knapsack  
**[Link](https://takeuforward.org/data-structure/unbounded-knapsack-dp-23/)**  
A thief wants to rob a store. He is carrying a bag of capacity W. The store has ‘n’ items of infinite supply.
Its weight is given by the ‘wt’ array and its value by the ‘val’ array. He can either include an item in its knapsack or
exclude it but can’t partially have it as a fraction.  
We need to find the maximum value of items that the thief can steal. He can take a single item any number of times he wants and put it in his knapsack.  

## Solution  
f(ind, j) - Maximum value of items from index 0 to ind, with capacity of knapsack j.  
![image](https://user-images.githubusercontent.com/56584349/177944004-50a7ff2f-e5b8-4caa-9646-48ce531142a9.png)  

## Memoization  
```cpp
#include <bits/stdc++.h>

using namespace std;

int knapsackUtil(vector<int>& wt, vector<int>& val, int ind, int W, vector<vector
<int>>& dp){

    if(ind == 0){
        return ((int)(W/wt[0])) * val[0];
    }
    
    if(dp[ind][W]!=-1)
        return dp[ind][W];
        
    int notTaken = 0 + knapsackUtil(wt,val,ind-1,W,dp);
    
    int taken = INT_MIN;
    if(wt[ind] <= W)
        taken = val[ind] + knapsackUtil(wt,val,ind,W-wt[ind],dp);
        
    return dp[ind][W] = max(notTaken,taken);
}


int unboundedKnapsack(int n, int W, vector<int>& val,vector<int>& wt) {
    
    vector<vector<int>> dp(n,vector<int>(W+1,-1));
    return knapsackUtil(wt, val, n-1, W, dp);
}

int main() {

  vector<int> wt = {2,4,6};
  vector<int> val = {5,11,13};
  int W=10;
  
  int n = wt.size();
                                 
  cout<<"The Maximum value of items, thief can steal is " <<unboundedKnapsack
  (n,W,val,wt);
}
```
TC - O(NW), SC - O(NW) + O(N)  

## Tabulation  
```cpp
#include <bits/stdc++.h>

using namespace std;

int unboundedKnapsack(int n, int W, vector<int>& val,vector<int>& wt) {
    
    vector<vector<int>> dp(n,vector<int>(W+1,0));
    
    //Base Condition
    
    for(int i=wt[0]; i<=W; i++){
        dp[0][i] = ((int) i/wt[0]) * val[0];
    }
    
    for(int ind =1; ind<n; ind++){
        for(int cap=0; cap<=W; cap++){
            
            int notTaken = 0 + dp[ind-1][cap];
            
            int taken = INT_MIN;
            if(wt[ind] <= cap)
                taken = val[ind] + dp[ind][cap - wt[ind]];
                
            dp[ind][cap] = max(notTaken, taken);
        }
    }
    
    return dp[n-1][W];
}

int main() {

  vector<int> wt = {2,4,6};
  vector<int> val = {5,11,13};
  int W=10;
  
  int n = wt.size();
                                 
  cout<<"The Maximum value of items, thief can steal is " <<unboundedKnapsack
  (n,W,val,wt);
}
```
TC, SC - O(NW)  
  
