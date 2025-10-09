#include <iostream>
#include <vector>
#include  <queue>
#include <algorithm>


using namespace std;

using MAP = vector<vector<int>>; 

struct COO {
    int r, c;
    COO operator+(const COO &rhs) const { return {r + rhs.r, c + rhs.c}; }
    bool operator==(const COO &rhs) const { return r == rhs.r && c == rhs.c; }
    bool is_valid(const int r_size, const int c_size) const { return r >=0 && r<r_size && c>=0 && c<c_size; }
};


vector<COO> drcs = {
    {-1,0}, {0,1}, {1,0}, {0,-1} // 북 동  남 서
};

vector<vector<COO>> move_drcs = {
    {{0,1}, {1,0}, {0,-1}}, // 남
    {{-1,0}, {1,0}, {0,-1}}, // 서
    {{-1,0}, {0,1}, {1,0}},  // 동
};

int R, C, K;

void printMap(MAP &map)
{
    for(int i=0; i<R+3; i++)
    {
        for(int j=0; j<C; ++j)
        {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
}

struct GOLLEM {
    int id;
    COO mid;
    MAP g;

    GOLLEM(int c, int d, int k) : mid{1,1}, id(k) {
        g.resize(3, vector<int>(3, 0));
        g[mid.r][mid.c] = id;
        for(auto &drc : drcs)
        {
            COO nxt = mid + drc;
            g[nxt.r][nxt.c] = id;
        }
        COO et = mid + drcs[d];
        g[et.r][et.c] = id + 1;
        mid = {1,c};
    }

    void check_map(MAP &map, int dir)
    {
        map[mid.r][mid.c] = 0; // 기ㅣ존 영역 0으로 삭제
        for(int i=0; i<4; i++) 
        {
            COO nxt = mid + drcs[i];
            map[nxt.r][nxt.c] = 0;
        }
        //cout << "center : " << mid.r << mid.c << '\n';

        MAP ng = g;
        COO ncenter = mid + drcs[2]; // 아래로 한칸 이동한 중심


        if(dir == 3) // 서쪽 이동인 경우
        {
            for(int i=0; i<3; i++)
            {
                for(int j=0; j<3; ++j)
                {
                    ng[i][j] = g[j][2-i]; // 회전
                }
            }
            ncenter = ncenter + drcs[3]; // 중심 서쪽으로 이동
        }
        else if(dir == 1) // 동쪽 이동인 경우
        {
            for(int i=0; i<3; i++)
            {
                for(int j=0; j<3; ++j)
                {
                    ng[i][j] = g[2-j][i];// 회전
                }
            }
            ncenter = ncenter + drcs[1]; // 중심 동쪽으로 이동
        }
        //cout << "new center : " << ncenter.r << ncenter.c << '\n';

        map[ncenter.r][ncenter.c] = id;
        for(auto &drc : drcs)
        {
            COO mask = ncenter + drc;
            map[mask.r][mask.c] = ng[drc.r + 1][drc.c + 1];
        }
        //printMap(map);
        //cout << "============================================" <<'\n';
        //cout << "============================================" <<'\n';

        g = ng;
    }

    bool move_south(MAP &map, const COO center, int dir)
    {
        bool res = true;
        COO tmp = center + drcs[2];
        for(auto &drc : move_drcs[0])
        {
            COO check = tmp + drc;
            if(!check.is_valid(R + 3, C))
            {
                //cout << "out of range " << '\n';
                return false;
            }
            if( map[check.r][check.c] != 0 && map[check.r][check.c] != id && map[check.r][check.c] != id + 1)
            {
                //cout << "some in " << '\n';
                return false;
            }
        }
        check_map(map, dir);

        mid = tmp;

        return res;
    }

    bool move_west(MAP &map)
    {
        bool res = true;
        COO tmp = mid + drcs[3];
        for(auto &drc : move_drcs[1])
        {
            COO check = tmp + drc;
            if(!check.is_valid(R + 3, C) || map[check.r][check.c] != 0)
            {
                return false;
            }
        }

        if(!move_south(map, tmp, 3))
        {
            res = false;
        }

        return res;
    }

    bool move_east(MAP &map) // 동 1
    {
        bool res = true;
        COO tmp = mid + drcs[1];
        for(auto &drc : move_drcs[2])
        {
            COO check = tmp + drc;
            if(!check.is_valid(R + 3, C))
            {
                //cout << "out of range " << '\n';
                return false;
            }
            if( map[check.r][check.c] != 0)
            {
                //cout << "some in " << '\n';
                return false;                
            }
        }
        //cout << "center : " << mid.r << mid.c << '\n';
        //cout << "new : " << tmp.r << tmp.c << '\n';

        if(!move_south(map, tmp, 1))
        {
            //printMap(map);
            res = false;
        }

        return res;
    }
};


void clear_map(MAP &target_map)
{
    for(int i=0; i<R+3; ++i)
    {
        for(int j=0; j<C; ++j)
        {
            target_map[i][j] = 0;
        }
    }
}


int move_goal(const MAP &map, const COO &st, int id)
{
    COO res {0,0};
    queue<pair<COO, int>> q;
    q.push({st, id});
    vector<vector<bool>> visited(R+3, vector<bool>(C, false));
    visited[st.r][st.c] = true;

    while(!q.empty())
    {
        COO cur;
        int curId;
        cur = q.front().first;
        curId = q.front().second;
        q.pop();

        if(cur.r > res.r)
        {
            res = cur;
        }

        for(auto &drc : drcs)
        {
            COO nxt = cur + drc;
            if(!nxt.is_valid(R+3, C) || visited[nxt.r][nxt.c]) continue;
            int nxtId = map[nxt.r][nxt.c];


            if(curId % 2 == 1 && nxtId != 0) // 현재가 입구이면 모든 위치 가능
            {
                visited[nxt.r][nxt.c] = true;
                q.push({nxt, nxtId});
            }
            else if(curId % 2 == 0) // 입구가 아니라면 같은 위치나 입구만 가능
            {
                if(nxtId == curId || nxtId == curId + 1)
                {
                    visited[nxt.r][nxt.c] = true;
                    q.push({nxt, nxtId});
                }
            }
        }
    }

    //cout << " ********** best r : " << res.r << res.c << "\n";
    return res.r;
}

int main()
{
    cin >> R >> C >> K;

    MAP map(R + 3, vector<int>(C, 0));

    int answer = 0;
    while(K--)
    {
        int c, d; cin >> c >> d;

        GOLLEM gollem(c-1, d, (K + 1)*2);
        //cout << "gollem  mid : " << gollem.mid.r <<  gollem.mid.c << '\n';
        bool flag = true;
        while(true)
        {
            if(gollem.move_south(map, gollem.mid, 2))
            {
                //cout << " move south " <<'\n';
            }
            else if(gollem.move_west(map))
            {
                //cout << " move west " <<'\n';

            }
            else if(gollem.move_east(map)) 
            {
                //cout << " move east " <<'\n';
            }
            else
            {

                if(gollem.mid.r < 4)
                {
                    //cout << " clear map " <<'\n';

                    clear_map(map);
                }
                else
                {
                    //cout << " ################### move goal ################ " <<'\n';

                    answer += move_goal(map, gollem.mid, gollem.id) - 2;
                    //cout << answer << '\n';
                }
                break;
            }
        }
    }

    cout << answer << '\n';

    return 0;
}