
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>


using namespace std;

struct Rabbit {
    int pid, x, y, cnt;
    Rabbit(int _pid) 
        : pid(_pid), x(1), y(1), cnt(0) {}
};


struct compare {
    bool operator()(Rabbit &a, Rabbit &b)
    {
        if(a.cnt != b.cnt) 
            return a.cnt > b.cnt;
        int sumA = a.x + a.y, sumB = b.x + b.y;
        if(sumA != sumB)
            return sumA > sumB;
        if(a.y != b.y)
            return a.y > b.y;     
        if(a.x != b.x)
            return a.x > b.x;
        return  a.pid > b.pid;  
    }
};

struct compare2 {
    bool operator()(pair<int,int> &a, pair<int,int> &b)
    {
        int sumA = a.first + a.second, sumB = b.first + b.second;
        if(sumA != sumB)
            return sumA < sumB;         // 합이 큰 것이 우선됨
        if(a.second != b.second)
            return a.second < b.second; // 두번째 값이 큰 것이 우선됨
        return a.first < b.first;  
    }
};

struct compare3 {
    bool operator()(Rabbit &a, Rabbit &b)
    {
        int sumA = a.x + a.y, sumB = b.x + b.y;
        if(sumA != sumB)
            return sumA < sumB;
        if(a.y != b.y)
            return a.y < b.y;     
        if(a.x != b.x)
            return a.x < b.x;
        return  a.pid < b.pid;   
    }
};

priority_queue<Rabbit, vector<Rabbit>, compare> select_pq;
priority_queue<int> score_pq;
int score[10000001];
long long dist[10000001];
long long total = 0;
pair<int,int> dd[4] = {{0,1},{-1,0},{0,-1},{1,0}};

int N, M, P;
int rX, rY;

void printRabbit()
{
    while(!select_pq.empty())
    {
        Rabbit r = select_pq.top();
        select_pq.pop();

        cout << "rabbit pid: " <<r.pid << "rabbit d: " << dist[r.pid] << "rabbit x: " << r.x << "rabbit y: " << r.y <<"\n"; 
    }
}

void initStart()
{
    cin >> N >> M >> P;
    
    while(P--)
    {
        int pid, d;
        cin >> pid >> d;
        Rabbit rabbit(pid);
        dist[pid] = d;
        select_pq.push(rabbit);
    }
    //printRabbit();
}

bool canMove(int x, int y)
{
    return ((x > 0) && (y>0)&& (x<=N) && (y<=M));
}


pair<int,int> move(int x, int y, int dir, int num)
{
    if(dir == 0 || dir == 2) {
        int M_range = M;  // y 좌표의 범위
        if(M_range == 1) return {x,y}; // 열이 하나뿐이면 이동 없음
        // 현재 y를 0-indexed로 변환
        int start = y - 1;
        int period = 2 * (M_range - 1);
        int newPos;
        if(dir == 0) { // 동쪽: 증가
            newPos = (start + num) % period;
        } else {       // 서쪽: 감소
            newPos = (start - num) % period;
            if(newPos < 0) newPos += period;
        }
        // 반사 효과: newPos가 M_range 이상이면 반전하여 계산
        int finalY = (newPos >= M_range ? period - newPos : newPos) + 1;
        return {x, finalY};
    }
    else { // 수직 이동: dir == 1 (북쪽) 또는 dir == 3 (남쪽)
        int N_range = N;  // x 좌표의 범위
        if(N_range == 1) return {x,y}; // 행이 하나뿐이면 이동 없음
        int start = x - 1;
        int period = 2 * (N_range - 1);
        int newPos;
        if(dir == 3) { // 남쪽: 증가
            newPos = (start + num) % period;
        } else {       // 북쪽: 감소
            newPos = (start - num) % period;
            if(newPos < 0) newPos += period;
        }
        int finalX = (newPos >= N_range ? period - newPos : newPos) + 1;
        return {finalX, y};
    }
}


pair<int,int> selectMove(Rabbit &rabbit)
{

    priority_queue<pair<int,int>, vector<pair<int,int>>, compare2> next_pq;

    for(int i=0; i<4; i++)
    {
        pair<int,int> cand = move(rabbit.x,rabbit.y,i, dist[rabbit.pid]);
        next_pq.push(cand);
    }

    rabbit.cnt++;

    return next_pq.top();
}

void startRace()
{
    int K, S;
    cin >> K >> S;
    priority_queue<Rabbit, vector<Rabbit>, compare3> kSelect_pq;
    while(K--)
    {
        Rabbit curRabbit = select_pq.top();
        //cout << "rabbit pid: " <<curRabbit.pid << "rabbit d: " << dist[curRabbit.pid] << "rabbit x: " << curRabbit.x << "rabbit y: " << curRabbit.y <<"\n"; 

        select_pq.pop();
        int nx, ny;
        tie(nx, ny) = selectMove(curRabbit);
        curRabbit.x = nx;
        curRabbit.y = ny;
        //cout << "sx : " << nx << "sy : " << ny <<"\n";
        total += nx + ny;
        score[curRabbit.pid] -= nx + ny;
        select_pq.push(curRabbit);
        kSelect_pq.push(curRabbit);
        //cout <<"pid : 20  "<< score[20]<< "\n";
        //cout <<"pid : 10  "<< score[10]<< "\n";
    }
    Rabbit kRabbit = kSelect_pq.top();
    kSelect_pq.pop();
    score[kRabbit.pid] += S;
    score_pq.push(score[kRabbit.pid]);
}

void changeD()
{
    int pid_t, L;
    cin >> pid_t >> L;

    dist[pid_t] *= L;
}

void selectBest()
{
    cout << score_pq.top() + total << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int Q;
    cin >> Q;

    while(Q--)
    {
        int tmp;
        cin >> tmp;

        switch(tmp)
        {
            case 100:
                initStart();
                break;
            case 200:
                startRace();
                break;
            case 300:
                changeD();
                break;
            case 400:
                selectBest();
                break;
        }
    }

    return 0;
}