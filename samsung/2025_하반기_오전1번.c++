#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>



using namespace std;

int N, M;
const int dx[3] = {0, -1, 1};
const int dy[3] = {1, 0, 0};

struct Baggage {
    int k, h, w, r, c;
    bool removed;
};


vector<vector<int>> board;
vector<Baggage> baggages;

inline bool inRange(int r, int c)
{
    return r>=0 && r<N && c>=0 && c<N;
}

bool canMove(int h, int w, int c, int r, int d)
{
    int r1 = (d==0) ? r + h -1 : r, c1 = (d==2) ? c + w -1 : c, r2 = r + h -1, c2 = (d==1) ? c : c + w -1;

    for(int i=r1; i<=r2; ++i)
    {
        for(int j=c1; j<=c2; ++j)
        {
            if(!inRange(i,j) || board[i][j] != 0) return false;
        }
    }
    return true;
}

pair<int,int> moveBox(int h, int w, int r, int c, int d)
{
    int rr = r, cc = c;

    while(true)
    {
        int nr = rr + dy[d], nc = cc + dx[d];
        if(canMove(h, w, nr, nc, d))
        {
            rr = nr; cc = nc;
        }
        else
        {
            break;
        }
    }

    return {rr, cc};
}

void placeBaggage(Baggage &b)
{
    b.removed = false;
    for(int i=b.r; i<b.r+b.h; ++i)
    {
        for(int j=b.c; j<b.c+b.w; ++j)
        {
            board[i][j] = b.k;
        }
    }
}

void removeBaggage(Baggage &b)
{
    b.removed = true;
    for(int i=b.r; i<b.r+b.h; ++i)
    {
        for(int j=b.c; j<b.c+b.w; ++j)
        {
            board[i][j] = 0;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M;
    board.assign(N, vector<int>(N, 0));
    baggages.reserve(M);

    for(int i=0; i<M; ++i)
    {
        int k, h, w, c;
        cin >> k >> h >> w >> c;

        auto [rr, cc] = moveBox(h, w, 0, c-1, 0);

        Baggage baggage = {k, h, w, rr, cc, false};
        placeBaggage(baggage);
        baggages.push_back(baggage);
    }


    for(int i=0; i<M; ++i)
    {
        int d = (i%2 == 0) ? 1 : 2;
        sort(baggages.begin(), baggages.end(), [](const Baggage &A, const Baggage &B){ return A.k < B.k; });

        for(auto &b : baggages)
        {
            if(b.removed) continue;

            auto [r, c] = moveBox(b.h, b.w, b.r, b.c, d);
            if((d == 1 && c==0) || (d==2 && c + b.w == N))
            {
                removeBaggage(b);
                cout << b.k << "\n";
                break;
            }
        }

        sort(baggages.begin(), baggages.end(), [](const Baggage &A, const Baggage &B){ return A.r+A.h > B.r + B.h; });

        for(auto &b : baggages)
        {
            if(b.removed) continue;

            removeBaggage(b);
            auto [r, c] = moveBox(b.h, b.w, b.r, b.c, 0);
            b.r = r; b.c = c;
            placeBaggage(b);
        }
    }


    return 0;
}
