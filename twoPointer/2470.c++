
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{
    int N, S;
    cin  >> N >> S;

    vector<int> pall(N);

    for (int i=0; i< N; i++)
    {
        cin >> pall[i];
    }


    int left = 0, right = 0, sum = 0;
    int count = numeric_limits<int>::max();

    while(right < N)
    {
        sum += pall[right++];

        while (sum >= S)
        {
            count = min(count, right - left);
            sum -= pall[left++];
        }

    }

    cout << (count == numeric_limits<int>::max() ? 0 : count) << "\n";

    return 0;
}