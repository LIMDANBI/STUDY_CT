#include<iostream>
#include<vector>
#define MAX_K 1001
#define MAX_N 10001
using namespace std;

struct STUDY {int p, t;}; // 중요도, 시간

int K, N; // 과목 수, 최대 공부 시간
int dp[MAX_K][MAX_N];
vector<STUDY> subject;

void input(){
    cin >> N >> K;
    subject.resize(K+1);
    for(int i=1; i<=K; i++) cin >> subject[i].p >> subject[i].t;
}

void solution(){

    int p, t; // priority, time
    for(int i=1; i<=K; i++){ // 과목 수 
        p = subject[i].p; // 중요도
        t = subject[i].t; // 시간
        for(int j=1; j<=N; j++) { // 최대 공부 시간
            if(j<t) dp[i][j] = dp[i-1][j]; // 시간이 부족한 경우
            else dp[i][j] = max(dp[i-1][j], dp[i-1][j-t]+p); // 해당 과목을 공부하는 게 이득인지
        }
    }
    cout << dp[K][N]; // 시간 내 최대가 되는 중요도
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}