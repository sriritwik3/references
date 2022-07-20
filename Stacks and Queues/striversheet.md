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

# 10) Implement LFU Cache  

# 11) Largest Rectangle in histogram  
Given an array of integers heights representing the histogram’s bar height where the width of each bar is 1  return the area of the largest rectangle in histogram.  

# 12) Sliding Window maximum  

# 13) Implement min stack  

# 14) Rotten Oranges  

# 15) Stock span problem  
The span of the stock's price today is defined as the maximum number of consecutive days (starting from today and going backward) for which the stock price was less than or equal to today's price.  


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

