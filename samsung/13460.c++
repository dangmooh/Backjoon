/*
보드 최대 100

상하좌우로 보드를 기울인다. 
while 문으로 공이 막히는 순간까지 움직인다.
목적지에 도착하는 것을 어떻게 판단할 것인가?
움직이는 함수에서 판단한다.


빨강 파랑의 위치 정보를 저장해 둔다
queue 변화한 빨강 파랑의 위치를 판단한다.


*/

#include <iostream>
#include <vector>
#include <queue>


using namespace std;

typedef struct _ball {
    int y, x;
    int cnt;
} ball;

int N, M;
int result;
vector<vector<char>> board;
ball red, blue;


int moveUp(const ball newRed, const ball newBlue);
int moveDown(const ball newRed, const ball newBlue);
int moveLeft(const ball newRed, const ball newBlue);
int moveRight(const ball newRed, const ball newBlue);

int (*pftn[4])(const ball, const ball) = {
    moveUp,
    moveDown,
    moveLeft,
    moveRight
};


void solvP()
{
    queue<ball> qRed;
    queue<ball> qBlue;

    qRed.push(red);
    qBlue.push(blue);

    while(!qRed.empty())
    {
        ball curRed = qRed.front();
        ball curBlue = qBlue.front();
        qRed.pop();
        qBlue.pop();

        for(int i=0; i < 4; i++)
        {
            int flag = pftn[i](curRed, curBlue);
            //cout << red.cnt << "\n";
            if(flag == 0 && curRed.cnt < 10) // goal
            {
                result = red.cnt;
                break;
            }
            else if(flag == 1 && curRed.cnt < 10) // nothing
            {
                qRed.push(red);
                qBlue.push(blue);
            }
            else // blue  
            {
                continue;
            }
        }
        if(result > 0) break;
    }
    
    cout << ((result > 0) ? result : -1) << "\n";
}


int moveUp(const ball newRed, const ball newBlue)
{
    int rX, rY, bX, bY, cntR = 0, cntB = 0, flag = 1;
    rX = newRed.x;
    rY = newRed.y;
    bX = newBlue.x;
    bY = newBlue.y;

    while(true)
    {
        rY -= 1;
        if(board[rY][rX] == '#')
        {
            rY += 1;
            break;
        }
        else if(board[rY][rX] == 'O')
        {
            flag = 0;
            break;
        }
        cntR++;
    }
    while(true)
    {
        bY -= 1;
        if(board[bY][bX] == '#')
        {
            bY += 1;
            break;
        }
        else if(board[bY][bX] == 'O')
        {
            flag = 2;
            break;
        }
        cntB++;
    }

    if(rX == bX && rY == bY)
    {
        (cntR > cntB) ? rY += 1 : bY += 1;
    }

    red = {rY, rX, newRed.cnt + 1};
    blue = {bY, bX, newBlue.cnt + 1};

    return flag;
}
int moveDown(const ball newRed, const ball newBlue)
{
    int rX, rY, bX, bY, cntR = 0, cntB = 0, flag = 1;
    rX = newRed.x;
    rY = newRed.y;
    bX = newBlue.x;
    bY = newBlue.y;

    while(true)
    {
        rY += 1;
        if(board[rY][rX] == '#')
        {
            rY -= 1;
            break;
        }
        else if(board[rY][rX] == 'O')
        {
            flag = 0;
            break;
        }
        cntR++;
    }
    while(true)
    {
        bY += 1;
        if(board[bY][bX] == '#')
        {
            bY -= 1;
            break;
        }
        else if(board[bY][bX] == 'O')
        {
            flag = 2;
            break;
        }
        cntB++;
    }

    if(rX == bX && rY == bY)
    {
        (cntR > cntB) ? rY -= 1 : bY -= 1;
    }

    red = {rY, rX, newRed.cnt + 1};
    blue = {bY, bX, newBlue.cnt + 1};

    return flag;
}
int moveLeft(const ball newRed, const ball newBlue)
{
    int rX, rY, bX, bY, cntR = 0, cntB = 0, flag = 1;
    rX = newRed.x;
    rY = newRed.y;
    bX = newBlue.x;
    bY = newBlue.y;

    while(true)
    {
        rX -= 1;
        if(board[rY][rX] == '#')
        {
            rX += 1;
            break;
        }
        else if(board[rY][rX] == 'O')
        {
            flag = 0;
            break;
        }
        cntR++;
    }
    while(true)
    {
        bX -= 1;
        if(board[bY][bX] == '#')
        {
            bX += 1;
            break;
        }
        else if(board[bY][bX] == 'O')
        {
            flag = 2;
            break;
        }
        cntB++;
    }

    if(rX == bX && rY == bY)
    {
        (cntR > cntB) ? rX += 1 : bX += 1;
    }

    red = {rY, rX, newRed.cnt + 1};
    blue = {bY, bX, newBlue.cnt + 1};

    return flag;
}
int moveRight(const ball newRed, const ball newBlue)
{
    int rX, rY, bX, bY, cntR = 0, cntB = 0, flag = 1;
    rX = newRed.x;
    rY = newRed.y;
    bX = newBlue.x;
    bY = newBlue.y;

    while(true)
    {
        rX += 1;
        if(board[rY][rX] == '#')
        {
            rX -= 1;
            break;
        }
        else if(board[rY][rX] == 'O')
        {
            flag = 0;
            break;
        }
        cntR++;
    }
    while(true)
    {
        bX += 1;
        if(board[bY][bX] == '#')
        {
            bX -= 1;
            break;
        }
        else if(board[bY][bX] == 'O')
        {
            flag = 2;
            break;
        }
        cntB++;
    }

    if(rX == bX && rY == bY)
    {
        (cntR > cntB) ? rX -= 1 : bX -= 1;
    }

    red = {rY, rX, newRed.cnt + 1};
    blue = {bY, bX, newBlue.cnt + 1};

    return flag;
}

int main()
{
    cin >> N >> M;
    
    board.resize(N, vector<char>(M));
    for(int i = 0; i < N; i++)
    {
        string s;
        cin >> s;
        for(int j=0; j < s.size(); j++)
        {
            if(s[j] == 'R')
            {
                red = {i, j, 0};
                board[i][j] = '.';
            }
            else if(s[j] == 'B')
            {
                blue = {i, j, 0};
                board[i][j] = '.';
            }
            else
            {
                board[i][j] = s[j];
            }
        }
    }

    solvP();

    return 0;
}