#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

struct airConditioner {
    int x, y, power;
    vector<vector<int>> airBoard;

    airConditioner(int _x, int _y, int _power, int n)
        : x(_x), y(_y), power(_power), airBoard(n, vector<int>(n, 0)) {}
};

vector<airConditioner> airList;

vector<tuple<int, int, int>> tmpWall;
vector<tuple<int, int, int>> wall;

vector<vector<bool>> visited;
vector<vector<pair<int,int>>> totalAir;

vector<pair<int,int>> offices;
int n, m, k;    
pair<int,int> dd[4] = {{0,-1},{-1,0},{0,1},{1,0}}; //l u r d

void printBoard()
{
    for(int j=0;j<n;j++)
    {
        for(int i=0; i<n; i++)
        {
            cout << totalAir[j][i].first << " ";
        }
        cout << "\n";
    }
}

void findWall()
{
    for(const tuple<int,int,int>& w : tmpWall) // 벽의 위치를 받아 어느 위치 어느 방향에서 불가능한지 저장
    {
        int x, y, s;
        tie(y, x, s) = w;

        if(s == 0)
        {
            wall.emplace_back(y-1,x,3);
            wall.emplace_back(y,x,1);
        }
        else
        {
            wall.emplace_back(y,x-1,2);
            wall.emplace_back(y,x,1);
        }
    }
}

bool canMove(int y, int x, int dir)
{
    for(const auto& w : wall) // 벽인 경우
    {
        int mx, my, md;
        tie(my,mx,md) = w;

        if(my == y && mx == x && md == dir)
        {
            return false;
        }
    }

    if(y<0 || x <0 || y>=n || x>=n ) // 경계인 경우
    {
        return false;
    }

    if(visited[y][x]) return false; // 방문한 경우우
    
    return true;
}

vector<pair<int, int>> findNext(int y, int x, int dir)
{
    vector<pair<int,int>> next(3, {-1,-1});

    next[0] = {y,x};
    int udir = (dir + 1 + 4) % 4;
    int nx1 = x + dd[udir].second;
    int ny1 = y + dd[udir].first;
    if(canMove(ny1, nx1, udir))
    {
        next[1] = {ny1, nx1};        
    }
    
    int ddir = (dir -1 +4) % 4;
    int nx2 = x + dd[ddir].second;
    int ny2 = y + dd[ddir].first;
    if(canMove(ny2, nx2, ddir))
    {
        next[2] = {ny2,nx2};
    }


    int cnt =0;
    for(const auto& n : next)
    {
        int ny, nx;
        tie(ny, nx) = n;
        if(canMove(ny,nx,dir))//경계, 방문처리, 벽인지 확인인
        {
            next[cnt] = {ny, nx};
            cnt++;
            continue; 
        }
        next[cnt] = {-1,-1};
        cnt++;
    }

    return next;
}

void spreadAir(airConditioner& ac)
{
    queue<tuple<int,int,int>> q;
    int dir = ac.power - 2;
    q.push(make_tuple(ac.y + dd[dir].first,ac.x+dd[dir].second, 5));
    ac.airBoard[ac.y + dd[dir].first][ac.x+dd[dir].second] = 5;
    while(!q.empty())
    {
        int curY, curX, curP;
        tie(curY, curX, curP) = q.front();
        q.pop();

        vector<pair<int,int>> s = findNext(curY, curX, dir);
        
        for(pair<int,int>& nextP : s)
        {
            int ny, nx;
            tie(ny,nx) = nextP;
            if(ny!=-1 && nx!=-1 && curP > 1) // 이동 가능하고 현재 바람의 세기가 2이상인 경우
            {
                ac.airBoard[ny][nx] = curP-1;
                visited[ny][nx] = true;
                q.push(make_tuple(ny,nx,curP -1));
            }
        }
    }

    cout << "-----------------"<<"\n";
    for(int j=0;j<n;j++)
    {
        for(int i=0; i<n; i++)
        {
            cout << ac.airBoard[j][i] << " ";
        }
        cout << "\n";
    }
    cout << "-----------------"<<"\n";
}

void sumAir()
{

    for(const auto& ac : airList)
    {
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                totalAir[i][j].first += ac.airBoard[i][j];
            }
        }
    }
}

void mixAir()
{
    visited.assign(n, vector<bool>(n, false)); // canMove에서 방문 경우 제외하기 위해
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            for(int k=0; k<4; k++)
            {
                if(canMove(i, j, k)) // 이동 가능하면
                {
                    int nx = i + dd[k].second;
                    int ny = j + dd[k].first;
                    if(ny<0 || nx <0 || ny>=n || nx>=n ) continue;// 경계인 경우
                    if(totalAir[ny][nx].first < totalAir[i][j].first) // 더 춥다면 mix
                    {
                        int dist = (totalAir[i][j].first - totalAir[ny][nx].first) /4;
                        totalAir[i][j].second -= dist;
                        totalAir[ny][nx].second += dist;
                    }
                }
            }
        }
    }
    
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++) //총 결과값을 더하고 다음 mix를 위해서 second 초기화
        {
            totalAir[i][j].first += totalAir[i][j].second;
            totalAir[i][j].second = 0;
        }
    }

}

void decreaseAir()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(i==0 || j==0) //경계인 경우 1감소
            {
                if(totalAir[i][j].first > 0)
                {
                    totalAir[i][j].first -= 1;
                }
            }
        }
    }
}

bool simulation()
{
    findWall();
    for(auto& ac : airList)
    {
        visited.assign(n, vector<bool>(n, false));
        spreadAir(ac);
    }

    sumAir();
    //printBoard();
    mixAir();
    decreaseAir();
    //printBoard();
    for(const auto& office : offices )
    {
        int nx, ny;
        tie(ny, nx) = office;
        if(totalAir[ny][nx].first < k)
        {
            return false;
        }
    }
    return true;
}


int main()
{
    cin >> n >> m >> k;

    totalAir.resize(n, vector<pair<int,int>>(n, {0,0}));

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            int tmp;
            cin >> tmp;
            if (tmp == 1)
            {
                offices.push_back({i,j});
            }
            else if(tmp > 1)
            {
                airList.emplace_back(j, i, tmp, n);
            }
        }
    }

    for(int i=0; i<m; i++)
    {
        int x, y, s;
        cin >> x >> y >> s;
        tmpWall.push_back(make_tuple(y, x, s));
    }

    int count = 0;
    while(true)
    {
        count++;
        if(simulation()) break;
    }
    cout << count <<"\n";

    return 0;
}