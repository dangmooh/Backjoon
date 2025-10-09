/*
다익스트라 O((V+E)log(V))
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

constexpr int INF = 1e9;
using pii = pair<int,int>;
using Graph = vector<vector<pii>>;

vector<int> dijkstra(int start, const Graph& graph, int N)
{
    vector<int> dist(N+1, INF);
    priority_queue<pii, vector<pii>, greater<>> pq;
    dist[start] = 0;

    pq.emplace(0, start);

    while(!pq.empty())
    {
        int curDist = pq.top().first;
        int u = pq.top().second;

        pq.pop();

        if(curDist > dist[u]) continue;

        for (const auto& [v, w] : graph[u])
        {
            if(dist[v] > curDist + w)
            {
                dist[v] = curDist + w;
                pq.emplace(dist[v], v);
            }
        }

    }

    return dist;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, X;
    cin >> N >> M >> X;

    Graph graph(N+1), reverseGraph(N+1);

    for(int i=0; i<M; ++i)
    {
        int v, e, w;
        cin >> v >> e >> w;
        graph[v].emplace_back(e, w);
        reverseGraph[e].emplace_back(v, w);
    }

    vector<int> to = dijkstra(X, graph, N);

    vector<int> from = dijkstra(X, reverseGraph, N);

    int answer = 0;

    for(int i=1; i<N+1; ++i)
    {
        answer = max(answer, to[i] + from[i]);
    }
    cout << answer << '\n';

    return 0;

}
    