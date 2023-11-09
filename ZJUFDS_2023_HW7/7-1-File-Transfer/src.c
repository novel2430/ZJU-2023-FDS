#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef struct Node{
  struct Node* parent;
}Node ;

// Node op
Node* node_init(){
  Node* res = (Node*)malloc(sizeof(Node));
  res->parent = res;
  return res;
}
Node* node_check_father(Node* node){
  if(node->parent == node) return node;
  node->parent = node_check_father(node->parent);
  return node->parent;
}
Node* node_check_father_non_recursice(Node* node){
  // find root
  Node* root = node;
  while(root->parent!=root) root = root->parent;
  // set root
  Node* cur = node;
  while(cur!=root){
    Node* tmp = cur->parent;
    cur->parent = root;
    cur = tmp;
  }
  return root;
}
void node_build_connect(Node* n1, Node* n2){
  if(n1==NULL || n2==NULL) return;
  node_check_father(n1)->parent = node_check_father(n2);
}
int node_is_connect(Node* n1, Node* n2){
  Node* n1_father = node_check_father(n1);
  Node* n2_father = node_check_father(n2);
  if(n1_father==n2_father) return true;
  return false;
}

int count_components(Node** nodes, int size){
  int count = 0;
  for(int i=0; i<size; i++){
    if(nodes[i]->parent==nodes[i]) count++;
  }
  return count;
}

int main(int argc, char *argv[]){
  int size;
  scanf("%d", &size);
  Node* nodes[size];
  for(int i=0; i<size; i++) nodes[i] = node_init();
  while(1){
    getchar();
    char op;
    scanf("%c", &op);
    if(op=='S') break;
    int n1, n2;
    scanf("%d %d", &n1, &n2);
    if(op=='C'){
      if(node_is_connect(nodes[n1-1], nodes[n2-1])){
        printf("yes\n");
      }
      else printf("no\n");
    }
    else if(op=='I'){
      node_build_connect(nodes[n1-1], nodes[n2-1]);
    }
  }
  int count = count_components(nodes, size);
  if(count==1) printf("The network is connected.\n");
  else printf("There are %d components.\n", count);
}
