#include<iostream>
#define MAX 100005
using namespace std;

int N, M, K;
int A[MAX];

void input(){
    cin >> N >> K >> M;
    for (int i = 1; i <= N; i++) cin >> A[i];
}

void solve(){
    int i, k=K;
    while(M--){ // 뒤집기 연산
        cin >> i;
        if(0<i && k<=i) k = i-k+1;
        if(0>i && N+i<k) k = (N+i)+N-k+1;
    }
    cout << k;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}