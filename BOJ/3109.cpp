#include<iostream>
#include<string>
#define MAX_R 10001
#define MAX_C 501
#define EMPTY 0
#define FULL 1
using namespace std;

int R, C, ans = 0;
int map[MAX_R][MAX_C];
int dr[] = { -1, 0, 1 };
int dc[] = { 1, 1, 1 };

void input() {
	cin >> R >> C;

	string state;
	for (int r = 0; r < R; r++) {
		cin >> state;
		for (int c = 0; c < C; c++) {
			if (state[c] == '.') map[r][c] = EMPTY;
			else map[r][c] = FULL;
		}
	}
}

bool dfs(int r, int c) {

	if (r < 0 || r >= R || c >= C || map[r][c] != EMPTY) return false;
	map[r][c] = FULL;
	if (c == C - 1) {
		ans++;
		return true;
	}

	for (int d = 0; d < 3; d++) {
		int nr = r + dr[d];
		int nc = c + dc[d];
		if (dfs(nr, nc)) return true; // 한 번 실패한 위치는 어떤 방법으로도 실패 -> 더 볼 필요 없음
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	for (int r = 0; r < R; r++) dfs(r, 0); // 처음 열과 마지막 열은 항상 비어 있음
	cout << ans; // 원웅이가 놓을 수 있는 파이프라인의 최대 개수
}