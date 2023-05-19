#include <iostream>
#define MAX 11
using namespace std;

int ans;
int N, M, C;
int maxProfit[2];
int map[MAX][MAX];

void input(){
    cin >> N >> M >> C;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++) cin >> map[i][j];
    }
}

void get_max_profit(int y, int x, int num, int cnt, int honey, int profit){
    if(honey > C) return;
    if(cnt == M){
        maxProfit[num] = max(profit, maxProfit[num]);
        return;
    }
    get_max_profit(y, x + 1, num, cnt + 1, honey, profit); // 미채취
    get_max_profit(y, x + 1, num, cnt + 1, honey+map[y][x], profit+map[y][x]*map[y][x]); // 채취

}

void solution(int y, int x, int cnt){
    if(cnt == 2) {
        ans = max(ans, maxProfit[0] + maxProfit[1]);
        return;
    }

    int j = x;
    for (int i = y; i < N; i++){ // 일꾼 1
        for (; j < N - M + 1; j++){
            maxProfit[cnt] = 0;
            get_max_profit(i, j, cnt, 0, 0, 0); // 해당 지점에서의 일꾼(cnt+1)의 최대 채취 양 구하기
            solution(i, j + M, cnt + 1);  // 일꾼 2
        } j = 0;
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    for (int t = 1; t <= T; t++){
        ans = 0;
        input();
        solution(0, 0, 0);
        cout << "#" << t << " " << ans << "\n";
    }
}