/*
QA
1. 좌표가 아닌 영역에 대한 내용에 대해서 어떻게 처리해야하는가?
2. 영역이 겹치는지 확인하는 방법
3. 미생물의 영역의 넓이를 어떻게 구해야하는지
*/


#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

#define MAX_N 16
#define MAX_Q 51

using pii = pair<int, int>;
using Map = vector<vector<int>>;

typedef struct _Misang {
    int minX, minY, maxX, maxY, size, number; // 맵 재배치시 영역을 판단하고 우선순위를 결정하기 위해
} Misang_t;

struct comp {
    bool operator()(const Misang_t& A, const Misang_t& B) {
        if (A.size != B.size) return A.size < B.size;
        return A.number > B.number;
    }
};

int N, Q;


pii dd[4] = { {0,1},{1,0}, {-1,0},{0,-1} };
inline bool inb(int x, int y) { return (x >= 0 && y >= 0 && x < N && y < N); }

Map map, newMap;
Misang_t misangList[MAX_Q];


void printMap(const Map& tmap)
{
    for (int i = N -1; i >=0 ; --i)
    {
        for (int j = 0; j < N; ++j)
        {
            cout << tmap[i][j] << ' ';
        }
        cout << '\n';
    }
}

void printMisang()
{
    for (int i = 1; i <= Q; ++i)
    {
        cout << "misang id : " << misangList[i].number << " size : " << misangList[i].size << '\n';
        cout << "max(x, y)" << misangList[i].maxX << ", " << misangList[i].maxY << '\n';
        cout << "min(x, y)" << misangList[i].minX << ", " << misangList[i].minY << '\n';
    }
}

void checkMisang(vector<vector<bool>>& visited, int targetId, int y, int x)
{
    queue<pii> q;
    q.emplace(x, y);
    visited[y][x] = true;

    while (!q.empty())
    {
        pii cur = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i)
        {
            int dx = cur.first + dd[i].first;
            int dy = cur.second + dd[i].second;
            if (inb(dx, dy) && !visited[dy][dx] && map[dy][dx] == targetId)
            {
                visited[dy][dx] = true;
                q.emplace(dx, dy);
            }
        }
    }
}

void eraseMisang(int targetId)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            map[i][j] = (map[i][j] == targetId) ? 0 : map[i][j];
        }
    }
}

void updateMisang(int targetId)
{
    int r2 = misangList[targetId].maxX - 1;
    int c2 = misangList[targetId].maxY - 1;
    int r1 = misangList[targetId].minX;
    int c1 = misangList[targetId].minY;
    int maxX = 0, maxY = 0, minX = MAX_N, minY = MAX_N;

    for (int i = c2; i >= c1; --i)
    {
        for (int j = r2; j >= r1; --j)
        {
            if (map[i][j] == targetId)
            {
                maxY = (maxY < i) ? i : maxY;
                maxX = (maxX < j) ? j : maxX;
                minY = (minY > i) ? i : minY;
                minX = (minX > j) ? j : minX;
            }
        }
    }


    misangList[targetId].maxX = maxX + 1;
    misangList[targetId].maxY = maxY + 1;
    misangList[targetId].minX = minX;
    misangList[targetId].minY = minY;
}

void injection(int misangId)
{
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    vector<int> check(Q+1, 0); // 몇 번째 미생물이 갈라졌는지 확인

    int r1 = misangList[misangId].minX;
    int c1 = misangList[misangId].minY;
    int r2 = misangList[misangId].maxX;
    int c2 = misangList[misangId].maxY;

    for (int i = c1; i < c2; ++i)
    {
        for (int j = r1; j < r2; ++j)
        {
            int curId = map[i][j];
            if (curId != 0)
            {
                misangList[curId].size--; // 미생물 사이즈 변경
            }
            map[i][j] = misangId;
            visited[i][j] = true;
        }
    }
    /*
    cout << "misnag id : " <<  misangId << '\n';
    cout << "(r1, c1)" << r1 << c1 << "(r2, c2)" << r2 << c2 << '\n';
    printMap();
    */

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (!visited[i][j] && map[i][j] != 0)
            {
                int curId = map[i][j];
                check[curId]++;
                checkMisang(visited, curId, i, j);
            }
        }
    }

    for (int id = 1; id <= Q; ++id)
    {
        if (check[id] >= 2)
        {
            misangList[id].size = 0; // 미생물이 갈리면 size = 0으로 없앤다.
            eraseMisang(id);
        }
        else if (check[id] == 1)
        {
            updateMisang(id); // 미생물의 최대 x와 y 좌표를 구한다.
        }
    }


}

