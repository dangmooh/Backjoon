#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int n, m;
const int INF = numeric_limits<int>::max();
vector<vector<int>> dist;


void floydWashall()
{
    for(int k = 1; k <= n; k++)
    {
        for(int i = 1; i<=n;i++)
        {
            for(int j =1; j<=n;j++)
            {
                if(dist[i][k] != INF && dist[k][j] != INF)
                {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;

    dist.assign(n+1, vector<int>(n+1, INF));

    for(int i = 1; i <= n; i++) dist[i][i] = 0;


    for(int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;

        dist[a][b] = c;
    }

    floydWashall();

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(dist[i][j] == INF)
                cout << "0 ";
            else
                cout << dist[i][j] <<" ";
        }
        cout << '\n';
    }
    return 0;
}