#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#define MAXN 50

int q_i[26][MAXN * MAXN];
int q_j[26][MAXN*MAXN];
int q_cnt[26];
char grid[MAXN][MAXN];

int n, m;

int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

inline int idx(int x, int y) {return y*m + x;} 
inline int inb(int x, int y) {return x>=0 && x<m && y>=0 && y<n;}

void crane(int target)
{
    for(int i=0; i<q_cnt[target]; i++)
    {
        int x = q_j[target][i];
        int y = q_i[target][i];
        grid[y][x] = '.';
    }
    q_cnt[target] = 0;

}

void forklift(int target)
{
    char ext[MAXN*MAXN];
    int q[MAXN*MAXN];
    int qh=0,qt=0;

    memset(ext, 0, sizeof(ext));

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            if((i==0||i==n-1||j==0||j==m-1)&&grid[i][j] == '.')
            {
                int id =idx(j, i);
                ext[id] = 1;
                q[qt++] = id;
            
            }
        }
    }

    while(qh<qt)
    {
        int id = q[qh++], y = id/m, x=id%m;
        
        for(int d=0; d<4; d++)
        {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if(inb(nx, ny))
            {
                int nid = idx(nx,ny);
                if(!ext[nid] && grid[ny][nx] == '.')
                {
                    ext[nid] = 1;
                    q[qt++] = nid;
                }                
            }

        }
    }

    int write = 0;

    for(int i=0; i<q_cnt[target]; i++)    
    {
        int x = q_j[target][i];
        int y = q_i[target][i];
        int ok = (x==0||x==m-1||y==0||y==n-1);
        if(!ok)
        {
            for(int d=0; d<4; d++)
            {
                int tn_x = x + dx[d];
                int tn_y = y + dy[d];

                if(inb(tn_x,tn_y) && ext[idx(tn_x, tn_y)])
                {
                    ok = 1;
                    break;
                }
            }
        }
        if(ok)
        {
            grid[y][x] = '.';
        }
        else
        {
            q_i[target][write] = y;
            q_j[target][write] = x;
            write++;
        }
    }

    q_cnt[target] = write;
}

// storage_len은 배열 storage의 길이입니다.
// requests_len은 배열 requests의 길이입니다.
// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
int solution(const char* storage[], size_t storage_len, const char* requests[], size_t requests_len) {
    int answer = 0;

    n = storage_len;
    m = strlen(storage[0]);
    memset(q_cnt, 0, sizeof(q_cnt));
 
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            grid[i][j] = storage[i][j];
            int num = storage[i][j] - 'A';
            int k = q_cnt[num]++;
            q_i[num][k] = i;
            q_j[num][k] = j;
        }
    }

    for(int i=0; i<requests_len; i++)
    {
        char *r = requests[i];
        int target = r[0] - 'A';
        if(r[1] == '\0')
        {
            forklift(target);
        }
        else{
            crane(target);
        }
    }

    for(int i=0; i<26; i++)
    {
        answer += q_cnt[i];
    }


    return answer;
}


