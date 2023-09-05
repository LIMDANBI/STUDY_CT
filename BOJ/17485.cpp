#include<iostream>
#define MAX 1001
#define INF 100001
using namespace std;

int N, M;
int map[MAX][MAX];
int dp[MAX][MAX][3]; // dp[y][x][k] : 방법 k로 (y, x)에 도착할 때, 필요한 연료

void input(){
    cin >> N >> M;
    for (int y = 1; y <= N; y++){
        for (int x = 1; x <= M; x++) {
            cin >> map[y][x];
            for (int k = 0; k < 3; k++) dp[y][x][k] = INF; // init for DP
        }
    }
}

void solution(){
    for (int y = 1; y <= N; y++){
        for (int x = 1; x <= M; x++){
            if(x!=1) dp[y][x][0] = min(dp[y-1][x-1][1], dp[y-1][x-1][2]) + map[y][x];
            dp[y][x][1] = min(dp[y-1][x][0], dp[y-1][x][2]) + map[y][x];
            if(x!=M) dp[y][x][2] = min(dp[y-1][x+1][0], dp[y-1][x+1][1]) + map[y][x];
        }
    }

    int ans = INF;
    for (int x = 1; x <= M; x++) {
        for (int d = 0; d < 3; d++)
            ans = min(ans, dp[N][x][d]);
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}