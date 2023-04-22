#include<iostream>
#include<algorithm>
#define MAX 20001
using namespace std;

int N, M;
int A[MAX], B[MAX];

void input(){
    cin >> N >> M;
    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < M; i++) cin >> B[i];
}

void solution(){
    sort(A, A + N);
    sort(B, B + M);

    int a=0, b=0, ans=0;
    while(a<N){
        if(A[a] <= B[b] || b==M) {
            a++;
            ans += b;
        }
        else b++;
    }
    cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    while(T--){
        input();
        solution();
    }
}