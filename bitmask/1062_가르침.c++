#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;


vector<int> word;
int answer = 0;
vector<int> candLetters;
int N, K;

int countReadable(int mask)
{
    int cnt = 0;
    for (int m : word)
    {
        if ((m & ~mask) == 0) cnt++;
    }
    return cnt;
}

void dfs(int idx, int picked, int learnMask)
{

    if (picked == K-5)
    {
        answer = max(answer, countReadable(learnMask));
        return;
    }
    if(idx == (int)candLetters.size()) return;

    int c = candLetters[idx];

    dfs(idx+1, picked+1, learnMask | (1 << c));
    dfs(idx+1, picked, learnMask);
}

int main()
{
    cin >> N >> K;

    if (K < 5)
    {
        cout << 0 << "\n";
    }
    else if (K == 26)
    {
        cout << N << "\n";
    }
    else
    {
        int candMask = 0;
        int baseMask = 0;
        for(char ch : string("antic")) baseMask |= (1<<(ch-'a'));

        for (int i = 0; i < N; ++i)
        {
            string s;
            cin >> s;
            int mask = 0;
            for (auto ch : s) { mask |= (1 << (ch - 'a')); }

            int count = 0;
            for (int i = 0; i < 26; ++i)
            {
                if ((mask >> i) & 1) count++;
            }

            if (count <= K)
            {
                candMask |= (mask & ~baseMask);
                word.push_back(mask);
            }
        }

        for (int i = 0; i < 26; ++i)
        {
            if ((candMask >> i) & 1) candLetters.push_back(i);
        }

        if ((int)candLetters.size() <= K - 5)
        {
            cout << (int)word.size() << "\n";
            return 0;
        }

        dfs(0, 0, baseMask);

        cout << answer << "\n";
    }


    return 0;
}