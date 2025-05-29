#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX 10001

vector<int> tree[MAX];
bool visited[MAX];
int dp[MAX][2];
int people[MAX];

void dfs(int node)
{
    visited[node] = true;

    dp[node][0] = 0;
    dp[node][1] = people[node];

    for(int child : tree[node])
    {
        if(!visited[child])
        {
            dfs(child);

            dp[node][0] += max(dp[child][1], dp[child][0]);
            dp[node][1] += dp[child][0];
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for(int i=0; i<N; i++)
    {
        cin >> people[i+1];
    }

    for(int i=0;i<N;i++)
    {
        int s, e;
        cin >> s >> e;

        tree[s].push_back(e);
        tree[e].push_back(s);
    }

    dfs(1);

    cout << max(dp[1][0], dp[1][1]) << "\n";

    return 0;
}