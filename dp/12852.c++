/*

우선 순위 순으로 설정을 해준다.
가장 빠른 경로를 선택해야 하므로 
우선 순위는  / 3 ->  / 2 -> - 1
up stream 방식을 이용해서 축적해 나간다.

*/

#include <iostream>
#include <vector>


using namespace std;


int main()
{

    int N;
    cin >> N;

    vector<int> dp(N+1, 0);
    vector<int> path(N+1, 0);

    for (int i=2; i<=N; i++)
    {
        dp[i] = dp[i-1] + 1;
        path[i] = i - 1;

        if (i%2 == 0 && dp[i] > dp[i/2] + 1)
        {
            dp[i] = dp[i/2] + 1;
            path[i] = i /2;
        }
        if (i%3 == 0 && dp[i] > dp[i/3] + 1)
        {
            dp[i] = dp[i/3] + 1;
            path[i] = i /3;
        }
    }

    cout << dp[N] << '\n';

    int cur =N;
    while (cur > 0)
    {
        cout << cur << " ";
        cur = path[cur];
    }

    cout << '\n';

    return 0;
}