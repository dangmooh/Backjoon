
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

#define MAX_P 300

vector<vector<int>> board;
vector<vector<int>> soldier;
pair<int,int> dd[4] = {{0,-1}, {0,1},{-1,0},{1,0}};
int N, M;
int sR, sC;
int eR, eC;
vector<pair<int,int>> aPosition;



bool canMove(int x, int y)
{
    return ((x >= 0) && (y >= 0) && (x < N) && (y <N) && (board[y][x] == 0));
}

int findPath(int x, int y)
{
    queue<tuple<int,int,int>> q;
    q.push({x, y, 0});
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    visited[y][x] = true;

    while(!q.empty())
    {
        int curR, curC, curN;
        tie(curC, curR, curN) = q.front();
        q.pop();
        
        for(const pair<int,int>& d : dd)
        {
            int nx = curC + d.first;
            int ny = curR + d.second;

            if(canMove(nx, ny) && !visited[ny][nx])
            {
                if(nx == eC && ny == eR) return curN;
                visited[ny][nx] = true;
                q.push({nx, ny, curN+1});
            }
        }
    }

    return 0;
}

void moveM()
{
    int result = MAX_P;
    pair<int,int> nP;
    for(const pair<int,int>& d : dd)
    {
        int nx = sC + d.first;
        int ny = sR + d.second;

        int tmp = findPath(nx, ny);
        if(tmp < result)
        {
            nP = make_pair(nx, ny);
        }
    }
    tie(sC, sR) = nP;
}

void findS()
{
    for(int i=0; i<4; i++)
    {
        
    }
}


void simulation()
{

    moveM();

    if(sC == eC && sR == eR) // 종료
    {
        cout << 0 << "\n";
        return;
    }

    findS();

    moveS();

    attackM();
}


int main()
{
    cin >> N >> M;
    board.resize(N, vector<int>(N, 0));
    soldier.resize(N, vector<int>(N, 0));

    cin >> sR >> sC >> eR >> eC;
    
    while(M--)
    {
        int aR, aC;
        cin >> aR >> aC;
        aPosition.emplace_back(aC,aR);
    }

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            cin >> board[i][j];
        }
    }

    for(const pair<int,int>& a : aPosition)
    {
        soldier[a.second][a.first]++;
    }
    
    if(findPath(sC, sR)==0)
    {
        cout << -1 << "\n";
        return 0;
    }

    simulation();

    return 0;
}