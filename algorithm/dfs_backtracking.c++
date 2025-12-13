/*
🧩 개념 정리

DFS로 조합을 만든다는 건 결국 이런 재귀 구조야:

dfs(현재 인덱스, 현재까지 고른 원소 리스트)


현재 인덱스: 다음에 고려할 숫자 (1~n)

리스트: 지금까지 선택한 숫자들

각 단계에서

그 숫자를 고른다

그 숫자를 건너뛴다

를 반복하면서, 원하는 개수(예: 5개)를 고르면 출력한다.

*/

//🧩 1️⃣ 전역 상태 사용 방식
#include <iostream>
#include <vector>

using namespace std;

int n = 10, k = 5;
vector<int> comb; // 현재까지 선택한 조합

void dfs(int start) {
    // base case: k개 다 골랐다면 출력
    if ((int)comb.size() == k) {
        for (int x : comb) cout << x << " ";
        cout << "\n";
        return;
    }

    // 1부터 n까지 중에서 start부터 탐색
    for (int i = start; i <= n; ++i) {
        comb.push_back(i);      // i를 선택
        dfs(i + 1);             // 다음 숫자는 i보다 큰 것부터
        comb.pop_back();        // i를 빼고 다른 조합 시도
    }
}

//🧠 2️⃣ 인자로 visited를 전달하는 방식
void dfs(int idx, vector<bool> visited, vector<int> path) {
    if (path.size() == 5) {
        // 완성된 조합 처리
        return;
    }

    for (int i = idx; i <= n; ++i) {
        if (visited[i]) continue;
        visited[i] = true;
        path.push_back(i);
        dfs(i + 1, visited, path);  // 복사된 상태로 다음 호출
        path.pop_back(); // 이 pop은 사실 의미 없음 (복사된 path니까)
    }
}


int main() {
    dfs(1); // 1부터 시작
}
