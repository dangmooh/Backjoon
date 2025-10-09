/*
dfs로 모든 곳을 탐색한다. -> 시간초과 3^1000
dp로 풀어야 한다. 

dp[i][j]로 집 i를 색 j로 칠할 때의 최소 값

*/

#include <iostream>
#include <vector>


using namespace std;

constexpr int RED = 0, GREEN = 1, BLUE = 2;
constexpr int COLOR_COUNT = 3;

using Cost = vector<vector<int>>;

Cost readInput(int& N)
{
    Cost cost(N, vector<int>(3));
    for(int i=0; i<N; ++i)
    {
        for(int j=0; j<3; ++j)
        {
            cin >> cost[i][j];
        }
    }
    return cost;
}

int calculateMinCost(const Cost& cost, int& N)
{
    Cost dp(2, vector<int>(3));
    dp[0] = cost[0];

    for (int i = 1; i < N; ++i) {
        int cur = i % 2, prev = (i - 1) % 2;
        dp[cur][RED]   = cost[i][RED]   + min(dp[prev][GREEN], dp[prev][BLUE]);
        dp[cur][GREEN] = cost[i][GREEN] + min(dp[prev][RED],   dp[prev][BLUE]);
        dp[cur][BLUE]  = cost[i][BLUE]  + min(dp[prev][RED],   dp[prev][GREEN]);
    }

    int last = (N-1)%2;
    return (min({dp[last][RED], dp[last][GREEN], dp[last][BLUE]}));

}

int main()
{
    int N;
    cin >> N;

    Cost cost = readInput(N);
    int result = calculateMinCost(cost, N);
    cout << result << '\n';

    return 0;
}