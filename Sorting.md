# 排序算法 Sorting
## 选择排序 Selection Sort
### 简述
选择排序是一种简单直观的排序算法。它的工作原理如下。首先在未排序序列中找到最小（大）元素，存放到排序序列的起始位置，然后，再从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾。以此类推，直到所有元素均排序完毕。  
![image](https://upload.wikimedia.org/wikipedia/commons/9/94/Selection-Sort-Animation.gif)
### 复杂度
| Average Time | Worst Time | Best Time | Space | Stability |
| --- | --- | --- | --- | --- |
| O(n<sup>2</sup>) | O(n<sup>2</sup>) | O(n<sup>2</sup>) | O(1) | No |
### 代码
```c
void selection_sort(int* arr, int size){
    for(int i=0; i<size-1; i++){
        int min_idx = i; // 纪录最小值的idx
        for(int ii=i+1; ii<size; ii++){
            if(a[min_idx] > a[ii]){
                min_idx = ii; // 找到未排序序列之最小
            }
        }
        if(min_idx != i){
            swap(arr, i, min_idx); // 交换
        }
    }
}
```
## 冒泡排序 Bubble Sort
### 简述
冒泡排序又称为泡式排序，是一种简单的排序算法。它重复地走访过要排序的数列，一次比较两个元素，如果它们的顺序错误就把它们交换过来。走访数列的工作是重复地进行直到没有再需要交换，也就是说该数列已经排序完成。这个算法的名字由来是因为越小的元素会经由交换慢慢“浮”到数列的顶端。
### 复杂度
| Average Time | Worst Time | Best Time | Space | Stability |
| --- | --- | --- | --- | --- |
| O(n<sup>2</sup>) | O(n<sup>2</sup>) | O(n) | O(1) | Yes |
### 代码
```c
void bubble_sort(int* arr, int size){
    for(int i=0; i<size-1; i++){
        for(int ii=0; ii<size-1-i; ii++){
            if(arr[ii] > arr[ii+1]){
                swap(arr, ii, ii+1);
            }
        }
    }
}
```
## 插入排序 Insertion Sort
### 简述
插入排序是一种简单直观的排序算法。它的工作原理是通过构建有序序列，对于未排序数据，在已排序序列中从后向前扫描，找到相应位置并插入。插入排序在实现上，通常采用in-place排序（即只需用到O(1)的额外空间的排序），因而在从后向前扫描过程中，需要反复把已排序元素逐步向后挪位，为最新元素提供插入空间。  
![image](https://upload.wikimedia.org/wikipedia/commons/0/0f/Insertion-sort-example-300px.gif)
### 复杂度
| Average Time | Worst Time | Best Time | Space | Stability |
| --- | --- | --- | --- | --- |
| O(n<sup>2</sup>) | O(n<sup>2</sup>) | O(n) | O(1) | Yes |
### 代码
```c
void insertion_sort(int* arr, int size){
    for(int i=0; i<size-1; i++){
        for(int ii=i+1; ii>0; ii--){
            if(arr[ii-1] > arr[ii]){
                swap(arr, ii-1, ii);
            }
        }
    }
}
```
## 希尔排序 Shell Sort
### 简述
希尔排序，也称**递减增量排序算法**，是插入排序的一种更高效的改进版本。希尔排序是非稳定排序算法。  
希尔排序是基于插入排序的以下两点性质而提出改进方法的:  
- 插入排序在对几乎已经排好序的数据操作时，效率高，即可以达到线性排序的效率
- 但插入排序一般来说是低效的，因为插入排序每次只能将数据移动一位

希尔排序通过将比较的全部元素**分为几个区域**来提升插入排序的性能。这样可以让一个元素可以一次性地朝最终位置前进一大步。然后算法再取越来越小的步长进行排序，算法的最后一步就是普通的插入排序，但是到了这步，需排序的数据几乎是已排好的了（此时插入排序较快）。  
例如，假设有这样一组数`13 14 94 33 82 25 59 94 65 23 45 27 73 25 39 10`，如果我们以步长为5开始进行排序，我们可以通过将这列表放在有5列的表中来更好地描述算法，这样他们就应该看起来是这样:  
```
13 14 94 33 82
25 59 94 65 23
45 27 73 25 39
10
```
然后我们对每列进行排序:
```
10 14 73 25 23
13 27 94 33 39
25 59 94 65 82
45
```
将上述四行数字，依序接在一起时我们得到`10 14 73 25 23 13 27 94 33 39 25 59 94 65 82 45`这时10已经移至正确位置了，然后再以3为步长进行排序:
```
10 14 73
25 23 13
27 94 33
39 25 59
94 65 82
45
```
排序之后变为:
```
10 14 13
25 23 33
27 25 59
39 65 73
45 94 82
94
```
最后以1步长进行排序（此时就是简单的插入排序了）。  
步长的选择是希尔排序的重要部分。只要最终步长为1任何步长序列都可以工作。而对于不同步长的选择，希尔算法会有**不同的平均与最坏时间复杂度**。
### 复杂度
**会根据步长选择有所不同**
| Average Time | Worst Time | Best Time | Space | Stability |
| --- | --- | --- | --- | --- |
| O(nlogn) | O(nlog<sup>2</sup>n) | O(n) | O(1) | No |
### 代码
```c
void shell_sort(int* arr, int size){
    for(int gap=size>>1; gap>0; gap>>=1){
        for(int i=gap; i<size; i++){
            for(int ii=i; ii>=gap; ii-=gap){
                if(arr[ii]>arr[ii-gap]){
                    swap(arr, ii, ii-gap);
                }
            }
        }
    }
}
```
## 归并排序 Merge Sort
### 简述
归并排序，是建立在**归并操作**上的一种有效的排序算法。1945年由约翰·冯·诺伊曼首次提出。该算法是采用**分治法(Divide and Conquer)**的一个非常典型的应用，且各层分治递归可以同时进行。  
采用分治法:
- 分割：递归地把当前序列平均分割成两半。
- 集成：在保持元素顺序的同时将上一步得到的子序列集成到一起（归并）。
![image](https://upload.wikimedia.org/wikipedia/commons/c/cc/Merge-sort-example-300px.gif)
### 复杂度
| Average Time | Worst Time | Best Time | Space | Stability |
| --- | --- | --- | --- | --- |
| O(nlogn) | O(nlogn) | O(n) | O(n) | Yes |
### 代码
#### 递归法 Top-down
```c
void merge_sort_conquer(int* arr, int low, int mid, int high, int* tmp){
    int start1 = low;
    int end1 = mid;
    int start2 = mid+1;
    int end2 = high;
    int cur_idx = 0;
    while(start1<=end1 && start2<=end2){
        if(arr[start1] < arr[start2]) tmp[cur_idx++] = arr[start1++];
        else tmp[cur_idx++] = arr[start2++];
    }
    while(start1>end1 && start2<=end2){
        tmp[cur_idx++] = arr[start2++];
    }
    while(start2>end2 && start1<=end1){
        tmp[cur_idx++] = arr[start1++];
    }
    for(int i=0; i<high-low+1; i++)
        arr[low+i] = tmp[i];
}
void merge_sort_divide(int* arr, int low, int high, int* tmp){
    if(low < high){
        int mid = (low + high)/2;
        merge_sort_divide(arr, low, mid, tmp);
        merge_sort_divide(arr, mid+1, high, tmp);
        merge_sort_conquer(arr, low, mid, high, tmp);
    }
}
void merge_sort(int* arr, int size){
    int* tmp = (int*)malloc(sizeof(int)*size);
    merge_sort_divide(arr, 0, size-1, tmp);
    free(tmp);
    tmp = NULL;
}
```
#### 迭代法 Bottom-up
```c
int min(int a, int b){
    if(a < b) return a;
    return b;
}
void merge_sort(int* arr, int size){
    int* a = arr;
    int* tmp = (int*)malloc(sizeof(int)*size);
    for(int gap=1; gap<size; gap+=gap){
        for(int i=0; i<size; i+=gap*2){
            int start1 = i;
            int end1 = min(i+gap-1, size-1);
            int start2 = end1+1;
            int end2 = min(i+gap*2-1, size-1);
            int cur_idx = start1;
            while(start1<=end1 && start2<=end2){
                if(a[start1] < a[start2]) tmp[cur_idx++] = a[start1++];
                else tmp[cur_idx++] = a[start2++];
            }
            while(start1>end1 && start2<=end2){
                tmp[cur_idx++] = a[start2++];
            }
            while(start2>end2 && start1<=end1){
                tmp[cur_idx++] = a[start1++];
            }
        }
        int* temp = a;
        a = tmp;
        tmp = temp;
    }
    for(int i=0; i<size; i++)
        arr[i] = a[i];
}
```
## 堆排序 Heap Sort
### 简述
堆排序是指利用堆这种数据结构所设计的一种排序算法。堆是一个近似完全二叉树的结构，并同时满足堆的性质:**子节点的值总是小于（或者大于）它的父节点**。  
若以升序排序说明，把数组转换成最大堆，这是一种满足最大堆性质的二叉树。重复从最大堆取出数值最大的结点（把根结点和最后一个结点交换，把交换后的最后一个结点移出堆），并让残余的堆维持最大堆性质。  
#### 堆节点的访问
- 父节点`i`之左子节点位置为`2i+1`  
- 父节点`i`之右子节点位置为`2i+2`  
- 子节点`i`之父节点位置为`(i-1)/2`
### 复杂度
| Average Time | Worst Time | Best Time | Space | Stability |
| --- | --- | --- | --- | --- |
| O(nlogn) | O(nlogn) | O(nlogn) | O(1) | No |
### 代码
```c
int max_idx(int* arr, int idx1, int idx2){
    if(arr[idx1] > arr[idx2]) return idx1;
    return idx2;
}
void percolate_down(int* arr, int size, int idx){
    int next = idx;
    for(int i=idx; i*2+1<size; i=next){
        if(i*2+2 < size){
            next = max_idx(arr, i*2+1, i*2+2);
        }
        else{
            next = i*2+1;
        }
        if(arr[i] > arr[next]) break;
        swap(arr, i, next);
    }
}
void init_heap(int* arr, int size){
    int last_parent_idx = size/2 - 1;
    for(int i=last_parent_idx; i>=0; i--){
        percolate_down(arr, size, i);
    }
}
void heap_sort(int* arr, int size){
    init_heap(arr, size);
    for(int i=size-1; i>0; i--){
        swap(arr, 0, i);
        size--;
        percolate_down(arr, size, 0);
    }
}
```
## 快速排序 Quick Sort
### 简述
快速排序，又称**分区交换排序(partition-exchange sort)**，是一种排序算法，最早由东尼·霍尔提出。在平均状况下，排序n个项目要O(nlogn)次比较。在最坏状况下则需要O(n<sup>2</sup>)次比较，但这种状况并不常见。事实上，快速排序O(nlogn)通常明显比其他算法更快，因为它的内部循环(inner loop)可以在大部分的架构上很有效率地达成。  
快速排序使用**分治法**策略来把一个序列分为较小和较大的2个子序列，然后递归地排序两个子序列。  
步骤为:
1. 挑选基准值: 从数列中挑出一个元素，称为**基准**(pivot)
2. 分割: 重新排序数列，所有比基准值小的元素摆放在基准前面，所有比基准值大的元素摆在基准后面（与基准值相等的数可以到任何一边）。在这个分割结束之后，对基准值的排序就已经完成
3. 递归排序子序列: 递归地将小于基准值元素的子序列和大于基准值元素的子序列排序

递归到最底部的判断条件是数列的大小是零或一，此时该数列显然已经有序。  
选取基准值有数种具体方法，此**选取方法对排序的时间性能有决定性影响**。  
#### Pivot 的选择
理想状况，我们希望每次pivot的选择都是当前序列的中位数，但在代码实现层面上是不现实的。常见的有以下两种选择方法。
- 随机数  
每次在选择pivot时，都自当前序列中随机选择一数，在代码实现上，需要有个伪随机数产生器，所以需要考虑实现及使用随机数生成算法的耗时，其开销可能很大。
- Median-of-3 (Mo3)  
在一般的的快速排序中，选择的是第一个元素作为pivot，这会出现某些分区严重不均的极端情况，比如划分为了1和n-1两个序列，从而导致出现最坏的情况。Mo3分区法与一般的快速排序方法不同，它并不是选择待排数组的第一个数作为中轴，而是选用待排数组**最左边、最右边和最中间的三个元素的中间值**作为pivot。
### 复杂度
| Average Time | Worst Time | Best Time | Space | Stability |
| --- | --- | --- | --- | --- |
| O(nlogn) | O(n<sup>2</sup>) | O(nlogn) | O(logn) | No |
### 代码
```c
int mid_of_3_idx(int* arr, int idx1, int idx2, int idx3){
    int tmp1 = arr[idx1];
    int tmp2 = arr[idx2];
    int tmp3 = arr[idx3];
    if(tmp1<=tmp2 && tmp2<=tmp3) return idx2;
    if(tmp3<=tmp2 && tmp2<=tmp1) return idx2;
    if(tmp1<=tmp3 && tmp3<=tmp2) return idx3;
    if(tmp2<=tmp3 && tmp3<=tmp1) return idx3;
    if(tmp2<=tmp1 && tmp1<=tmp3) return idx1;
    if(tmp3<=tmp1 && tmp1<=tmp2) return idx1;
    return idx2;
}
void partition_sort(int* arr, int low, int high){
    if(low >= high) return;
    int pivot_idx = mid_of_3_idx(arr, low, (high+low)/2, high);
    int pivot = arr[pivot_idx];
    swap(arr, pivot_idx, high);
    int i = low;
    int j = high;
    while(i < j){
        while(i<j && arr[i]<=pivot){
            i++;
        } 
        arr[j] = arr[i];
        while(j>i && arr[j]>=pivot){
            j--;
        }
        arr[i] = arr[j];
    }
    arr[i] = pivot;
    partition_sort(arr, low, i-1);
    partition_sort(arr, i+1, high);
}
void quick_sort(int* arr, int size){
    partition_sort(arr, 0, size-1);
}
```
## 计数排序 Counting Sort
### 简述
计数排序是一种稳定的**线性时间非比较排序算法**。该算法于1954年由 Harold H. Seward 提出。计数排序使用一个额外的`数组C` ，其中第i个元素是待排序`数组A`中值等于i的元素的个数。然后根据数组C将A中的元素排到正确的位置。
#### 算法流程
1. 找出待排`数组A`最小值`min`以及`max`
2. 构建`数组C(count)`，其大小为`max-min+1`
3. 遍历`数组A`，将其值减去min所得，表示为对应`数组C`之下标，并将其`数组C`下标对应值加一。`count[ A[i]-min ]++`
4. 遍历`数组C`，对于`i>0`的赋值`count[i] = count[i] + count[i-1]`
5. 倒叙遍历`数组A`，建立排序`数组B`，满足`B[ count[(A[i]-min)] - 1 ] = A[i]; count[(A[i]-min)]--`
6. 输出`数组B`
### 复杂度
| Average Time | Worst Time | Best Time | Space | Stability |
| --- | --- | --- | --- | --- |
| O(n+k) | O(n+k) | O(n+k) | O(n+k) | Yes |
### 代码
```c
void counting_sort(int* arr, int size){
  int min = arr[0];
  int max = arr[0];
  for(int i=0; i<size; i++){
    if(arr[i] < min) min = arr[i];
    if(arr[i] > max) max = arr[i];
  }
  int count_arr_size = max-min+1;
  int count[count_arr_size];
  for(int i=0; i<count_arr_size; i++) count[i] = 0;
  for(int i=0; i<size; i++){
    count[arr[i]-min]++;
  }
  for(int i=0; i<count_arr_size; i++){
    if(i>0)
      count[i] = count[i-1] + count[i];
  }
  int res[size];
  for(int i=size-1; i>=0; i--){
    res[count[(arr[i]-min)]-1] = arr[i];
    count[(arr[i]-min)]--;
  }
  for(int i=0; i<size; i++){
    arr[i] = res[i];
  }
}
```
## 桶排序 Bucket Sort
### 简述
桶排序或所谓的**箱排序**，是一个排序算法，工作的原理是将数组分到有限数量的桶里。每个桶再个别排序(有可能再使用别的排序算法或是以递归方式继续使用桶排序进行排序)。桶排序是**鸽巢排序**的一种归纳结果。当要被排序的数组内的数值是均匀分配的时候，桶排序使用线性时间O(n)。  
元素分配进桶里  
![image](https://upload.wikimedia.org/wikipedia/commons/6/61/Bucket_sort_1.svg)  
对桶中元素排序  
![image](https://upload.wikimedia.org/wikipedia/commons/e/e3/Bucket_sort_2.svg)
#### 算法流程
1. 设置一个定量数目，表示为一个桶中至多的元素个数，通常为`(Max-Min)/n + 1`
2. 根据上一点决定的元素个数，决定需要多少桶子，`(Max-Min)/(bucketSize) + 1`
3. 寻访序列，并且把项目一个一个放到对应的桶子去
4. 对每个不是空的桶子进行排序，或将非空桶字递归到1.
5. 从不是空的桶子里把项目再放回原来的序列中
### 复杂度
| Average Time | Worst Time | Best Time | Space | Stability |
| --- | --- | --- | --- | --- |
| O(n+k) | O(n<sup>2</sup>) | O(n) | O(n*k) | Yes |
### 代码
```c
List* bucket_sort_help(List* bucket){
  if(bucket == NULL) return NULL;
  if(bucket->head->value <= 1) return bucket;
  int size = bucket->head->value;
  int min = bucket->head->next->value;
  int max = bucket->head->next->value;
  for(ListNode* cur=bucket->head->next; cur!=NULL; cur=cur->next){
    if(cur->value < min) min = cur->value;
    if(cur->value > max) max = cur->value;
  }
  int bucket_size = (max - min)/size + 1;
  int bucket_count = (max - min)/bucket_size + 1;
  if(bucket_count == 1) return bucket;
  List* buckets[bucket_count];
  for(int i=0; i<bucket_count; i++){
    buckets[i] = init_list();
  }
  for(ListNode* cur=bucket->head->next; cur!=NULL; cur=cur->next){
    int idx = (cur->value - min)/bucket_size;
    add_list(buckets[idx], cur->value);
  }
  empty_list(bucket);
  for(int i=0; i<bucket_count; i++){
    buckets[i] = bucket_sort_help(buckets[i]);
  }
  for(int i=0; i<bucket_count; i++){
    List* cur_bucket = buckets[i];
    for(ListNode* cur = cur_bucket->head->next; cur!=NULL; cur=cur->next){
      add_list(bucket, cur->value);
    }
    delete_list(cur_bucket);
  }
  return bucket;
}
void bucket_sort(int* arr, int size){
  List* all_in_on = init_list();
  for(int i=0; i<size; i++){
    add_list(all_in_on, arr[i]);
  }
  all_in_on = bucket_sort_help(all_in_on);
  int count = 0;
  for(ListNode* cur=all_in_on->head->next; cur!=NULL; cur=cur->next){
    arr[count++] = cur->value;
  }
}
```
