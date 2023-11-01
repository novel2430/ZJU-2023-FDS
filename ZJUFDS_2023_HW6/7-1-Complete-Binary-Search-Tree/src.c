#include <stdio.h>
#include <stdlib.h>

// Merge Sort
void merge_sort_help(int* arr, int* tmp, int low_idx, int high_idx){
  if(low_idx>=high_idx) return;
  int mid = (low_idx + high_idx)/2;
  merge_sort_help(arr, tmp, low_idx, mid);
  merge_sort_help(arr, tmp, mid+1, high_idx);
  int start1 = low_idx;
  int end1 = mid;
  int start2 = mid+1;
  int end2 = high_idx;
  int cur_idx = start1;
  while(cur_idx<=high_idx){
    if(arr[start1] < arr[start2] && start1<=end1){
      tmp[cur_idx] = arr[start1++];
    }
    else if(arr[start1] >= arr[start2] && start2<=end2){
      tmp[cur_idx] = arr[start2++]; 
    }
    else if (start1>end1) {
      tmp[cur_idx] = arr[start2++]; 
    }
    else if (start2>end2) {
      tmp[cur_idx] = arr[start1++];
    }
    cur_idx++;
  }
  for(int i=low_idx; i<=high_idx; i++){
    arr[i] = tmp[i];
  }
}
void merge_sort(int* arr, int size){
  int* tmp = (int*)malloc(sizeof(int)*size);
  merge_sort_help(arr, tmp, 0, size-1);
}


int main(int argc, char *argv[]){
  int a[8] = {4, 2, 3, 1, 23, 0, 11, 8};
  merge_sort(a, 8);
  for(int i=0; i<8; i++) printf("%d ", a[i]);
  return EXIT_SUCCESS;
}


