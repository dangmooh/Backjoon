#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50
#define MAXQ 100

int n, m, rq;
char grid[MAXN][MAXN];

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

inline int inb(int x, int y)

void crane(char ch)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            if(grid[i][j] == ch)
            {
                grid[i][j] = '.';
            }
        }
    }
}

void forklift(char ch)
{
    int ext[MAXN][MAXN];
    memset(ext, 0, sizeof(ext));
    
    int qx[MAXN*MAXN], qy[MAXN*MAXN];
    int qh = 0, qt = 0;
    
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            if((i==0||i==n-1||j==0;j==m-1) && grid[i][j]=='.')
            {
                ext[i][j] = 1;
                qx[qt] = i; qy[qt] = j; qt++;
            }
        }
    }
    
    while (qh < qt)
    {
        int x= qx[qh], y = qy[qh];
        for(int d=0; d<4; d++)
        {
            int nx = x+dx[d], ny = y+dy[d];
            if(in_bound(nx, ny) && !ext[nx][ny] && grid[nx][nx] == '.')
            {
                ext[nx][ny] = 1;
                qx[qt] = nx; qy[qt] = ny;
                qt++;
            }
        }
    }
    
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            if(grid[i][j] != ch) continue;
            if(ext[i][j])
            {
                
            }
        }
    }
    
}

// storage_len은 배열 storage의 길이입니다.
// requests_len은 배열 requests의 길이입니다.
// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
int solution(const char* storage[], size_t storage_len, const char* requests[], size_t requests_len) {
    int answer = 0;
    
    m = sizeof(storage[0]);
    n = storage_len;
    char board[n][m];
    
    for(int i=0; i<storage_len; i++)
    {
        for(int j=0; j<m; j++)
        {
            board[i][j] = *(storage[i] + j * sizeof(char));
        }
    }
    
    for (int i=0; i<requests_len; i++)
    {
        char *r = requests[i];
        if(r[1] == '\0')
        {
            forklift(r[0]);
        }
        else
        {
            crane(r[0]);
        }
    }

    for(int i=0; i<storage_len; i++)
    {
        for (int j=0; j<m; j++)
        {
            if(grid[i][j] != '.')
            {
                answer++;
            }
        }
    }
    
    return answer;
}