# Maximum Product Subarray  
Given an array that contains both negative and positive integers, find the maximum product subarray.  

### Approaches  
The main gist in this problem is that even if we multiply 2 negative numbers we might get maximum product. So we just can't ignore them.  
Let's start with the naive approaches.  
**Too naive** Iterate through all possible subarrays and find the maximum one. Would take O(n^2). If we optimise a little, it would take O(n^2).  
**2 pointer approach**  
1) Through intution explanation we know that if all the elements are positive or the negative elements are even then ur answer will be product of complete array which u will get in variable l and r at the last iteration.
2) But if negative elements are odd then u have to remove one negative element and it is sure that it will be either right of max prefix product or left of max suffix product. So u need not to modify anything in your code as u are getting prefix product in l and suffix prduxt in r.
3) If array also contains 0 then your l and r will become 0 at that point...then just update it to 1(or else u will keep multiplying with 0) to get the product ahead making another subarray.    
```cpp
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int leftAns = nums[0], rightAns = nums[0], isZero = 0, n = nums.size();
        int l = 1, r = 1;
        for(int i=0;i<n;i++){
            leftAns = max(leftAns, l = l*nums[i] );
            rightAns = max(rightAns, r = r*nums[n-1-i]);
              if(nums[i] == 0){
                isZero = 1;
                l = 1;
            }
            if(nums[n-i-1] == 0){
                isZero = 1;
                r = 1;
            }
        }
        return isZero?max(0,max(leftAns,rightAns)):max(leftAns,rightAns);
    }
};
```
TC - O(N), SC - O(N)  

Another approach is to store the minimum and maximum so far. If we get a neg number swap them because multiplying neg number with min gives the max. And multiplying with max gives min.  
```cpp
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int maxi=nums[0],mini=nums[0],temp=nums[0];
        for(int i=1;i<nums.size();i++)
        {
            if(nums[i]<0) swap(maxi,mini);
            maxi = max(nums[i],maxi*nums[i]);
            mini = min(nums[i],mini*nums[i]);
            temp = max(temp,maxi);
        }
        return temp;
    }
};
```
TC- O(N), SC - O(1)  
