#include <string>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int N, M;
vector<vector<char>> board;

inline bool inb(int r, int c) { return r>=0 && r<=N+1 && c>=0 && c<=M+1; }

void printMap()
{
    cout << "----------------------------------------" <<"\n";

    for(int i=0; i<=N+1; ++i)
    {
        for(int j=0; j<=M+1; ++j)
        {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

void erase(char target)
{
    queue<pair<int,int>> q;
    vector<vector<bool>> visited(N+2, vector<bool>(M+2, false));
    q.push({0,0});
    visited[0][0] = true;
    vector<pair<int, int>> cand;
    while(!q.empty())
    {
        auto [r, c] = q.front(); q.pop();
        
        for(int d=0; d<4; ++d)
        {
            int nr = r + dy[d];
            int nc = c + dx[d];
            
            if(!inb(nr,nc) || visited[nr][nc]) continue;
            if(board[nr][nc] == '.') q.push({nr, nc});
            if(board[nr][nc] == target) cand.push_back({nr,nc});
            visited[nr][nc] = true;
        }    
        
    }
        
    
    
    for(auto [r, c] : cand)
    {
        board[r][c] = '.'; 
    }
    
}



int solution(vector<string> storage, vector<string> requests) {
    int answer = 0;

}