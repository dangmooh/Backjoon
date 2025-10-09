/*


최단 경로 “경로 자체”를 복원해야 할 때

경로를 실제로 출력해야 하는 문제 (ex: 이동 경로, 명령 문자열 등)

방향성이 중요할 때

같은 위치라도 “들어온 방향”에 따라 다르게 처리해야 할 때
(예: 미로에서 돌아서 오는 경우, 이동 방향별 다른 조건 등)

상태가 여러 개일 때

ex) 벽을 부쉈는지, 열쇠를 들고 있는지 등 “방문 상태”가 다르면 따로따로 방문 체크

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
