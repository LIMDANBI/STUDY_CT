#include<iostream>
#include<cstring>
#include<set>
#define MAX 100
using namespace std;

int N, M;
bool visited[MAX];
set<int> fs[MAX], rs[MAX];

void input(){
    cin >> N >> M;

    int a, b;
    for (int i = 0; i < M; i++){
        cin >> a >> b;
        fs[a].insert(b);
        rs[b].insert(a);
    }
}

int get_weight(int n, set<int> *s){
    int res = 1;
    visited[n] = true;
    for(int nxt : s[n]){
        if(visited[nxt]) continue;
        res += get_weight(nxt, s);
    }
    return res;
}

void solve(){
    int ans = 0;
    for (int n = 1; n <= N; n++){
        // 1. 가벼운 구슬 계산
        memset(visited, false, sizeof(visited));
        int lighter = get_weight(n, fs);

        // 2. 무거운 구슬 계산
        memset(visited, false, sizeof(visited));
        int heavier = get_weight(n, rs);

        // 3. 중간 크기의 구슬이 될 수 없는 경우를 체크
        if (lighter > (N + 1) / 2 || heavier > (N + 1) / 2) ans++;
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}