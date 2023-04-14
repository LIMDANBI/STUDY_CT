#include <algorithm>
#include <vector>
#include <set>
using namespace std;

int solution(vector<int> nums){
    int answer = (int)nums.size()/2;
    
    set<int> s;
    for(int i=0; i<(int)nums.size(); i++) s.insert(nums[i]);
    answer = min(answer, (int)s.size());
    return answer;
}