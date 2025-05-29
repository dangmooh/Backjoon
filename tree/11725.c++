#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N;
vector<int> parent;
vector<vector<int>> adj;

void bfs(int node)
{
    queue<int> q;
    q.push(node);
    parent[node] = -1;

    while(!q.empty())
    {
        int cur = q.front();
        q.pop();

        for (int next : adj[cur])
        {
            if(parent[next] == 0)
            {
                parent[next] = cur;
                q.push(next);
            }
        }
    }
}

int main()
{
    cin >> N;
    adj.resize(N+1);
    parent.resize(N+1, 0);

    for(int i=0; i<N-1; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    parent[1] = -1;
    bfs(1);

    for(int i=2; i<=N; i++)
    {
        cout << parent[i] << '\n';
    }

    return 0;
}