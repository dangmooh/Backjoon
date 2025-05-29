#include <iostream>
#include <vector>

using namespace std;

#define MAX 100001
vector<int> tree[MAX];
int dp[MAX][MAX];
bool visited[MAX];
int N;

void dfs(int node)
{
    
}

int main()
{
    cin >> N;

    for(int i=0; i<N; ++i)
    {
        int s, e;
        cin >> s >> e;
        tree[e].push_back(s);
        tree[s].push_back(e);
    }

    dfs(1);

    return 0;
}