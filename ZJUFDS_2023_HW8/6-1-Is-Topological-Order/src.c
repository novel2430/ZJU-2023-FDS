#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;
#define MaxVertexNum 10  /* maximum number of vertices */
typedef int Vertex;      /* vertices are numbered from 1 to MaxVertexNum */

typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode{
    Vertex AdjV;
    PtrToAdjVNode Next;
};

typedef struct Vnode{
    PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode;
struct GNode{  
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;

LGraph ReadG(); /* details omitted */

bool IsTopSeq( LGraph Graph, Vertex Seq[] );

int main()
{
    int i, j, N;
    Vertex Seq[MaxVertexNum];
    LGraph G = ReadG();
    scanf("%d", &N);
    for (i=0; i<N; i++) {
        for (j=0; j<G->Nv; j++)
            scanf("%d", &Seq[j]);
        if ( IsTopSeq(G, Seq)==true ) printf("yes\n");
        else printf("no\n");
    }

    return 0;
}

/* Your function will be put here */

bool IsTopSeq( LGraph Graph, Vertex Seq[] ){
    int in_degree[1000];
    PtrToAdjVNode t_node;
    for(int i=0;i<=Graph->Nv;i++)
        in_degree[i]=0;
    for(int i=0;i<Graph->Nv;i++){
        t_node=Graph->G[i].FirstEdge;
        while (t_node){
            in_degree[t_node->AdjV] = in_degree[t_node->AdjV] + 1;
            t_node=t_node->Next;
        }
    } 
    for(int i=0;i<Graph->Nv;i++){
        if(in_degree[Seq[i]-1]!=0)
            return false;
        else{
            t_node=Graph->G[Seq[i]-1].FirstEdge;
            while(t_node){
                in_degree[t_node->AdjV] = in_degree[t_node->AdjV] - 1;
                t_node=t_node->Next;
            }
        }
    }
    return true;
}
