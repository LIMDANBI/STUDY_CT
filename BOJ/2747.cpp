#include<iostream>
#define MAX 46
using namespace std;

int N, dp[MAX];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    dp[1] = dp[2] = 1;
    for(int i=3; i<=N; i++) dp[i] = dp[i-1]+dp[i-2];
    cout << dp[N];
}