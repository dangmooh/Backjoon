#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>


using namespace std;

int N, Q, answer;
vector<int> message, authority;
vector<vector<int>> child;
vector<bool> avail;


void prepare()
{
    for(int i=1; i<=N; ++i)
    {
        cin >> message[i];
        child[message[i]][1]++;
    }

    for(int i=1; i<=N; ++i)
    {
        cin >> authority[i];
    }
}

void toggle()
{
    int c;
    cin >> c;
    avail[c] = !avail[c];
}

void power_change()
{
    int c, power;
    cin >> c >> power;
    authority[c] = power;
}


void parent_change()
{
    int m1, m2;
    cin >> m1 >> m2;
    int p1 = message[m1], p2 = message[m2];

    if(p1 == p2) return;

    for(int &x : child[p1])
    {
        if(x == m1) x = m2; 
    }

    for(int &x : child[p2])
    {
        if(x == m2) x = m1; 
    }

    message[m1] = p2;
    message[m2] = p1;
}

void dfs(int target, int depth)
{
    int power = authority[target];
    if(power < depth) answer--;
    answer++;

    for(int c1 : child[target])
    {
        if(avail[c1])
        {
            //cout << " target : " << target << ' ';

            dfs(c1, depth + 1);
        }
    }
}

void search_message()
{
    int c;
    cin >> c;
    answer = 0;

    for(int c1 : child[c])
    {
        if(avail[c1])
        {
            dfs(c1, 1);
        }
    }


    //cout << '\n';
    //cout << "=================================" << '\n';
    cout << answer << '\n';

}

int main()
{
    cin >> N >> Q;

    message.resize(N+1, 0); authority.resize(N+1, 0); avail.resize(N+1, true);
    child.resize(N+1, vector<int>(21,0));
    while(Q--)
    {
        int q;
        cin >> q;
        switch(q)
        {
            case 100:
            prepare();
            break;

            case 200:
            toggle();
            break;

            case 300:
            power_change();
            break;

            case 400:
            parent_change();
            break;

            case 500:
            search_message();
            break;
        }
    }


    return 0;
}