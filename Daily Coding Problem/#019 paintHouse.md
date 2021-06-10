# Paint House II

## Problem Statement

A builder is looking to build a row of N houses that can be of K different colors. He has a goal of minimizing cost while ensuring that no two neighboring houses are of the same 
color.Given an N by K matrix where the nth row and kth column represents the cost to build the nth house with kth color, return the minimum cost which achieves this goal.

## Solution

### Intuition

Use a 2D DP. Suppose if we have the cost for coloring first i houses, if we have to color i+1'th house. We store values of all possible colorings of house i+1 and total cost for 
coloring house i+1 with color j provided we already colored first i houses. I understand that you understood nothing. Let's go through this simpe example.

Given values of coloring n houses with k different colors.

| color1  | color2 | color3 |
| ------------- | ------------- | ------------- |
| 14  | 2  | 11 |
| 3  | 11  | 8 |
| 14  | 3  | 10 |

Each time, we just need a single row to be stores in our dp, so we store the previous row in 1d dp instead of using 2d dp.
Possibities for coloring first house with all colors will be 

| 14  | 2  | 11 |
| ------------- | ------------- | ------------- |

For coloring second house with color1, we check in our dp which color has minimum cost excluding the current color,
So now our dp becomes

| 3+2  | 11+11  | 8+2 |
| ------------- | ------------- | ------------- |

dp[0] indicate coloring house 2 with color1 and coloring house 1 with color2 and so on. So, final cost after coloring 2 houses is

| 5  | 22  | 10 |
| ------------- | ------------- | ------------- |

For house 3 it becomes

| 14+10 = *24*  | 3+5 = *8*  | 10+5 = *15* |
| ------------- | ------------- | ------------- |

So, our final cost will be minimum of all of these i.e 8 and it is achieved by coloring first house with color2, 2nd with color 1 and 3rd with color 2 and thus no adjacent houses
have same color.

For this, we have to maintain 2 minimum values in the dp after each iteration(**think why ?**)

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)

int32_t main()
{
    fastio;
    ll n,k;
    cin >> n >> k;
    ll input[n+1][k+1];
    
    for(ll i=1;i<=n;i++)
        for(ll j=1;j<=k;j++) cin >> input[i][j];
        
    ll dp[k+1];
    ll ind1,ind2,min1=INT_MAX,min2=INT_MAX;
    
    for(ll i=1;i<=k;i++){
        dp[i] = input[1][i];
        if(dp[i] < min1) min2 = min1,ind2 = ind1,min1 = dp[i],ind1 = i;
        else if(dp[i] < min2 && i!=ind1) min2 = dp[i],ind2 = i;
    }
 
    for(ll i=2;i<=n;i++){
        
        for(ll j=1;j<=k;j++){
            if(j == ind1) dp[j] = min2 + input[i][j];
            else dp[j] = min1 + input[i][j];
        }
        
        min1 = INT_MAX, min2 = INT_MAX;
        
        for(ll j=1;j<=k;j++){
            if(dp[j] < min1) min2 = min1,ind2 = ind1,min1 = dp[j],ind1 = j;
            else if(dp[j] < min2 && j!=ind1) min2 = dp[j],ind2 = j;
        }
    }
    
    cout << min1 << '\n';
    return 0;
}    
```

