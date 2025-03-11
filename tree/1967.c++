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
            if(dist[child] == -1)  // 방문하지 않은 노드
            {
                dist[child] = dist[parent] + cost;
                q.push(child);
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    adj.resize(N+1);
    for(int i = 0; i < N-1; i++)  // ⚠ 트리의 간선 개수는 N-1개
    {
        int s;
        cin >> s;

        while(true)
        {
            int e, c;
            cin >> e;
            if (e == -1) break;
            cin >> c;
            adj[s].emplace_back(e, c);
            adj[e].emplace_back(s, c);  // ⚠ 양방향 그래프 저장 필요
        }
    }

    // Step 1: BFS from node 1 to find the farthest node
    bfs(1);
    int index = 1, distance = 0;  // ⚠ index 초기화
    for (int i = 1; i <= N; i++)  // ⚠ 1번 노드 포함
    {
        if(dist[i] > distance)
        {
            distance = dist[i];
            index = i;
        }
    }

    // Step 2: BFS from the farthest node to get the tree's diameter
    bfs(index);
    int result = 0;
    for (int i = 1; i <= N; i++)
    {
        if(dist[i] > result)
        {
            result = dist[i];
        }
    }

    cout << result << '\n';
    return 0;
}
