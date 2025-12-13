/*
2025/10/15
홍다윗

특정 시간대에 해당 하는 모든 것을 탐지해야한다.

구간이 1억으로 크고 미사일의 개수는 50만으로 완탐은 불가능

처음과 끝을 이용해서 모든 미사일을 요격해야 하므로

끝을 기준으로 해야한다.

해당 끝 구간을 기준으로 
1. 시작 지점이 걸치는 경우 pass
2. 걸치는 경우 삭제

간단하게 생각하면 벡터 3개를 만들어서 시작, 종료, vaild

삭제 하는 인덱스가 문제이다.

종료 시점을 기준으로 시작 시점을 구분해서 삭제를 해야한다.

맵을 2개 만들면 가능하기는 하다. 
map<e, idx> map<s, idx>

인덱스가 문제인데

종료 시점을 오름차순 기준으로 시작 시점이 미만인 미사일을 삭제하면 된다.


간단하게 생각해보면 벡터 2개를 만든다. <- 이게 완탐 하나를 기준으로 모든 것을 탐색
pair<e, s>, valid(n,true);
valid[0] = false;

기준이 변경되어야 한다.
그러면 pair<e,s>로 한다음
해당 순서대로 s를 따로 관리를 해서 idx를 찾는 방법?
seq
for(auto[e,s] :pair)
    seq = s;
    
그러면 종료 시점을 초과하는 첫 s의 idx를 찾는다 lower_bound <- 이것도 결국에는 완탐이다.
valid를 따로 만들어야하나? 그게 간편하기는 하다.
완탐을 하지 않으려면 확실히 삭제를 해야하며 이때 s 기준도 같이 삭제가 되어야 한다.

*/


#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<vector<int>> targets) {
    int answer = 0;
    int N = (int)targets.size();
    sort(targets.begin(), targets.end(), [](const vector<int> &A, const vector<int> &B){ return A[1] < B[1];});

    int maxT = 0;

    for(int i=0; i<N; ++i)
    {
        int s = targets[i][0], e = targets[i][1];

        if(maxT <= s)
        {
            answer++;
            maxT = e;
        }
    }


    return answer;
}