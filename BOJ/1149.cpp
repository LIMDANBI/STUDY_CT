#include<iostream>
#define MAX 1002
#define COLOR 3 // red green blue
using namespace std;

int N;
int dp[COLOR][MAX];
int map[COLOR][MAX];

void input(){
    cin >> N;
    for(int i=1; i<=N; i++){
        for(int j=0; j<COLOR; j++) cin >> map[j][i];
    }
}

void solution(){
    for(int n=1; n<=N; n++){
        dp[0][n] = min(dp[1][n-1], dp[2][n-1]) + map[0][n];
        dp[1][n] = min(dp[0][n-1], dp[2][n-1]) + map[1][n];
        dp[2][n] = min(dp[0][n-1], dp[1][n-1]) + map[2][n];
    }
    cout << min(min(dp[0][N], dp[1][N]), dp[2][N]); // 모든 집을 칠하는 비용의 최솟값
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}