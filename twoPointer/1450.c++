#include <iostream>

using namespace std;

typedef long long ll;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    ll C;
    cin >> N >> C;                  // 1) N, C 입력 받기

    vector<ll> w(N);
    for(int i = 0; i < N; i++){
        cin >> w[i];               // 2) 각 물건의 무게 w[i]를 입력 받기
    }

    // 3) 물건을 두 그룹으로 분할: 앞쪽 절반(A), 뒤쪽 절반(B)
    int mid = N / 2;
    vector<ll> A, B;               // A와 B 그룹의 부분집합 합을 저장할 벡터

    // 4) A 그룹의 부분집합 합 모두 구하기
    //    (0 ~ mid-1까지의 물건들로 만들 수 있는 모든 부분집합)
    for(int i = 0; i < (1 << mid); i++){
        ll sumA = 0;
        for(int j = 0; j < mid; j++){
            // i의 j번째 비트가 1이면 j번째 물건을 포함
            if(i & (1 << j)) sumA += w[j];
        }
        A.push_back(sumA);
    }

    // 5) B 그룹의 부분집합 합 모두 구하기
    //    (mid ~ N-1까지의 물건들로 만들 수 있는 모든 부분집합)
    for(int i = 0; i < (1 << (N - mid)); i++){
        ll sumB = 0;
        for(int j = 0; j < (N - mid); j++){
            if(i & (1 << j)) sumB += w[mid + j];
        }
        B.push_back(sumB);
    }

    // 6) B 그룹 부분집합 합 리스트를 정렬
    sort(B.begin(), B.end());

    // 7) A 그룹의 각 합에 대해
    //    B 그룹에서 (C - 해당 A 그룹 합) 이하인 값들의 개수를
    //    이진 탐색으로 찾아 전체 개수를 누적
    long long answer = 0;
    for(ll valA : A){
        if(valA <= C){
            ll remain = C - valA;
            // upper_bound: remain보다 큰 값이 처음 나타나는 위치
            // => remain 이하인 값들의 개수가 (pos - B.begin())
            auto pos = upper_bound(B.begin(), B.end(), remain);
            answer += (pos - B.begin());
        }
    }

    // 8) 최종 결과 출력
    cout << answer << "\n";
    return 0;
}
