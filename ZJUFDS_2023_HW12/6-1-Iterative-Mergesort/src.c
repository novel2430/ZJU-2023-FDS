#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass( ElementType list[], ElementType sorted[], int N, int length );

void output( ElementType list[], int N )
{
    int i;
    for (i=0; i<N; i++) printf("%d ", list[i]);
    printf("\n");
}

void  merge_sort( ElementType list[],  int N )
{
    ElementType extra[MAXN];  /* the extra space required */
    int  length = 1;  /* current length of sublist being merged */
    while( length < N ) { 
        merge_pass( list, extra, N, length ); /* merge list into extra */
        output( extra, N );
        length *= 2;
        merge_pass( extra, list, N, length ); /* merge extra back to list */
        output( list, N );
        length *= 2;
    }
} 


int main()
{
    int N, i;
    ElementType A[MAXN];

    scanf("%d", &N);
    for (i=0; i<N; i++) scanf("%d", &A[i]);
    merge_sort(A, N);
    output(A, N);

    return 0;
}

/* Your function will be put here */
int min(int x, int y) {
  return x < y ? x : y;
}
void merge_pass( ElementType list[], ElementType sorted[], int N, int length ){
  for(int start=0; start<N; start+=length*2){
    int cur_idx = start;
    int start1 = start;
    int end1 = min(start+length, N); 
    int start2 = end1;
    int end2 = min(start+length*2, N);
    while(start1<end1 && start2<end2){
      if(list[start1]>list[start2]){
        sorted[cur_idx++] = list[start2++];
      } 
      else{
        sorted[cur_idx++] = list[start1++];
      }
    }
    while(start1<end1){
      sorted[cur_idx++] = list[start1++];
    }
    while(start2<end2){
      sorted[cur_idx++] = list[start2++];
    }
  }
}
