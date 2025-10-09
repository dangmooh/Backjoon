/*
음수로 음수 경로 확인 bellman fold
*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using pii = pair<int,int>;
using Graph = vector<vector<pii>>;


bool spfa(int N, const Graph& graph)
{
    vector<int> dist(N+1, 0), cnt(N+1,0);
    vector<bool> inQueue(N+1, false);
    queue<int> q;

    for(int i=1; i<=N; ++i)
    {
        q.push(i);
        inQueue[i] = true;
    }

    while(!q.empty())
    {
        int u = q.front(); q.pop();
        inQueue[u] = false;

        for(auto& [v, w] : graph[u])
        {
            if(dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                cnt[v]++;
                if(cnt[v] >= N)
                {
                    return true;
                }
                if(!inQueue[v])
                {
                    q.push(v);
                    inQueue[v] = true;
                }
            }
        }
    }

    return false;
}

int main()
{
    int T;
    cin >> T;

    while(T--)
    {
        int N, M, W;
        cin >> N >> M >> W;

        Graph graph(N+1);

        for(int i=0; i<M; ++i)
        {
            int S, E, T;
            cin >> S>> E >> T;
            graph[S].emplace_back(E, T);
            graph[E].emplace_back(S, T);
        }

        for(int i=0; i<W; ++i)
        {
            int S, E, T;
            cin >> S >> E >> T;
            graph[S].emplace_back(E, -T);
        }

        bool cycle = spfa(N, graph);
        if(cycle)
        {
            cout << "YES" << '\n';
        }
        else
        {
            cout << "NO" << '\n';
        }
    }



    return 0;
}