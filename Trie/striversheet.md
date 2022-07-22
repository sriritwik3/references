# Trie  
## Striver sheet  

# 1) Implement Trie  
Implementing insertion, search, and startWith operations in a trie or prefix-tree.  
Implementation:    
Type 1: To insert a string “word” in Trie.                             
Type 2: To check if the string “word” is present in Trie or not.  
Type 3: To check if there is any string in the Trie that starts with the given prefix string “word”.  

```cpp
struct Node {
    Node *links[26];
    bool flag = false;
    bool hasKey(char ch){
        return (links[ch-'a'] != NULL);
    }
    Node *get(char ch){
        return links[ch-'a'];
    }
    void put(char ch){
        links[ch-'a'] = new Node();
    }
    bool isEnd(){
        return flag;
    }
    void setEnd(){
        flag = true;
    }
};


class Trie {
public:
    Node *root;
    Trie() {
        root = new Node();
    }
    
    void insert(string word) {
        Node *node = root;
        for(int i=0;i<word.size();i++){
            if(!node->hasKey(word[i]))
                node->put(word[i]);
            node = node->get(word[i]);
        }
        node->setEnd();
    }
    
    bool search(string word) {
        Node *node = root;
        for(int i=0;i<word.size();i++){
            if(!node->hasKey(word[i])) return false;
            node = node->get(word[i]);
        }
        if(node->isEnd()) return true;
        return false;
    }
    
    bool startsWith(string prefix) {
         Node *node = root;
        for(int i=0;i<prefix.size();i++){
            if(!node->hasKey(prefix[i])) return false;
            node = node->get(prefix[i]);
        }
        return true;
    }
};

```

# 2) Implement Trie II  
Implement a data structure ”TRIE” from scratch. Complete some functions.  
1) Trie(): Initialize the object of this “TRIE” data structure.  
2) insert(“WORD”): Insert the string “WORD”  into this “TRIE” data structure.  
3) countWordsEqualTo(“WORD”): Return how many times this “WORD” is present in this “TRIE”.  
4) countWordsStartingWith(“PREFIX”): Return how many words are there in this “TRIE” that have the string “PREFIX” as a prefix.  
5) erase(“WORD”): Delete this string “WORD” from the “TRIE”.  
Note:  
1. If erase(“WORD”) function is called then it is guaranteed that the “WORD” is present in the “TRIE”.  
2. If you are going to use variables with dynamic memory allocation then you need to release the memory associated with them at the end of your solution.  

```cpp
struct Node {
  Node * links[26];
  int cntEndWith = 0;
  int cntPrefix = 0;

  bool containsKey(char ch) {
    return (links[ch - 'a'] != NULL);
  }
  Node * get(char ch) {
    return links[ch - 'a'];
  }
  void put(char ch, Node * node) {
    links[ch - 'a'] = node;
  }
  void increaseEnd() {
    cntEndWith++;
  }
  void increasePrefix() {
    cntPrefix++;
  }
  void deleteEnd() {
    cntEndWith--;
  }
  void reducePrefix() {
    cntPrefix--;
  }
  int getEnd() {
    return cntEndWith;
  }
  int getPrefix() {
    return cntPrefix;
  }
};
class Trie {
  private:
    Node * root;

  public:
    /** Initialize your data structure here. */
    Trie() {
      root = new Node();
    }

  /** Inserts a word into the trie. */
  void insert(string word) {
    Node * node = root;
    for (int i = 0; i < word.length(); i++) {
      if (!node -> containsKey(word[i])) {
        node -> put(word[i], new Node());
      }
      node = node -> get(word[i]);
      node -> increasePrefix();
    }
    node -> increaseEnd();
  }

 int countWordsEqualTo(string &word)
    {
        Node *node = root;
        for (int i = 0; i < word.length(); i++)
        {
            if (node->containsKey(word[i]))
            {
                node = node->get(word[i]);
            }
            else
            {
                return 0;
            }
        }
        return node->getEnd();
    }


  int countWordsStartingWith(string & word) {
    Node * node = root;
    for (int i = 0; i < word.length(); i++) {
      if (node -> containsKey(word[i])) {
        node = node -> get(word[i]);
      } else {
        return 0;
      }
    }
    return node -> getPrefix();
  }

  void erase(string & word) {
    Node * node = root;
    for (int i = 0; i < word.length(); i++) {
      if (node -> containsKey(word[i])) {
        node = node -> get(word[i]);
        node -> reducePrefix();
      } else {
        return;
      }
    }
    node -> deleteEnd();
  }
};
```

# 3) Longest string with all prefixes  
Insert all strings into the trie. Iterate through all strings and keep track of the longest prefix that is also the part of the trie.  
TC, SC - O(N * Len)  

