#include <iostream>
#include <vector>

using namespace std;

static const int MOD = 1000000000;

int dp[101][10][1<<10];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // 초기화: 길이 1, 자리 x (1~9), mask = 1<<x
    for(int x = 1; x <= 9; ++x){
        dp[1][x][1<<x] = 1;
    }

    for(int i=1; i<N; ++i)
    {
        for(int x=0; x<=9; ++x)
        {
            for(int mask=0; mask<(1<<10); ++mask)
            {
                int cur = dp[i][x][mask];
                if(!cur) continue;

                if(x>0)
                {
                    int m2 = mask | (1<<(x-1));
                    dp[i+1][x-1][m2] = (dp[i+1][x-1][m2] + cur) % MOD;
                }

                if(x<9)
                {
                    int m2 = mask | (1<<(x+1));
                    dp[i+1][x+1][m2] = (dp[i+1][x+1][m2] + cur) % MOD;
                }
            }
        }
    }

    int full = (1<<10) - 1;
    int answer = 0;
    for(int x=0; x<=9; ++x)
    {
        answer = (answer + dp[N][x][full] % MOD);
    }

    cout << answer << "\n";

    return 0;
}