# Stacks and Queues  
## Striver Sheet  

# 1) Implementation of stack using arrays  
```cpp
class Stack {
  int size;
  int * arr;
  int top;
  public:
    Stack() {
      top = -1;
      size = 1000;
      arr = new int[size];
    }
  void push(int x) {
    top++;
    arr[top] = x;
  }
  int pop() {
    int x = arr[top];
    top--;
    return x;
  }
  int Top() {
    return arr[top];
  }
  int Size() {
    return top + 1;
  }
};
```  

# 2) Implement Queue using arrays  
 We try to fill the array in the circular manner. So we do mod addition. Meanwhile take care of some of the corner cases.  
 ```cpp
class Queue {
  int * arr;
  int start, end, currSize, maxSize;
  public:
    Queue() {
      arr = new int[16];
      start = -1;
      end = -1;
      currSize = 0;
    }

  Queue(int maxSize) {
    ( * this).maxSize = maxSize;
    arr = new int[maxSize];
    start = -1;
    end = -1;
    currSize = 0;
  }
  void push(int newElement) {
    if (currSize == maxSize) {
      cout << "Queue is full\nExiting..." << endl;
      exit(1);
    }
    if (end == -1) {
      start = 0;
      end = 0;
    } else
      end = (end + 1) % maxSize;
    arr[end] = newElement;
    cout << "The element pushed is " << newElement << endl;
    currSize++;
  }
  int pop() {
    if (start == -1) {
      cout << "Queue Empty\nExiting..." << endl;
    }
    int popped = arr[start];
    if (currSize == 1) {
      start = -1;
      end = -1;
    } else
      start = (start + 1) % maxSize;
    currSize--;
    return popped;
  }
  int top() {
    if (start == -1) {
      cout << "Queue is Empty" << endl;
      exit(1);
    }
    return arr[start];
  }
  int size() {
    return currSize;
  }

};
```  
Time Complexity:
pop function: O(1) 
push function: O(1) 
top function: O(1) 
size function: O(1)   
Space Complexity: 
Whole Queue: O(n)  

# 3) Implement Stack using queues  
### Using 2 queues  
push - Add x to Q2. Add all elements of Q1 to Q2. Swap Q1 and Q2. This way the most recent element stands first.  
pop - remove element from Q1.  
```
void push(int x){
    Q2.push(x);
    while(!Q1.empty()){
        Q2.push(Q1.front());
        Q1.pop();
    }
    swap(Q1,Q2);
}

void pop(){
    Q1.pop();
}  
```  
### Using single queue  
push - push the element in the queue and size-1 times pop the top element and again push that element back in the queue. In this way most recent element will be on the top.  
```cpp
class Stack {
  queue < int > q;
  public:
    void Push(int x) {
      int s = q.size();
      q.push(x);
      for (int i = 0; i < s; i++) {

        q.push(q.front());
        q.pop();
      }
    }
  int Pop() {
    int n = q.front();
    q.pop();
    return n;
  }
  int Top() {
    return q.front();
  }
  int Size() {
    return q.size();
  }
};
````
TC, SC - O(N)  

# 4)Implement Queue using stack  
### using 2 stacks when push operation is O(N) and pop is O(1)    
use 2 stacks s1 and s2. Whenever we have to push an element pop all elements from s1 and push to s2. Insert element in s1. And then bring back all elements to s1. 
```cpp
void Push(int data) {
    // Pop out all elements from the stack input
    while (!input.empty()) {
      output.push(input.top());
      input.pop();
    }
    // Insert the desired element in the stack input
    cout << "The element pushed is " << data << endl;
    input.push(data);
    // Pop out elements from the stack output and push them into the stack input
    while (!output.empty()) {
      input.push(output.top());
      output.pop();
    }
  }
  // Pop the element from the Queue
  int Pop() {
    if (input.empty()) {
      cout << "Stack is empty";
      exit(0);
    }
    int val = input.top();
    input.pop();
    return val;
  }
  // Return the Topmost element from the Queue
  int Top() {
    if (input.empty()) {
      cout << "Stack is empty";
      exit(0);
    }
    return input.top();
  }
  // Return the size of the Queue
  int size() {
    return input.size();
  }
