/*

처음 시작은 (0,0)이고 동쪽 방향으로 시작한다. 직사각형 영역(n,m)이고 1. 1<=n,m<=300 2. 0<=x<=n, 0<=y<=m 3. 목적지로 이동이 불가할 경우 -1을 출력

움직임은 총 3개로 1. 한칸 이동 후 오른쪽으로 90도 회전 2. 오른쪽 90도 회전 후 한 칸 이동 3. 오른쪽으로 90도 회전

목표 x,y가 주어지면 해당 위치로 이동하는 최소 명령 수를 출력하라


*/


#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int dx[4] = {1, 0, -1, 0}; // 동, 남, 서, 북
int dy[4] = {0, 1, 0, -1};

struct State {
    int x, y, dir, cnt;
};

int min_commands(int n, int m, int goal_x, int goal_y) {
    vector<vector<vector<bool>>> visited(n, vector<vector<bool>>(m, vector<bool>(4, false)));
    queue<State> q;
    q.push({0, 0, 0, 0}); // (x, y, dir, cnt)
    visited[0][0][0] = true;

    while (!q.empty()) {
        auto [x, y, dir, cnt] = q.front(); q.pop();

        if (x == goal_x && y == goal_y)
            return cnt;

        // 1. 한 칸 이동 후 오른쪽 90도 회전
        int nx1 = x + dx[dir], ny1 = y + dy[dir];
        int ndir1 = (dir + 1) % 4;
        if (nx1 >= 0 && nx1 < n && ny1 >= 0 && ny1 < m && !visited[nx1][ny1][ndir1]) {
            visited[nx1][ny1][ndir1] = true;
            q.push({nx1, ny1, ndir1, cnt + 1});
        }

        // 2. 오른쪽 90도 회전 후 한 칸 이동
        int ndir2 = (dir + 1) % 4;
        int nx2 = x + dx[ndir2], ny2 = y + dy[ndir2];
        if (nx2 >= 0 && nx2 < n && ny2 >= 0 && ny2 < m && !visited[nx2][ny2][ndir2]) {
            visited[nx2][ny2][ndir2] = true;
            q.push({nx2, ny2, ndir2, cnt + 1});
        }

        // 3. 오른쪽 90도 회전만(이동 X)
        int ndir3 = (dir + 1) % 4;
        if (!visited[x][y][ndir3]) {
            visited[x][y][ndir3] = true;
            q.push({x, y, ndir3, cnt + 1});
        }
    }
    return -1;
}

int main() {
    int n, m, gx, gy;
    cin >> n >> m >> gx >> gy;
    cout << min_commands(n, m, gx, gy) << '\n';
    return 0;
}
