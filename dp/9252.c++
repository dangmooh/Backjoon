/*


*/
#include <iostream>
#include <vector>


using namespace std;

int main()
{
    string s1, s2;
    cin >> s1 >> s2;

    int n = s1.size(), m = s2.size();
    vector<vector<char>> dp(s1.size() + 1, vector<char>(s2.size() + 1, 0));

    for(int i=1; i<=s1.size(); i++)
    {
        for(int j=1; j<=s2.size(); j++)
        {
            if(s1[i-1] == s2[j-1])
            {
                dp[i][j] = dp[i-1][j-1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
            }
        }
    }


    cout << dp[n][m] << "\n";

    string LCS = "";
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s1[j - 1]) {
            LCS = s1[i - 1] + LCS;
            i--; j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    if (!LCS.empty()) cout << LCS << "\n";

    return 0;
}