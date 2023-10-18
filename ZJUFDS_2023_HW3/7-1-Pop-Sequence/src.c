#include <stdio.h>
#include <stdlib.h>

// Basic Struct
typedef struct stack_node{
  int values;
  struct stack_node* next;
  struct stack_node* before;
}stack_node;
typedef struct my_stack {
  stack_node* head;
  stack_node* top;
}my_stack ;

// Node op
stack_node* node_init(int num){
  stack_node* node = (stack_node*)malloc(sizeof(stack_node));
  node->values = num;
  node->next = NULL;
  node->before = NULL;
  return node;
}
void node_delete(stack_node* node){
  if(node==NULL) return;
  free(node);
  node = NULL;
}

// Stack op
my_stack* stack_init(){
  my_stack* res = (my_stack*)malloc(sizeof(my_stack));
  res->head = node_init(0);
  res->top = res->head;
  return res;
}
void stack_delete(my_stack* stack){
  if(stack==NULL) return;
  stack_node* cur = stack->head;
  while(cur != NULL){
    stack_node* next_node = cur->next;
    node_delete(cur);
    cur = next_node;
  }
  free(stack);
  stack = NULL;
}
void stack_push(my_stack* stack, int num){
  stack->head->values++;
  stack_node* node = node_init(num);
  stack->top->next = node;
  node->before = stack->top;
  stack->top = node;
}
int stack_pop(my_stack* stack){
  stack->head->values--;
  int res = stack->top->values;
  stack_node* old_top = stack->top;
  stack_node* new_top = stack->top->before;
  node_delete(old_top);
  stack->top = new_top;
  stack->top->next = NULL;
  return res;
}
int stack_is_empty(my_stack* stack){
  if(stack==NULL || stack->head!=stack->top){
    return 0;
  }
  return 1;
}

int main(){
  int max_length, max_num, seq_count;
  scanf("%d %d %d", &max_length, &max_num, &seq_count);
  // build test
  int test[seq_count][max_num];
  for(int i=0; i<seq_count; i++){
    for(int j=0; j<max_num; j++){
      int cur_num;
      scanf("%d", &cur_num);
      test[i][j] = cur_num;
    }
  }
  // do test
  for(int i=0; i<seq_count; i++){
    my_stack* stack = stack_init();
    int idx = 1;
    for(int j=0; j<max_num; j++){
      int now_num = test[i][j];
      for(;idx<=now_num && stack->head->values<max_length; idx++){
        stack_push(stack, idx);
      }
      if(stack->top!=stack->head && stack->top->values==now_num){
        stack_pop(stack);
      }
      else break;
    }
    if(i>0) printf("\n");
    if(stack_is_empty(stack)) printf("YES");
    else printf("NO");
    stack_delete(stack);
  }
}