# 4) Number of distinct substrings in a string  
Given a string of alphabetic characters. Return the count of distinct substrings of the string(including the empty string) using the Trie data structure.  
The basic intuition is to generate all the substrings and store them in the trie along with its creation. If a substring already exists in the trie then we can ignore, else we can make an entry and increase the count. Let’s see a detailed explanation.  
```cpp
struct Node {
  Node * links[26];

  bool containsKey(char ch) {
    return (links[ch - 'a'] != NULL);
  }

  Node * get(char ch) {
    return links[ch - 'a'];
  }

  void put(char ch, Node * node) {
    links[ch - 'a'] = node;
  }
};

int countDistinctSubstrings(string & s) {
  Node * root = new Node();
  int count = 0;
  int n = s.size();
  for (int i = 0; i < n; i++) {
    Node * node = root;
    for (int j = i; j < n; j++) {
      if (!node -> containsKey(s[j])) {
        node -> put(s[j], new Node());
        count++;
      }
      node = node -> get(s[j]);
    }
  }
  return count + 1;
}
```
Time Complexity: O(n^2), because we have to go through the entire string for all possible different starting points in order to generate all the substrings.  
Space Complexity: O(n^2), because in the worst case, all the substrings can be distinct and there will be a node for every substring. Number of substrings of a string of length n is (n * (n + 1) / 2). Hence in the worst case, space complexity will be O(n^2).  

# 5) Power set  
### Using recursion  
```cpp
void solve(int i, string s, string &f) {
	if (i == s.length()) {
		cout << f << " ";
		return;
	}
	f = f + s[i];
	solve(i + 1, s,  f);
	f.pop_back();
	solve(i + 1, s,  f);
}
```
Time Complexity: O(2^n) 
Space Complexity: O(n), recursion stack.
### Bit manipulation  
```cpp
vector<string> AllPossibleStrings(string s) {
	int n = s.length();
	vector<string>ans;
	for (int num = 0; num < (1 << n); num++) {
		string sub = "";
		for (int i = 0; i < n; i++) {
			//check if the ith bit is set or not
			if (num & (1 << i)) {
				sub += s[i];
			}
		}
		if (sub.length() > 0) {
			ans.push_back(sub);
		}
	}
	sort(ans.begin(), ans.end());
	return ans;
}
```
Time Complexity: O(2^n * n)  
Reason: O(2^n) for the outer for loop and O(n) for the inner for loop.  
Space Complexity: O(1)   

