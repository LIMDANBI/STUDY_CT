#include<iostream>
#define MAX 25
using namespace std;

int N, K;
int num[MAX];
bool used[MAX];
bool isPossible;

void input(){
    cin >> N >> K;
    isPossible = false; // init
    for(int i=0; i<N; i++) cin >> num[i];
}

void check(int cnt, int sum){
    if(sum == K) isPossible = true;
    if(isPossible || cnt == N) return;

    check(cnt+1, sum); // 해당 수를 더하지 않아봄
    check(cnt+1, sum+num[cnt]); // 해당 수를 더해봄
}

void solve(){
    int T; cin >> T;
    while(T--){
        input();
        check(0, 0);
        isPossible ? cout << "YES\n" : cout << "NO\n";
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    solve();
}