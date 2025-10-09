
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX 1000001

int N;
vector<int> adj[MAX];
int dp[MAX][2];
bool visited[MAX];

void dfs(int u)
{
    visited[u] = true;
    dp[u][0] = 0;
    dp[u][1] = 1;

    for(int v : adj[u])
    {
        if(!visited[v])
        {
            dfs(v);
            dp[u][0] += dp[v][1];
            dp[u][1] = min(dp[v][0], dp[v][1]);
        }
    }
}

int main()
{
    cin >> N;

    for(int i=0; i<N; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1);

    return 0;
}