#include <iostream>
#include <vector>
#include <queue>

using namespace std;


typedef struct {
    int x, y, w;
} Block;


vector<vector<int>> map;
pair<int,int> dd[4] = {{1,0},{-1,0},{0,1},{0,-1}};


static inline bool inb(int x, int y, int N, int M) {return x>=0 && x<M && y>=0 && y<N;}

void make_map(int N, int M)
{
    map.assign(N, vector<int>(M, 0));
    for(int i=0; i<N; ++i)
    {
        string s;
        cin >> s;
        for(int j=0; j<M; ++j)
        {
            map[i][j] = s[j] - '0';
        }
    }
}

int solvP(int N, int M)
{
    vector<vector<vector<int>>> visited(N, vector<vector<int>>(M, vector<int>(2,0)));

    queue<Block> q;
    q.emplace(0,0,0);
    visited[0][0][0] = 1;


    while(!q.empty())
    {
        Block curB = q.front(); q.pop();

        if(curB.x == M-1 && curB.y == N-1)
        {
            return visited[curB.y][curB.x][curB.w];
        }

        for(int i=0; i<4; ++i)
        {
            int x = dd[i].first + curB.x, y = dd[i].second + curB.y;
            if(inb(x,y,N,M))
            {
                if(map[y][x] == 0 && visited[y][x][curB.w] == 0)
                {
                    q.emplace(x, y, curB.w);
                    visited[y][x][curB.w] = visited[curB.y][curB.x][curB.w] + 1;
                }
                else if(map[y][x] && curB.w == 0 && visited[y][x][1] == 0)
                {
                    visited[y][x][1] = visited[y][x][curB.w] + 1;
                    q.emplace(x,y,1);
                }
            }
        }
    }
    return -1;
}

int main()
{
    int N, M;
    cin >> N >> M;

    make_map(N, M);

    int answer = solvP(N, M);

    cout << answer << '\n';
    return 0;
}