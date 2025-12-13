/*

시뮬레이션 경로 생성 시간 동기화

여러 객체가 동일한 시간에 움직이게 된다.

따라서 각 객체가 시간에 따라 어떻게 움직이는 지를 판단해야한다.

중요한 것은 모든 객체는 같은 시간이라는 기준점으로 서로 영향을 주어선 안된다.

움직임을 동시에 하며 모두 움직인 후 충돌 감지

충돌 감지 방법
여러 객체가 

*/


#include <string>
#include <vector>
#include <map>
using namespace std;

int solution(vector<vector<int>> points, vector<vector<int>> routes) {
    int answer = 0;
    
    int s = (int)routes.size();
    vector<int> time(s); 
    vector<vector<pair<int,int>>> robots(s, vector<pair<int,int>>(20000));
    int maxT = 0;
    for(int i=0; i<s; ++i)
    {
        int s = routes[i][0] - 1;
        int r1 = points[s][0], c1 = points[s][1];
        int t=0;
        robots[i][t] = make_pair(r1, c1);

        for(int j=1; j<(int)routes[i].size(); ++j)
        {
            int nxt = routes[i][j] - 1;
            int r2 = points[nxt][0], c2 = points[nxt][1];
            int dr = (r1 - r2 > 0) ? -1 : 1, dc = (c1 - c2 > 0) ? -1 : 1;

            while(r1 != r2)
            {
                t++;
                r1 += dr;
                robots[i][t] = make_pair(r1, c1);
            }

            while(c1 != c2)
            {
                t++;
                c1 += dc;
                robots[i][t] = make_pair(r1, c1);
            }
        }
        time[i] = t;
        maxT = max(maxT, t);
    }
    

    int coll = 0;
    for(int i=0; i<=maxT; ++i)
    {
        map<pair<int,int>, int> cnt;
        for(int j=0; j<s; ++j)
        {
            if(i<=time[j]) cnt[robots[j][i]]++;
        }
        for(auto& [pos, num] : cnt)
        {
            if(num > 1) coll++;
        }
    }
    
    answer = coll;

    return answer;
}