/*
무제한 배낭 문제 이므로 앞에서부터 순회한다.
시간 복잡도 : O(N×M)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{
    int C, N;
    cin >> C >> N;

    vector<pair<int,int>> town(N);
    int max_cust = 0;
    for(int i=0; i<N; i++)
    {
        int cost, cust;
        cin >> cost >> cust;
        town[i] = {cost, cust};
        max_cust = max(max_cust, cust);
    }

    const int INF = 1e9;
    int M = C + max_cust;
    vector<int> dp(M+1, INF);
    dp[0] = 0;

    for(auto [cost, cust] : town)
    {
        for(int v= cust; v<= M; ++v)
        {
            if(dp[v - cust] + cost < dp[v])
            {
                dp[v] = dp[v - cust] + cost;
            }
        }
    }

    int answer = INF;
    for (int i=C; i<=M; ++i)
    {
        answer = min(answer, dp[i]);
    }

    cout << answer << "\n";

    return 0;
}