#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAXM 100


int dx[4] = {0,0,1,-1}, dy[4] = {1,-1,0,0};
int visited[MAXM][MAXM];
int N, M;

inline int idx(int x, int y) {return y*M + x;}
inline bool inb(int x, int y) {return x>=0 && x<M && y>=0 && y<N;}

int bfs(const char* maps[], int sx, int sy, int tx, int ty)
{
    int qh=0, qt=0;
    int queue[MAXM*MAXM];
    memset(visited, 0, sizeof(visited));
    queue[qt++] = idx(sx, sy);
    visited[sy][sx] = 1;
    
    while(qh<qt)
    {
        int x = queue[qh] % M, y = queue[qh++] / M;

        if(x == tx && y == ty) return visited[y][x] - 1;

        for(int i=0; i<4; i++)
        {
            int nx = x + dx[i], ny = y + dy[i];

            if(inb(nx, ny) && visited[ny][nx] == 0 && maps[ny][nx] != 'X')
            {
                visited[ny][nx] = visited[y][x] + 1;
                queue[qt++] = idx(nx, ny);
            }
        }
    }

    return -1;
}

// maps_len은 배열 maps의 길이입니다.
// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
int solution(const char* maps[], size_t maps_len) {
    int answer = 0;
    N = (int)maps_len;
    int sx, sy, rx, ry, ex, ey;

    for(size_t i=0; i<maps_len; ++i) // 시작, 레버, 종료 위치 찾기 
    {
        const char* r = maps[i];
        M = strlen(r);
        for(size_t j=0; j<M; j++)
        {
            if(r[j] == 'S')
            {
                sx = j; sy = i;
            }
            else if(r[j] == 'L')
            {
                rx = j; ry = i;
            }
            else if(r[j] == 'E')
            {
                ex = j; ey =i;
            }
        }
    }

    int l_len = bfs(maps, sx, sy, rx, ry);
    if(l_len == -1)
    {
        return -1;
    }
    int e_len = bfs(maps, rx,ry,ex,ey);

    if(e_len == -1)
    {
        return -1;
    }
    answer = l_len + e_len;
    return answer;
}