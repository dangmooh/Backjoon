#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#define MAX_N 800
#define MAX_M 200000
#define MAX_PQ (MAX_M*2 + MAX_N)

typedef struct {
    int to, w, next;
} Edge;

Edge edges[2*MAX_M];
int head[MAX_N+1];
int edge_cnt;


void add_edge(int u, int v, int w)
{
    edges[edge_cnt].to = v;
    edges[edge_cnt].w = w;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

typedef struct {
    int v, dist;
} Node;

Node pq[MAX_PQ];
int pq_size;



void pq_push(Node nd)
{
    int child = pq_size++;

    while(child>1 && pq[child/2].dist > nd.dist )
    {
        pq[child] = pq[child/2];
        child /=2;
    }
    pq[child] = nd;
}

Node pq_pop()
{
    Node ret = pq[1];

    Node low = pq[pq_size--];
    int parent = 1, child;

    while((child = parent*2) <= pq_size)
    {
        if(child + 1 <= pq_size && pq[child].dist > pq[child+1].dist)
        {
            child++;
        }
        if(pq[child].dist > low.dist) break;
        pq[parent] = pq[child];
        parent = child;
    }
    pq[parent] = low;

    return ret;
}

int pq_empty()
{
    return pq_size == 0;
}


void dijkstra(int src, int N, int dist[])
{
    const int INF = INT_MAX;
    for(int i=1; i<=N; i++) dist[i] = INF;
    dist[src] = 0;
    pq_size = 0;
    pq_push((Node){src, 0});

    while(!pq_empty())
    {
        
        Node cur = pq_pop();
        int u = cur.v, d = cur.dist;
        if(d>dist[u]) continue;
        for(int e=head[u]; e!=-1; e = edges[e].next)
        {
            int v = edges[e].to;
            int nd = d + edges[e].w;
            if(nd < dist[v]) {
                dist[v] = nd;
                pq_push((Node){v, nd});
            }
        }
    }
}


int main()
{
    int N, E;
    scanf("%d %d", &N, &E);

    for(int i=1; i<=N; i++) head[i] = -1;
    edge_cnt = 0;

    for(int i=0; i<E; i++)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        add_edge(a, b, c);
        add_edge(b, a, c);
    }

    int v1, v2;
    scanf("%d %d", &v1, &v2);

    int dist1[MAX_N+1];
    int distv1[MAX_N+1];
    int distv2[MAX_N+1];

        // 세 번의 다익스트라
    dijkstra(1,   N, dist1);
    dijkstra(v1,  N, distv1);
    dijkstra(v2,  N, distv2);

    long long route1 = (long long)dist1[v1] + distv1[v2] + distv2[N];
    long long route2 = (long long)dist1[v2] + distv2[v1] + distv1[N];
    long long ans = route1 < route2 ? route1 : route2;
    if (dist1[v1] == INT_MAX || distv1[v2] == INT_MAX || distv2[N] == INT_MAX)
        ans = LLONG_MAX;
    if (dist1[v2] == INT_MAX || distv2[v1] == INT_MAX || distv1[N] == INT_MAX)
        ans = LLONG_MAX;

    if (ans >= INT_MAX) printf("-1\n");
    else printf("%lld\n", ans);

}

