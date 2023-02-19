#include<iostream>
#define MAX 1001
using namespace std;

int N;
int A[MAX], dp[MAX]; // dp[i] : i번째 값을 마지막으로 하는 가장 긴 증가하는 부분 수열

void input(){
    cin >> N;
    for(int i=0; i<N; i++) cin >> A[i];
}

void solution(){  
    int ans = 0;
    for(int i=0; i<N; i++){
        dp[i] = 1;
        for(int j=0; j<i; j++) {
            if(A[j] < A[i]) dp[i] = max(dp[i], dp[j]+1);
        }
        ans = max(ans, dp[i]);
    } cout << ans;
}

int main(){
    freopen("input.txt", "r", stdin);
    input();
    solution();
}