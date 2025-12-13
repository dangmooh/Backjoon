/*
2025.12.11


3X3 보드에 O, X를 번걸아 가면서 표시 (O가 선공)
-> turn 제

실수가 발생할 경우의 수
1. O보다 X가 더 많은 경우
4. X보다 O가 1개 보다 더 많은 경우


1,3은 단순히 보드의 개수를 새면 된다.


*/

#include <string>
#include <vector>
using namespace std;

bool isWin(const vector<string>& board, char c) {
    // 가로
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == c && board[i][1] == c && board[i][2] == c)
            return true;
    }
    // 세로
    for (int j = 0; j < 3; ++j) {
        if (board[0][j] == c && board[1][j] == c && board[2][j] == c)
            return true;
    }
    // 대각선 2개
    if (board[0][0] == c && board[1][1] == c && board[2][2] == c)
        return true;
    if (board[0][2] == c && board[1][1] == c && board[2][0] == c)
        return true;

    return false;
}

int solution(vector<string> board) {
    int cntO = 0, cntX = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == 'O') cntO++;
            else if (board[i][j] == 'X') cntX++;
        }
    }

    // 1. 말 개수 기본 조건
    if (cntX > cntO) return 0;
    if (cntO > cntX + 1) return 0;

    bool winO = isWin(board, 'O');
    bool winX = isWin(board, 'X');

    // 2. 둘 다 승리인 경우
    if (winO && winX) return 0;

    // 3. O가 이긴 경우 → O는 항상 X보다 1개 더 많아야 함
    if (winO && cntO != cntX + 1) return 0;

    // 4. X가 이긴 경우 → O와 X 개수가 같아야 함
    if (winX && cntO != cntX) return 0;

    // 5. 그 외는 모두 가능
    return 1;
}
