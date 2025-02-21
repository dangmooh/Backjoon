/*
특별한 조건이 있는 경우의 최단 거리 찾기이다.
순간이동 하는 경우를 우선으로 처리해 주어야하며 
왜인지 모르겠지만 -1 , +1 순서로 처리를 해주어야한다.
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    int N, K;
    cin >> N >> K;

    deque<pair<int,int>> dq;
    dq.push_back({N,0});

    vector<bool> visited(100001, false);
    visited[N] = true;

    while(!dq.empty())
    {
        int cur = dq.front().first;
        int num = dq.front().second;
        dq.pop_front();

        if(cur == K)
        {
            cout << num << '\n';
            return 0; 
        }


        if(cur*2<= 100000 && !visited[cur * 2])
        {
            dq.push_front({cur * 2, num});
            visited[cur * 2] = true;
        }
        if(cur-1>=0 && !visited[cur-1])
        {
            dq.push_back({cur-1, num+1});
            visited[cur-1] = true;
        }
        
        if(cur + 1 <= 100000 && !visited[cur+1])
        {
            dq.push_back({cur+1, num + 1});
            visited[cur+1] = true;
        }
        
    }


    return 0;
}