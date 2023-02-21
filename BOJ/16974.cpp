#include<iostream>
#define MAX 51
using namespace std;

int N;
long long X;
long long patty[MAX];

void make_bugger(){
    patty[0] = 1;
    for(int i=1; i<=N; i++) patty[i] = patty[i-1]*2+1;
}

long long get_patty(int n, long long x){
    if(n==0 || x==0) { // 레벨 0 버거, 다 먹은 경우
        if(x == 0) return 0;
        else return 1;
    }
    if(patty[n] < x) return patty[n-1]+1+get_patty(n-1, x-patty[n]); // 중간 패티보다 많이 먹는 경우
    else if(patty[n] == x) return patty[n-1]+1; // 중간 패티까지 먹는 경우
    else return get_patty(n-1, x-1); // 중간 패티보다 적게 먹는 경우
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> N >> X;
    make_bugger();
    cout << get_patty(N, X);
}