#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using Graph = vector<vector<int>>;

constexpr int INF = 1e9;

int main()
{
    int n, m;
    cin >> n >> m;

    Graph dist(n+1, vector<int>(n+1, INF));
    for(int i=0; i<m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;

        dist[u][v] = min(dist[u][v], w);
    }

    for(int i=1; i<=n; ++i)
    {
        for(int j=1; j<=n; ++j)
        {
            for(int k=1; k<=n; ++k)
            {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    for(int i=1; i<=n; ++i)
    {
        for(int j=1; j<=n; ++j)
        {
            cout << (dist[i][j] == INF ? 0 : dist[i][j]) << '\n';
        }
    }

    return 0;
}