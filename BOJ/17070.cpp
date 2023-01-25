#include<iostream>
#define MAX 17
using namespace std;

int N, ans=0;
int home[MAX][MAX];

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) cin >> home[i][j];
	}
}

void dfs(int r, int c, int d) {

	if (r >= N || c >= N || home[r][c]) return; // 범위를 벗어나거나, 벽인 경우
	if (d == 2 && (home[r - 1][c] || home[r][c - 1])) return; // 대각선 이동시 필요한 공간이 벽인 경우
	if (r == N - 1 && c == N - 1) { // 한쪽 끝으로 이동 성공
		ans++;
		return;
	}
	if (d == 0) { // 가로
		dfs(r, c + 1, 0); // 가로
		dfs(r + 1, c + 1, 2); // 대각선
	}
	else if (d == 1) { // 세로
		dfs(r + 1, c, 1); // 세로 
		dfs(r + 1, c + 1, 2); // 대각선
	}
	else { // 대각선
		dfs(r, c + 1, 0); // 가로
		dfs(r + 1, c, 1); // 세로 
		dfs(r + 1, c + 1, 2); // 대각선
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	dfs(0, 1, 0);
	cout << ans;
}