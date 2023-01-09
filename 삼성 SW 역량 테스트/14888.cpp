#include<iostream>
#define MAX 12
using namespace std;

int N;
int max_val = -100000001; // 만들 수 있는 식의 결과의 최댓값
int min_val = 100000001; // 최솟값
int A[MAX], oper[4]; // +. -, *, /

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) cin >> A[i];
	for (int i = 0; i < 4; i++) cin >> oper[i];
}

void dfs(int res, int idx) {
	if (idx == N) {
		max_val = max(res, max_val);
		min_val = min(res, min_val);
		return;
	}
	for (int i = 0; i < 4; i++) {
		if (oper[i]) {
			oper[i]--;
			if (i == 0) dfs(res + A[idx], idx + 1);
			if (i == 1) dfs(res - A[idx], idx + 1);
			if (i == 2) dfs(res * A[idx], idx + 1);
			if (i == 3) dfs(res / A[idx], idx + 1);
			oper[i]++;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	dfs(A[0], 1);
	cout << max_val << "\n" << min_val;
}