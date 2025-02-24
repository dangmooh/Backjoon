/*
수열의 크기 = 10만
sort = nlogn 

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{

    int n;
    cin >> n;
    
    vector<int> pall(n, 0);

    for(int i = 0; i < n; i++)
    {
        cin >> pall[i];
    }


    int x;
    cin >> x;

    sort(pall.begin(), pall.end());
    int left = 0, right = pall.size() -1;
    int count = 0;

    while(left < right )
    {
        int tmp = pall[left] + pall[right];

        if( tmp == x)
        {
            count++;
            left++;
            right--;
        }
        else if(tmp > x)
        {
            right--;
        } 
        else
        {
            left++;
        }
    }
    
    cout << count << '\n';

    return 0;
}