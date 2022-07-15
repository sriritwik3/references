# Strings
## Striver Sheet  

# 1) Reverse words in a string  
We start traversing the string from the end until we hit a space. It indicates that we have gone past a word and now we need to store it.  
We check if our answer variable is empty or not  
If it’s empty, it indicates that this is the last word we need to print, and hence, there shouldn’t be any space after this word.  
If it’s empty we add it to our result with a space after it. Here’s a quick demonstration of the same.  
```cpp
class Solution {
public:
    string reverseWords(string s) {
        string temp = "", ans = "";
        int i = 0;
        while(i<s.size()){
            if(s[i] == ' '){
                if(ans == "") ans = temp;
                else if(temp != "")ans = temp +" "+ ans;
                temp = "";
            }
            else temp += s[i];
            i++;
        }
        cout << ans << endl;
        if(temp != ""){
            if(ans == "") ans = temp;
            else if(temp != "")ans = temp + " " + ans;
        }
        return ans;
       
    }
};
```
TC - O(N), SC - O(1)  

# 2) Longest Palindromic Substring  
Brute - O(n^3) - verify all possible substrings whether they are palindrome or not.  
dp - O(n^2) time and space.  
expand around center - O(n^2) time, O(1) space   
Manachers algorithm would take O(n) time - but tbd   
### Expand around center approach  
There can be 2n-1 possible centers because there can be odd length and even length palindromes. For odd length palindrome i can be the center. For even length palindromes i,i+1 is the center.  
```cpp
class Solution {
public:
    string longestPalindrome(string s) {
    ll maxl=1; string ans = s.substr(0,1); ll l,r;
    for(ll i=0;i<s.size();i++){
       
            l=i,r=i;
            while(l>=0 && r<s.size() && s[l]==s[r]) {
                if(r-l+1 > maxl)
                    ans = s.substr(l,r-l+1),maxl = r-l+1;
                l--,r++;
            }
            
        l=i,r=i+1;
        while(l>=0 && r<s.size() && s[l]==s[r]) {
            if(r-l+1 > maxl)
                ans=s.substr(l,r-l+1), maxl=r-l+1;
            l--,r++;         
        }
            
    }
    return ans;
    }
};
```

# 3) Roman to Integer  
```cpp
class Solution {
public:
    int romanToInt(string s) {
        unordered_map<int,int> m;
        m['I'] = 1;
        m['V'] = 5;
        m['X'] = 10;
        m['L'] = 50;
        m['C'] = 100;
        m['D'] = 500;
        m['M'] = 1000;
        int ans = 0;
        for(int i=0;i<s.size()-1;i++){
            if(m[s[i]] < m[s[i+1]]) ans -= m[s[i]];
            else ans += m[s[i]];
        }
        ans += m[s[s.size()-1]];
        return ans;
    }
};
``` 
TC, SC - O(N)  

# 4) Integer to Roman  
```python
class Solution:
    def intToRoman(self, nums: int) -> str:
        M = ["","M","MM","MMM"]
        C = ["","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"]
        X = ["","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"]
        I = ["","I","II","III","IV","V","VI","VII","VIII","IX"]
        return M[nums//1000] + C[(nums%1000)//100] + X [(nums%100)//10] + I[(nums%10)]
```