```

### Using 2 stacks when push is O(1) and pop is amortised O(1)  
push elements into s1. whenever top or pop operation has to be done check whether s2 is empty or not. if empty bring elements from s1 to s2. Else pop from s2 itself.  
```cpp
class MyQueue {
  public:
    stack < int > input, output;
  /** Initialize your data structure here. */
  MyQueue() {

  }

  /** Push element x to the back of queue. */
  void push(int x) {
    cout << "The element pushed is " << x << endl;
    input.push(x);
  }

  /** Removes the element from in front of queue and returns that element. */
  int pop() {
    // shift input to output 
    if (output.empty())
      while (input.size())
        output.push(input.top()), input.pop();

    int x = output.top();
    output.pop();
    return x;
  }

  /** Get the front element. */
  int top() {
    // shift input to output 
    if (output.empty())
      while (input.size())
        output.push(input.top()), input.pop();
    return output.top();
  }

  int size() {
    return (output.size() + input.size()); 
  }

};
```  
# 5) Check for balanced parentheses  
Check Balanced Parentheses. Given string str containing just the characters ‘(‘, ‘)’, ‘{‘, ‘}’, ‘[‘ and ‘]’, check if the input string is valid and return true if the string is balanced otherwise return false.  
Note: string str is valid if:   
Open brackets must be closed by the same type of brackets.  
Open brackets must be closed in the correct order.  
```cpp
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        bool flag = true;
        for(int i=0;i<s.size();i++){
            if(s[i] == '(' || s[i] == '[' || s[i] == '{') st.push(s[i]);
            else{
                if(s[i] == ')'){
                    if(!st.empty() && st.top() == '(') st.pop();
                    else {
                        flag = false;
                        break;
                    }
                }
                else if(s[i] == ']'){
                    if( !st.empty() && st.top() == '[') st.pop();
                    else {
                        flag = false;
                        break;
                    }
                }
                else{
                    if( !st.empty() && st.top() == '{') st.pop();
                    else {
                        flag = false;
                        break;
                    }
                }
            }
        }
        if(!st.empty()) flag = false;
        return flag;
    }
};
```
TC, SC - O(N)  

# 6) Next greater element in a circular array  
For a normal array the approach would be like this - we come from the last element of the array. insert it into the stack and for the ith element from the last
we see if the top element of stack is lesser than that of the i'th element if it is, we pop it out. we pop all the elements unless they are larger than the current element.  
So for every element, the top most element at the stack would be the next greater element.  
So for a circular array, we would rather repeat the array twice and do the similar process.  
```cpp
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        stack<int> s;
        int n = nums.size();
        vector<int> ans(n,-1);
        for(int i = 2*n-1;i>=0;i--){
            while(!s.empty() && s.top() <= nums[i%n]) s.pop();
            if(i < n && !s.empty()) ans[i] = s.top();
            s.push(nums[i%n]);
        }
        return ans;
    }
};
```
TC,SC - O(N)  

# 7) Sort a stack  
### Approach 1 - using another stack  
- Create a temporary stack say tmpStack.
- While input stack is NOT empty do this: 
   - Pop an element from input stack call it temp
   - while temporary stack is NOT empty and top of temporary stack is greater than temp, 
   - pop from temporary stack and push it to the input stack
   - push temp in temporary stack
- The sorted numbers are in tmpStack.  
```cpp
stack<int> sortStack(stack<int> &input)
{
    stack<int> tmpStack;
    while (!input.empty())
    {
        int tmp = input.top();
        input.pop();
        while (!tmpStack.empty() && tmpStack.top() > tmp)
        {
            input.push(tmpStack.top());
            tmpStack.pop();
        }
        tmpStack.push(tmp);
    }
    return tmpStack;
}
```
TC - O(N^2), SC - O(N)  
### Approach 2 - using recursion  
![image](https://user-images.githubusercontent.com/56584349/179973740-ab32f1b4-55ef-459c-b0a6-493840a55076.png)   
TC - O(N^2), SC - O(N)  

# 8) Next Smaller Element  
Similar approach as that of Next greater element. It's just that we do in the reverse way.  

# 9) Implement LRU cache   
Design a data structure that follows the constraints of Least Recently Used (LRU) cache”.  
Implement the LRUCache class:  
- LRUCache(int capacity) we need to initialize the LRU cache with positive size capacity.
- int get(int key) returns the value of the key if the key exists, otherwise return -1.
- Void put(int key,int value), Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache.if the number of keys exceeds the capacity from this operation, evict the least recently used key.
The functions get and put must each run in O(1) average time complexity.  

### Approach
Usin normal array or dequeue or anything like that would definitely take O(n) complexity but as we want it to be done in O(1) we can think of something like linkedlist.  
Here we use DLL and a hashmap.  
The node right to the head is the most recently used one. and the node left to tail is the leastrecently used.  
So whenever we want to remove something left to the tail and add the new node to the right of head.  
Whenever we have to do any operation like get or update, we check whether the key exists using a hashmap and if it exists we go to the reference node.  Update/get the value.  
And then remove the node from that place and place it next to head.  
We need to update the pointers accordingly.  
```cpp
class LRUCache {
public:
    class Node{
        public:
        int key;
        int val;
        Node *prev, *next;
        Node(int _key, int _val){
            key = _key;
            val = _val;
        }
    };
    
