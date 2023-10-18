# 7-1 Queue Using Two Stacks
A queue (FIFO structure) can be implemented by two stacks (LIFO structure) in the following way:

1. Start from two empty stacks s<sub>1</sub> and s<sub>2</sub>

2. When element `e` is enqueued, it is actually pushed onto s<sub>1</sub>

3. When we are supposed to dequeue, s<sub>2</sub> is checked first. If s<sub>2</sub> is empty, everything in s<sub>1</sub> will be transferred to s<sub>2</sub> by popping from s<sub>1</sub> and immediately pushing onto s<sub>2</sub>. Then we just pop from s<sub>2</sub> -- the top element of s<sub>2</sub> must be the first one to enter s<sub>1</sub> thus is the first element that was enqueued.

Assume that each operation of push or pop takes 1 unit of time. You job is to tell the time taken for each dequeue.
## Input Specification:
Each input file contains one test case. For each case, the first line gives a positive integer `N` (≤10<sup>3</sup>), which are the number of operations. Then `N` lines follow, each gives an operation in the format
```
Operation Element
```
where `Operation` being `I` represents enqueue and `O` represents dequeue. For each `I`, `Element` is a positive integer that is no more than 10<sup>6</sup>. No `Element` is given for `O` operations.

It is guaranteed that there is at least one `O` operation.
## Output Specification:
For each dequeue operation, print in a line the dequeued element and the unites of time taken to do this dequeue. The numbers in a line must be separated by 1 space, and there must be no extra space at the beginning or the end of the line.

In case that the queue is empty when dequeue is called, output in a line `ERROR` instead.
## Sample Input:
```
10
I 20
I 32
O
I 11
O
O
O
I 100
I 66
O
```
## Sample Output:
```
20 5
32 1
11 3
ERROR
100 5
```
