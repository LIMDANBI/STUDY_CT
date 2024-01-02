#include<iostream>
#define MAX 11
using namespace std;

int N, ans=10001;
bool visited[MAX];
int cost[MAX][MAX];

void input(){
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) cin >> cost[i][j];
    }
}

void solve(int cnt, int sum){ // 각 빌딩을 어느 장소에 세우면 비용의 합이 최소가 되는지
    if(ans < sum) return;
    if(cnt == N){
        ans = min(ans, sum);
        return;
    }
    for(int idx=0; idx<N; idx++){
        if(visited[idx]) continue;
        visited[idx] = true;
        solve(cnt+1, sum+cost[cnt][idx]);
        visited[idx] = false;
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve(0, 0);
    cout << ans;
}