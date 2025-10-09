#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin >> N;

    
    vector<long long> A(N);

    for(int i=0; i<N; ++i)
    {
        cin >> A[i];
    }

    vector<long long> tail;

    for(int i=0; i<N; ++i)
    {
        auto it = lower_bound(tail.begin(), tail.end(), A[i]);
        if(it == tail.end())
        {
            tail.push_back(A[i]);
        }
        else
        {
            *it = A[i];
        }
    }

    cout << tail.size() << '\n';
    return 0;
}