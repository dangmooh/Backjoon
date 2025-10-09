#include <iostream>
#include <string>

using namespace std;



int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL);

    int N;
    cin >> N;

    string s;
    cin >> s;

    int b = 0, e = 3 * N -1;
    char day[3] = {'B', 'L', 'D'};
    int target = 0;
    int count = 0;

    for(int i=0; i<=e; i++)
    {
        cout << s[i] << ' ';
    }

    while(b < e )
    {
        if(s[b] == day[target])
        {
            b++;
            count++;
            cout << s[b] << '\n';
        }
        else if(s[e] == day[target])
        {
            e--;
            count++;
            cout << s[e] << '\n';
        }
        else
        {
            break;
        }
        target = (target + 1) % 3;
    }

    cout << count << '\n';
    return 0;
}