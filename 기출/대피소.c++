#include <iostream>
#include <vector>
#include <set>
#include <algorithm>


using namespace std;

using Pii = pair<int, int>;
int N, K;

vector<Pii> graph;
set<int> dist;

void find_dist()
{
    Pii start = graph[0];
    for(int i=1; i<N; ++i)
    {
        int d = abs(start.first - graph[i].first) + abs(start.second - graph[i].second);
        dist.insert(d);
    }

}

bool canCover(int mid, int k)
{
    auto start = dist.begin();
    while(k--)
    {
        if(start == dist.end()) break;
        int nxt = *start + mid;
        start = dist.upper_bound(nxt);
    }

    return start == dist.end();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K;

    while (N--)
    {
        int x, y;
        cin >> x >> y;
        graph.push_back({ y,x });
    }

    find_dist();
    int l = *dist.rbegin() - *dist.begin();
    int s = 0;
    int mid = 0;

    while(s < l)
    {
        mid = (l + s) >> 1;
        if(canCover(mid, K))
        {
            l = mid;
        }
        else
        {
            s = mid + 1;
        }
    }


    cout << mid << "\n";

    return 0;
}