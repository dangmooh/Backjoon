#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstdlib> // llabs


using namespace std;



int main()
{
    int N; cin >> N;

    vector<long long> pall;
    for(int i=0; i<N; ++i)
    {
        cin >> pall[i];
    }

    int low = 0, hi = N-1;
    long long ansL = pall[low], ansR = pall[hi];
    long long bstAbs = numeric_limits<long long>::max();
    while(low < hi)
    {
        long long mid = pall[low] + pall[hi];

        if(llabs(mid) < bstAbs)
        {
            bstAbs = llabs(mid);
            ansL = pall[low];
            ansR = pall[hi];
            if(bstAbs == 0) break;
        }
        if(mid < 0 )
        {
            low++;
        }
        else
        {
            hi--;
        }
    }

    cout << ansL << ' ' << ansR << '\n';

    return 0;
}