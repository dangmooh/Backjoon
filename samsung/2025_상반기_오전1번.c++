#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;

#define MAX_N 50;
#define MAX_T 30;

typedef struct _Student {
    int x, y, count, priority;
    char food;
} Student;

using Pii = pair<int, int>;
using Map = vector<vector<pair<int, char>>>;
using Group = vector<vector<Student>>;

bool compare(const Student& A, const Student& B)
{
    if (A.priority != B.priority) return A.priority < B.priority;
    else if (A.count != B.count) return A.count > B.count;
    else if (A.y != B.y) return A.y < B.y;
    else if (A.x != B.x) return A.x < B.x;
    return false;
}

Pii dd[4] = { {-1,0}, {1,0}, {0,-1}, {0,1} }; // (y, x) u d l r


int N, T;

Map map;
Group group; // 그룹을 지어서 해당 그룹에 해당하는 것들을 모은다.
vector<Student> bestStudents;


inline bool inb(int y, int x) { return (y >= 0 && x >= 0 && y < N && x < N); }

void printMapPower()
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cout << map[i][j].first << ' ';
        }
        cout << "\n";
    }
}
void printMapFood()
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cout << map[i][j].second << ' ';
        }
        cout << "\n";
    }
}

int findPriority(char food)
{
    if (food == 'T' || food == 'C' || food == 'M') return 0;
    else if (food == 'D' || food == 'E' || food == 'F') return 1;
    else return 2;
}

inline int mask_of(char f){
    if(f=='T') return 1<<0;
    if(f=='C') return 1<<1;
    if(f=='M') return 1<<2;
    if(f=='D') return (1<<0)|(1<<1);
    if(f=='F') return (1<<0)|(1<<2);
    if(f=='E') return (1<<1)|(1<<2);
    return (1<<0)|(1<<1)|(1<<2); // 'G'
}

inline char char_of(int m){
    if(m==(1<<0))             return 'T';
    if(m==(1<<1))             return 'C';
    if(m==(1<<2))             return 'M';
    if(m==((1<<0)|(1<<1)))    return 'D';
    if(m==((1<<0)|(1<<2)))    return 'F';
    if(m==((1<<1)|(1<<2)))    return 'E';
    return 'G';
}

inline char mixFood(char a, char b){
    return char_of(mask_of(a) | mask_of(b));   // **합집합**
}

void updateMap()
{
    int groupSize = (int)group.size();
    for (int i = 0; i < groupSize; ++i)
    {
        //cout << " group food : " << group[i][0].food << '\n';
        int studentSize = (int)group[i].size();
        for (int j = 0; j < studentSize; ++j)
        {
            int x = group[i][j].x, y = group[i][j].y, power = group[i][j].count;
            map[y][x].first = power;
            //cout << "(x, y) : " << x << ", " << y << ' ' << "power : " << power; 
        }
        //cout << '\n';
    }
}

void morning()
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            map[i][j].first++;
        }
    }
}

vector<Student> makeGroup(vector<vector<bool>>& visited, int y, int x)
{
    vector<Student> students;

    visited[y][x] = true;
    queue<Pii> q;
    q.emplace(y, x);
    char target = map[y][x].second;
    int priority = findPriority(target);

    while (!q.empty())
    {
        int curY = q.front().first;
        int curX = q.front().second;
        q.pop();

        students.push_back({ curX, curY, map[curY][curX].first, priority, target });

        for (int i = 0; i < 4; ++i)
        {
            int nx = curX + dd[i].second;
            int ny = curY + dd[i].first;
            if (inb(ny, nx) && !visited[ny][nx] && map[ny][nx].second == target)
            {
                visited[ny][nx] = true;
                q.emplace(ny, nx);
            }
        }
    }

    return students;
}



void vouteBest(int groupId)
{
    int size = (int)group[groupId].size();
    if (size == 1) return;

    sort(group[groupId].begin(), group[groupId].end(), compare);

    group[groupId][0].count += size - 1; // best의 신앙심은 size -1 더하고
    for (int i = 1; i < size; ++i) // 나머지는 -1
    {
        group[groupId][i].count -= 1;
    }
}

void afternoon()
{
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    group.clear();
    bestStudents.clear();

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (!visited[i][j])
            {
                vector<Student> students = makeGroup(visited, i, j);
                group.push_back(students);
            }
        }
    }


    int sizeGroup = (int)group.size();
    for (int id = 0; id < sizeGroup; ++id)
    {
        vouteBest(id); // best한테 몰아주기
        bestStudents.push_back(group[id][0]);
    }

    sort(bestStudents.begin(), bestStudents.end(), compare);
    updateMap(); // power의 변화 업데이트
}

void night()
{
    vector<vector<bool>> visited(N, vector<bool>(N, false));

    for (Student& bestStudent : bestStudents)
    {

        int dir = bestStudent.count % 4;
        int power = bestStudent.count - 1;
        char food = bestStudent.food;
        int x = bestStudent.x;
        int y = bestStudent.y;
        //cout << "bestStudent : " << food << " power : " << power << " dir : " << dir << " x, y" << x << " , " << y << '\n';
        //printMapPower();
        if (visited[y][x]) continue; // 전파당했으면 당일에는 전파할 수 없다.
        map[y][x].first = 1;

        while (true)
        {
            x += dd[dir].second;
            y += dd[dir].first;

            if (power <= 0 || !inb(y, x)) break; // 경계를 나가거나 power가 0이 되면 종료

            int counterPower = map[y][x].first;
            char counterFood = map[y][x].second;
            if (counterFood == food) continue; // 같은 음식이면 통과

            if (power > counterPower) // 강한 전파
            {
                //cout << "strong : " << counterPower << " (x, y) : " << x << ", " << y << '\n';
                power -= counterPower + 1;
                map[y][x].first += 1;
                map[y][x].second = food;
                visited[y][x] = true;
            }
            else // 약한 전파
            {
                //cout << "weak : " << counterPower << " (x, y) : " << x << ", " << y << '\n';

                char mix = mixFood(food, counterFood);
                map[y][x].first += power;
                map[y][x].second = mix;
                power = 0;
                visited[y][x] = true;
            }
        }
    }

}

void sumPower()
{
    long long totalPower[7] = { 0, };

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            char food = map[i][j].second;
            int power = map[i][j].first;
            switch (food)
            {
            case 'T':
                totalPower[6] += power;
                break;

            case 'C':
                totalPower[5] += power;
                break;

            case 'M':
                totalPower[4] += power;
                break;

            case 'E':
                totalPower[3] += power;
                break;

            case 'F':
                totalPower[2] += power;
                break;

            case 'D':
                totalPower[1] += power;
                break;

            default:
                totalPower[0]+= power;
                break;
            }
        }
    }

    for (int i = 0; i < 7; ++i)
    {
        cout << totalPower[i] << ' ';
    }
    cout << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> T;

    map.resize(N, vector<pair<int, char>>(N));
    for (int i = 0; i < N; ++i)
    {
        string s;
        cin >> s;
        for (int j = 0; j < N; ++j)
        {
            map[i][j].second = s[j];
        }
    }

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cin >> map[i][j].first;
        }
    }


    while (T--)
    {

        morning();

        afternoon();

        night();

        sumPower();
        //printMapFood();
        //printMapPower();
    }


    return 0;
}   