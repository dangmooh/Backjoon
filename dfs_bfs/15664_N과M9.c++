#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

int N, M;
vector<int> number, seq;
vector<int> visited;

void dfs(int start, int depth)
{

    if(depth == M)
    {
        for(int i=0; i<M; ++i) cout << seq[i] << ' ';
        cout << '\n';
        return;
    }
    
    int last = 0;
    for(int i=start; i<N; ++i)
    {
        int num = number[i];

        if(!visited[i] && seq[i] != last)
        {
            visited[i] = true;
            seq[depth] = num;
            last = num;
            dfs(i, depth+1);
            visited[i] = false;
        }
    }

}

int main()
{
    cin >> N >> M;

    number.resize(N);seq.resize(M); visited.resize(10001, 0);    

    for(int i=0; i<N; ++i)
    {
        int tmp;
        cin >> tmp;
        number[i] = tmp;
        visited[tmp]++;
    }

    sort(number.begin(), number.end());

    dfs(0, 0);


    return 0;
}