bool isAvailable(const Map &board, int dx, int dy, int targetId)
{
    for (int col = 0; col < N; ++col)      // col = y
        for (int row = 0; row < N; ++row)    // row = x
            if (map[col][row] == targetId) 
            {
                int ny = col + dy, nx = row + dx;
                if (board[ny][nx] != 0) return false;    // 겹침 금지
            }
    return true;
}

void moveMisang()
{
    priority_queue<Misang_t, vector<Misang_t>, comp> pq;
    newMap.assign(N, vector<int>(N, 0));

    for (const Misang_t& misang : misangList)
    {
        if (misang.size != 0)
        {
            pq.push(misang);
        }
    }

    //printMisang();
    while (!pq.empty())
    {
        Misang_t curMisang = pq.top(); pq.pop();

        bool flag = false;
        int curId = curMisang.number;
        int dCol = 0;
        int dRow = 0;

        //cout << "move misangId : " << curId << '\n';
        //cout << "min(x, y) : " << curMisang.minX << curMisang.minY << "\n";
        //printMap(newMap);
        for (int row = 0; row < N && !flag; ++row)  // 전칸 조사를 해야한다. 
        //x 좌표가 가장 작으면서 y좌표가 작은 곳 없다면 해당 생물 out
        {
            for (int col = 0; col < N; ++col)
            {
                //if (newMap[col][row] != 0) continue; // 다른 미생물이 있다면
                int dx = row - curMisang.minX;
                int dy = col - curMisang.minY;

                int nx = curMisang.maxX + dx - 1; // max가 맞는지 확신해야한다.
                int ny = curMisang.maxY + dy - 1;
                if (inb(nx, ny) && isAvailable(newMap, dx, dy, curId)) // 가능 하다면 상대 값을 구해서 저장한다.
                {
                    dCol = dy;
                    dRow = dx;
                    misangList[curId].minX = row;
                    misangList[curId].minY = col;
                    misangList[curId].maxX = nx + 1;
                    misangList[curId].maxY = ny + 1;                    
                    flag = true;
                    break;
                }
            }
        }
        if (!flag)
        {
            //cout << "divided misangID : " << curId << '\n';
            misangList[curId].size = 0; // 둘 곳이 없다면 사라진다.
            continue;
        }

        //cout << "(dr, dc)" << dRow << dCol << '\n';
        for (int col = 0; col < N; ++col) // 새로운 map으로 옮긴다.
        {
            for (int row = 0; row < N; ++row)
            {
                if (map[col][row] == curId)
                {
                    int nCol = col + dCol;
                    int nRow = row + dRow;
                    newMap[nCol][nRow] = curId;
                }
            }
        }

    }

    map = newMap;
    //printMap(map);
}

long long calcScore()
{
    long long res = 0;

    bool isAdjacent[MAX_Q][MAX_Q] = { false, };


    for (int col = 0; col < N; ++col)
    {
        for (int row = 0; row < N; ++row)
        {
            int curId = map[col][row];
            if (curId == 0) continue;

            for (int dir = 0; dir < 4; ++dir)
            {
                int adjCol = col + dd[dir].second, adjRow = row + dd[dir].first;
                if (!inb(adjRow, adjCol)) continue;
                int adjId = map[adjCol][adjRow];
                if (adjId != 0 && adjId != curId)
                {
                    isAdjacent[curId][adjId] = true;
                    isAdjacent[adjId][curId] = true;
                }
            }
        }
    }

    for (int i = 1; i <= Q; ++i)
    {
        for (int j = i + 1; j <= Q; ++j)
        {
            if (isAdjacent[i][j])
            {
                res += misangList[i].size * misangList[j].size;
            }
        }
    }

    return res;
}


int main() {
    // Please write your code here.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> Q;
    map.resize(N, vector<int>(N, 0));

    int count = 0;
    int T = Q;
    while (T--)
    {
        int r1, r2, c1, c2;
        long long answer;
        cin >> r1 >> c1 >> r2 >> c2;
        count++;
        int size = (r2 - r1) * (c2 - c1);
        //cout << count << size << '\n';
        misangList[count] = { r1, c1, r2, c2, size, count };
        injection(count);
        moveMisang();
        answer = calcScore();
        cout << answer << '\n';
    }


    return 0;
}

