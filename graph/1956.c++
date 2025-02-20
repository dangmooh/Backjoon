/*
플로이드 워셜


*/


#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

int V, E;
const int INF = numeric_limits<int>::max();

vector<vector<int>> dist;

void folydWarshall()
{

    for(int k = 1; k <= V; k++)
    {
        for(int i = 1; i <=V; i++)
        {
            for(int j= 1; j <= V; j++)
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
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> V >> E;

    dist.assign(V+1, vector<int>(V+1,INF));

    for(int i = 1; i <=V; i++) dist[i][i] = 0;

    for(int i = 0; i < E; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        dist[a][b] = c;
    }

    folydWarshall();

    int minCycle = INF;

    for(int i = 1; i<= V; i++)
    {
        for(int j = 1; j <=V; j++)
        {
            if(i != j && dist[i][j] != INF && dist[j][i] != INF)
            {
                minCycle = min(minCycle, dist[i][j] + dist[j][i]);
            }
        }
    }

    cout << (minCycle == INF ? -1 : minCycle) << '\n';

    return 0;
}