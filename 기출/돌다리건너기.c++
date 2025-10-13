#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Node {
    int x, y, cost;
    bool operator<(const Node &o) const {return cost > o.cost;}
};

int n;
pair<int,int> dxys[4] = {{0,-1}, {1,0}, {0,1}, {-1,0}};
int opposite[4] = {2, 3, 0, 1};
inline bool inb(int y, int x) { return x >=0 && x<n && y>=0 && y<n;}

int main()
{

    cin >> n;
    vector<vector<int>> board(n, vector<int>(n));
    for(int i=0; i<n; ++i)
        for(int j=0; j<n; ++j)
            cin >> board[i][j];


    vector<vector<int>> dist(n, vector<int>(n, 1e9));
    priority_queue<Node> pq;

    dist[0][0] = 0;
    pq.push({0,0,0});

    while(!pq.empty())
    {
        Node cur = pq.top(); pq.pop();

        if(cur.cost > dist[cur.y][cur.x]) continue;

        if(cur.x == n-1 && cur.y==n-1)
        {
            cout << cur.cost << "\n";
            return 0;
        }

        for(int i=0; i<4; ++i)
        {
            int nx = cur.x + dxys[i].first;
            int ny = cur.y + dxys[i].second;
            
            if(!inb(ny, nx) || board[ny][nx] != opposite[i]) continue;

            int rot = (i - board[cur.y][cur.x] + 4) % 4;
            int ncost = cur.cost + rot + 1;

            if(ncost < dist[ny][nx])
            {
                dist[ny][nx] = ncost;
                pq.push({nx, ny, ncost});
            }
        }
    }

    cout << -1 << "\n";

    return 0;
}