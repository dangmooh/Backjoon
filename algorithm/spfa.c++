/*

SPFA (Shortest Path Faster Algorithm)

bellman ford의 queue 기반 최적화
음수 가중치가 있는 최단거리 계산 및 음수 cycle 감지 가능
갱신된 정점만 재방문한다.

시간 복잡도 평균 O(E) 최악 O(VE) <- bellman ford

*/


#include <vector>
#include <queue>

using namespace std;

using pii = pair<int,int>;
using Graph = vector<vector<pii>>;

bool spfa(int N, int src, const Graph& graph)
{
  vector<int> dist(N+1, 0), cnt(N+1, 0);
  vector<bool> inQueue(N+1, false);
  queue<int> q;

  for(int i=1; i<=N; ++i)
  {
    q.emplace(i);
    inQueue[i] = true;
  }

  while(!q.empty())
  {
    int u = q.front(); q.pop();
    inQueue[u] = false;

    for(const auto& [v, w] : graph[u])
    {
      if(dist[u] + w < dist[v])
      {
        dist[v] = dist[u] + w;
        cnt[v]++;
        if(cnt[v] >= N)
        {
          return false;
        }

        if(!inQueue[v])
        {
          inQueue[v] = true;
          q.push(v);
        }
      }
    }
  }
  return false;
}