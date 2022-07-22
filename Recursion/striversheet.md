# Recursion   
## Striver Sheet  

# 1) Subset Sum : sum of all subsets  
Given an array print all the sum of the subset generated from it, in the increasing order.  
For any element there can be 2 possibilities that it can be picked or not picked.  So here goes a tree by which we can think of recursion.  
```cpp
class Solution {
  public:
    void solve(int ind, vector < int > & arr, int n, vector < int > & ans, int sum) {
      if (ind == n) {
        ans.push_back(sum);
        return;
      }
      //element is picked
      solve(ind + 1, arr, n, ans, sum + arr[ind]);
      //element is not picked
      solve(ind + 1, arr, n, ans, sum);
    }
  vector < int > subsetSums(vector < int > arr, int n) {
    vector < int > ans;
    solve(0, arr, n, ans, 0);
    return ans;
  }
};
```
Atlast you need to sort the array.  
Time Complexity: O(2^n)+O(2^n log(2^n)). Each index has two ways. You can either pick it up or not pick it. So for n index time complexity for O(2^n) and for sorting it will take (2^n log(2^n)).  
SC - O(2^N)   

# 2) Subset II | Print all the unique subsets  
Given an array of integers that may contain duplicates the task is to return all possible subsets. Return only unique subsets and they can be in any order.  
### Approach 1  
Use a similar recursive approach where we have 2 options include/not incldue for an element and then use a set to avoid duplicates.  
Time Complexity: O( 2^n * (k log (x) )). 2^n  for generating every subset and k* log( x)  to insert every combination of average length k in a set of size x. After this, we have to convert the set of combinations back into a list of list /vector of vectors which takes more time.  
Space Complexity:  O(2^n * k) to store every subset of average length k. Since we are initially using a set to store the answer another O(2^n * k) is also used.
### Approach 2  
sort the array and then do recursion.  
```cpp
class Solution {
public:
    vector<vector<int>> subsets;
    vector<int> subset;

    void generate(int i, vector<int>& nums){
        if(i == nums.size()){
            subsets.push_back(subset);
            return; 
        }
        //1. I choose the current number
        subset.push_back(nums[i]);
        generate(i+1,nums);
        subset.pop_back(); //backtracking
        //2. I dont choose the current number [hence I go to the next different number]
        int nextIdx = upper_bound(nums.begin(), nums.end(), nums[i]) - nums.begin();      
        generate(nextIdx, nums);
        return; 
    }


    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
       sort(nums.begin(), nums.end()); 
       generate(0,nums);
       return subsets;
    }
};
```
### Bitmasking with hashing approach  
```cpp
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        unordered_set<string> seen;
        for (int mask = 0, size = 1 << n; mask < size; ++mask) {
            vector<int> subset;
            string hashcode = "";
            for (int i = 0; i < n; i++) {
                int bit = (mask >> i) & 1; // Get i_th bit of mask
                if (bit == 1) {
                    subset.push_back(nums[i]);
                    hashcode += to_string(nums[i]) + ",";
                }
            }
            if (!seen.count(hashcode)) {
                ans.push_back(subset);
                seen.insert(hashcode);
            }
        }
        return ans;
    }
};
```
Time: O(2^N * N), Space: O(2^N)  

# 3) Combination Sum I  
Given an array of distinct integers and a target, you have to return the list of all unique combinations where the chosen numbers sum to target. You may return the combinations in any order.  
The same number may be chosen from the given array an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.  

It is guaranteed that the number of unique combinations that sum up to target is less than 150 combinations for the given input.  
```cpp
class Solution {
  public:
    void findCombination(int ind, int target, vector < int > & arr, vector < vector < int >> & ans, vector < int > & ds) {
      if (ind == arr.size()) {
        if (target == 0) {
          ans.push_back(ds);
        }
        return;
      }
      // pick up the element 
      if (arr[ind] <= target) {
        ds.push_back(arr[ind]);
        findCombination(ind, target - arr[ind], arr, ans, ds);
        ds.pop_back();
      }
      findCombination(ind + 1, target, arr, ans, ds);

    }
  public:
    vector < vector < int >> combinationSum(vector < int > & candidates, int target) {
      vector < vector < int >> ans;
      vector < int > ds;
      findCombination(0, target, candidates, ans, ds);
      return ans;
    }
};
```
```cpp
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> temp;
        sort(candidates.begin(),candidates.end());
        dfs(candidates,target,temp,result,0);
        return result;
    }
    
    void dfs(vector<int> candidates,int target,vector<int> &temp,vector<vector<int>>  &result,int start){
        if(target < 0) return;
        else if(target==0){
            result.push_back(temp);
            return;
        }
        for(int i=start;i<candidates.size() && target >= candidates[i];i++){
            temp.push_back(candidates[i]);
            dfs(candidates,target-candidates[i],temp,result,i);
            temp.pop_back();
        }
    }
};
```
Time Complexity: O(2^t * k) where t is the target, k is the average length  
Reason: Assume if you were not allowed to pick a single element multiple times, every element will have a couple of options: pick or not pick which is 2^n different recursion calls, also assuming that the average length of every combination generated is k. (to put length k data structure into another data structure)  
Why not (2^n) but (2^t) (where n is the size of an array)?  
Assume that there is 1 and the target you want to reach is 10 so 10 times you can “pick or not pick” an element.  
Space Complexity: O(k * x), k is the average length and x is the no. of combinations  

