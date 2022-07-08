# Shortest Common Supersequence  
**[Link](https://takeuforward.org/data-structure/shortest-common-supersequence-dp-31/)**  
We are given two strings ‘S1’ and ‘S2’. We need to return their shortest common supersequence.
A supersequence is defined as the string which contains both the strings S1 and S2 as subsequences.  

## Solution 
![image](https://user-images.githubusercontent.com/56584349/177994467-9b2a12a5-8998-4c81-b8e1-fbd4899bab63.png)  
Characters of LCS needs to be covered only once so length of SCSS = n+m-k.  
We use the dp table of LCS to print SCSS.  

- We start from cell dp[n][m]. Initially i=n and j=m.    
- At every cell, we will check if S1[i-1] == S2[j-1], if it is then it means this character is a part of the longest common subsequence. So we will push it to the ans string str. Then we will move to the diagonally top-left(↖)  cell by assigning i to i-1 and j to j-1.  
- Else, this character is not a part of the longest common subsequence so we include it in ans string. Originally this cell got its value from its left cell (←) or from its top cell (↑). Whichever cell’s value will be more of the two, we will move to that cell.  
- We will continue till i>0 and j>0, failing it we will break from the loop.  
- After breaking, either i>0 or j>0 (only one condition will fail to break from the while loop), if(i>0) we push all the characters from S1 to ans string, else if(j>0), we push all the remaining characters from S2.
- At last, we reverse the ‘ans’ string and we get our answer.  

```cpp
#include <bits/stdc++.h>

using namespace std;

string shortestSupersequence(string s1, string s2){

  int n = s1.size();
  int m = s2.size();

  vector < vector < int >> dp(n + 1, vector < int > (m + 1, 0));
  for (int i = 0; i <= n; i++) {
    dp[i][0] = 0;
  }
  for (int i = 0; i <= m; i++) {
    dp[0][i] = 0;
  }

  for (int ind1 = 1; ind1 <= n; ind1++) {
    for (int ind2 = 1; ind2 <= m; ind2++) {
      if (s1[ind1 - 1] == s2[ind2 - 1])
        dp[ind1][ind2] = 1 + dp[ind1 - 1][ind2 - 1];
      else
        dp[ind1][ind2] = 0 + max(dp[ind1 - 1][ind2], dp[ind1][ind2 - 1]);
    }
  }

  int len = dp[n][m];
  int i = n;
  int j = m;

  int index = len - 1;
  string ans = "";

  while (i > 0 && j > 0) {
    if (s1[i - 1] == s2[j - 1]) {
      ans += s1[i-1];
      index--;
      i--;
      j--;
    } else if (dp[i - 1][j] > dp[i][j - 1]) {
        ans += s1[i-1];
        i--;
    } else {
        ans += s2[j-1];
        j--;
    }
  }
  
  //Adding Remaing Characters - Only one of the below two while loops will run 
  
  while(i>0){
      ans += s1[i-1];
      i--;
  }
  while(j>0){
      ans += s2[j-1];
      j--;
  }

  reverse(ans.begin(),ans.end());
  
  return ans;
}

int main() {

  string s1 = "brute";
  string s2 = "groot";

  cout << "The Longest Common Supersequence is "<<shortestSupersequence(s1,s2);
}
```
TC, SC - O(NM)  
