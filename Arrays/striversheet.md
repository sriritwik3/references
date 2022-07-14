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
Given a matrix, your task is to rotate the matrix 90 degrees clockwise.  
Eg : Input: [[1,2,3],[4,5,6],[7,8,9]]  
Output: [[7,4,1],[8,5,2],[9,6,3]]   
### Approach
Brute - take a dummy matrix. First row becomes last column, second row becomes second last column and so on. - TC,SC - O(N * N).  
### Optimal  
If we carefully observer, we can notice that first column becomes first row but in reverse. So we can transpose the matrix and reverse each row. To transpose we can iterate upto it's diagnol and swap matrix[i][j] and matrix[j][i].  
```cpp
void rotate(vector < vector < int >> & matrix) {
  int n = matrix.size();
  //transposing the matrix
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      swap(matrix[i][j], matrix[j][i]);
    }
  }
  //reversing each row of the matrix
  for (int i = 0; i < n; i++) {
    reverse(matrix[i].begin(), matrix[i].end());
  }
}
```
TC - O(2 * N * N), SC - O(1)  

# 8) Merge Overlapping sub intervals  
Given an array of intervals, merge all the overlapping intervals and return an array of non-overlapping intervals.  
### Approach  
Linearly iterate over the array if the data structure is empty insert the interval in the data structure. If the last element in the data structure overlaps with the current interval we merge the intervals by updating the last element in the data structure, and if the current interval does not overlap with the last element in the data structure simply insert it into the data structure.  
```cpp
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> ans;
        for(int i=0;i<intervals.size();i++){
            if(ans.empty() || ans.back()[1] < intervals[i][0])
                ans.push_back({intervals[i][0], intervals[i][1]});
            else   
                ans.back()[1] = max(ans.back()[1], intervals[i][1]);
        }
        return ans;
    }
};
```
TC - O(NLOGN) for sorting, SC - O(N)  

# 9) Merge two sorted arrays without extra space  
Given two sorted arrays arr1[] and arr2[] of sizes n and m in non-decreasing order. Merge them in sorted order. Modify arr1 so that it contains the first N elements and modify arr2 so that it contains the last M elements.  
### Approach  
- Use a for loop in arr1.
- Whenever we get any element in arr1 which is greater than the first element of arr2,swap it.
- Rearrange arr2.
- Repeat the process.  
```cpp
void merge(int arr1[], int arr2[], int n, int m) {
  // code here
  int i, k;
  for (i = 0; i < n; i++) {
    // take first element from arr1 
    // compare it with first element of second array
    // if condition match, then swap
    if (arr1[i] > arr2[0]) {
      int temp = arr1[i];
      arr1[i] = arr2[0];
      arr2[0] = temp;
    }

    // then sort the second array
    // put the element in its correct position
    // so that next cycle can swap elements correctly
    int first = arr2[0];
    // insertion sort is used here
    for (k = 1; k < m && arr2[k] < first; k++) {
      arr2[k - 1] = arr2[k];
    }
    arr2[k - 1] = first;
  }
}
```
TC - O(NM), SC - O(1)  
### Better Approach - Gap method  
- Initially take the gap as (m+n)/2;
- Take as a pointer1 = 0 and pointer2 = gap.
- Run a oop from pointer1 &  pointer2 to  m+n and whenever arr[pointer2]<arr[pointer1], just swap those.
- After completion of the loop reduce the gap as gap=gap/2.
- Repeat the process until gap>0.
```cpp
void merge(int ar1[], int ar2[], int n, int m) {
  // code here 
  int gap = ceil((float)(n + m) / 2);
  while (gap > 0) {
    int i = 0;
    int j = gap;
    while (j < (n + m)) {
      if (j < n && ar1[i] > ar1[j]) {
        swap(ar1[i], ar1[j]);
      } else if (j >= n && i < n && ar1[i] > ar2[j - n]) {
        swap(ar1[i], ar2[j - n]);
      } else if (j >= n && i >= n && ar2[i - n] > ar2[j - n]) {
        swap(ar2[i - n], ar2[j - n]);
      }
      j++;
      i++;
    }
    if (gap == 1) {
      gap = 0;
    } else {
      gap = ceil((float) gap / 2);
    }
  }
}
```
TC - O((m+n)log(m+n)), SC- O (1)  

