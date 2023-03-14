#include<iostream>
#include<algorithm>
#include<vector>
#define MAX 1001
#define STUDENT 101
using namespace std;

int N, K;
vector<int> nums;
int recommend[STUDENT]; // 현재 추천 수

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> N >> K;
    
    while(K--){
        int n; cin >> n;
        recommend[n]++;

        bool flag = false;
        for(int i=0; i<nums.size(); i++){
            if(nums[i] == n) flag = true;
        }
        if(flag) continue; // 기존 후보인 경우

        if(nums.size() < N) nums.push_back(n); // 후보 자리가 남아 있는 경우
        else{ // 후보 자리가 부족한 경우
            int min_val = MAX;
            for(int i=0; i<nums.size(); i++) min_val = min(min_val, recommend[nums[i]]);
            for(int i=0; i<nums.size(); i++){
                if(recommend[nums[i]] == min_val) {
                    recommend[nums[i]] = 0;
                    for(int j=i+1; j<nums.size(); j++) nums[j-1] = nums[j];
                    nums[nums.size()-1] = n;
                    break;
                }
            }
        }
    }

    sort(nums.begin(), nums.end());
    for(int i=0; i<nums.size(); i++) cout << nums[i] << " ";
}