# Minimum Coins  
**[Link](https://takeuforward.org/data-structure/minimum-coins-dp-20/)**  
We are given a target sum of ‘X’ and ‘N’ distinct numbers denoting the coin denominations.  
We need to tell the minimum number of coins required to reach the target sum. We can pick a coin denomination for any number of times we want.  

## Solution  
f(ind, t) - minimum number of coins required to get target t if we consider the arr from 0 to index ind.  
![image](https://user-images.githubusercontent.com/56584349/177937491-f9c3d3ec-500c-45e6-8e97-040245933638.png)  

## Memoization  
```cpp
#include <bits/stdc++.h>

using namespace std;

int minimumElementsUtil(vector<int>& arr, int ind, int T, vector<vector<int>>& dp){

    if(ind == 0){
        if(T%arr[0] == 0) return T/arr[0];
        else return 1e9;
    }
    
    if(dp[ind][T]!=-1)
        return dp[ind][T];
        
    int notTaken = 0 + minimumElementsUtil(arr,ind-1,T,dp);
    
    int taken = 1e9;
    if(arr[ind] <= T)
        taken = 1 + minimumElementsUtil(arr,ind,T-arr[ind],dp);
        
    return dp[ind][T] = min(notTaken,taken);
}


int minimumElements(vector<int>& arr, int T){
    
    int n= arr.size();
    
    vector<vector<int>> dp(n,vector<int>(T+1,-1));
    int ans =  minimumElementsUtil(arr, n-1, T, dp);
    if(ans >= 1e9) return -1;
    return ans;
}

int main() {

  vector<int> arr ={1,2,3};
  int T=7;
                                 
  cout<<"The minimum number of coins required to form the target sum is " 
  <<minimumElements(arr,T);
}
```
TC - O(NT), SC - O(NT) + O(N)  

## Tabulation  
```cpp
#include <bits/stdc++.h>

using namespace std;

int minimumElements(vector<int>& arr, int T){
    
    int n= arr.size();
    
    vector<vector<int>> dp(n,vector<int>(T+1,0));
    
    for(int i=0; i<=T; i++){
        if(i%arr[0] == 0)  
            dp[0][i] = i/arr[0];
        else dp[0][i] = 1e9;
    }
    
    for(int ind = 1; ind<n; ind++){
        for(int target = 0; target<=T; target++){
            
            int notTake = 0 + dp[ind-1][target];
            int take = 1e9;
            if(arr[ind]<=target)
                take = 1 + dp[ind][target - arr[ind]];
                
             dp[ind][target] = min(notTake, take);
        }
    }
    
    int ans = dp[n-1][T];
    if(ans >=1e9) return -1;
    return ans;
}

int main() {

  vector<int> arr ={1,2,3};
  int T=7;
                                 
  cout<<"The minimum number of coins required to form the target sum is " 
  <<minimumElements(arr,T);
}
```
TC, SC - O(NT)  

## Space Optimised  
```cpp
#include <bits/stdc++.h>

using namespace std;

int minimumElements(vector<int>& arr, int T){
    
    int n= arr.size();
    
    vector<int> prev(T+1,0), cur(T+1,0);
    
    for(int i=0; i<=T; i++){
        if(i%arr[0] == 0)  
            prev[i] = i/arr[0];
        else prev[i] = 1e9;
    }
    
    for(int ind = 1; ind<n; ind++){
        for(int target = 0; target<=T; target++){
            
            int notTake = 0 + prev[target];
            int take = 1e9;
            if(arr[ind]<=target)
                take = 1 + cur[target - arr[ind]];
                
             cur[target] = min(notTake, take);
        }
        prev = cur;
    }
    
    int ans = prev[T];
    if(ans >=1e9) return -1;
    return ans;
}


int main() {

  vector<int> arr ={1,2,3};
  int T=7;
                                 
  cout<<"The minimum number of coins required to form the target sum is " 
  <<minimumElements(arr,T);
}
```
TC - O(NT), SC - O(T)  
