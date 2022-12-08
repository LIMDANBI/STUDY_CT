#include<iostream>
#define MAX 101
using namespace std;

long long dp[MAX];

void solution(){
    dp[1] = dp[2] = dp[3] = 1;
    for(int i=4; i<MAX; i++) dp[i] = dp[i-2]+dp[i-3];
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    solution();
    while(T--){
        int N; cin >> N;
        cout << dp[N] << "\n";
    }
}