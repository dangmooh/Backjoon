/*
에라토스테네스의 체 O(N log log N)
two pointer O(N)
*/

#include <iostream>
#include <vector>


using namespace std;

vector<int> findnum(int N)
{
    vector<bool> solv(N+1, true);
    for(int i =1; i < N+1; i++)
    {
        solv[i] = i;
    }    

    for (int i = 2; i * i <= N; i++)
    {
        if(solv[i] == false) continue;

        for(int j = i * i; j <= N; j += i)
        {
            solv[j] = false;
        }
    }
    vector<int> ret;
    for (int i = 2; i<= N; i++)
    {
        if(solv[i] == true) ret.push_back(i);
    }

    return ret;
}


int main()
{
    int N;
    cin >> N;

    // N 전까지 소수를 구하는 함수
    vector<int> num = findnum(N);

    int left=0, right=0, sum=0;
    int count=0;
    while(right < num.size())
    {
        sum += num[right++];

        while(sum >= N)
        {
            if(sum == N) count++;
            sum -= num[left++];
        }
    }

    cout << count << '\n';

    return 0;
}