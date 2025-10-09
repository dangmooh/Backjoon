#include <iostream>
#include <vector>


using namespace std;



int main()
{
    ios::sync_with_stdio(false); // C와 C++ stream 동기화 해제 (입출력 속도 ↑)
    cin.tie(0); // cin과 cout의 tie 해제
    int N, M; cin >> N >> M;

    vector<vector<int>> map(N + 1, vector<int>(N + 1, 0));
    vector<vector<int>> dp(N + 1, vector<int>(N + 1, 0));

    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            cin >> map[i][j];
            dp[i][j] = map[i][j] + dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
        }
    }


    while (M--)
    {
        int x1, y1, x2, y2; cin >> y1 >> x1 >> y2 >> x2;

        int answer = 0;
        answer = dp[y2][x2] - dp[y2][x1 - 1] - dp[y1 - 1][x2] + dp[y1 - 1][x1 - 1];
        cout << answer << '\n';
    }

    return 0;
}