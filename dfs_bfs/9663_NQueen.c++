#include <iostream>
#include <vector>
using namespace std;

int N;
int result = 0; // 가능한 배치 수
vector<int> queens; // 퀸의 위치를 저장 (queens[row] = col)

// 현재 행(row)에 퀸을 놓을 수 있는지 확인
bool isValid(int row, int col) {
    for (int i = 0; i < row; i++) {
        // 같은 열에 퀸이 있거나, 대각선에 퀸이 있는 경우
        if (queens[i] == col || abs(queens[i] - col) == abs(i - row)) {
            return false;
        }
    }
    return true;
}

// 백트래킹 함수
void solveNQueen(int row) {
    if (row == N) {
        result++; // 모든 퀸을 배치했으므로 경우의 수 증가
        return;
    }

    for (int col = 0; col < N; col++) {
        if (isValid(row, col)) { // 유효한 위치인지 확인
            queens[row] = col;  // 퀸 배치
            solveNQueen(row + 1); // 다음 행으로 진행
            // 백트래킹: queens[row]는 다음 반복에서 덮어쓰므로 별도 취소 작업 필요 없음
        }
    }
}

int main() {
    cin >> N;

    queens.resize(N); // 체스판 크기 초기화
    solveNQueen(0);   // 0번째 행부터 시작

    cout << result << endl; // 가능한 배치 수 출력
    return 0;
}