# 4) Combination Sum II  
Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sum to target. Each number in candidates may only be used once in the combination.  

Note: The solution set must not contain duplicate combinations.  
Duplicate combinations in sense if there are three 1's in the array and two 6s. we can take the combination [1,1,6] once but we cannot take the same [1,1,6] with different
indices contributing it to it again.  

```python3
class Solution:
    def combinationSum2(self, candidates: List[int], target: int) -> List[List[int]]:
        result = []
        
        self.dfs(sorted(candidates),target,[],result)
        return result
    
    def dfs(self,cds,target,temp,res):
        if target < 0:
            return
        elif target == 0:
            if temp not in res:
                res.append(temp)
            return
        else:
            for i in range(len(cds)):
                if cds[i] > target:
                    break   
                self.dfs(cds[i+1:],target-cds[i],temp+[cds[i]],res)
                
```
Let's take an example [1,1,2] the below example for the first 1 will do take care of all cases like 1, 1 1, 1 1 2. But whenever we choose to don't pick the first 1 and 
go to second 1. We simply ignore it considering the fact that all the cases will be covered in the case of the first 1 being picked.  
Whenever we use for loop inside a recursion and popping the inserted element after the recursive call implies that we are actually doing the traditional pick/non pick 
approach here. If a recursive call is made it indicated the current element is picked. And after the call we're poppinig that element to take care of the case when element 
is not picked and we simply move on to next index in the for loop.  
```cpp
void findCombination(int ind, int target, vector < int > & arr, vector < vector < int >> & ans, vector < int > & ds) {
  if (target == 0) {
    ans.push_back(ds);
    return;
  }
  for (int i = ind; i < arr.size(); i++) {
    if (i > ind && arr[i] == arr[i - 1]) continue;
    if (arr[i] > target) break;
    ds.push_back(arr[i]);
    findCombination(i + 1, target - arr[i], arr, ans, ds);
    ds.pop_back();
  }
}
vector < vector < int >> combinationSum2(vector < int > & candidates, int target) {
  sort(candidates.begin(), candidates.end());
  vector < vector < int >> ans;
  vector < int > ds;
  findCombination(0, target, candidates, ans, ds);
  return ans;
}
```  
Time Complexity:O(2^n * k)  
Reason: Assume if all the elements in the array are unique then the no. of subsequence you will get will be O(2^n). we also add the ds to our ans when we reach the base case that will take “k”//average space for the ds.  
Space Complexity:O(k * x)  
Reason: if we have x combinations then space will be x * k where k is the average length of the combination.  

# 5) Palindrome Partitioning  
You are given a string s, partition it in such a way that every substring is a palindrome. Return all such palindromic partitions of s.  
Note: A palindrome string is a string that reads the same backward as forward.  
```cpp
class Solution {
private: 
    bool isPalindrome(string s){
        for(int i=0;i<s.size()/2;i++){
            if(s[i] != s[s.size()-1-i]) return false;
        }
        return true;
    }
    
    void recurse(string s,int start, vector<string> &tempList, vector<vector<string>> &store){
        if(start == s.size())
            store.push_back(tempList);
        for(int end = start;end < s.size();end++){
            if(isPalindrome(s.substr(start,end-start+1))){
                tempList.push_back(s.substr(start,end-start+1));
                recurse(s,end+1,tempList,store);
                tempList.pop_back();
            }
        }
    }
    
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> store;
        vector<string> temp;
        recurse(s,0,temp,store);
        return store;
    }
};
```
Time Complexity: O( (2^n) * k * (n/2) )  
Reason: O(2^n) to generate every substring and O(n/2)  to check if the substring generated is a palindrome. O(k) is for inserting the palindromes in another data structure, where k  is the average length of the palindrome list.  
Space Complexity: O(k * x)  
Reason: The space complexity can vary depending upon the length of the answer. k is the average length of the list of palindromes and if we have x such list of palindromes in our final answer. The depth of the recursion tree is n, so the auxiliary space required is equal to the O(n).  

