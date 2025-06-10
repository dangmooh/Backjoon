/*
주제 : 비용이 있는 방향 그래프에서 출발점에서 도착점까지 최소 비용 구하기
시간 : O(N + MlogN)
*/

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <queue>

using namespace std;

const int INF = numeric_limits<int>::max();
vector<pair<int,int>> graph[1001];


vector<int> dijkstra(int start)
{
    vector<int> distance(1001, INF);
    priority_queue<pair<int,int>> pq;
    pq.push({0, start});
    distance[start] = 0;

    while(!pq.empty())
    {
        const auto [cost, start] = pq.top();
        pq.pop();
        
        if(cost > distance[start]) continue; // 이거를 왜 해야하지?

        for(const auto [next_cost, next] : graph[start])
        {
            
            if(next_cost + distance[start] > distance[next]) continue;

            distance[next] = next_cost + distance[start];
            pq.push({distance[next], next});


        }


    }
    return distance;
}

int main()
{
    int N, M;
    cin >> N >> M;

    for(int i=0; i<M; i++)
    {
        int start, end, cost;
        cin >> start >> end >> cost;

        graph[start].emplace_back(cost, end);
    }

    int start, end;
    cin >> start >> end;

    vector<int> distance = dijkstra(start);
    cout << distance[end] << "\n";


    return 0;
}