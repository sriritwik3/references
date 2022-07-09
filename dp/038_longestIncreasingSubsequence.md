# Longest Increasing Subsequence  
**[https://www.geeksforgeeks.org/longest-increasing-subsequence-dp-3/]**  

The Longest Increasing Subsequence (LIS) problem is to find the length of the longest subsequence of a given sequence such that all
elements of the subsequence are sorted in increasing order. For example, the length of LIS for {10, 22, 9, 33, 21, 50, 41, 60, 80} is 6
and LIS is {10, 22, 33, 50, 60, 80}.   

## Solution  
lis_ending_here(arr, i) = 1 + lis_ending_here(arr, j) --> j < i and arr[j] < arr[i].  
![image](https://user-images.githubusercontent.com/56584349/178102643-6aad5e81-1065-4774-af95-70e6d06f95da.png)  

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int lis(int arr[], int n) {
  int lis[n];

  lis[0] = 1;

  /* Compute optimized LIS values in
     bottom up manner */
  for (int i = 1; i < n; i++) {
    lis[i] = 1;
    for (int j = 0; j < i; j++)
      if (arr[i] > arr[j] && lis[i] < lis[j] + 1)
        lis[i] = lis[j] + 1;
  }

  // Return maximum value in lis[]
  return *max_element(lis, lis + n);
}
int main() {
	// Your code goes here;
	int arr[] = {10, 22, 9, 33, 21, 50, 41, 60, 80};
	int n = 9;
	cout << lis(arr, n);
	return 0;
}
```
TC - O(n^2), SC - O(n)  

### Another approach is to sort the array s1 and call it s2. Now find longest common subsequence in s1 and s2.  

## Greedy with Binary search approach  
- Let's construct the idea from following example.
- Consider the example nums = [2, 6, 8, 3, 4, 5, 1], let's try to build the increasing subsequences starting with an empty one: sub1 = [].
1. Let pick the first element, sub1 = [2].
2. 6 is greater than previous number, sub1 = [2, 6]
3. 8 is greater than previous number, sub1 = [2, 6, 8]
4. 3 is less than previous number, we can't extend the subsequence sub1, but we must keep 3 because in the future there may have the longest subsequence start with [2, 3], sub1 = [2, 6, 8], sub2 = [2, 3].
5. With 4, we can't extend sub1, but we can extend sub2, so sub1 = [2, 6, 8], sub2 = [2, 3, 4].
6. With 5, we can't extend sub1, but we can extend sub2, so sub1 = [2, 6, 8], sub2 = [2, 3, 4, 5].
7. With 1, we can't extend neighter sub1 nor sub2, but we need to keep 1, so sub1 = [2, 6, 8], sub2 = [2, 3, 4, 5], sub3 = [1].
8. Finally, length of longest increase subsequence = len(sub2) = 4.  
- In the above steps, we need to keep different sub arrays (sub1, sub2..., subk) which causes poor performance. But we notice that we can just keep one sub array, when new number x is not greater than the last element of the subsequence sub, we do binary search to find the smallest element >= x in sub, and replace with number x.
- Let's run that example nums = [2, 6, 8, 3, 4, 5, 1] again:
1. Let pick the first element, sub = [2].
2. 6 is greater than previous number, sub = [2, 6]
3. 8 is greater than previous number, sub = [2, 6, 8]
4. 3 is less than previous number, so we can't extend the subsequence sub. We need to find the smallest number >= 3 in sub, it's 6. Then we overwrite it, now sub = [2, 3, 8].
5. 4 is less than previous number, so we can't extend the subsequence sub. We overwrite 8 by 4, so sub = [2, 3, 4].
6. 5 is greater than previous number, sub = [2, 3, 4, 5].
7. 1 is less than previous number, so we can't extend the subsequence sub. We overwrite 2 by 1, so sub = [1, 3, 4, 5]. 

```cpp
class Solution { // 8 ms, faster than 91.61%
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> sub;
        for (int x : nums) {
            if (sub.empty() || sub[sub.size() - 1] < x) {
                sub.push_back(x);
            } else {
                auto it = lower_bound(sub.begin(), sub.end(), x); // Find the index of the smallest number >= x
                *it = x; // Replace that number with x
            }
        }
        return sub.size();
    }
};
```
TC - O(NLOGN), SC-  O(N), can  make it O(1) by overwriting the original num array.  
