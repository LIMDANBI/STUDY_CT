#include<iostream>
#define MAX 25
using namespace std;

int N, M, sl, sr;
int ans=10001;
int order[MAX];

void input(){
    cin >> N;
    cin >> sl >> sr;
    cin >> M;
    for(int i=1; i<=M; i++) cin >> order[i];
}

void solve(int m, int l, int r, int move){
    if(ans <= move) return; // 더 작게 이동하는 방법을 이미 알고 있음
    if(m > M){ // 종료 조건
        ans = move;
        return;
    }
    if(order[m] > l) solve(m+1, l, order[m], move+abs(order[m]-r)); // right 문을 이용
    if(order[m] < r) solve(m+1, order[m], r, move+abs(order[m]-l)); // left 문을 이용
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve(1, sl, sr, 0);
    cout << ans;
}