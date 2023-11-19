#include <stdio.h>
#include <stdlib.h>

int graph[300][300];

void graph_init(){
  for(int i=0; i<300; i++){
    for(int j=0; j<300; j++)
      graph[i][j] = 0;
  }
}

int is_seq_ok(int* seq, int size, int total_size){
  if(size-1!=total_size || seq[0]!=seq[size-1] ) return 0;
  int node[total_size+1];
  for(int i=0; i<total_size+1; i++) node[i] = 0;
  node[seq[0]] = 1;
  for(int i=1; i<size; i++){
    if(i<size-1){
      if(node[seq[i]]) return 0;
      node[seq[i]] = 1;
    }
    if(graph[seq[i-1]][seq[i]] == 0) {
      return 0;
    }
  }
  return 1;
}

int main(int argc, char *argv[]){
  graph_init();
  int total_size, edge_size;
  scanf("%d %d", &total_size, &edge_size);
  for(int i=0; i<edge_size; i++){
    int n1, n2;
    scanf("%d %d", &n1, &n2);
    graph[n1][n2] = 1;
    graph[n2][n1] = 1;
  }
  int case_count;
  scanf("%d", &case_count);
  for(int i=0; i<case_count; i++){
    int seq_size;
    scanf("%d", &seq_size);
    int seq[seq_size];
    for(int j=0; j<seq_size; j++){
      int num;
      scanf("%d", &num);
      seq[j] = num;
    }
    if(is_seq_ok(seq, seq_size, total_size)) printf("YES\n");
    else printf("NO\n");
  }
}

