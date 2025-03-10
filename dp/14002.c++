#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

int main()
{
    int N;
    cin >> N;

    vector<int> A(N);

    for (int i=0; i<N; i++)
    {
        cin >> A[i];     
    }

    vector<int> dp(N, 1);
    vector<int> prev(N, -1);
    int maxLength = 1, lastIndex = 0;
    for (int i=1; i<N; i++)
    {
        for (int j=0; j<i; j++)
        {
            if(A[j] < A[i] && dp[i] < dp[j] + 1)
            {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
        if (dp[i] > maxLength)
        {
            maxLength = dp[i];
            lastIndex = i;
        }
    }

    cout << maxLength << '\n';

    vector<int> list;
    for(int i=lastIndex; i != -1; i = prev[i])
    {
        list.push_back(A[i]);
    }
    reverse(list.begin(), list.end());

    for(int i =0; i<maxLength; i++)
    {
        cout << list[i] << " ";
    }
    cout << '\n';

    return 0;
}