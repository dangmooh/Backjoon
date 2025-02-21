#include <iostream>
#include <vector>
#include <limits>

using namespace std;

typedef long long ll;

int N, M;
vector<pair<int, int>> graph[501];
const ll INF = numeric_limits<ll>::max();

vector<ll> bellmanFord()
{
    vector<ll> dist(N+1, INF);
    dist[1] = 0;

    for(int i = 1; i < N; i++)
    {
        for(int u =1; u <= N; u++)
        {
            if(dist[u] == INF) continue;

            for(const auto &node : graph[u])
            {
                if(node.second + dist[u] < dist[node.first])
                {
                    dist[node.first] = node.second + dist[i];
                }
            }
        }
    }

    for(int i = 1; i<= N; i++)
    {
        if(dist[i] == INF) continue;
        for(const auto &node : graph[i])
        {
            if(dist[i] + node.second < dist[node.first])
            {
                return {};
            }
        }
    }

    return dist;

}

int main()
{

    cin >> N >> M;


    for(int i = 0; i<M; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].emplace_back(b, c);
    }

    vector<ll> result = bellmanFord();

    if (result.empty()) {
        cout << "-1\n"; // 음수 사이클 존재
    } else {
        for (int i = 2; i <= N; i++) {
            if (result[i] == INF)
                cout << "-1\n"; // 도달 불가능
            else
                cout << result[i] << '\n';
        }
    }
    return 0;
}