# 10) Find the duplicate number  
Given an array of N + 1 size, where each element is between 1 and N. Assuming there is only one duplicate number, your task is to find the duplicate number.  
### XOR Approach  
This works only when a number is repeated only once.  
```cpp
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size() - 1;
        int xorx;
        switch(n%4){
            case 0: xorx = n; break;
            case 1: xorx = 1; break;
            case 2: xorx = n+1; break;
            case 3: xorx = 0; break;
                
        }
        cout << xorx;
        for(int i=0;i<nums.size();i++)
            xorx ^= nums[i];
        return xorx;
    }
};
```
### Negative marking approach  
```cpp
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int ans = -1;
        for(int i=0;i<nums.size();i++){
            if(nums[abs(nums[i])-1] < 0) return abs(nums[i]);
            else nums[abs(nums[i]) -1] *= -1;
        }
        return ans;
    }
};
```
### Linkedlist cycle detection approach  
```cpp
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = nums[0], fast = nums[0];
        do{
            slow = nums[slow];
            fast = nums[nums[fast]];
        }
        while(slow != fast); 
        fast = nums[0];
        while(slow != fast) slow = nums[slow], fast = nums[fast];
        return slow;
    }
};
```
All approaches - TC - O(N), SC - O(1)   

# 11) Repeat and Missing Number  
You are given a read-only array of N integers with values also in the range [1, N] both inclusive. Each integer appears exactly once except A which appears twice and B which is missing. The task is to find the repeating and missing numbers A and B where A repeats twice and B is missing.  
### formulae approach  
Using formula for sum of first N natural numbers,sum of squares of first N natural numbers.  
```cpp
vector<int>missing_repeated_number(const vector<int> &A) {
    long long int len = A.size();

    long long int S = (len * (len+1) ) /2;
    long long int P = (len * (len +1) *(2*len +1) )/6;
    long long int missingNumber=0, repeating=0;
     
    for(int i=0;i<A.size(); i++){
       S -= (long long int)A[i];
       P -= (long long int)A[i]*(long long int)A[i];
    }
     
    missingNumber = (S + P/S)/2;

    repeating = missingNumber - S;

    vector <int> ans;

    ans.push_back(repeating);
    ans.push_back(missingNumber);

    return ans;
}
```
TC - O(N), SC - O(1)  
### Xor approach  
Do xor of first n natural numbers. And then do xor with all array elements. We will get answer as repeated ^ missing.  
The thing is if we took any set bit in that repeated ^ missing, it indicate in one of the number, that bit will be 0 and in other number it will be 1.  
So let's divide all the numbers into 2 sets based on that set bit such that one number will be in set 1 and other will be in set 2.  
Now based on that setbit, divide all the array elements and the first n numbers. And do xor in every set.  
We will be left with the required numbers in both the sets. Manually find the respective numbers by iterating again.  
```cpp
vector < int >Solution::repeatedNumber (const vector < int >&arr) {
    int xor1;
    int set_bit_no;

    int i;
    int x = 0; // missing
    int y = 0; // repeated
    int n = arr.size();

    xor1 = arr[0];
    for (i = 1; i < n; i++)
        xor1 = xor1 ^ arr[i];
    for (i = 1; i <= n; i++)
        xor1 = xor1 ^ i;
    set_bit_no = xor1 & ~(xor1 - 1);

    for (i = 0; i < n; i++) {
        if (arr[i] & set_bit_no)
            x = x ^ arr[i];

        else
            y = y ^ arr[i];
    }

    for (i = 1; i <= n; i++) {
        if (i & set_bit_no)
            x = x ^ i;
        else           
            y = y ^ i;
    }

    int x_count = 0;
    for (int i=0; i<n; i++) {
        if (arr[i]==x)
            x_count++;
    }
    
    if (x_count==0)
        return {y, x};
    
    return {x, y};
}
```
TC - O(n), SC - O(1)  

