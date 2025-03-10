#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<pair<int,int>>> adj;
vector<int> dist;
int N;


void bfs(int start)
{
    dist.assign(N+1, -1);
    dist[start] = 0;
    queue<int> q;
    q.push(start);

    while(!q.empty())
    {
        int parent = q.front();
        q.pop();

        for(const auto &[child, cost] : adj[parent])
        {
            if(dist[child] == -1)
            {
                dist[child] = cost + dist[parent];
                q.push(child);
            }
        }
    }
}

int main()
{

    cin >> N;

    adj.resize(N+1);
    for(int i=0; i< N; i++)
    {
        int s;
        cin >> s;

        while(1)
        {
            int e, c;
            cin >> e;
            if (e == -1) break;
            cin >> c;
            adj[s].emplace_back(e, c);
        }
    }

    bfs(1);
    int index, distance = 0;
    for (int i= 2; i<= N; i++)
    {
        if(dist[i] > distance)
        {
            distance = dist[i];
            index = i;
        }
    }

    bfs(index);

    int result = 0;
    for (int i= 1; i<= N; i++)
    {
        if(dist[i] > result)
        {
            result = dist[i];
        }
    }
    cout << result << '\n';
    return 0;
}