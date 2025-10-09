#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <limits>

using namespace std;
using Pii = pair<int,int>;

const int INF = numeric_limits<int>::max();
const int MAX_GRID_SIZE = 50; // 격자의 최대 크기는 50입니다.
const int MAX_JUMP_POWER = 5; // 개구리가 가질 수 있는 최대 점프력은 5입니다.
int N, Q;


struct COO {
    int r, c;
    COO operator+(const COO &rhs) const { return {r + rhs.r, c + rhs.c}; }
    COO operator*(const int j) const { return {r * j, c * j}; }
    bool operator==(const COO &rhs) const {return r == rhs.r && c == rhs.c; }
    bool inb(const int size) const { return r >=0 && r<size && c>=0 && c<size; }
    int generate_id(const int j) const { return (MAX_JUMP_POWER+1)*((N*c) + r) + j;} 
};

vector<COO> drcs = {{1,0}, {-1,0}, {0,1}, {0,-1}};

vector<vector<char>> board;
vector<Pii> state_graph[MAX_GRID_SIZE * MAX_GRID_SIZE * MAX_JUMP_POWER];



void make_tree() //O(40000)
{
    for(int i=0; i<N; ++i)
    {
        for(int j=0; j<N; ++j) 
        {
            if(board[i][j] != '.') continue;

            COO cur = {i, j};
            for(int k=1; k<=MAX_JUMP_POWER; ++k) 
            {
                int curId = cur.generate_id(k);

                for(const auto &drc : drcs)
                {
                    COO nxt = cur;
                    bool flag = true;
                    for(int step=0; step<k; ++step)
                    {
                        nxt = nxt + drc;
                        if(!nxt.inb(N) || board[nxt.r][nxt.c] == '#')
                        {
                            flag = false;
                            break;
                        }
                    }

                    if(!flag || board[nxt.r][nxt.c] != '.') continue;
                    
                    int nxtId = nxt.generate_id(k);
                    state_graph[curId].push_back({1,nxtId});
                }

                if(k<MAX_JUMP_POWER)
                {
                    int nk = k+1;
                    int nxtId = cur.generate_id(nk);
                    state_graph[curId].push_back({nk*nk,nxtId});
                }
                for(int t=1; t<k; ++t)
                {
                    int nxtId = cur.generate_id(t);
                    state_graph[curId].push_back({1,nxtId});
                }
            }
        }
    }
}

int dijkstra(COO st, COO ed)
{
    int st_id = st.generate_id(1);
    vector<int> dist(MAX_GRID_SIZE * MAX_GRID_SIZE * MAX_JUMP_POWER, INF);
    priority_queue<Pii, vector<Pii>, greater<>> pq;
    pq.push({0, st_id});
    dist[st_id] = 0;

    while(!pq.empty())
    {
        Pii cur = pq.top(); pq.pop();

        if(cur.first > dist[cur.second]) continue;

        int j = cur.second % (MAX_JUMP_POWER + 1);
        int curR = (cur.second / (MAX_JUMP_POWER + 1)) % N;
        int curC = (cur.second / (MAX_JUMP_POWER + 1)) / N;
        COO curP = {curR, curC};

        if(curP == ed)
        {
            return cur.first;
        }

        for(auto& nxt : state_graph[cur.second])
        {
            if(dist[nxt.second] > cur.first + nxt.first)
            {
                dist[nxt.second] = cur.first + nxt.first;
                pq.push({cur.first + nxt.first, nxt.second});
            }
        }
    }
    return -1;
}

int main()
{

    cin >> N;
    board.resize(N, vector<char>(N));
    for(int i=0; i<N; ++i)
    {
        string s;
        cin >> s;
        for(int j=0; j<N; ++j)
        {
            board[i][j] = s[j];
        }
    }

    make_tree();
    cin >> Q;

    while(Q--)
    {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        COO st = {r1-1, c1-1}, ed = {r2-1, c2-1};

        cout << dijkstra(st, ed) << '\n';
    }

    return 0;
}