    unordered_map<int, Node*> m;
    int capacity = 0;
    Node *head = new Node(-1,-1);
    Node *tail = new Node(-1,-1);
    
    LRUCache(int _capacity) {
        capacity = _capacity;
        head->next = tail;
        tail->prev = head;
    }
    
    void addNode(Node *temp){
        Node * store = head->next;
        head->next = temp;
        temp->next = store;
        temp->prev = head;
        store->prev = temp;
    }
    
    void deleteNode(Node *temp){
        Node *nprev = temp->prev;
        Node *nnext = temp->next;
        nprev->next = nnext;
        nnext->prev = nprev;
    }
    
    int get(int key) {
        if(m.find(key) != m.end()){
            Node *temp = m[key];
            int ans = temp->val;
            deleteNode(temp);
            addNode(temp);
            m[key] = head->next;
            return ans;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if(m.find(key) != m.end())
            deleteNode(m[key]); 
        else if(m.size() == capacity){
            m.erase(tail->prev->key);
            deleteNode(tail->prev);
        }
        addNode(new Node(key,value));
        m[key] = head->next;
    }
};
```

# 10) Implement LFU Cache  
Design and implement a data structure for a Least Frequently Used (LFU) cache.  

Implement the LFUCache class:  

- LFUCache(int capacity) Initializes the object with the capacity of the data structure.  
- int get(int key) Gets the value of the key if the key exists in the cache. Otherwise, returns -1.
- void put(int key, int value) Update the value of the key if present, or inserts the key if not already present. When the cache reaches its capacity, it should invalidate and remove the least frequently used key before inserting a new item. For this problem, when there is a tie (i.e., two or more keys with the same frequency), the least recently used key would be invalidated.  
To determine the least frequently used key, a use counter is maintained for each key in the cache. The key with the smallest use counter is the least frequently used key.  

When a key is first inserted into the cache, its use counter is set to 1 (due to the put operation). The use counter for a key in the cache is incremented either a get or put operation is called on it.  

The functions get and put must each run in O(1) average time complexity.  

### Approach
We move on the similar thoughts as that of LRU cache.  Here we use 2 hash maps. One is to store <freq, DLL> and other is to store <key, Node*>.  And 2 variables
capacity and leastFreq.  
Whenever you need to do put operation, check whether that element already exists in map2. If it doesn't exists we insert it in DLL of map1 with key of freq 1. The DLL here follows the same intuition of LRU cache.  
Whenever you need to do get/update operation, check whether that element already exists in map2. Get the value and delete the node from the DLL corresponding to that 
freq and insert it in the DLL of freq + 1.  
Whenever any of your DLL goes empty, update the leastFreq variable.  
```cpp
struct Node {
    int key, value, cnt;
    Node *next; 
    Node *prev;
    Node(int _key, int _value) {
        key = _key;
        value = _value; 
        cnt = 1; 
    }
}; 
struct List {
    int size; 
    Node *head; 
    Node *tail; 
    List() {
        head = new Node(0, 0); 
        tail = new Node(0,0); 
        head->next = tail;
        tail->prev = head; 
        size = 0;
    }
    
