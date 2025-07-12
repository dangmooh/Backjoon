#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_X 100
#define MAX_M 100
#define MAX_PATH 20000

typedef struct {
    int r, c;
} Pos;

static int cmp_pos(const void *A, const void *B)
{
    const Pos *a = A, *b = B;
    if(a->r != b->r) return a->r - b->r;
    return a->c - b->c;
}

// points_rows는 2차원 배열 points의 행 길이, points_cols는 2차원 배열 points의 열 길이입니다.
// routes_rows는 2차원 배열 routes의 행 길이, routes_cols는 2차원 배열 routes의 열 길이입니다.
int solution(int** points, size_t points_rows, size_t points_cols, int** routes, size_t routes_rows, size_t routes_cols) {
    int answer = 0;

    size_t n_points = points_rows;
    size_t n_robots = routes_rows;
    size_t m = routes_cols;

    size_t max_path = m * 200 + 5;
    Pos **path = malloc(n_robots * sizeof(Pos*));
    int *path_len = malloc(n_robots*sizeof(int));
    for(size_t i=0; i<n_robots; ++i)
    {
        path[i] = malloc(max_path * sizeof(Pos));
        path_len[i] = 0;
    }

    int maxT = 0;
    for (size_t i=0; i<n_robots; ++i)
    {
        int idx0 = routes[i][0] - 1;
        Pos cur = {points[idx0][0], points[idx0][1]};
        path[i][path_len[i]++] = cur;

        for(size_t j=1; j<m; ++j)
        {
            int dst_idx = routes[i][j] - 1;
            Pos dst = {points[dst_idx][0], points[dst_idx][1]};

            while(cur.r != dst.r)
            {
                cur.r += (dst.r > cur.r ? 1 : -1);
                path[i][path_len[i]++] = cur;
            }

            while(cur.c != dst.c)
            {
                cur.c += (dst.c > cur.c ? 1 : -1);
                path[i][path_len[i]++] = cur;
            }
        }
        if(path_len[i] > maxT) maxT = path_len[i];
    }

    Pos *positions = malloc(n_robots * sizeof(Pos));
    int total_coll = 0;

    for(int t=0; t<maxT; ++t)
    {
        int cnt = 0;
        for(size_t i=0; i<n_robots; ++i)
        {
            if(t < path_len[i])
            {
                positions[cnt++] = path[i][t];
            }
        }
        if(cnt <2) continue;

        qsort(positions, cnt, sizeof(Pos), cmp_pos);

        for(int k=1; k<cnt; ++k)
        {
            if(positions[k].r == positions[k-1].r && positions[k].c == positions[k-1].c
            && (k==1||positions[k-1].r != positions[k-2].r||positions[k-1].c != positions[k-2].c))
            {
                total_coll++;
            }
        }
    }

    for(size_t i=0; i<n_robots; ++i)
    {
        free(path[i]);
    }

    free(path);
    free(path_len);
    free(positions);

    return total_coll;
}