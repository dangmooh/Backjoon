#include <iostream>
#include <vector>

using namespace std;


int main()
{
    int n, k;
    cin >> n >> k;

    vector<int> coin(n);
    vector<int> dp(k+1, 0);
    for(int i=0; i<n; ++i)
    {
        cin >> coin[i];
    }
    
    dp[0] = 1;
    for(auto cost : coin)
    {
        for(int i=cost; i<=k; ++i)
        {
            dp[i] += dp[i - cost];
        }
    }

    cout << dp[k] << "\n";

    return 0;
}