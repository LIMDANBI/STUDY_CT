#include<iostream>
#define MAX 101
#define MAX_K 100001
using namespace std;

int N, K;
int weight[MAX], value[MAX], dp[MAX][MAX_K];

void input(){
    cin >> N >> K;
    for(int i=1; i<=N; i++) cin >> weight[i] >> value[i];
}

void solution(){

    for(int i=1; i<=N; i++){
        for(int j=1; j<=K; j++){
            if(weight[i] > j) dp[i][j] = dp[i-1][j];
            else dp[i][j] = max(dp[i-1][j], dp[i-1][j-weight[i]]+value[i]);
        }
    }
    
    cout << dp[N][K]; // 배낭에 넣을 수 있는 물건들의 가치의 최댓값
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}