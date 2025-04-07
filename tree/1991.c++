#include <iostream>
<<<<<<< HEAD
#include <vector>
#include <queue>
=======
#include <map>
>>>>>>> 80171284c865a0d10641cf2fa91a6e1b1da7b549


using namespace std;

<<<<<<< HEAD
typedef struct _node{
    char left;
    char right;
} node_t;

vector<vector<node_t>> tree;

int main()
{

    int N;
    cin >> N;

    while(N--)
    {
        
    }

=======
map<char,pair<char,char>> tree;

void preorder(char node) {
    if (node == '.') return;
    cout << node;               // 루트 출력
    preorder(tree[node].first); // 왼쪽 서브트리 탐색
    preorder(tree[node].second); // 오른쪽 서브트리 탐색
}

void inorder(char node) {
    if (node == '.') return;
    inorder(tree[node].first);
    cout << node;
    inorder(tree[node].second);
}

void postorder(char node) {
    if (node == '.') return;
    postorder(tree[node].first);
    postorder(tree[node].second);
    cout << node;
}

int main()
{
    int N;
    cin >> N;

    for(int i=0; i<N; i++)
    {
        char s, l, r;
        cin >> s >> l >> r;

        tree[s] = {l, r};
    }


    preorder('A'); cout << "\n";
    inorder('A'); cout << "\n";
    postorder('A'); cout << "\n";

>>>>>>> 80171284c865a0d10641cf2fa91a6e1b1da7b549
    return 0;
}