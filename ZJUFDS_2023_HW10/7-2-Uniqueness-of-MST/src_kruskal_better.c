#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 150000
typedef enum { FALSE, TRUE } boolean;
typedef enum {
  UNIQUE,
  PLURAL,
  NONE
} ResType;

typedef struct Node{
  int val;
  struct Node* parent;
}Node ;
typedef struct Edge{
  Node* v1;
  Node* v2;
  int weight;
}Edge ;
typedef struct Graph{
  int node_num;
  int edge_num;
  Edge* edges[MAXN];
  Node* nodes[MAXN];
}Graph ;

Node* node_init(int val){
  Node* res = (Node*)malloc(sizeof(Node));
  res->val = val;
  res->parent = res;
  return res;
}
Node* node_find_parent(Node* node){
  if(node == node->parent) return node;
  node->parent = node_find_parent(node->parent);
  return node->parent;
}
boolean node_is_same_set(Node* node1, Node* node2){
  Node* n1_parent = node_find_parent(node1);
  Node* n2_parent = node_find_parent(node2);
  if(n1_parent==n2_parent) return TRUE;
  return FALSE;
}
void node_union(Node* node1, Node* node2){
  node_find_parent(node1)->parent = node_find_parent(node2);
}

Graph* graph_init(int node_num, int edge_num){
  Graph* res = (Graph*)malloc(sizeof(Graph));
  res->node_num = node_num;
  res->edge_num = edge_num;
  for(int i=0; i<res->node_num; i++){
    res->nodes[i] = node_init(i+1);
  }
  return res;
}
void graph_insert_edge(Graph* graph, int idx, int v1, int v2, int weight){
  graph->edges[idx] = (Edge*)malloc(sizeof(Edge));
  graph->edges[idx]->v1 = graph->nodes[v1-1];
  graph->edges[idx]->v2 = graph->nodes[v2-1];;
  graph->edges[idx]->weight = weight;
}

void merge_sort_conquer(Edge** arr, Edge** tmp, int low, int mid, int high){
  int start_1 = low;
  int end_1 = mid;
  int start_2 = mid+1;
  int end_2 = high;
  int idx = 0;
  while(start_1<=end_1 && start_2<=end_2){
    if(arr[start_1]->weight < arr[start_2]->weight){
      tmp[idx++] = arr[start_1++];
    }
    else{
      tmp[idx++] = arr[start_2++];
    }
  }
  while(start_1 <= end_1){
    tmp[idx++] = arr[start_1++];
  }
  while(start_2 <= end_2){
    tmp[idx++] = arr[start_2++];
  }
  idx = 0;
  while(low <= high){
    arr[low++] = tmp[idx++];
  }
}
void merge_sort_divide(Edge** arr, Edge** tmp, int low, int high){
  if(low<high){
    int mid = (low+high)/2;
    merge_sort_divide(arr, tmp, low, mid);
    merge_sort_divide(arr, tmp, mid+1, high);
    merge_sort_conquer(arr, tmp, low, mid, high);
  }
}
void merge_sort_edge(Graph* graph){
  Edge* tmp[MAXN];
  merge_sort_divide(graph->edges, tmp, 0, graph->edge_num-1);
}

ResType kruskal(Graph* graph, int* mst_val){
  int mst_edge_count = 0;
  // find MST
  int flag = 0;
  for(int i=0; i<graph->edge_num&&mst_edge_count<graph->node_num-1; i++){
    Edge* cur_edge = graph->edges[i];
    if(!node_is_same_set(cur_edge->v1, cur_edge->v2)){
      for(int j=i+1; flag==0&&j<graph->edge_num&&graph->edges[j]->weight==cur_edge->weight; j++){
        Edge* edge = graph->edges[j];
        if(node_is_same_set(cur_edge->v1, edge->v1) && node_is_same_set(cur_edge->v2, edge->v2)){
          flag = 1;
          break;
        }
        if(node_is_same_set(cur_edge->v1, edge->v2) && node_is_same_set(cur_edge->v2, edge->v1)){
          flag = 1;
          break;
        }
      }
      (*mst_val) += cur_edge->weight;
      mst_edge_count++;
      node_union(cur_edge->v1, cur_edge->v2);
    }
  }
  if(mst_edge_count!=graph->node_num-1) return NONE;
  if(flag) return PLURAL;
  return UNIQUE;
}
int graph_count_set(Graph* graph){
  int res = 0;
  for(int i=0; i<graph->node_num; i++){
    if(graph->nodes[i]->parent==graph->nodes[i]) res++;
  }
  return res;
}

int main(int argc, char *argv[]){
  int node_num, edge_num;
  scanf("%d %d", &node_num, &edge_num);
  Graph* graph = graph_init(node_num, edge_num);
  for(int i=0; i<edge_num; i++){
    int v1, v2, weight;
    scanf("%d %d %d", &v1, &v2, &weight);
    graph_insert_edge(graph, i, v1, v2, weight);
  }
  merge_sort_edge(graph);
  int mst_val = 0;
  ResType res = kruskal(graph, &mst_val);
  switch (res) {
    case UNIQUE:
      printf("%d\nYes\n", mst_val);
      break;
    case PLURAL:
      printf("%d\nNo\n", mst_val);
      break;
    case NONE:
      printf("No MST\n%d\n", graph_count_set(graph));
      break;
    default:
      break;
  }
  return 0;
}
