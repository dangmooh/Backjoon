#include <string>
#include <vector>
#include <iostream>

using namespace std;
int cnt = 0;
int N, M;
vector<vector<int>> quize;
vector<int> qa;
bool check(vector<int> include) //10 * 5 * 5 = 250
{
    
    for(int i=0; i<M; ++i)
    {
        int cnt =0;
        for(int j=0; j<5; ++j)
        {
            int target = quize[i][j];
            for(int k=0; k<5; ++k)
            {
                if(target == include[k]) cnt++;
            }
        }
        
        if(qa[i] != cnt)
            return false;
    }
    
    return true;
}
void printQ(vector<int> path)
{
    for(auto q : path)
    {
        cout << q << " ";
    }
    cout << "\n";
}
void dfs(int idx, vector<int> path)
{
    if((int)path.size() == 5)
    {
        if(check(path)) 
        {
            //printQ(path);
            cnt++;
        }
        return;
    }
    if(idx > N) return;

    
    path.push_back(idx);
    dfs(idx+1, path);
    path.pop_back();
    dfs(idx+1, path);
        
}

int solution(int n, vector<vector<int>> q, vector<int> ans) {
    int answer = 0;
    N = n;
    quize = q;
    qa = ans;
    
    M = (int)ans.size();
    
    vector<int> path;
    dfs(1,path);
    
    
    return cnt;
}