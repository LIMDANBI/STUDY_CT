#include<iostream>
#include<vector>
#include<algorithm>
#define MAXN 15
#define MAXM 105
using namespace std;

int N; // 직원 수
int M; // 상하관계 수 
int sol[MAXN]; // 정답
bool used[MAXN];
int bonus[MAXN]; // 보너스
vector<int> v[MAXN]; // 직원들 관계 저장

void input(){
    cin >> N >> M;

    int s, e;
    for (int i=0; i<M; i++){
        cin >> s >> e;
        v[s].push_back(e);
    }
    for (int i=1; i<=N; i++){ 
        cin >> bonus[i];
    }
}

void output(){
    for(int i=1; i<=N; i++) {
        cout << sol[i] << " ";
    }
}

bool comp(int a, int b){
    return a > b;
}

bool check(){
    for(int n=1; n<=N; n++){
        for(auto nxt : v[n]){
            // 직급이 낮은 사람보다 보너스가 많지 않은 경우
            if(sol[n] <= sol[nxt])
                return false;
        }
    }
    return true;
}

void simul(int n){
    if(N < n){
        
        // 불가능한 경우
        if(!check()) return;

        // 가능한 경우
        output(); // 정답 출력
        exit(0); // 종료
    }

    for(int b=1; b<=N; b++){
        if(used[b]) continue;
        sol[n] = bonus[b];
        used[b] = true;
        simul(n+1);
        used[b] = false;
    }
}


void solve(){

    // 1. 보너스 오름차순 정렬
    sort(bonus, bonus+N);

    // 2. 완전 탐색
    simul(1);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}