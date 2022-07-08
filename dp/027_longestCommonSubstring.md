# Longest Common Substring  
**[Link](https://takeuforward.org/data-structure/longest-common-substring-dp-27/)**  
A substring of a string is a subsequence in which all the characters are consecutive. Given two strings, we need to find the longest common substring.
Print the length of the longest common substring.  

## Solution  
Quite similar to the LCS problem with these modifications.  
- if(S1[i-1] != S2[j-1]), the characters don’t match, therefore the consecutiveness of characters is broken. So we set the cell value (dp[i][j]) as 0.
- if(S1[i-1] == S2[j-1]), then the characters match and we simply set its value to 1+dp[i-1][j-1]. We have done so because dp[i-1][j-1] gives us the longest common substring till the last cell character (current strings -{matching character}). As the current cell’s character is matching we are adding 1 to the consecutive chain.

Now dp[n][m] doesn't contain the answer but the maximum value in the entire dp array is the answer.  

## Tabulation  
```cpp
#include <bits/stdc++.h>

using namespace std;

int lcs(string &s1, string &s2){
    
    int n = s1.size();
    int m = s2.size();
    
    vector<vector<int>> dp(n+1,vector<int>(m+1,0));

    int ans = 0;
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s1[i-1]==s2[j-1]){
                int val = 1 + dp[i-1][j-1];
                dp[i][j] = val;
                ans = max(ans,val);
            }
            else
                dp[i][j] = 0;
        }
    }
    
    return ans;
    
}

int main() {

  string s1= "abcjklp";
  string s2= "acjkp";
                                 
  cout<<"The Length of Longest Common Substring is "<<lcs(s1,s2);
}
```
TC , SC - O(NM)  

## Space optimised  
```cpp
#include <bits/stdc++.h>

using namespace std;


int lcs(string &s1, string &s2){
	//	Write your code here.
    
    int n = s1.size();
    int m = s2.size();
    
    vector<int> prev(m+1,0), cur(m+1,0);

    int ans = 0;
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s1[i-1]==s2[j-1]){
                int val = 1 + prev[j-1];
                cur[j] = val;
                ans = max(ans,val);
            }
            else
                cur[j] = 0;
        }
        prev=cur;
    }
    
    return ans;
    
}

int main() {

  string s1= "abcjklp";
  string s2= "acjkp";
                                 
  cout<<"The Length of Longest Common Substring is "<<lcs(s1,s2);
}
```
TC - O(NM), SC - O(M)  

