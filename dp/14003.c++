
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

    return 0;
}