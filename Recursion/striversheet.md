# Recursion   
## Striver Sheet  

# 1) Subset Sum : sum of all subsets  
Given an array print all the sum of the subset generated from it, in the increasing order.  
For any element there can be 2 possibilities that it can be picked or not picked.  So here goes a tree by which we can think of recursion.  
```cpp
class Solution {
  public:
    void solve(int ind, vector < int > & arr, int n, vector < int > & ans, int sum) {
      if (ind == n) {
        ans.push_back(sum);
        return;
      }
      //element is picked
      solve(ind + 1, arr, n, ans, sum + arr[ind]);
      //element is not picked
      solve(ind + 1, arr, n, ans, sum);
    }
  vector < int > subsetSums(vector < int > arr, int n) {
    vector < int > ans;
    solve(0, arr, n, ans, 0);
    return ans;
  }
};
```
Atlast you need to sort the array.  
Time Complexity: O(2^n)+O(2^n log(2^n)). Each index has two ways. You can either pick it up or not pick it. So for n index time complexity for O(2^n) and for sorting it will take (2^n log(2^n)).  
SC - O(2^N)   

# 2) Subset II | Print all the unique subsets  
Given an array of integers that may contain duplicates the task is to return all possible subsets. Return only unique subsets and they can be in any order.  
### Approach 1  
Use a similar recursive approach where we have 2 options include/not incldue for an element and then use a set to avoid duplicates.  
Time Complexity: O( 2^n * (k log (x) )). 2^n  for generating every subset and k* log( x)  to insert every combination of average length k in a set of size x. After this, we have to convert the set of combinations back into a list of list /vector of vectors which takes more time.  
Space Complexity:  O(2^n * k) to store every subset of average length k. Since we are initially using a set to store the answer another O(2^n * k) is also used.
### Approach 2  
sort the array and then do recursion.  
```cpp
class Solution {
public:
    vector<vector<int>> subsets;
    vector<int> subset;

    void generate(int i, vector<int>& nums){
        if(i == nums.size()){
            subsets.push_back(subset);
            return; 
        }
        //1. I choose the current number
        subset.push_back(nums[i]);
        generate(i+1,nums);
        subset.pop_back(); //backtracking
        //2. I dont choose the current number [hence I go to the next different number]
        int nextIdx = upper_bound(nums.begin(), nums.end(), nums[i]) - nums.begin();      
        generate(nextIdx, nums);
        return; 
    }


    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
       sort(nums.begin(), nums.end()); 
       generate(0,nums);
       return subsets;
    }
};
```
### Bitmasking with hashing approach  
```cpp
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        unordered_set<string> seen;
        for (int mask = 0, size = 1 << n; mask < size; ++mask) {
            vector<int> subset;
            string hashcode = "";
            for (int i = 0; i < n; i++) {
                int bit = (mask >> i) & 1; // Get i_th bit of mask
                if (bit == 1) {
                    subset.push_back(nums[i]);
                    hashcode += to_string(nums[i]) + ",";
                }
            }
            if (!seen.count(hashcode)) {
                ans.push_back(subset);
                seen.insert(hashcode);
            }
        }
        return ans;
    }
};
```
Time: O(2^N * N), Space: O(2^N)  

# 3) Combination Sum I  
Given an array of distinct integers and a target, you have to return the list of all unique combinations where the chosen numbers sum to target. You may return the combinations in any order.  
The same number may be chosen from the given array an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.  

It is guaranteed that the number of unique combinations that sum up to target is less than 150 combinations for the given input.  
```cpp
class Solution {
  public:
    void findCombination(int ind, int target, vector < int > & arr, vector < vector < int >> & ans, vector < int > & ds) {
      if (ind == arr.size()) {
        if (target == 0) {
          ans.push_back(ds);
        }
        return;
      }
      // pick up the element 
      if (arr[ind] <= target) {
        ds.push_back(arr[ind]);
        findCombination(ind, target - arr[ind], arr, ans, ds);
        ds.pop_back();
      }
      findCombination(ind + 1, target, arr, ans, ds);

    }
  public:
    vector < vector < int >> combinationSum(vector < int > & candidates, int target) {
      vector < vector < int >> ans;
      vector < int > ds;
      findCombination(0, target, candidates, ans, ds);
      return ans;
    }
};
```
```cpp
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> temp;
        sort(candidates.begin(),candidates.end());
        dfs(candidates,target,temp,result,0);
        return result;
    }
    
    void dfs(vector<int> candidates,int target,vector<int> &temp,vector<vector<int>>  &result,int start){
        if(target < 0) return;
        else if(target==0){
            result.push_back(temp);
            return;
        }
        for(int i=start;i<candidates.size() && target >= candidates[i];i++){
            temp.push_back(candidates[i]);
            dfs(candidates,target-candidates[i],temp,result,i);
            temp.pop_back();
        }
    }
};
```
Time Complexity: O(2^t * k) where t is the target, k is the average length  
Reason: Assume if you were not allowed to pick a single element multiple times, every element will have a couple of options: pick or not pick which is 2^n different recursion calls, also assuming that the average length of every combination generated is k. (to put length k data structure into another data structure)  
Why not (2^n) but (2^t) (where n is the size of an array)?  
Assume that there is 1 and the target you want to reach is 10 so 10 times you can “pick or not pick” an element.  
Space Complexity: O(k * x), k is the average length and x is the no. of combinations  

