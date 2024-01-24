#include<iostream>
#define SIZE 6
using namespace std;

int K;
int W, H, w, h; // 큰 면적, 작은 면적
int D[SIZE+1], M[SIZE+1];

void input(){
    cin >> K;
    for(int i=0; i<SIZE; i++){
        cin >> D[i] >> M[i];
        if(D[i]<3) W = max(W, M[i]);
        else H = max(H, M[i]);
    }
}

void solve(){

    // 계산을 쉽게 하기 위해
    D[SIZE] = D[0];
    M[SIZE] = M[0];

    for(int i=0; i<SIZE; i++){
        if(D[i]==1 && D[i+1]==3 || D[i]==4 && D[i+1]==1 
        || D[i]==2 && D[i+1]==4 || D[i]==3 && D[i+1]==2) { // 동남(13), 북동(41), 서북(24), 남서(32)
            w = M[i];
            h = M[i+1];
            break;
        }
    }
    cout << (W*H - w*h) * K;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}