# 12) Count inversions in an array  
TBD

# 13) Search in a 2D matrix  
Given an m * n 2D matrix and an integer, write a program to find if the given integer exists in the matrix.  
Given matrix has the following properties:  
Integers in each row are sorted from left to right.  
The first integer of each row is greater than the last integer of the previous row.  
### Approaches
Naive - O(m * n) search every element.  
Efficient - binary search - O(logMN)  
```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int lo = 0;
        if(!matrix.size()) return false;
        int hi = (matrix.size() * matrix[0].size()) - 1;
        
        while(lo <= hi) {
            int mid = (lo + (hi - lo) / 2);
            if(matrix[mid/matrix[0].size()][mid % matrix[0].size()] == target) {
                return true;
            }
            if(matrix[mid/matrix[0].size()][mid % matrix[0].size()] < target) {
                lo = mid + 1;
            }
            else {
                hi = mid - 1;
            }
        }
        return false;
    }
};
```
# 14) Pow(X,n)  
Given a double x and integer n, calculate x raised to power n. Basically Implement pow(x, n).  
### Approaches
Naive - O(N)  
Optimal - Binary exponentiation  
```cpp
double myPow(double x, int n) {
  double ans = 1.0;
  long long nn = n;
  if (nn < 0) nn = -1 * nn;
  while (nn) {
    if (nn % 2) {
      ans = ans * x;
      nn = nn - 1;
    } else {
      x = x * x;
      nn = nn / 2;
    }
  }
  if (n < 0) ans = (double)(1.0) / (double)(ans);
  return ans;
}
```
TC - O(LOGN), SC - O(1)  

# 15) Majority Element (> N/2 times)  
- Initialize 2 variables: 
     - Count –  for tracking the count of element
     - Element – for which element we are counting
- Traverse through nums array.
   - If Count is 0 then initialize the current traversing integer of array as Element 
   - If the traversing integer of array and Element are same increase Count by 1
   - If they are different decrease Count by 1
- The integer present in Element is the result we are expecting.  
```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int count = 0;
        int candidate = 0;

        for (int num : nums) {
            if (count == 0) {
                candidate = num;
            }
            if(num==candidate) count += 1; 
            else count -= 1; 
        }

        return candidate;
    }
};
```
TC - O (N), SC - O(1)  

# 16) Majority element (> N/3 times)  
Given an array of N integers. Find the elements that appear more than N/3 times in the array. If no such element exists, return an empty vector.  
### Approach  
Let, ele be the element present in the array at any index.   
- if ele == num1, so we increment c1.
- if ele == num2, so we increment c2.
- if c1 is 0, so we assign num1 = ele.
- if c2 is 0, so we assign num2 = ele.
- In all the other cases we decrease both c1 and c2.
In the last step, we will run a loop to check if num1 or nums2 are the majority elements or not by running a for loop check.  
```cpp
vector < int > majorityElement(int nums[], int n) {
  int sz = n;
  int num1 = -1, num2 = -1, count1 = 0, count2 = 0, i;
  for (i = 0; i < sz; i++) {
    if (nums[i] == num1)
      count1++;
    else if (nums[i] == num2)
      count2++;
    else if (count1 == 0) {
      num1 = nums[i];
      count1 = 1;
    } else if (count2 == 0) {
      num2 = nums[i];
      count2 = 1;
    } else {
      count1--;
      count2--;
    }
  }
  vector < int > ans;
  count1 = count2 = 0;
  for (i = 0; i < sz; i++) {
    if (nums[i] == num1)
      count1++;
    else if (nums[i] == num2)
      count2++;
  }
  if (count1 > sz / 3)
    ans.push_back(num1);
  if (count2 > sz / 3)
    ans.push_back(num2);
  return ans;
}
```
TC - O(N), SC - O(1)  

