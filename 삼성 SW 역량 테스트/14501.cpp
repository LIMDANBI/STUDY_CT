#include<iostream>
#include<vector>
#define MAX 16
using namespace std;

int N;
int dp[MAX];
pair<int, int> consult[MAX]; // time, pay

void input(){
    cin >> N;
    
    int t, p;
    for(int i=0; i<N; i++){
        cin >> t >> p;
        consult[i] = {t, p};
    }
}

void solution(){
    for(int day=N-1; day>=0; day--){
        if(day + consult[day].first > N) dp[day] = dp[day+1]; // 회사에 없어서 상담이 불가능한 경우
        else dp[day] = max(dp[day+1], dp[day+consult[day].first]+consult[day].second);
        
    } cout << dp[0]; // 백준이가 얻을 수 있는 최대 수익
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}