#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> tri(n+1, vector<int>(n+1, -1));
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<i+1; j++)
        {
            cin >> tri[i][j];
        }
    }

    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));

    dp[1][1] = tri[1][1];
    for(int i=2; i<=n; i++)
    {
        for(int j=1; j<i+1; j++)
        {
            if(j == 1)
            {
                dp[i][j] = dp[i-1][j] + tri[i][j];
            }
            else if(j==i)
            {
                dp[i][j] = dp[i-1][j-1] + tri[i][j];
            }
            else
            {
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-1]) + tri[i][j];
            }
        }
    }

    int answer = 0;
    for(int i=1; i<=n; i++)
    {
        answer = max(dp[n][i], answer);
    }
    cout << answer <<'\n';
    return 0;
}