# Buy and Sell stock II  
**[Link](https://takeuforward.org/data-structure/buy-and-sell-stock-ii-dp-36/)**  
We are given an array Arr[] of length n. It represents the price of a stock on ‘n’ days. The following guidelines need to be followed:  

- We can buy and sell the stock any number of times.
- In order to sell the stock, we need to first buy it on the same or any previous day.
- We can’t buy a stock again after buying it once. In other words, we first buy a stock and then sell it. After selling we can buy and sell again. But we can’t sell before buying and can’t buy before selling any previously bought stock.  

![image](https://user-images.githubusercontent.com/56584349/178094061-24a01fbf-3d5d-4432-8d54-b1c0ebfb5c3b.png)  

## Solution  

![image](https://user-images.githubusercontent.com/56584349/178095355-e5522f3c-7a8a-4bdc-a3ec-54b1319a818d.png)  
if buy == 0, we can either buy the stock or choose not to do any transaction.  
if buy == 1, we can either sell the stock or choose not to do any transaction.  

## Memoization  
```cpp
#include <bits/stdc++.h>

using namespace std;

long getAns(long *Arr, int ind, int buy, int n, vector<vector<long>> &dp ){

    if(ind==n) return 0; //base case
    
    if(dp[ind][buy]!=-1)
        return dp[ind][buy];
        
    long profit;
    
    if(buy==0){// We can buy the stock
        profit = max(0+getAns(Arr,ind+1,0,n,dp), -Arr[ind] + getAns(Arr,ind+1,1,n,dp));
    }
    
    if(buy==1){// We can sell the stock
        profit = max(0+getAns(Arr,ind+1,1,n,dp), Arr[ind] + getAns(Arr,ind+1,0,n,dp));
    }
    
    return dp[ind][buy] = profit;
}


long getMaximumProfit(long *Arr, int n)
{
    //Write your code here
    
    vector<vector<long>> dp(n,vector<long>(2,-1));
    
    if(n==0) return 0;
    long ans = getAns(Arr,0,0,n,dp);
    return ans;
}

int main() {

  int n =6;
  long Arr[n] = {7,1,5,3,6,4};
                                 
  cout<<"The maximum profit that can be generated is "<<getMaximumProfit(Arr, n);
}
```
TC - (2N), SC - O(2N) + O(N)  

## Tabulation  
```cpp
#include <bits/stdc++.h>

using namespace std;


long getMaximumProfit(long *Arr, int n)
{
    //Write your code here
    
    vector<vector<long>> dp(n+1,vector<long>(2,-1));
    
    //base condition
    dp[n][0] = dp[n][1] = 0;
    
    long profit;
    
    for(int ind= n-1; ind>=0; ind--){
        for(int buy=0; buy<=1; buy++){
            if(buy==0){// We can buy the stock
                profit = max(0+dp[ind+1][0], -Arr[ind] + dp[ind+1][1]);
            }
    
            if(buy==1){// We can sell the stock
                profit = max(0+dp[ind+1][1], Arr[ind] + dp[ind+1][0]);
            }
            
            dp[ind][buy]  = profit;
        }
    }
    return dp[0][0];
}

int main() {

  int n =6;
  long Arr[n] = {7,1,5,3,6,4};
                                 
  cout<<"The maximum profit that can be generated is "<<getMaximumProfit(Arr, n);
}
```
TC,SC - O(2N)  

## Space optimised  
```cpp
#include <bits/stdc++.h>

using namespace std;


long getMaximumProfit(long *Arr, int n)
{
    //Write your code here
    
    vector<long> ahead (2,0);
    vector<long> cur(2,0);
    
    //base condition
    ahead[0] = ahead[1] = 0;
    
    long profit;
    
    for(int ind= n-1; ind>=0; ind--){
        for(int buy=0; buy<=1; buy++){
            if(buy==0){// We can buy the stock
                profit = max(0+ahead[0], -Arr[ind] + ahead[1]);
            }
    
            if(buy==1){// We can sell the stock
                profit = max(0+ahead[1], Arr[ind] + ahead[0]);
            }
            cur[buy]  = profit;
        }
        
        ahead = cur;
    }
    return cur[0];
}

int main() {

  int n =6;
  long Arr[n] = {7,1,5,3,6,4};
                                 
  cout<<"The maximum profit that can be generated is "<<getMaximumProfit(Arr, n);
}
```
TC, SC - o(2N), O(1)
