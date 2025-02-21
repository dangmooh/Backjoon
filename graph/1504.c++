/*
dijkstra 시간 복잡도 = O(3 (V + E) log V)
N = 800, E = 200,000 이므로 가능하다.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;


vector<vector<pair<int,int>>> adj;
const int INF = numeric_limits<int>::max();
int N, E;

vector<int> dijkstra(int s, int e)
{
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    vector<int> dist(N+1, INF);
    pq.push({0,s});
    dist[s] = 0;

    while(!pq.empty())
    {
        int curDist = pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        if(curDist > dist[cur]) continue;

        for(const auto [next, Dist] : adj[cur])
        {
            int nextDist = curDist + Dist;
            if(nextDist < dist[next])
            {
                dist[next] = nextDist;
                pq.push({nextDist, next});
            }
        }
    }
    return dist;
}

int main()
{
    cin >> N >> E;

    adj.resize(N+1);
    for(int i = 0; i < E; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a,c);
    }

    int v1,v2;
    cin >> v1 >> v2;

    vector<int> road1 = dijkstra(1, E);
    vector<int> road2 = dijkstra(v1, E);
    vector<int> road3 = dijkstra(v2, E);

    // 경로1: 1 → v1 → v2 → N
    int route1 = (road1[v1] == INF || road2[v2] == INF || road3[N] == INF) ? INF : road1[v1] + road2[v2] + road3[N];
    // 경로2: 1 → v2 → v1 → N
    int route2 = (road1[v2] == INF || road3[v1] == INF || road2[N] == INF) ? INF : road1[v2] + road3[v1] + road2[N];


    int result = min (route1, route2);
    cout << ((result == INF) ? -1 : result) << '\n';

    return 0;
}