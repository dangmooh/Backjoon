#include <iostream>
#include <vector>

using namespace std;


int main()
{
    int N;
    cin >>N;

    vector<int> s(N);
    for(int i=0; i<N; ++i)
    {
        cin >> s[i];
    }

    vector<int> poll;
    for(int i=0; i<N; ++i)
    {
        auto it = lower_bound(poll.begin(), poll.end(), s[i]);
        if(it == poll.end())
        {
            poll.push_back(s[i]);
        }
        else
        {
            *it = s[i];
        }
    }

    cout << poll.size() << '\n';

    return 0;
}