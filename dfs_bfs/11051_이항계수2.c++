#include <iostream>
#include <vector>


using namespace std;


int main()
{

    int N, K;
    cin >> N >> K;
    int dp[1001][1001] = {0,};
    for(int i=0; i<N+1; ++i)
    {
        dp[0][0] = 1; dp[N][N] = 1;
        for(int j=1; j<i; ++j)
        {
            dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
        }
    }

    cout << dp[N][K] % 10007 << '\n';


    return 0;
}