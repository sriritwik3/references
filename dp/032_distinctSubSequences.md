# Distinct Subsequences  
**[Link](https://takeuforward.org/data-structure/distinct-subsequences-dp-32/)**  
We are given two strings S1 and S2, we want to know how many distinct subsequences of S2 are present in S1. 

## Solution  
f(i,j) - count of all distinct subsequences of s2[0..j-1] in the string s1[0..i-1].  
![image](https://user-images.githubusercontent.com/56584349/178027105-568e24c0-79c0-42ed-80f5-af6bdc5dc409.png)  
if(s1[i] == s2[j]) continue for i-1,j-1 and also jth character in s2 can be equal to someother in s1.so call both f(i-1,j) and f(i-1,j-1).  
else call f(i-1,j). search for jth character in s1.  

## Memoization  
```cpp
#include <bits/stdc++.h>

using namespace std;

int prime = 1e9+7;

int countUtil(string s1, string s2, int ind1, int ind2,vector<vector<int>>& dp){
    if(ind2<0)
        return 1;
    if(ind1<0)
        return 0;
    
    if(dp[ind1][ind2]!=-1)
        return dp[ind1][ind2];
    
    if(s1[ind1]==s2[ind2]){
        int leaveOne = countUtil(s1,s2,ind1-1,ind2-1,dp);
        int stay = countUtil(s1,s2,ind1-1,ind2,dp);
        
        return dp[ind1][ind2] = (leaveOne + stay)%prime;
    }
    
    else{
        return dp[ind1][ind2] = countUtil(s1,s2,ind1-1,ind2,dp);
    }
}

int subsequenceCounting(string &t, string &s, int lt, int ls) {
    // Write your code here.
    
    vector<vector<int>> dp(lt,vector<int>(ls,-1));
    return countUtil(t,s,lt-1,ls-1,dp);
} 


int main() {

  string s1 = "babgbag";
  string s2 = "bag";

  cout << "The Count of Distinct Subsequences is "
  <<subsequenceCounting(s1,s2,s1.size(),s2.size());
}
```
TC - O(NM), SC - O(NM) + O(N) + O(M)  

## Tabulation  
```cpp
#include <bits/stdc++.h>

using namespace std;

int prime = 1e9+7;


int subsequenceCounting(string &s1, string &s2, int n, int m) {
    // Write your code here.
    
    vector<vector<int>> dp(n+1,vector<int>(m+1,0));
    
    for(int i=0;i<n+1;i++){
        dp[i][0]=1;
    }
    for(int i=1;i<m+1;i++){
        dp[0][i]=0;
    }
    
    for(int i=1;i<n+1;i++){
        for(int j=1;j<m+1;j++){
            
            if(s1[i-1]==s2[j-1])
                dp[i][j] = (dp[i-1][j-1] + dp[i-1][j])%prime;
            else
                dp[i][j] = dp[i-1][j];
        }
    }
    
    
    return dp[n][m];
} 


int main() {

  string s1 = "babgbag";
  string s2 = "bag";

  cout << "The Count of Distinct Subsequences is "<<
  subsequenceCounting(s1,s2,s1.size(),s2.size());
}
```
TC, SC - O(NM)  

## Space optimised  
```cpp
#include <bits/stdc++.h>

using namespace std;

int prime = 1e9+7;


int subsequenceCounting(string &s1, string &s2, int n, int m) {
    // Write your code here.
    
    vector<int> prev(m+1,0);
    
    prev[0]=1;
    
    for(int i=1;i<n+1;i++){
        for(int j=m;j>=1;j--){ // Reverse direction
            
            if(s1[i-1]==s2[j-1])
                prev[j] = (prev[j-1] + prev[j])%prime;
            else
                prev[j] = prev[j]; //can omit this statemwnt
        }
    }
    
    
    return prev[m];
} 

int main() {

  string s1 = "babgbag";
  string s2 = "bag";

  cout << "The Count of Distinct Subsequences is "<<
  subsequenceCounting(s1,s2,s1.size(),s2.size());
}
```
TC - O(NM), SC - O(M)  