# 6) Maximum XOR of 2 numbers in an array  
You are given two arrays of non-negative integers say ‘arr1’ and ‘arr2’ of sizes N and M respectively. Find the maximum value of ( ‘A’ xor ‘B’ ) where ‘A’ and ‘B’ are any elements from ‘arr1’ and ‘arr2’ respectively and ‘xor’ represents the bitwise xor operation. Maximum XOR of Two Numbers in an Array.  
### Approach  
Normally, when we only have an element x and we need to find the maximum xor with x from all the array elements. We follow the following approach.  
We go with binary format of all the numbers and insert them in binary form into a trie. Now we also get the binary form of x. Normally to get the maximum xor, we need
to have odd number of 1's. So if a particular bit is 1 in x we check for a 0 in the trie and viceversa. If found well and good else go with the available one.  
Now using this concept let’s solve the actual problem.  
arr1: push all the elements into the trie.    
arr2: Treat every element of arr2 as x and find the MaxXOR and consider the maximum of all.  
```cpp
struct Node {
    Node *links[2];
    bool flag = false;
    bool hasKey(int a){
        return (links[a] != NULL);
    }
    Node *get(int a){
        return links[a];
    }
    void put(int a){
        links[a] = new Node();
    }
};

class Trie {
    Node *root;
    public : 
    Trie(){
        root = new Node();
    }
    void insert(int num){
        Node *node = root;
        for(int i=31;i>=0;i--){
            if(!node->hasKey((num >> i) & 1))
                node->put((num >> i) & 1);
            node = node->get((num >> i)&1);
        }
    }
    int findMax(int x){
        int ans = 0;
        Node *node = root;
        for(int i=31;i>=0;i--){
            int bit = (x >> i)&1;
            if(node->hasKey(!bit)){
                ans |= (1 << i);
                node = node->get(!bit);
            } else node = node->get(bit);
        }
        return ans;
    }
};


class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        Trie* trie = new Trie();
        for(auto i:nums) trie->insert(i);
        int ans = 0;
        for(int i=0;i<nums.size();i++)
            ans = max(ans, trie->findMax(nums[i]));
        return ans;
    }
};
```
The code is for the case when both the numbers are from same array.  
Time Complexity: O(N* 32) + O(M* 32)  
Reason: For inserting all the elements of arr1 into the trie take O(N* 32) [32 Bit] and O(M* 32) for finding the maxXOR for every element of arr2.  
Space Complexity: O(N* 32)   
Reason: Since we are inserting all the elements of arr1 into trie where every element is of size 32 bit but the space complexity will be less than O(N* 32) because they might have overlapped.  
### Bitmask approach  
```java
  public int findMaximumXOR(int[] nums) {
        int maxResult = 0; 
        int mask = 0;
        /*The maxResult is a record of the largest XOR we got so far. if it's 11100 at i = 2, it means 
        before we reach the last two bits, 11100 is the biggest XOR we have, and we're going to explore
        whether we can get another two '1's and put them into maxResult
        
        This is a greedy part, since we're looking for the largest XOR, we start 
        from the very begining, aka, the 31st postition of bits. */
        for (int i = 31; i >= 0; i--) {
            
            //The mask will grow like  100..000 , 110..000, 111..000,  then 1111...111
            //for each iteration, we only care about the left parts
            mask = mask | (1 << i);
            
            Set<Integer> set = new HashSet<>();
            for (int num : nums) {
                
/*                we only care about the left parts, for example, if i = 2, then we have
                {1100, 1000, 0100, 0000} from {1110, 1011, 0111, 0010}*/
                int leftPartOfNum = num & mask;
                set.add(leftPartOfNum);
            }
            
            // if i = 1 and before this iteration, the maxResult we have now is 1100, 
            // my wish is the maxResult will grow to 1110, so I will try to find a candidate
            // which can give me the greedyTry;
            int greedyTry = maxResult | (1 << i);
            
            for (int leftPartOfNum : set) {
                //This is the most tricky part, coming from a fact that if a ^ b = c, then a ^ c = b;
                // now we have the 'c', which is greedyTry, and we have the 'a', which is leftPartOfNum
                // If we hope the formula a ^ b = c to be valid, then we need the b, 
                // and to get b, we need a ^ c, if a ^ c exisited in our set, then we're good to go
                int anotherNum = leftPartOfNum ^ greedyTry;
                if (set.contains(anotherNum)) {
                    maxResult= greedyTry;
                    break;
                }
            }
            
            // If unfortunately, we didn't get the greedyTry, we still have our max, 
            // So after this iteration, the max will stay at 1100.
        }
        
        return maxResult;
    }
```
TC - O(N)  

# 7) Maximum XOR with an element from the array  
You are given an array nums consisting of non-negative integers. You are also given a queries array, where queries[i] = [xi, mi].  
The answer to the ith query is the maximum bitwise XOR value of xi and any element of nums that does not exceed mi. In other words, the answer is max(nums[j] XOR xi) for all j such that nums[j] <= mi. If all elements in nums are larger than mi, then the answer is -1.  
Return an integer array answer where answer.length == queries.length and answer[i] is the answer to the ith query.  
### Approach  
We sort the array first. And then we also sort all the queries(offline approach) based on the value of mi.  
We only insert those elements into the trie which are currently less than xi of the present query.  
```cpp
struct Node {
    Node *links[2];
    bool flag = false;
    bool hasKey(int a){
        return (links[a] != NULL);
    }
    Node *get(int a){
        return links[a];
    }
    void put(int a){
        links[a] = new Node();
    }
};

class Trie {
    Node *root;
    public : 
    Trie(){
        root = new Node();
    }
    void insert(int num){
        Node *node = root;
        for(int i=31;i>=0;i--){
            if(!node->hasKey((num >> i) & 1))
                node->put((num >> i) & 1);
            node = node->get((num >> i)&1);
        }
    }
    int findMax(int x){
        int ans = 0;
        Node *node = root;
        for(int i=31;i>=0;i--){
            int bit = (x >> i)&1;
            if(node->hasKey(!bit)){
                ans |= (1 << i);
                node = node->get(!bit);
            } else node = node->get(bit);
        }
        return ans;
    }
};

class Solution {
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        Trie* trie = new Trie();
        vector<pair<int, pair<int,int>>> offlineQueries;
        sort(nums.begin(), nums.end());
        vector<int> ans(queries.size(),0);
        for(int i=0;i<queries.size();i++)
            offlineQueries.push_back({queries[i][1], {queries[i][0], i}});
        sort(offlineQueries.begin(), offlineQueries.end());
        int index = 0;
        for(int i=0;i<queries.size();i++){
            while(index < nums.size() && nums[index] <= offlineQueries[i].first)
                trie->insert(nums[index]),index++;
            if(index == 0) ans[offlineQueries[i].second.second] = -1;
            else ans[offlineQueries[i].second.second] = trie->findMax(offlineQueries[i].second.first);
        }
        return ans;
    }
};
```
TC - O(QLOGQ + NLOGN + 32 * N)  