    void addFront(Node *node) {
        Node* temp = head->next;
        node->next = temp;
        node->prev = head;
        head->next = node;
        temp->prev = node;
        size++; 
    }
    
    void removeNode(Node* delnode) {
        Node* delprev = delnode->prev;
        Node* delnext = delnode->next;
        delprev->next = delnext;
        delnext->prev = delprev;
        size--; 
    }
    
    
    
};
class LFUCache {
    map<int, Node*> keyNode; 
    map<int, List*> freqListMap; 
    int maxSizeCache;
    int minFreq; 
    int curSize; 
public:
    LFUCache(int capacity) {
        maxSizeCache = capacity; 
        minFreq = 0;
        curSize = 0; 
    }
    void updateFreqListMap(Node *node) {
        keyNode.erase(node->key); 
        freqListMap[node->cnt]->removeNode(node); 
        if(node->cnt == minFreq && freqListMap[node->cnt]->size == 0) {
            minFreq++; 
        }
        
        List* nextHigherFreqList = new List();
        if(freqListMap.find(node->cnt + 1) != freqListMap.end()) {
            nextHigherFreqList = freqListMap[node->cnt + 1];
        } 
        node->cnt += 1; 
        nextHigherFreqList->addFront(node); 
        freqListMap[node->cnt] = nextHigherFreqList; 
        keyNode[node->key] = node;
    }
    
    int get(int key) {
        if(keyNode.find(key) != keyNode.end()) {
            Node* node = keyNode[key]; 
            int val = node->value; 
            updateFreqListMap(node); 
            return val; 
        }
        return -1; 
    }
    
    void put(int key, int value) {
        if (maxSizeCache == 0) {
            return;
        }
        if(keyNode.find(key) != keyNode.end()) {
            Node* node = keyNode[key]; 
            node->value = value; 
            updateFreqListMap(node); 
        }
        else {
            if(curSize == maxSizeCache) {
                List* list = freqListMap[minFreq]; 
                keyNode.erase(list->tail->prev->key); 
                freqListMap[minFreq]->removeNode(list->tail->prev);
                curSize--; 
            }
            curSize++; 
            minFreq = 1; 
            List* listFreq = new List(); 
            if(freqListMap.find(minFreq) != freqListMap.end()) {
                listFreq = freqListMap[minFreq]; 
            }
            Node* node = new Node(key, value); 
            listFreq->addFront(node);
            keyNode[key] = node; 
            freqListMap[minFreq] = listFreq; 
        }
    }
};, 
```

# 11) Largest Rectangle in histogram  
Given an array of integers heights representing the histogram’s bar height where the width of each bar is 1  return the area of the largest rectangle in histogram.  
For any element at index i maximum area would be (r-l+1) * a[i] where r is the last element to the right where all elements from i to r are >= a[i] and similarly
to the left.  
To efficiently do this, we do  
```python3
class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        if(len(heights)==0):
            return 0
        left = [0]*len(heights)
        right = [0]*len(heights)
        left[0],right[len(heights)-1] = -1,len(heights)
        for i in range(1,len(heights)):
            p = i-1
            while(p>=0 and heights[p] >= heights[i]):
                p = left[p]
            left[i] = p
        for i in range(len(heights)-2,-1,-1):
            p = i + 1
            while(p<len(heights) and heights[p] >= heights[i]):
                p = right[p]
            right[i] = p
        area = 0
        for i in range(len(heights)):
            area = max(area,heights[i]*(right[i]-left[i]-1))
        return area
```
We can also think of using the approach of next and previous smaller elements using stack  
```cpp
class Solution {
  public:
    int largestRectangleArea(vector < int > & heights) {
      int n = heights.size();
      stack < int > st;
      int leftsmall[n], rightsmall[n];
      for (int i = 0; i < n; i++) {
        while (!st.empty() && heights[st.top()] >= heights[i]) {
          st.pop();
        }
        if (st.empty())
          leftsmall[i] = 0;
        else
          leftsmall[i] = st.top() + 1;
        st.push(i);
      }
      // clear the stack to be re-used
      while (!st.empty())
        st.pop();

      for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && heights[st.top()] >= heights[i])
          st.pop();

