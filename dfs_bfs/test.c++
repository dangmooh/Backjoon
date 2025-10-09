#include <iostream>
#include <vector>
#include <queue>

using namespace std;

constexpr int INF = 1e9;
vector<vector<pair<int,int>>> board;
int N, M, X;

vector<int> dijkstra(int start)
{
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    vector<bool> visited(N+1, false);
    vector<int> dist(N+1, INF);
    pq.emplace(0, start);

    while(!pq.empty())
    {
        pair<int,int> cur = pq.top();
        pq.pop();
        
        if(cur.first > dist[cur.second])
        {
            continue;
        }

        for(auto& next : board[cur.second])
        {
            if(cur.first + next.second < dist[next.first])
            {
                dist[next.first] = cur.first + next.second;
                pq.emplace(dist[next.first], next.second);
            }
        }
    }

    return dist;
}

int main()
{

    cin >> N >> M >> X;

    board.resize(N+1);
    for(int i=0; i<N; ++i)
    {
        int u, e, t;
        cin >> u >> e >> t;
        board[e].emplace_back(u, t);
    }

    vector<int> answer = dijkstra(X);

    int 
    return 0;
}