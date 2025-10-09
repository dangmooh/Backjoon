#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <limits>
#include <tuple>
using namespace std;

using ll = long long;
using Map = vector<vector<char>>;

#define MAX_N 50
#define MAX_Q 1000

int N;
Map map;
int r1, c1, r2, c2;

constexpr ll INF = numeric_limits<ll>::max();


const pair<int, int> dd[4] = { {-1,0}, {1,0}, {0,-1}, {0,1} };

inline bool inb(int y, int x) { return (x >= 0 && x < N && y >= 0 && y < N); }

inline bool canJump(int y, int x, int dir, int k) {
    int cy = y, cx = x;
    for (int step = 1; step <= k; ++step) {
        cy += dd[dir].first;
        cx += dd[dir].second;
        if (!inb(cy, cx)) return false;
        if (map[cy][cx] == '#') return false;         // 경로/착지에 바위
        // 착지만 금지라면:
        if(step==k && map[cy][cx]=='S') return false;
    }
    return true;
}

ll dijkstra(int r1, int c1, int r2, int c2)
{
    static ll dist[MAX_N][MAX_N][6];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 1; k <= 5; k++)
                dist[i][j][k] = INF;

    using Node = tuple<ll, int, int, int>;
    priority_queue<Node, vector<Node>, greater<>> pq;
    dist[r1][c1][1] = 0;
    pq.emplace(0, r1, c1, 1);

    while (!pq.empty())
    {
        ll t;
        int r, c, k;
        tie(t, r, c, k) = pq.top(); pq.pop();
        if (t != dist[r][c][k]) continue;
        if (r == r2 && c == c2) return t;

        for (int d = 0; d < 4; ++d)
        {
            int nr = r + dd[d].first * k, nc = c + dd[d].second * k;
            if (canJump(r, c, d, k)) {
                if (dist[nr][nc][k] > t + 1) {
                    dist[nr][nc][k] = t + 1;
                    pq.emplace(t + 1, nr, nc, k);
                }
            }
        }

        if (k < 5) {
            ll cost = (k + 1) * (k + 1);
            if (dist[r][c][k + 1] > t + cost) {
                dist[r][c][k + 1] = t + cost;
                pq.emplace(t + cost, r, c, k + 1);
            }
        }

        for (int nk = 1; nk < k; nk++) {
            if (dist[r][c][nk] > t + 1) {
                dist[r][c][nk] = t + 1;
                pq.emplace(t + 1, r, c, nk);
            }
        }
    }
    return -1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    map.resize(N, vector<char>(N));

    for (int i = 0; i < N; ++i)
    {
        string s; cin >> s;
        for (int j = 0; j < N; ++j)
        {
            map[i][j] = s[j];
        }
    }

    int Q;
    cin >> Q;

    while (Q--)
    {
        cin >> r1 >> c1 >> r2 >> c2;
        r1--; r2--; c1--; c2--;
        cout << dijkstra(r1, c1, r2, c2) << '\n';

    }

    return 0;
}