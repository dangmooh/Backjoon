#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int N;
    cin >> N;

    int full = (1 << N) -1;
    vector<pair<int,int>> favor(N);

    for(int i=0; i<N; ++i)
    {
        cin >> favor[i].first >> favor[i].second;
    }

    int answer = 1e9;
    for(int mask = 1; mask<=full; ++mask)
    {
        int s =1, c=0;
        for(int i=0; i<N; ++i)
        {
            if((mask >> i) & 1)
            {
                s *= favor[i].first;
                c += favor[i].second;
            }
        }

        int diff = abs(s - c);
        if(answer > diff)
        {
            answer = diff;
        }
    }

    cout << answer << "\n";

    return 0;
}