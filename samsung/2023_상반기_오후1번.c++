#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>


using namespace std;

using Pii = pair<int, int>;
using Board = vector<vector<int>>;


int N, M, K;

struct COO {
    int r, c;
    COO operator+(const COO& rhs) const { return { r + rhs.r, c + rhs.c }; }
    int operator-(const COO& rhs) const { return abs(r - rhs.r) + abs(c - rhs.c); }
    bool operator==(const COO& rhs) const { return r == rhs.r && c == rhs.c; }
    bool inb(int size) const { return r >= 0 && r < size && c >= 0 && c < size; }
};

vector<COO> drcs = { {1,0}, {-1,0}, {0,1}, {0,-1} };

bool comp(const pair<COO, int>& A, const pair<COO, int>& B)
{
    if (A.second != B.second) return A.second < B.second;
    else if (A.first.r != B.first.r) return A.first.r < B.first.r;
    return A.first.c > B.first.c;
}

struct Mirror {
    vector<pair<COO, int>> runners;
    Board mirror, runners_board;
    COO goal;
    int move_dist;

    Mirror(const Board& _mirror, const Board& _runners_board, const COO& _goal) : mirror(_mirror), runners_board(_runners_board), goal(_goal), move_dist(0) {    }

    void turn()
    {

        for(int i=0; i<length; ++i)
        {
            min_r = (min_r - 1 >= 0) ? min_r - 1 : min_r;
            min_c = (min_c - 1 >= 0) ? min_c - 1 : min_c;
        }

        //cout << " ----------- turn map ---------------" <<'\n';
        //cout << "runners_rc : " << runners[0].first.r << " , " <<  runners[0].first.c << " " << length <<'\n';

        //cout << "min_rc : " << min_r << " , " <<  min_c << " " << length <<'\n';

        Board newMirror(length+1, vector<int>(length+1));
        Board newRunnersBoard(length+1, vector<int>(length+1));

        for (int i = 0; i <= length; ++i)
        {
            for (int j = 0; j <= length; ++j)
            {
                newMirror[i][j] = mirror[length - j + min_r][i + min_c];
                newRunnersBoard[i][j] = runners_board[length - j + min_r][i + min_c];
                if (newMirror[i][j] > 0) newMirror[i][j]--;
            }
        }


        for (int i = min_r; i <= min_r + length; ++i)
        {
            for (int j = min_c; j <= min_c + length; ++j)
            {
                mirror[i][j] = newMirror[i - min_r][j - min_c];
                runners_board[i][j] = newRunnersBoard[i - min_r][j - min_c];
            }
        }
    }

    void find_goal()
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                if (mirror[i][j] < 0) { goal.r = i; goal.c = j; }
                if (runners_board[i][j] >0)
                {
                    int dist = max(abs(i - goal.r), abs(j - goal.c));
                    runners.push_back({ {i, j}, dist });
                }
            }
        }
    }
    void find_runners()
    {
        runners.clear();
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                for(int r =0; r<runners_board[i][j]; ++r)
                {
                    int dist = max(abs(i - goal.r), abs(j - goal.c));
                    runners.push_back({ {i, j}, dist });
                }
            }
        }
    }

    void move_runner()
    {
        for (const auto& runner : runners)
        {
            COO nxt = runner.first;
            for (const auto& drc : drcs)
            {
                COO tmp_nxt = runner.first + drc;
                if (!tmp_nxt.inb(N) || mirror[tmp_nxt.r][tmp_nxt.c] > 0) continue;

                if (tmp_nxt == goal) 
                { 
                    move_dist++; 
                    runners_board[runner.first.r][runner.first.c]--; 
                    break; 
                }

                int cur_dist = runner.first - goal;
                int tmp_dist = tmp_nxt - goal;

                if (cur_dist > tmp_dist)
                {
                    move_dist++;
                    runners_board[tmp_nxt.r][tmp_nxt.c]++;
                    runners_board[runner.first.r][runner.first.c]--;
                    nxt = tmp_nxt;
                    break;
                }
            }
        }
        find_runners();
        //print_rummers();
    }

    void print_map()
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                cout << mirror[i][j] << " ";
            }
            cout << "\n";
        }
    }

    void print_rummers()
    {
        cout << "==================================================" <<'\n';
        for (const auto& runner : runners)
        {
            cout << " runner  : " << runner.first.r << " " << runner.first.c << " " << runner.second << '\n';
        }
    }
};


int main()
{
    cin >> N >> M >> K;

    Board board(N, vector<int>(N)), runners_board(N, vector<int>(N, 0));
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cin >> board[i][j];
        }
    }

    for (int i = 0; i < M; ++i)
    {
        int r, c;
        cin >> r >> c;
        runners_board[r-1][c-1]++;
    }

    COO _goal;
    int r, c;
    cin >> r >> c;
    _goal = { r - 1, c - 1 };
    board[_goal.r][_goal.c] = -1;

    Mirror runner_mirror(board, runners_board, _goal);

    while (K--)
    {
        //cout << " ----------- current stage : "<< K << "---------------" << '\n';

        runner_mirror.find_goal();
        runner_mirror.find_runners();

        runner_mirror.move_runner();

        runner_mirror.turn();

        //runner_mirror.print_map();

        if (runner_mirror.runners.empty()) break;
    }
    runner_mirror.find_goal();

    cout << runner_mirror.move_dist << '\n';
    cout << runner_mirror.goal.r + 1 << " " << runner_mirror.goal.c + 1 << '\n';

    return 0;
}