#include<iostream>
#define MAX 10
using namespace std;

int N;      // 보내려는 물품 개수
int C[MAX]; // BOX 개수
int sol[MAX]; // 보내는 BOX 개수
int num[] = {1, 5, 10, 50, 100, 500, 1000, 3000, 6000, 12000}; // 용량

void input(){
	cin >> N;
	for(int i = 0; i < MAX; i++) cin >> C[i];
}

void solve(){

    // 1. 최소 개수
    int n = N;
    for (int cur = MAX - 1; cur >= 0; cur--){
        int q = n / num[cur];
        if(q == 0) continue;

        sol[cur] = min(q, C[cur]);
        n -= num[cur] * sol[cur];
        C[cur] -= sol[cur];
    }

    // 2. 최소 개수 -> 최대 개수 (그리디)
    for (int cur = MAX - 1; cur > 0; cur--){
        if(sol[cur] == 0) continue;
        for (int prv = cur - 1; prv >= 0; prv--){
            int need = num[cur]/num[prv]; // 바꾸기 위해 몇개가 필요한지
            int cnt = min(sol[cur], C[prv]/need); // 바꿀 수 있는 개수
            if(cnt == 0) continue;
            
            C[cur] += cnt;
            sol[cur] -= cnt;

            C[prv] -= cnt*need;
            sol[prv] += cnt*need;

            if(sol[cur] == 0) break; 
        }
    }

    // 3. 정답 출력
    int ans = 0;
    for(auto n : sol) ans+=n;
    
    cout << ans << "\n";
    for(auto n : sol) cout << n << " ";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}