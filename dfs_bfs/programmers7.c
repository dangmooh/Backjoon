#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXE 1000000
#define MAXN 1000001

int inedge[MAXN] = {0,}, outedge[MAXN] = {0,};
int inedge2[MAXN] = {0,}, outedge[MAXN] = {0,};
int ec, maxV;

int to[MAXE*2], nxt[MAXE*2], head[MAXN];
int queue[MAXE*2];

int find_created(const int** edges, size_t edges_rows)
{
    maxV = 0;
    for(int i=0; i< edges_rows;++i)
    {
        int u = edges[i][0], v = edges[i][1];
        if(u>maxV) maxV = u;
        if(v>maxV) maxV = v;

        inedge[v]++; outedge[u]++;
    }

    for(int i=1; i<=maxV; i++)
    {
        if(inedge[i] == 0 && outedge[i] > 1) return i;
    }
    return -1;

}

void make_graph(const int** edges, size_t edges_rows, int created)
{
    ec = 0;
    memset(head, -1, sizeof(head));
    for(int i=0; i<edges_rows; ++i)
    {
        int u = edges[i][0], v = edges[i][1];
        if(u == created || v == created) continue;
        to[ec] = v; nxt[ec] = head[u]; head[u] = ec++; 
        to[ec] = u; nxt[ec] = head[v]; head[v] = ec++;
    }

}


// edges_rows는 2차원 배열 edges의 행 길이, edges_cols는 2차원 배열 edges의 열 길이입니다.
int* solution(int** edges, size_t edges_rows, size_t edges_cols) {
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    int* answer = (int*)malloc(1);

    int created = find_created(edges, edges_rows);
    make_graph(edges, edges_rows, created);


    return answer;
}