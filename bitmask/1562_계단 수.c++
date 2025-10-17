#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long dp[101][10][1<<10];

int main()
{
    int  N;

    for(int i=1; i<=9; ++i)
    {
        dp[1][i][1<<i] = 1;
    }

    for(int len =2; len<=N; ++len)
    {
        for(int last = 0; last <=9; ++last)
        {
            for(int mask=0; mask<(1<<10); ++mask)
            {
                if(last>0)
                {
                    
                }
            }
        }
    }

    return 0;
}