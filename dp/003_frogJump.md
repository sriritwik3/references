# Frog Jump  

There is a frog on the 1st step of an N stairs long staircase.
The frog wants to reach the Nth stair. HEIGHT[i] is the height of the (i+1)th stair.If Frog jumps from ith to jth stair,
the energy lost in the jump is given by |HEIGHT[i-1] - HEIGHT[j-1] |.In the Frog is on ith staircase, he can jump either to (i+1)th stair or to (i+2)th stair.
Your task is to find the minimum total energy used by the frog to reach from 1st stair to Nth stair.  

## Solution 

Greedy solution won't work because initially, even if we take the effective and cheapest path we eventually might end up taking costlier paths.  
**step-1  express the problem in terms of indices**.  
f(n-1) indicate minimum energy required from stair 0 to stair n-1. f(0) is 0 - base case.  
**step-2 try all choices to reach the goal**.  
frog can jump either one step or 2 steps. cost will be taken from the height array and the rest will be calculated recursively.  
![image](https://user-images.githubusercontent.com/56584349/177547577-3406361f-7311-4843-a255-1ca2a66f37af.png)  
**step-3 take minimum of all the choices**.  
take the minimum of those and also handle edge cases.  
![image](https://user-images.githubusercontent.com/56584349/177547822-937ff6e2-c52a-4ace-bce2-d820b08a7309.png)

Now, when we're clear with recurrence relations move on to dynamic programming.  

# Memoization
create a dp array and initialise to -1. if dp[i] already exists, return it. else set it to the computed value and return it.  

## Memoization Code

```cpp
#include <bits/stdc++.h>

using namespace std;

int solve(int ind, vector<int>& height, vector<int>& dp){
    if(ind==0) return 0;
    if(dp[ind]!=-1) return dp[ind];
    int jumpTwo = INT_MAX;
    int jumpOne= solve(ind-1, height,dp)+ abs(height[ind]-height[ind-1]);
    if(ind>1)
        jumpTwo = solve(ind-2, height,dp)+ abs(height[ind]-height[ind-2]);
    
    return dp[ind]=min(jumpOne, jumpTwo);
}


int main() {

  vector<int> height{30,10,60 , 10 , 60 , 50};
  int n=height.size();
  vector<int> dp(n,-1);
  cout<<solve(n-1,height,dp);
}
```

TC - O(N), SC - O(N) STACK SPACE + O(N) ARRAY  

# Tabulation  
initialise the dp with base conditions, here dp[0] = 0 and then try to calculate iteratively.  

## Tabulation Code 

```cpp
#include <bits/stdc++.h>

using namespace std;


int main() {

  vector<int> height{30,10,60,10,60,50};
  int n=height.size();
  vector<int> dp(n,-1);
  dp[0]=0;
  for(int ind=1;ind<n;ind++){
      int jumpTwo = INT_MAX;
        int jumpOne= dp[ind-1] + abs(height[ind]-height[ind-1]);
        if(ind>1)
            jumpTwo = dp[ind-2] + abs(height[ind]-height[ind-2]);
    
        dp[ind]=min(jumpOne, jumpTwo);
  }
  cout<<dp[n-1];
}
```

TC - O(N), SC - O(N) for array

## Space Optimised

If we carefully observe, we only need to store the last 2 previously computed sub problem's result instead of storing every problem's result. So further optimising the space to constant space.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<int> height{30,10,60,10,60,50};
  int n=height.size();
  int prev=0;
  int prev2=0;
  for(int i=1;i<n;i++){
      
      int jumpTwo = INT_MAX;
      int jumpOne= prev + abs(height[i]-height[i-1]);
      if(i>1)
        jumpTwo = prev2 + abs(height[i]-height[i-2]);
    
      int cur_i=min(jumpOne, jumpTwo);
      prev2=prev;
      prev=cur_i;
        
  }
  cout<<prev;
}
```

SC - O(1), TC - O(N)
