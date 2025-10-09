#include <bits/stdc++.h>
using namespace std;

// -------- Fenwick (Max) with rollback --------
struct FenwickMaxRollback {
    int N;                         // 최대 높이 (1e6)
    vector<int> bit;               // 1-indexed
    vector<pair<int,int>> mods;    // (idx, old_value) 변경 기록 스택

    FenwickMaxRollback(int N_=1'000'001) : N(N_), bit(N_+2, 0) {}

    // prefix max [1..x]
    int query(int x) const {
        int res = 0;
        for (; x > 0; x -= (x & -x)) res = max(res, bit[x]);
        return res;
    }

    // point update: bit[pos] = max(bit[pos], val)
    // 변경된 노드만 push하여 롤백 가능하게 함
    void update(int pos, int val) {
        for (int i = pos; i <= N; i += (i & -i)) {
            if (bit[i] < val) {
                mods.emplace_back(i, bit[i]);
                bit[i] = val;
            }
        }
    }

    // 현재 기록된 변경을 size == checkpoint 가 될 때까지 되돌린다
    void rollback(size_t checkpoint) {
        while (mods.size() > checkpoint) {
            auto [i, oldv] = mods.back();
            mods.pop_back();
            bit[i] = oldv;
        }
    }
};

// -------- 메인 로직 --------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const long long W = 1'000'000LL;      // 이동/케이블 가중치

    int Q; 
    if (!(cin >> Q)) return 0;

    // 상태
    FenwickMaxRollback fw(1'000'001);     // 높이 <= 1e6
    vector<int> H;                        // 높이 배열
    vector<int> DP;                       // LIS_end_at[i]
    vector<size_t> chk;                   // 각 원소가 추가될 때 fenwick mods의 크기(롤백 체크포인트)

    // 길이별 마지막 높이 멀티셋 (LIS 길이 l을 가진 원소들의 '마지막 높이'들)
    // 길이는 1..L 까지 사용. 필요 시 확장.
    vector<multiset<int>> bucket;
    int L = 0;                            // 전체 LIS 길이

    auto ensure_bucket = [&](int need){
        if ((int)bucket.size() <= need) bucket.resize(need+1);
    };

    auto append_height = [&](int h) {
        // 기록용
        size_t cp = fw.mods.size();

        // LIS_end_at 계산: 1 + max_{height < h} DP
        int best = fw.query(h-1);
        int len  = best + 1;

        fw.update(h, len);

        // 상태 반영
        H.push_back(h);
        DP.push_back(len);
        chk.push_back(cp);

        ensure_bucket(len);
        bucket[len].insert(h);
        L = max(L, len);
    };

    auto pop_back_height = [&](){
        // 현재 배열의 마지막 원소 제거
        int h  = H.back();   H.pop_back();
        int ln = DP.back();  DP.pop_back();
        size_t cp = chk.back(); chk.pop_back();

        // 길이 버킷에서 하나 제거
        auto it = bucket[ln].find(h);
        if (it != bucket[ln].end()) bucket[ln].erase(it);

        // Fenwick 롤백
        fw.rollback(cp);

        // 전체 LIS 길이 조정
        while (L > 0 && bucket[L].empty()) --L;
    };

    auto answer_query = [&](int m_index){   // m_index: 1-indexed
        int idx = m_index - 1;              // 내부 0-index
        int moves = DP[idx] + L - 1;        // (dp[m]-1) + 1 + (L-1)
        // L은 항상 >=1 이므로 bucket[L]은 비어있지 않음
        int lastH = *bucket[L].rbegin();    // 최장 증가수열들의 마지막 높이 중 최대
        long long score = W * (long long)moves + (long long)lastH;
        cout << score << '\n';
    };

    // 질의 처리
    for (int qi = 0; qi < Q; ++qi) {
        int op; cin >> op;
        if (op == 100) {
            int n; cin >> n;
            H.reserve(H.size()+n);
            DP.reserve(DP.size()+n);
            chk.reserve(chk.size()+n);
            for (int i = 0; i < n; ++i) {
                int h; cin >> h;
                append_height(h);
            }
        } else if (op == 200) {
            int h; cin >> h;
            append_height(h);
        } else if (op == 300) {
            // 가장 오른쪽(마지막) 산을 제거
            pop_back_height();
        } else if (op == 400) {
            int m; cin >> m;   // 왼쪽에서 m번째 산에서 케이블을 탄다고 가정
            answer_query(m);
        }
    }

    return 0;
}
