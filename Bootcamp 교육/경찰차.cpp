#include<iostream>
#define MAX 25
using namespace std;

struct POS{
	int y, x;
} pos[MAX]; // 사건 좌표

int N; // 도로의 개수
int W; // 사건의 개수
int ans;

void input(){
	cin >> N;
	cin >> W;
	for (int i=0; i<W; i++){
		cin >> pos[i].y >> pos[i].x;
	}
}

void dfs(int w, int cost, int fy, int fx, int sy, int sx){
    if(W <= w){ // 조료조건
        ans = min(ans, cost);
        return;
    }
   
    // 1. 1번 경찰차 이용
    int fcost = abs(pos[w].y - fy) + abs(pos[w].x-fx);
    dfs(w+1, cost+fcost, pos[w].y, pos[w].x, sy, sx);

    // 2. 2번 경찰차 이용
    int scost = abs(pos[w].y - sy) + abs(pos[w].x-sx);
    dfs(w+1, cost+scost, fy, fx, pos[w].y, pos[w].x);
}

void solve(){
    ans = 1e9;
    dfs(0, 0, 1, 1, N, N);
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}