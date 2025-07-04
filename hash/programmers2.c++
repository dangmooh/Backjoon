#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;


vector<int> solution(vector<string> genres, vector<int> plays) 
{
    unordered_map<string, int> genreSum;
    int N = genres.size();
    for(int i=0; i<N; ++i)
    {
        genreSum[genres[i]] += plays[i];
    }

    vector<pair<string, int>> genreOrder;
    genreOrder.reserve(genreSum.size());
    for (auto &p : genreSum)
    {
        genreOrder.emplace_back(p.first, p.second);
    }
    sort(genreOrder.begin(), genreOrder.end(), [](auto &a, auto &b){
        return a.second > b.second;
    });

    unordered_map<string, vector<pair<int,int>>> bucket;

    for(int i=0; i<N; ++i)
    {
        bucket[genres[i]].emplace_back(plays[i], i);
    }
    for (auto &entry : bucket)
    {
        auto &vec = entry.second;
        sort(vec.begin(), vec.end(), [](auto &a, auto &b){
            if(a.first != b.first) return a.first > b.first;
            return a.second < b.second;
        });
    }

    vector<int> answer;
    for (auto &g : genreOrder)
    {
        auto &vec = bucket[g.first];
        for (int i=0; i<(int)vec.size() && i<2; ++i)
        {
            answer.push_back(vec[i].second);
        }
    }

    return answer;
}