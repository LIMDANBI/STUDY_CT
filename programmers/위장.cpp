#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

int solution(vector<vector<string>> clothes) {
    int answer = 1;
    
    unordered_map<string, int> um;
    for(int i=0; i<(int)clothes.size(); i++){
        if(um.find(clothes[i][1]) == um.end()) um[clothes[i][1]] = 1;
        else um[clothes[i][1]]++;
    }

    for(auto e : um) answer *= (e.second+1);
    return answer-1; // 모두 선택하지 않는 경우의 수 1개를 빼줌
}