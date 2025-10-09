


#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

using MAP = vector<vector<int>>;

struct COO {
    int x, y;
    COO operator-(const COO &rhs) const {return {abs(x - rhs.x), abs(y - rhs.y)};} 
    COO operator+(const COO &rhs) const { return {x + rhs.x, y + rhs.y};}
    bool operator==(const COO &rhs) const { return x == rhs.x && y == rhs.y; }
    bool is_valid(int size) const { return x >=0 && x < size && y >= 0 && y< size; }

};

struct TIME {
    int x, y, d, v;
};

constexpr int INF = 1e9;
int N, M, F;
MAP map;
vector<COO> dd = {{1,0},{-1,0},{0,1},{0,-1}}; // 동 서 남 북
vector<vector<vector<int>>> time_map;


void printMap()
{

    for(int i=0; i<5; ++i)
        {
            cout << "time_map : " << i <<'\n';
            for(int r = 0; r<M; ++r)
            {
                for(int c=0; c<M; ++c)
                {
                    cout << time_map[i][r][c] << " ";
                }
                cout << '\n';
            }
        }
    
}

inline pair<COO,int> is_east(const COO &rhs, int dir)
{
    COO res;
    if(dir == 3) 
    {
        res= {M - rhs.y -1, M - rhs.x -1};
        return {res, 4};
    }
    res = {M - rhs.x -1, rhs.y};
    if(dir == 0) return {res, 3};
    else if(dir == 1) return {res, 2};
}

inline pair<COO,int> is_west(const COO &rhs, int dir)
{
    COO res;
    if(dir == 3) 
    {
        res = {rhs.y, rhs.x};
        return {res, 4};
    }
    res = {M - rhs.x -1, rhs.y};
    if(dir == 0) return {res, 2};
    else if(dir == 1) return {res, 3};
}

inline pair<COO,int> is_north(const COO &rhs, int dir)
{
    COO res;
    if(dir == 3) 
    {
        res = {rhs.x, M - rhs.y -1};
        return {res, 4};
    }
    res = {M - rhs.x -1, rhs.y};
    if(dir == 0) return {res, 0};
    else if(dir == 1) return {res, 1};
}

inline pair<COO,int> is_south(const COO &rhs, int dir)
{
    COO res;
    res = {M - rhs.x -1, rhs.y};

    if(dir == 3) 
    {
        return {res, 4};
    }
    if(dir == 0) return {res, 1};
    else if(dir == 1) return {res, 0};
}

inline pair<COO,int> is_up(const COO &rhs, int dir)
{
    COO res;
    if(dir == 0) 
    {
        res= {M - rhs.y -1, M - rhs.x -1};
    }
    else if(dir == 1) 
    {
        res = {rhs.y, rhs.x};
    }
    else if(dir == 2) 
    {
        res = {rhs.x, M - rhs.y -1};
    }
    else 
    {
        res = {M - rhs.x -1, rhs.y};
    }
    return {res, dir};
}

pair<COO, int> find_time_entrance(const MAP &map, const COO &tmp)
{
    queue<COO> q;
    q.push(tmp);
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    visited[tmp.y][tmp.x] = true;

    while(!q.empty())
    {
        COO cur = q.front(); q.pop();

        for(int i=0; i<4; ++i)
        {
            COO nxt = cur + dd[i];
            if(!visited[nxt.y][nxt.x] && map[nxt.y][nxt.x] != 1)
            {
                if(map[nxt.y][nxt.x] == 0) return {cur - tmp, i};
                visited[nxt.y][nxt.x] = true;
                q.push(nxt);                
            }
        }
    }
}

int find_time(const COO &st)
{
    queue<tuple<COO, int, int>> q;
    q.push({st, 4, 0});
    vector<vector<vector<bool>>> visited(5, vector<vector<bool>>(M, vector<bool>(M, false)));
    visited[4][st.y][st.x] = true;

    while(!q.empty())
    {
        COO cur; int type, t;
        tie(cur, type, t) = q.front(); q.pop();

        if(time_map[type][cur.y][cur.x] == 4)
        {
            return t;
        }

        for(int i=0; i<4; i++)
        {
            COO nxt = cur + dd[i];
            int ntype = type;
            //cout << "is : " << ntype << " dir : " << i << " x,y " << cur.x << cur.y <<'\n';

            if(!nxt.is_valid(M)) // 벗어나면
            {  
                //cout << " FALSE invalid : " << ntype << " dir : " << i << " x,y " << cur.x << cur.y <<'\n';

                if(type != 4 && i == 2) continue; //바닥으로 향하는 것은 제외

                pair<COO, int> tmp;
                if(type == 0) 
                {
                    tmp = is_east(cur, i);
                }
                else if(type == 1) 
                {
                    tmp = is_west(cur, i);
                }
                else if(type == 2) 
                {
                    tmp = is_north(cur, i);
                }
                else if(type == 3) 
                {
                    tmp = is_south(cur, i);
                }
                else if(type == 4) 
                {
                    tmp = is_up(cur, i);
                }
                nxt = tmp.first; ntype = tmp.second;

            }

            if(time_map[ntype][nxt.y][nxt.x] != 1 && !visited[ntype][nxt.y][nxt.x])
            {
                //cout << " NXT : " << ntype << " dir : " << i << " x,y " << nxt.x << nxt.y << '\n';

                visited[ntype][nxt.y][nxt.x] = true;
                q.push({nxt, ntype, t + 1});
            }
            
        }
        
    }

    return -1;
}


