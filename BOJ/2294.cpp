#include<iostream>
#define INF 987654321
using namespace std;

int n, k;
int coin[101], dp[10001];

void input(){
    cin >> n >> k;
    for(int i=1; i<=n; i++) cin >> coin[i];
    for(int i=1; i<=k; i++) dp[i] = INF;
}

void solution(){
    for(int i=1; i<=n; i++){
        for(int j=1; j<=k; j++){
            if(j == coin[i]) dp[j] = 1;
            if(j > coin[i]) dp[j] = min(dp[j], dp[j-coin[i]]+1);
        }
    }
    if(dp[k] == INF) cout << -1;
    else cout << dp[k]; // 사용한 동전의 최소 개수
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}