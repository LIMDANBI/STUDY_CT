#include<iostream>
#define MAX 100001
using namespace std;

int N;
int dp[3][MAX];
int sticker[3][MAX];

void input(){
    cin >> N;
    for(int i=1; i<=2; i++){
        for(int j=1; j<=N; j++){
            dp[i][j] = 0;
            cin >> sticker[i][j];
        }
    }
}

void solution(){
    
    dp[1][1] = sticker[1][1];
    dp[2][1] = sticker[2][1];

    for(int j=2; j<=N; j++){
        dp[1][j] = max(dp[2][j-2], dp[2][j-1]) + sticker[1][j];
        dp[2][j] = max(dp[1][j-2], dp[1][j-1]) + sticker[2][j];
    }
    cout << max(dp[1][N], dp[2][N]) << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    while(T--){
        input();
        solution();
    }
}