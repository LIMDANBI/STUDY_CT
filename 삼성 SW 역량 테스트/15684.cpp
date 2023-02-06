#include<iostream>
#include<vector>
#define MAX_H 31
#define MAX_N 11
#define IMPOSSIBLE 4
using namespace std;

int N, M, H;
int ans = IMPOSSIBLE;
bool isLine[MAX_H][MAX_N];

void input() {
	cin >> N >> M >> H;

	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b; // 1 ≤ a ≤ H , 1 ≤ b ≤ N-1
		isLine[a][b] = true; // 입력으로 주어지는 가로선이 서로 연속하는 경우는 없음
	}
}

bool ispossible() {
	for (int n = 1; n <= N; n++) { // 세로선
		int col = n;
		for (int h = 1; h <= H; h++) {
			if (isLine[h][col]) col++;
			else if (isLine[h][col - 1]) col--;
		}
		if (col != n) return false; // i번 세로선의 결과 != i번
	} return true;
}

void solution(int cnt, int row, int maxcnt) {
    if(cnt == maxcnt){
        if(ispossible()) ans = maxcnt; // i번 세로선의 결과가 i번이 나오도록 사다리 게임을 조작하려면, 추가해야 하는 가로선 개수의 최솟값
        return;
    }
    for (int a = row; a <= H; a++) {
		for (int b = 1; b < N; b++) {
			if (isLine[a][b] || isLine[a][b+1] || isLine[a][b-1]) continue; // 이미 가로선이 있는 경우, 서로 연속하는 경우
			isLine[a][b] = true;
			solution(cnt + 1, a, maxcnt);
			isLine[a][b] = false;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
    for(int maxcnt=0; maxcnt<4 && ans==IMPOSSIBLE; maxcnt++) solution(0, 1, maxcnt);
    ans == IMPOSSIBLE ? cout << -1 : cout << ans;
}