# 17) Grid Unique Paths  
Given a matrix m X n, count paths from left-top to the right bottom of a matrix with the constraints that from each cell you can either only move to the rightward direction or the downward direction.  
### Approaches  
dp - O(n * m)  
combinatorics - (m+n-2)C(m-1) - O(max(m,n))  
```cpp
class Solution {
public:
    int uniquePaths(int m, int n) {
            int N = n + m - 2;
            int r = m - 1; 
            double res = 1;
            
            for (int i = 1; i <= r; i++)
                res = res * (N - r + i) / i;
            return (int)res;
    }
};
```

# 18) Count Reverse Pairs  
TBD

# 19) Two sum
Given an array of integers nums[] and an integer target, return indices of the two numbers such that their sum is equal to the target.  
### Approaches  
Naive - O(n^2) - for every element, check every other element.  
2 pointer approach - first sort the array and then use 2 pointers.  
```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    	vector<int> res,store;
    	store = nums;
    	sort(store.begin(), store.end());
    	int left=0,right=nums.size()-1;
    	int n1,n2;
    	while(left<right){
        	if(store[left]+store[right]==target){
            	n1 = store[left];
            	n2 = store[right];
            	break;
        	}
        	else if(store[left]+store[right]>target)
            	    right--;
        	else
            	    left++;
    	}
    	for(int i=0;i<nums.size();++i){
        	if(nums[i]==n1)
            	    res.emplace_back(i);
        	else if(nums[i]==n2)
            	    res.emplace_back(i);
    	}
    	    return res;
	}
```
TC - O(NLOGN), SC - O(N)  
Hashing - O(n), O(n)  
```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    vector<int> res;
    unordered_map<int, int> mp;
    for (int i = 0; i < nums.size(); ++i) {
   	 if (mp.find(target - nums[i]) != mp.end()) {
   		 res.emplace_back(i);
   		 res.emplace_back(mp[target - nums[i]]);
   		 return res;
   	 }
   	 mp[nums[i]] = i;
    }
    return res;
}
```

# 20) Three Sum  
Given an array of N integers, your task is to find unique triplets that add up to give a sum of zero. In short, you need to return an array of all the unique triplets [arr[a], arr[b], arr[c]] such that i!=j, j!=k, k!=i, and their sum is equal to zero.  
### Approaches  
**Naive** - We keep three-pointers i,j, and k. For every triplet we find the sum of A[i]+A[j]+A[k]. If this sum is equal to zero, we’ve found one of the triplets. We add it to our data structure and continue with the rest.  
```cpp
vector < vector < int >> threeSum(vector < int > & nums) {
  vector < vector < int >> ans;
  vector < int > temp;
  int i, j, k;
  for (i = 0; i < nums.size() - 2; i++) {
    for (j = i + 1; j < nums.size() - 1; j++) {
      for (k = j + 1; k < nums.size(); k++) {
        temp.clear();
        if (nums[i] + nums[j] + nums[k] == 0) {
          temp.push_back(nums[i]);
          temp.push_back(nums[j]);
          temp.push_back(nums[k]);
        }
        if (temp.size() != 0)
          ans.push_back(temp);
      }
    }
  }
  return ans;
}
```
TC - O(N^3), SC - O(3 * K)  
**optimal**  
fixing one pointer and using 2 pointer approach.  
```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>> ans;
        for(int i=0;i<max(0,(int)nums.size()-2);i++){
            vector<int> vec;
            int l = i, m = i + 1, r = nums.size() - 1;
            while(m < r){
                int temp = nums[m] + nums[r];
                if(temp > -nums[l]) r--;
                else if(temp < -nums[l]) m++;
                else{
                    vec = {nums[l], nums[m], nums[r]};
                    ans.push_back(vec);
                    while(m < nums.size() - 1 && nums[m] == vec[1]) m++;
                    while(r >= m && nums[r] == vec[2]) r--;
                }
            }
            while(i+1 < nums.size() && nums[i+1] == nums[i]) i++;
        }
        return ans;
    }
};
```
TC - O(N^2), SC - O(M)  

