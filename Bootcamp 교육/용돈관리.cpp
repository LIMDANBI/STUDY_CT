#include<iostream>
#define MAX 100005
using namespace std;

int N, M; // N일 동안 M번 인출
int money[MAX];

void input(){
    cin >> N >> M;
    for(int i=0; i<N; i++) cin >> money[i];
}

bool check(int val, int chance){
    int now = 0;
    for(int i=0; i<N; i++){
        if(now < money[i]) { // 가지고 있는 금액이 모자른 경우
            now = val - money[i]; // 남은 금액을 통장에 넣고, K원 인출
            if(--chance<0 || now<0) return false; // M번 인출, K만큼 인출로 불가능한 경우
        }
        else now -= money[i];
    }
    return true;
}

void solve(){ // 철수가 설정 가능 한 K의 최소값
    int low=0, mid, high=MAX*MAX;
    while (low <= high){
        mid = (low+high)/2;
        if(check(mid, M)) high = mid-1;
        else low = mid+1;
    }
    cout << low;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}