        if (st.empty())
          rightsmall[i] = n - 1;
        else
          rightsmall[i] = st.top() - 1;

        st.push(i);
      }
      int maxA = 0;
      for (int i = 0; i < n; i++) {
        maxA = max(maxA, heights[i] * (rightsmall[i] - leftsmall[i] + 1));
      }
      return maxA;
    }
};
```
An even better approach  
![image](https://user-images.githubusercontent.com/56584349/180193881-4f6b830f-5839-41b6-b473-45c96cee3b18.png)  
![image](https://user-images.githubusercontent.com/56584349/180193932-77ed0dd2-457e-4cd1-ab01-b6e1c941a749.png)  
![image](https://user-images.githubusercontent.com/56584349/180193967-079d3359-b7fd-4b5b-8380-2ee94cb9bac4.png)  

```cpp
int largestRectangleArea(vector < int > & histo) {
      stack < int > st;
      int maxA = 0;
      int n = histo.size();
      for (int i = 0; i <= n; i++) {
        while (!st.empty() && (i == n || histo[st.top()] >= histo[i])) {
          int height = histo[st.top()];
          st.pop();
          int width;
          if (st.empty())
            width = i;
          else
            width = i - st.top() - 1;
          maxA = max(maxA, width * height);
        }
        st.push(i);
      }
      return maxA;
    }
```

# 12) Sliding Window maximum  
Given an array of integers arr, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position. Return the max sliding window.  
### Approach 1  
**Initial Ideas**
We have to use some datastructure instead of array to store the elements of current window in each iteration. One key point which can reduce our complexity is in a current window, if x > i and a[x] > a[i] there is no use of storing a[i] in the window, as for all subsequent windows only a[x] will contribute as it is greater than a[i]. So there is no use of storing all the elements of current window in our data strucuture. And there is no use of storing elements of previous windows which are not a part of the current window.

**Entire intution**
We use a data structure called deque as we can push and pop elements both from both front and back. We store indices of the array elements in the deque such that we won't change the order in which elements appear in original array. We keep on pushing indices at the back of the deque. If the front of the deque has index i < (i-k+1) it means that the index is less than the current window and the element at that index is not a part of the current window. So we pop it from the front. And if the back of the deque has index x which is less than current index i and a[x] < a[i], then there is no use of that a[x] as everytime, only a[i] will contribute to our answer. So we pop all the elements from the back where x < i and a[x] < a[i].  
```cpp
deque<ll> dq;
    for(ll i=1;i<=n;i++){
        while(!dq.empty() && i-k+1 > dq.front()) dq.pop_front(); //elements which are not a part of the current window
        while(!dq.empty() && a[dq.back()] < a[i]) dq.pop_back(); //elements which are smaller than the current element
        dq.push_back(i);
        if(i>=k) cout << a[dq.front()] << ' ';
    }
 ```
 TC - O(N), SC - O(K)  
 ### Approach 2  
 Firstly, we divide the array into blocks of k. We use 2 dp arrays namely left and right. Where left[i] denotes the maximum of all the elemenths which are left to a[i] only in the block in which a[i] is present. Similarly right[i] conains the maximum of all elemnents to the right of a[i] in that particular block. Finally, when calculating the maximum element in a sub array(window), we print the maximum right[starting index in the window] and left[ending index in the window].  
 ```cpp
  ll a[n+1],left[n+1],right[n+2];
    right[n+1] = -INT_MAX;
    for(ll i=1;i<=n;i++) cin >> a[i];
    for(ll i=1;i<=n;i++){
        if((i-1)%k == 0) left[i] = a[i];
        else left[i] = max(left[i-1],a[i]);
        
        if((n+1-i)%k == 0) right[n+1-i] = a[n+1-i];
        else right[n+1-i] = max(right[n+2-i],a[n+1-i]);
    }
    for(ll i=1,j=k;j<=n;i++,j++) cout << max(right[i],left[j]) << ' ';
 ```
 TC,SC - O(N)  

# 13) Implement min stack  
```cpp
class MinStack {
  stack < pair < int, int >> st;

