#include<iostream>
#define MAX 101
#define MAX_K 10001
using namespace std;

int n, k;
int coin[MAX], dp[MAX_K];

void input(){
    cin >> n >> k;
    for(int i=1; i<=n; i++) cin >> coin[i];
}

void solution(){ // dp[j] : 가치 j를 만들 수 있는 경우의 수
    for(int i=1; i<=n; i++){
    	if(coin[i] <= k) dp[coin[i]]++;
        for(int j=coin[i]+1; j<=k; j++) dp[j] += dp[j-coin[i]];
    }
    cout << dp[k];
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}