# 5) Implement ATOI  
Implement the myAtoi(string s) function, which converts a string to a 32-bit signed integer (similar to C/C++'s atoi function).  
The algorithm for myAtoi(string s) is as follows:    
Read in and ignore any leading whitespace.  
Check if the next character (if not already at the end of the string) is '-' or '+'. Read this character in if it is either. This determines if the final result is negative or positive respectively. Assume the result is positive if neither is present.
Read in next the characters until the next non-digit character or the end of the input is reached. The rest of the string is ignored.
Convert these digits into an integer (i.e. "123" -> 123, "0032" -> 32). If no digits were read, then the integer is 0. Change the sign as necessary (from step 2).
If the integer is out of the 32-bit signed integer range [-231, 231 - 1], then clamp the integer so that it remains in the range. Specifically, integers less than -231 should be clamped to -231, and integers greater than 231 - 1 should be clamped to 231 - 1.
Return the integer as the final result.  

![image](https://user-images.githubusercontent.com/56584349/179205780-96d07362-7f3f-485a-87cb-beaef2e96ee9.png)  
```
'123'  => 123 (a number with no sign is a positive number).  
'+123' => 123 (a number with '+' sign is a positive number).  
'-12'  => -12 (a number with '-' sign is a negative number).  
'-+12' => 0   (another sign after one sign is considered as non-digit character).  
'   1234' => 1234 (whitespaces at beginning are removed).  
'      4' => 4    (whitespaces at beginning are removed).  
' 12   4' => 12   (only the leading whitespaces are removed).  
'12345 567 v' => 12345 (digits are appended until a non-digit character occurs).  
'00123'       => 00123 => 123 (0s in the beginning of the numbers are discarded).  
'-23a45 567 v' => -23 (we stopped when 'a' character occured).  
'123 45 567 v' => 123 (we stopped when a space character occured).  
'a+123 bcd 45' => 0   (we stopped when 'a' character occured in the beginning).  
```

```cpp
class Solution {
public:
    int myAtoi(string input) {
        int sign = 1; 
        int result = 0; 
        int index = 0;
        int n = input.size();
        
        // Discard all spaces from the beginning of the input string.
        while (index < n && input[index] == ' ') { 
            index++; 
        }
        
        // sign = +1, if it's positive number, otherwise sign = -1. 
        if (index < n && input[index] == '+') {
            sign = 1;
            index++;
        } else if (index < n && input[index] == '-') {
            sign = -1;
            index++;
        }
        
        // Traverse next digits of input and stop if it is not a digit. 
        // End of string is also non-digit character.
        while (index < n && isdigit(input[index])) {
            int digit = input[index] - '0';

            // Check overflow and underflow conditions. 
            if ((result > INT_MAX / 10) || (result == INT_MAX / 10 && digit > INT_MAX % 10)) { 
                // If integer overflowed return 2^31-1, otherwise if underflowed return -2^31.    
                return sign == 1 ? INT_MAX : INT_MIN;
            }
            
            // Append current digit to the result.
            result = 10 * result + digit;
            index++;
        }
        
        // We have formed a valid number without any overflow/underflow.
        // Return it after multiplying it with its sign.
        return sign * result;
    }
};
```
TC - O(N), SC - O(1)  

# 6) Implement Strstr  
Implement strStr().  
Given two strings needle and haystack, return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.  
Clarification:   
What should we return when needle is an empty string? This is a great question to ask during an interview.  
For the purpose of this problem, we will return 0 when needle is an empty string. This is consistent to C's strstr() and Java's indexOf().  
### Approaches  
Normal brute would take O(m.n) time.  
KMP algorithm. For reference watch Tushar Roy's youtbe videos.  
In KMP we usually use LPS array. which basically means longest prefix which is also the suffix.  
```cpp
class Solution {
public:
    int strStr(string haystack, string needle) {
        int m = haystack.size(), n = needle.size();
        if (!n) {
            return 0;
        }
        vector<int> lps = kmpProcess(needle);
        for (int i = 0, j = 0; i < m;) {
            if (haystack[i] == needle[j]) { 
                i++, j++;
            }
            if (j == n) {
                return i - j;
            }
            if (i < m && haystack[i] != needle[j]) {
                j ? j = lps[j - 1] : i++;
            }
        }
        return -1;
    }
private:
    vector<int> kmpProcess(string needle) {
        int n = needle.size();
        vector<int> lps(n, 0);
        for (int i = 1, len = 0; i < n;) {
            if (needle[i] == needle[len]) {
                lps[i++] = ++len;
            } else if (len) {
                len = lps[len - 1];
            } else {
                lps[i++] = 0;
            }
        }
        return lps;
    }
};
```
TC - O(N+M), SC - O(N)  

# 7) Longest Common prefix  
```cpp
class Solution {
public:
    string longestCommonPrefix(vector<string>& s) {
        int n = s.size();
        if(n == 0) return "";
        int m = s[0].size();
        string ans = "";
        for(int i=0;i<m;i++){
            bool flag = true;
            for(int j=1;j<n;j++)
                if(s[j][i] != s[0][i]) flag = false;
            if(flag == false) break;
            ans += s[0][i];
        }
        return ans;
    }
};
```

# 8) RabinKarp  
![image](https://user-images.githubusercontent.com/56584349/179210508-d0569c49-d41b-4b8b-8476-103043ab85cc.png)  
```cpp
vector<int> rabin_karp(string const& s, string const& t) {
    const int p = 31; 
    const int m = 1e9 + 9;
    int S = s.size(), T = t.size();

    vector<long long> p_pow(max(S, T)); 
    p_pow[0] = 1; 
    for (int i = 1; i < (int)p_pow.size(); i++) 
        p_pow[i] = (p_pow[i-1] * p) % m;

    vector<long long> h(T + 1, 0); 
    for (int i = 0; i < T; i++)
        h[i+1] = (h[i] + (t[i] - 'a' + 1) * p_pow[i]) % m; 
    long long h_s = 0; 
    for (int i = 0; i < S; i++) 
        h_s = (h_s + (s[i] - 'a' + 1) * p_pow[i]) % m; 

    vector<int> occurences;
    for (int i = 0; i + S - 1 < T; i++) { 
        long long cur_h = (h[i+S] + m - h[i]) % m; 
        if (cur_h == h_s * p_pow[i] % m)
            occurences.push_back(i);
    }
    return occurences;
}
```

# 9) Kmp   
![image](https://user-images.githubusercontent.com/56584349/179253714-a0740758-5f65-43e9-890f-1a782e5cfd26.png)  
![image](https://user-images.githubusercontent.com/56584349/179253870-9ae6500c-a5c6-45ad-9f39-607f9a3e610d.png)  
```cpp
vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}
```
![image](https://user-images.githubusercontent.com/56584349/179254508-704f8c1a-4394-486d-b53d-4c21f8603d19.png)  
**KMP for string search code.**  
```cpp
void KMPStringSearch(char* pat, char* str) {
    int M = strlen(pat);
    int N = strlen(str);
  
    int lps[M];
    computeLPSArray(pat, M, lps);
  
    int i = 0; 
    int j = 0;
    while (i < N) {
        if (pat[j] == str[i]) {
            j++;
            i++;
        }
        if (j == M) {
            printf("Found pattern at index %d ", i - j);
            j = lps[j - 1];
        }
        else if (i < N && pat[j] != str[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
}
```

# 10) Minimum characters needed to be inserted in the beginning to make it palindromic  
First we need to find length of longest palindromic subsequence in the given string. And the answer is length - that.  
To find length of longest palindromic subsequence, we can reverse the original string and find LCS of original and reversed.  
```cpp
int minInsertions(string s) {
  return s.size() - longestPalindromeSubseq(s);
}
int dp[501][501] = {};
int longestPalindromeSubseq(string &s) {
  for (int len = 1; len <= s.size(); ++len)
    for (int i = 0; i + len <= s.size(); ++i) 
      dp[i][i + len] = s[i] == s[i + len - 1] ? dp[i + 1][i + len - 1] + (len == 1 ? 1 : 2) 
        : max(dp[i][i + len - 1], dp[i + 1][i + len]);
  return dp[0][s.size()];
}
```

# 11) Check for Anagrams  
```cpp
class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.size() != t.size()) return false;
        vector<int> freq(26,0);
        for(int i=0;i<s.size();i++) freq[s[i] - 'a']++, freq[t[i] - 'a']--;
        for(int i=0;i<26;i++) cout << freq[i] << ' ';
        for(int i=0;i<26;i++) if(freq[i] != 0) return false;
        return true;
    }
};
```

# 12) Count and Say  
```cpp
string countAndSay(int n) {
    if (n == 0) return "";
    string res = "1";
    while (--n) {
        string cur = "";
        for (int i = 0; i < res.size(); i++) {
            int count = 1;
             while ((i + 1 < res.size()) && (res[i] == res[i + 1])){
                count++;    
                i++;
            }
            cur += to_string(count) + res[i];
        }
        res = cur;
    }
    return res;
}
```

# 13) Compare version numbers  
```cpp
int compareVersion(string version1, string version2) {
    int i = 0; 
    int j = 0;
    int n1 = version1.size(); 
    int n2 = version2.size();
    
    int num1 = 0;
    int num2 = 0;
    while(i<n1 || j<n2)
    {
        while(i<n1 && version1[i]!='.'){
            num1 = num1*10+(version1[i]-'0');
            i++;
        }
        while(j<n2 && version2[j]!='.'){
            num2 = num2*10+(version2[j]-'0');;
            j++;
        }
        if(num1>num2) return 1;
        else if(num1 < num2) return -1;
        num1 = 0;
        num2 = 0;
        i++;
        j++;
    }  
   return 0;
}
```
A slightly better bersion using stringstreams  
```cpp
class Solution {
public:
    int compareVersion(string version1, string version2) {
        istringstream ver1(version1 + '.'),ver2(version2 + '.');
        char delimiter = '.';
        int a=0,b=0;
        while(ver1.good() || ver2.good())
        {
            if(ver1.good()) ver1 >> a >> delimiter;
            if(ver2.good()) ver2 >> b >> delimiter;
            if(a > b) return 1;
            else if(a < b) return -1;
            a=0,b=0;
        }
        return 0;
    }
};
```

