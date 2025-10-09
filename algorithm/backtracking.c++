/*

1. 기본 start와 depth
void dfs(int start, int depth) {
    if(depth == M) {
        for(int i=0; i<M; ++i) cout << seq[i] << ' ';
        cout << '\n';
        return;
    }
    for(int i=start; i<=N; ++i) {
        seq[depth] = i;
        dfs(i+1, depth+1);
    }
}

2. 중복허용

void dfs(int start, int depth)
{
    if(depth == M)
    {
        for(int i=0; i<M; ++i) cout << seq[i] << ' ';
        cout << '\n';
        return;
    }

    for(int i=start; i<N; ++i)
    {
        if(!visited[i])
        {
            visited[i] = true;
            seq[depth] = number[i];
            dfs(i+1, depth+1);
            visited[i] = false;
        }
    }
}
*/