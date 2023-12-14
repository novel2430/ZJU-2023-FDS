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
    PtrToVNode node = ptr_node_init(v2);
    if(res->Array[v1]==NULL) res->Array[v1] = node;
    else{
      node->Next = res->Array[v1];
      res->Array[v1] = node;
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
Graph build_graph_inverse(Graph graph){
  Graph res = (Graph)malloc(sizeof(struct GNode));
  res->NumOfEdges = graph->NumOfEdges;
  res->NumOfVertices = graph->NumOfVertices;
  res->Array = (PtrToVNode*)malloc(sizeof(PtrToVNode)*res->NumOfVertices);
  for(int i=0; i<res->NumOfVertices; i++) res->Array[i] = NULL;
  for(int i=0; i<res->NumOfVertices; i++){
    for(PtrToVNode cur = graph->Array[i]; cur!=NULL; cur=cur->Next){
      int v1 = cur->Vert;
      int v2 = i;
      PtrToVNode node = (PtrToVNode)malloc(sizeof(struct VNode));
      node->Vert = v2;
      node->Next = NULL;
      if(res->Array[v1]==NULL) res->Array[v1] = node;
      else{
        node->Next = res->Array[v1];
        res->Array[v1] = node;
      }
    }
  }
  return res;
}
void kosaraju_first_dfs(Graph graph, Stack* stack, Boolean* visit, Boolean* in_stack, int cur_idx){
  if(visit[cur_idx]) return;
  visit[cur_idx] = TRUE;
  for(PtrToVNode cur=graph->Array[cur_idx]; cur!=NULL; cur=cur->Next){
    kosaraju_first_dfs(graph, stack, visit, in_stack, cur->Vert);
  }
  stack_insert(stack, cur_idx);
  in_stack[cur_idx] = TRUE;
}
void kosaraju_second_dfs(Graph graph, Boolean* visit, Boolean* in_stack, int cur_idx, void (*print_visit)(Vertex V)){
  if(visit[cur_idx] || !in_stack[cur_idx]) return;
  visit[cur_idx] = TRUE;
  print_visit(cur_idx);
  for(PtrToVNode cur=graph->Array[cur_idx]; cur!=NULL; cur=cur->Next){
    kosaraju_second_dfs(graph, visit, in_stack, cur->Vert, print_visit);
  }
}
void kosaraju(Graph graph, Boolean* is_visit, int start, void (*visit)(Vertex V)){
  Graph inverse_graph = build_graph_inverse(graph);
  Stack* stack = stack_init(graph->NumOfVertices);
  Boolean is_visit_2[graph->NumOfVertices];
  Boolean in_stack[graph->NumOfVertices];
  for(int i=0; i<graph->NumOfVertices; i++) is_visit_2[i] = FALSE;
  for(int i=0; i<graph->NumOfVertices; i++) in_stack[i] = FALSE;
  kosaraju_first_dfs(graph, stack, is_visit, in_stack, start);
  while(!stack_is_empty(stack)){
    int stack_top = stack_pop(stack);
    if(is_visit_2[stack_top]) continue;
    kosaraju_second_dfs(inverse_graph, is_visit_2, in_stack, stack_top, visit);
    printf("\n");
  }
}
void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) ){
  Boolean is_visit[G->NumOfVertices];
  for(int i=0; i<G->NumOfVertices; i++) is_visit[i] = FALSE;
  for(int i=0; i<G->NumOfVertices; i++){
    if(is_visit[i]) continue;
    kosaraju(G, is_visit, i, visit);
  }

}
