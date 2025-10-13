#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>


using namespace std;

struct Ship {
    int id, p, r;
    int last;
};

struct comp {
    bool operator()(const pair<int, int> &A, const pair<int, int> &B)
    {
        if(A.first != B.first)
        {
            return A.first > B.first;
        }
        else
        {
            return A.second < B.second;
        }
    }
};

unordered_map<int, Ship> um;
priority_queue<pair<int, int>, vector<pair<int, int>>, comp> pq;

void placeShip()
{
    Ship ship;  
    cin >> ship.id >> ship.p >> ship.r;
    ship.last = 0;
    um[ship.id] = ship;
    pq.push({ship.p, ship.id});
}

void replaceShip(int target)
{
    int np; 
    cin >> np;
    um[target].p = np;
    pq.push({np, target});
}

void attack(int t)
{
    vector<int> attackShips;
    vector<pair<int,int>> readyShips;
    long long damage = 0;

    while(!pq.empty() && attackShips.size() == 5)
    {
        pair<int, int> top = pq.top(); pq.pop();
        Ship &cur = um[top.second];

        if(top.first != cur.p) continue;
        
        if(cur.last + cur.r > t)
        {
            readyShips.push_back(top);
            continue;
        }

        damage += cur.p;
        cur.last = t;
        attackShips.push_back(top.second);
    }

    for(const auto &p : readyShips)
    {
        pq.push(p);
    }

    for(int ship : attackShips)
    {
        pq.push({um[ship].p, ship});
    }

    cout << damage << " " << attackShips.size();
    for(int ship : attackShips)
    {
        cout << " " << ship;
    }
    cout << "\n";

    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for(int i=1; i<=T; ++i)
    {
        int q; cin >> q;
        
        if(q==100)
        {
            int N;
            cin >> N;

            for(int i=0; i<N; ++i)
            {
                placeShip();
            }
        }
        else if(q==200)
        {
            placeShip();
        }
        else if(q==300)
        {
            int id; cin >> id;
            replaceShip(id);
        }
        else
        {
            attack(i);
        }
    }

    return 0;
}