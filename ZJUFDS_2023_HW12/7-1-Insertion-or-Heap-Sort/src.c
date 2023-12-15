#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000

typedef enum SortType{
  INSERTION,
  HEAP
}SortType ;

SortType get_sort_type(int* arr, int* orig, int size){
  if(arr[0]<arr[1]) return INSERTION;
  return HEAP;
}
void swap(int* arr, int idx1, int idx2){
  int tmp = arr[idx1];
  arr[idx1] = arr[idx2];
  arr[idx2] = tmp;
}
int max_idx(int* arr, int idx1, int idx2){
  if(arr[idx1]>arr[idx2]) return idx1;
  return idx2;
}
void do_sort(SortType type, int* arr, int size){
  if(type==INSERTION){
    int idx = 0;
    for(int i=0; i<size-1; i++){
      if(arr[i]>arr[i+1]){
        idx = i+1;
        break;
      }
    }
    for(int i=idx; i>0; i--){
      if(arr[i]<arr[i-1]){
        swap(arr, i, i-1);
      }
    }
  }
  else{
    int max = arr[0];
    int heap_size = 0;
    for(int i=0; i<size; i++){
      if(arr[i]>max){
        heap_size = i;
        break;
      }
    }
    heap_size--;
    swap(arr, 0, heap_size);
    for(int start=0, next=start; start*2+1<heap_size; start=next){
      if(2*(start+1) < heap_size){
        next = max_idx(arr, start*2+1, 2*(start+1));
      }
      else{
        next = start*2 + 1;
      }
      if(arr[start]>arr[next]) break;
      swap(arr, start, next);
    }
  }
  for(int i=0; i<size; i++){
    if(i>0) printf(" ");
    printf("%d", arr[i]);
    if(i==size-1) printf("\n");
  }
}

int main(int argc, char *argv[]){
  int size;
  int arr[MAXN];
  int orig[MAXN];
  scanf("%d", &size);
  for(int i=0; i<size; i++){
    scanf("%d", &orig[i]);
  }
  for(int i=0; i<size; i++){
    scanf("%d", &arr[i]);
  }
  switch(get_sort_type(arr, orig, size)){
    case INSERTION:
      printf("Insertion Sort\n");
      do_sort(INSERTION, arr, size);
      break;
    case HEAP:
      printf("Heap Sort\n");
      do_sort(HEAP, arr, size);
      break;
    default:
      break;
  }
  return 0;
}
