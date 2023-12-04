// USING DINIC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 2000
#define INF 0x3f3f3f3f

typedef enum { FALSE, TRUE } boolean;
typedef struct Graph{
  int edge_num;
  int node_num;
  int flow[MAXN][MAXN];
  char dict[MAXN][4];
}Graph ;

typedef struct QueueNode{
  int val;
  struct QueueNode* next;
}QueueNode ;
typedef struct Queue{
  QueueNode* head;
  QueueNode* tail;
}Queue ;

QueueNode* queue_node_init(int val){
  QueueNode* res = (QueueNode*)malloc(sizeof(QueueNode));
  res->val = val;
  res->next = NULL;
  return res;
}
Queue* queue_init(){
  Queue* res = (Queue*)malloc(sizeof(Queue));
  res->head = queue_node_init(0);
  res->tail = res->head;
  return res;
}
void queue_insert(Queue* queue, int val){
  QueueNode* node = queue_node_init(val);
  queue->tail->next = node; 
  queue->tail = node;
  queue->head->val++;
}
int queue_pop(Queue* queue){
  int res = -1;
  QueueNode* cur = queue->head->next;
  if(cur!=NULL){
    res = cur->val;
    queue->head->next = cur->next;
    if(cur==queue->tail){
      queue->tail = queue->head;
    }
    free(cur);
    cur = NULL;
    queue->head->val--;
  }
  return res;
}
void queue_delete(Queue* queue){
  QueueNode* cur = queue->head;
  while(cur!=NULL){
    QueueNode* tmp = cur;
    cur = cur->next;
    free(tmp);
    tmp = NULL;
  }
  free(queue);
  queue = NULL;
}
boolean queue_is_empty(Queue* queue){
  if(queue->head==queue->tail) return TRUE;
  return FALSE;
}

Graph* graph_init(char* start, char* end, int edge_num){
  Graph* res = (Graph*)malloc(sizeof(Graph));
  res->edge_num = 2;
  res->node_num = edge_num;
  memset(res->flow, 0, sizeof(res->flow));
  strcpy(res->dict[0], start);
  strcpy(res->dict[1], end);
  return res;
}
void graph_insert_edge(Graph* graph, char* planet1, char* planet2, int weight){
  int p1_idx = -1;
  int p2_idx = -1;
  for(int i=0; i<graph->node_num; i++){
    if(strcmp(graph->dict[i], planet1)==0){
      p1_idx = i;
    }
    if(strcmp(graph->dict[i], planet2)==0){
      p2_idx = i;
    }
  }
  if(p1_idx==-1){
    strcpy(graph->dict[graph->node_num], planet1);
    p1_idx = graph->node_num;
    graph->node_num++;
  }
  if(p2_idx==-1){
    strcpy(graph->dict[graph->node_num], planet2);
    p2_idx = graph->node_num;
    graph->node_num++;
  }
  graph->flow[p1_idx][p2_idx] = weight;
}

int min(int a, int b){
  if(a>b) return b;
  return a;
}
int count_node_flow_sum(Graph* graph, int idx){
  int res = 0;
  for(int i=0; i<graph->node_num; i++){
    res += graph->flow[idx][i];
  }
  return res;
}
void build_level_graph_bfs(int* level, Graph* graph){
  Queue* queue = queue_init();
  queue_insert(queue, 0);
  level[0] = 1;
  while(!queue_is_empty(queue)){
    int cur_idx = queue_pop(queue);
    for(int i=0; i<graph->node_num; i++){
      if(level[i]==0 && graph->flow[cur_idx][i]>0){
        queue_insert(queue, i);
        level[i] = level[cur_idx]+1; 
      }
    }
  }
  queue_delete(queue);
}
int find_blocking_flow_dfs(Graph* graph, int* level, int cur_idx, int last_flow){
  if(cur_idx==1){
    // meet end
    return last_flow;
  }
  int res = 0;
  for(int i=0; i<graph->node_num; i++){
    if(level[i]==level[cur_idx]+1 && graph->flow[cur_idx][i]>0){
      int flow = find_blocking_flow_dfs(graph, level, i, min(last_flow-res, graph->flow[cur_idx][i]));
      graph->flow[cur_idx][i] -= flow;
      graph->flow[i][cur_idx] += flow;
      res += flow;
    }
  }
  return res;
}

void dinic(Graph* graph){
  int level[MAXN];
  while(1){
    // build level graph
    memset(level, 0, sizeof(level));
    build_level_graph_bfs(level, graph);
    // find blocking flow in level graph
    // &
    // update residual graph
    if(!find_blocking_flow_dfs(graph, level, 0, INF)){
      // No blocking flow then break
      break;
    }
  }
}

int main(int argc, char *argv[]){
  char start[4];
  char end[4];
  int edge_num;
  scanf("%s %s %d", start, end, &edge_num);
  Graph* graph = graph_init(start, end, edge_num);
  for(int i=0; i<edge_num; i++){
    char planet1[4];
    char planet2[4];
    int capacity;
    scanf("%s %s %d", planet1, planet2, &capacity);
    graph_insert_edge(graph, planet1, planet2, capacity);
  }
  int before = count_node_flow_sum(graph, 0);
  dinic(graph);
  int after = count_node_flow_sum(graph, 0);
  printf("%d\n", before-after);
  return 0;
}
