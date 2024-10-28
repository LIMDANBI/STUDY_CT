
#include<iostream>
#define MAX 20
using namespace std;

int N, K;
int ans;
int A[MAX];

void init(){
    ans = 0;
}

void input(){
    cin >> N >> K;
    for (int i = 0; i < N; i++){
        cin >> A[i];
    }
}

void solution(int idx, int sum){
    
    // 1. 종료 조건
    if(idx >= N){
        // 정답 조건 체크
        if(sum == K){
            ans++;
        }
        return;
    }

    // 2. 수를 포함할지 고려
    solution(idx + 1, sum); // 해당 수를 미포함
    solution(idx + 1, sum + A[idx]); // 포함
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    for (int t = 1; t <= T; t++){
        init();
        input();
        solution(0, 0);
        cout << "#" << t << " " << ans << "\n";
    }
}