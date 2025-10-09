/*
1) MAP이란? 
map은 각 노드가 key와 value 쌍으로 이루어진 트리입니다.  
중복을 허용하지 않습니다.
따라서 map은 first, second가 있는 pair 객체로 저장되는 데 first- key로 second- value로 저장됩니다. 
C++의 map의 내부 구현은 검색, 삽입, 삭제가 O(logn) 인 레드블랙트리로 구성되어 있습니다.

2) MAP 기본 형태
map <key, value> map1;

3) MAP 정렬
map은 자료를 저장할때 내부에서 자동으로 정렬합니다.
map은 key를 기준으로 정렬하며 오름차순으로 정렬합니다. 
만약 내림차순으로 정렬하고 싶은 경우와 같이 사용하면 됩니다.
map <int, int, greater> map1; 
*/

#include <iostream>
#include <map>

using namespace std;

map<char, pair<char,char>> tree;

void preorder(char node)
{
    if(node == '.') return;
    cout << node;
    preorder(tree[node].first);
    preorder(tree[node].second);
}

void postorder(char node)
{
    if(node == '.') return;
    postorder(tree[node].first);
    postorder(tree[node].second);
}
int main()
{
    int N;
    cin >> N;
    
    for(int i=0; i<N; ++i)
    {
        char s, l, r; cin >> s >> l >> r;
        tree[s] = {l, r};
    }
    preorder('A'); cout << '\n';
    postorder('A'); cout << '\n';
}