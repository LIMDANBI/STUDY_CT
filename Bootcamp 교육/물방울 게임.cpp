#include<iostream>
#include<algorithm>
#define MAX 105
using namespace std;

int A; // 초기 유저의 물방울 크기
int N; // 물방울 개수
int ans;
int W[MAX];

void input(){
    cin >> A >> N;
    for (int i=0; i<N; i++) cin >> W[i];
}

void simul(int cur, int idx, int skill){

    if(ans <= skill) return; // 가지치기

    // 1. 먹을 수 있을 때 까지
    while(idx<N && W[idx]<cur){
        cur+=W[idx];
        idx++;
    }

    // 2. 다 먹은 경우
    if(N <= idx) {
        ans = skill;
        return;
    }

    // 3. 다 먹지 못한 경우
    simul(cur, N, skill+(N-idx)); // 뒤에거 다지우기
    simul(cur+(cur-1), idx, skill+1); // 크게 키워보기
}

void solve(){

    // 1. 오름 차순 정렬
    sort(W, W+N);

    // 2. 시뮬레이션
    simul(A, 0, 0);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int TC; cin >> TC;
    for(int t=1; t<=TC; t++){
        ans = MAX;
        input();
        solve();
        cout << "Case #" << t << ": " << ans << "\n";
    }
}