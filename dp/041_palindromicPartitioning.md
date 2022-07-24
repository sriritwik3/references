# Palindromic Partitioning  
Given a string s, partition s such that every substring of the partition is a palindrome.  

Return the minimum cuts needed for a palindrome partitioning of s.  

Explanations later, just go through these approaches.  
Here is the basic idea of the solution:  

Initialize the 'cut' array: For a string with n characters s[0, n-1], it needs at most n-1 cut. Therefore, the 'cut' array is initialized as cut[i] = i-1  

Use two variables in two loops to represent a palindrome:  
The external loop variable 'i' represents the center of the palindrome. The internal loop variable 'j' represents the 'radius' of the palindrome. Apparently, j <= i is a must.  
This palindrome can then be represented as s[i-j, i+j]. If this string is indeed a palindrome, then one possible value of cut[i+j] is cut[i-j] + 1, where cut[i-j] corresponds to s[0, i-j-1] and 1 correspond to the palindrome s[i-j, i+j];  

When the loops finish, you'll get the answer at cut[s.length]  
```cpp
class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        vector<int> cut(n+1, 0);  // number of cuts for the first k characters
        for (int i = 0; i <= n; i++) cut[i] = i-1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; i-j >= 0 && i+j < n && s[i-j]==s[i+j] ; j++) // odd length palindrome
                cut[i+j+1] = min(cut[i+j+1],1+cut[i-j]);

            for (int j = 1; i-j+1 >= 0 && i+j < n && s[i-j+1] == s[i+j]; j++) // even length palindrome
                cut[i+j+1] = min(cut[i+j+1],1+cut[i-j+1]);
        }
        return cut[n];
    }
};
```  
Calculate and maintain 2 DP states:  

pal[i][j] , which is whether s[i..j] forms a pal  

d[i], which is the minCut for s[i..n-1]    

Once we comes to a pal[i][j]==true:  

if j==n-1, the string s[i..n-1] is a Pal, minCut is 0, d[i]=0;  
else: the current cut num (first cut s[i..j] and then cut the rest  
s[j+1...n-1]) is 1+d[j+1], compare it to the exisiting minCut num  
d[i], repalce if smaller.  
d[0] is the answer.  
```cpp
class Solution {
    public:
        int minCut(string s) {
            if(s.empty()) return 0;
            int n = s.size();
            vector<vector<bool>> pal(n,vector<bool>(n,false));
            vector<int> d(n);
            for(int i=n-1;i>=0;i--)
            {
                d[i]=n-i-1;
                for(int j=i;j<n;j++)
                {
                    if(s[i]==s[j] && (j-i<2 || pal[i+1][j-1]))
                    {
                       pal[i][j]=true;
                       if(j==n-1)
                           d[i]=0;
                       else if(d[j+1]+1<d[i])
                           d[i]=d[j+1]+1;
                    }
                }
            }
            return d[0];
        }
    };
    ```
