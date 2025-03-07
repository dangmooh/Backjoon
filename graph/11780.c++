/*
floydWarshall O(n^3) 이므로 100이하인 경우 사용가능
모든 정점 쌍 간 최단 경로를 구하는 알고리즘

경로 추적

*/

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int INF = 1e9;
int n, m;
vector<vector<int>> dist, trace;

// 플로이드-워셜 알고리즘 수행
void floydWarshall() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    trace[i][j] = trace[k][j]; // 경로 갱신
                }
            }
        }
    }
}

// 경로를 역추적하여 출력 i = 시작 j = 도착
vector<int> getPath(int i, int j) {
    vector<int> path;
    if (trace[i][j] == -1) return path; // 경로 없음
    while (j != i) {
        path.push_back(j);
        j = trace[i][j];
    }
    path.push_back(i);
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    dist.assign(n + 1, vector<int>(n + 1, INF));
    trace.assign(n + 1, vector<int>(n + 1, -1));

    for (int i = 1; i <= n; i++) {
        dist[i][i] = 0; // 자기 자신 비용 0
    }

    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        if (dist[u][v] > c) { // 최소 비용 갱신
            dist[u][v] = c;
            trace[u][v] = u; // 경로 초기화
        }
    }

    floydWarshall();

    // 최소 비용 출력
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << (dist[i][j] == INF ? 0 : dist[i][j]) << " ";
        }
        cout << "\n";
    }

    // 경로 출력
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j || dist[i][j] == INF) {
                cout << "0\n"; // 경로 없음
            } else {
                vector<int> path = getPath(i, j);
                cout << path.size() << " ";
                for (int city : path) {
                    cout << city << " ";
                }
                cout << "\n";
            }
        }
    }

    return 0;
}
