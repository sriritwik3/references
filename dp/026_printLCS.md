# Print LCS  
**[Link](https://takeuforward.org/data-structure/print-longest-common-subsequence-dp-26/)**  
Print the actual string of Longest Common Subsequence  

## Solution  
- We will fill the string str from the last by maintaining a pointer. 
- We will start from the right-most cell of the dp array, initially i=n and j=m.  
- At every cell, we will check if S1[i-1] == S2[j-1], if it is then it means this character is a part of the longest common substring. So we will push it to the str (at last). Then we will move to the diagonally top-left(↖)  cell by assigning i to i-1 and j to j-1.  
- Else, this character is not a part of the longest common subsequence. It means that originally this cell got its value from its left cell (←) or from its top cell (↑). Whichever cell’s value will be more of the two, we will move to that cell.  
- We will continue till i>0 and j>0, failing it we will break from the loop.  
- At last we will get our lcs string in “str”.  

```cpp
#include <bits/stdc++.h>

using namespace std;

void lcs(string s1, string s2) {

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
  string str = "";
  for (int k = 1; k <= len; k++) {
    str += "$"; // dummy string
  }

  while (i > 0 && j > 0) {
    if (s1[i - 1] == s2[j - 1]) {
      str[index] = s1[i - 1];
      index--;
      i--;
      j--;
    } else if (s1[i - 1] > s2[j - 1]) {
      i--;
    } else j--;
  }
  cout << str;
}

int main() {

  string s1 = "abcde";
  string s2 = "bdgek";

  cout << "The Longest Common Subsequence is ";
  lcs(s1, s2);
}
```
TC, SC -  O(NM)  
