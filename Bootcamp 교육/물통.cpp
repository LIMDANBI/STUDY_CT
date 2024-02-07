#include<iostream>
#define MAX 1001
#define INF 1e9
using namespace std;

int A, B, C, D;
int work[MAX][MAX];

void input(){
    cin >> A >> B >> C >> D;
}

void init(){
    for(int i=0; i<=A; i++){
        for(int j=0; j<=B; j++) work[i][j] = INF;
    }
}

void simul(int a, int b, int cnt){
    
    // 이미 더 적게 도달할 수 있는 경우
    if(work[a][b] <= cnt) return;

    // 더 적게 도달하는 작업 수
    work[a][b] = cnt;

    // 1. F(A)
    simul(A, b, cnt+1);

    // 2. F(B)
    simul(a, B, cnt+1);

    // 3. E(A)
    simul(0, b, cnt+1);

    // 4. E(B)
    simul(a, 0, cnt+1);

    // 5. M(A, B)
    int emptySpace = B-b;
    int send = min(emptySpace, a);
    simul(a-send, b+send, cnt+1);

    // 6. M(B, A)
    emptySpace = A-a;
    send = min(emptySpace, b);
    simul(a+send, b-send, cnt+1);
}

void solve(){

    // 1. 초기화
    init();

    // 2. 시뮬레이션
    simul(0, 0, 0);

    // 3. 정답 출력
    if(work[C][D] == INF) cout << -1;
    else cout << work[C][D];
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}