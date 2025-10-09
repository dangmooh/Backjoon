/*
dp

안 취할 것인가
위를 취할 것인가
아래를 취할 것인가

취했을때 안취했을때 각각의 최대값을 계산해야 하나?


*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{
    int T;
    cin >> T;

    while(T--)
    {
        int n;
        cin >> n;

        vector<vector<int>> stickers(2, vector<int>(n+1));
        for(int i=0; i<2; ++i)
        {
            for(int j=1; j<=n; ++j)
            {
                cin >> stickers[i][j];
            }
        }

        vector<vector<int>> dp(n+1,vector<int>(3,0));

        for(int i=1; i<=n; ++i)
        {
            dp[i][0] = max({dp[i-1][0], dp[i-1][1], dp[i-1][2]});
            dp[i][1] = max(dp[i-1][0], dp[i-1][2]) + stickers[0][i];
            dp[i][2] = max(dp[i-1][0], dp[i-1][1]) + stickers[1][i];
        }
        cout << max({dp[n][0], dp[n][1], dp[n][2]}) << '\n';
    }
    return 0;
}