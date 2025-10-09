#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <string>

using namespace std;

using Board = vector<vector<int>>;

struct COO {
    int y, x;
    COO operator+(const COO& rhs) const { return { y + rhs.y, x + rhs.x }; }
    bool inb(int N) const { return x >= 0 && x < N && y >= 0 && y < N; }
};

vector<COO> dxys = { {0,1}, {0,-1}, {1,0},{-1,0} };

void printMap(const Board &board, int N)
{
    for(int i=0; i<N; ++i)
    {
        for(int j=0; j<N; ++j)
        {
            cout << board[i][j] << " ";
        }
        cout << '\n';
    }
}

struct PUZZLE_TABLE {
    unordered_map<string, vector<int>> puzzle;
    vector<bool> erase;
    Board A;
    int size;
    int count;

    PUZZLE_TABLE(const Board& table, int N) : A(table), size(N), count(0)
    {
    }

    void printHash()
    {
        for(auto &it : puzzle)
        {
            cout << " puzzle : " << it.first << '\n';
        }
    }

    Board turn_talbe(const Board& board)
    {
        Board newBoard(size, vector<int>(size));
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                newBoard[i][j] = board[size - 1 - j][i];
            }
        }

        return newBoard;
    }

    void find_puzzle(vector<vector<bool>>& visited, int y, int x, int id)
    {
        queue<COO> q;
        q.push({ y,x });
        visited[y][x] = true;
        A[y][x] = id;

        while (!q.empty())
        {
            COO cur = q.front(); q.pop();

            for (int i = 0; i < 4; ++i)
            {
                COO nxt = cur + dxys[i];
                if (!nxt.inb(size) || A[nxt.y][nxt.x] == 0 || visited[nxt.y][nxt.x]) continue;
                //cout << " why : " << nxt.x << " y : " << nxt.y << " id : " << id << '\n';
                visited[nxt.y][nxt.x] = true;
                A[nxt.y][nxt.x] = id;
                q.push(nxt);
            }
        }
    }

    void find_puzzle2(const Board& board, vector<vector<bool>>& visited, int y, int x, int id)
    {
        queue<COO> q;
        q.push({ y,x });
        visited[y][x] = true;
        string answer = "";

        while (!q.empty())
        {
            COO cur = q.front(); q.pop();

            for (int i = 0; i < 4; ++i)
            {
                COO nxt = cur + dxys[i];
                if (!nxt.inb(size) || board[nxt.y][nxt.x] == 0 || visited[nxt.y][nxt.x]) continue;
                visited[nxt.y][nxt.x] = true;
                q.push(nxt);
                answer += to_string(i);
            }
        }

        puzzle[answer].push_back(id);
    }

    void select_id()
    {
        vector<vector<bool>> visited(size, vector<bool>(size, false));
        int targetId = 1;
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                if (A[i][j] == 0 || visited[i][j]) continue;
                find_puzzle(visited, i, j, targetId);
                targetId++;
            }
        }

        erase.resize(targetId, false);
    }

    void choose_puzzle(const Board& board)
    {
        vector<vector<bool>> visited(size, vector<bool>(size, false));
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                if (board[i][j] == 0 || visited[i][j]) continue;
                int targetId = board[i][j];
                find_puzzle2(board, visited, i, j, targetId);
            }
        }
    }

    void make_puzzle()
    {
        select_id();
        printMap(A, size);
        Board tmp = A;
        for (int t = 0; t < 4; ++t) // 모든 방향에서의 퍼즐을 map에 저장
        {
            choose_puzzle(tmp);
            tmp = turn_talbe(tmp);
        }
        //printHash();
    }

    bool is_valid(const string& s)
    {
        auto it = puzzle.find(s);

        if (it != puzzle.end()) // 알맞는 퍼즐이라면
        {
            cout << "it is in the puzzle " << '\n';
            auto &vec = it->second;
            for(auto id : vec)
            {
                if (!erase[id]) // 지우지 않은 퍼즐의 회전이라면
                {
                    cout << "the id is  : " << id << "\n";
                    erase[id] = true;
                    count += (int)s.size() + 1; // 채운 갯수 세기
                    return true;
                }
            }
        }
        cout << "it has been used" << '\n';
        return false;
    }

    void printUsed()
    {
        for(int i=1; i<(int)erase.size(); ++i)
        {
            cout << " used : " << i << "    " << erase[i] <<'\n';
        }
    }

};  


string fill_puzzle(const Board& game_board, vector<vector<bool>>& visited, int y, int x)
{
    queue<COO> q;
    q.push({ y,x });
    visited[y][x] = true;
    string answer = "";
    int N = (int)game_board.size();

    while (!q.empty())
    {
        COO cur = q.front(); q.pop();

        for (int i = 0; i < 4; ++i)
        {
            COO nxt = cur + dxys[i];
            if (!nxt.inb(N) || game_board[nxt.y][nxt.x] == 1 || visited[nxt.y][nxt.x]) continue;
            visited[nxt.y][nxt.x] = true;
            q.push(nxt);

            answer += to_string(i);
        }
    }

    return answer;
}

