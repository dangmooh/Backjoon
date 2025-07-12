#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXG 500
int gold[MAXG*MAXG];
int gridy[MAXG * MAXG];
int visited[MAXG][MAXG] = {0,};
bool oil_col[MAXG * MAXG][MAXG] = {false,};

int queue[MAXG * MAXG];
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};
int m, n;

inline int idx(int y, int x) {return y*n + x;} 
inline bool inb(int y, int x) {return x>=0&&x<n&&y>=0&&y<m;}

// land_rows는 2차원 배열 land의 행 길이, land_cols는 2차원 배열 land의 열 길이입니다.
int solution(int** land, size_t land_rows, size_t land_cols) {
    int answer = 0;
    m = land_rows;
    n = land_cols;

    /*1. 각 석유 매장량을 배열에 번호를 부여해 저장한다. <- bfs 최대 500 * 500 */
    int ec = 1;
    for(size_t i=0; i<land_rows; ++i)
    {
        for(size_t j=0; j<land_cols; ++j)
        {
            if(visited[i][j] || land[i][j] == 0) continue;
            int total = 1;
            int qt=0, qh=0;
            queue[qt++] = idx(i, j);
            visited[i][j] = ec;
            oil_col[ec][j] = true;

            while(qt>qh)
            {
                int x = queue[qh] % n, y = queue[qh++] / n;

                for(int i=0; i<4; i++)
                {
                    int nx = x + dx[i], ny = y + dy[i];
                    if(inb(ny, nx) && visited[ny][nx] == 0 && land[ny][nx])
                    {
                        queue[qt++] = idx(ny, nx);
                        visited[ny][nx] = ec;
                        oil_col[ec][nx] = true;
                        total++;
                    }
                }
            }
            gold[ec++] = total;
        }
    }
    /*2. 1부터 500까지 완탐으로 몇번 석유들을 가지고 있는지 저장한다. <-500*/
    int col_sum[MAXG]={0,};
    for(int id=1; id<ec; id++)
    {
        for(int j=0; j<land_cols; j++)
        {
            if(oil_col[i][j])
            {
                col_sum[j] += gold[id];
            }
        }
    }

    int best = 0;
    for(int i = 0; i < n; i++) 
    {
        if(best < col_sum[i]) 
        {
            best = col_sum[i];
        }
    }

    return best;
}