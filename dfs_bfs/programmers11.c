#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXT 500000
#define MAXX 100000000

bool endX[MAXX+1] = {false,};
bool startX[MAXX] = {false,};

int compare(const void *a, const void *b)
{
    const int *x1 = *(const int **)a;
    const int *x2 = *(const int **)b;
    return x1[1] - x2[1];
}

// targets_rows는 2차원 배열 targets의 행 길이, targets_cols는 2차원 배열 targets의 열 길이입니다.
int solution(int** targets, size_t targets_rows, size_t targets_cols) {
    int answer = 0;
    int maxX = 0; 

    
    qsort(targets,targets_rows,sizeof(int *),compare);

    for(size_t i=0; i<targets_rows; ++i)
    {
        int s = targets[i][0], e = targets[i][1];
        if(maxX <= s)
        {
            answer++;
            maxX = e;
        }
    }

    return answer;
}