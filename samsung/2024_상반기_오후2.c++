#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

constexpr int MAX_N = 100001;

int depth[MAX_N] = {0,};
vector<vector<int>> childs(MAX_N);
vector<int> roots;

struct Node {
    int id, p, c, max_depth;
    bool color[6] = {false,};
    Node(int _id, int _p, int _c, int _max_depth) : id(_id), p(_p), c(_c) {
        color[_c] = true;
        if(p == -1)
        {
            roots.push_back(id);
            max_depth = _max_depth;
            depth[id] = max_depth;
        }
        else 
        {
            childs[p].push_back(id);
            max_depth = depth[p] > _max_depth ? _max_depth : depth[p] - 1;
            depth[id] = max_depth;
        }
    }
};

Node node_list[MAX_N];
int Q;


void update_value(int m_id, int p_id)
{
    if(p_id == -1) return;

    for(int i=1; i<=5; ++i)
    {
        node_list[p_id].color[i] = (node_list[m_id].color[i] == true) ? true : node_list[p_id].color[i];
    }

    update_value(node_list[p_id].id, node_list[p_id].p);
}

void make_node()
{
    int m_id, p_id, color, max_depth;
    cin >> m_id >> p_id >> color >> max_depth;
    if(p_id != -1 && depth[p_id] < 2) return; //새로운 노드가 아니고 depth가 안된다면 추가 x
    Node node(m_id, p_id, color, max_depth); // 새로운 노드를 생성하고 

    node_list[m_id] = node;
    update_value(m_id, p_id);
}

void update_color(int m_id, int color)
{
    for(int child : childs[m_id])
    {
        node_list[child].c = color;
        for(int i=1; i<=5; ++i)
        {
            node_list[child].color[i] = (i == color) ? true : false;
        } 
        update_color(child, color);
    }
}

void change_color()
{
    int m_id, color;
    cin >> m_id >> color;
    int cur = node_list[m_id].c;
    node_list[m_id].color[cur] = false;
    node_list[m_id].color[color] = true;


    update_color(m_id, color);
    //update_value(m_id, node_list[m_id].p);

}

void search_color()
{
    int m_id; cin >> m_id;

    cout << node_list[m_id].c <<'\n';

}

int find_value(int m_id)
{
    int res = 0;
    for(int i=1; i<=5; ++i)
    {
        res += node_list[m_id].color[i] == true ? 1 : 0;
    }

    return res * res;
}

void dfs(int m_id, int &answer)
{
    for(int child : childs[m_id])
    {
        answer += find_value(child);
        dfs(child, answer);
    }
}

void search_value()
{
    int answer = 0;
    for(int root : roots)
    {
        for(int child : childs[root])
        {
            answer += find_value(child);
            dfs(child, answer);
        }
    }

    cout << answer << '\n';
}

int main()
{
    cin >> Q;

    while(Q--)
    {
        int q;
        cin >> q;
        
        switch(q)
        {
            case 100:
            make_node();
            break;

            case 200:
            change_color();
            break;

            case 300:
            search_color();
            break;

            case 400:
            search_value();
            break;
        }

    }


    return 0;
}