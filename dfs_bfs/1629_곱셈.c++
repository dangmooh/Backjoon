#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using pii = pair<int,int>;
using Graph = vector<vector<pii>>;

constexpr int INF = 1e9;

vector<int> dijkstra(int start, const Graph& graph, int V)
{
    priority_queue<pii, vector<pii>, greater<>> pq;
    pq.emplace(0, start);
    vector<int> dist(V+1, INF);
    dist[start] = 0;

    while(!pq.empty())
    {
        int curDist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if(curDist > dist[u]) continue;

        for(auto& [v, weight] : graph[u])
        {
            if(dist[v] > curDist + weight)
            {
                dist[v] = curDist + weight;
                pq.emplace(dist[v], v);
            }
        }
    }

    return dist;
}

int main()
{
    int V, E;
    cin >> V >> E;
    int K;
    cin >> K;

    Graph graph(V+1);

    for(int i=0; i< E; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
    }

    vector<int> dist = dijkstra(K, graph, V);

    for (int i = 1; i <= V; ++i) {
        if (dist[i] == INF)
            cout << "INF\n";
        else
            cout << dist[i] << '\n';
    }

    return 0;
}

