#include<iostream>
#define MAX 1001
#define DIV 10007
using namespace std;

int N;
int dp[MAX];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> N;

    dp[1] = 1;
    dp[2] = 2;
    for(int i=3; i<=N; i++) dp[i] = (dp[i-1] + dp[i-2])%DIV;
    cout << dp[N];
}