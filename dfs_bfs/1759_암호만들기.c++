#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int L, C;
vector<char> A;
vector<char> pall;
vector<bool> visited;
void dfs(int start, int depth)
{
    if (depth == L)
    {
        int x = 0, y = 0;
        for (int i = 0; i < L; ++i)
        {
            
            if (pall[i] == 'a' || pall[i] == 'e' || pall[i] == 'i' || pall[i] == 'o' || pall[i] == 'u') x++;
            else y++;
        }
        if (x < 1 || y < 2) return;
        for (int i = 0; i < L; ++i) cout << pall[i];
        cout << '\n';
        return;
    }

    for (int i = start; i < A.size(); ++i)
    {
        if (!visited[i])
        {
            //visited[i] = true;
            pall[depth] = A[i];
            dfs(i + 1, depth + 1);
            //visited[i] = false;
        }
    }
}

int main()
{

    cin >> L >> C;
    A.resize(C); pall.resize(L);
    for (int i = 0; i < C; ++i) cin >> A[i];
    visited.assign(C, false);
    sort(A.begin(), A.end());
    dfs(0, 0);

    return 0;
}