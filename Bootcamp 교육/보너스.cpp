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
vector<int> emp[MAXN]; // 직원들 관계 저장

void input(){
    cin >> N >> M;

    int s, e;
    for (int i=0; i<M; i++){
        cin >> s >> e;
        emp[s].push_back(e);
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
        for(auto nxt : emp[n]){
            // 직급이 낮은 사람보다 보너스가 많지 않은 경우
            if(sol[n] <= sol[nxt])
                return false;
        }
    }
    return true;
}

void simul(int n){
    if(N < n){
        if(!check()) return; // 불가능한 경우
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

    // 1. 보너스 내림차순 정렬
    sort(bonus+1, bonus+N+1, comp);

    // 2. 사장은 제일 큰 금액
    sol[1] = bonus[1];
    used[1] = true;

    // 3. 완전 탐색
    simul(2);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}