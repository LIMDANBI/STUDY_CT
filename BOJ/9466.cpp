#include<iostream>
#include<cstring>
#define MAX 100005
using namespace std;

int N;
int num[MAX];
int cnt[MAX];
int visited[MAX];

void init(){
    memset(cnt, 0, sizeof(cnt));
    memset(visited, 0, sizeof(visited));
}

void input(){
    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> num[i];
}

int get_team(int n, int t, int d){
    visited[n] = t;
    cnt[n] = d;

    int nxt = num[n];

    // cycle을 이룬 경우
    if(visited[nxt] == t)
        return d - cnt[nxt] + 1;

    // 이전 탐색에서 이미 방문한 경우
    if(visited[nxt])
        return 0;

    return get_team(nxt, t, d + 1);
}

void solve(){
    int ans = N, turn=1;
    for (int n = 1; n <= N; n++){
        if(visited[n]) continue; // 이미 방문한 경우
        ans -= get_team(n, turn++, 1);
    }
    cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int TC; cin >> TC;
    while(TC--){
        init();
        input();
        solve();
    }
}