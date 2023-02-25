#include<iostream>
#define MAX 100001
using namespace std;

int N;
int honey[MAX], sum[MAX];

void input(){
    cin >> N;

    int h;
    for(int i=1; i<=N; i++) {
        cin >> honey[i];
        sum[i] = sum[i-1] + honey[i]; // 누적 합
    }
}

void solution(){
    int ans = 0;
    for(int i=2; i<N; i++) {
        ans = max(ans, (sum[N]-honey[1]-honey[i])+(sum[N]-sum[i])); // 벌(1) 벌(i) 벌통(N)
        ans = max(ans, (sum[i]-honey[1])+(sum[N-1]-sum[i-1]));  // 벌(1) 벌통(i) 벌(N)
        ans = max(ans, sum[i-1]+(sum[N-1]-honey[i])); // 벌통(1) 벌(i) 벌(N)
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}