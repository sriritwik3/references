# Minimum Path Sum in a Traingular grid

**[link](https://takeuforward.org/data-structure/minimum-path-sum-in-triangular-grid-dp-11/)**  

We are given a Triangular matrix. We need to find the minimum path sum from the first row to the last row.
At every cell we can move in only two directions: either to the bottom cell (↓) or to the bottom-right cell  
![image](https://user-images.githubusercontent.com/56584349/177761355-e7fe8594-7e22-4c9d-985d-888c42f04c4d.png)  

## Memoization  

```cpp
#include <bits/stdc++.h>

using namespace std;

int minimumPathSumUtil(int i, int j, vector<vector<int> > &triangle,int n, 
vector<vector<int> > &dp) {
  
  if(dp[i][j]!=-1)
  return dp[i][j];
  
  if(i==n-1) return triangle[i][j];
    
  int down = triangle[i][j]+minimumPathSumUtil(i+1,j,triangle,n,dp);
  int diagonal = triangle[i][j]+minimumPathSumUtil(i+1,j+1,triangle,n,dp);
  
  return dp[i][j] = min(down, diagonal);
  
}

int minimumPathSum(vector<vector<int> > &triangle, int n){
    vector<vector<int> > dp(n,vector<int>(n,-1));
    return minimumPathSumUtil(0,0,triangle,n,dp);
    
}

int main() {

  vector<vector<int> > triangle{{1},
                                {2,3},
                                {3,6,7},
                                {8,9,6,10}};
                            
  int n = triangle.size();
  
  cout<<minimumPathSum(triangle,n);
}
```
TC - O(N * N), SC - O(N) stack space + O(n^2)

## Tabulation  

```cpp
#include <bits/stdc++.h>

using namespace std;

int minimumPathSum(vector<vector<int> > &triangle, int n){
    vector<vector<int> > dp(n,vector<int>(n,0));
    
    for(int j=0;j<n;j++){
        dp[n-1][j] = triangle[n-1][j];
    }
    
    for(int i=n-2; i>=0; i--){
        for(int j=i; j>=0; j--){
            
            int down = triangle[i][j]+dp[i+1][j];
            int diagonal = triangle[i][j]+dp[i+1][j+1];
            
            dp[i][j] = min(down, diagonal);
        }
    }
    
    return dp[0][0];
    
}

int main() {

  vector<vector<int> > triangle{{1},
                                {2,3},
                                {3,6,7},
                                {8,9,6,10}};
                            
  int n = triangle.size();
  
  cout<<minimumPathSum(triangle,n);
}
```
TC,SC - O(N^2)

## Space Optimised  

```cpp
#include <bits/stdc++.h>

using namespace std;

int minimumPathSum(vector<vector<int> > &triangle, int n){
    vector<int> front(n,0), cur(n,0);
    
    for(int j=0;j<n;j++){
        front[j] = triangle[n-1][j];
    }
    
    for(int i=n-2; i>=0; i--){
        for(int j=i; j>=0; j--){
            
            int down = triangle[i][j]+front[j];
            int diagonal = triangle[i][j]+front[j+1];
            
            cur[j] = min(down, diagonal);
        }
        front=cur;
    }
    
    return front[0];
    
}

int main() {

  vector<vector<int> > triangle{{1},
                                {2,3},
                                {3,6,7},
                                {8,9,6,10}};
                            
  int n = triangle.size();
  
  cout<<minimumPathSum(triangle,n);
}
```

TC - O(N^2), SC - O(N)
