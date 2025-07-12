#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10
#define MAXI 11

int info_global[MAXI];
int best_alloc[MAXN + 1], curr_alloc[MAXN+1];
int best_diff, total_arrows;

void dfs(int idx, int arrow_left)
{
    if(idx == 10)
    {
        curr_alloc[idx] = arrow_left;

        int ryan =0, apeach=0;
        for(int i=0; i<MAXI; i++)
        {
            if(info_global[i]==0 && curr_alloc[i] ==0) continue;
            if(curr_alloc[i]>info_global[i]) ryan += 10 - i;
            else apeach += 10 -i;
        }
        int diff = ryan - apeach;
        if(diff<=0) return;

        if(diff>best_diff)
        {
            best_diff = diff;
            memcpy(best_alloc, curr_alloc, sizeof(curr_alloc));
        }
        else if(diff==best_diff)
        {
            for(int i=10; i>=0; --i)
            {
                if(curr_alloc[i] > best_alloc[i])
                {
                    memcpy(best_alloc, curr_alloc, sizeof(curr_alloc));
                    break;
                }
                else if(curr_alloc[i] < best_alloc[i])
                {
                    break;
                }
            }
        }
        return;
    }
    int need = info_global[idx] + 1;
    if(arrow_left >= need)
    {
        curr_alloc[idx] = need;
        dfs(idx+1, arrow_left - need);
        curr_alloc[idx] = 0;
    }
    curr_alloc[idx] = 0;
    dfs(idx+1, arrow_left);
}

// info_len은 배열 info의 길이입니다.
int* solution(int n, int info[], size_t info_len) {
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.

    memcpy(info_global, info, sizeof(int)*MAXI);
    memset(best_alloc, 0, sizeof(best_alloc));
    memset(curr_alloc, 0, sizeof(curr_alloc));
    total_arrows = n;
    best_diff=0;
    dfs(0, total_arrows);
    int* answer = (int*)malloc(1);

    if(best_diff == 0)
    {
        answer[0] = -1;
    }
    else
    {
        return best_alloc;
    }

    return answer;
}