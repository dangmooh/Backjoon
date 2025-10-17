#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int answer = 1000;
int people[10];
int N;
vector<int> adj[10];

void dfs(int idx, int group, int &visited)
{
    visited |= (1 << idx);
    for (int i : adj[idx])
    {
        if ((group >> i) & 1) // 그룹에 속해있고
        {
            if((visited >> i) & 1) continue; // 이미 방문했다면
            dfs(i, group, visited);
        }    
    }
    
    return;
}

bool check(int group)
{
    int visited = 0;

    for (int i = 0; i < 10; ++i)
    {
        if ((group >> i) & 1)
        {
            dfs(i, group, visited);
            break;
        }
    }

    return visited == group;
}

int sumP(int group)
{
    int ret = 0;

    for (int i = 0; i < N; ++i)
    {
        if ((group >> i) & 1)
        {
            ret += people[i];
        }
    }

    return ret;
}

int main()
{
    cin >> N;

    int totalP = 0;
    for (int i = 0; i < N; ++i)
    {
        int p;
        cin >> p;
        people[i] = p;
        totalP += p;
    }

    int cnt = 0;
    for (int i = 0; i < N; ++i)
    {
        int c; cin >> c;
        if (c == 0) cnt++;
        for (int j = 0; j < c; ++j)
        {
            int a; cin >> a;
            adj[i].push_back(a - 1);
        }
    }
    if (cnt > 2)
    {
        cout << -1 << "\n";
        return 0;
    }

    int full = (1 << N) - 1;
    for (int mask = 1; mask < full; ++mask) // 각 선거구는 적어도 하나씩 포함
    {
        int A = mask;
        int B = full ^ mask;

        if (!check(A)) continue; // group A가 연결되어 있지 않다면
        if (!check(B)) continue; // group B가 연결되어 있지 않다면

        int pA = sumP(A); // A 인구의 수
        int pB = totalP - pA;
        answer = min(answer, abs(pB - pA));
    }

    cout << ((answer == 1000) ? -1 : answer) << "\n";

    return 0;
}