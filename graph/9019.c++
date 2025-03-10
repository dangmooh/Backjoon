#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int D(int n) { return (2*n) % 10000;}
int S(int n) { return (n==0) ? 9999 : n - 1;}
int L(int n) { return (n%1000) * 10 + n /1000;}
int R(int n) { return (n%10) * 1000 + n / 10;}

int main()
{

    int T;
    cin >> T;

    while(T--)
    {
        int A, B;
        cin >> A >> B;

        vector<bool> visited(10000, false);
        queue<pair<int, string>> q;
        q.push({A, ""});
        visited[A] = true;

        while(!q.empty())
        {
            int cur = q.front().first;
            string path = q.front().second;
            q.pop();

            if(cur == B)
            {
                cout << path << '\n';
                break;
            }

            int nextVals[4] = {D(cur), S(cur), L(cur), R(cur)};
            char commands[4] = {'D', 'S', 'L', 'R'};

            for (int i=0; i<4; i++)
            {
                int next = nextVals[i];
                if(!visited[next])
                {
                    visited[next] = true;
                    q.push({next, path + commands[i]});
                }
            }
        }
    }

    return 0;
}