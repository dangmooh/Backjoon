#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

int N, M;
vector<int> number, seq;
vector<bool> visited;

void dfs(int start, int depth)
{
if(depth == M)
{
    for(int i=0; i<M; ++i) cout << seq[i] << ' ';
    cout << '\n';
    return;
}

for(int i=start; i<N; ++i)
{
    if(!visited[i])
    {
        visited[i] = true;
        seq[depth] = number[i];
        dfs(i+1, depth+1);
        visited[i] = false;
    }
}
}

int main()
{
cin >> N >> M;
number.resize(N); seq.resize(M); visited.resize(N, false);
for(int i=0; i<N; ++i)
{
    cin >> number[i];
}

sort(number.begin(), number.end());

dfs(0, 0);

return 0;
}