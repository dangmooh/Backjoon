#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>


using namespace std;

using PII = pair<int,int>;
using MAP = vector<vector<int>>;

queue<int> q;
int K, M;

PII dd[4] = {{0,1},{1,0},{0,-1},{-1,0}};

inline bool inb(int r, int c) { return r>=0 && r<5 && c>=0 && c<5; }

void printMap(MAP &map)
{
    for(int i=0; i<5; ++i)
    {
        for(int j=0; j<5; ++j)
        {
            cout << map[i][j] << " ";
        }
        cout << '\n';
    }
}

int bfs(MAP &map, int r, int c, int target)
{
    int res = 0;
    vector<vector<bool>> visited(5, vector<bool>(5, false));
    queue<PII> bq;
    queue<PII> eq;
    eq.push({r,c});
    visited[r][c] = true;
    bq.push({r, c});
    

    while(!bq.empty())
    {
        PII cur = bq.front(); bq.pop();

        for(int i=0; i<4; ++i)
        {
            int nx = cur.second + dd[i].second;
            int ny = cur.first + dd[i].first;

            if(!inb(ny, nx) || visited[ny][nx]) continue;
            if(map[ny][nx] == target)
            {
                eq.push({ny, nx});
                bq.push({ny,nx});
                visited[ny][nx] = true;
            }
        }
    }

    if(eq.size() >= 3) // 획득 가능하면 해당 삭제
    {
        res = eq.size();
        while(!eq.empty())
        {
            PII cur = eq.front(); eq.pop();
            map[cur.first][cur.second] = 0;
        }
    }

    return res;
}

int get_gold(MAP &map)
{
    int res = 0;

    for(int i=0; i<5; ++i)
    {
        for(int j=0; j<5; ++j)
        {
            if(map[i][j] == 0) continue;
            res += bfs(map, i, j, map[i][j]);
        }
    }

    return res;
}

void fill_gold(MAP &map)
{
    for(int i=4; i>=0; --i)
    {
        for(int j=0; j<5; ++j)
        {
            if(map[i][j] == 0)
            {
                map[i][j] = q.front();
                q.pop();
            }
        }
    }
}

MAP turn(const MAP &tmp)
{
    MAP res(3, vector<int>(3));
    for(int i=0; i<3; ++i)
    {
        for(int j=0; j<3; ++j)
        {
            res[i][j] = tmp[2-j][i];
        }
    }
    return res;
}

pair<MAP, int> find_gold(MAP map, int r, int c, int t)
{
    vector<vector<int>> tmp(3, vector<int>(3));

    int res = 0;
    for(int i=0; i<3; ++i)
    {
        for(int j=0; j<3; ++j)
        {
            tmp[i][j] = map[r-1 + i][c-1+j];
        }
    }


    for(int i=0; i<t; ++i)
    {
        tmp = turn(tmp);
    }

    for(int i=0; i<3; ++i)
    {
        for(int j=0; j<3; ++j)
        {
            map[r-1 + i][c-1+j] = tmp[i][j];
        }
    }
    //cout << "current : " << r << c << t << '\n';
    //printMap(map);

    while(true)
    {
        int get = get_gold(map);
        if(get == 0) break;
        res += get;
    }

    return {map, res};
}


int main()
{
    cin >> K >> M;

    MAP map(5, vector<int>(5));
    for(int i=0; i<5; ++i)
    {
        for(int j=0; j<5; ++j)
        {
            cin >> map[i][j];
        }
    }

    while(M--)
    {
        int t;
        cin >> t;
        q.push(t);
    }


    while(K--)
    {
        MAP newMap;
        int r = 0, c = 0, angle = 0, gold = 0;

        pair<MAP, int> cur;
        for(int i=1; i<4; ++i)
        {
            for(int j=1; j<4; ++j)
            {
                for(int t=1; t<4; ++t)
                {
                    cur = find_gold(map, i, j, t);
                    if(gold < cur.second)
                    {
                        r = i; c = j; angle = t; gold = cur.second; newMap = cur.first;
                    }
                }
            }
        }

        if(gold == 0) break;
        cout << gold << '\n';
        fill_gold(newMap);

    }


    return 0;
}