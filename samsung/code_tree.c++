/*

특수 영양제의 이동
특수 영양제는 보드가 연결된 것 처럼 움직인다. <- 경계를 벗어나는 움직임은 절대값으로 처리하면 된다.
8방향이 존재한다. <- 

영양제 처리 
대각선의 1보다 큰 나무만큼 성장하게 된다.

새로운 영양제 생성
2이상의 나무의 성장을 없애고 생성



*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, result;
int d, p;
bool first = true;
vector<vector<int>> board;
vector<vector<bool>> visited;

pair<int, int> dd[8] = {
    {1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}
};

void printBoard()
{
    cout << "-------------------------" << "\n";
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cout << board[i][j] << ' ';
        }
        cout << "\n";
    }
    cout << "-------------------------" << "\n";
}

void findMax()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            result += board[i][j];
        }
    }
}

void grow(int y, int x)
{
    if(y -1 >= 0 && x - 1 >= 0)
    {
        if(board[y-1][x-1] >= 1)
        {
            board[y][x] += 1;
        }
    }
    if(y -1 >= 0 && x + 1 < n)
    {
        if(board[y-1][x+1] >= 1)
        {
            board[y][x] += 1;
        }
    }
    if(y +1 < n && x - 1 >= 0)
    {
        if(board[y+1][x-1] >= 1)
        {
            board[y][x] += 1;
        }
    }
    if(y +1 < n && x + 1 < n)
    {
        if(board[y+1][x+1] >= 1)
        {
            board[y][x] += 1;
        }
    }
}

void move(vector<pair<int,int>> position, int d, int p, int count)
{
    count++;
    visited.assign(n, vector<bool>(n, false));
    vector<pair<int,int>> growP;
    for(auto& pos : position)
    {
        int nx = (pos.first + dd[d].first * p) % n;
        int ny = (pos.second + dd[d].second * p) % n;

        if(ny < 0) ny += n;
        if(nx < 0) nx += n;

        board[ny][nx] += 1;
        visited[ny][nx] = true;
        growP.push_back({nx,ny});
    }
    for(auto& g : growP)
    {
        grow(g.second, g.first);
    }

    
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(board[i][j] >= 2 && !visited[i][j])
                {
                    board[i][j] -= 2;
                    position.push_back({j, i});
                }
            }
        }
    if(count < m)
    {
        cin >> d >> p;
        move(position, d, p, count);
    }
    else{
        //printBoard();
        return;
    }

}

int main() {
    
    cin >> n >> m;
    board.resize(n, vector<int>(n));

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cin >> board[i][j];
        }
    }
    vector<pair<int,int>> position;
    position.push_back({0,n-1});
    position.push_back({1,n-1});
    position.push_back({0,n-2});
    position.push_back({1,n-2});

    cin >> d >> p;
    move(position, d-1, p, 0);

    findMax();
    cout << result << "\n";

    return 0;
}