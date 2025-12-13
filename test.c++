#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_P 100
#define MAX_R 100

int robot_x[MAX_R][MAX_P*MAX_P*2];
int robot_y[MAX_R][MAX_P*MAX_P*2];
int robot_t[MAX_R] = {0,};
int num, maxT, total_coll;

typedef struct {
    int x, y;
} Pos;

int comp_idx(const void *A, const void *B)
{
    const Pos *a = (Pos *)A, *b = (Pos *)B;
    if(a->y != b->y) return a->y - b->y;
    return a->x - b->x;
}

void find_route(int** points, size_t points_rows, int** routes, size_t routes_rows, size_t routes_cols)
{
    maxT = 0;
    for(int r=0; r<routes_rows; ++r)
    {
        int time = 0;
        int sp = routes[r][0] - 1;
        int sx = points[sp][1], sy = points[sp][0];
        robot_x[r][time] = sx; robot_y[r][time++] = sy;

        for(int i=1; i<routes_cols; ++i)
        {
            int ep = routes[r][i] - 1; 
            int ex = points[ep][1], ey = points[ep][0];
            while(sy != ey)
            {
                sy += sy > ey ? -1 : 1;
                robot_x[r][time] = sx; robot_y[r][time++] = sy;
            }
            
            while(sx != ex)
            {
                sx += sx > ex ? -1 : 1;
                robot_x[r][time] = sx; robot_y[r][time++] = sy;
            }
        }
        robot_t[r] = time;
        if (time > maxT) maxT = time;
    }
}

void count_coll()
{
    total_coll = 0;
    Pos buffer[num];

    for(int t=0; t<=maxT; ++t)
    {
        int qh = 0, qt = 0;
        for(int r=0; r<num; ++r)
        {
            if(robot_t[r] > t)
            {
                buffer[qt].x = robot_x[r][t];
                buffer[qt++].y = robot_y[r][t];
            }
        }
        
        if(qt < 2) continue;
        
        qsort(buffer, qt, sizeof(Pos), comp_idx);
        
        while(qh < qt)
        {
            int j = qh + 1;
            while(j < qt && buffer[j].x == buffer[qh].x && buffer[j].y == buffer[qh].y)
            {
                ++j;
            }
            
            if(j-qh >=2) total_coll++;
            qh = j;
        }
    }
}

// points_rows는 2차원 배열 points의 행 길이, points_cols는 2차원 배열 points의 열 길이입니다.
// routes_rows는 2차원 배열 routes의 행 길이, routes_cols는 2차원 배열 routes의 열 길이입니다.
int solution(int** points, size_t points_rows, size_t points_cols, int** routes, size_t routes_rows, size_t routes_cols) {
    int answer = 0;
    num = (int)routes_rows; 
    
    find_route(points, points_rows, routes, routes_rows, routes_cols);
    
    count_coll();
    
    return total_coll;
}