#include <iostream>
#include <vector>


using namespace std;

int N;
vector<vector<int>> node;


void dfs(int p, vector<int>& parent)
{
    for(int child : node[p])
    {
        if(parent[child] == 0)
        {
            parent[child] = p;
            dfs(child, parent); 
        }
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    cin >> N;

    node.resize(N+1);
    vector<int> parent(N+1, 0);

    for(int i=0; i<N; ++i)
    {
        int a, b; cin >> a >> b;

        node[a].push_back(b);
        node[b].push_back(a);
    }

    parent[1] = 1;
    dfs(1, parent);

    for(int i=2; i<=N; ++i)
    {
        cout << parent[i] << '\n';
    }

    return 0;
}