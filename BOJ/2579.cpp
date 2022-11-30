#include<iostream>
#define MAX 301
using namespace std;

int N;
int arr[MAX], dp[MAX];

void input(){
    cin >> N;
    for(int i=1; i<=N; i++) cin >> arr[i];
}

void solution(){
    dp[1] = arr[1];
    dp[2] = arr[1] + arr[2];
    for(int i=3; i<=N; i++) dp[i] = max(dp[i-2]+arr[i], dp[i-3]+arr[i-1]+arr[i]); // 두 계단 점프 or 한 계단 점프
    cout << dp[N]; // 계단 오르기 게임에서 얻을 수 있는 총 점수의 최댓값
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}