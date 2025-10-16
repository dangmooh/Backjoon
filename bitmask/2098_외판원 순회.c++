#include <iostream>
#include <vector>
#include <limits>

using namespace std;

constexpr int INF = numeric_limits<int>::max();


int main()
{
    int N;
    cin >> N;

    int full = (1<<N) -1;

    vector<vector<int>> dp(1<<N, vector<int>(N, INF));
    vector<vector<int>> W(N, vector<int>(N, 0));

    for(int i=0; i<N; ++i)
    {
        for(int j=0; j<N; ++j)
        {
            cin >> W[i][j];
        }
    }

    int start = 0;
    for(int mask=0; mask<=full; ++mask)
    {
        for(int u=0; u<N; ++u)
        {
            if(!(mask & (1<<u))) continue; // 현재 상태에 시작 노드가 포함되지 않은 경우
            if(dp[mask][u] == INF) continue; //현재 상태에서 시작 노드에 도착한 적이 없는 경우

            for(int v=0; v<N; ++v)
            {
                if(W[u][v] == 0) continue; // 시작노드에서 도착노드로 길이 없는 경우
                if(mask & (1<<v)) continue; // 현재 상태에서 도착 노드가 포함되어 있는 경우

                int nmask = mask | (1<<v);
                int total = W[u][v] + dp[mask][u];
                if(total < dp[nmask][v])
                {
                    dp[nmask][v] = total;
                }
            }
        }
    }

    int answer = INF;

    for(int u=0; u<N; ++u)
    {
        if(u == start) continue; 
        if(dp[full][u] == INF) continue; // 마지막노드로 도착하지 못한경우
        if(W[u][start] == 0) continue; // 마지막 노드에서 처음 노드로 돌아오지 못한경우
        int total = dp[full][u] + W[u][start];
        if(total < answer)
        {
            answer = total;
        }
    }
    cout << answer << "\n";

    return 0;
}