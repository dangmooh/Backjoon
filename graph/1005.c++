#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int townTime[1001] = {0,};

int main()
{

    int T;
    cin >> T;

    while(T--)
    {
        int N, K;
        cin >> N >> K;


        vector<int> town[1001];
        vector<bool> visited(N, false);
        for(int i=1; i<=N; i++)
        {
            int t;
            cin >> t;
            townTime[i] = t;
        }

        while(K--)
        {
            int X, Y;
            cin >> X >> Y;

            town[Y].push_back(X);
        }
        int W;
        cin >> W;

        queue<int> q;
        q.push(W);
        visited[W] = true;

        int totalTime = 0;
        while(!q.empty())
        {
            int start = q.front();
            q.pop();

            int maxTime = 0;

            for(const int node : town[start])
            {
                maxTime = max(maxTime, townTime[node]);
                if(!visited[node])
                {
                    q.push(node);
                    visited[node] = true;
                }
            }

            totalTime += maxTime;

        }

    }

    return 0;
}