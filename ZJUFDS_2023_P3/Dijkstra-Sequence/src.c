#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10000

typedef enum { FALSE, TRUE } boolean;

typedef int Element ;

typedef struct EdgeNode{
  int adjvex;
  int weight;
  struct EdgeNode* next;
} EdgeNode;

typedef struct VertexNode{
  Element data;
  EdgeNode* first_edge;
}VertexNode ;

typedef struct Graph{
  int node_num;
  int edge_num;
  VertexNode* adj_list[MAXN];
}Graph ;

typedef struct HeapNode{
  int weight;
  int idx;
}HeapNode ;

typedef struct Heap{
  int size;
  HeapNode* value[MAXN];
}Heap ;

// VertexNode op
VertexNode* vertex_node_init(Element data);
void vertex_node_insert_edge(VertexNode* node, int adjvex, int weight);

// EdgeNode op
EdgeNode* edge_node_init(int adjvex, int weight);

// Graph op
Graph* graph_init(int node_num, int edge_num);
void graph_insert_edge(Graph* graph, Element v1, Element v2, int weight);
boolean is_dijkstra_sequence(Graph* graph, int* seq);
boolean is_dijkstra_sequence_normal(Graph* graph, int* seq, int* dist, boolean* visit);
boolean is_dijkstra_sequence_heap(Graph* graph, int* seq, int* dist, boolean* visit, Heap* heap);

// Heap op
Heap* heap_init();
HeapNode heap_pop_min(Heap* heap);
void heap_insert(Heap* heap, int weight, int idx);
boolean heap_is_empty(Heap* heap);


// VertexNode op
VertexNode* vertex_node_init(Element data){
  VertexNode* res = (VertexNode*)malloc(sizeof(VertexNode));
  res->data = data;
  res->first_edge = NULL;
  return res;
}
void vertex_node_insert_edge(VertexNode* node, int adjvex, int weight){
  if(node==NULL) return;
  EdgeNode* edge_node = edge_node_init(adjvex, weight);
  if(node->first_edge!=NULL){
    edge_node->next = node->first_edge;
  }
  node->first_edge = edge_node;
}

// EdgeNode op
EdgeNode* edge_node_init(int adjvex, int weight){
  EdgeNode* res = (EdgeNode*)malloc(sizeof(EdgeNode));
  res->adjvex = adjvex;
  res->weight = weight;
  res->next = NULL;
  return res;
}

// Graph op
Graph* graph_init(int node_num, int edge_num){
  Graph* res = (Graph*)malloc(sizeof(Graph));
  res->node_num = node_num;
  res->edge_num = edge_num;
  for(int i=0; i<node_num; i++){
    res->adj_list[i] = vertex_node_init(i+1);
  }
  return res;
}
void graph_insert_edge(Graph* graph, Element v1, Element v2, int weight){
  if(graph==NULL) return;
  vertex_node_insert_edge(graph->adj_list[v1-1], v2-1, weight);
  vertex_node_insert_edge(graph->adj_list[v2-1], v1-1, weight);
}
boolean is_dijkstra_sequence(Graph* graph, int* seq){
  if(graph==NULL || seq==NULL || graph->node_num==0 || graph->edge_num==0) return FALSE;
  int dist[graph->node_num];
  memset(dist, 127, sizeof(dist));
  boolean visit[graph->node_num];
  memset(visit, FALSE, sizeof(visit));
  Heap* heap = heap_init();
  boolean res = is_dijkstra_sequence_heap(graph, seq, dist, visit, heap);
  // boolean res = is_dijkstra_sequence_normal(graph, seq, dist, visit);
  free(heap);
  return res;
}
boolean is_dijkstra_sequence_heap(Graph* graph, int* seq, int* dist, boolean* visit, Heap* heap){
  int node_num = graph->node_num;
  dist[seq[0]-1] = 0;
  heap_insert(heap, 0, seq[0]-1); 
  int i=0;
  while(heap_is_empty(heap)==FALSE){
    HeapNode min = heap_pop_min(heap);
    if(visit[min.idx]==TRUE) continue; // means current min is old one (already update)
    int cur_idx = seq[i]-1;
    if(min.weight<dist[cur_idx]) return FALSE;
    visit[min.idx] = TRUE;
    for(EdgeNode* cur = graph->adj_list[min.idx]->first_edge; cur!=NULL; cur=cur->next){
      if(visit[cur->adjvex]==FALSE && dist[cur->adjvex] > dist[cur_idx]+cur->weight){
        dist[cur->adjvex] =  dist[cur_idx]+cur->weight;
        heap_insert(heap, dist[cur_idx]+cur->weight, cur->adjvex);
      }
    }
    i++;
  }
  return TRUE;
}
boolean is_dijkstra_sequence_normal(Graph* graph, int* seq, int* dist, boolean* visit){
  int node_num = graph->node_num;
  dist[seq[0]-1] = 0;
  for(int i=0; i<node_num; i++){
    int cur_idx = seq[i]-1;
    // check is the smallest
    for(int j=0; j<node_num; j++){
      if(visit[j]==FALSE && dist[j]<dist[cur_idx]) return FALSE;
    }
    // update dist array
    visit[cur_idx] = TRUE;
    for(EdgeNode* cur = graph->adj_list[cur_idx]->first_edge; cur!=NULL; cur=cur->next){
      if(visit[cur->adjvex]==FALSE && dist[cur->adjvex] > dist[cur_idx]+cur->weight){
        dist[cur->adjvex] =  dist[cur_idx]+cur->weight;
      }
    }
  } 
  return TRUE;
}

