#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10000
#define MAXE (MAXN * 2)
#define INF 0x7FFFFFFF

int head[MAXN + 1];
int to[MAXE + 1];
int cost[MAXE + 1];
int nxt[MAXE + 1];
int ecnt = 0;

void add_edge(int u, int v, int w)
{
    nxt[++ecnt] = head[u];
    head[u] = ecnt;
    to[ecnt] = v;
    cost[ecnt] = w;
}

int N;
int dist[MAXN + 1];
int que[MAXN + 1];

void bfs(int start, int *farthest_node, int *farhest_dist)
{
    int front = 0, rear = 0;

    for(int i=1; i<= M; i++)
    {
        dist[i] = -1;
    }
    dist[start] = 0;
    que[rear++] = start;

    *farthest_node = start;
    *farthest_dist = 0;

    while(front < rear)
    {
        int u = que[front++];
        if(dist[u] > *farthest_dist)
        {
            *farthest_dist = dist[u];
            *farthest_node = u;
        }

        for (int e = head[u]; e; e= nxt[e])
        {
            int v = to[e];
            if (dist[v] == -1)
            {
                dist[v] = dist[u] + cost[e];
                que[rear++] = v;
            }
        }
    }

}


int main(void)
{

    if(scanf("%d", &N) != 1) return 0;

    for (int i=1; i<=N; i++)
    {
        head[i] = 0;
    }

    for (int i=0; i<N; i++)
    {
        int s;
        scanf("%d", &s);
        while (1)
        {
            int e, c;
            scanf("%d", &e);
            if ( e == -1) break;
            scanf("%d", &c);
            add_edge(s, e, c);
            add_edge(e, s, c);
        }
    }


    return 0;
}