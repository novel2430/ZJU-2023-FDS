#include <stdio.h>
#include <stdlib.h>

#define MaxVertices 10  /* maximum number of vertices */
typedef int Vertex;     /* vertices are numbered from 0 to MaxVertices-1 */
typedef struct VNode *PtrToVNode;
struct VNode {
    Vertex Vert;
    PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode {
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};

Graph ReadG(); /* details omitted */

void PrintV( Vertex V )
{
   printf("%d ", V);
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) );

int main()
{
    Graph G = ReadG();
    StronglyConnectedComponents( G, PrintV );
    return 0;
}

PtrToVNode ptr_node_init(Vertex v){
  PtrToVNode res = (PtrToVNode)malloc(sizeof(struct VNode));
  res->Vert = v;
  res->Next = NULL;
  return res;
}
Graph ReadG(){
  Graph res = (Graph)malloc(sizeof(struct GNode));
  int vertice_num, edge_num;
  scanf("%d %d", &vertice_num, &edge_num);
  res->NumOfVertices = vertice_num;
  res->NumOfEdges = edge_num;
  res->Array = (PtrToVNode*)malloc(sizeof(PtrToVNode)*res->NumOfVertices);
  for(int i=0; i<vertice_num; i++) res->Array[i] = NULL;
  for(int i=0; i<edge_num; i++){
    int v1, v2;
    scanf("%d %d", &v1, &v2);
    if(res->Array[v1]==NULL) res->Array[v1] = ptr_node_init(v2);
    else{
      PtrToVNode tmp = res->Array[v1]->Next;
      res->Array[v1]->Next = ptr_node_init(v2);
      res->Array[v1]->Next->Next = tmp;
    }
  }
  return res;
}

/* Your function will be put here */
typedef enum Boolean {FALSE, TRUE} Boolean ;
typedef int StackVal; ;
typedef struct Stack{
  int max_size; 
  int cur_top;
  StackVal* array;
} Stack;
Stack* stack_init(int max){
  Stack* res = (Stack*)malloc(sizeof(Stack));
  res->max_size = max;
  res->cur_top = -1;
  res->array = (StackVal*)malloc(sizeof(StackVal)*res->max_size);
  return res;
}
Boolean stack_is_empty(Stack* stack){
  if(stack->cur_top==-1) return TRUE;
  return FALSE;
}
void stack_insert(Stack* stack, StackVal val){
  stack->cur_top++;
  stack->array[stack->cur_top] = val;
}
StackVal stack_pop(Stack* stack){
  int res = stack->array[stack->cur_top]; 
  stack->cur_top--;
  return res;
}
StackVal stack_peak(Stack* stack){
  int res = stack->array[stack->cur_top]; 
  return res;
}
void stack_empty(Stack* stack){
  while(!stack_is_empty(stack)){
    stack_pop(stack);
  }
}

int min(int a, int b){
  if(a < b) return a;
  return b;
}
void tarjan(Graph G, Stack* stack, int* dfn, int* low, Boolean* in_stack, int cur_idx, int* visit_count, void (*visit)(Vertex V)){
  dfn[cur_idx] = *visit_count;
  low[cur_idx] = *visit_count;
  (*visit_count)++;
  stack_insert(stack, cur_idx);
  in_stack[cur_idx] = TRUE;
  for(PtrToVNode cur=G->Array[cur_idx]; cur!=NULL; cur=cur->Next){
    if(dfn[cur->Vert]<0){
      tarjan(G, stack, dfn, low, in_stack, cur->Vert, visit_count, visit);
      low[cur_idx] = min(low[cur_idx], low[cur->Vert]);
    }
    else if(in_stack[cur->Vert]){
      low[cur_idx] = min(low[cur_idx], dfn[cur->Vert]);
    }
  }
  if(low[cur_idx]==dfn[cur_idx]){
    while(!stack_is_empty(stack)){
      int stack_top = stack_pop(stack);
      in_stack[stack_top] = FALSE;
      visit(stack_top);
      if(cur_idx==stack_top) break;
    }
    printf("\n");
  }
}
void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) ){
  Stack* stack = stack_init(G->NumOfVertices);
  int dfn[G->NumOfVertices];
  int low[G->NumOfVertices];
  Boolean in_stack[G->NumOfVertices];
  for(int i=0; i<G->NumOfVertices; i++){
    dfn[i] = -1;
    low[i] = -1;
    in_stack[i] = FALSE;
  }
  for(int i=0; i<G->NumOfVertices; i++){
    int visit_count = 0;
    if(dfn[i]==-1)
      tarjan(G, stack, dfn, low, in_stack, i, &visit_count, visit);
    stack_empty(stack);
  }
}
