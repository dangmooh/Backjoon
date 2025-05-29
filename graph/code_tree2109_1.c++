/*

주사위 만들기

이동 함수
- 처음에는 오른쪽
- board > dice : 반시계 90도
- board < dice : 시계 90도
- board = dice : 진행방향
- 보드를 벗어나면 반대방향으로

점수 계산 
- 인접한 모든 같은 수 많큼


*/

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

vector<vector<int>> board;

int n, m;
int r, d, u;
int dx, dy;
int dir = 0;
int result = 0;
pair<int,int> dd[4] = {{1,0},{0,1},{-1,0},{0,-1}}; //시계방향

void makeDice()
{
    int tmpU, tmpR, tmpD;
    if(dir == 0)
    {
        tie(u, d, r)= make_tuple() 7 - r;
        tmpR = u;
        tmpD = d; 
    }
    else if(dir == 1)
    {
        tmpU = 7 - d;
        tmpD = u;
        tmpR = r; 
    }
    else if(dir==2)
    {
        tmpU = r;
        tmpD = d;
        tmpR = 7 - u;
    }
    else
    {
        tmpD = 7 - u;
        tmpR = r;
        tmpU = d;
    }
    u = tmpU;
    d = tmpD;
    r = tmpR;
}

void moveDice()
{
    if((7-u) )
}

void sumCount(int i, int j)
{
    vector<vector<bool>> visited(n, vector<bool>(n, false));

    
    int target = board[i][j];
    queue<pair<int,int>> q;
    q.push({j,i});
    visited[i][j] = true;

    while(!q.empty())
    {
        int curX, curY;
        tie(curX, curY) = q.front();
        q.pop();


        for(int i=0; i<4; i++)
        {
            int nx = curX + dd[i].first;
            int ny = curY + dd[i].second;
            if(target == board[ny][nx] && !visited[ny][nx] && nx >= 0 && nx < n&& ny >= 0&& ny <n)
            {
                visited[curY][curX] = true;
                result += target;
                q.push({nx,ny});
            }
        }

    }
}

void simulation()
{
    makeDice();
    moveDice();
    sumCount();

}



int main()
{
    cin >> n >> m; 

    board.resize(n, vector<int>(n));

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cin >> board[i][j];
        }
    }
    dx = 0;
    dy = 0;
    r = 3;
    d = 2;
    u = 1;
    while(m--)
    {
        simulation();
    }
    return 0;
}