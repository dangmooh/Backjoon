/*

시작한 시간이 되면 시작을 해야한다.
-> 동기화 문제
진행중이던 과제를 멈추고 새로운 과제 시작
-> 저장 기능
진행중이던 과제를 끝냈을 때,가장 최근에 멈춰둔 과제 부터 이어서 진행
-> 순서 
과제를 끝낸 순서대로 이름을 배역에 담아 return

plans = [name, start, playtime] 길이는 1000보다 작으므로 완탐도 가능
name은 알파벳 소문자 중복 x
start hh:mm의 형태 중복 x
playtime 단위는 분 100보다 작다 

스케줄링 문제
last in first out 이므로 stack 형식이다.

해결책

1. 시작하는 순서 정렬
2. 동기화를 위한 시간 변수  
t = 0;
t = current start time;
while()
if next start time >= t + current playtime;  현재 과제 종료
    if stack is not empty;                   남은 과제가 있다면
        t += current playtime;
        current = stack top;                 남은 과제 꺼내기

        while (stack is not empty && t + current playtime < next start time)남은 과제가 없거나 새로운 과제 시작 시간보다 클때까지
            if(t += )
            
    else                                     남은 과제가 없다면
        current = second;                    새로운 과제 실행
        t = next start time;
else 새로운 과제 끼어듬
    current play time -= (next start time - t);진행중이던 과제의 playtime 설정
    stack push current;                     stack에 넣기
    t = next start time;                    새로운 과제 실행



*/


#include <string>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

struct Plan {
    string name;
    int start;
    int remain;
};


int toMinute(const string &t) {
    int h = stoi(t.substr(0,2));
    int m = stoi(t.substr(3,2));
    return h * 60 + m;
}

vector<string> solution(vector<vector<string>> plans) {
    vector<string> answer;

    int n = plans.size();
    vector<Plan> v;
    v.reserve(n);

    for (auto &p : plans) {
        Plan cur;
        cur.name = p[0];
        cur.start = toMinute(p[1]);
        cur.remain = stoi(p[2]);
        v.push_back(cur);
    }

    sort(v.begin(), v.end(), [](const Plan &A, const Plan &B){return A.start < B.start;});
    stack<Plan> st;

    for(int i=0; i<n; ++i) {
        int curStart = v[i].start;
        int curRemain = v[i].remain;
        int nextStart = (i +1 < n) ? v[i+1].start : 24 *60;
        int available = nextStart - curStart;

        if(curRemain <= available){
            available -= curRemain;
            answer.push_back(v[i].name);

            while(available > 0 && !st.empty())
            {
                Plan top = st.top();
                st.pop();
                if(top.remain <= available)
                {
                    available -= top.remain;
                    answer.push_back(top.name);
                }
                else {
                    top.remain -= available;
                    available = 0;
                    st.push(top);
                }
            }
        }
        else {
            v[i].remain = curRemain - available;
            st.push(v[i]);
        }
    }

    while(!st.empty())
    {
        answer.push_back(st.top().name);
        st.pop();
    }

    return answer;
}