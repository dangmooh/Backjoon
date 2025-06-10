#include <iostream>
#include <vector>

using namespace std;



int main()
{
    int N, K;

    cin >> N >> K;

    vector<pair<int,int>> jwel(N);
    vector<int> bag(K);

    for(int i=0; i<N; i++)
    {
        int M, V;
        cin >> M >> V;
        jwel[i] = {M, V};
    }

    for(int i=0; i<K; i++)
    {
        int C;
        cin >> C;
        bag[i] = C;
    }

    return 0;
}