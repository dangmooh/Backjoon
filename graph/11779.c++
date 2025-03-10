/*
도시 = 1000, 노선 = 100000
이므로 floyd-Warshall O(N*N)은 불가
dijkstra O(n + m logn)
시작 지점에서 모든 지점까지 최단 거리로 가는 경우
*/

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

vector<vector<pair<int,int>>> bus;
const int INF = numeric_limits<int>::max();
int n, m;
vector<int> trace;

vector<int> dikstra(int start, int end)
{
    vector<int> distance(n+1, INF);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0,start});
    distance[start] = 0;
    trace.resize(n+1, -1);

    while(!pq.empty())
    {
        int cur = pq.top().second;
        int curD = pq.top().first;
        pq.pop();
        
        if(curD > distance[cur]) continue;

        for(const auto [next, dist] : bus[cur])
        {
            int nextDist = curD + dist;
            if(nextDist < distance[next])
            { 
                trace[next] = cur;
                distance[next] = nextDist;
                pq.push({nextDist, next});
            }
        }

    }


    return distance;
}

int main()
{
    cin >> n >> m;
    bus.resize(n+1);

    for(int i=0; i<m; i++)
    {
        int s, e, c;
        cin >> s >> e >> c;

        bus[s].push_back({e,c});   
    }
    int s, e;
    cin >> s >> e;
    vector<int> dist = dikstra(s, e);

    vector<int> result;
    for(int i=e; i != -1; i =trace[i])
    {
        result.push_back(i);
    }
    cout << dist[e] << '\n';
    cout << result.size() << '\n';
    for(int i=result.size()-1; i>=0; i--)
    {
        cout << result[i] << " ";
    }
    cout << '\n';
    return 0;
}