#include<iostream>
#define MAX 101
#define MAX_K 10001
using namespace std;

int n, k;
int coin[MAX];
int dp[MAX][MAX_K];

void input(){
    cin >> n >> k;
    for(int i=1; i<=n; i++) cin >> coin[i];
}

void solution(){ // dp[i][j] : i 종류의 동전을 사용해서 가치 j를 만들 수 있는 경우의 수

    // init
    for(int j=1; j<=k; j++){
        if(j%coin[1] == 0) dp[1][j] = 1;
    }

    // dynamic programming
    for(int i=2; i<=n; i++){
        for(int j=1; j<=k; j++){
            dp[i][j] = dp[i-1][j];
            if(j == coin[i]) dp[i][j]++;
            if(j>=coin[i]) dp[i][j] += dp[i][j-coin[i]];
        }
    }
    cout << dp[n][k];
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}