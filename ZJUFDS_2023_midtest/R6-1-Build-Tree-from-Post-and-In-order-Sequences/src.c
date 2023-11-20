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

Tree node_init(int num){
    Tree res = (Tree)malloc(sizeof(struct TreeNode));
    res->Left = NULL;
    res->Right = NULL;
    res->Element = num;
    return res;
}


Tree BuildTree( int inorder[], int postorder[], int N ){
    if(inorder == NULL || postorder==NULL || N==0) return NULL;
    int size = N;
    int cur_root_value = postorder[size-1];
    // find root idx
    int idx = 0;
    for(int i=0; i<size; i++){
        if(inorder[i] == cur_root_value){
            idx = i;
            break;
        }
    }
    Tree cur_root = node_init(cur_root_value);
    // build Left
    int new_in[MAXN], new_post[MAXN];
    for(int i=0; i<idx; i++){
        new_in[i] = inorder[i];
        new_post[i] = postorder[i];
    }
    cur_root->Left = BuildTree(new_in, new_post, idx);
    // build Right
    for(int i=0; i<size-idx-1; i++){
        new_in[i] = inorder[i+idx+1];
        new_post[i] = postorder[i+idx];
    }
    cur_root->Right = BuildTree(new_in, new_post, size-idx-1);
    return cur_root;
}
