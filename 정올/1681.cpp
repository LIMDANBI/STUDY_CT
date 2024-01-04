#include<iostream>
#define MAX 15
#define INF 100001
using namespace std;

int N;
int ans = INF;
int map[MAX][MAX];
bool visited[MAX];

void input(){
    cin >> N;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++) {
            cin >> map[i][j];
            if(map[i][j] == 0) map[i][j] = INF;
        }
    }
}

void solve(int cnt, int prv, int cost){
    if(ans <= cost) return;
    if(N <= cnt) {
        ans = min(ans, cost+map[prv][1]);
        return;
    }
    for(int nxt=2; nxt<=N; nxt++){
        if(visited[nxt]) continue;
        visited[nxt] = true;
        solve(cnt+1, nxt, cost+map[prv][nxt]);
        visited[nxt] = false;
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve(1, 1, 0);
    cout << ans;
}