# Binary Search Trees  
## Striver Sheet  

# 1) Populate next right pointers of tree  
You are given a perfect binary tree where all leaves are on the same level, and every parent has two children. The binary tree has the following definition:  
```
struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
```
Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.  
Initially, all next pointers are set to NULL.  
Refer to [Link](https://leetcode.com/problems/populating-next-right-pointers-in-each-node/discuss/1654181/C%2B%2BPythonJava-Simple-Solution-w-Images-and-Explanation-or-BFS-%2B-DFS-%2B-O(1)-Optimized-BFS) for good explanation.  \

Using BFS  
```cpp
class Solution {
public:
    Node* connect(Node* root) {
        if(!root) return nullptr;
        queue<Node*> q;
        q.push(root);        
        while(size(q)) {
            Node* rightNode = nullptr;                    // set rightNode to null initially
            for(int i = size(q); i; i--) {                // traversing each level
                auto cur = q.front(); q.pop();            // pop a node from current level and,
                cur -> next = rightNode;                  // set its next pointer to rightNode
                rightNode = cur;                          // update rightNode as cur for next iteration
                if(cur -> right)                          // if a child exists
                    q.push(cur -> right),                 // IMP: push right first to do right-to-left BFS
                    q.push(cur -> left);                  // then push left
            }
        }
        return root;
    }
};
```  
TC - O(N), SC - O(width)  
Using DFS  
```cpp
class Solution {
public:
    Node* connect(Node* root) {
        if(!root) return nullptr;
        auto L = root -> left, R = root -> right, N = root -> next;
        if(L) {
            L -> next = R;                                // next of root's left is assigned as root's right
            if(N) R -> next = N -> left;                  // next of root's right is assigned as root's next's left (if root's next exist)
            connect(L);                                   // recurse left  - simple DFS 
            connect(R);                                   // recurse right
        }
        return root;
    }
};
```
TC - O(N), SC - O(LogN) recursive depth  
Space optimised BFS as we already point next pointers for each node, no need to store them in a DS.  
```cpp
class Solution {
public:
    Node* connect(Node* root) {
        Node *ans = root;
        while(root){
            Node* cur = root;
            while(cur){
                if(cur->left){ 
                    cur->left->next = cur->right;
                    if(cur->next) cur->right->next = cur->next->left;
                }
                else break;
                cur = cur->next;
            }
            root = root->left;
        }
        return ans;
    }
};
```

# 2) Search given key in BST  
```cpp
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if(root == NULL) return NULL;
        if(val == root->val) return root;
        if(val < root->val) return searchBST(root->left, val);
        return searchBST(root->right, val);
    }
};
```
```cpp
TreeNode* searchBST(TreeNode* root, int val) {
    while (root != nullptr && root->val != val) {
      root = (root->val > val) ? root->left : root->right;
    }
    return root;
}
```  

# 3) Construct BST from given keys   
If array is not sorted, sort it first  
Iterative approach  
```cpp
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        int start = 0, end = nums.size() - 1, mid;
        stack<pair<TreeNode*,pair<int,int>>> s;
        TreeNode *root = new TreeNode();
        s.push({root,{ start, end}});
        while(!s.empty()){
            auto it = s.top();
            s.pop();
            start = it.second.first, end = it.second.second;
            mid = start + (end-start)/2;
            TreeNode * temp = it.first;
            temp->val = nums[mid];
            temp->left = mid>start ? new TreeNode() :  NULL;
            temp->right = end>mid  ? new TreeNode() :  NULL;
            if(temp->left) s.push({temp->left, {start, mid-1}});
            if(temp->right) s.push({temp->right, {mid+1, end}});
        }
        return root;
    }
};
```
Recursive approach   
```cpp
class Solution {
public:
    TreeNode* recur(vector<int> &nums, int start, int end){
        if(start > end) return NULL;
        int mid = start + (end-start)/2;
        TreeNode *root = new TreeNode(nums[mid]);
        root->left = recur(nums, start, mid-1);
        root->right = recur(nums, mid+1,end);
        return root;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return recur(nums, 0, nums.size()-1);
    }
};
```

# 4) Construct BST from preorder traversal   
Normal recursive brute would take O(n^2)  
```cpp
class Solution {
public:
    TreeNode* helper(vector<int>& arr,int l,int r){
		//BASE CASE
        if(l>r)
            return NULL;
		
		//First element is root itself
        TreeNode *root=new TreeNode(arr[l]);
		
        int pos=l;     //For corner case that only 1 element is given it the array
        for(int i=l+1; i<=r; i++){   //Find the index of last element which is smaller than the root node
            if(arr[i]<root->val)
                pos=i;
            else
                break;
        }
        root->left=helper(arr,l+1,pos);  //Make left subtree
        root->right=helper(arr,pos+1,r); //Make right subtree
        return root;
    }
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int l=0;                  //Left most element of array
		int r=preorder.size()-1;  //Right most element of the array
        return helper(preorder,l,r);
    }
};
```
We can sort the array - inorder traversal.  Now, if we know in order and pre order - we can construct a unique BT but that too will take O(N + NLOGN).  
Now for every node, maintain a maximum bound and recur.  So in that way we can get to know whether a node can go in that position.  
```cpp
class Solution {
public:
    TreeNode* bstFromPreorder(vector<int>& A) {
        int i = 0;
        return build(A, i, INT_MAX);
    }

    TreeNode* build(vector<int>& A, int& i, int bound) {
        if (i == A.size() || A[i] > bound) return NULL;
        TreeNode* root = new TreeNode(A[i++]);
        root->left = build(A, i, root->val);
        root->right = build(A, i, bound);
        return root;
    }
};
```
TC - O(3N), SC - only stackk space.  

# 5) Check if a BT is BST or not  
One approach is to do inorder traversal and check whether it's sorted or not.  
```cpp
class Solution {
private: 
    TreeNode* prev = NULL;
public:
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*> st;
        while(!st.empty() || root != NULL){
            if(root != NULL){
                //cout << root->val << " \n";
                st.push(root);
                root = root->left;
            }
            else{
                auto it = st.top();
                st.pop();
                //cout << it->val << " " << (prev!=NULL?prev->val:'11') << endl;
                if(prev!=NULL && it != NULL && it->val <= prev->val) return false;
                else if(it != NULL) prev = it;
                root = it->right;
            }
        }
        return true;
    }
};
```   
Another approach is to maintain ranges for each node and check whether the node's value lies in that range.  
```cpp
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return valid(root, LONG_MIN, LONG_MAX);
    }
private:
    bool valid(TreeNode* root, long min, long max) {
        if (!root) {
            return true;
        }
        if (root -> val <= min || root -> val >= max) {
            return false;
        }
        return valid(root -> left, min, root -> val) && valid(root -> right, root -> val, max);
    }
};
```

# 6) Find LCA of two nodes in BST  
The first point of split is the LCA.  
```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(p->val < root->val && q->val < root->val) 
            return lowestCommonAncestor(root->left, p,q);
        if(p->val > root->val && q->val > root->val)
            return lowestCommonAncestor(root->right,p,q);
        else
            return root;
    }
};
```
TC - O(H), SC - stack space  

# 7) Find the inorder predecessor/successor of a given Key in BST  
keep on eliminating the subtrees by seeing the possibility of a node being the predecessor.  And store the last node which satisfies the property of being the answer.   
```cpp
void findPreSuc(Node* root, Node*& pre, Node*& suc, int key)
{

// Your code goes here
    pre = NULL, suc = NULL;
    Node * temp = root;
    while(temp != NULL){
        if(key >= temp->key)
            temp = temp->right;
        else
            suc = temp, temp = temp->left;
    }
    temp = root;
    while(temp != NULL){
        if(key <= temp->key)
            temp = temp->left;
        else
            pre = temp, temp = temp->right;
    }

}
```
```cpp
void findPreSuc(Node* root, Node*& pre, Node*& suc, int key)
{
    // Base case
    if (root == NULL)  return ;
 
    // If key is present at root
    if (root->key == key)
    {
        // the maximum value in left subtree is predecessor
        if (root->left != NULL)
        {
            Node* tmp = root->left;
            while (tmp->right)
                tmp = tmp->right;
            pre = tmp ;
        }
 
        // the minimum value in right subtree is successor
        if (root->right != NULL)
        {
            Node* tmp = root->right ;
            while (tmp->left)
                tmp = tmp->left ;
            suc = tmp ;
        }
        return ;
    }
 
    // If key is smaller than root's key, go to left subtree
    if (root->key > key)
    {
        suc = root ;
        findPreSuc(root->left, pre, suc, key) ;
    }
    else // go to right subtree
    {
        pre = root ;
        findPreSuc(root->right, pre, suc, key) ;
    }
}
```
TC -O(H), SC - stack space  

# 8) Ceil in a BST    
```cpp
int findCeil(TreeNode* root, int key){
  int ans = -1;
  while(root){
    if(root->val == key){
      ceil = root;
      return;
    }
    if(key > root->val) root = root->right;
    else ceil = root, root = root->left;
  }
  return ceil;
}
```

# 9) Floor in a BST  
Similar to ceil  

# 10) Find Kth smallest element in BST  
Inorder traversal of a tree results in a sorted array. So we can do recursive in order.  
```cpp
node* kthsmallest(node* root,int &k)
{
	if(root==NULL)
	return NULL;
	
	node* left=kthsmallest(root->left,k);
	if(left!=NULL)
	return left;
	k--;
	if(k==0)
	return root;
	
	return kthsmallest(root->right,k);
}
```

# 11) Find Kth largest element in BST   
If we know number of nodes, we can find n-k'th smallest number or we can simply do reverse in order.  
```cpp
node* kthlargest(node* root,int& k)
{
	if(root==NULL)
	return NULL;
	
	node* right=kthlargest(root->right,k);
	if(right!=NULL)
	return right;
	k--;
	
	if(k==0)
	return root;
	
	return kthlargest(root->left,k);
}
```

# 12) Find a pair with given sum in BST  
We can do normal set based approaches or any 2 pointer approaches as well.  
But to make use of the property that it is a BST , we can somehow do it in O(H) space and O(1) amortised complexity per each call using BST iterators.   
We maintain the code for 2 iterators one for reverse and other for normal.  
```cpp
class BSTIterator {
private:
    stack<TreeNode*> st;
    bool reverse = false;
public:
    BSTIterator(TreeNode* root, bool r) {
        reverse = r;
        pushAll(root);
    }
    
    int next() {
        auto it = st.top();
        st.pop();
        if(!reverse) pushAll(it->right);
        else pushAll(it->left);
        return it->val;
    }
    
    bool hasNext() {
        return !st.empty();
    }
    void pushAll(TreeNode *root){
        while(root) {
            st.push(root);
            if(!reverse)
                root = root->left;
            else root = root->right;
        }
    }
};

class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        if(root == NULL) return false;
        BSTIterator l(root,false), r(root, true);
        int i = l.next(), j = r.next();
        while(i < j){
            if(i+j == k) return true;
            if(i+j < k) i = l.next();
            else j = r.next();
        }
        return false;
    }
};
```


# 13) BST iterator  
![image](https://user-images.githubusercontent.com/56584349/180647095-eee56b0a-36e8-4788-9b4e-f789a786b1f4.png)  
We have to do each operation in O(1) time (amortised in a way).  And total space should be O(H)  
```cpp
class BSTIterator {
private:
    stack<TreeNode*> st;
public:
    BSTIterator(TreeNode* root) {
        pushAll(root);
    }
    
    int next() {
        auto it = st.top();
        st.pop();
        if(it->right) pushAll(it->right);
        return it->val;
    }
    
    bool hasNext() {
        return !st.empty();
    }
    void pushAll(TreeNode *root){
        while(root) st.push(root), root = root->left;
    }
};
```
 

# 14) Size of largest BST in binary tree   
We can use the code of validate BST for every subtree but that would tak O(n^2).  
For every node, keep track of largest, smallest values in it;s subtree and also the maximum size of subtree which is BST  
![image](https://user-images.githubusercontent.com/56584349/180645341-a5fe67c0-37e6-4bd8-899b-c4d1edcec0e5.png)  
```cpp
int ans;
class prop{
public:
    bool bst;       //to check if tree is bst
    int ma;         //max value in a tree
    int mi;         //min value in an tree
    int ms;         //current maximum sum
    prop(){
        bst=true;
        ma=INT_MIN;
        mi=INT_MAX;
        ms=0;
    }
};
class Solution {
public:
    prop calcSum(TreeNode* root){
        if (root == NULL){
            return prop();
        }
        prop p;
        prop pl = calcSum(root->left);                        //recursive call for left sub-tree
        prop pr = calcSum(root->right);                       //recursive call for right sub-tree
		
		//if sub-tree including this node is bst
        if ( pl.bst==true && pr.bst==true && root->val>pl.ma && root->val<pr.mi ){
            p.bst = true;                                                      //current tree is a bst
            p.ms = pl.ms + pr.ms + root->val;          
            p.mi  = min(root->val, pl.mi);
            p.ma = max(root->val, pr.ma);
        }
		//if current tree is not a bst
        else {
            p.bst=false;
            p.ms=max(pl.ms, pr.ms);
        }
		
        ans=max(ans, p.ms);
        return p;
    }
    int maxSumBST(TreeNode* root){
        ans = 0;
        calcSum(root);
        return ans;
    }
};
```
TC - O(N), SC -O(1)  

# 15) Recover BST  
2 nodes are swappped in a BST. recover the BST  
Brute - do any kind of traversal. Sort the array so you can get to know the actual inorder traversal. Now again do inorder traversal and correct the swapped nodes.  
Optimal - keep track of violations i.e while doing an inorder traversal, whhenever a node is less than prev node keep track of it.  
```cpp
class Solution {
    TreeNode *prev = new TreeNode(INT_MIN) ,*first, *middle, *last;
public:
    void inOrder(TreeNode *root){
        if(root == NULL) return;
        inOrder(root->left);
        if(root->val < prev->val){
            if(first == NULL){
                first = prev;
                middle = root;
            } else last = root;
        }
        prev = root;
        inOrder(root->right);
    }
    
    void recoverTree(TreeNode* root) {
        if(root == NULL) return;
        inOrder(root);
        if(last != NULL && first != NULL){
            swap(first->val, last->val);
        } else if(first != NULL && middle != NULL ) swap(first->val, middle->val);
    }
};
```
TC - O(N), SC - stack space  
