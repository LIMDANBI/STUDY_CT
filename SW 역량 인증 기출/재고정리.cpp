#include<iostream>
#define MAX 100005
#define INF 1e9
#define KIND 15
using namespace std;

int N; // 제품 수
int M; // 제품 종류 수
int ans;
int id[MAX]; // 제품 ID
int cnt[KIND]; // id별 제품 개수
int order[MAX];
bool used[MAX];

void input(){
	cin >> N >> M;
	for(int i = 1; i <= N; i++) {
        cin >> id[i];
        cnt[id[i]]++;
    }
}

int check(int s, int m){
    int res = 0;
    for (int i = 0; i < cnt[m]; i++){
        if(id[s+i] != m) res++;
    }
    return res;
}

void permu(int idx, int mcnt, int start){
    if(ans <= mcnt) return; // 가지치기
    if(M <= idx){ // 종료 조건
        ans = mcnt;
        return;
    }
    for (int m = 1; m <= M; m++){
        if(used[m]) continue;
        used[m] = true;
        order[idx] = m;
        permu(idx + 1, mcnt+check(start, m), start+cnt[m]);
        used[m] = false;
    }
}

void solve(){

    // 1. 초기화
    ans = INF;

    // 2. 완전 탐색 (순열) + 가지치기
    permu(0, 0, 1);

    // 3. 정답 출력
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}