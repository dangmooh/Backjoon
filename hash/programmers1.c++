#include <iostream>
#include <unordered_map>

using namespace std;




int solution(vector<vector<string>> clothes) {
    int answer = 0;

    unordered_map<string,string> hash;

    for(const auto& clothe : clothes)
    {
        
    }

    return answer;
}

int main()
{
    vector<string> participant = { "leo","kiki", "eden"}; 
    vector<string> completion = {"eden", "kiki"};

    string result = solution(participant, completion);
    cout << result << "\n";

    return 0;
}