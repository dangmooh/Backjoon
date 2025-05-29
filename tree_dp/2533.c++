#include <iostream>
#include <vector>

using namespace std;

const int MAX = 1000001;

vector<int> tree[MAX];
bool visited[MAX];
int dp[MAX][2];

void dfs(int node)
{
    visited[node] = true;
    dp[node][0] = 0;
    dp[node][1] = 1;

    for (int child : tree[node])
    {
        if(!visited[child])
        {
            dfs(child);

            dp[node][0] += dp[child][1];
            dp[node][1] += min(dp[child][0], dp[child][1]);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for(int i=0; i<n-1; i++)
    {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    dfs(1);

    cout << min(dp[1][0], dp[1][1]) << "\n";

    return 0;
}