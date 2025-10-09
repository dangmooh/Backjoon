#include <algorithm>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <queue>

using namespace std;

using PII = pair<int,int>;
using MAP = vector<vector<int>>;
#define INF 1e9

struct COO {
    int x, y;
    COO operator+(const COO &rhs) const { return {x + rhs.x, y + rhs.y}; }
    int get_dist(const COO &rhs) const { return abs(rhs.x - x) + abs(rhs.y - y); }
    bool operator==(const COO &rhs) const { return x == rhs.x && y == rhs.y; }
    bool operator!=(const COO &rhs) const { return x != rhs.x || y != rhs.y; }
    bool is_valid(int N) const {return x >= 0 && x < N && y >= 0 && y < N; }
};

vector<vector<COO>> dxys = {{{-1,0}, {1,0}, {0,-1}, {0,1}}, {{0,-1}, {0,1}, {-1,0}, {1,0}}};

struct WARRIOR_MAP {
    vector<COO> warriors;
    vector<vector<unordered_set<int>>> A;

    WARRIOR_MAP(int N, const vector<COO> &init) : warriors(init) 
    {
        A.resize(N, vector<unordered_set<int>>(N));
        for(int i=0; i<(int)warriors.size(); ++i) A[warriors[i].x][warriors[i].y].insert(i);
    }

    void remove_warrior(int idx)
    {
        COO target = warriors[idx];
        A[target.x][target.y].erase(idx);
        if(idx == (int)warriors.size() - 1)
        {
            warriors.pop_back();
        }
        else
        {
            warriors[idx] = warriors.back();
            warriors.pop_back();

            A[warriors[idx].x][warriors[idx].y].erase((int)warriors.size());
            A[warriors[idx].x][warriors[idx].y].insert(idx);
        }
    }

    int remove_same_cell(const COO &medusa)
    {
        int ret = 0;
        for(int i=0; i< (int)warriors.size(); ++i)
        {
            if(warriors[i] == medusa)
            {
                remove_warrior(i);
                i--;
                ret++;
            }
        }
        return ret;
    }

    PII move_warriors(const MAP &map, const COO &medusa)
    {
        remove_same_cell(medusa);
        int step_cnt = 0;

        for(int i=0; i<(int)warriors.size(); ++i)
        {
            if(map[warriors[i].x][warriors[i].y] == 0)
            {
                step_cnt += move_warrior(map, medusa, i);
            }
        }
        int attackers = remove_same_cell(medusa);
        return {step_cnt, attackers};
    }

    int move_warrior(const MAP &map, const COO &medusa, int idx)
    {
        int step_cnt = 0;
        
        auto &w = warriors[idx];
        
        for(auto &tmp : dxys)
        {
            bool moved = false;
            for(auto &dxy :tmp)
            {
                COO nxt = w + dxy;
                if(!nxt.is_valid((int)map.size()) || map[nxt.x][nxt.y] == 1) continue;

                if(nxt.get_dist(medusa) < w.get_dist(medusa))
                {
                    A[w.x][w.y].erase(idx);
                    w = nxt;
                    A[w.x][w.y].insert(idx);
                    step_cnt++;
                    moved = true;
                    break;
                }
            }
            if(!moved) break;
        }
        return step_cnt;
    }

    bool is_warrior(const COO &p) const { return !A[p.x][p.y].empty(); }
};


MAP get_dist_from(const MAP &road, const COO st)
{
    int N = (int)road.size();
    MAP dist(N, vector<int>(N, INF));
    queue<COO> q;
    q.push(st);
    dist[st.x][st.y] = 0;

    while(!q.empty())
    {
        COO cur = q.front();
        q.pop();

        for(const auto &dxy : dxys[0])
        {
            COO nxt = cur + dxy;
            if(!nxt.is_valid(N) || road[nxt.x][nxt.y] == 1) continue;
            if(dist[nxt.x][nxt.y] > dist[cur.x][cur.y] + 1)
            {
                dist[nxt.x][nxt.y] = dist[cur.x][cur.y] + 1;
                q.push(nxt);
            }
        }
    }

    return dist;
}


