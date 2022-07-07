# Grid Unique Paths  

Given two values M and N, which represent a matrix[M][N]. We need to find the total unique paths from the top-left cell (matrix[0][0]) to the rightmost cell
(matrix[M-1][N-1]).  
At any cell we are allowed to move in only two directions:- bottom and right.  

**[Problem link](https://takeuforward.org/data-structure/grid-unique-paths-dp-on-grids-dp8/)**  

## Solution  
**step-1 express problem in terms of indices.**  
f(i,j) - total number of unique paths from matrix corresponding from [0,0] to [i,j].  And also base cases are when i=0 & j=0, i<0 | j<0.  
**step-2 try all possible choices at given index.**  
All we can do is move up or move left. If up i-1 or if left j-1.  
![image](https://user-images.githubusercontent.com/56584349/177739534-9e90c65f-3dca-413a-8893-2ddb8d2ce2a7.png)  
**step-3 find the answer from the choices.**  
simply add them up.  

## Memoization  

```cpp
#include <bits/stdc++.h>

using namespace std;

int countWaysUtil(int i, int j, vector<vector<int> > &dp) {
  if(i==0 && j == 0)
    return 1;
  if(i<0 || j<0)
    return 0;
  if(dp[i][j]!=-1) return dp[i][j];
    
  int up = countWaysUtil(i-1,j,dp);
  int left = countWaysUtil(i,j-1,dp);
  
  return dp[i][j] = up+left;
  
}

int countWays(int m, int n){
    vector<vector<int> > dp(m,vector<int>(n,-1));
    return countWaysUtil(m-1,n-1,dp);
    
}

int main() {

  int m=3;
  int n=2;
  
  cout<<countWays(m,n);
}
```
TC - O(MN)  
Space Complexity: O((N-1)+(M-1)) + O(MN)  
Reason: We are using a recursion stack space:O((N-1)+(M-1)), here (N-1)+(M-1) is the path length and an external DP Array of size ‘MN’.  

## Tabulation  

```cpp
//base conditions - dp[0][0] = 1;
#include <bits/stdc++.h>
using namespace std;

int countWaysUtil(int m, int n, vector<vector<int> > &dp) {
  for(int i=0; i<m ;i++){
      for(int j=0; j<n; j++){
          //base condition
          if(i==0 && j==0){
              dp[i][j]=1;
              continue;
          }
          
          int up=0;
          int left = 0;
          
          if(i>0) 
            up = dp[i-1][j];
          if(j>0)
            left = dp[i][j-1];
            
          dp[i][j] = up+left;
      }
  }
  return dp[m-1][n-1]; 
}

int countWays(int m, int n){
    vector<vector<int> > dp(m,vector<int>(n,-1));
    return countWaysUtil(m,n,dp);
}

int main() {
  int m=3;
  int n=2;
  cout<<countWays(m,n);
}
```

TC,SC - O(MN)  

## Space Optimised  

```cpp
#include <bits/stdc++.h>

using namespace std;

int countWays(int m, int n){
    vector<int> prev(n,0);
    for(int i=0; i<m; i++){
        vector<int> temp(n,0);
        for(int j=0; j<n; j++){
            if(i==0 && j==0){
                temp[j]=1;
                continue;
            }
            
            int up=0;
            int left =0;
            
            if(i>0)
                up = prev[j];
            if(j>0)
                left = temp[j-1];
                
            temp[j] = up + left;
        }
        prev = temp;
    }
    
    return prev[n-1];
    
}

int main() {

  int m=3;
  int n=2;
  
  cout<<countWays(m,n);
}
```
