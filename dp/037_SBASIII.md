# Buy and Sell Stock III  
**[Link](https://takeuforward.org/data-structure/buy-and-sell-stock-iii-dp-37/)**  
We are given an array Arr[] of length n. It represents the price of a stock on ‘n’ days. The following guidelines need to be followed:  

- We can buy and sell the stock any number of times.
- In order to sell the stock, we need to first buy it on the same or any previous day.
- We can’t buy a stock again after buying it once. In other words, we first buy a stock and then sell it. After selling we can buy and sell again. But we can’t sell before buying and can’t buy before selling any previously bought stock.
- We can do at most 2 transactions.  

## Solution  
f(ind, buy, rem) - maximum profit we can generate from day ind to day n-1 where buy - tells whether we can buy/sell on that particular day, rem - no.of transactions
remaining.  
![image](https://user-images.githubusercontent.com/56584349/178096532-21281cfa-f25e-4d80-bd35-95f31414db02.png)  

## Memoization  
```cpp
#include <bits/stdc++.h>

using namespace std;

int getAns(vector<int>& Arr, int n, int ind, int buy, int cap, vector<vector<vector<int>>>& dp ){

    if(ind==n || cap==0) return 0; //base case
    
    if(dp[ind][buy][cap]!=-1)
        return dp[ind][buy][cap];
        
    int profit;
    
    if(buy==0){// We can buy the stock
        profit = max(0+getAns(Arr,n,ind+1,0,cap,dp), 
                    -Arr[ind] + getAns(Arr,n,ind+1,1,cap,dp));
    }
    
    if(buy==1){// We can sell the stock
        profit = max(0+getAns(Arr,n,ind+1,1,cap,dp),
                    Arr[ind] + getAns(Arr,n,ind+1,0,cap-1,dp));
    }
    
    return dp[ind][buy][cap] = profit;
}


int maxProfit(vector<int>& prices, int n)
{
    // Creating a 3d - dp of size [n][2][3]
    vector<vector<vector<int>>> dp(n,
                                    vector<vector<int>> 
                                            (2,vector<int>(3,-1)));
    
    return getAns(prices,n,0,0,2,dp);
   
}

int main() {

  vector<int> prices = {3,3,5,0,0,3,1,4};
  int n = prices.size();
                                 
  cout<<"The maximum profit that can be generated is "<<maxProfit(prices, n);
}
```
TC - O(2 * N * 3), SC - O(2 * N * 3) + O(N)  

## Tabulation  
```cpp
#include <bits/stdc++.h>

using namespace std;


int maxProfit(vector<int>& Arr, int n)
{
    // Creating a 3d - dp of size [n+1][2][3] initialized to 0
    vector<vector<vector<int>>> dp(n+1,
                                    vector<vector<int>> 
                                            (2,vector<int>(3,0)));
                                            
    // As dp array is intialized to 0, we have already covered the base case
    
    for(int ind = n-1; ind>=0; ind--){
        for(int buy = 0; buy<=1; buy++){
            for(int cap=1; cap<=2; cap++){
                
                if(buy==0){// We can buy the stock
                    dp[ind][buy][cap] = max(0+dp[ind+1][0][cap], 
                                -Arr[ind] + dp[ind+1][1][cap]);
                 }
    
                if(buy==1){// We can sell the stock
                    dp[ind][buy][cap] = max(0+dp[ind+1][1][cap],
                                Arr[ind] + dp[ind+1][0][cap-1]);
                }
            }
        }
    }
    
    
    return dp[0][0][2];
   
}

int main() {

  vector<int> prices = {3,3,5,0,0,3,1,4};
  int n = prices.size();
                                 
  cout<<"The maximum profit that can be generated is "<<maxProfit(prices, n);
}
```
TC, SC - O(2 * 3 * N)  

## Space optimised  
```cpp
#include <bits/stdc++.h>

using namespace std;


int maxProfit(vector<int>& Arr, int n)
{
    
    vector<vector<int>> ahead(2,vector<int> (3,0));
    
    vector<vector<int>> cur(2,vector<int> (3,0));
    
    
    for(int ind = n-1; ind>=0; ind--){
        for(int buy = 0; buy<=1; buy++){
            for(int cap=1; cap<=2; cap++){
                
                if(buy==0){// We can buy the stock
                    cur[buy][cap] = max(0+ahead[0][cap], 
                                -Arr[ind] + ahead[1][cap]);
                 }
    
                if(buy==1){// We can sell the stock
                    cur[buy][cap] = max(0+ahead[1][cap],
                                Arr[ind] + ahead[0][cap-1]);
                }
            }
        }
        ahead = cur;
    }
    
    return ahead[0][2];
   
}

int main() {

  vector<int> prices = {3,3,5,0,0,3,1,4};
  int n = prices.size();
                                 
  cout<<"The maximum profit that can be generated is "<<maxProfit(prices, n);
}
```
SC - O(1)

```cpp
int maxtwobuysell(int arr[],int size) {
    int first_buy = INT_MIN;
      int first_sell = 0;
      int second_buy = INT_MIN;
      int second_sell = 0;
       
      for(int i=0;i<size;i++) {
         
          first_buy = max(first_buy,-arr[i]);//we set prices to negative, so the calculation of profit will be convenient
          first_sell = max(first_sell,first_buy+arr[i]);
          second_buy = max(second_buy,first_sell-arr[i]);//we can buy the second only after first is sold
          second_sell = max(second_sell,second_buy+arr[i]);
       
    }
     return second_sell;
}
```
