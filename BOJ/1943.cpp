#include<iostream>
#include<cstring>
#include<vector>
#define MAX 50001
using namespace std;

struct COIN {int val, cnt;};
vector<COIN> coin(101);

int N;
int total=0; // 총 받은 금액
bool dp[MAX]; // dp[i] : i원을 만들 수 있으면 true, 없으면 false 저장

void input(){
    cin >> N; total=0;
    for(int i=1; i<=N; i++){
        cin >> coin[i].val >> coin[i].cnt;
        total+=(coin[i].val*coin[i].cnt); // 총 금액
    }
}

int solution(){
    if(total%2) return 0; // 홀수인 경우, 반으로 나누는 것 불가능

    memset(dp, 0, sizeof(dp)); // init
    int half = total/2;
    dp[0] = true;

    for(int n=1; n<=N; n++){ // 동전의 종류
        for(int val=half; val>=coin[n].val; val--){ // 금액 (이전 인덱스가 다음 인덱스에 영향을 미침 ➔ 탑다운)
            if(dp[val-coin[n].val]){
                for(int cnt=0; cnt<coin[n].cnt && val+coin[n].val*cnt<=half; cnt++) dp[val+coin[n].val*cnt] = true; // 동전 개수
            }
        }
    }
    if(dp[half]) return 1; return 0;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    for(int i=0; i<3; i++){
        input();
        cout << solution() << "\n";
    }
}