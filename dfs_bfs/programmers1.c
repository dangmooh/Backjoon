#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define MAXT 120
#define MAXN 40


int solution(int** info, size_t info_rows, size_t info_cols, int n, int m) {
    int answer = 0;
    static char dp[MAXT][MAXT], dp2[MAXT][MAXT];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    for (int i=0; i<info_rows; i++)
    {
        memset(dp2, 0, sizeof(dp2));
        int da = info[i][0], db = info[i][1];
        for (int a=0; a<n; i++)
        {
            for (int b=0; b<m; b++)
            {
                if(!dp[a][b]) continue;
                if(a + da < n)
                {
                    dp2[a + da][b] = 1;
                }
                if(b + db < m)
                {
                    dp2[a][b + db] = 1;
                }
            }
        }
        memcpy(dp, dp2, sizeof(dp));
    }


    int answer = -1;
    for (int a =0; a<n; a++)
    {
        int ok = 0;
        for (int b=0; b<m; b++)
        {
            if(dp[a][b]) { ok = 1; break; }
        }
        if (ok) { answer = a; break; }
    }

    printf("%d\n", answer);

    return answer;
}