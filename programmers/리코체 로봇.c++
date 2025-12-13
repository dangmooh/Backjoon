/*
2025.12.11

격자모양 목표 위치 도착 최소 거리
상 하 좌 우 막힐때까지 이동
도착할 수 없다면 -1 return

*/

#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    int x, y, d; // 좌표와 이동 횟수
};

int solution(vector<string> board) {
    int h = board.size();
    int w = board[0].size();

    int sx = -1, sy = -1; // R 위치
    int gx = -1, gy = -1; // G 위치

    // 시작, 목표 위치 찾기
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (board[i][j] == 'R') {
                sx = i; sy = j;
            } else if (board[i][j] == 'G') {
                gx = i; gy = j;
            }
        }
    }

    // 방문 배열
    vector<vector<bool>> visited(h, vector<bool>(w, false));

    // BFS
    queue<Node> q;
    q.push({sx, sy, 0});
    visited[sx][sy] = true;

    // 상하좌우
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    while (!q.empty()) {
        Node cur = q.front();
        q.pop();

        // 목표에 도착
        if (cur.x == gx && cur.y == gy) {
            return cur.d;
        }

        // 4방향으로 미끄러지기
        for (int dir = 0; dir < 4; ++dir) {
            int nx = cur.x;
            int ny = cur.y;

            // 장애물/벽을 만날 때까지 이동
            while (true) {
                int tx = nx + dx[dir];
                int ty = ny + dy[dir];

                // 보드 밖이거나 장애물 만나면 멈춤
                if (tx < 0 || tx >= h || ty < 0 || ty >= w ||
                    board[tx][ty] == 'D') {
                    break;
                }

                nx = tx;
                ny = ty;
            }

            // 제자리면(한 칸도 못 움직인 경우) 스킵
            if (nx == cur.x && ny == cur.y) continue;

            if (!visited[nx][ny]) {
                visited[nx][ny] = true;
                q.push({nx, ny, cur.d + 1});
            }
        }
    }

    // 도달 불가
    return -1;
}
