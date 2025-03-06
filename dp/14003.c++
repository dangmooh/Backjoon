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

    return 0;
}