#include<iostream>
#define MAX 1001
using namespace std;

int N, seq[MAX], dp[MAX];

void input(){
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> seq[i];
}

void solution(){

    int ans = 0;
    for (int i = 1; i <= N; i++){
        dp[i] = 1;
        for (int j = 1; j < i; j++){
            if(seq[j] > seq[i]) dp[i] = max(dp[i], dp[j]+1);
        }
        ans = max(ans, dp[i]);
    }
    cout << ans;
}

int main(){
    freopen("../input.txt", "r", stdin);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    input();
    solution();
}