# 21) Four Sum  
Given an array of N integers, your task is to find unique quads that add up to give a target value. In short, you need to return an array of all the unique quadruplets [arr[a], arr[b], arr[c], arr[d]] such that their sum is equal to a given target.  
### Approach  
It's very similar to 3 sum. So, we can generalise this for k sum. We fix k-2 pointers one by one and then use 2 pointer approach and then try removing duplicates for each pointer.  
```cpp
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& num, int target) {
        vector<vector<int> > res;
        if (num.empty())
            return res;
        int n = num.size(); 
        sort(num.begin(),num.end());
        for (int i = 0; i < n; i++) { 
            int target_3 = target - num[i];
            for (int j = i + 1; j < n; j++) {
                int target_2 = target_3 - num[j];      
                int front = j + 1;
                int back = n - 1;    
                while(front < back) {
                    int two_sum = num[front] + num[back];
                    if (two_sum < target_2) front++;              
                    else if (two_sum > target_2) back--;
                    else {
                    
                        vector<int> quadruplet(4, 0);
                        quadruplet[0] = num[i];
                        quadruplet[1] = num[j];
                        quadruplet[2] = num[front];
                        quadruplet[3] = num[back];
                        res.push_back(quadruplet);
                        while (front < back && num[front] == quadruplet[2]) ++front;
                        while (front < back && num[back] == quadruplet[3]) --back;            
                    }
                }
                while(j + 1 < n && num[j + 1] == num[j]) ++j;
            }    
            while (i + 1 < n && num[i + 1] == num[i]) ++i;  
        }
    
        return res;
    }
};
```
TC - O(N^3)  

# 22) Longest Consecutive sequence  
You are given an array of ‘N’ integers. You need to find the length of the longest sequence which contains the consecutive elements.  
Eg : Input: [100, 200, 1, 3, 2, 4]  
Output: 4  
Explanation: The longest consecutive subsequence is 1, 2, 3, and 4.  
### Approaches  
1 - If we sort the array, TC - O(NLOGN), SC - O(1)  
**Optimal**
Use a hashset ans first insert all array elements into hashset. Check if this can be the starting element of consecutive sequence by checking whether x-1 exists or not. If it's the first, check for x+1 and so on. Update the answer accordingly.  
```cpp
int longestConsecutive(vector < int > & nums) {
  set < int > hashSet;
  for (int num: nums) {
    hashSet.insert(num);
  }
  int longestStreak = 0;
  for (int num: nums) {
    if (!hashSet.count(num - 1)) {
      int currentNum = num;
      int currentStreak = 1;
      while (hashSet.count(currentNum + 1)) {
        currentNum += 1;
        currentStreak += 1;
      }
      longestStreak = max(longestStreak, currentStreak);
    }
  }
  return longestStreak;
}
```
TC,SC - O(N)  

# 23) Largest subarray with 0 sum  
Given an array containing both positive and negative integers, we have to find the length of the longest subarray with the sum of all elements equal to zero.   
### Approaches  
**Naive** - O(n^2)  
**Optimal** -  Now let’s say we know that the sum of subarray(i, j) = S, and we also know that sum of subarray(i, x) = S where i < x < j. We can conclude that the sum of subarray(x+1, j) = 0. So we can do ths using prefix sums.  
```cpp
int maxLen(int A[], int n)
{
    unordered_map<int,int> mpp; 
    int maxi = 0;
    int sum = 0; 
    for(int i = 0;i<n;i++) {
        sum += A[i]; 
        if(sum == 0) 
            maxi = i + 1; 
        else 
            if(mpp.find(sum) != mpp.end()) 
                maxi = max(maxi, i - mpp[sum]); 
            else 
                mpp[sum] = i;
        }   
    }
    return maxi; 
}
```
TC,SC - O(N)  