  public:
    void push(int x) {
      int min;
      if (st.empty()) {
        min = x;
      } else {
        min = std::min(st.top().second, x);
      }
      st.push({x,min});
    }

  void pop() {
    st.pop();
  }

  int top() {
    return st.top().first;
  }

  int getMin() {
    return st.top().second;
  }
};
```
TC - O(1), SC - O(2N)  
We push the updated value in the stack if the val is less than current mini i.e 2 * val - mini. To get the top element check if it's less than mini. if it is it 
indicates that it's the updated value. So, we can just return mini. else we can return the top value itself. And when we pop we have to update mini => mini = 2 * mini - el.  
```cpp
class MinStack {
  stack < long long > st;
  long long mini;
  public:
    /** initialize your data structure here. */
    MinStack() {
      while (st.empty() == false) st.pop();
      mini = INT_MAX;
    }

  void push(int value) {
    long long val = Long.valuevalue;
    if (st.empty()) {
      mini = val;
      st.push(val);
    } else {
      if (val < mini) {
        st.push(2 * val * 1 LL - mini);
        mini = val;
      } else {
        st.push(val);
      }
    }
  }

  void pop() {
    if (st.empty()) return;
    long long el = st.top();
    st.pop();

    if (el < mini) {
      mini = 2 * mini - el;
    }
  }

  int top() {
    if (st.empty()) return -1;

    long long el = st.top();
    if (el < mini) return mini;
    return el;
  }

  int getMin() {
    return mini;
  }
};
```
TC - O(1), SC - O(N)  

# 14) Rotten Oranges  
You will be given an m x n grid, where each cell has the following values :   
2  –  represents a rotten orange  
1  –  represents a Fresh orange  
0  –  represents an Empty Cell  
Every minute, if a Fresh Orange is adjacent to a Rotten Orange in 4-direction ( upward, downwards, right, and left ) it becomes Rotten.   
Return the minimum number of minutes required such that none of the cells has a Fresh Orange. If it’s not possible, return -1  
```cpp
int orangesRotting(vector<vector<int>>& grid) {
        if(grid.empty()) return 0;
        int m = grid.size(), n = grid[0].size(), days = 0, tot = 0, cnt = 0;
        queue<pair<int, int>> rotten;
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(grid[i][j] != 0) tot++;
                if(grid[i][j] == 2) rotten.push({i, j});
            }
        }
        int dx[4] = {0, 0, 1, -1};
        int dy[4] = {1, -1, 0, 0};
        
        while(!rotten.empty()){
            int k = rotten.size();
            cnt += k; 
            while(k--){
                int x = rotten.front().first, y = rotten.front().second;
                rotten.pop();
                for(int i = 0; i < 4; ++i){
                    int nx = x + dx[i], ny = y + dy[i];
                    if(nx < 0 || ny < 0 || nx >= m || ny >= n || grid[nx][ny] != 1) continue;
                    grid[nx][ny] = 2;
                    rotten.push({nx, ny});
                }
            }
            if(!rotten.empty()) days++;
        }
        return tot == cnt ? days : -1;
    }
```
TC - O(N^2 * 4), SC - O(N^2)  

# 15) Stock span problem  
The span of the stock's price today is defined as the maximum number of consecutive days (starting from today and going backward) for which the stock price was less than or equal to today's price.  
![image](https://user-images.githubusercontent.com/56584349/180133497-b1cbcfaf-9eeb-493a-b9b7-632f125723de.png)  
```cpp
stack<pair<int, int>> s;
    int next(int price) {
        int res = 1;
        while (!s.empty() && s.top().first <= price) {
            res += s.top().second;
            s.pop();
        }
        s.push({price, res});
        return res;
    }
