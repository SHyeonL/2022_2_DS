#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];


int get_min_vertex(int n)
{
    int v, i;
    for (i = 0; i <n; i++)
        if (!selected[i]) {
            v = i;
            break;
        }
    for (i = 0; i < n; i++)
        if (!selected[i] && (distance[i] < distance[v])) v = i;
    return (v);
}

void prim(GraphType* g, int s)
{
    int i, u, v;

    for (u = 0; u<g->n; u++)
        distance[u] = INF;
    distance[s] = 0;
    for (i = 0; i<g->n; i++) {
        u = get_min_vertex(g->n); // 거리가 최소가 되는 정점 선택
        selected[u] = TRUE; // 선택한 정점의 상태를 TRUE로 변경
        if (distance[u] == INF) return; // 거리 값이 무한대라면 오류 발생으로 간주함
        printf("정점 %d 추가\n", u);
        for (v = 0; v<g->n; v++)
            if (g->weight[u][v] != INF) // 가중치가 무한대가 아니라면
                if (!selected[v] && g->weight[u][v]< distance[v]) // 무한대인 distance값보다 weight가 작다면(엣지가 존재한다면)
                    distance[v] = g->weight[u][v]; // distance 값을 설정해줌
    }
}

int main(void)
{
    GraphType g = { 7,
                    {{ 0, 29, INF, INF, INF, 10, INF },
                     { 29,  0, 16, INF, INF, INF, 15 },
                     { INF, 16, 0, 12, INF, INF, INF },
                     { INF, INF, 12, 0, 22, INF, 18 },
                     { INF, INF, INF, 22, 0, 27, 25 },
                     { 10, INF, INF, INF, 27, 0, INF },
                     { INF, 15, INF, 18, 25, INF, 0 } }
    };
    prim(&g, 0);
    return 0;
}