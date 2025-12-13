/*
2025.12.11

최소한의 피로도로 광물을 캔다

각 곡괭이는 종류에 상관없이 광물 5개를 캔 후 사용불가
한 번 선택한 곡괭이는 사용불가까지 사용
광물은 주어진 순서대로 가능
모든 광물을 캐거나 더이상 사용할 곡괭이가 없을 때까지
최소한의 피로도를 return

5개씩 묶음을 지어서 돌 곡괭이의 피로도 순으로 정렬을 한 다음에 
가장 피로도가 적은 곳은 돌 그다음은 철 다이아 순으로 계산한다.


*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Group {
    int dia = 0;
    int iron = 0;
    int stone = 0;
    int weight = 0;
};

int solution(vector<int> picks, vector<string> minerals) {
    int answer = 0;

    int num = (minerals.size() + 4) / 5;
    int total = picks[0] + picks[1] + picks[2];
    int limit = min((int)minerals.size(), total * 5);

    vector<Group> groups;
    groups.reserve((limit + 4) / 5);

    for(int i=0; i<limit; ++i)
    {
        if (i%5 == 0) groups.push_back(Group());
        Group &g = groups.back();

        if(minerals[i] == "diamond")
        {
            g.dia++;
        }
        else if(minerals[i] == "iron")
        {
            g.iron++;
        }
        else
        {
            g.stone++;
        }
    }

    for(auto &g : groups)
    {
        g.weight = 25 * g.dia + 5 *g.iron + g.stone;
    }

    sort(groups.begin(), groups.end(),
        [](const Group &A, const Group &B){ return A.weight > B.weight;});

    for(auto &g : groups)
    {
        int pick = -1;
        if(picks[0] > 0)
        {
            pick = 0;
            picks[0]--;
        }
        else if(picks[1]>0)
        {
            pick = 1;
            picks[1]--;
        }
        else if(picks[2]>0)
        {
            pick = 2;
            picks[2]--;
        }
        else
        {
            break;
        }

        if(pick==0)
        {
            answer += g.dia + g.iron + g.stone;
        }
        else if(pick==1)
        {
            answer += 5*g.dia + g.iron + g.stone;
        }
        else
        {
            answer += 25*g.dia + 5*g.iron + g.stone;
        }
    }



    return answer;
}