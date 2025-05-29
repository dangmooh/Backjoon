/*
공격

빈 공간 채우기

4번 이상 반복 삭제

몬스터 채우기

*/

#include <iostream>
#include <vector>
#include <list>

using namespace std;

int n, m;
int result = 0;
vector<vector<int>> board;
vector<vector<int>> tmpBoard;

vector<pair<int,int>> monster;
vector<pair<int,int>> tmpMonster;

void findMonster()
{
    monster.clear();
    pair<int, int> dd[4] = {{-1,0}, {0,1}, {1,0}, {0,1}};

    int dir = 0, count = 1;
    int curX = n/2, curY = n/2;

    while(curX || curY)
    {
        for(int i=0; i<count; i++)
        {
            curX += dd[dir].first; curY += dd[dir].second;
            monster.push_back(make_pair(curX, curY));

            if(!curX && !curY) break;
        }
        dir = (dir + 1) % 4;
        if(dir == 0 || dir == 2) count++;
    }

}

void fillSpace()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            tmpBoard[i][j] = 0;
        }
    }

    int idx = 0;
    for(pair<int,int>& pos : monster)
    {
        int tx, ty;
        tie(tx, ty) = pos;

        if(board[ty][tx] != 0)
        {
            int mx,my;
            tie(mx, my) = monster[idx];
            tmpBoard[my][mx] = board[ty][tx];
            idx++;
        }
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            board[i][j] = tmpBoard[i][j];
        }
    }

}

void attack(int d, int p)
{
    pair<int, int> dd[4] = {{1,0},{0,1},{-1,0},{0,-1}}; // r d l u

    int nx = n/2, ny = n/2;
    while(p--)
    {
        nx += dd[d].first;
        ny += dd[d].second;
        result += board[ny][nx];
        board[ny][nx] = 0;
    }
    fillSpace();
}


void eraseRepeat()
{
    findMonster();

    int s = 0;
    int count = 0;
    for(pair<int,int>& pos : monster)
    {
        int mx, my;
        tie(mx, my) = pos;

        
        if(board[][] == board[my][mx])
        {
            count++;
        }
        if
    }

}


void solvP(int d, int p)
{
    findMonster();
    attack(d, p);

    eraseRepeat();

    fillMonster();
}

int main()
{

    cin >> n >> m;
    ux = n / 2;
    uy = n / 2;
    board.resize(n, vector<int>(n));
    tmp.resize(n, vector<int>(n,0));

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cin >> board[i][j];
        }
    }

    while(m--)
    {
        int d, p;
        cin >> d >> p;
        solvP(d, p);

    }

    return 0;
}