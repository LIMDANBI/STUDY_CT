#include<iostream>
#define SIZE 5
using namespace std;

struct POS { int r, c; };
POS pos[SIZE * SIZE + 5];

int map[SIZE][SIZE];
bool check[SIZE][SIZE];

void input() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			cin >> map[i][j];
			pos[map[i][j]] = { i, j };
		}
	}
}

bool isBingo() {
	int cnt = 0;
	bool is_check;

	// row 체크
	for (int r = 0; r < SIZE; r++) {
		is_check = true;
		for (int c = 0; c < SIZE; c++) {
			if (map[r][c]) is_check = false;
		}
		if (is_check) cnt++;
	}

	// col 체크
	for (int c = 0; c < SIZE; c++) {
		is_check = true;
		for (int r = 0; r < SIZE; r++) {
			if (map[r][c]) is_check = false;
		}
		if (is_check) cnt++;
	}

	// diagonal 체크
	is_check = true;
	for (int i = 0; i < SIZE; i++) {
		if (map[i][i]) is_check = false;
	}
	if (is_check) cnt++;

	is_check = true;
	for (int i = 0; i < SIZE; i++) {
		if (map[i][SIZE-i-1]) is_check = false;
	}
	if (is_check) cnt++;

	if (cnt >= 3) return true;
	return false;
}

void solve() {
	int idx, num, r, c;
	for (idx = 0; idx < SIZE * SIZE; idx++) {
		num; cin >> num; // 사회자가 부르는 수
		r = pos[num].r;
		c = pos[num].c;
		map[r][c] = 0; // 불린 수 표시
		if (isBingo()) break; // 빙고가 완성된 경우
	}
	cout << idx + 1;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	solve();
}