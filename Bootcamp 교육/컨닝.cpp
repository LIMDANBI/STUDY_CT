#include<iostream>
#include<algorithm>
#define MAX 100005
using namespace std;

int N;// 개수
int F[MAX];

void input(){
    cin >> N;
    for(int i=0; i<N; i++) cin >> F[i];
}

void solve(){
    long long ans = 0;

    // 1. 정렬
    sort(F, F+N);

    // 2. 검사해야 할 파일 쌍의 수 확인 (투포인터)
    int s=0, e=1;
    while(s < N-1){
        while(e!=N && F[e]*0.9 <= F[s]) e++; // 작은 파일의 크기가 큰 파일의 크기의 90% 이상
        ans += (e-s-1);
        s++;
    }

    // 3. 정답 출력
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}