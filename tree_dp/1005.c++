/*
위상 정렬과 DP
시간 복잡도 : O(N + K)
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) 
    {
        int N, K;
        cin >> N >> K;

        vector<int> D(N+1);
        for(int i=1; i<=N; i++)
        {
            cin >> D[i];
        }

        vector<vector<int>> adj(N+1);
        vector<int> indegree(N+1, 0);
        for(int i=0; i<K; i++)
        {
            int X, Y;
            cin >> X >> Y;
            adj[X].push_back(Y);
            indegree[Y]++;
        }

        int W;
        cin >> W;

        vector<int> dp(N+1, 0);

        queue<int> q;
        for (int i=1; i<=N; i++)
        {
            if(indegree[i] == 0)
            {
                dp[i] = D[i];
                q.push(i);
            }
        }

        while(!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int v : adj[u])
            {
                dp[v] = max(dp[v], dp[u] + D[v]);

                if(--indegree[v] == 0)
                {
                    q.push(v);
                }
            
            }
        }
        cout << dp[W] << "\n";
    }


    return 0;
}