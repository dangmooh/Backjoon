#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> inorder, postorder;
unordered_map<int, int> inorder_idx;
int N;

void solve(int in_start, int in_end, int post_start, int post_end)
{
    if(in_start > in_end || post_start > post_end) return;

    int root = postorder[post_end];
    cout << root << " ";

    int root_index = inorder_idx[root];
    int left_size = root_index - in_start;

    solve(in_start, root_index -1, post_start, post_start +left_size - 1);
    solve(root_index + 1, in_end, post_start + left_size, post_end -1);
}

int main()
{
    cin >> N;
    inorder.resize(N);
    postorder.resize(N);

    for(int i=0; i<N; i++)
    {
        cin >> inorder[i];
        inorder_idx[inorder[i]] = i;
    }

    for(int i=0; i<N; i++)
    {
        cin >> postorder[i];
    }

    solve(0, N-1, 0, N-1);
    cout << '\n';

    return 0;
}