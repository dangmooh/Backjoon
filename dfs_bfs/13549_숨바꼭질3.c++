#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef struct {
    int x, d, t;
} Node;

inline bool inb(int x) { return x < 100001 && x >= 0; }

void bfs(int N, int K)
{
    queue<Node> q;
    q.emplace(N, 0, 0);
    vector<vector<int>> street(100001, vector<int>(4, -1));
    street[N][0] = 0;

    while(!q.empty())
    {
        Node cur = q.front(); q.pop();

        if(cur.x == K)
        {
            street[K][cur.d] = cur.t;
        }

        int next1 = cur.x + 1;
        if(inb(next1) && street[next1][1] != -1)
        {
            street[next1][1] = street[cur.x][cur.d] + 1;
            q.emplace(next1, 1, )
        }

        int next2 = cur.x - 1;
        if(inb(next2) && street[next2][2] != -1)
        {
            street[next2][1] = street[cur.x][cur.d] + 1;
        }

        int next3 = cur.x * 2;
        if(inb(next3) && street[next3][3] != -1)
        {
            street[next3][1] = street[cur.x][cur.d];
        }

    }
}

int main()
{
    int N, K; cin >> N >> K;

    bfs(N, K);


    return 0;
}