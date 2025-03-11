#include <iostream>
#include <map>


using namespace std;

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

    return 0;
}