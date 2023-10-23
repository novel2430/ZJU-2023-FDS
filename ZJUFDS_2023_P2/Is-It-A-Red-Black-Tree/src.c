#include <stdio.h>
#include <stdlib.h>

// Global var
// #Intro: black nodes count in the shortest path
int nil_length = 0;

// # Enum Color
// # Intro: color of red-black-tree's node
typedef enum Color{
  BLACK,
  RED
} Color;

// # Struct TreeNode
// # Intro: red-black-tree's node
//  - int value: node's value
//  - Color color: node's color
//  - TreeNode* child[2]: child[0]=left child, child[1]=right child
typedef struct TreeNode{
  int value; // NIL node => value:-1
  Color color;
  struct TreeNode* child[2];
}TreeNode ;

// # Struct BlackRedTree
// # Intro: red-black-tree
//  - TreeNode* root: tree's root
typedef struct BlackRedTree{
  TreeNode* root;
}BlackRedTree ;

// # Function node_init
// # Intro: get a node with value input
//  - int value: value for node
//  - returns: a node with value input, 2 children point to NULL
TreeNode* node_init(int value){
  TreeNode* res = (TreeNode*)malloc(sizeof(TreeNode));
  if(value < 0){
    res->color = RED;
    res->value = -1*value;
  }
  else{
    res->color = BLACK;
    res->value = value;
  }
  res->child[0] = NULL;
  res->child[1] = NULL;
  return res;
}

// # Function node_nil
// # Intro: get a nil node
//  - returns: a nil node (color is BLACK)
TreeNode* node_nil(){
  TreeNode* res = (TreeNode*)malloc(sizeof(TreeNode));
  res->value = -1;
  res->color = BLACK;
  res->child[0] = NULL;
  res->child[1] = NULL;
  return res;
}

// # Function node_is_nil
// # Intro: judge input node is nil or not
//  - TreeNode* node: the judged node
//  - returns: 1=>nil node, 0=>not nil node
int node_is_nil(TreeNode* node){
  if(node->value == -1) return 1;
  return 0;
}

// # Function node_delete
// # Intro: delete node
//  - TreeNode* node: deleted note
//  - returns: void
void node_delete(TreeNode* node){
  if(node == NULL) return;
  free(node);
  node = NULL;
}

// # Function tree_init
// # Intro: get an empty red-black-tree
//  - returns: an empty red-black-tree
BlackRedTree* tree_init(){
  BlackRedTree* res = (BlackRedTree*)malloc(sizeof(BlackRedTree));
  res->root = NULL;
  return res;
}

// # Function tree_delete_help
// # Intro: recursivily delete nodes in tree
//  - TreeNode* node: deleted node in tree
//  - returns: void
void tree_delete_help(TreeNode* node){
  if(node==NULL) return;
  tree_delete_help(node->child[0]);
  tree_delete_help(node->child[1]);
  node_delete(node);
}

// # Function tree_delete
// # Intro: delete tree
//  - BlackRedTree* tree: deleted tree
//  - returns: void
void tree_delete(BlackRedTree* tree){
  if(tree==NULL) return;
  tree_delete_help(tree->root);
  tree = NULL;
}

// # Function tree_build_help
// # Intro: recursivily build node, and build the relationship between nodes
//  - int* nums: preorder sequence
//  - int low: current smallest index in preorder
//  - int high: current largest index in preorder
//  - returns: current build node
TreeNode* tree_build_help(int* nums, int low, int high){
  if(high < low) return node_nil();
  TreeNode* node = node_init(nums[low]);
  int root_num = node->value;
  // <key point> : if idx dosent match any number, it will be high+1
  int idx;
  for(idx=low+1; idx<=high; idx++){
    int cur_num = nums[idx];
    if(cur_num<0) cur_num = -1*cur_num;
    if(cur_num > root_num) break;
  }
  node->child[0] = tree_build_help(nums, low+1, idx-1);
  node->child[1] = tree_build_help(nums, idx, high);
  return node;
}

// # Function tree_build_by_preorder
// # Intro: create a tree by giving preorder sequence
//  - int* nums: preorder sequence
//  - int size: sequence size
//  - returns: red-black-tree
BlackRedTree* tree_build_by_preorder(int* nums, int size){
  BlackRedTree* res = tree_init();
  res->root = tree_build_help(nums, 0, size-1);
  return res;
}

// # Function tree_is_black_red_help
// # Intro: judge legality by recursivily(DFS way) scanning all node 
//  - TreeNode* node: current tree node
//  - TreeNode* parent: current node's parent (Root node's parent is NULL)
//  - int black_count: count how many black nodes we meet
//  - returns: 0=>not legal, 1=>legal
int tree_is_black_red_help(TreeNode* node, TreeNode* parent, int black_count){
  if(node==NULL) return 1;
  if(parent==NULL){
    // current node is root node
    if(node->color == RED) return 0;
    return 1*tree_is_black_red_help(node->child[0], node, 1)*tree_is_black_red_help(node->child[1], node, 1);
  }
  else if(node_is_nil(node)){
    // current node is nil node
    black_count++;
    if(nil_length==0){
      // first meet nil node
      nil_length = black_count;
      return 1;
    }
    if(black_count!=nil_length) return 0;
    return 1;
  }
  else{
    // current node is normal node
    if(parent->color==RED && node->color==RED) return 0;
    if(node->color == BLACK) black_count++;
    return 1*tree_is_black_red_help(node->child[0], node, black_count)*tree_is_black_red_help(node->child[1], node, black_count);
  }
}

// # Function tree_is_black_red
// # Intro: judge the tree's legality
//  - BlackRedTree* tree: red-black-tree
//  - returns: 0=>not legal, 1=>legal
int tree_is_black_red(BlackRedTree* tree){
  if(tree==NULL || tree->root==NULL) return 0;
  nil_length = 0;
  return tree_is_black_red_help(tree->root, NULL, 0);
}

int main(){
  int case_count;
  scanf("%d", &case_count);
  BlackRedTree* trees[case_count];
  for(int i=0; i<case_count; i++){
    int size;
    scanf("%d", &size);
    int nums[size];
    for(int j=0; j<size; j++) scanf("%d", &nums[j]);
    trees[i] = tree_build_by_preorder(nums, size);
  }
  for(int i=0; i<case_count; i++){
    if(tree_is_black_red(trees[i])) printf("Yes\n");
    else printf("No\n");
    tree_delete(trees[i]);
  }
  return 0;
}
