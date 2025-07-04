/*
시간은 걱정하지 않아도 된다.

합치는 문제


다음 상태로 넘기는 문제
보드 전체의 상태를 넘겨도 문제 없음
queue에다가 보드 상태 전체를 저장할 수 있나?


*/


#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef vector<vector<int>> Board;

Board board;
vector<vector<bool>> visited;

int N;
int result = 0;

void moveUp(Board curBoard);
void moveDown(Board curBoard);
void moveLeft(Board curBoard);
void moveRight(Board curBoard);

void (*pftr[4])(Board) = {
    moveUp,
    moveDown,
    moveLeft,
    moveRight
}
bool canMove(int y, int x, int dy, int dx)
{
    if(y+dy >= 0 && y+dy < N && x+dx >= 0 && x+dx < N)
    {
        while(board[y+dy][x+dx] != 0)
        {
            
        }
    }
    return (y+dy >= 0 && y+dy < N && x+dx >= 0 && x+dx < N) ? true : false;
}

void solvP()
{
    queue<pair<Board, int>> q;
    q.push({board, 0});

    while(!q.empty())
    {
        Board curBoard = q.front().first;
        int curCnt = q.front().second;
        q.pop();

        for(int i=0; i<4; i++)
        {
            pftr[i](curBoard);
            if(curCnt == 4)
            {
                result = max(result, findMax(board));
                continue;
            }
            if(curBoard != board)
            {
                q.push({board, curCnt + 1});
            }
        }
    }
    cout << result << "\n";
    return;
}

void moveUp(Board curBoard)
{
    visited.assign(N, vector<bool>(N, false));
    
    for(int i=1; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            int ny = i;
            while(ny - 1>= 0 && board[ny -1][j] == 0)
            {
                ny -= 1;
            }
            while(curBoard[i - 1][j] != 0)
        }
    }
}

int main()
{
    cin >> N;
    board.resize(N, vector<int>(N, 0));

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            cin >> board[i][j];
        }
    }

    solvP(board);

    return 0;
}