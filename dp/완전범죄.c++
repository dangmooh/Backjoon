#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


int solution_minA(const vector<pair<int,int>>& info, int n, int m) {
    int N = info.size();
    int sumA_total = 0;
    int sumB_total = 0;
    for (auto &p : info) {
        sumA_total += p.first;
        sumB_total += p.second;
    }  
    // bounds
    int maxA = sumA_total;
    int maxB = sumB_total;
    // dp[sb][sa] : 가능한지 (sb: sum of b's for items assigned to A, sa: sum of a's for items assigned to A)
    vector<vector<char>> dp(maxB + 1, vector<char>(maxA + 1, 0));
    dp[0][0] = 1;

    for (int i = 0; i < N; ++i) {
        int a = info[i].first;
        int b = info[i].second;
        // in-place update: iterate descending to avoid reuse in same iteration
        for (int sb = maxB - b; sb >= 0; --sb) {
            for (int sa = maxA - a; sa >= 0; --sa) {
                if (dp[sb][sa]) dp[sb + b][sa + a] = 1;
            }
        }
    }

    int best = INT_MAX;
    // need sb > sumB_total - m  (i.e., sb >= (sumB_total - m + 1))
    int need_sb_min = sumB_total - m + 1;
    if (need_sb_min < 0) need_sb_min = 0; // if m > sumB_total, requirement is sb >=0 (always true)

    for (int sb = need_sb_min; sb <= maxB; ++sb) {
        for (int sa = 0; sa <= maxA; ++sa) {
            if (!dp[sb][sa]) continue;
            if (sa < n) { // A not caught
                // B not caught is guaranteed by sb >= need_sb_min
                best = min(best, sa);
            }
        }
    }
    if (best == INT_MAX) return -1;
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;
    vector<pair<int,int>> info(N);
    for (int i = 0; i < N; ++i) cin >> info[i].first >> info[i].second;
    int n, m; cin >> n >> m;

    int ans = solution_minA(info, n, m);
    cout << ans << "\n";
    return 0;
}