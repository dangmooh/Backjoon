#include <iostream>
#include <vector>


using namespace std;


int main()
{

    int N, K;

    vector<pair<int,int>> pack(N);

    for(int i=0; i<N; ++i)
    {
        int W, V;
        pack.emplace_back(W, V);
    }

    vector<vector<int>> dp(N+1, vector<int>(K+1, 0));
    for(int i=1; i<=N; ++i)
    {
        for(int w=0; w<=K, ++w)
        {
            dp[i][w] = dp[i-1][w]
        }
    }

    return 0;
}