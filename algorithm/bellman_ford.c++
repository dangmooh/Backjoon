/*
bellman ford

시간 복잡도 O(VE)
음수 간선 및 cycle 감지
*/

#include <vector>

using namespace std;

typedef struct {
  int u, v, w;
} Edge;

bool bellmanFord(int N, int src, vector<Edge>& edges, vector<long long>& dist)
{
  const long long INF = LLONG_MAX / 4;
  dist.assign(N+1, INF);
  dist[src] = 0;

  for(int i=1; i<N;++i)
  {
    bool updated = false;
    for(const auto& e : edges)
    {
      if(dist[e.u] != INF && dist[e.u] + e.w < dist[e.v])
      {
        dist[e.v] = dist[e.u] + e.w;
        updated = true;
      }
    }
    if(!updated) break;
  }


  for(const auto& e : edges)
  {
    if(dist[e.u] != INF && dist[e.u] + e.w < dist[e.v])
    {
      return false;
    }
  }
  return true;

}