# 4) Combination Sum II  
Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sum to target. Each number in candidates may only be used once in the combination.  

Note: The solution set must not contain duplicate combinations.  
Duplicate combinations in sense if there are three 1's in the array and two 6s. we can take the combination [1,1,6] once but we cannot take the same [1,1,6] with different
indices contributing it to it again.  

```python3
class Solution:
    def combinationSum2(self, candidates: List[int], target: int) -> List[List[int]]:
        result = []
        
        self.dfs(sorted(candidates),target,[],result)
        return result
    
    def dfs(self,cds,target,temp,res):
        if target < 0:
            return
        elif target == 0:
            if temp not in res:
                res.append(temp)
            return
        else:
            for i in range(len(cds)):
                if cds[i] > target:
                    break   
                self.dfs(cds[i+1:],target-cds[i],temp+[cds[i]],res)
                
```
Let's take an example [1,1,2] the below example for the first 1 will do take care of all cases like 1, 1 1, 1 1 2. But whenever we choose to don't pick the first 1 and 
go to second 1. We simply ignore it considering the fact that all the cases will be covered in the case of the first 1 being picked.  
Whenever we use for loop inside a recursion and popping the inserted element after the recursive call implies that we are actually doing the traditional pick/non pick 
approach here. If a recursive call is made it indicated the current element is picked. And after the call we're poppinig that element to take care of the case when element 
is not picked and we simply move on to next index in the for loop.  
```cpp
void findCombination(int ind, int target, vector < int > & arr, vector < vector < int >> & ans, vector < int > & ds) {
  if (target == 0) {
    ans.push_back(ds);
    return;
  }
  for (int i = ind; i < arr.size(); i++) {
    if (i > ind && arr[i] == arr[i - 1]) continue;
    if (arr[i] > target) break;
    ds.push_back(arr[i]);
    findCombination(i + 1, target - arr[i], arr, ans, ds);
    ds.pop_back();
  }
}
vector < vector < int >> combinationSum2(vector < int > & candidates, int target) {
  sort(candidates.begin(), candidates.end());
  vector < vector < int >> ans;
  vector < int > ds;
  findCombination(0, target, candidates, ans, ds);
  return ans;
}
```  
Time Complexity:O(2^n * k)  
Reason: Assume if all the elements in the array are unique then the no. of subsequence you will get will be O(2^n). we also add the ds to our ans when we reach the base case that will take “k”//average space for the ds.  
Space Complexity:O(k * x)  
Reason: if we have x combinations then space will be x * k where k is the average length of the combination.  

# 5) Palindrome Partitioning  
You are given a string s, partition it in such a way that every substring is a palindrome. Return all such palindromic partitions of s.  
Note: A palindrome string is a string that reads the same backward as forward.  
```cpp
class Solution {
private: 
    bool isPalindrome(string s){
        for(int i=0;i<s.size()/2;i++){
            if(s[i] != s[s.size()-1-i]) return false;
        }
        return true;
    }
    
    void recurse(string s,int start, vector<string> &tempList, vector<vector<string>> &store){
        if(start == s.size())
            store.push_back(tempList);
        for(int end = start;end < s.size();end++){
            if(isPalindrome(s.substr(start,end-start+1))){
                tempList.push_back(s.substr(start,end-start+1));
                recurse(s,end+1,tempList,store);
                tempList.pop_back();
            }
        }
    }
    
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> store;
        vector<string> temp;
        recurse(s,0,temp,store);
        return store;
    }
};
```
Time Complexity: O( (2^n) * k * (n/2) )  
Reason: O(2^n) to generate every substring and O(n/2)  to check if the substring generated is a palindrome. O(k) is for inserting the palindromes in another data structure, where k  is the average length of the palindrome list.  
Space Complexity: O(k * x)  
Reason: The space complexity can vary depending upon the length of the answer. k is the average length of the list of palindromes and if we have x such list of palindromes in our final answer. The depth of the recursion tree is n, so the auxiliary space required is equal to the O(n).  

We could actually improve this by storing a 2d dp array to check whether string from index i to j is a palindrome in dp[i][j].  

# 6) K-th Permutation Sequence  
Given N and K, where N is the sequence of numbers from 1 to N([1,2,3….. N]) find the Kth permutation sequence.  



