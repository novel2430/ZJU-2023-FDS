# Normal Dijkstra Sequence
## Chapter 1: Introduction
Dijkstra's algorithm is one of the very famous greedy algorithms.
It is used for solving the single source shortest path problem which gives the shortest paths from one particular source vertex to all the other vertices of the given graph. It was conceived by computer scientist Edsger W. Dijkstra in 1956 and published three years later.

In this algorithm, a set contains vertices included in shortest path tree is maintained. During each step, we find one vertex which is not yet included and has a minimum distance from the source, and collect it into the set. Hence step by step an ordered sequence of vertices, let's call it **Dijkstra sequence**, is generated by Dijkstra's algorithm.

On the other hand, for a given graph, there could be more than one Dijkstra sequence. Your job is to check whether a given sequence is Dijkstra sequence or not.
### Input Specification:
Each input file contains one test case. For each case, the first line contains two positive integers N<sub>v</sub> (≤10<sup>3</sup>) and N<sub>e</sub> (≤10<sup>5</sup>), which are the total numbers of vertices and edges, respectively. Hence the vertices are numbered from 1 to N<sub>v</sub>.
Then N<sub>e</sub> lines follow, each describes an edge by giving the indices of the vertices at the two ends, followed by a positive integer weight (≤100) of the edge. It is guaranteed that the given graph is connected.

Finally the number of queries, K, is given as a positive integer no larger than 100, followed by K lines of sequences, each contains a permutationof the N<sub>v</sub> vertices. It is assumed that the first vertex is the source for each sequence.

All the inputs in a line are separated by a space.
### Output Specification:
For each of the K sequences, print in a line `Yes` if it is a Dijkstra sequence, or `No` if not.
### Sample Input:
```
5 7
1 2 2
1 5 1
2 3 1
2 4 1
2 5 2
3 5 1
3 4 1
4
5 1 3 4 2
5 3 1 2 4
2 3 4 5 1
3 2 1 5 4
```
### Sample Output:
```
Yes
Yes
Yes
No

```
## Chapter 2: Algorithm Specification
### Data Struct
- Heap
```c
typedef struct HeapNode{
  int weight;
  int idx;
}HeapNode ;
typedef struct Heap{
  int size;
  HeapNode* value[MAXN];
}Heap ;
```
- Adjacency List
```c
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
```
- Graph
```c
typedef struct Graph{
  int node_num;
  int edge_num;
  VertexNode* adj_list[MAXN];
}Graph ;
```
### Algorithm
- Heap Insert
```c
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
```
- Heap Pop
```c
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
```
- Dijkstra (without Heap)
```c
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
```
- Dijkstra (with Heap)
```c
boolean is_dijkstra_sequence_heap(Graph* graph, int* seq, int* dist, boolean* visit, 
    Heap* heap){
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
```
## Chapter 3: Testing Results
- Sample Output  
![image](https://github.com/novel2430/MyImage/blob/main/P3-002.png?raw=true)
- PTA  
![image](https://github.com/novel2430/MyImage/blob/main/P3-001.png?raw=true)
## Chapter 4: Analysis and Comments
- m: edge count
- n: node count
### Time
- Without Heap : O(n<sup>2</sup>)
- With Heap : O(mlogn)
### Space
- Without Heap : O(n)
- With Heap : O(n)