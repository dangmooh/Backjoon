/*
부분 수열
dp
dp[i][j] = A[0~i-1]와 B[0~j-1]의 LCS 길이

if(A[i-1] == B[j-1])
{
    dp[i][j] = dp[i-1][j-1] + 1
} 
else
{
    dp[i][j] = max(dp[i-1][j], dp[i][j-1])
}

*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    string A, B;

    cin >> A >> B;

    int N = A.size(), M = B.size();
    vector<vector<int>> dp(N+1, vector<int>(M+1, 0));
    for(int i=1; i<=N; ++i)
    {
        for(int j=1; j<=M; ++j)
        {
            if(A[i-1] == B[j-1])
            {
                dp[i][j] = dp[i-1][j-1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    cout << dp[N][M] << '\n';
    return 0;
}