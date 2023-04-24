#include<iostream>
#include<algorithm>
#include<vector>
#define MAX 101
using namespace std;

struct POS { int y, x; };
vector<POS> pos, bishop;

int N;
int bk = 0, wh = 0;
bool map[MAX][MAX];

void input() {
	cin >> N;

	bool possible;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> possible;
			if (possible) pos.push_back({ i, j });
		}
	}
}

bool impossible() {
	for (int a = 0; a < (int)bishop.size() - 1; a++) {
		for (int b = a + 1; b < (int)bishop.size(); b++) {
			int ay = bishop[a].y, ax = bishop[a].x;
			int by = bishop[b].y, bx = bishop[b].x;
			if (abs(ay - by) == abs(ax - bx)) return true;
		}
	}
	return false;
}

void solution_bk(int cnt, int use) {

	if (impossible()) return;
	if (cnt == (int)pos.size()) {
		bk = max(bk, use);
		return;
	}

	solution_bk(cnt + 1, use);

	int y = pos[cnt].y;
	int x = pos[cnt].x;
	if ((y + x) % 2 == 0) {
		bishop.push_back(pos[cnt]);
		solution_bk(cnt + 1, use + 1);
		bishop.pop_back();
	}
}

void solution_wh(int cnt, int use) {

	if (impossible()) return;
	if (cnt == (int)pos.size()) {
		wh = max(wh, use);
		return;
	}

	solution_wh(cnt + 1, use);

	int y = pos[cnt].y;
	int x = pos[cnt].x;
	if ((y + x) % 2 != 0) {
		bishop.push_back(pos[cnt]);
		solution_wh(cnt + 1, use + 1);
		bishop.pop_back();
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	input();
	solution_bk(0, 0);
	solution_wh(0, 0);
	cout << bk+wh;
}