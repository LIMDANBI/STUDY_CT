#include <iostream>
#define MAX 105
using namespace std;
int N, M; //재료종류수, 가진돈
int X[MAX]; //1인분당 필요한 양
int Y[MAX]; //주방에 있는 양
int Sm[MAX]; //작은 포장 재료 양
int Pm[MAX]; //작은 포장 가격
int Sv[MAX]; //큰포장 재료 양
int Pv[MAX]; //큰포장 가격

void input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> X[i] >> Y[i] >> Sm[i] >> Pm[i] >> Sv[i] >> Pv[i];
	}
}

bool isPossible(int val, int money){
    for (int n = 0; n < N; n++){
        int need = X[n] * val - Y[n];
        if(need <= 0) continue; // 이미 충분한 재료가 있어서 구매할 필요 x

        int cost = 1e6;
        int maxSmallCnt = need/Sm[n] + (need%Sm[n]>0 ? 1 : 0);
        for (int scnt = 0; scnt <= maxSmallCnt; scnt++){ // 작은 포장을 scnt개 사는 경우
            int left = need - scnt * Sm[n];
            int lcnt = left == 0 ? 0 : left/Sv[n] + (left%Sv[n]>0 ? 1 : 0);
            cost = min(cost, scnt * Pm[n] + lcnt * Pv[n]);
        }
        money -= cost;
        if(money < 0) return false; // 돈을 모두 사용한 경우
    }
    return true; // 주어진 돈으로 가능한 경우
}

void solve(){ // '준비할 수 있는 최대 식사량'으로 이분탐색
    int low = 0, mid, high = 1e6;
    while(low <= high){
        mid = (low + high) / 2;
        if(isPossible(mid, M))
            low = mid + 1;
        else
            high = mid - 1;
    }
    cout << high;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
    solve();
}