# 24) Count number of sub arrays with given xor k  
Given an array of integers A and an integer B. Find the total number of subarrays having bitwise XOR of all elements equal to B.  
### Approaches  
**Naive** - check all possible subarrays - O(n^2)  
**optimal** - prefix xor and map  
We need to traverse the array while we maintain variables for current_perfix_xor, counter, and also a map to keep track of visited xors. This map will maintain the frequency count of all previous visited current_prefix_xor values. If for any index current_prefix_xor is equal to B, we increment the counter. If for any index we find that Z is present in the visited map, we increment the counter by visited[Z] (Z=current_prefi_xor^B). At every index, we insert the current_prefix_xor into the visited map with its frequency.  
```cpp
class Solution{
    public:
    int solve(vector<int> &A, int B) {
    unordered_map<int,int>visited;
    int cpx = 0;
    long long c=0;
    for(int i=0;i<A.size();i++){
        cpx^=A[i];
        if(cpx==B) c++;
        int h = cpx^B;
        if(visited.find(h)!=visited.end()){
            c=c+visited[h];
        }
        visited[cpx]++;
    }
    return c;
}
};
```
TC, SC - O(N)  

# 25) Longest Substring without repeat  
Given a String, find the length of longest substring without any repeating character.  
### Approaches 
**Naive** - O(n^2)  
2pointer
```cpp
class Solution {
  public:
    int lengthofLongestSubstring(string s) {
      vector < int > mpp(256, -1);

      int left = 0, right = 0;
      int n = s.size();
      int len = 0;
      while (right < n) {
        if (mpp[s[right]] != -1)
          left = max(mpp[s[right]] + 1, left);

        mpp[s[right]] = right;

        len = max(len, right - left + 1);
        right++;
      }
      return len;
    }
};
```
TC,SC - O(N)  

# 26) Traping Rain Water  
Given an array of non-negative integers representation elevation of ground. Your task is to find the water that can be trapped after rain.  
![image](https://user-images.githubusercontent.com/56584349/178978573-93b69f7e-e2d1-48f0-9454-b5695b065449.png)  
The amount of water we can store at a particular index = min(leftMax,rightMax) - arr[i]
brute would be done in O(n^2).  If we use prefix and suffix arrays, it would be done in O(N) but also takes up some space.  
**Optimal** is to use 2 pointer approach.  
```cpp
int trap(vector < int > & height) {
  int n = height.size();
  int left = 0, right = n - 1;
  int res = 0;
  int maxLeft = 0, maxRight = 0;
  while (left <= right) {
    if (height[left] <= height[right]) {
      if (height[left] >= maxLeft) {
        maxLeft = height[left];
      } else {
        res += maxLeft - height[left];
      }
      left++;
    } else {
      if (height[right] >= maxRight) {
        maxRight = height[right];
      } else {
        res += maxRight - height[right];
      }
      right--;
    }
  }
  return res;
}
```
TC - O(N), SC - O(1)  

# 27) Max Consecutive Ones  
Given an array that contains only 1 and 0 return the count of maximum consecutive ones in the array.  
```cpp
class Solution {
  public:
    int findMaxConsecutiveOnes(vector < int > & nums) {
      int cnt = 0;
      int maxi = 0;
      for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == 1) {
          cnt++;
        } else {
          cnt = 0;
        }

        maxi = max(maxi, cnt);
      }
      return maxi;
    }
};
```
TC - O(N), SC - O(1)  
