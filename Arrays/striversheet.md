# Arrays
## Striver Sheet  
**[Link](https://takeuforward.org/interviews/strivers-sde-sheet-top-coding-interview-problems/)**  

# 1) Set Matrix Zeros  
Given a matrix if an element in the matrix is 0 then you will have to set its entire column and row to 0 and then return the matrix.  
### Initial Approaches
Normal brute like exactly do what questions asks us to do.  Another approach would be to use 2 dummy arrays i.e if row[i] == 1 it means there is a 0 in ith row, and we need to make that entire row 0.  
### Optimised approach  
Instead of using 2 dummy arrays, change the array in place i.e if found a 0 in matrix[i][j], make a note of it in the first row or column like matrix[i][0] = 0 and matrix[0][j] = 0. The only problem would arise if we mark matrix[0][0] to 0. There is no way in which we can know whether it came off from the 1st row or 1st column. So we need to any of that manually by ignoring it in the normal process. So in this approach below, we ignore 1st column completely. And whenever we find a zero in the first column we store a variable flag.  
```cpp
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        if(!matrix.size()) return;
        bool iscol = false;
        for(int i=0;i<matrix.size();i++){
            if(matrix[i][0] == 0) iscol = true;
            for(int j=1;j<matrix[0].size();j++){
                if(matrix[i][j] == 0){
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }
        for(int i=0;i<matrix.size();i++){
            for(int j=0;j<matrix[0].size();j++){
                cout << matrix[i][j] << " " ;
            }
            cout << endl;
        }
        for(int i = matrix.size()-1;i>=0;i--){
            for(int j = matrix[0].size()-1;j>=1;j--){
                if(matrix[i][0] == 0 || matrix[0][j] == 0) matrix[i][j] = 0;
            }
        }
        if(iscol){
            for(int i=0;i<matrix.size();i++) matrix[i][0] = 0;
        }
    }
};
```
TC - O(2NM), SC - O(1)  

# 2) Pascal's triangle  
Given an integer N, return the first N rows of Pascal’s triangle.  
In Pascal’s triangle, each number is the sum of the two numbers directly above it as shown in the figure below:  
![image](https://user-images.githubusercontent.com/56584349/178724838-1934d95c-e0c3-4319-a28b-4aae9c3fb88f.png)  
### Approach  
```cpp
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ans(numRows);
        for(int i=0;i<numRows;i++){
            ans[i].resize(i+1);
            ans[i][0] = ans[i][i] = 1;
            for(int j=1;j<i;j++) ans[i][j] = ans[i-1][j-1] + ans[i-1][j];
        }
        return ans;
    }
};
```
TC, SC - O(numRows * numRows)  

# 3) Next Permutation  
Given an array Arr[] of integers, rearrange the numbers of the given array into the lexicographically next greater permutation of numbers.  
If such an arrangement is not possible, it must rearrange it as the lowest possible order (i.e., sorted in ascending order).  
### Brute would take a lot of time by finding all possible permutations.  
Can also choose to use c++'s built in function - **next_permutation(arr,arr+n)**;  
### Optimal approach.  
From the right side, find the first element such that nums[i] < nums[i+1]. It implies we don't need to change the left of such index. Only to the right of it will be changed. And that too that ith index element woould become the next immediate element that is just greater than nums[i]. And the rest will be in the ascending order.  
```cpp
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int k = -1, n = nums.size();
        for(int i=n-2;i>=0;i--){
            if(nums[i] < nums[i+1]){
                k = i;
                break;
            }
        }
        if(k==-1) reverse(nums.begin(),nums.end());
        else{
            for(int j=n-1;j<=k+1;j--){
                if(nums[j] > nums[k]){
                    swap(nums[j], nums[k]);
                    reverse(nums.begin()+k+1,nums.end());
                        break;
                }
            }
        }
    }
};
```
TC - O(N), SC - O(1)  

# 4)Maximum subarray Sum in an array  
Given an integer array arr, find the contiguous subarray (containing at least one number) which
has the largest sum and return its sum and print the subarray.  
### Naive  
Use 2 for loops and check for all subarrays.  
### Optimal  
A cool intro to dp where dp[i] indicate MSA upto ith index including element from ith index.  Can space optimise this dp solution just by storing in prev variable.  
```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int start = 0, end = 0, msa = nums[0], prev = nums[0];
        for(int i=1;i<nums.size();i++){
            int temp = nums[i] + max(0, prev);
            if(temp > msa){
                if(prev > 0) end = i;
                else start = end = i;
                msa = temp;
            }
            prev = temp;
        }
        //the elements are from index start to end.
        return msa;
    }
};
```
TC - O(N), SC - O(1)  
### Subtle divide and conquer  
```java
class Solution {
public int maxSubArray(int[] nums) {

    // use divide and conquer: store current max sum of left-attached
    // subarray, max sum of right-attached subarray, max sum, and sum
    // Time: O(n) because f(n) = 2 * f(n/2) + O(1) => f(n)=O(n)
    // Space: O(lgn) because the runtime stack is of maximum depth O(lgn)
    
    
    int n = nums.length;
    if (n == 0)
        return 0;
    
    return helper(0, n - 1, nums)[2];
    
}

private int[] helper(int left, int right, int[] nums) {
    // return values: leftMax, rightMax, max, sum
    
    if (left == right)
        return new int[]{nums[left], nums[right], nums[left], nums[left]};
    
    int mid = (left + right) / 2;
    int[] leftSums = helper(left, mid, nums),
          rightSums = helper(mid + 1, right, nums);
    
    return new int[]{Math.max(leftSums[0], leftSums[3] + rightSums[0]),
                     Math.max(rightSums[1], rightSums[3] + leftSums[1]),
                     Math.max(leftSums[1] + rightSums[0], 
                              Math.max(leftSums[2], rightSums[2])),
                     leftSums[3] + rightSums[3]};
    
}
```
TC - O(N) as T(N) = 2 * T(N/2) + O(1).  
SC - stack space  

# 5)Sort an array of 0's, 1's and 2's.  
Given an array consisting of only 0s, 1s and 2s. Write a program to in-place sort the array without using inbuilt sort functions. ( Expected: Single pass-O(N) and constant space)  
```cpp
void sortColors(int A[], int n) {
    int n0 = -1, n1 = -1, n2 = -1;
    for (int i = 0; i < n; ++i) {
        if (A[i] == 0) 
        {
            A[++n2] = 2; A[++n1] = 1; A[++n0] = 0;
        }
        else if (A[i] == 1) 
        {
            A[++n2] = 2; A[++n1] = 1;
        }
        else if (A[i] == 2) 
        {
            A[++n2] = 2;
        }
    }
}
```
```cpp
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int zero = 0, second = nums.size()-1, ind = 0;
        while(ind <= second){
            if(nums[ind] == 0) swap(nums[ind++],nums[zero++]);
            else if(nums[ind] == 2) swap(nums[ind],nums[second--]);
            else ind++;
        }
    }
};
```
TC - O(N), SC - O(1)  

# 6) Stock Buy and Sell  
You are given an array of prices where prices[i] is the price of a given stock on an ith day.  
You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock. Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.  
### Approach  
Bruteforce - 2 loops - O(n^2)  
### Optimal  
At ith day, calculate the profit if the stock was sold on that day. Meanwhile keep track of the minimal rate at which we can buy so far.  
```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minimal = prices[0], ans = -1;
        for(int i = 1;i<prices.size();i++){
            ans = max(ans, prices[i] - minimal);
            minimal = min(minimal, prices[i]);
        }
        return ans<=0?0:ans;
    }
};
```
TC - O(N), SC - O(1)  

# 7) Rotate Matrix  
