#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_G 500

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

inline int turn(char c, char d)
{
    if (c=='L') return (d + 3) & 3;
    if (c == 'R') return (d+1) & 3;
    return d;
}

inline int idx3(int i, int j, int d, int M, int N) {return (i*M + j)*N + d;}

int com_int(const void *a, const void *b)
{
    return *(const int*)a - *(const int*)b;
}


int trace_cycle(const char* grid[], bool *visited, int M, int N, int si, int sj, int sd)
{
    int len = 0;
    int i=si, j=sj, d =sd;
    while(true)
    {
        int id = idx3(i, j, d, M, N);
        if(visited[id]) break;
        visited[id] = true;
        len++;

        char c = grid[i][j];
        d = turn(c, d);
        i = (i + dx[d] + N) % N;
        j = (j + dy[d] + M) % M;
    }
    return len;
}

// grid_len은 배열 grid의 길이입니다.
// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
int* solution(const char* grid[], size_t grid_len) {
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    int* answer = (int*)malloc(1);

    int N = (int)grid_len, M = strlen(grid[0]);

    bool *visited = calloc(M*N*4, sizeof(bool));
    int *res = malloc(sizeof(int) *M *N *4);
    int rc = 0;

    for()
    return answer;
}