We could actually improve this by storing a 2d dp array to check whether string from index i to j is a palindrome in dp[i][j].  

# 6) K-th Permutation Sequence  
Given N and K, where N is the sequence of numbers from 1 to N([1,2,3….. N]) find the Kth permutation sequence.  
One way is to get all permutations using recursion and sort them.  
Time complexity: O(N! * N) +O(N! Log N!)  
Reason:  The recursion takes O(N!)  time because we generate every possible permutation and another O(N)  time is required to make a deep copy and store every sequence in the data structure. Also, O(N! Log N!)  time required to sort the data structure  
Space complexity: O(N)   
Reason: Result stored in a vector, we are auxiliary space taken by recursion  
### Optimal approach  
We first decide which number should come in the first position. Then the problem is reduced to n-1 numbers and n-1 positions.  
Let's consider an example where the  length of the permutation is 4. Total possible permutations are 24.  
The 0th – 5th permutation will start with 1   
The 6th – 11th permutation will start with 2  
The 12th – 17th permutation will start with 3   
The 18th – 23rd permutation will start with 4.  
If given K =17, as we are considering 0 based indexing we take it as k = 16. And 16/6 = 2. So it will lie in 2nd block. And as 16%6 is 4, it is the 4th sequence in the 2nd block.  
Our new search space comprises three elements {1,2,4} where K = 4 . Using the previous technique we can consider the second position to be occupied can be any one of these 3 numbers. Again one block can start with 1, another can start with 2 and the last one can start with 4 . Since one position is fixed, the remaining two numbers of each block can form 2! = 2  sequences. In sorted order :  
The 0th – 1st sequence starts with 1   
The 2nd – 3rd sequence starts with 2   
The 4th – 5th sequence starts with 4  
The 4th permutation will lie in 4/2 - 2nd block and thus it takes the number 4. And as 4%2 = 0, it's 0th sequence in 2nd block.  
And if we repeat the process we get the answer as 3 4 1 2.  
```cpp
class Solution {
  public:
    string getPermutation(int n, int k) {
      int fact = 1;
      vector < int > numbers;
      for (int i = 1; i < n; i++) {
        fact = fact * i;
        numbers.push_back(i);
      }
      numbers.push_back(n);
      string ans = "";
      k = k - 1;
      while (true) {
        ans = ans + to_string(numbers[k / fact]);
        numbers.erase(numbers.begin() + k / fact);
        if (numbers.size() == 0) {
          break;
        }

        k = k % fact;
        fact = fact / numbers.size();
      }
      return ans;
    }
};
```
TC - O(N^2), SC -O(N)    

# 7) Print all permutations of string/array  
```cpp
class Solution {
  private:
    void recurPermute(vector < int > & ds, vector < int > & nums, vector < vector < int >> & ans, int freq[]) {
      if (ds.size() == nums.size()) {
        ans.push_back(ds);
        return;
      }
      for (int i = 0; i < nums.size(); i++) {
        if (!freq[i]) {
          ds.push_back(nums[i]);
          freq[i] = 1;
          recurPermute(ds, nums, ans, freq);
          freq[i] = 0;
          ds.pop_back();
        }
      }
    }
  public:
    vector < vector < int >> permute(vector < int > & nums) {
      vector < vector < int >> ans;
      vector < int > ds;
      int freq[nums.size()];
      for (int i = 0; i < nums.size(); i++) freq[i] = 0;
      recurPermute(ds, nums, ans, freq);
      return ans;
    }
};
```
TC - O(N! * N), SC - O(N)  
```cpp
class Solution {
  private:
    void recurPermute(int index, vector < int > & nums, vector < vector < int >> & ans) {
      if (index == nums.size()) {
        ans.push_back(nums);
        return;
      }
      for (int i = index; i < nums.size(); i++) {
        swap(nums[index], nums[i]);
        recurPermute(index + 1, nums, ans);
        swap(nums[index], nums[i]);
      }
    }
  public:
    vector < vector < int >> permute(vector < int > & nums) {
      vector < vector < int >> ans;
      recurPermute(0, nums, ans);
      return ans;
    }
};
```
TC - O(N! * N), SC - O(1)   

# 8) N queens problem  
The n-queens is the problem of placing n queens on n × n chessboard such that no two queens can attack each other. Given an integer n, return all distinct solutions to the n -queens puzzle. Each solution contains a distinct boards configuration of the queen’s placement, where ‘Q’ and ‘.’ indicate queen and empty space respectively.  

