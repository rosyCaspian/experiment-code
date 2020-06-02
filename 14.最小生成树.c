#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 10
#define INFINITY 32768

typedef struct AdjMatrix
{
    char vertex[MAX_VERTEX_NUM];
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum, arcnum;
} AdjMatrix;

typedef struct Edge
{
    int a, b;
    int weight;
} Edge;

AdjMatrix *createGraph()
{
    AdjMatrix *pGraph = (AdjMatrix *)malloc(sizeof(AdjMatrix));
    pGraph->vexnum = 0;
    pGraph->arcnum = 0;
    for (int i = 0; i < MAX_VERTEX_NUM; i++)
        for (int j = 0; j < MAX_VERTEX_NUM; j++)
            pGraph->arcs[i][j] = INFINITY;

    return pGraph;
}

/*
int locateVertex(AdjMatrix *pGraph, char v)
{
    for (int i = 0; i < pGraph->vexnum; i++)
        if (pGraph->vertex[i] == v)
            return i;

    return -1;
}
*/

void initGraph(AdjMatrix *pGraph)
{
    pGraph->vexnum = 9;
    pGraph->arcnum = 15;

    pGraph->vertex[0] = 'A';
    pGraph->vertex[1] = 'B';
    pGraph->vertex[2] = 'C';
    pGraph->vertex[3] = 'D';
    pGraph->vertex[4] = 'E';
    pGraph->vertex[5] = 'F';
    pGraph->vertex[6] = 'G';
    pGraph->vertex[7] = 'H';
    pGraph->vertex[8] = 'I';

    pGraph->arcs[0][1] = 10;
    pGraph->arcs[0][5] = 11;
    pGraph->arcs[1][2] = 18;
    pGraph->arcs[1][6] = 16;
    pGraph->arcs[1][8] = 12;
    pGraph->arcs[2][3] = 22;
    pGraph->arcs[2][8] = 8;
    pGraph->arcs[3][8] = 21;
    pGraph->arcs[3][6] = 24;
    pGraph->arcs[3][7] = 16;
    pGraph->arcs[3][4] = 20;
    pGraph->arcs[4][7] = 7;
    pGraph->arcs[4][5] = 26;
    pGraph->arcs[5][6] = 17;
    pGraph->arcs[6][7] = 19;
}

void MiniSpanTree(AdjMatrix *pGraph)
{
    int i, j, w = 0, n = 0;
    int *set = (int *)malloc(sizeof(int) * pGraph->vexnum);
    Edge *edge = (Edge *)malloc(sizeof(Edge) * pGraph->arcnum);
    int *weights = (int *)malloc(sizeof(int) * pGraph->vexnum + 1);

    // 初始化顶点集合
    for (i = 0; i < pGraph->vexnum; i++)
        set[i] = i;

    // 初始化边
    for (i = 0; i < pGraph->vexnum; i++)
    {
        for (j = 0; j < pGraph->vexnum; j++)
        {
            if (pGraph->arcs[i][j] != INFINITY)
            {
                edge[n].a = i;
                edge[n].b = j;
                edge[n].weight = pGraph->arcs[i][j];
                n++;
            }
        }
    }

    weights[pGraph->vexnum] = 0;

    for (i = 0; i < pGraph->arcnum - 1; i++)
        for (j = i + 1; j < pGraph->arcnum; j++)
        {
            if (edge[i].weight > edge[j].weight)
            {
                Edge temp = {edge[i].a,
                             edge[i].b,
                             edge[i].weight};
                edge[i].a = edge[j].a;
                edge[i].b = edge[j].b;
                edge[i].weight = edge[j].weight;
                edge[j].a = temp.a;
                edge[j].b = temp.b;
                edge[j].weight = temp.weight;
            }
        }

    printf("最小生成树边的集合: { ");
    for (i = 0; i < pGraph->arcnum; i++)
    {
        if (set[edge[i].a] != set[edge[i].b])
        {
            for (n = 0; n < pGraph->vexnum; n++)
                if (set[n] == set[edge[i].b])
                    set[n] = set[edge[i].a];
            printf("(%c, %c) ", pGraph->vertex[edge[i].a], pGraph->vertex[edge[i].b]);
            weights[w++] = edge[i].weight;
            weights[pGraph->vexnum] += edge[i].weight;
        }
    }

    printf("}\n累计权值: ");
    for (i = 0; i < w - 1; i++)
        printf("%d + ", weights[i]);
    printf("%d = %d", weights[w - 1], weights[pGraph->vexnum]);

    free(set);
    free(edge);
    free(weights);
}

int main()
{
    AdjMatrix *Graph = createGraph();
    initGraph(Graph);
    MiniSpanTree(Graph);

    free(Graph);
    return 0;
}