#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000
#define MAX_EDGES 1000000

int townTime[MAX_N+1];
int head[MAX_N+1], to[MAX_EDGES], nxt[MAX_EDGES];
int visited[MAX_N+1];
int queue[MAX_N+1];
int edge_cnt;


int main()
{
    int T;
    if(scanf("%d", &T) != 1) return 0;
    while(T--)
    {
        int N, K;
        scanf("%d %d", &N, &K);

        for(int i=1; i<=N; ++i)
        {
            scanf("%d", &townTime[i]);
            visited[i] = 0;
            head[i] = -1;
        }

        edge_cnt = 0;
        for(int i=0; i<K; ++i)
        {
            int x, y;
            scanf("%d %d", &x, &y);

            to[edge_cnt] = x;
            nxt[edge_cnt] = head[y];
            head[y] = edge_cnt++;
        }

        int w;
        scanf("%d", &w);

        int qh=0,qt=0;
        queue[qt++] = w;
        visited[w] = 1;
        int totalTime = 0;

        while(qh<qt)
        {
            int u = queue[qh++];
            int maxTime = 0;
            for(int e = head[u]; e!=-1; e=nxt[e])
            {
                int v = to[e];
                if(townTime[v]>maxTime)
                {
                    maxTime = townTime[v];
                }
                if(!visited[v])
                {
                    visited[v] = 1;
                    queue[qt++] = v;
                }
            }
            totalTime += maxTime;
        }
        printf("%d\n", totalTime);
    } 
    return 0;
}


