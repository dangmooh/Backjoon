#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define MAXN 30

int N, m;

static unsigned int* build_query_masks(int **q, size_t q_rows)
{
    unsigned int *mask_q  = (unsigned int *)malloc(q_rows * sizeof(unsigned int));
    if(!mask_q) exit(1);
    for (size_t i=0; i<q_rows; i++)
    {
        unsigned int m =0;
        for(int j=0; j<5; j++)
        {
            int x = q[i][j];
            m |= 1u << (x-1);
        }
        mask_q[i] = m;
    }

    return mask_q;
}

static int is_valid_code(unsigned int mask_code, unsigned int *mask_q, int ans[], size_t m)
{
    for(size_t i=0; i<m; i++)
    {
        int cnt = __builtin_popcount(mask_code & mask_q[i]);
        if (cnt != ans[i]) return 0;
    }
    return 1;
}

static int count_possible_codes(int n,
                                unsigned int *mask_q, int ans[], size_t m)
{
    int total = 0;
    for(int a=1; a<= n-4; a++)
    {
        for(int b=a+1; b<=n-3; b++)
        {
            for(int c=b+1; c<=n-2; c++)
            {
                for(int d=c+1; d<=n-1; d++)
                {
                    for(int e=d+1; e<=n; e++)
                    {
                        unsigned int code_mask =
                        (1u<<(a-1)) | (1u <<(b-1)) |
                        (1u<<(c-1)) | (1u<<(d-1)) |
                        (1u<<(e-1));
                        if(is_valid_code(code_mask, mask_q, ans, m)) total++;
                    }
                }
            }
        }
    }
    return total;
}

// q_rows는 2차원 배열 q의 행 길이, q_cols는 2차원 배열 q의 열 길이입니다.
// ans_len은 배열 ans의 길이입니다.
int solution(int n, int** q, size_t q_rows, size_t q_cols, int ans[], size_t ans_len) {
    int answer = 0;

    unsigned int *mask_q = build_query_masks(q, q_rows);

    int result = count_possible_codes(n, mask_q, ans, ans_len);

    free(mask_q);
    
    return result;
}