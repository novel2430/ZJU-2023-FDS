#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType Element;
    Tree  Left;
    Tree  Right;
};

Tree BuildTree(); /* details omitted */

int Isomorphic( Tree T1, Tree T2 );

int checkValue(Tree n1, Tree n2){
  if(n1!=NULL && n2!=NULL && n1->Element==n2->Element) return 1;
  if(n1==NULL && n2==NULL) return 1;
  return 0;
}
int checkChild(Tree n1, Tree n2){
  Tree n1_left = n1->Left;
  Tree n1_right = n1->Right;
  Tree n2_left = n2->Left;
  Tree n2_right = n2->Right;
  if(checkValue(n1_left, n2_left) && checkValue(n1_right, n2_right)) return 1; // same
  if(checkValue(n1_left, n2_right) && checkValue(n1_right, n2_left)) return 2; // same with swap
  return 0; // not same
}
int Isomorphic_help( Tree T1, Tree T2 ){
  if(T1==NULL && T2==NULL) return 1;
  int situation = checkChild(T1, T2);
  if(situation==1){
    int r1 = Isomorphic_help(T1->Left, T2->Left);
    int r2 = Isomorphic_help(T1->Right, T2->Right);
    return r1*r2;
  }
  else if(situation==2){
    int r1 = Isomorphic_help(T1->Left, T2->Right);
    int r2 = Isomorphic_help(T1->Right, T2->Left);
    return r1*r2;
  }
  else{
    return 0;
  }
}
int Isomorphic( Tree T1, Tree T2 ){
  int res = checkValue(T1, T2);
  if(res==0) return 0;
  return Isomorphic_help(T1, T2);
}

int main()
{
    Tree T1, T2;
    /* T1 = BuildTree(); */
    /* T2 = BuildTree(); */
    printf("%d\n", Isomorphic(T1, T2));
    return 0;
}

/* Your function will be put here */

