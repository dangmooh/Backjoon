<<<<<<< HEAD
/*
기존의 14002번은 수열의 크기가 1000이어서 N * N이 가능했지만
백만이라 N * N은 안된다. N logN 정도로 줄여야한다.
N logN -> 이분탐색
*/
#include <iostream>
#include <vector>


using namespace std;


int main()
{
    int N;
    cin >> N;

    vector<int> list(N);

    for(int i=0; i <N; i++)
    {
        cin >> list[i];
    }

    vector<int> dp(N);
    for(int i=1; i< N; i++)
    {
        for(int j=0; j<i; j++)
        {

        }
    }

=======
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{

    int N;
    cin >> N;
    vector<int> lis(N);

    for(int i=0; i<N; i++)
    {
        cin >> lis[i];
    }

    vector<int> list;
    vector<int> trace(N, -1);
    vector<int> idx(N,-1);
    for(int i=0; i<N; i++)
    {
       auto pos = lower_bound(list.begin(), list.end(), lis[i]);
       int index = pos - list.begin();

       if (pos == list.end())
       {
        list.push_back(lis[i]);
       }
       else 
       {
        *pos = lis[i];
       }

       idx[i] = index;
       if(index > 0)
       {
        trace[i] = find(idx.begin(), idx.begin()+i, index -1) - idx.begin();
       }
    }

    cout << list.size() << '\n';

    int lastIndex = -1;
    for(int i=0; i<N; i++)
    {
        if(idx[i] == list.size() - 1)
        {
            lastIndex = i;
            break;
        }
    }

    vector<int> result;
    while (lastIndex != -1)
    {
        result.push_back(lis[lastIndex]);
        lastIndex = trace[lastIndex];
    }
    reverse(result.begin(), result.end());

    for (int num : result) {
        cout << num << " ";
    }
    cout << "\n";

>>>>>>> 9e973d7f2a4175353f1c2e00a72b0b770fa633ef
    return 0;
}