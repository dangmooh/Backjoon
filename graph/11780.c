#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100
#define INF 1000000000

int n, m;
int dist[MAXN+1][MAXN+1];
int trace[MAXN+1][MAXN+1];

int getPath(int i, int j, int *path)
{
    if(trace[i][j] == -1) return 0;
    int sz =0;
    int cur = j;
    while(cur != i)
    {
        path[sz++] = cur;
        cur = trace[i][cur];
    }
    path[sz++] = i;
    
    return sz;
}

int main(void)
{
    scanf("%d %d", &n, &m);

    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=n; j++)
        {
            dist[i][j] = (i == j ? 0: INF);
            trace[i][j] = -1;
        }
    }

    for (int e=0; e<m; e++)
    {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        if(c<dist[u][v])
        {
            dist[u][v] = c;
            trace[u][v] = u;
        }
    }

    for (int k=1; k<=n; k++)
    {
        for (int i=1; i<=n; i++)
        {
            if(dist[i][k] == INF) continue;
            for (int j=1; j<=n; j++)
            {
                if(dist[k][j] == INF) continue;
                int nd = dist[i][k] + dist[k][j];
                if (nd < dist[i][j])
                {
                    dist[i][j] = nd;
                    trace[i][j] = trace[k][j];
                }
            }
        }
    }

    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=n; j++)
        {
            if (dist[i][j] == INF) printf("0 ");
            else printf("%d ", dist[i][j]);
        }
        printf("\n");
    }

    int path[MAXN+1];
    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=n; j++)
        {
            if (i == j || dist[i][j] == INF)
            {
                printf("0\n");
            }
            else
            {
                int sz = getPath(i, j, path);
                printf("%d", sz);

                for(int t=sz; t>= 0; t--)
                {
                    printf("%d ", path[t]);
                }
                printf("\n");
            }
        }
    }



    return 0;
}