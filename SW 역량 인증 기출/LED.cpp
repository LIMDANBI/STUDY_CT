#include<iostream>
#define MAX 100005
using namespace std;

int N; //LED 수
bool S[MAX]; // LED 상태
int pat[MAX]; // 패턴 개수

void input(){
	cin >> N;
	for (int i = 0; i < N; i++) cin >> S[i];
}

void solve(){

    // 1. ON/OFF 패턴 구간 구하기
    int idx = 0, cnt = 1;
    for (int i = 1; i < N; i++){
        if(S[i] != S[i-1]) cnt++;
        else{
            pat[idx++] = cnt;
            cnt = 1;
        }
    }
    pat[idx++] = cnt;

    // 2. 슬라이딩 윈도우, 가장 긴 ON/OFF 패턴 구간의 길이
    int ans = 0, tmp = 0;
    for (int i = 0; i < 3; i++)
        tmp += pat[i];
    ans = tmp; // 총 구간이 3개보다 작을 수 있음

    for (int r = 3; r < idx; r++){
        tmp += (pat[r] - pat[r - 3]);
        ans = max(ans, tmp);
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}