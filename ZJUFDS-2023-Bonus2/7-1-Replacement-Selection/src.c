#include <stdio.h>
#include <stdlib.h>

#define MAXN 500000

typedef enum Boolean{FALSE, TRUE} Boolean ;
typedef int DataValue ;
typedef struct Heap{
  DataValue nodes[MAXN];
  int size;
}Heap;

Heap* heap_init(){
  Heap* res = (Heap*)malloc(sizeof(Heap));
  res->size = 0;
  return res;
};
void heap_delete(Heap* heap){
  if(heap==NULL) return;
  free(heap);
  heap = NULL;
}
void swap(Heap* heap, int idx1, int idx2){
  if(heap==NULL) return;
  DataValue tmp = heap->nodes[idx1];
  heap->nodes[idx1] = heap->nodes[idx2];
  heap->nodes[idx2] = tmp;
}
int min_idx(Heap* heap, int idx1, int idx2){
  if(heap->nodes[idx1] < heap->nodes[idx2]) return idx1;
  return idx2;
}
void heap_insert(Heap* heap, DataValue data){
  if(heap==NULL) return;
  heap->size++;
  heap->nodes[heap->size] = data;
  for(int idx=heap->size; idx>1; idx=idx/2){
    DataValue cur = heap->nodes[idx];
    DataValue parent = heap->nodes[idx/2];
    if(parent>cur) swap(heap, idx, idx/2);
    else break;
  }
}
DataValue heap_pop(Heap* heap){
  DataValue res = heap->nodes[1];
  swap(heap, 1, heap->size);
  for(int idx=1; idx*2<heap->size; ){
    int next_idx = idx;
    if(idx*2+1<heap->size){
      next_idx = min_idx(heap, idx*2, idx*2+1);
    }
    else if(heap->nodes[idx]>heap->nodes[idx*2]){
      next_idx = idx*2;
    }
    if(heap->nodes[idx] > heap->nodes[next_idx])
      swap(heap, idx, next_idx);
    else break;
    idx = next_idx;
  }
  heap->size--;
  return res;
}
Boolean heap_is_empty(Heap* heap){
  if(heap->size==0) return TRUE;
  return FALSE;
}

void replacement_selection(int* arr, int size, int capacity){
  Heap* heap1 = heap_init();
  Heap* heap2 = heap_init();
  for(int i=0; i<size&&i<capacity; i++) heap_insert(heap1, arr[i]);
  int cur_idx = capacity;
  while(!heap_is_empty(heap1) || !heap_is_empty(heap2)){
    int print_num_count = 0;
    int flag = 0;
    while(!heap_is_empty(heap1)){
      int cur_min = heap_pop(heap1);
      flag = 1;
      if(cur_idx < size){
        int cur_num = arr[cur_idx++];
        if(cur_min < cur_num) heap_insert(heap1, cur_num);
        else heap_insert(heap2, cur_num);
      }
      if(print_num_count++ > 0) printf(" ");
      printf("%d", cur_min);
    }
    if(flag) printf("\n");
    print_num_count = 0;
    flag = 0;
    while(!heap_is_empty(heap2)){
      flag = 1;
      int cur_min = heap_pop(heap2);
      if(cur_idx < size){
        int cur_num = arr[cur_idx++];
        if(cur_min < cur_num) heap_insert(heap2, cur_num);
        else heap_insert(heap1, cur_num);
      }
      if(print_num_count++ > 0) printf(" ");
      printf("%d", cur_min);
    }
    if(flag) printf("\n");
  }
  heap_delete(heap1);
  heap_delete(heap2);
}

int main(int argc, char *argv[]){
  int size, capacity;
  scanf("%d %d", &size, &capacity);
  int arr[MAXN];
  for(int i=0; i<size; i++){
    scanf("%d", &arr[i]);
  }
  replacement_selection(arr, size, capacity);
  return 0;
}
