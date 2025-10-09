/*

dijkstra

한 노드에서 다른 모든 노드까지의 최단거리 계산
시간 복잡도 : O((V+E)logV)
E가 V^2에 근접하면 배열 기반의 O(V^2)보다 오히려 성능이 떨어진다.

priority queue를 이용해서 가장 짧은 거리를 가진 노드를 꺼낸다.
재방문을 허용하기에 음수 가중치도 허용하지만 cycle은 불가능 <- 우선순위 큐의 특성으로

*/

#include <vector>
#include <queue>

using namespace std;

using pii = pair<int,int>;
using Graph = vector<vector<pii>>;

constexpr int INF = 1e9;

bool cycle = false;

vector<int> dijkstra(int start, const Graph& graph, int N)
{
    vector<int> dist(N+1,INF);
    priority_queue<pii, vector<pii>, greater<>> pq;
    pq.emplace(0, start);
    dist[start] = 0;

    while(!pq.empty())
    {
        int curDist = pq.top().first, u = pq.top().second; pq.pop();

        if(curDist > dist[u]) continue;

        for(const auto& [e, weight] : graph[u])
        {
            int newDist = curDist + weight;
            if(dist[e] > newDist)
            {
                dist[e] = newDist;
                pq.emplace(newDist, e);
            }
        }
    }

    return dist;
}


