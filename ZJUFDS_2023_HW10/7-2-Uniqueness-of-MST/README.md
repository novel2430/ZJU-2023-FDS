# Uniqueness of MST
Given any weighted undirected graph, there exists at least one minimum spanning tree (MST) if the graph is connected. Sometimes the MST may not be unique though. Here you are supposed to calculate the minimum total weight of the MST, and also tell if it is unique or not.
## Input Specification:
Each input file contains one test case. Each case starts with a line containing 2 numbers N (≤ 500), and M, which are the total number of vertices, and the number of edges, respectively. Then M lines follow, each describes an edge by 3 integers:
```
V1 V2 Weight
```
where `V1` and `V2` are the two ends of the edge (the vertices are numbered from 1 to N), and `Weight` is the positive weight on that edge. It is guaranteed that the total weight of the graph will not exceed 2<sup>30</sup>.
## Output Specification:
For each test case, first print in a line the total weight of the minimum spanning tree if there exists one, or else print No MST instead. Then if the MST exists, print in the next line `Yes` if the tree is unique, or `No` otherwise. There there is `no MST`, print the number of connected components instead.
## Sample Input 1:
```
5 7
1 2 6
5 1 1
2 3 4
3 4 3
4 1 7
2 4 2
4 5 5
```
## Sample Output 1:
```
11
Yes
```
## Sample Input 2:
```
4 5
1 2 1
2 3 1
3 4 2
4 1 2
3 1 3
```
## Sample Output 2:
```
4
No
```
## Sample Input 3:
```
5 5
1 2 1
2 3 1
3 4 2
4 1 2
3 1 3
```
## Sample Output 3:
```
No MST
2
```
