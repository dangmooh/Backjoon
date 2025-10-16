#include <iostream>
#include <vector>
#include <algorithm>
#include <set>


using namespace std;

set<int> house;
vector<int> pos;
vector<bool> alive;

void make_house(int c)
{
    while(c--)
    {
        int x; cin >> x;
        house.insert(x);
        pos.push_back(x);
        alive.push_back(true);
    }
}

void cursh_house()
{
    int q; cin >> q;
    house.erase(pos[q-1]);
    alive[q-1] = false;
}

bool canSearch(int r, int mid)
{
    auto start = house.begin();
    while(r--)
    {
        if(start == house.end()) break;
        int nxt = *start + mid;
        start = lower_bound(house.begin(), house.end(), nxt);
    }

    return start == house.end();
}

void search_house()
{
    int r; cin >> r;
    
    int s = 0, l = (*house.rbegin() - *house.begin()); // binary search
    int mid = 0;

    while(s < l)
    {
        mid = (s + l) >> 1;
        if(canSearch(r, mid))
        {
            l = mid ;
        }
        else
        {
            s = mid + 1;
        }
    }

    cout << mid << "\n";
}

int main()
{

    int Q; cin >> Q;

    while(Q--)
    {
        int q;
        cin >> q;

        if(q==100)
        {
            int N;
            make_house(N);
        }
        else if(q==200)
        {
            make_house(1);
        }
        else if(q==300)
        {
            crush_house();
        }
        else if(q==400)
        {
            search_house();
        }
        else
        {

        }
    }

    return 0;
}