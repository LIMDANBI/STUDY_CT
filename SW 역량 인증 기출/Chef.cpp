#include<iostream>
#include<algorithm>
#define MAX 10005
using namespace std;

struct GUEST{int p, t;};
GUEST guest[MAX];

int N; // 손님 수
int maxT;
bool used[MAX];

bool comp(GUEST g1, GUEST g2){
    return g1.t > g2.t;
}

void input(){
	cin >> N;
	for (int i = 0; i < N; i++){
        cin >> guest[i].p >> guest[i].t;
        maxT = max(maxT, guest[i].t);
    }
}

void solve(){
    
    int ans = 0; // 얻을 수 있는 최대 수익

    // 1. 시간 기준 내림차순 정렬
    sort(guest, guest + N, comp);

    // 2. 예약 시간을 뒤에서부터 확정시킴
    for (int t = maxT; t > 0; t--){
        int maxP=-1, idx=-1;
        for (int n = 0; n < N; n++){
            if(used[n] || guest[n].t < t) continue;
            if(maxP < guest[n].p){
                maxP = guest[n].p;
                idx = n;
            }
        }
        if(maxP == -1) continue;
        used[idx] = true;
        ans += maxP;
    }

    // 3. 정답 출력
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}