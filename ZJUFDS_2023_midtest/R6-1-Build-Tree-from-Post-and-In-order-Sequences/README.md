# R6-1 Build Tree from Post- and In-order Sequences
You are supposed to write a function of constructing a binary tree with given postorder and inorder sequences.
## Format of function:
```c
Tree BuildTree( int inorder[], int postorder[], int N );
```
where `Tree` is defined as the following:
```c
typedef struct TreeNode *Tree;
struct TreeNode {
    int Element;
    Tree  Left;
    Tree  Right;
};
```
The inorder and postorder sequences are stored in int `inorder[]` and int `postorder[]`, respectively. The integer `N` is the number of nodes in the tree. The function `BuildTree` is supposed to return the pointer to the root of the constructed tree.
## Sample program of judge:
```c
#include <stdio.h>
#include <stdlib.h>

#define MAXN 10

typedef struct TreeNode *Tree;
struct TreeNode {
    int Element;
    Tree  Left;
    Tree  Right;
};

Tree BuildTree( int inorder[], int postorder[], int N );

void Inorder_output( Tree T ); /* details omitted */
void Postorder_output( Tree T ); /* details omitted */

int main()
{
    Tree T;
    int inorder[MAXN], postorder[MAXN], N, i;

    scanf("%d", &N);
    for (i=0; i<N; i++) scanf("%d", &inorder[i]);
    for (i=0; i<N; i++) scanf("%d", &postorder[i]);
    T = BuildTree(inorder, postorder, N);
    printf("Check:\n");
    Inorder_output(T);   printf("\n");
    Postorder_output(T); printf("\n");

    return 0;
}

/* Your function will be put here */
```
## Sample Input:
```
7
1 2 3 4 5 6 7
2 3 1 5 7 6 4
```
## Sample Output:
```
Check:
1 2 3 4 5 6 7 
2 3 1 5 7 6 4
```
