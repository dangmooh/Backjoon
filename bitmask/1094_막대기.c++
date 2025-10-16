#include <iostream>

using namespace std;


int main()
{
    int X;
    cin >> X;

    int total = 0;
    for (int i = 0; i <= 6; ++i)
    {
        if ((X >> i) & 1)
            total++;
    }

    cout << total << "\n";
    return 0;
}