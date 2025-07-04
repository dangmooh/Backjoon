/*
그리디 + 우선순위 큐
O((N+K)log(N+K))
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

using ll = long long;

int main()
{
    int N, K;

    cin >> N >> K;

    priority_queue<int> pq;
    vector<int> bag(K);
    vector<pair<int,int>> jwel(N);
    for(int i=0; i<N; i++)
    {
        int M, V;
        cin >> M >> V;
        jwel[i] = {M, V};
    }


    for(int i=0; i<K; i++)
    {
        int C;
        cin >> C;
        bag[i] = C;
    }


    sort(bag.begin(), bag.end());
    sort(jwel.begin(), jwel.end(), [](auto &a, auto &b){return a.first < b.first;});

    ll answer = 0;
    int idx = 0;


    for(int weight : bag)
    {
        while(idx < N && jwel[idx].first <= weight)
        {
            pq.push(jwel[idx].second);
            ++idx;
        }

        if(!pq.empty())
        {
            answer += pq.top();
            pq.pop();
        }
    }

    cout << answer << "\n";
    return 0;
}