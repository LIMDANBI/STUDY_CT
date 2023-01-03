#include<iostream>
#define MAX 21
using namespace std;

int N, M;
int A[MAX], B[MAX];

void input(){
    cin >> N >> M;
    for(int i=0; i<N; i++) cin >> A[i];
    for(int i=0; i<M; i++) cin >> B[i];
}

int solution(){
    int ans = -1000000001;

    if(N < M){
        for(int i=0; i<=M-N; i++){
            int res = 0;
            for(int j=i; j<i+N; j++) res+=(A[j-i]*B[j]);
            ans = max(ans, res);
        }
    }
    else{ // N >= M
        for(int i=0; i<=N-M; i++){
            int res = 0;
            for(int j=i; j<i+M; j++) res+=(A[j]*B[j-i]);
            ans = max(ans, res);
        }
    }

    return ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    for(int t=1; t<=T; t++){
        input();
        cout << "#" << t << " " << solution() << "\n";
    }
}