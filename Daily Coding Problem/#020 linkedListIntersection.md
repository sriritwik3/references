# Intersection  of 2 singly linked lists

## Problem Statement

This problem was asked by Google.
Given two singly linked lists that intersect at some point, find the intersecting node. The lists are non-cyclical.
For example, given A = 3 -> 7 -> 8 -> 10 and B = 99 -> 1 -> 8 -> 10, return the node with value 8.
In this example, assume nodes with the same value are the exact same node objects.
Do this in O(M + N) time (where M and N are the lengths of the lists) and constant space.

## Solution
  
#### It becomes a cakewalk problem, once you know this approach
  
Iterate through each linked lists. If they are of same length, you can simply return the node where both of them has same lengths.
**What if both the lists are of varying length??**

That's where the real question arrives. Let's assume difference between lengths of both lists to be k. 

By the time the smaller list reaches it's end the bigger list is k nodes behind the smaller list. So, what we can do is assignt the pointer of smaller list to the head of bigger list
and when bigger list reaches it's end assign it's pointer to head of smaller one. 
Now, when one pointer is at starting of smaller node, another pointer is already k nodes ahead of head of bigger node. So, they will definitely collide at some node.
  
**THINK AGAIN IF YOU DIDN'T UNDERSTAND THIS**. It's easy.
  
### Code
```python
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> ListNode:
        a,b = headA,headB
        while a!=b:
            a = a.next if a else headB
            b = b.next if b else headA
        return a
        
```
