#include <iostream>
#include <vector>
#include <queue>

using namespace std;
vector<int> visited(100001, -1);
vector<int> result;
void printTrace(int start)
{
    int idx = visited[start];
    result.push_back(start);

    if(idx == 0) 
    {
        return;
    }
    else if(idx == 1)
    {
        printTrace(start + 1);
    }
    else if(idx == 2)
    {
        printTrace(start - 1);
    }
    else if(idx == 3)
    {
        printTrace(start / 2);
    }

}

int main()
{
    int N, K;

    cin >> N >> K;

    queue<pair<int,int>> q;
    q.push({N, 0});
    visited[N] = 0;

    while(!q.empty())
    {
        int cur = q.front().first;
        int curNum = q.front().second;
        q.pop();

        if(cur == K)
        {
            cout << curNum << '\n';
            printTrace(K);
            break;
        }

        int nextX3 = cur * 2;
        if(nextX3 <= 100000 && visited[nextX3] == -1)
        {
            q.push({nextX3, curNum + 1});
            visited[nextX3] = 3;
        }

        int nextX2 = cur + 1;
        if(nextX2 <= 100000 && visited[nextX2] == -1)
        {
            q.push({nextX2, curNum + 1});
            visited[nextX2] = 2;
        }

        int nextX1 = cur - 1;
        if(nextX3 >= 0 && visited[nextX1] == -1)
        {
            q.push({nextX1, curNum + 1});
            visited[nextX1] = 1;
        }
    }

    for(int i=result.size()-1; i>=0; i--)
    {
        cout << result[i] << " ";
    }
    cout << '\n';

    return 0;
}