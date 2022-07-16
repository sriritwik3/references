# Binary Search  
## Striver Sheet  

Iterator lower_bound (Iterator first, Iterator last, const val)   
Iterator upper_bound (Iterator first, Iterator last, const val)   
**lower_bound** returns an iterator pointing to the first element in the range [ first,last ) which has a value not less than ‘val'
and if the value is not present in the vector then it returns the end iterator  
**upper_bound** returns an iterator pointing to the first element in the range [first,last) which has a value greater than ‘val’.   

# 1) The Nth root of an integer  
The nth root of a number M is defined as a number X when raised to the power N equals M.  
```cpp
double multiply(double number, int n) {
    double ans = 1.0;
    for(int i = 1;i<=n;i++) {
        ans = ans * number;
    }
    return ans; 
}

void getNthRoot(int n, int m) {
    double low = 1;
    double high = m;
    double eps = 1e-6; 
    
    while((high - low) > eps) {
        double mid = (low + high) / 2.0; 
        if(multiply(mid, n) < m) {
            low = mid; 
        }
        else {
            high = mid; 
        }
    } 
    cout <<n<<"th root of "<<m<<" is "<<low<<endl;  
}
```
Time Complexity: N x log(M x 10^d) Where N is for multiply the number we want to check N times. M x 10^d because we are checking for d decimal places in between two integers.  
sc- O(1)  

# 2) Matrix Median  
Median in a row wise sorted matrix.  
Note: No extra memory is allowed.  
For an element to be the median, there should be n/2 elements lesser than that element. So we are gonna perform binary search on that logic.  
First we try to find the minimum and maximum element of the matrix which can be simply done by comparing all the first column and last column elements respectively.  
And start with mid = (min + max)/2. To find the no. of lesser elements we can use upper bound on every row.  If it is lesser than rc/2 median will be in the first half else in the second half.  
```cpp
int binaryMedian(int m[][MAX], int r ,int c)
{
    int min = INT_MAX, max = INT_MIN;
    for (int i=0; i<r; i++)
    {
        // Finding the minimum element
        if (m[i][0] < min)
            min = m[i][0];
 
        // Finding the maximum element
        if (m[i][c-1] > max)
            max = m[i][c-1];
    }
 
    int desired = (r * c + 1) / 2;
    while (min < max)
    {
        int mid = min + (max - min) / 2;
        int place = 0;
 
        // Find count of elements smaller than or equal to mid
        for (int i = 0; i < r; ++i)
            place += upper_bound(m[i], m[i]+c, mid) - m[i];
        if (place < desired)
            min = mid + 1;
        else
            max = mid;
    }
    return min;
}
```
Time Complexity: O(32 * r * log(c)). The upper bound function will take log(c) time and is performed for each row. And since the numbers will be max of 32 bit, so binary search of numbers from min to max will be performed in at most 32 ( log2(2^32) = 32 ) operations.   
Auxiliary Space: O(1)  

