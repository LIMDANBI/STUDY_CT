#include<iostream>
#define MAX 25
using namespace std;

int N, K;
int num[MAX];
int psum[MAX]; // 구간합
bool used[MAX];

void input(){
    cin >> N >> K;
    for(int i=1; i<=N; i++) {
        cin >> num[i];
        psum[i] = psum[i-1] + num[i];
    }
}

bool check(int cnt, int sum){
    if(sum == K) return true;
    if(cnt == N+1 || sum > K || sum+psum[N]-psum[cnt-1] < K) return false; // backtracking

    if(check(cnt+1, sum)) return true; // 해당 수를 더하지 않아봄
    if(check(cnt+1, sum+num[cnt])) return true; // 해당 수를 더해봄
    return false;
}

void solve(){
    int T; cin >> T;
    while(T--){
        input();
        check(1, 0) ? cout << "YES\n" : cout << "NO\n";
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    solve();
}