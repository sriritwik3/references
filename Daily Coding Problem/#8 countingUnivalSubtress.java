/* A unival tree (which stands for "universal value") is a tree where all nodes under it have the same value.
Given the root to a binary tree, count the number of unival subtrees.
For example, the following tree has 5 unival subtrees:
   0
  / \
 1   0
    / \
   1   0
  / \
 1   1 */


//All leafnodes are automatically unival trees. 
//We recursively go for leaf nodes and populate the count for each node if the value of a node is equal to both left and right nodes.

class BinaryTreeNode{
   BinaryTreeNode left;
   BinaryTreeNode right;
   int value;
}

//stores whether a given node is unival and also stores the count of unival nodes in the subtree of that node
class UnivalSubTreeCount{
   boolean isUnival;
   int count;
   UnivalSubTreeCount(boolean isUnival, int count){
      this.isUnival = isUnival;
      this.count = count;
   }
}

class calculateUnivalTrees{
   public UnivalSubTreeCount calculateFunction(BinaryTreeNode node){
      //BASE CASES

      //if a node is null we will mark it as unival such that it helps us to check for it's parent's univality and the count is 0 obviously.
      if(node == null) return new UnivalSubTreeCount(true,0);
      //if both children are null then the node is unival and the count is 1
      if(node.left == null && node.right == null) return new UnivalSubTreeCount(true,1);

      UnivalSubTreeCount leftCount = calculateFunction(node.left);
      UnivalSubTreeCount rightCount = calculateFunction(node.right);

      if(leftCount.isUnival && rightCount.isUnival && (node.left == null || node.left.value == node.value)
      && (node.right == null || node.right.value == node.value)){
         // if that node is unival total count becomes left + right + 1
         return new UnivalSubTreeCount(true,leftCount.count + rightCount.count + 1);
      }
      return new UnivalSubTreeCount(false,leftCount.count + rightCount.count);
   }
}