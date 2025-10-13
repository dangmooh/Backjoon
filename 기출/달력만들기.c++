#include <iostream>
#include <string>

using namespace std;


int monthDay[12] = {31, 28, 31, 30, 31, 30, 31, 31,30, 31, 30, 31};
bool isLeap(int year)
{
    return (year %4 == 0);
}

string week[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

string getWeekday(int year, int month, int day)
{
    int baseYear = 2024;
    int days = 0;  

    for(int i=baseYear; i<year; ++i)
    {
        days += 365 + (isLeap(i) ? 1 : 0 );
    }

    for(int i=0; i<month - 1; ++i)
    {
        days += monthDay[i] + (i==1 && isLeap(i) ? 1 : 0);
    }

    days += day - 1;

    int idx = (1 + days) % 7;
    return week[idx];

}

int main()
{
    int y, m, d;
    cin >> y >> m >> d;

    cout << getWeekday(y, m, d) << '\n';

    return 0;
}