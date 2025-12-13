#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

constexpr int INF = numeric_limits<int>::max();

int solution(vector<vector<int>> info, int n, int m) {
    int answer =0;
    int N = (int)info.size();
    int totalB = 0, totalA = 0;
    for(auto &i : info) { totalB += i[1];  totalA += i[0]; }
    
    vector<vector<bool>> dp(totalB+1, vector<bool>(totalA+1, false));
    dp[0][0] = true;
    
    for(int i=0; i<N; ++i)
    {
        int A = info[i][0], B = info[i][1];
        for(int sb = totalB - B; sb >=0; --sb)
        {
            for(int sa = totalA - A; sa>=0; --sa)
            {
                if(dp[sb][sa]) dp[sb+B][sa+A] = true;
            }
        }
    }
    int maxA = INF;
    int minB = totalB - m + 1;
    if(minB < 0) minB = 0;
    
    for(int sb = minB; sb <= totalB; ++sb)
    {
        for(int sa = 0; sa <=totalA; ++sa)
        {
            if(dp[sb][sa] && sa <n)
            {
                maxA = min(maxA, sa);
            }
        }
    }
    
    if(maxA == INF) {answer =  -1;}
    else answer = maxA;
    return answer;
}
