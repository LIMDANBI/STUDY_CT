#include<iostream>
#define MAX 1000001
using namespace std;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;
    int dp[MAX];
    dp[0] = dp[1] = 0;
    dp[2] = dp[3] = 1;

    for(int i=4; i<=N; i++){
        dp[i] = dp[i-1]+1;
        if(i%2==0) dp[i] = min(dp[i], dp[i/2]+1);
        if(i%3==0) dp[i] = min(dp[i], dp[i/3]+1);
    }
    cout << dp[N];
}