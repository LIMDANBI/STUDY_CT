#include<iostream>
#define MAX 10
using namespace std;

int N;      // 보내려는 물품 개수
int C[MAX]; // BOX 개수
int sol[MAX]; // 보내는 BOX 개수
int psum[MAX+1]; // 누적합
int num[] = {1, 5, 10, 50, 100, 500, 1000, 3000, 6000, 12000}; // 용량

void input(){
	cin >> N;
	for(int i = 0; i < MAX; i++) {
        cin >> C[i];
        psum[i + 1] = psum[i] + (C[i] * num[i]);
    }
}

void solve(){

    // 1. 남은 BOX들로 보낼 수 없을 경우에만 배정
    int ans = 0;
    for (int cur = MAX - 1; cur >= 0; cur--){
        if(N <= psum[cur]) continue;
        int q = (N-psum[cur])/num[cur];
        int r = (N-psum[cur])%num[cur];
        int cnt = q + (r>0 ? 1 : 0);
        N -= cnt * num[cur];
        sol[cur] = cnt;
        ans += cnt;
    }

    // 2. 정답 출력    
    cout << ans << "\n";
    for(auto n : sol) cout << n << " ";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}