```
```cpp
while(stk.empty() == false && price[stk.top()] <= price[i]) {
            stk.pop();
        }
        if(stk.empty() == true) {
            result[i] = i + 1;
        } else {
            result[i] = i - stk.top();
        }
        stk.push(i);
```
Both of the 2 approaches would work. one is to find the previous higher element.  Other is to add previous answers(see diagram to understand)  

# 16) Maximum of minimums of every window size  
You are given an array of ‘N’ integers, you need to find the maximum of minimum for every window size. The size of the window should vary from 1 to ‘N’ only.  
Instead of calculating answer for a particular window size let;s check whether a particular element can be the answer for any window size.  
We calculate next smaller and previous smaller for every index using stack.  
So that the current element is a part of window of size nextsmaller[i] - previoussmaller[i] - 1.  
```cpp
    for (int i = 0; i < n; i++) {
        int length = next[i] - prev[i] - 1;
        answer[length - 1] = max(answer[length - 1], arr[i]);
    }
    for (int i = n - 2; i >= 0; i--) 
        answer[i] = max(answer[i], answer[i + 1]);
```
TC, SC - O(N)  

# 17) The Celebrity problem  
There are ‘N’ people at a party. Each person has been assigned a unique id between 0 to 'N' - 1(both inclusive). A celebrity is a person who is known to everyone but does not know anyone at the party.  
If there is no celebrity, print -1  
### Approach 1 
Treat it like a graph problem, calculate in degrees and out degrees for a node. Check which node has indegree n-1 and out degree 0.
TC - O(N^2), SC - O(N)  
### Approach 2 - normal brute   
Assume that i can be the answer. check if its indegree is n-1 and outdegree 0. Similarly check for all the values of i from 0 to n-1.  
TC - O(N^2), SC - O(1)  
### Approach 3
**Intuition**  
- If A knows B, then A can’t be a celebrity. Discard A, and B may be celebrity.
- If A doesn’t know B, then B can’t be a celebrity. Discard B, and A may be celebrity.
- Repeat above two steps till there is only one person.
- Ensure the remained person is a celebrity. (What is the need of this step?).  
**Approach**  
- Create a stack and push all the id’s in the stack.
- Run a loop while there are more than 1 element in the stack.
- Pop top two element from the stack (represent them as A and B)
- If A knows B, then A can’t be a celebrity and push B in stack. Else if A doesn’t know B, then B can’t be a celebrity push A in stack.
- Assign the remaining element in the stack as the celebrity.
- Run a loop from 0 to n-1 and find the count of persons who knows the celebrity and the number of people whom the celebrity knows. if the count of persons who knows the celebrity is n-1 and the count of people whom the celebrity knows is 0 then return the id of celebrity else return -1.
```cpp
int findCelebrity(int n) {
    stack<int> ids;
    for(int i = 0; i < n; i++) {
        ids.push(i);
    }
    while(ids.size() > 1) {
        int id1 = ids.top();
        ids.pop();
        int id2 = ids.top();
        ids.pop();
        if(knows(id1, id2))
            ids.push(id2); 
        else {
            ids.push(id1); 
    }
    int celebrity = ids.top();
    bool knowAny = false, knownToAll = true;
    for(int i = 0; i < n; i++) {
        if(knows(celebrity, i)) {
            knowAny = true;
            break;
        }
    }

    for(int i = 0; i < n; i++) {
        if(i != celebrity and !knows(i, celebrity)) {
            knownToAll = false;
            break;
        }
    }

    if(knowAny or !knownToAll)
        celebrity = -1;
    return celebrity;
}
```
TC,SC-  O(N)  
### 2 POINTER APPROACH  
The idea is to use two pointers, one from start and one from the end. Assume the start person is A, and the end person is B. If A knows B, then A must not be the celebrity. Else, B must not be the celebrity. At the end of the loop, only one index will be left as a celebrity. Go through each person again and check whether this is the celebrity.   
TC - O(N), SC - O(1)  

