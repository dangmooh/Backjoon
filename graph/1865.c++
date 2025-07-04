/*
N개의 지점이 있고 N개의 지점 사이에는 M개의 도로와 W개의 웜홀이 있다.

bellman forld : O(N x (M + W)) 
N-1에서 N 번째로 넘어갈 때 무한 cycle을 찾는다. 

*/

#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

struct Edge {
    int u;
    int v;
    int w;
}

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        cin >> N >> M >> W;

        vector<Edge> graph.reserve(2 * M + W);

        for (int i=0; i<M; i++)
        {
            int S, E, T;
            cin >> S >> E >>T;

            graph.push_back({S, E, T});
            graph.push_back({E, S, T});
        }

        for (int i=0; i<W; i++)
        {
            int S, E, T;
            cin >> S >> E >> T;

            graph.push_back({S, E, -T});
        }

        vector<ll> dist(N + 1, 0);

        for (int i=1; i <= N; ++i)
        {
            bool Cycle = false;

            for(const Edge &e : graph)
            {

                if(dist[e.u] + e.w < dist[e.v])
                {
                    dist[e.v] = dist[e.u] + e.w;
                    Cycle = true;
                }
            }

            if(i==N && Cycle)
            {
                cout << "YES\n";
                break;
            }

            if(!Cycle)
            {
                cout << "NO\n";
                break;
            }

        }


    }



    return 0;
}