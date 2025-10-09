#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <sstream>



using namespace std;


void pare_url(const string& url, string& domain, int& pid)
{
    size_t pos = url.rfind('/');
    domain = url.substr(0, pos);
    pid = stoi(url.substr(pos+1));
}

struct Task {
    int rt, st, p, pid;
    string url, domain;

    Task(int _rt, int _p, const string& _url) : rt(_rt), p(_p), url(_url) {
        st = -1;
        pare_url(url, domain, pid);
    }

    Task() = default;

    bool operator>(const Task& rhs) const {
        if(p != rhs.p) return p > rhs.p;
        return rt > rhs.rt;
    }
};

struct History {
    int st, et;
    History(int _st, int _et) : st(_st), et(_et) {}
    History() = default;

    bool is_valid_time(int ct) const {
        int gap = et - st;
        return st + 3LL*gap <= ct;
    }
};

int n;

unordered_map<string, priority_queue<Task, vector<Task>, greater<Task>>> domain_pqs;

unordered_map<string, History> domain_judge_history;

priority_queue<int, vector<int>, greater<int>> resting_judger_ids;

unordered_set<string> judging_domains;

unordered_map<int, Task> judgers;

unordered_set<string> waiting_urls;

void process_200(int t, int p, const string& url);

void process_100(int n_, const string& url)
{
    n =n_;
    for(int i=1; i<=n; ++i)
    {
        resting_judger_ids.push(i);
    }
    process_200(0,1,url);
}

void process_200(int t, int p, const string& url)
{
    if(waiting_urls.count(url)) return;
    Task task(t, p, url);
    domain_pqs[task.domain].push(task);

    waiting_urls.insert(url);
}
bool is_domain_judgeable(int cur_time, const string& domain) {
    // 조건 1: 해당 도메인이 현재 다른 채점기에서 채점 중이면 불가능합니다.
    if (judging_domains.count(domain)) {
        return false;
    }
    // 조건 2: 해당 도메인의 마지막 채점 기록을 확인하여 유예 기간인지 확인합니다.
    if (domain_judge_history.count(domain)) {
        History history = domain_judge_history[domain];
        if (!history.is_valid_time(cur_time)) {
            return false;
        }
    }
    return true;
}

// 명령어 300: 채점 시도
void process_300(int t) {
    // 쉬고 있는 채점기가 없으면 채점을 시작할 수 없습니다.
    if (resting_judger_ids.empty()) {
        return;
    }

    // 채점할 최적의 태스크를 찾습니다.
    Task best_task;
    bool found = false;

    // 모든 도메인의 대기 큐를 확인합니다.
    for (auto const& [domain, pq] : domain_pqs) {
        // 해당 도메인에 대기 중인 태스크가 없거나, 현재 채점 불가능한 도메인이면 건너뜁니다.
        if (pq.empty() || !is_domain_judgeable(t, domain)) {
            continue;
        }
        
        // 현재 도메인의 가장 우선순위 높은 태스크를 가져옵니다.
        Task current_task = pq.top();

        // 지금까지 찾은 최적의 태스크보다 우선순위가 높으면 교체합니다.
        if (!found || best_task > current_task) { // best_task > current_task 와 동일
             best_task = current_task;
             found = true;
        }
    }

    // 채점 가능한 태스크가 없는 경우 함수를 종료합니다.
    if (!found) {
        return;
    }
    
    // --- 채점 시작 처리 ---
    // 가장 번호가 작은 쉬는 채점기를 배정합니다.
    int j_id = resting_judger_ids.top();
    resting_judger_ids.pop();
    
    best_task.start_time = t;
    
    // 배정된 태스크를 해당 도메인의 대기 큐에서 제거합니다.
    domain_pqs[best_task.domain].pop();
    // 도메인을 '채점 중' 상태로 변경합니다.
    judging_domains.insert(best_task.domain);
    // 채점기 맵에 현재 채점하는 태스크를 기록합니다.
    judgers[j_id] = best_task;
    // 전체 대기 큐에서 URL을 제거합니다.
    waiting_urls.erase(best_task.url);
}

// 명령어 400: 채점 종료
void process_400(int t, int j_id) {
    // 해당 채점기가 채점 중이 아니었다면 무시합니다.
    if (judgers.find(j_id) == judgers.end()) {
        return;
    }
    
    Task task = judgers[j_id];
    
    // 채점 기록을 History 객체로 만들어 저장/갱신합니다.
    domain_judge_history[task.domain] = History(task.st, t);

    // 채점기를 다시 쉬는 상태로 만듭니다.
    resting_judger_ids.push(j_id);
    judging_domains.erase(task.domain);
    judgers.erase(j_id);
}
// 명령어 500: 채점 대기 큐 조회
void process_500(int t) {
    // waiting_urls 집합의 크기가 곧 대기 큐에 있는 태스크의 수입니다.
    cout << waiting_urls.size() << "\n";
}



int main()
{

    int Q; cin >> Q;

    while(Q--)
    {
        int req; cin >> req;

        switch(req) {
            case 100:
            cal_ready();
            break;

            case 200:
            cal_req();
            break;

            case 300:
            cal_try();
            break;
            
            case 400:
            cal_end();
            break;

            case 500:
            break;
        }
    }



    return 0;
}