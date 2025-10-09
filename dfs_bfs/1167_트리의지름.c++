#include <iostream>
#include <vector>
#include <cstring>


using namespace std;

constexpr int MAX_V = 100001;

vector<pair<int,int>> tree[MAX_V];
bool visited[MAX_V];
int maxDist = 0;
int farthestNode = 0;


void dfs(int node, int dist)
{
    visited[node] = true;

    if(dist > maxDist)
    {
        maxDist = dist;
        farthestNode = node;
    }

    for(const auto& [next, weight] : tree[node])
    {
        if(!visited[next])
        {
            dfs(next, dist + weight);
        }
    }

}

int main()
{
    int V;
    cin >> V;

    for(int i=1; i< 6; ++i)
    {
        int tmp;
        cin >> tmp;
        if(tmp == i) continue;
        while(tmp != -1)
        {
            int v, e;
            cin >> v >> e;
            tree[i].emplace_back(v, e);
        }
    }

    memset(visited, false, sizeof(visited));
    dfs(1, 0);

    maxDist = 0;
    dfs(farthestNode, 0);

    cout << maxDist << '\n';

    return 0;
}