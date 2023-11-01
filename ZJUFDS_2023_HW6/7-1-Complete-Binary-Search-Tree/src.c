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

// Build Tree Layer print
void get_tree_layer_help(int* inorder, int n, int size, int* cur_idx, int* layer){
  if(n>=size) return;
  get_tree_layer_help(inorder, 2*n+1, size, cur_idx, layer);
  layer[n] = inorder[(*cur_idx)++];
  get_tree_layer_help(inorder, 2*(n+1), size, cur_idx, layer);
}
int* get_tree_layer(int* inorder, int size){
  int* tmp = (int*)malloc(sizeof(int)*size);
  int base_idx = 0;
  get_tree_layer_help(inorder, 0, size, &base_idx, tmp);
  return tmp;
}

int main(int argc, char *argv[]){
  int count;
  scanf("%d", &count);
  int nums[count];
  for(int i=0; i<count; i++) scanf("%d", &nums[i]);
  merge_sort(nums, count);
  int* res = get_tree_layer(nums, count);
  for(int i=0; i<count; i++){
    if(i>0) printf(" ");
    printf("%d", res[i]);
  }
  return 0;
}
