# Binary Trees
## Striver Sheet  

**Initialisation of Binary tree in c++**  
```cpp
struct node {
  int data;
  struct node * left, * right;
};

struct node * newNode(int data) {
  struct node * node = (struct node * ) malloc(sizeof(struct node));
  node -> data = data;
  node -> left = NULL;
  node -> right = NULL;

  return (node);
}
struct node * root = newNode(1);
  root -> left = newNode(2);
  root -> right = newNode(3);
  root -> left -> left = newNode(4);
  root -> left -> right = newNode(5);
  root -> left -> right -> left = newNode(8);
  root -> right -> left = newNode(6);
  root -> right -> right = newNode(7);
  root -> right -> right -> left = newNode(9);
  root -> right -> right -> right = newNode(10);
```


# 1) Inorder traversal of a Binary tree  
Inorder - left-root-right  
![image](https://user-images.githubusercontent.com/56584349/179389612-2a415c33-ef86-406d-9cd4-ba557766e2e8.png)  
## Recursive approach  
One important thing to note about inorder traversal is to return back from a child to it's parent. Usually we dont have a parent pointer.  
So, recursion is the best way to think about.  
Recurse until you find a left child which is a leaf. Print it's node->value and then recurse until you find it's right value and return back.  
```cpp
void inOrderTrav(node * curr, vector < int > & inOrder) {
  if (curr == NULL)
    return;

  inOrderTrav(curr -> left, inOrder);
  inOrder.push_back(curr -> data);
  inOrderTrav(curr -> right, inOrder);
}
```
TC,SC - O(N) for recursion stack  
## Iterative Approach  
The fundamental problem we face in this scenario is that there is no way that we can move from a child to a parent. To solve this problem, we use an explicit stack data structure. While traversing we can insert node values to the stack in such a way that we always get the next node value at the top of the stack.  
```cpp
vector < int > inOrderTrav(node * curr) {
  vector < int > inOrder;
  stack < node * > s;
  while (true) {
    if (curr != NULL) {
      s.push(curr);
      curr = curr -> left;
    } else {
      if (s.empty()) break;
      curr = s.top();
      inOrder.push_back(curr -> data);
      s.pop();
      curr = curr -> right;
    }
  }
  return inOrder;
}
```
TC, SC - O (N) Reason : In the worst case like if tree only have left children.   

# 2) Pre order traversal  
![image](https://user-images.githubusercontent.com/56584349/179391021-40899d83-6aeb-4a04-903d-804813a3dd8d.png)  
### Iterative approach  
The fundamental problem we face in this scenario is that there is no way that we can move from a child to a parent. To solve this problem, we use an explicit stack data structure. While traversing we can insert node values to the stack in such a way that we always get the next node value at the top of the stack.  
We first insert right and then left because, left should go first and hence it should be on top of the second so insert after right child.  
```cpp
vector < int > preOrderTrav(node * curr) {
  vector < int > preOrder;
  if (curr == NULL)
    return preOrder;

  stack < node * > s;
  s.push(curr);

  while (!s.empty()) {
    node * topNode = s.top();
    preOrder.push_back(topNode -> data);
    s.pop();
    if (topNode -> right != NULL)
      s.push(topNode -> right);
    if (topNode -> left != NULL)
      s.push(topNode -> left);
  }
  return preOrder;

}
```
TC, SC - O(N)

### Recursive approach  
```cpp
void preOrderTrav(node * curr, vector < int > & preOrder) {
  if (curr == NULL)
    return;

  preOrder.push_back(curr -> data);
  preOrderTrav(curr -> left, preOrder);
  preOrderTrav(curr -> right, preOrder);
}
```
TC,SC-  O(N)  (in the worst case)  

# 3) Post order traversal  
![image](https://user-images.githubusercontent.com/56584349/179392122-34565102-8fc8-41a2-ac4c-070de845463e.png)  
### Recursive approach  
```cpp
void postOrderTrav(node * curr, vector < int > & postOrder) {
  if (curr == NULL)
    return;

  postOrderTrav(curr -> left, postOrder);
  postOrderTrav(curr -> right, postOrder);
  postOrder.push_back(curr -> data);
}
```
TC, SC - O(N)  
### Iterative using 2 stacks  
- We take two explicit stacks S1 and S2.
- We insert our node to S1(if it’s not pointing to NULL).
- We will set up a while loop to run till S1 is non-empty.
- In every iteration, we pop out the top of S1 and then push this popped node to S2. Moreover we will push the left child and right child of this popped node to S1.(If they are not pointing to NULL).
- Then we start the next iteration with the next node as top of S1.
- We stop the iteration when S1 becomes empty.
- At last we start popping at the top of S2 and print the node values, we will get the postorder traversal.  
![image](https://user-images.githubusercontent.com/56584349/179395805-2989a4f6-c420-4468-9fa3-d9d77544bf8f.png)  
```cpp
vector < int > postOrderTrav(node * curr) {

  vector < int > postOrder;
  if (curr == NULL) return postOrder;

  stack < node * > s1;
  stack < node * > s2;
  s1.push(curr);
  while (!s1.empty()) {
    curr = s1.top();
    s1.pop();
    s2.push(curr);
    if (curr -> left != NULL)
      s1.push(curr -> left);
    if (curr -> right != NULL)
      s1.push(curr -> right);
  }
  while (!s2.empty()) {
    postOrder.push_back(s2.top() -> data);
    s2.pop();
  }
  return postOrder;
}
```
TC,SC - O(N)  
### Iterative using 1 stack  
#### Intuition  
First we need to understand what we do in a postorder traversal. We first explore the left side of the root node and keep on moving left until we encounter a node pointing to NULL. As now there is nothing more to traverse on the left, we move to the immediate parent(say node P) of that NULL node. Now we again start our left exploration from the right child of that node P. We will print a node’s value only when we have returned from its both children.  
#### Approach  
- We take an explicit data structure and a cur pointer pointing to the root of the tree.
- We run a while loop till the time the cur is not pointing to NULL or the stack is non-empty.
- If cur is not pointing to NULL, it means then we simply push that value to the stack and move the cur pointer to its left child because we want to explore the left child before the root or the right child.
- If the cur is pointing to NULL, it means we can’t go further left, then we take a variable temp and set it to  cur’s parent’s right child (as we have visited the left child, now we want to visit the right child). We have node cur’s parent at the top of the stack.
- If node temp is not pointing to NULL, we simply initialise cur as node temp so that we can again start looking at the left of node temp from the next iteration.
- If node temp is pointing to NULL, then first of all we are sure that we have visited both children of temp’s parent, so it’s time to print it. Therefore we set temp to its parent( present at the top of stack), pop the stack and then print temp’s value. Additionally,  this new temp(parent of NULL-pointing node) can be the right child of the node present at the top of stack after popping.In that case the node at top of the stack is parent of temp and the next node to be printed. Therefore we run an additional while loop to check if that is the case, if true then again move temp to its parent and print its value.  
**A dry run would definitely clarify all the doubts.  **
```cpp
vector < int > postOrderTrav(node * cur) {

  vector < int > postOrder;
  if (cur == NULL) return postOrder;

  stack < node * > st;
  while (cur != NULL || !st.empty()) {

    if (cur != NULL) {
      st.push(cur);
      cur = cur -> left;
    } else {
      node * temp = st.top() -> right;
      if (temp == NULL) {
        temp = st.top();
        st.pop();
        postOrder.push_back(temp -> data);
        while (!st.empty() && temp == st.top() -> right) {
          temp = st.top();
          st.pop();
          postOrder.push_back(temp -> data);
        }
      } else cur = temp;
    }
  }
  return postOrder;

}
```
TC,SC - O(N)  

# 4) Morris Inorder traversal  

# 5) Morris Pre Order  

# 6) Morris post order  

# 7) Left/Right View of Binary tree  
**Right view**  
Doing the reverse level order traversal and inserting 1st element in each level to the answer.  Just do the reverse for left view.  
```cpp
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        queue<TreeNode*> q;
        vector<int> ans;
        if(root == NULL)return ans;
        q.push(root);
        while(!q.empty()){
            int n = q.size();
            for(int i=0;i<n;i++){
                TreeNode *it = q.front();
                q.pop();
                if(i == 0) ans.push_back(it->val);
                if(it->right != NULL) q.push(it->right);
                if(it->left != NULL) q.push(it->left);
            }
        }
        return ans;
    }
};
```
TC - O(N), SC - O(max Nodes in a level)
Doing pre order traversal and checking if it's the first node in that level.  
```cpp
class Solution {
private:
    vector<int> ans;
    void kindOfPreOrder(TreeNode* root, int level){
        if(!root) return;
        if(level == ans.size()) ans.push_back(root->val);
        kindOfPreOrder(root->right,level+1);
        kindOfPreOrder(root->left,level+1);
    }
public:
    vector<int> rightSideView(TreeNode* root) {
        kindOfPreOrder(root,0);
        return ans;
    }
};
```
TC - O(N), SC - O(H)   

# 8) Bottom View of Binary tree  
Given a binary tree, print the bottom view from left to right. A node is included in the bottom view if it can be seen when we look at the tree from the bottom.  
**Intuition**:  We can mark straight lines like in the image below and mark them with +ve and -ve indexes. The Last node of every line will be my Bottom view.  
```cpp
class Solution {
  public:
    vector <int> bottomView(Node *root) {
        vector<int> ans; 
        if(root == NULL) return ans; 
        map<int,int> mpp; 
        queue<pair<Node*, int>> q; 
        q.push({root, 0}); 
        while(!q.empty()) {
            auto it = q.front(); 
            q.pop(); 
            Node* node = it.first; 
            int line = it.second; 
            mpp[line] = node->data; 
            
            if(node->left != NULL) {
                q.push({node->left, line-1}); 
            }
            if(node->right != NULL) {
                q.push({node->right, line + 1}); 
            }
            
        }
        
        for(auto it : mpp) {
            ans.push_back(it.second); 
        }
        return ans;  
    }
};
```
TC, SC - O(N)  

# 9) Top view of Binary Tree  
Given below is a binary tree. The task is to print the top view of the binary tree. The top view of a binary tree is the set of nodes visible when the tree is viewed from the top.  
![image](https://user-images.githubusercontent.com/56584349/179403198-2644c47f-0779-4f67-86b7-ee49e568142f.png)  
Just do a normal level order traversal. But in the queue, along with the node also store the vertical axis coordinate. And use a map to check whether we already visited a node in that coordinate.  
```cpp
class Solution
{
    public:
    //Function to return a list of nodes visible from the top view 
    //from left to right in Binary Tree.
    vector<int> topView(Node *root)
    {
        vector<int> ans; 
        if(root == NULL) return ans; 
        map<int,int> mpp; 
        queue<pair<Node*, int>> q; 
        q.push({root, 0}); 
        while(!q.empty()) {
            auto it = q.front(); 
            q.pop(); 
            Node* node = it.first; 
            int line = it.second; 
            if(mpp.find(line) == mpp.end()) mpp[line] = node->data; 
            
            if(node->left != NULL) {
                q.push({node->left, line-1}); 
            }
            if(node->right != NULL) {
                q.push({node->right, line + 1}); 
            }
            
        }
        
        for(auto it : mpp) {
            ans.push_back(it.second); 
        }
        return ans; 
    }
};
```
TC, SC - O(N)  

# 10) All orders in single traversal  
![image](https://user-images.githubusercontent.com/56584349/179404257-c843f2c1-3094-4077-a87e-a77ba01ba537.png)  
![image](https://user-images.githubusercontent.com/56584349/179404277-755767b0-4880-4416-9a49-61fd384f8742.png)  


```cpp
void allTraversal(node * root, vector < int > & pre, vector < int > & in , vector < int > & post) {
  stack < pair < node * , int >> st;
  st.push({
    root,
    1
  });
  if (root == NULL) return;

  while (!st.empty()) {
    auto it = st.top();
    st.pop();

    // this is part of pre
    // increment 1 to 2 
    // push the left side of the tree
    if (it.second == 1) {
      pre.push_back(it.first -> data);
      it.second++;
      st.push(it);

      if (it.first -> left != NULL) {
        st.push({
          it.first -> left,
          1
        });
      }
    }

    // this is a part of in 
    // increment 2 to 3 
    // push right 
    else if (it.second == 2) {
      in .push_back(it.first -> data);
      it.second++;
      st.push(it);

      if (it.first -> right != NULL) {
        st.push({
          it.first -> right,
          1
        });
      }
    }
    // don't push it back again 
    else {
      post.push_back(it.first -> data);
    }
  }
}
```
TC - O(N) -  We are visiting every node thrice therefore time complexity will be O(3 * N), which can be assumed as linear time complexity.   
SC- O (N) - We are using three lists and a stack to store the nodes. The time complexity will be about O(4 * N), which can be assumed as linear time complexity.  

# 11) Vertical order traversal  
![image](https://user-images.githubusercontent.com/56584349/179404490-826cc45e-f306-46f9-b872-bd573802e6bf.png)  
If two or more nodes are overlapping , will be printed in ascending order.  

# 12) Root to node path in BT  
Print Root to Node Path In A Binary Tree. Write a program to print path from root to a given node in a binary tree.  
we see that whenever we find the required node, its path is well present in our recursion call stack. We just need to figure out how we can use the recursive calls to print the required path.  
![image](https://user-images.githubusercontent.com/56584349/179405071-7a35fed9-53ec-4f16-b2a5-eac11f7a17e0.png)  
![image](https://user-images.githubusercontent.com/56584349/179405100-9780bf61-7669-49be-b08b-72417edbf49e.png)  
```cpp
bool getPath(node * root, vector < int > & arr, int x) {
  if (!root)
    return false;
  arr.push_back(root -> data);
  if (root -> data == x)
    return true;
  if (getPath(root -> left, arr, x) ||
    getPath(root -> right, arr, x))
    return true;
  arr.pop_back();
  return false;
}
```
The vector is passed by reference. So, the final ans would be in the vector arr.    
TC, SC - O(N)  

# 13) Max Width of BT  
Write a program to find the Maximum Width of A Binary Tree. Maximum width is from left non-null node to right non-null node which also includes null nodes in between.  
![image](https://user-images.githubusercontent.com/56584349/179449048-63548319-6506-4fec-a23d-bbb3d596ee65.png)  
![image](https://user-images.githubusercontent.com/56584349/179449489-8db62047-559a-4c11-b601-2ae1f17328f1.png)   
So,we can do level order traversal by assgining indices to all nodes.  Left child - 2 * i + 1, right child - 2 * i + 2  
But this might lead to overflow. So in each level we subtract the index value from the idnex value of starting node.  
```cpp
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        int ans = -1;
        queue<pair<TreeNode*,int>> q;
        q.push({root,0});
        while(!q.empty()){
            int n = q.size();
            long long first = q.front().second;
            long long last = q.back().second;
            ans = max(ans, (int)last - (int)first + 1);
            for(int i=0;i<n;i++){
                auto temp = q.front();
                q.pop();
                long long index = temp.second - first;
                if(temp.first->left != NULL) q.push({temp.first->left, (int)(2*index) + 1});
                if(temp.first->right !=NULL) q.push({temp.first->right, (int)(2*index) + 2});
            }
        }
        return ans;
    }
};
```
TC,SC - O(N)  

# 14) Level order traveral  
```cpp
class Solution {
public:
    vector<int> levelOrder(TreeNode* root) {
        vector<int> ans; 
        
        if(root == NULL) 
            return ans; 
            
        queue<TreeNode*> q; 
        q.push(root); 
        
        while(!q.empty()) {
           
            TreeNode *temp = q.front(); 
            q.pop(); 
            
            if(temp->left != NULL) 
                q.push(temp->left); 
            if(temp->right != NULL) 
                q.push(temp->right); 
                
            ans.push_back(temp->val); 
        }
        return ans; 
    }
};
```
TC,SC - O(N)  

# 15) Height of BT  
```cpp
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(root == NULL) return 0; 
        
        int lh = maxDepth(root->left); 
        int rh = maxDepth(root->right); 
        
        return 1 + max(lh, rh); 
    }
};
```
TC - O(N), SC - stack space
A level order traversal can also be done.  

# 16) Diameter of BT  
**Naive idea**  
- Traverse the tree recursively.
- At every node, calculate height of left and right subtrees.
- Calculate the diameter for every node using the above formula.
- Calculate the maximum of all diameters. This can be done simply using a variable passed by reference in the recursive calls or a global static variable.  
If done carefully, we cal return the depth from the recursive call as well as find the highest diameter at that node.  
```cpp
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int diameter = 0;
        int ignore = getAns(root, diameter);
        return diameter;
    }
    
    int getAns(TreeNode *root, int &diameter){
        if(root == NULL) return 0;
        int lh = getAns(root->left, diameter);
        int rh = getAns(root->right, diameter);
        diameter = max(diameter, lh + rh);
        return 1 + max(lh,rh);
    }
};
```
TC - O(N), SC - Recursion stack space   
Another good approach would be as follows : 
Find the farthest node from the root. And again find the farthest node from that node. And that length(distance - 2nd one) would be the diameter.  

# 17) Check if BT is height balanced or not  
Check whether the given Binary Tree is a Balanced Binary Tree or not. A binary tree is balanced if, for all nodes in the tree, the difference between left and right subtree height is not more than 1.  
For all Nodes , Absolute( Left Subtree Height – Right Subtree Height ) <= 1  
Naive would be same as above  
```cpp
class Solution {

public:
    bool isBalanced(TreeNode* root) {
        return dfsHeight (root) != -1;
    }

    int dfsHeight (TreeNode *root) {

        if (root == NULL) return 0;
        
        int leftHeight = dfsHeight (root -> left);

        if (leftHeight == -1) 
            return -1;
        
        int rightHeight = dfsHeight (root -> right);

        if (rightHeight == -1) 
            return -1;
        
        if (abs(leftHeight - rightHeight) > 1)  
            return -1;

        return max (leftHeight, rightHeight) + 1;
    }
};
```
TC - O(N), SC - Recursion stack space  

# 18) LCA in BT  


# 19) Check if 2 trees are identical or not  
```cpp
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(p == NULL || q == NULL) return p==q;
        return (p->val == q->val) && isSameTree(p->left,q->left) && isSameTree(p->right,q->right);
    }
};
```
TC - O(N), SC - Recursion stack space  

# 20) Zigzag traversal of BT  
Given the root of a binary tree, return the zigzag level order traversal of Binary Tree. (i.e., from left to right, then right to left for the next level and alternate between).  
Just maintain a flag variable to know which direction we have to move.  
```cpp
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if(root == NULL) return ans;
        queue<TreeNode*> q;
        q.push(root);
        bool flag = true;
        while(!q.empty()){
            int n = q.size();
            vector<int> row(n);
            for(int i=0;i<n;i++){
                int index = flag?i:n-i-1;
                TreeNode *temp = q.front();
                q.pop();
                row[index] = temp->val;
                if(temp->left != NULL) q.push(temp->left);
                if(temp->right != NULL) q.push(temp->right);
            }
            flag = !flag;
            ans.push_back(row);
        }
        return ans;
    }
};
```
TC, SC - O(N)  

# 21) Boundary traversal of BT  
Write a program for the Anti-Clockwise Boundary traversal of a binary tree.  
![image](https://user-images.githubusercontent.com/56584349/179461130-d4d7068b-3584-45a1-915c-69bcaab5181e.png)  
- Part 1: Left Boundary of the tree (excluding the leaf nodes).
- Part 2: All the leaf nodes travelled in the left to right direction.
- Part 3: Right Boundary of the tree (excluding the leaf nodes), traversed in the reverse direction.  
Root comes from both the sides. So to avoid any confusion push it first and ignore it in both the sides.  
For printing leaf nodes, level order traversal wouldn't work because it print upper leaves first irrespective of whether it's left or not.  
```cpp
void addLeftBoundary(node * root, vector < int > & res) {
  node * cur = root -> left;
  while (cur) {
    if (!isLeaf(cur)) res.push_back(cur -> data);
    if (cur -> left) cur = cur -> left;
    else cur = cur -> right;
  }
}
void addRightBoundary(node * root, vector < int > & res) {
  node * cur = root -> right;
  vector < int > tmp;
  while (cur) {
    if (!isLeaf(cur)) tmp.push_back(cur -> data);
    if (cur -> right) cur = cur -> right;
    else cur = cur -> left;
  }
  for (int i = tmp.size() - 1; i >= 0; --i) {
    res.push_back(tmp[i]);
  }
}

void addLeaves(node * root, vector < int > & res) {
  if (isLeaf(root)) {
    res.push_back(root -> data);
    return;
  }
  if (root -> left) addLeaves(root -> left, res);
  if (root -> right) addLeaves(root -> right, res);
}
```
![image](https://user-images.githubusercontent.com/56584349/179461725-1e101690-9ea4-4973-a656-05201f314447.png)  

# 22) Maximum Path sum  
Write a program to find the maximum sum path in a binary tree. A path in a binary tree is a sequence of nodes where every adjacent pair of nodes are connected by an edge. A node can only appear in the sequence at most once. A path need not pass from the root. We need to find the path with the maximum sum in the binary tree.  
![image](https://user-images.githubusercontent.com/56584349/179490584-02cb8f58-30db-4332-b494-504f13abace5.png)  
- Initialize a maxi variable to store our final answer.
- Do a simple tree traversal. At each node, find  recursively its leftMaxPath and its rightMaxPath.
- Calculate the maxPath through the node as val + (leftMaxPath + rightMaxPath) and update maxi accordingly.
- Return the maxPath when node is not the curving point as val + max(leftMaxPath, rightMaxPath).
```cpp
class Solution {
private:
    int ans = INT_MIN;
    int dfs(TreeNode* root){
        if(!root) return 0;
        int l = max(0, dfs(root->left));
        int r = max(0, dfs(root->right));
        ans = max(ans, l+r+root->val);
        return max(l,r) + root->val;
    }
public:
    int maxPathSum(TreeNode* root) {
        dfs(root);
        return ans;
    }
};
```
TC - O(N), SC - Recursion stack space - o(n)  

# 23) Construct BT from inorder and preorder  

# 24) Construct BT from inorder and postorder  

# 25) Symmetric BT  
A symmetrical binary tree is a tree that forms a mirror of itself around the center. In other words, every node in the left subtree will have a mirror image in the right subtree.  
![image](https://user-images.githubusercontent.com/56584349/179494464-5318c3ff-7139-419b-988a-51983bb8f182.png)  
![image](https://user-images.githubusercontent.com/56584349/179494506-4a5bfdd6-b71d-44eb-9e00-36f334e43060.png)  
```cpp
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if(root == NULL) return false;
        return isSymmetric(root->left, root->right);
    }
    
    bool isSymmetric(TreeNode* root1, TreeNode *root2){
        if(root1 == NULL || root2 == NULL) return root1 == root2;
        return (root1->val == root2->val && isSymmetric(root1->left, root2->right) &&
               isSymmetric(root1->right, root2->left));
    }
};
```
TC,SC - O(N)  
**Iterative Solution**  
```cpp
class Solution {
public:
    bool isSymmetric(TreeNode *root) {
        TreeNode *left, *right;
        if (!root)
            return true;
        
        queue<TreeNode*> q1, q2;
        q1.push(root->left);
        q2.push(root->right);
        while (!q1.empty() && !q2.empty()){
            left = q1.front();
            q1.pop();
            right = q2.front();
            q2.pop();
            if (NULL == left && NULL == right)
                continue;
            if (NULL == left || NULL == right)
                return false;
            if (left->val != right->val)
                return false;
            q1.push(left->left);
            q1.push(left->right);
            q2.push(right->right);
            q2.push(right->left);
        }
        return true;
    }
};
```

# 26) Flatten BT to linkedlist  
- If we observe, we are moving in a reverse postorder way : i.e  right, left, root. 
- We take a reference variable (say prev) to store the previous node( initialized to NULL).
- Whenever we visit a node, we set the right child to the prev and left child to NULL. 
- Next we assign this current node to prev.
- We perform the above two operations on all the nodes in the traversal.  
```cpp
class Solution {
public:
    TreeNode *ans = NULL;
    void flatten(TreeNode *root){
        if(root == NULL) return;
        flatten(root->right);
        flatten(root->left);
        root->right  = ans;
        root->left = NULL;
        ans = root;     
    }
};
```
TC,SC - O(N)  


# 27) Check for children sum property  
The children sum property is defined as, For every node of the tree, the value of a node is equal to the sum of values of its children(left child and right child).  
Note:   
The node values can be increased by 1 any number of times but decrement of any node value is not allowed.  
A value for a NULL node can be assumed as 0.  
You are not allowed to change the structure of the given binary tree.  
![image](https://user-images.githubusercontent.com/56584349/179511284-db7d4725-dd98-4e09-a8ee-3a621e0f09c7.png)  
```cpp
void reorder(node * root) {
  if (root == NULL) return;
  int child = 0;
  if (root -> left) {
    child += root -> left -> data;
  }
  if (root -> right) {
    child += root -> right -> data;
  }

  if (child < root -> data) {
    if (root -> left) root -> left -> data = root -> data;
    else if (root -> right) root -> right -> data = root -> data;
  }

  reorder(root -> left);
  reorder(root -> right);

  int tot = 0;
  if (root -> left) tot += root -> left -> data;
  if (root -> right) tot += root -> right -> data;
  if (root -> left || root -> right) root -> data = tot;
}
```
TC, SC - O(N)  

# 28) Invert a Binary tree
```cpp
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(root){
            swap(root->left, root->right);
            invertTree(root->left);
            invertTree(root->right);
        }
        return root;
    }
};
```
```cpp
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        stack<TreeNode*> s;
        s.push(root);
        while(!s.empty()){
            auto it = s.top();
            s.pop();
            if(it != NULL){
                swap(it->left, it->right);
                s.push(it->left);
                s.push(it->right);
            }
        }
        return root;
    }
};
```

# 29) Serialise and deserialise binary tree  
Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.  
![image](https://user-images.githubusercontent.com/56584349/179550687-b3dcb78a-edea-4570-b32a-1edf5805af97.png)  
We do a level order traversaland whenever we get a null, we hash it as some character.  And while deserialsing we do the same.  
Don;t forget to use commans in between the node values.  
```cpp
 // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string ans = "";
        if(root == NULL) return ans;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            int n = q.size();
            for(int i=0;i<n;i++){
                TreeNode *temp = q.front();
                q.pop();
                if(temp == NULL) ans +="#,";
                else ans += (to_string(temp->val) + ',');
                if(temp != NULL){
                    q.push(temp->left);
                    q.push(temp->right);
                }
            }
        }
        return ans;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data.size() == 0) return NULL; 
        stringstream s(data);
        string str; 
        getline(s, str, ',');
        TreeNode *root = new TreeNode(stoi(str));
        queue<TreeNode*> q; 
        q.push(root); 
        while(!q.empty()) {
            TreeNode *node = q.front(); 
            q.pop(); 
            
            getline(s, str, ',');
            if(str == "#") {
                node->left = NULL; 
            }
            else {
                TreeNode* leftNode = new TreeNode(stoi(str)); 
                node->left = leftNode; 
                q.push(leftNode); 
            }
            
            getline(s, str, ',');
            if(str == "#") {
                node->right = NULL; 
            }
            else {
                TreeNode* rightNode = new TreeNode(stoi(str)); 
                node->right = rightNode;
                q.push(rightNode); 
            }
        }
        return root; 
    }
```
TC, SC - O(N)  








