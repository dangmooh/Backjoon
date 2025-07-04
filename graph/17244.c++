/*
map인데 s, e 지점이 있으며 꼭 지나야하는 여러 좌표가 주어져있다. 
s에서 e로 꼭 지나야하는 지점들을 지나며 도착하는 최단 거리를 구하여라.

bitmasking + bfs + graph
*/

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

vector<vector<char>> map;
vector<pair<int,int>> item;
vector<vector<int>> itemIdx;
vector<vector<vector<bool>>> visited;
int N, M;
int sx, sy, ex, ey;
pair<int,int> dd[4] = {{0,1},{0,-1},{1,0},{-1,0}};

int main()
{
    cin >> N >> M;
    map.resize(M, vector<char>(N));
    itemIdx.resize(M, vector<int>(N,-1));
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<M; j++)
        {
            char tmp;
            cin >> tmp;
            map[i][j] = tmp;
            if(tmp == 'X')
            {
                item.emplace_back({i, j});
            }
            else if(tmp == 'S')
            {
                sx = j;
                sy = i;
            }
            else if (tmp == 'E')
            {
                ex = j;
                ey = i;
            }
        }
    }

    int itemSize = item.size();
    for (int i=0; i<itemSize; i++)
    {
        auto [y, x] = item[i];
        itemIdx[y][x] = i;
    }

    visited.resize(M, vector<vector<bool>>(N, vector<bool>(1<<itemSize, false)));

    queue<tuple<int,int,int,int>> q;
    visited[sy][sx][0] = true;
    q.push({sy,sx,0,0});

    int answer = -1;
    while(!q.empty())
    {
        auto [x, y, mask, dist] = q.front();
        q.pop();

        if(y==ey && x==ex && mask == (1<<itemSize) - 1)
        {
            answer = dist;
            break;
        }

        for(int i=0; i<4; i++)
        {
            int ny = y + dd[i].first;
            int nx = x + dd[i].second;

            if(ny <0 || nx < 0 || ny>=M || nx >= N)
            {
                continue;
            }
            if(map[ny][nx] == '#')
            {
                continue;
            }
            int newMask = mask;
            if(map[ny][nx] == 'X')
            {
                int idx = itemIdx[ny][nx];
                newMask = mask | (1<<idx);
            }
            if(!visited[ny][nx][newMask])
            {
                visited[ny][nx][newMask] = true;
                q.push({ny,nx,newMask,dist+1});
            }
        }

    }
    cout << answer << "\n";
    return 0;
}