// Heap op
void swap(int pos1, int pos2, Heap* H){
  HeapNode* tmp = H->value[pos1];
  H->value[pos1] = H->value[pos2];
  H->value[pos2] = tmp;
}
int min_idx(int idx1, int idx2, Heap* H){
  if(H->value[idx1]->weight < H->value[idx2]->weight) return idx1;
  return idx2;
}
Heap* heap_init(){
  Heap* res = (Heap*)malloc(sizeof(Heap));
  res->size = 0;
  return res;
}
HeapNode heap_pop_min(Heap* heap){
  HeapNode* res = heap->value[1];
  heap->value[1] = heap->value[heap->size];
  heap->size--;
  for(int pos=1, child_idx; pos*2<=heap->size; pos=child_idx){
    int val = heap->value[pos]->weight;
    if(pos*2+1 <= heap->size)
      child_idx = min_idx(pos*2, pos*2+1, heap);
    else child_idx = pos*2;
    if(heap->value[child_idx]->weight < val) swap(pos, child_idx, heap);
    else break;
  }
  HeapNode node;
  node.weight = res->weight;
  node.idx = res->idx;
  free(res);
  return node;
}
void heap_insert(Heap* heap, int weight, int idx){
  if(heap==NULL) return;
  HeapNode* new_node = (HeapNode*)malloc(sizeof(HeapNode));
  new_node->weight = weight;
  new_node->idx = idx;
  heap->value[heap->size+1] = new_node;
  heap->size++;
  for(int pos=heap->size,parent_idx; pos>1; pos=parent_idx){
    int val = heap->value[pos]->weight;
    if(pos%2==0) parent_idx = pos/2;
    else parent_idx = (pos-1)/2;
    if(heap->value[parent_idx]->weight>val) swap(pos, parent_idx, heap);
    else break;
  }
}
boolean heap_is_empty(Heap* heap){
  if(heap->size==0) return TRUE;
  else return FALSE;
}

int main(int argc, char *argv[]){
  // build graph
  int node_num, edge_num;
  scanf("%d %d", &node_num, &edge_num);
  Graph* graph = graph_init(node_num, edge_num);
  for(int i=0; i<edge_num; i++){
    int v1, v2, weight;
    scanf("%d %d %d", &v1, &v2, &weight);
    graph_insert_edge(graph, v1, v2, weight);
  }
  int case_count;
  scanf("%d", &case_count);
  for(int i=0; i<case_count; i++){
    int seq[graph->node_num];
    for(int j=0; j<graph->node_num; j++){
      scanf("%d", &seq[j]);
    }
    if(is_dijkstra_sequence(graph, seq)==TRUE) printf("Yes\n");
    else printf("No\n");
  }
  return 0;
}