# 3) Search single element in a sorted array  
Given a sorted array of N integers, where every element except one appears exactly twice and one element appears only once. Search Single Element in a sorted array.  
### Approaches  
If we do XOR of all array elements, we get the answer but it would take O(N) but using binary search would take O(logN) time.  
We can think of using binary search because the array is sorted.  
![image](https://user-images.githubusercontent.com/56584349/179341605-2c8cef5a-cd92-4bc5-82f3-f7b276ba8db7.png)  
![image](https://user-images.githubusercontent.com/56584349/179341612-a5189ee1-a783-4643-9ecf-8db436333774.png)  
```cpp
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while(left < right){
            int mid = (left + right)/2;
            if((mid % 2 == 0 && nums[mid] == nums[mid + 1]) || (mid % 2 == 1 && nums[mid] == nums[mid - 1]))
                left = mid + 1;
            else
                right = mid;
        }
        
        return nums[left];
    }
};
```
TC - O(N), SC - O(1)  

# 4) Search in a Rotated sorted array  
There is an integer array nums sorted in ascending order (with distinct values). Given the array nums after the possible clockwise rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums. We need to search a given element in a rotated sorted array.  
### Binary Search approach  
```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int low = 0, high = nums.size()-1;
        int pivot = -1;
        while(low <= high){
            cout << low << " " << high << endl;
            int mid = low + (high-low)/2;
            if(nums[mid] == target) return mid;
            if(nums[low] > nums[mid]){ // ENTIRE right array will be sorted so we first check if it's present in the right subarray if not we go for the left
                if(target <= nums[high] && nums[mid] < target) low = mid+1;
                else high = mid-1;
            }
            else{ // entire left array will be sorted, so we check if it's present in the left sub array if not we go for the right
                if(target < nums[mid] && nums[low] <= target) high = mid-1; 
                else low = mid+1;
            }
        }
        return -1;
    }
};
```
TC - O(LOGN), SC - O(1)

# 5) Allocate minimum number of pages  
The College library has N bags, the ith book has A[i] number of pages.  
You have to allocate books to B number of students so that the maximum number of pages allocated to a student is minimum.  
Conditions given :  
A book will be allocated to exactly one student.  
Each student has to be allocated at least one book.  
Allotment should be in contiguous order, for example, A student cannot be allocated book 1 and book 3, skipping book 2.  
Calculate and return the minimum possible number. Return -1 if a valid assignment is not possible.  
### Approach  
The maximum possible answer can be sum of all pages when no.of student is 1. The minimum possible answer is maximum array element when no.of students is n.  
So we use binary search on this search space and check whether with the current mid can we achieve our minimal distribution.  
```cpp
int isPossible(vector < int > & A, int pages, int students) {
  int cnt = 0;
  int sumAllocated = 0;
  for (int i = 0; i < A.size(); i++) {
    if (sumAllocated + A[i] > pages) {
      cnt++;
      sumAllocated = A[i];
      if (sumAllocated > pages) return false;
    } else {
      sumAllocated += A[i];
    }
  }
  if (cnt < students) return true;
  return false;
}

int books(vector < int > & A, int B) {
  if (B > A.size()) return -1;
  int low = A[0];
  int high = 0;
  //to find maximum value and sum of all pages
  for (int i = 0; i < A.size(); i++) {
    high = high + A[i];
    low = max(low, A[i]);
  }
  //binary search
  while (low <= high) {
    int mid = (low + high) >> 1;
    if (isPossible(A, mid, B)) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return low;
}
```
tc - O(NlogM) where M is the initial search space, SC- O(1)  

# 6) Aggressive cows  
There is a new barn with N stalls and C cows. The stalls are located on a straight line at positions x1,….,xN (0 <= xi <= 1,000,000,000). We want to assign the cows to the stalls, such that the minimum distance between any two of them is as large as possible. What is the largest minimum distance?  
Eg : INput - No of stalls = 5 , Array: {1,2,8,4,9}, And number of cows: 3
![image](https://user-images.githubusercontent.com/56584349/179346009-ebeeec1b-ed6e-4dbc-8d19-379494d74bdc.png)  
### Approach  
We want to check whether a particular number can be the answer. So we can binary search on this when we know the initial range. To do BS, we need to sort the array first.  
minimum possible distance would be smallest distance between 2 successive numbers and maximum possible distance would be a[n-1] - a[0] as the array is sorted.  
If a particular distance(mid) is possible we store it in a temp variable and reduce the search space to righter half as we need maximum possible minimum distance. If it;s not possible we reduce the search space to left half.  
```cpp
    #include <bits/stdc++.h>

    using namespace std;
    bool isPossible(int a[], int n, int cows, int minDist) {
      int cntCows = 1;
      int lastPlacedCow = a[0];
      for (int i = 1; i < n; i++) {
        if (a[i] - lastPlacedCow >= minDist) {
          cntCows++;
          lastPlacedCow = a[i];
        }
      }
      if (cntCows >= cows) return true;
      return false;
    }
    int main() {
      int n = 5, cows = 3;
      int a[]={1,2,8,4,9};
      sort(a, a + n);

      int low = 1, high = a[n - 1] - a[0];

      while (low <= high) {
        int mid = (low + high) >> 1;

        if (isPossible(a, n, cows, mid)) {
          low = mid + 1;
        } else {
          high = mid - 1;
        }
      }
      cout << "The largest minimum distance is " << high << endl;

      return 0;
    }
```
TC - O(NlogM) where M is the initial search space, SC - O(1)  

# 7) Median of 2 sorted arrays  
Given two sorted arrays arr1 and arr2 of size m and n respectively, return the median of the two sorted arrays.  
### Approach  
We can use the same approach as discussed in 2nd problem median matrix. But the best efficient approach is described below.  
- If n is odd median will be a single element else it is average of middle 2 elements.  
- We will always choose to do BS on shorter array.  
- Our final split will be in a way such that all the left elements are lesser than right elements in both the arrays.  
- As the median itself means that there exists (m+n+1)/2 smaller elements than that.  
- Take one pointer l1 initially as n(size of first array)/2.  
- Other will definitely be at l2 = (m+n+1)/2 - l1.  
- To satisfy the third point, we check whether leftMax of l1 <= rightMin of l2 and leftMax of l2 <= rightMIn of l1.  
- If leftMax 


TC - O(log(min(m,n)))), SC - O(1)  