void move_medusa(const MAP &dist, COO &cur)
{
    int N = (int)dist.size();
    for(auto &dxy : dxys[0])
    {
        COO nxt = cur + dxy;
        if(!nxt.is_valid(N)) continue;
        if(dist[nxt.x][nxt.y] == dist[cur.x][cur.y] - 1)
        {
            cur = nxt;
            break;
        }
    }
}

pair<MAP, int> get_vision_map(int N, const WARRIOR_MAP &warrior_map, const COO medusa, const vector<COO> &vision_dxys)
{
    
    int warrior_cnt = 0;
    queue<COO> q;
    queue<pair<COO, int>> wq;
    q.push(medusa);

    MAP visited(N, vector<int>(N, 0));

    while(!q.empty())
    {
        COO cur = q.front(); q.pop(); 

        for(int i=0; i<3; ++i)
        {
            COO nxt = cur + vision_dxys[i];

            if(!nxt.is_valid(N) || visited[nxt.x][nxt.y] != 0) continue;
            if(warrior_map.is_warrior(nxt))
            {
                int dir = -1;
                if(medusa.x == nxt.x || medusa.y == nxt.y) dir = 1;
                else if((nxt.x - medusa.x) * vision_dxys[0].x > 0 && (nxt.y - medusa.y) * vision_dxys[0].y > 0) dir=0;
                else dir = 2;
                wq.push({nxt, dir});
            }
            visited[nxt.x][nxt.y] = 1;
            q.push(nxt);
        }
    }

    while(!wq.empty())
    {
        COO cur = wq.front().first; 
        int dir = wq.front().second;
        wq.pop();

        if(dir == -1) continue;
        
        for(int d=0; d<3; d++)
        {
            if(dir==1 && d != 1) continue;
            if(dir==0 && d == 2) continue;
            if(dir==2 && d == 0) continue;
            COO nxt = cur + vision_dxys[d];
            if(!nxt.is_valid(N) || visited[nxt.x][nxt.y] == 0) continue;
            
            visited[nxt.x][nxt.y] = 0;
            wq.push({nxt,dir});
        }
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (visited[i][j]) warrior_cnt += (int)warrior_map.A[i][j].size();

    return {visited, warrior_cnt};
}

int main()
{
    int N, M;
    cin >> N >> M;
    COO st, ed;
    cin >> st.x >> st.y >> ed.x >> ed.y;

    vector<COO> init_warriors(M);
    for (int i=0; i<M; ++i) cin >> init_warriors[i].x >> init_warriors[i].y;

    WARRIOR_MAP warrior_map(N, init_warriors);

    MAP road(N, vector<int>(N));
    for(int i=0; i<N; ++i)
    {
        for(int j=0; j<N; ++j)
        {
            cin >> road[i][j];
        }
    }

    auto dist = get_dist_from(road, ed);

    if(dist[st.x][st.y] == INF) { cout << -1 << '\n'; return 0; }

    COO cur = st;

    vector<vector<COO>> vision_dxys = {
        {{-1,-1}, {-1, 0}, {-1,1}},
        {{1,-1}, {1, 0}, {1,1}},
        {{-1,-1}, {0,-1}, {1, -1}},
        {{-1,1}, {0,1}, {1,1}},
    };

    while(cur != ed)
    {
        move_medusa(dist, cur);

        if(cur == ed) { cout << 0 << '\n'; break;}
        MAP best_map;
        int best_seen = -1, best_dir = 0;

        for(int d=0; d<4; ++d)
        {
            pair<MAP, int> tmp = get_vision_map(N, warrior_map, cur, vision_dxys[d]);
            if(tmp.second > best_seen) { best_dir = d; best_seen = tmp.second; best_map = move(tmp.first); }
        }
        
        PII res = warrior_map.move_warriors(best_map, cur);
        cout << res.first << ' ' << best_seen << ' '  << res.second << '\n';
    }

    return 0;
}