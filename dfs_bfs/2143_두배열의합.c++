#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

vector<int> sA, sB;
vector<bool> vA, vB;

void dfsA(const vector<int> &A, int start, int res)
{
    for(int i=start; i<A.size(); ++i)
    {
        if(!vA[i])
        {
            sA.push_back(res);
            vA[i] = true;
            dfsA(A, i+1, res + A[i]);
            vA[i] = false;
        }
    }
}

void dfsB(const vector<int> &B, int start, int res)
{
    for(int i=start; i<B.size(); ++i)
    {
        if(!vB[i])
        {
            sB.push_back(res);
            vB[i] = true;
            dfsA(B, i+1, res + B[i]);
            vB[i] = false;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll T; cin >> T;

    int n; cin >> n;

    vector<int> A(n);
    vA.resize(n, false);
    for(int i=0; i<n; ++i) cin >> A[i];

    int m; cin >> m;

    vector<int> B(m);
    vB.resize(n,false);
    for(int i=0; i<m; ++i) cin >> B[i];

    dfsA(A, 0, 0);

    dfsB(B, 0, 0);
    
    sort(sB.begin(), sB.end());

    for(int x : sA)
    {
        
    }

    return 0;
}