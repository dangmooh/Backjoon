#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <unordered_set>

using namespace std;

using Pii = pair<int,int>;
using Graph = vector<vector<Pii>>;

constexpr int INF = numeric_limits<int>::max(); 
#define MAX_ID 30001

struct TRIP {
    int id, revenue, dest, dist, money = -1;
};

struct comp {
    bool operator()(const TRIP &A, const TRIP &B) {
        if(A.money != B.money) return A.money < B.money;
        else return A.id > B.id;
    }
};

TRIP tripList[MAX_ID];
unordered_set<int> idList;
Graph graph;
vector<int> dist;
int n, m;
priority_queue<TRIP, vector<TRIP>, comp> trip_pq;


void dijkstra(int start)
{
    priority_queue<Pii, vector<Pii>, greater<>> pq;
    dist.assign(n, INF);
    dist[start] = 0;
    pq.push({0, start});

    while(!pq.empty())
    {
        Pii cur = pq.top(); pq.pop();

        if(cur.first > dist[cur.second]) continue;

        for(const auto &nxt : graph[cur.second])
        {
            if(dist[nxt.first] > cur.first + nxt.second)
            {
                dist[nxt.first] = dist[cur.second] + nxt.second;
                pq.emplace(dist[nxt.first], nxt.first);
            }
        }
    }
}

void make_tree()
{
    cin >> n >> m;
    graph.resize(n);
    for(int i=0; i<m; ++i)
    {
        int v, u, w;
        cin >> v >> u >> w;
        graph[v].push_back({u, w});
        graph[u].push_back({v, w});
    }

    dijkstra(0);


}

void make_trip()
{
    int id, revenue, dest, cost;
    cin >> id >> revenue >> dest;
    idList.insert(id);
    cost = dist[dest];
    tripList[id] = {id, revenue, dest, cost, revenue - cost};
    trip_pq.push(tripList[id]); // 전역 PQ에 push
}

void cancel_trip()
{
    int id;
    cin >> id;
    idList.erase(id);
}

void sell_trip()
{
    while(!trip_pq.empty())
    {
        TRIP cur = trip_pq.top(); trip_pq.pop();
        
        if(!idList.count(cur.id)) continue;

        int new_cost = dist[cur.dest];
        int new_money = cur.revenue - new_cost;
        if (cur.money != new_money)
        {
            tripList[cur.id].dist = new_cost;
            tripList[cur.id].money = new_money;
            trip_pq.push(tripList[cur.id]);
            continue;
        }
        // 3. 판매 불가 (이익 < 0)
        if (new_money < 0 || new_cost == INF) {
            //idList.erase(cur.id);
            continue;
        }

        // 4. 판매 성공
        cout << cur.id << "\n";
        idList.erase(cur.id);
        return;
    }
    cout << -1 << "\n";
}

void update_trip()
{
    for(const auto &id : idList)
    {
        tripList[id].dist = dist[tripList[id].dest];
        tripList[id].money = tripList[id].revenue - tripList[id].dist;
        trip_pq.push(tripList[id]); // 갱신된 값 push
    }
}

int main()
{
    int Q; cin >> Q;

    while(Q--)
    {
        int req; cin >> req;

        switch(req)
        {
            case 100:
            make_tree();
            break;

            case 200:
            make_trip();
            break;

            case 300:
            cancel_trip();
            break;

            case 400:
            sell_trip();
            break;

            case 500:
            int s; cin >> s;
            dijkstra(s);
            update_trip();
            break;
        }
    }

    return 0;
}
