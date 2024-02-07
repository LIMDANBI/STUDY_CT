#include<iostream>
#define MAX 10
using namespace std;

int W; // 사용할 금액
int A[6]; // 각 동전 개수(갖고 있는)
int sol[6]; // 답
int coin[] = {500, 100, 50, 10, 5, 1};
int psum[MAX]; // 누적합

void input(){
	cin >> W;
	for (int i=0; i<6; i++){
		cin >> A[i];
	}
}

void make_psum(){
    for(int i=5; i>=0; i--){
        psum[i] = psum[i+1] + (coin[i]*A[i]);
    }
}

void solve(){

    // 1. 누적합 만들기
    make_psum();

    // 2. 그리디 
    int send = 0;
    for(int i=0; i<6; i++){
        if(W <= psum[i+1]) continue;
        int diff = W-psum[i+1];
        int q = diff / coin[i];
        int r = diff % coin[i];
        sol[i] = q + (r ? 1 : 0);
        W -= (sol[i]*coin[i]);
        send += sol[i];
    }

    // 3. 정답 출력
    cout << send << "\n";
    for(int i=0; i<6; i++) cout << sol[i] << " ";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}