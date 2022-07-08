# Minimum Insertions/deletions to convert str1 to str2  
**[Link](https://takeuforward.org/data-structure/minimum-insertions-deletions-to-convert-string-dp-30/)**  
We are given two strings, str1 and str2. We are allowed the following operations:  
Delete any number of characters from string str1.  
Insert any number of characters in string str1.  
We need to tell the minimum operations required to convert str1 to str2.  

## Solution  
Minimum Operations required = (n – k) + (m – k)  

Here n and m are the length of str1 and str2 respectively and k is the length of the longest common subsequence of str1 and str2.  
- We first find LCS and keep all those characters intact.  
- Then remove the remaining characters from str1.  => (n-k)  
- Then finally add the characters which are present in str2 and not in str1. => (m-k)  
