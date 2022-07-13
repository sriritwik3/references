# LinkedList
## Striver SDE sheet 
**[Link](https://takeuforward.org/interviews/strivers-sde-sheet-top-coding-interview-problems/)**  

# 1) Reverse a Linked List  
Given the head of a singly linked list, write a program to reverse the linked list, and return the head pointer to the reversed list.  

Definition of linked list  
```cpp
struct ListNode {
     int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
    };
```

### Approach - 1  
Take 3 pointers, one pointing to the current node. one to track previous nodes so that we can interchange links between them. one to keep track of nodes infront of current node.  
```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *ans = NULL, *cur = head;
        while(cur){
            ListNode *temp = cur->next;
            cur->next = ans;
            ans = cur;
            cur = temp;
        }
        return ans;
    }
};
```
TC - O(N), SC - O(1) we store onlyu 3 pointers.  

### Approach -2 Recursive solution.  
We traverse to the end of the list recursively.  
As we reach the end of the list, we make the end node the head. Then receive previous nodes and make them connected to the last one.  
At last, we link the second node to the head and the first node to NULL. We return to our new head.  
```cpp
class Solution {
public:

    ListNode* reverseList(ListNode* &head) {

        if (head == NULL||head->next==NULL)
            return head;

        ListNode* nnode = reverseList(head->next);
        head->next->next = head;
        head->next = NULL;
        return nnode;
    }
};
```
TC - O(N), SC - Stack space  

# 2) Find the middle of the LinkedList  
 Given the head of a singly linked list, return the middle node of the linked list. If there are two middle nodes, return the second middle node.  
 ### Naive
 Iterate through the linked list, count no.of nodes and iterate again and while iterating second time maintain a counter and stop at n/2th node and return it.  
 ### Tortoise Hare appproach  
 In the Tortoise-Hare approach, we increment slow ptr by 1 and fast ptr by 2, so if take a close look fast ptr will travel double than that of the slow pointer. So when the fast ptr will be at the end of Linked List, slow ptr would have covered half of Linked List till then. So slow ptr will be pointing towards the middle of Linked List.  
 ```cpp
 class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode *slow = head, *fast = head;
        while(fast && fast->next) slow=slow->next, fast=fast->next->next;
        return slow;
    }
};
 ```
 TC - O(N), SC - O(1)  
 
 # 3) Merge two sorted linked lists
 Given two singly linked lists that are sorted in increasing order of node values, merge two sorted linked lists and return them as a sorted list. The list should be made by splicing together the nodes of the first two lists.  
 ### Approach 1  
 Create a new dummy node. Find the smallest among two nodes pointed by the head pointer of both input lists, and store that data in a new list created.And repeat the process.  
 TC,SC - O(N+M)  
 ### Approach 2 - Doing it inplace  
- Step 1: Create two pointers, say l1 and l2. Compare the first node of both lists and find the small among the two. Assign pointer l1 to the smaller value node.  
- Step 2: Create a pointer, say res, to l1. An iteration is basically iterating through both lists till the value pointed by l1 is less than or equal to the value pointed by l2.  
- Step 3: Start iteration. Create a variable, say, temp. It will keep track of the last node sorted list in an iteration.   
- Step 4: Once an iteration is complete, link node pointed by temp to node pointed by l2. Swap l1 and l2.  
- Step 5: If any one of the pointers among l1 and l2 is NULL, then move the node pointed by temp to the next higher value node.  

```cpp
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1 == NULL) return l2;
        if(l2 == NULL) return l1;
        if(l1->val > l2->val) swap(l1, l2);
        ListNode *ans = l1;
        while(l1 != NULL && l2 != NULL){
            ListNode *temp = NULL;
            while(l1 != NULL && l1->val <= l2->val) temp = l1, l1 = l1->next;
            temp->next = l2;
            swap(l1,l2);
        }
        return ans;
    }
};
```
TC - O(N+M), SC - O(1)  

# 4) Remove Nth node from back of the list.  
Given a linked list, and a number N. Find the Nth node from the end of this linked list and delete it. Return the head of the new modified linked list.  
### Naive
Traverse 2 times and maintain a counter.  
### 2 pointer approach  
Maintain a slow pointer and a fast pointer. When fast pointer reaches nth node activate slow pointer. When fast pointer reaches the end, slow pointer will be at n'th node from the last.  
```cpp
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *ans = new ListNode(NULL);
        ans->next = head;
        ListNode *slow = ans, *fast = ans;
        for(int i=0;i<n;i++) fast = fast->next;
        while(fast->next != NULL) slow = slow->next, fast = fast->next;
        slow->next = slow->next->next;
        return ans->next;
    }
};
```
TC - O(N), SC - O(1)  

# 5) Add two numbers as a linked list  
Given the heads of two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.   
### Approach
Follow the normal addition procedure using a carry variable.  
```cpp
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry = 0;
        ListNode *ans = new ListNode(0);
        ListNode *ans1 = ans;
        while(l1!=NULL || l2!=NULL || carry!=0 ){
            int a = 0, b = 0 ;
            if(l1!=NULL) a = l1->val;
            if(l2!=NULL) b = l2->val;
            ListNode *temp = new ListNode((a + b + carry)%10);
            carry = (a + b + carry)/10;
            ans1->next = temp;
            ans1 = ans1->next;
            if(l1 != NULL)
            l1 = l1->next;
            if(l2 !=NULL)
            l2 = l2->next;
        }
        return ans->next;
    }
};
```
TC, SC - O(max(m,n))  

# 6)Delete a given node in O(1)  
Write a function to delete a node in a singly-linked list. You will not be given access to the head of the list instead, you will be given access to the node to be deleted directly. It is guaranteed that the node to be deleted is not a tail node in the list.  
```cpp
class Solution {
public:
    void deleteNode(ListNode* node) {
        *node = *node->next;
    }
};
```

# 7)Find intersection point of Y linkedlist  
Given the heads of two singly linked-lists headA and headB, return the node at which the two lists intersect. If the two linked lists have no intersection at all, return null.  
### Naive
For each node in list 1, check for all nodes in list2. TC - O(MN), SC - O(1). Hashing - O(N+M), O(N).  
### Difference of length approach
- Find length of both the lists.
- Find the positive difference of these lengths.
- Move the dummy pointer of the larger list by difference achieved. This makes our search length reduced to the smaller list length.
- Move both pointers, each pointing two lists, ahead simultaneously if both do not collide.
TC - O(2max(length of list1,length of list2))+O(abs(length of list1-length of list2))+O(min(length of list1,length of list2)), SC - O(1)  
```cpp
int getDifference(node* head1,node* head2) {
     int len1 = 0,len2 = 0;
        while(head1 != NULL || head2 != NULL) {
            if(head1 != NULL) {
                ++len1; head1 = head1->next;
            }
            if(head2 != NULL) {
                ++len2; head2 = head2->next;
            }
            
        }
        return len1-len2;//if difference is neg-> length of list2 > length of list1 else vice-versa
}

//utility function to check presence of intersection
node* intersectionPresent(node* head1,node* head2) {
 int diff = getDifference(head1,head2);
        if(diff < 0) 
            while(diff++ != 0) head2 = head2->next; 
        else while(diff-- != 0) head1 = head1->next;
        while(head1 != NULL) {
            if(head1 == head2) return head1;
            head2 = head2->next;
            head1 = head1->next;
        }
        return head1;


}
```
### Further optimised  
take 2 pointers one pointing to head of one list and other pointing to other list. start iterating through the lists and if one reaches null start off from other pointers head. and the place where they collide is the point of intersection.  
```cpp
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *a = headA, *b = headB;
        while(a != b){
            a = a==NULL?headB:a->next;
            b = b==NULL?headA:b->next;
        }
        return a;
    }
};
```
TC - O(2 * max(length of list1,length of list2)), SC - O(1)  

# 8) Detect a cycle in a linked list  
Given head, the head of a linked list, determine if the linked list has a cycle in it. There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer.  
Return true if there is a cycle in the linked list. Otherwise, return false.  
### Better approaches  
hashing - O(N), O(N). change values of all traversed nodes to -1 - O(N), O(1).  
### Optimal  
- We will take two pointers, namely fast and slow. Fast pointer takes 2 steps ahead and slow pointer takes 2 points ahead.
- Iterate through the list until the fast pointer is equal to NULL. This is because NULL indicates that there is no cycle present in the given list.
- Cycle can be detected when fast and slow pointers collide.
TC - O(N), SC - O(1)  
```cpp
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        while(fast!=NULL && fast->next!=NULL){
            slow = slow->next;
            fast = fast->next->next;
            if(fast == NULL) return false;
            if(slow == fast) return true;
        }
        return false;
    }
};
```
# 9) Reverse a linkedlist in groups of size K  
Given the head of a linked list, reverse the nodes of the list k at a time, and return the modified list. k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.  
### Recursive Approach
```cpp
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *cur = head;
        int counter = 0;
        while(cur!=NULL && counter!=k) cur = cur->next, counter++; // find the k+1 node
        if(counter == k){ // if k+1 node is found
            ListNode *temp = reverseKGroup(cur, k); // reverse list with k+1 node as head
            // head - head-pointer to direct part, 
            // temp - head-pointer to reversed part;
            while(counter-- > 0){  // reverse current k-group: 
                ListNode *tmp = head->next;
                head->next = temp;
                temp = head;
                head = tmp;
            }
            head = temp;
        }
        return head;
    }
};
```
It takes stack space but we have to do in constant space so we have to go for iterative.  
### Iterative Approach  
```cpp

```
TC - O(N), SC - O(1)  

# 10) Check if a linked list is apalindrome or not  
Given the head of a singly linked list, return true if it is a palindrome.  
### Using extra datastructure like stack or an array
TC,SC - O(N)  
### Optimal  
Find the middle element. Reverse the second half. And compare both halves
```cpp
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        ListNode *slow = head, *fast = head;
        while(fast->next!=NULL && fast->next->next != NULL) slow = slow->next, fast = fast->next->next;
        ListNode *cur = slow->next, *rev = NULL;
        while(cur){
            ListNode *temp = cur->next;
            cur->next = rev;
            rev = cur;
            cur = temp;
        }
        ListNode *iter = head;
        while(rev != NULL){
            if(iter->val !=rev->val) return false;
            iter = iter->next;
            rev = rev->next;
        }
        return true;
    }
};
```
TC - O(N/2) for finding the middle element, reversing the list from the middle element, and traversing again to find palindrome respectively.  
SC - O(1)  

# 11) Starting point of loop in a linkedlist  
Given the head of a linked list, return the node where the cycle begins. If there is no cycle, return null.  
There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. Internally, pos is used to denote the index of the node that the tail’s next pointer is connected to (0-indexed). It is -1 if there is no cycle. Note that pos is not passed as a parameter.  
Do not modify the linked list.  
### Intuition  
The following steps are required:

- Initially take two pointers, fast and slow. The fast pointer takes two steps ahead while the slow pointer will take a single step ahead for each iteration.
- We know that if a cycle exists, fast and slow pointers will collide.
- If the cycle does not exist, the fast pointer will move to NULL
- Else, when both slow and fast pointer collides, it detects a cycle exists.
- Take another pointer, say entry. Point to the very first of the linked list.
- Move the slow and the entry pointer ahead by single steps until they collide. 
- Once they collide we get the starting node of the linked list.
- But why use another pointer, or xentry?
Let’s say a slow pointer covers the L2 distance from the starting node of the cycle until it collides with a fast pointer. L1 is the distance traveled by the entry pointer to the starting node of the cycle. So, in total, the slow pointer covers the L1+L2 distance. We know that a fast pointer covers some steps more than a slow pointer. Therefore, we can say that a fast pointer will surely cover the L1+L2 distance. Plus, a fast pointer will cover more steps which will accumulate to nC length where cC is the length of the cycle and n is the number of turns. Thus, the fast pointer covers the total length of L1+L2+nC. 
We know that the slow pointer travels twice the fast pointer. So this makes the equation to
2(L1+L2) = L1+L2+nC. This makes the equation to  
L1+L2 = nC. Moving L2 to the right side   
L1 = nC-L2 and this shows why the entry pointer and the slow pointer would collide.  
```cpp
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow= head, *fast = head;
        while(fast!=NULL && fast->next != NULL ){
            slow = slow->next;
            fast = fast->next->next;
            if(fast == NULL) return NULL;
            if(slow == fast){
                ListNode *start = head;
                while(start != slow) start = start->next, slow = slow->next;
                return slow;
            }
        }
        return NULL;
    }
};
```
TC - O(N), SC - O(1)

# 12) Flattening of Linked list  
Given a Linked List of size N, where every node represents a sub-linked-list and contains two pointers:  
(i) a next pointer to the next node,  
(ii) a bottom pointer to a linked list where this node is head.  
Each of the sub-linked-list is in sorted order.  
Flatten the Link List such that all the nodes appear in a single level while maintaining the sorted order.   
Note: The flattened list will be printed using the bottom pointer instead of the next pointer.  
![image](https://user-images.githubusercontent.com/56584349/178660187-433a2a63-c59e-4801-bc7b-f67c0084edbe.png)  
### Approach  
keep on merging lists two at a time.  
```cpp
Node* mergeTwoLists(Node* a, Node* b) {
    
    Node *temp = new Node(0);
    Node *res = temp; 
    
    while(a != NULL && b != NULL) {
        if(a->data < b->data) {
            temp->bottom = a; 
            temp = temp->bottom; 
            a = a->bottom; 
        }
        else {
            temp->bottom = b;
            temp = temp->bottom; 
            b = b->bottom; 
        }
    }
    
    if(a) temp->bottom = a; 
    else temp->bottom = b; 
    
    return res -> bottom; 
    
}
Node *flatten(Node *root)
{
   
        if (root == NULL || root->next == NULL) 
            return root; 
  
        // recur for list on right 
        root->next = flatten(root->next); 
  
        // now merge 
        root = mergeTwoLists(root, root->next); 
  
        // return the root 
        // it will be in turn merged with its left 
        return root; 
}
```
TC - O(no.of nodes), SC -O(1)  

# 13) Rotate a linked list  
Given the head of a linked list, rotate the list to the right by k places.  
### Approach  
- Calculate the length of the list.
- Connect the last node to the first node, converting it to a circular linked list.
- Iterate to cut the link of the last node and start a node of k%length of the list rotated list.  
```cpp
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(k == 0 || head==NULL || head->next == NULL) return head;
        int length = 0;
        ListNode *cur = head;
        while(true){
            length++;
            if(cur->next == NULL){
                cur->next = head;
                break;
            }
            cur = cur->next;
        }
        k = k%length;
        cout << k << " " << cur->next->val << endl;
        ListNode *ans;
        while(true){
            length--;
            if(length == k){
                ans = head->next;
                head->next = NULL;
                break;
            }
            head = head->next;
        }
        return ans;
    }
};
```
TC - O(length of the list) for calculating the length of the list. O(length of the list – (length of list%k)) for breaking link.  
SC - O(1)  

# 14) Clone a linked list with random and next pointer  
### Normal Approach using hashing
use an unordered map<Node, node> and hash[originalNode] should contain newly created node.  
```cpp
class Solution {
public:
    Node* copyRandomList(Node* head) {
        map<Node*, Node*> m;
        int i=0;
        Node* ptr = head;
        while (ptr) {
            m[ptr] =new Node(ptr->val);
            ptr = ptr->next;
        }
        ptr = head;
        while (ptr) {
            m[ptr]->next = m[ptr->next];
            m[ptr]->random = m[ptr->random];
            ptr = ptr->next;
        }
        return m[head];
    }
};
```
TC - O(N), SC - O(N)    
### Optimal Approach  
We do 3 iterations. IN first iteration copy the node right infront of it's original node eg; 1->2->3 becomes 1->1->2->2->3->3. In 2nd iteration we can assign random pointers to the new noded by doing node->next->random = node->random->next. In 3rd itration break the links/  
```cpp
class Solution {
public:
    Node* copyRandomList(Node* head) {
        Node *l1,*l2, *ans;
        if(head == NULL) return head;
        l1 = head;
        while(l1){
            Node *newly = new Node(l1->val);
            newly->next = l1->next;
            l1->next = newly;
            l1 = l1->next->next;
        }
        l1 = head;
        while(l1){
            if(l1->random != NULL)
            l1->next->random = l1->random->next;
            l1 = l1->next->next;
        }
        ans = head->next;
        l1 = head;
        while(l1){
            l2 = l1->next;
            l1->next = l1->next->next;
            if(l2->next != NULL) l2->next = l2->next->next;
            l1 = l1->next;
        }
        return ans;
    }
};
```
TC - O(N), SC - O(1)  

