#include <iostream>
#include <vector>
#include <queue>

using namespace std;


int n;

pair<int, int> drcs[4] = {{1,0}, {0,1},{-1,0},{0,-1}};
int opp[4] = {2, 3, 0, 1};

int main()
{

    cin >> n;
    vector<vector<int>> board(n, vector<int>(n));
    for(int i=0; i<n; ++i)
        for(int j=0; j<n; ++j)
            cin >> board[i][j];

    queue<pair<int,int>> q;
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    q.push({0,0});
    visited[0][0] = true;


    while(!q.empty())
    {
        auto [r, c] = q.front(); q.pop();
        if(r==n-1 && c==n-1)
        {
            
            break;
        }
        
    }

    

    return 0;
}