int solution(vector<vector<int>> game_board, vector<vector<int>> table) {
    int answer = -1;
    int N = (int)game_board.size();
    PUZZLE_TABLE puzzel_table(table, N);

    puzzel_table.make_puzzle();

    vector<vector<bool>> visited(N, vector<bool>(N, false));
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (game_board[i][j] == 1 || visited[i][j]) continue;
            string res = fill_puzzle(game_board, visited, i, j);
            cout << " find res : " << res << '\n';
            bool flag = puzzel_table.is_valid(res);
            cout << " res : " << flag << '\n';
        }
    }

    answer = puzzel_table.count;
    //puzzel_table.printUsed();


    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto run = [&](const vector<vector<int>>& gb,
                   const vector<vector<int>>& tb,
                   const string& name,
                   int expect) {
        int got = solution(gb, tb);
        cout << "[" << name << "] got=" << got
             << ", expect=" << expect
             << (got==expect ? " 1" : " 0") << "\n";
    };

    // ---------- TC1: 1칸 퍼즐 + 동일 모양 다수 (중복 소진/카운팅 검증) ----------
    // game_board: 1=채워짐, 0=구멍(두 개의 단일 칸 구멍)
    // table: 서로 떨어진 세 개의 단일 칸 블록(그 중 2개만 사용되어야 함)
    {
        vector<vector<int>> gb = {{0,0,1,0,1,0,1,0,1,0,1,0,0,1,0,0,0,0}, {1,0,0,0,1,0,1,0,1,0,1,0,0,1,0,1,1,1}, {0,1,1,1,0,0,1,0,1,0,0,1,1,0,1,0,0,0}, {0,0,0,0,1,1,0,0,1,1,0,1,0,0,1,0,0,0}, {0,1,1,1,0,0,1,1,1,1,0,1,1,1,0,1,1,1}, {1,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0}, {0,0,0,1,1,1,0,0,1,1,0,1,1,1,1,0,0,1}, {1,1,1,0,0,0,1,1,0,0,1,0,0,0,0,1,1,0}, {0,0,1,0,1,1,1,0,0,1,0,1,1,1,1,0,0,0}, {1,1,0,1,1,0,1,1,1,1,0,1,0,0,0,1,1,1}, {0,0,0,0,1,0,0,0,0,1,0,1,0,0,1,0,1,0}, {1,1,1,1,0,1,1,1,1,1,0,1,0,1,0,0,1,0}, {0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,1,0,0}, {1,0,1,1,0,1,1,0,0,0,1,0,0,0,1,0,0,1}, {1,0,0,1,1,0,0,1,1,1,0,1,1,1,0,1,1,0}, {0,1,1,0,0,1,0,1,0,0,1,0,0,0,0,0,1,0}, {0,0,0,1,0,1,0,1,0,0,1,1,1,1,1,1,1,0}, {0,1,0,1,1,0,0,1,0,1,0,0,0,0,0,0,1,0}};
        vector<vector<int>> tb = {{1,1,1,1,1,1,0,1,0,1,1,0,0,1,0,0,1,0}, {0,0,0,0,0,0,1,1,1,0,1,0,1,1,0,1,1,0}, {1,0,1,1,0,1,0,1,0,1,1,0,1,0,1,1,0,1}, {1,1,0,1,1,1,0,1,0,1,0,1,1,0,1,0,0,1}, {1,1,1,0,0,0,1,0,1,0,1,0,0,1,0,0,1,1}, {0,0,0,1,1,1,0,1,1,1,0,1,1,0,1,0,0,0}, {1,1,1,0,0,0,0,0,1,1,0,1,1,0,1,1,1,1}, {0,0,1,0,1,1,0,1,0,0,1,0,0,1,0,0,0,0}, {1,0,1,0,0,0,0,1,0,1,1,0,1,1,0,1,1,1}, {1,0,1,0,1,1,1,1,0,1,1,0,0,0,1,1,1,0}, {1,1,0,1,0,0,0,0,1,0,0,1,1,1,0,0,0,0}, {0,0,1,1,1,1,0,1,1,0,1,0,0,0,1,1,0,1}, {1,1,0,1,0,0,1,0,0,1,0,1,0,1,0,1,0,1}, {1,1,0,0,1,1,1,0,1,1,0,1,0,1,0,1,0,1}, {0,0,1,1,0,1,1,0,1,0,1,1,0,0,0,1,0,0}, {1,1,1,0,1,0,0,1,0,1,1,0,0,1,0,1,0,1}, {0,0,0,0,1,0,1,1,1,0,0,1,0,1,1,0,1,1}, {0,1,1,1,1,0,0,1,0,0,1,1,0,1,0,0,1,1}};
        // 기대: 단일 구멍 2개 → 단일 블록 3개 중 2개 사용 → 2칸
        run(gb, tb, "TC1: single-cells & duplicate shapes", 73);
    }

    }

    return 0;
}