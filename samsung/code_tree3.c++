

#include <iostream>
#include <vector>


using namespace std;

vector<vector<int>> board;
int n, m;

void simulation()
{

    
}

int main()
{
    cin >> n >> m;

    board.resize(n, vector<int>(n));

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> board[i][j];

    while(m--)
    {
        simulation();
    }

    return 0;
}