### Approach 1  
```cpp
class Solution {
  public:
    bool isSafe1(int row, int col, vector < string > board, int n) {
      // check upper element
      int duprow = row;
      int dupcol = col;

      while (row >= 0 && col >= 0) {
        if (board[row][col] == 'Q')
          return false;
        row--;
        col--;
      }

      col = dupcol;
      row = duprow;
      while (col >= 0) {
        if (board[row][col] == 'Q')
          return false;
        col--;
      }

      row = duprow;
      col = dupcol;
      while (row < n && col >= 0) {
        if (board[row][col] == 'Q')
          return false;
        row++;
        col--;
      }
      return true;
    }

  public:
    void solve(int col, vector < string > & board, vector < vector < string >> & ans, int n) {
      if (col == n) {
        ans.push_back(board);
        return;
      }
      for (int row = 0; row < n; row++) {
        if (isSafe1(row, col, board, n)) {
          board[row][col] = 'Q';
          solve(col + 1, board, ans, n);
          board[row][col] = '.';
        }
      }
    }

  public:
    vector < vector < string >> solveNQueens(int n) {
      vector < vector < string >> ans;
      vector < string > board(n);
      string s(n, '.');
      for (int i = 0; i < n; i++) {
        board[i] = s;
      }
      solve(0, board, ans, n);
      return ans;
    }
};
```
TC - O(N * N!), SC - O(N ^ 2)  

### Approach 2
Optimisin the issafe function. To check the left row, we use a vector named row and check whether a element is alread filled in that row.  
Similarly we use arrays of sizes 2* n -1 to check the upper and lower diagnols and the indices we use to acccess are row+col, n- 1 + col-row.  
![image](https://user-images.githubusercontent.com/56584349/180376995-54bca4a7-2959-470d-ae04-607488c5b13f.png)  
![image](https://user-images.githubusercontent.com/56584349/180377032-13e3b63c-213b-4070-bc77-bff0b19fa4b9.png)  
```cpp
class Solution {
  public:
    void solve(int col, vector < string > & board, vector < vector < string >> & ans, vector < int > & leftrow, vector < int > & upperDiagonal, vector < int > & lowerDiagonal, int n) {
      if (col == n) {
        ans.push_back(board);
        return;
      }
      for (int row = 0; row < n; row++) {
        if (leftrow[row] == 0 && lowerDiagonal[row + col] == 0 && upperDiagonal[n - 1 + col - row] == 0) {
          board[row][col] = 'Q';
          leftrow[row] = 1;
          lowerDiagonal[row + col] = 1;
          upperDiagonal[n - 1 + col - row] = 1;
          solve(col + 1, board, ans, leftrow, upperDiagonal, lowerDiagonal, n);
          board[row][col] = '.';
          leftrow[row] = 0;
          lowerDiagonal[row + col] = 0;
          upperDiagonal[n - 1 + col - row] = 0;
        }
      }
    }

  public:
    vector < vector < string >> solveNQueens(int n) {
      vector < vector < string >> ans;
      vector < string > board(n);
      string s(n, '.');
      for (int i = 0; i < n; i++) {
        board[i] = s;
      }
      vector < int > leftrow(n, 0), upperDiagonal(2 * n - 1, 0), lowerDiagonal(2 * n - 1, 0);
      solve(0, board, ans, leftrow, upperDiagonal, lowerDiagonal, n);
      return ans;
    }
};
```
TC - O(N * N!), SC - O(N)  

# 9) Sudoku solver  
Given a 9×9 incomplete sudoku, solve it such that it becomes valid sudoku. Valid sudoku has the following properties.  
1) All the rows should be filled with numbers(1 – 9) exactly once.  
2) All the columns should be filled with numbers(1 – 9) exactly once.  
3) Each 3×3 submatrix should be filled with numbers(1 – 9) exactly once.  
     
Note: Character ‘.’ indicates empty cell.  
```cpp
bool isValid(vector < vector < char >> & board, int row, int col, char c) {
  for (int i = 0; i < 9; i++) {
    if (board[i][col] == c)
      return false;

    if (board[row][i] == c)
      return false;

    if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c)
      return false;
  }
  return true;
}

bool solve(vector < vector < char >> & board) {
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[0].size(); j++) {
      if (board[i][j] == '.') {
        for (char c = '1'; c <= '9'; c++) {
          if (isValid(board, i, j, c)) {
            board[i][j] = c;

            if (solve(board))
              return true;
            else
              board[i][j] = '.';
          }
        }

        return false;
      }
    }
  }
  return true;
}
```
TC - O(9^(N^2)), SC - O(1)   

