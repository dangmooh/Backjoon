/*

knapsack problem

1. 2차원 배열로 해결한다.

    for(int i=1; i<=N; ++i) {
        for(int w=0; w<=K; ++w) {
            dp[i][w] = dp[i-1][w]; // 안 넣는 경우
            if(w >= W[i]) // 넣는 경우
                dp[i][w] = max(dp[i][w], dp[i-1][w-W[i]] + V[i]);
        }
    }
2. 1차원 배열로 해결한다.

    for(int i=0; i<N; ++i) {
        int W, V; cin >> W >> V;
        for(int w=K; w>=W; --w) // 중복으로 넣는 것을 방지하기 위해서 뒤에서 나아간다.
            dp[w] = max(dp[w], dp[w-W] + V);
    }

*/