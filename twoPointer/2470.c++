
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{
    int N;
    cin  >> N;


    vector<long long> lquid(N);

    for(int i =0; i<N;i++)
    {
        cin >> lquid[i];
    }

    sort(lquid.begin(), lquid.end());

    int left = 0, right = N-1;
    int result = 2e9;
    int ans1, ans2;

    while(left < right)
    {
        int sum = lquid[left] + lquid[right];

        if(abs(sum) < result)
        {
            result = abs(sum);
            ans1 = lquid[left];
            ans2 = lquid[right];        
        } else if(sum > 0)
        {
            right--;
        } else {
            left++;
        }
    }

    cout << ans1 << " " << ans2 << '\n';

    return 0;
}