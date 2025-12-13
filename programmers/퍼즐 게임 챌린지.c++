#include <string>
#include <vector>

using namespace std;

vector<int> d; 
vector<int> t;

bool check(int level, long long limit)
{
    long long total = 0;

    for(int i=0; i<(int)d.size(); ++i)
    {
        int tmp = d[i] - level;
        if(tmp <= 0)
        {
            total += t[i];
        }
        else
        {
            if(i == 0)
            {
                total += t[i] * (tmp + 1);
            }
            else
            {
                total += t[i] * (tmp+1) + t[i-1]*(tmp); 
            }
        }
        
    }
    if(limit  >= total)
    {
        return true;
    }
    return false;
}

int solution(vector<int> diffs, vector<int> times, long long limit) {
    int answer = 0;
    
    int maxl = 0;
    for(int diff : diffs)
    {
        maxl = max(maxl, diff);
    }
    
    int l = 1, r = maxl;
    
    int mid;
    t = times;
    d = diffs;
    
    while(l <= r) // 닫힌 구간 1~maxl까지 만족하는 level의 최소 값을 찾아야 하므로 
    {
        mid = (l + r) >> 1;
        if(check(mid, limit)) // 만족하면 r의 값을 줄인다. 즉 최소 값을 찾기 위해서 범위를 줄인다
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    
    
    return l;
}








