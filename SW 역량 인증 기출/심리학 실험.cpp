#include<iostream>
#define MAX 100005
using namespace std;

int N; // 후보자 수
int A[MAX]; // 기질 값 (오름차순)

void input(){
    cin >> N;
    for (int i = 0; i < N; i++) cin >> A[i];
}

void solve(){

    int a = 0, b = N - 1; // 두 실험 대상자
    int l = 0, r = N - 1; // 투 포인터
    int val = 2000000001; // 0에 가장 가까운 절대 값
    
    while(l < r && val != 0){
        int sum = A[l] + A[r];
        if(abs(sum) < val){
            a = l; b = r;
            val = abs(sum);
        }
        sum <= 0 ? l++ : r--;
    }

    cout << a << " " << b;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}