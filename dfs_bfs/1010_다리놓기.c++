#include <iostream>
#include <vector>


using namespace std;


int main()
{
    int T; cin >> T;



    long long comb[31][31] = {0};
    for (int n = 0; n <= 30; ++n) {
        comb[n][0] = comb[n][n] = 1;
        for (int k = 1; k < n; ++k) {
            comb[n][k] = comb[n-1][k-1] + comb[n-1][k];
        }
    }

    int T; 
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;          // 조건: 0 < N ≤ M < 30
        cout << comb[M][N] << '\n';
    }
    return 0;


    return 0;
}