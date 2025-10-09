/*
floyd-warshall

시간복잡도 : O(N^3)

정점의 개수가 100이하일 경우 사용
*/


#include <vector>
#include <algorithm>

using namespace std;

constexpr int INF = 1e9;

vector<vector<int>> floydWarshall(const vector<vector<int>>& dist, int n)
{
    vector<vector<int>> min_dist(n+1, vector<int>(n+1, INF));
    
    for(int k=1; k<=n; ++k)
    {
        for(int i=1; i<=n; ++i)
        {
            for(int j=1; j<=n; ++j)
            {
                min_dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    
    return min_dist;
}