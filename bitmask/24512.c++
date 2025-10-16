#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

constexpr int INF = numeric_limits<int>::max();


int main()
{
    int N, M; 
    cin >> N >> M;

    vector<vector<int>> cost(N, vector<int>(N, INF));

    for(int i=0; i<M; ++i)
    {
        int u, v, c;
        cin >> u >> v >> c;

        cost[u-1][v-1] = c;
    }

    int FULL = (1 << N) - 1;
    vector<vector<int>> dp((1<<N), vector<int>(N, INF));
    vector<vector<int>> parent_prev((1<<N), vector<int>(N, -1));
    vector<vector<int>> parent_mask((1<<N), vector<int>(N, -1));

    int start = 0;
    dp[1<<start][start] = 0;


     for (int mask = 0; mask <= FULL; mask++) { // 전체 조합
        for (int u = 0; u < N; u++) { //시작 지점을 선택
            if (!(mask & (1 << u))) continue; // u에 방문하지 않은 경우
            if (dp[mask][u] == INF) continue; // 해당 상태에 도착한적 없는 경우
            for (int v = 0; v < N; v++) { // 도착 지점을 선택
                if (mask & (1 << v)) continue; // 도착지점에 간적 있다면
                if (cost[u][v] == INF) continue; // 길이 없다면
                int nmask = mask | (1 << v); // 새로운 상태 
                int cand = max(dp[mask][u], cost[u][v]); // 현재까지 경로의 최대값
                if (cand < dp[nmask][v]) { // 더 작은 bottleneck이면 갱신
                    dp[nmask][v] = cand; 
                    parent_prev[nmask][v] = u; // 이전 마지막 정점
                    parent_mask[nmask][v] = mask; // 이전 방문집합
                }
            }
        }
    }

    int answer = INF;
    int best_last = -1;
    for (int u = 0; u < N; u++) {
        if (u == start) continue;
        if (dp[FULL][u] == INF) continue;      // 모든 정점 방문 상태로 u에 도달 불가
        if (cost[u][start] == INF) continue;   // u→start 간선이 없으면 사이클 완성 불가
        int total = max(dp[FULL][u], cost[u][start]); // 사이클 완성한 최종 bottleneck
        if (total < answer) {
            answer = total;
            best_last = u;
        }
    }

    if (answer == INF) {
        cout << -1 << "\n";
        return 0;
    }

    cout << answer << "\n";

    vector<int> path;
    int mask = FULL;
    int cur = best_last;
    while (cur != start) {
        path.push_back(cur);
        int pm = parent_prev[mask][cur];
        int pmask = parent_mask[mask][cur];
        mask = pmask;
        cur = pm;
    }
    path.push_back(start);
    reverse(path.begin(), path.end());

    for (int x : path) {
        cout << x + 1 << " ";
    }

    return 0;
}