void find_entrance(const COO &st, const COO &ed, int start_time, const vector<TIME> &strange)
{
    MAP dist(N, vector<int>(N, 0));

    for(const auto &s : strange)
    {
        int x = s.x, y = s.y, d = s.d, v = s.v;
        dist[y][x] = INF;
        for(int i=1;; ++i)
        {
            x += dd[d].x;
            y += dd[d].y;
            if(!(x>=0 && x<N && y>=0 && y<N)) break;
            if(map[y][x] == 0) // 경계이며 도로일 경우
            {
                map[y][x] = -1;
                dist[y][x] = v * i - start_time;
            }
        }
    }

    queue<COO> q;
    q.push(st);
    dist[st.y][st.x] = 1;
    map[ed.y][ed.x] == 0;

    while(!q.empty())
    {
        COO cur = q.front(); q.pop();
        

        if(cur == ed)
        {
            cout << start_time + dist[cur.y][cur.x] << '\n';
            return;
        }

        for(auto &d : dd)
        {
            COO nxt = cur + d;
            if(nxt.is_valid(N) && map[nxt.y][nxt.x] != 1&& map[nxt.y][nxt.x] != 3)
            {
                if(map[nxt.y][nxt.x] == -1 && dist[nxt.y][nxt.x] > dist[cur.y][cur.x] + 1)
                {
                    dist[nxt.y][nxt.x] = dist[cur.y][cur.x] + 1;
                    q.push(nxt);
                }
                else if (dist[nxt.y][nxt.x] == 0)
                {
                    dist[nxt.y][nxt.x] = dist[cur.y][cur.x] + 1;
                    q.push(nxt);
                }

            }
        }
    }


    cout << -1 << '\n';
    return;
}

int main()
{
    cin >> N >> M >> F;

    map.resize(N, vector<int>(N));
    COO time_st, time_ed, map_st, map_ed, tmp;

    bool flag = false;
    for(int i=0; i<N; ++i)
    {
        for(int j=0; j<N; ++j)
        {
            cin >> map[i][j];
            if(map[i][j] == 3 && !flag) 
            {
                tmp = {j, i};
                flag = true;
            }
            if(map[i][j] == 4)
            {
                map_ed = {j, i};
            }
        }
    }
    pair<COO, int> entrance;
    entrance = find_time_entrance(map, tmp);
    COO mid = entrance.first;
    int dir = entrance.second;

    map_st = tmp + mid + dd[dir];
    
    if(dir == 2) time_ed = {mid.x, mid.y};//남
    else if(dir == 3) time_ed = {M-mid.x -1, M-mid.y-1};      //북
    else if(dir == 0) time_ed = {M-mid.y-1, mid.x};      //동
    else  time_ed = {mid.y, M-mid.x-1};                  //서


    time_map.resize(5, vector<vector<int>>(M, vector<int>(M)));

    for(int i=0; i<5; ++i)
    {
        for(int r = 0; r<M; ++r)
        {
            for(int c=0; c<M; ++c)
            {
                cin >> time_map[i][r][c];
                if(i==4 && time_map[i][r][c] == 2) time_st = {c, r};
            }
        }
    }

    //cout << "time_ed : " << dir << " x , y " << time_ed.x << time_ed.y << '\n';

    time_map[dir][time_ed.y][time_ed.x] = 4; // 시간의 벽 탈출구 표식
    //cout << "entrance : " << time_map[dir][time_ed.y][time_ed.x] << '\n';
    

    
    int map_time = find_time(time_st);
    //cout << "map_time : "<< map_time <<'\n';
    if(map_time == -1)
    {
        cout << -1 <<'\n';
        return 0;
    }


    vector<TIME> time(F);

    for(int i=0; i<F; ++i)
    {
        cin >> time[i].y >> time[i].x >> time[i].d >> time[i].v;
    }


    //cout << "entrance : " << map_st.x << map_st.y << '\n';

    find_entrance(map_st, map_ed, map_time, time);



    return 0;
}