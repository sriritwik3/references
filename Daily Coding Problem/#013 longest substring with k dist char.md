# Longest Substring with K distinct characters

## Problem Statement
Given an integer k and a string s, find the length of the longest substring that contains at most k distinct characters.
For example, given s = "abcba" and k = 2, the longest substring with k distinct characters is "bcb".

## Solution

### Intuition

We maintain a window which can contain atmost k distinct charaters. Each time it exceeds k, we remove elements from the left and update their 
frequency from the map and decrease the length of window.
Each time we encounter a distinct character which is not present in the map increment window
When window gets greater than k, remove the characters from left of the sliding window(based on our left index l) untill window <= k
Don't get confused betwen window and sliding window. Out of convention in my code, window means the no.of distinct characters present in our sliding window
and Sliding window is an imaginary window which holds the current substing from index l to i
l is the starting index of sliding window
i is the current end of sliding window
Thus each time we store maximum size of sliding window by i-l+1

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)

int32_t main()
{
    fastio;
    string s;
    ll k;
    cin >> k;
    cin >> s;
    unordered_map<char,ll> m;
    ll l=0,window=0,ans=1;
    for(ll i=0;i<s.size();i++){
        if(m.find(s[i]) == m.end()) m[s[i]] = 1,window++;
        else m[s[i]]++;
        while(window > k){
            m[s[l]]--;
            if(m[s[l]] == 0) m.erase(s[l]),window--;
            l++;
        }
        ans = max(ans,i-l+1);
    }
    cout << ans <<  '\n';
    return 0;
} 
```
