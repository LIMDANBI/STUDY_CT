#include<iostream>
#define MAX 500005
using namespace std;

int N, M;
int par[MAX];

int find_(int x){
    if(par[x] == x) return x;
    return par[x] = find_(par[x]);
}

int union_(int y, int x){
    int py = find_(y);
    int px = find_(x);
    if(py != px) {
        par[px] = py;
        return 0;
    }
    return 1;
}

void solve(){
    cin >> N >> M;

    // 1. 초기화
    for (int i = 0; i < N; i++)
        par[i] = i;

    // 2. cycle 찾기
    int ans = 0;
    for (int m = 1; m <= M; m++){
        int y, x; cin >> y >> x;
        if(union_(y, x)) {
            ans = m;
            break;
        }
    }
    
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    solve();
}