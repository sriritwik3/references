# Sliding Window Maximum

## Problem Statement

This problem was asked by Google.

Given an array of integers and a number k, where 1 <= k <= length of the array, compute the maximum values of each subarray of length k.

For example, given array = [10, 5, 2, 7, 8, 7] and k = 3, we should get: [10, 7, 8, 8], since:

10 = max(10, 5, 2)
7 = max(5, 2, 7)
8 = max(2, 7, 8)
8 = max(7, 8, 7)
Do this in O(n) time and O(k) space. You can modify the input array in-place and you do not need to store the results. You can simply print them out as you compute them.

## Solution

### Initial Ideas

We have to use some datastructure instead of array to store the elements of current window in each iteration. One key point which can reduce our complexity is in a current window, 
if x > i and a[x] > a[i] there is no use of storing a[i] in the window, as for all subsequent windows only a[x] will contribute as it is greater than a[i]. So there is no use of 
storing all the elements of current window in our data strucuture. And there is no use of storing elements of previous windows which are not a part of the current window.

### Entire intution

We use a data structure called deque as we can push and pop elements both from both front and back. We store indices of the array elements in the deque such that we won't change the
order in which elements appear in original array. We keep on pushing indices at the back of the deque. If the front of the deque has index i  < (i-k+1) it means that the index is less
than the current window and the element at that index is not a part of the current window. So we pop it from the front. And if the back of the deque has index x which is less than
current index i and a[x] < a[i], then there is no use of that a[x] as everytime, only a[i] will contribute to our answer. So we pop all the elements from the back where x < i and 
a[x] < a[i].

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)

int32_t main()
{
    fastio;
    ll n,k;
    cin >> n >> k;
    ll a[n+1];
    for(ll i=1;i<=n;i++) cin >> a[i];
    deque<ll> dq;
    for(ll i=1;i<=n;i++){
        while(!dq.empty() && i-k+1 > dq.front()) dq.pop_front(); //elements which are not a part of the current window
        while(!dq.empty() && a[dq.back()] < a[i]) dq.pop_back(); //elements which are smaller than the current element
        dq.push_back(i);
        if(i>=k) cout << a[dq.front()] << ' ';
    }
    return 0;
}    
```
