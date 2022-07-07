# Partition into 2 subsets with minimum absolute differene  
**[Link](https://takeuforward.org/data-structure/partition-set-into-2-subsets-with-min-absolute-sum-diff-dp-16/)**  
We are given an array ‘ARR’ with N positive integers. We need to partition the array into two subsets such that the absolute difference of the
sum of elements of the subsets is minimum.  
We need to return only the minimum absolute difference of the sum of elements of the two partitions.  

## Solution  
Create a dp array of size [n][totSum+1]. The size of the input array is ‘n’, so the index will always lie between ‘0’ and ‘n-1’.
The target can take any value between ‘0’ and ‘totSum’. Therefore we take the dp array as dp[n][totSum+1]

## Memoization  
```cpp
#include <bits/stdc++.h>
using namespace std;

bool subsetSumUtil(int ind, int target, vector < int > & arr, vector < vector 
< int >> & dp) {
  if (target == 0)
    return dp[ind][target]=true;
  if (ind == 0)
    return dp[ind][target] = arr[0] == target;
  if (dp[ind][target] != -1)
    return dp[ind][target];
  bool notTaken = subsetSumUtil(ind - 1, target, arr, dp);
  bool taken = false;
  if (arr[ind] <= target)
    taken = subsetSumUtil(ind - 1, target - arr[ind], arr, dp);
  return dp[ind][target] = notTaken || taken;
}

int minSubsetSumDifference(vector < int > & arr, int n) {
  int totSum = 0;
  for (int i = 0; i < n; i++) {
    totSum += arr[i];
  }
  vector < vector < int >> dp(n, vector < int > (totSum + 1, -1));
  for (int i = 0; i <= totSum; i++) {
    bool dummy = subsetSumUtil(n - 1, i, arr, dp);
  }
  int mini = 1e9;
  for (int i = 0; i <= totSum; i++) {
    if (dp[n - 1][i] == true) {
      int diff = abs(i - (totSum - i));
      mini = min(mini, diff);
    }
  }
  return mini;
}

int main() {
  vector < int > arr = {1,2,3,4};
  int n = arr.size();
  cout << "The minimum absolute difference is: " << minSubsetSumDifference(arr, n);

}
```
Time Complexity: O(N * totSum) +O(N) +O(N)  
Reason: There are two nested loops that account for O(N * totSum), at starting we are running a for loop to calculate totSum and at last a for loop to traverse the last row.  
Space Complexity: O(N * totSum) + O(N)  
Reason: We are using an external array of size ‘N * totSum’ and a stack space of O(N).  

## Tabulation 
```cpp
#include <bits/stdc++.h>
using namespace std;

int minSubsetSumDifference(vector < int > & arr, int n) {
  int totSum = 0;

  for (int i = 0; i < n; i++) {
    totSum += arr[i];
  }

  vector < vector < bool >> dp(n, vector < bool > (totSum + 1, false));

  for (int i = 0; i < n; i++) {
    dp[i][0] = true;
  }

  if (arr[0] <= totSum)
    dp[0][totSum] = true;

  for (int ind = 1; ind < n; ind++) {
    for (int target = 1; target <= totSum; target++) {

      bool notTaken = dp[ind - 1][target];

      bool taken = false;
      if (arr[ind] <= target)
        taken = dp[ind - 1][target - arr[ind]];

      dp[ind][target] = notTaken || taken;
    }
  }

  int mini = 1e9;
  for (int i = 0; i <= totSum; i++) {
    if (dp[n - 1][i] == true) {
      int diff = abs(i - (totSum - i));
      mini = min(mini, diff);
    }
  }
  return mini;
}

int main() {
  vector<int> arr = {1,2,3,4};
  int n = arr.size();
  cout << "The minimum absolute difference is: " << minSubsetSumDifference(arr, n);
}
```
TC - O(N * totSum) + O(N) + O(N), SC - O(N * totSum)  

## space optimised  
```cpp
#include <bits/stdc++.h>

using namespace std;

int minSubsetSumDifference(vector < int > & arr, int n) {
  int totSum = 0;

  for (int i = 0; i < n; i++) {
    totSum += arr[i];
  }

  vector < bool > prev(totSum + 1, false);

  prev[0] = true;

  if (arr[0] <= totSum)
    prev[arr[0]] = true;

  for (int ind = 1; ind < n; ind++) {
    vector < bool > cur(totSum + 1, false);
    cur[0] = true;
    for (int target = 1; target <= totSum; target++) {
      bool notTaken = prev[target];

      bool taken = false;
      if (arr[ind] <= target)
        taken = prev[target - arr[ind]];

      cur[target] = notTaken || taken;
    }
    prev = cur;
  }

  int mini = 1e9;
  for (int i = 0; i <= totSum; i++) {
    if (prev[i] == true) {
      int diff = abs(i - (totSum - i));
      mini = min(mini, diff);
    }
  }
  return mini;
}

int main() {

  vector<int> arr = {1,2,3,4};
  int n = arr.size();

  cout << "The minimum absolute difference is: " << minSubsetSumDifference(arr, n);
}
```
SC - O(totSum)  
