#include <iostream>
#include <vector>
#include <set>


using namespace std;


using ll = long long;

int Q, N;
set<ll> house;
vector<ll> pos;
vector<char> alive;

void buildHouse(ll x)
{
    pos.push_back(x);
    alive.push_back(true);
    house.insert(x);
}

void buildTown(int N)
{
    pos.push_back(0);
    alive.push_back(false);

    while(N--)
    {
        ll x; cin >> x;
        buildHouse(x);
    }
}

void destoryHouse(int x)
{
    alive[x] = false;
    house.erase(pos[x]);
}

static inline bool canCover(const set<ll>& house, ll T, int r)
{
    if(house.empty()) return true;
    auto it = house.begin();
    for(int i=0; i<r && it != house.end(); ++i)
    {
        ll start = *it;
        ll limit = start + T;
        it = house.upper_bound(limit);
    }
    return it == house.end();
}

void searchHouse(int r)
{
    int m = (int)house.size();
    if(r>=m) 
    {
        cout << 0 <<'\n';
        return;
    }
    ll start = 0, end = *house.rbegin() -*house.begin();
    while(start < end)
    {
        ll mid = (start + end) >> 1;
        if(canCover(house, mid, r)) end = mid;
        else start = mid + 1;
    }
    cout << start << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> Q;

    for(int i=0; i<Q; ++i)
    {
        int command;
        cin >> command;

        switch(command) 
        {
            case 100 :
            cin >> N;
            buildTown(N);
            break;
            
            case 200:
            ll p;
            cin >> p;
            buildHouse(p);
            break;

            case 300:
            int q;
            cin >> q;
            destoryHouse(q);
            break;

            case 400:
            int r;
            cin >> r;
            searchHouse(r);
            break;

            default:
            cout << "error";
            break;
        }
    }

    return 0;
}