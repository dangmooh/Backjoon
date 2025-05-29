#include <iostream>
#include <vector>
using namespace std;

#define MAX 100001

vector<int> tree[MAX];
int praise[MAX];

void dfs(int current)
{
    for (int child : tree[current])
    {
        praise[child] += praise[current];  // 누적 전달
        dfs(child);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    int root;
    for (int i = 1; i <= n; i++)
    {
        int boss;
        cin >> boss;
        if (boss == -1)
            root = i;
        else
            tree[boss].push_back(i);
    }

    for (int i = 0; i < m; i++)
    {
        int idx, w;
        cin >> idx >> w;
        praise[idx] += w;
    }

    dfs(root);

    for (int i = 1; i <= n; i++)
        cout << praise[i] << " ";
    cout << "\n";

    return 0;
}
