# 7-1 ZigZagging on a Tree
Suppose that all the keys in a binary tree are distinct positive integers. A unique binary tree can be determined by a given pair of postorder and inorder traversal sequences. And it is a simple standard routine to print the numbers in level-order. However, if you think the problem is too simple, then you are too naive. This time you are supposed to print the numbers in "zigzagging order" -- that is, starting from the root, print the numbers level-by-level, alternating between left to right and right to left. For example, for the following tree you must output: 1 11 5 8 17 12 20 15.

![image](https://images.ptausercontent.com/337cbfb0-a7b2-4500-9664-318e9ffc870e.jpg)
## Input Specification:
Each input file contains one test case. For each case, the first line gives a positive integer N (≤30), the total number of nodes in the binary tree. The second line gives the inorder sequence and the third line gives the postorder sequence. All the numbers in a line are separated by a space.
## Output Specification:
For each test case, print the zigzagging sequence of the tree in a line. All the numbers in a line must be separated by exactly one space, and there must be no extra space at the end of the line.
## Sample Input:
```
8
12 11 20 17 1 15 8 5
12 20 17 11 15 8 5 1
```
## Sample Output:
```
1 11 5 8 17 12 20 15
```
## Note
2 part

1. Build tree by inorder/preorder or inorder/postorder
2. zig-zag print tree
### build tree
```c
TreeNode* build_tree(int* inorder, int* postorder, int length){
  if(length==0) return NULL;
  int root_val = postorder[length-1];
  TreeNode* res = tree_node_init(root_val);
  int idx = 0;
  // find root idx in inorder seq
  for(int i=0; i<length; i++){
    if(inorder[i] == root_val){
      idx = i;
      break;
    }
  }
  // split old seq to new seq (go left)
  int new_inorder[30];
  int new_postorder[30];
  for(int i=0; i<idx; i++) {
    new_inorder[i] = inorder[i];
    new_postorder[i] = postorder[i];
  }
  res->left = build_tree(new_inorder, new_postorder, idx);
  // split old seq to new seq (go rigth)
  for(int i=0; i+idx+1<length; i++) {
    new_inorder[i] = inorder[i+idx+1];
  }
  for(int i=0; i+idx<length-1; i++){
    new_postorder[i] = postorder[i+idx];
  }
  res->right = build_tree(new_inorder, new_postorder, length-idx-1);
  return res; 
}
```
### zig-zag
use 2 stack
```c
void tree_zig_zag_print(Tree* tree){
  if(tree==NULL || tree->top==NULL) return;
  my_stack* stack = stack_init(); 
  my_stack* stack_2 = stack_init(); 
  stack_push(stack, tree->top);
  int flag = 0;
  // stop when 2 stack all full
  while(!stack_is_empty(stack) || !stack_is_empty(stack_2)){
    // stack1 pop, and push in stack2
    while(!stack_is_empty(stack)){
      TreeNode* cur = stack_pop(stack);
      if(flag++ > 0) printf(" ");
      printf("%d", cur->value);
      if(cur->right != NULL)
        stack_push(stack_2, cur->right);
      if(cur->left != NULL)
        stack_push(stack_2, cur->left);
    }
    // stack2 pop, and push in stack1
    while(!stack_is_empty(stack_2)){
      TreeNode* cur = stack_pop(stack_2);
      printf(" %d", cur->value);
      if(cur->left != NULL)
        stack_push(stack, cur->left);
      if(cur->right != NULL)
        stack_push(stack, cur->right);
    }
  }
  stack_delete(stack);
  stack_delete(stack_2);
}
```
