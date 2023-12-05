#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 2000
#define MAXE 150000
typedef enum { FALSE, TRUE } boolean;
typedef enum {
  UNIQUE,
  PLURAL,
  NONE
} ResType;

typedef struct Edge{
  int v1;
  int v2;
  int weight;
}Edge ;
typedef struct Graph{
  int node_num;
  int edge_num;
  Edge* weights[MAXN][MAXN];
  Edge* MST_edges[MAXE];
}Graph ;

typedef struct HeapNode{
  Edge* edge;
  int to;
}HeapNode ;

typedef struct Heap{
  int size;
  HeapNode* value[MAXE];
}Heap ;

void swap(int pos1, int pos2, Heap* H){
  HeapNode* tmp = H->value[pos1];
  H->value[pos1] = H->value[pos2];
  H->value[pos2] = tmp;
}
int min_idx(int idx1, int idx2, Heap* H){
  if(H->value[idx1]->edge->weight < H->value[idx2]->edge->weight) return idx1;
  return idx2;
}
Heap* heap_init(){
  Heap* res = (Heap*)malloc(sizeof(Heap));
  res->size = 0;
  return res;
}
void heap_node_delete(HeapNode* node){
  if(node==NULL) return;
  free(node);
  node = NULL;
}
boolean heap_is_empty(Heap* heap){
  if(heap->size==0) return TRUE;
  else return FALSE;
}
void heap_delete(Heap* heap){
  if(heap==NULL) return;
  for(int i=1; i<=heap->size; i++){
    heap_node_delete(heap->value[i]);
  }
  free(heap);
  heap = NULL;
}
HeapNode heap_pop_min(Heap* heap){
  HeapNode* res = heap->value[1];
  heap->value[1] = heap->value[heap->size];
  heap->size--;
  for(int pos=1, child_idx; pos*2<=heap->size; pos=child_idx){
    int val = heap->value[pos]->edge->weight;
    if(pos*2+1 <= heap->size)
      child_idx = min_idx(pos*2, pos*2+1, heap);
    else child_idx = pos*2;
    if(heap->value[child_idx]->edge->weight < val) swap(pos, child_idx, heap);
    else break;
  }
  HeapNode node;
  node.edge = res->edge;
  node.to = res->to;
  heap_node_delete(res);
  return node;
}
void heap_insert(Heap* heap, Edge* edge, int to){
  if(heap==NULL) return;
  HeapNode* new_node = (HeapNode*)malloc(sizeof(HeapNode));
  new_node->edge = edge;
  new_node->to = to;
  heap->value[heap->size+1] = new_node;
  heap->size++;
  for(int pos=heap->size,parent_idx; pos>1; pos=parent_idx){
    int val = heap->value[pos]->edge->weight;
    if(pos%2==0) parent_idx = pos/2;
    else parent_idx = (pos-1)/2;
    if(heap->value[parent_idx]->edge->weight>val) swap(pos, parent_idx, heap);
    else break;
  }
}

Graph* graph_init(int node_num, int edge_num){
  Graph* res = (Graph*)malloc(sizeof(Graph));
  res->node_num = node_num;
  res->edge_num = edge_num;
  for(int i=0; i<node_num; i++){
    for(int j=0; j<node_num; j++)
      res->weights[i][j] = NULL;
  }
  return res;
}
void graph_insert_edge(Graph* graph, int v1, int v2, int weight){
  Edge* edge = (Edge*)malloc(sizeof(Edge));
  edge->v1 = v1;
  edge->v2 = v2;
  edge->weight = weight;
  graph->weights[v1-1][v2-1] = edge;
  graph->weights[v2-1][v1-1] = edge;
}

ResType find_mst(Graph* graph, Heap* heap, boolean* visit, int start_idx, int* mst_val, int* mst_edge_count){
  visit[start_idx] = TRUE;
  for(int i=0; i<graph->node_num; i++){
    if(graph->weights[start_idx][i]!=NULL){
      heap_insert(heap, graph->weights[start_idx][i], i);
    }
  }
  while(!heap_is_empty(heap)){
    HeapNode min = heap_pop_min(heap);
    Edge* edge = min.edge;
    if(visit[min.to]) continue;
    visit[min.to] = TRUE;
    (*mst_val) += min.edge->weight;
    graph->MST_edges[(*mst_edge_count)++] = edge;
    for(int i=0; i<graph->node_num; i++){
      if(!visit[i] && graph->weights[min.to][i]!=NULL){
        heap_insert(heap, graph->weights[min.to][i], i);
      }
    }
  }
  if((*mst_edge_count)!=graph->node_num-1) return NONE;
  return UNIQUE;
}
int find_tree_count(Graph* graph, Heap* heap, boolean* visit){
  int res = 1;
  int mst_val = 0;
  int mst_edge_count = 0;
  for(int i=0; i<graph->node_num; i++){
    if(!visit[i]){
      find_mst(graph, heap, visit, i, &mst_val, &mst_edge_count);
      res++;
    }
  }
  return res;
}
ResType tree_unique(Graph* graph, Heap* heap, int min_mst_val, int mst_edge_count){
  boolean visit[MAXN];
  for(int ii=0; ii<mst_edge_count; ii++){
    Edge* cannot_use_edge = graph->MST_edges[ii];
    memset(visit, FALSE, sizeof(visit));
    visit[0] = TRUE;
    int mst_val = 0;
    for(int i=0; i<graph->node_num; i++){
      if(graph->weights[0][i]!=NULL){
        heap_insert(heap, graph->weights[0][i], i);
      }
    }
    while(!heap_is_empty(heap)){
      HeapNode min = heap_pop_min(heap);
      Edge* edge = min.edge;
      if(visit[min.to] || edge==cannot_use_edge) continue;
      visit[min.to] = TRUE;
      mst_val += edge->weight;
      for(int i=0; i<graph->node_num; i++){
        if(!visit[i] && graph->weights[min.to][i]!=NULL){
          heap_insert(heap, graph->weights[min.to][i], i);
        }
      }
    }
    if(mst_val==min_mst_val) return PLURAL;
  }
  return UNIQUE;
}
ResType prim(Graph* graph, int* mst_val, int* tree_count){
  int mst_edge_count = 0;
  Heap* heap = heap_init();
  boolean visit[MAXN];
  memset(visit, FALSE, sizeof(visit));
  ResType res = find_mst(graph, heap, visit, 0, mst_val, &mst_edge_count);
  if(res==NONE){
    (*tree_count) = find_tree_count(graph, heap, visit);
  }
  else{
    res = tree_unique(graph, heap, *mst_val, mst_edge_count);
  }
  heap_delete(heap);
  return res;
}


int main(int argc, char *argv[]){
  int node_num, edge_num;
  scanf("%d %d", &node_num, &edge_num);
  Graph* graph = graph_init(node_num, edge_num);
  for(int i=0; i<edge_num; i++){
    int v1, v2, weight;
    scanf("%d %d %d", &v1, &v2, &weight);
    graph_insert_edge(graph, v1, v2, weight);
  }
  int mst_val = 0;
  int tree_count = 0;
  ResType res = prim(graph, &mst_val, &tree_count);
  switch (res) {
    case UNIQUE:
      printf("%d\nYes\n", mst_val);
      break;
    case PLURAL:
      printf("%d\nNo\n", mst_val);
      break;
    case NONE:
      printf("No MST\n%d\n", tree_count);
      break;
    default:
      break;
  }
  return 0;
}
