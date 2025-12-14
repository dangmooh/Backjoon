/*
2025.12.14

LIS
*/



#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


int main()
{

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;

    vector<int> A(N);

    for(int i=0; i<N; ++i)
    {
        cin >> A[i];
    }

    // dp1[i] = maximum sum of increasing subsequence ending at i
    vector<int> dp1(N);
    for (int i = 0; i < N; ++i) dp1[i] = A[i];

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (A[i] > A[j])
            {
                dp1[i] = max(dp1[i], dp1[j] + A[i]);
            }
        }
    }

    int answer = 0;
    for(int i=0; i<N; ++i)
    {
        answer = (answer < dp1[i]) ? dp1[i] : answer;
    }
    
    cout << answer << "\n";

    return 0;
}