# 10) M coloring problem  
Given an undirected graph and a number m, determine if the graph can be colored with at most m colors such that no two adjacent vertices of the graph are colored with the same color.  
Trying every color from 1 to m with the help of a for a loop.  
Is safe function returns true if it is possible to color it with that color i.e none of the adjacent nodes have the same color.  
Color it with color i then call the recursive function for the next node if it returns true we will return true.   
And If it is false then take off the color.  
Now if we have tried out every color from 1 to m and it was not possible to color it with any of the m colors then return false.  
```cpp
bool isSafe(int node, int color[], bool graph[101][101], int n, int col) {
  for (int k = 0; k < n; k++) {
    if (k != node && graph[k][node] == 1 && color[k] == col) {
      return false;
    }
  }
  return true;
}
bool solve(int node, int color[], int m, int N, bool graph[101][101]) {
  if (node == N) {
    return true;
  }

  for (int i = 1; i <= m; i++) {
    if (isSafe(node, color, graph, N, i)) {
      color[node] = i;
      if (solve(node + 1, color, m, N, graph)) return true;
      color[node] = 0;
    }

  }
  return false;
}

//Function to determine if graph can be coloured with at most M colours such
//that no two adjacent vertices of graph are coloured with same colour.
bool graphColoring(bool graph[101][101], int m, int N) {
  int color[N] = {
    0
  };
  if (solve(0, color, m, N, graph)) return true;
  return false;
}
```
Time Complexity: O( N^M) (n raised to m), Space Complexity: O(N)  

# 11) Rat in a maze  

```cpp
class Solution {
  void solve(int i, int j, vector < vector < int >> & a, int n, vector < string > & ans, string move,
    vector < vector < int >> & vis, int di[], int dj[]) {
    if (i == n - 1 && j == n - 1) {
      ans.push_back(move);
      return;
    }
    string dir = "DLRU";
    for (int ind = 0; ind < 4; ind++) {
      int nexti = i + di[ind];
      int nextj = j + dj[ind];
      if (nexti >= 0 && nextj >= 0 && nexti < n && nextj < n && !vis[nexti][nextj] && a[nexti][nextj] == 1) {
        vis[i][j] = 1;
        solve(nexti, nextj, a, n, ans, move + dir[ind], vis, di, dj);
        vis[i][j] = 0;
      }
    }

  }
  public:
    vector < string > findPath(vector < vector < int >> & m, int n) {
      vector < string > ans;
      vector < vector < int >> vis(n, vector < int > (n, 0));
      int di[] = {
        +1,
        0,
        0,
        -1
      };
      int dj[] = {
        0,
        -1,
        1,
        0
      };
      if (m[0][0] == 1) solve(0, 0, m, n, ans, "", vis, di, dj);
      return ans;
    }
};
```
Time Complexity: O(4^(m* n)), because on every cell we need to try 4 different directions.  
Space Complexity:  O(m* n) ,Maximum Depth of the recursion tree(auxiliary space).  

# 12) Word Break II | Print all possible ways  
You are given a non-empty string S containing no spaces’ and a dictionary of non-empty strings (say the list of words). You are supposed to construct and return all possible sentences after adding spaces in the originally given string ‘S’, such that each word in a sentence exists in the given dictionary.  
Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]  
Output: ["cats and dog","cat sand dog"]  

```cpp
class Solution {
    public:
        vector<string> wordBreak(string s, vector<string>& wordDict) 
        {
            int max_len = 0;
            unordered_set<string> dict;
            for(string& str : wordDict)
            {
                dict.insert(str);
                max_len = max(max_len, (int)str.length());
            }

            unordered_map<int, vector<string>> mp;
            return break_word(s, 0, dict, max_len, mp);
        }

    protected:
        vector<string> break_word(  const string& s, int n, unordered_set<string>& dict, 
                                    int max_len, unordered_map<int, vector<string>>& mp)
        {
            if(mp.count(n)) return mp[n];

            string str;
            for(int i = n; i < s.length() && str.length() <= max_len; ++i)
            {
                str += s[i];
                if(dict.count(str))
                {
                    if(i == s.length()-1)
                        mp[n].push_back(str);
                    else
                    {
                        vector<string> vs = break_word(s, i+1, dict, max_len, mp);
                        for(auto& a : vs) mp[n].push_back(str + " " + a);
                    }
                }
            }
            return mp[n];
        }
};
```
We can also dare to use trie to solve this problem  


