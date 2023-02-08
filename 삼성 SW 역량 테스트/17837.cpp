#include<iostream>
#include<vector>
#define MAX 13
#define WHITE 0
#define RED 1
#define BLUE 2
using namespace std;

struct CHESS { int y, x, dir; };

int N, K;
bool iscontinue = true;

CHESS chess[MAX];
int color[MAX][MAX];
vector<int> map[MAX][MAX];
int dy[] = {0, 0, 0, -1, 1}; // 1부터 순서대로 →, ←, ↑, ↓
int dx[] = {0, 1, -1, 0, 0};

void input() {
	cin >> N >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) cin >> color[i][j];
	}

	int y, x, dir;
	for (int num = 1; num <= K; num++) {
		cin >> y >> x >> dir; // 행, 열의 번호, 이동 방향
		chess[num] = { y, x, dir };
		map[y][x].push_back(num);
	}
}

void move_red(int y, int x, int idx, int dir) { //  A번 말과 위에 있는 모든 말의 순서를 반대로 바꿔서 이동
	int ny = y + dy[dir];
	int nx = x + dx[dir];
	for (int i = map[y][x].size() - 1; i >= idx; i--) {
        int num = map[y][x][i];
		map[ny][nx].push_back(num); // 이동
		chess[num].y = ny; // 바뀐 위치 저장
        chess[num].x = nx;
	}
	// 턴이 진행되던 중에 말이 4개 이상 쌓이는 순간 게임이 종료
	if (map[ny][nx].size() >= 4) { iscontinue = false; return; }
	int tmp = map[y][x].size() - idx;
	while (tmp--) map[y][x].pop_back(); // 옮겼으므로
}

void move_white(int y, int x, int idx, int dir) {  // A번 말과 위에 있는 모든 말 이동
	int ny = y + dy[dir];
	int nx = x + dx[dir];
	for (int i = idx; i < map[y][x].size(); i++) {
        int num = map[y][x][i];
		map[ny][nx].push_back(num); // 이동
		chess[num].y = ny; // 바뀐 위치 저장
        chess[num].x = nx;
	}
	// 턴이 진행되던 중에 말이 4개 이상 쌓이는 순간 게임이 종료
	if (map[ny][nx].size() >= 4) {iscontinue = false; return;}
	int tmp = map[y][x].size() - idx;
	while (tmp--) map[y][x].pop_back(); // 옮겼으므로
}

void move_blue(int y, int x, int num, int idx, int dir) {
	if (dir == 1 || dir == 3) dir++; else dir--; // 방향 change
	int ny = y + dy[dir];
	int nx = x + dx[dir];
    chess[num].dir = dir; // 바뀐 방향 저장
	if (ny<1 || ny>N || nx<1 || nx>N || color[ny][nx] == BLUE) return;
	else if (color[ny][nx] == RED) move_red(y, x, idx, dir);
	else if (color[ny][nx] == WHITE) move_white(y, x, idx, dir);
}

void game() {
	for (int num = 1; num <= K && iscontinue; num++) {
		int y = chess[num].y;
		int x = chess[num].x;
        int dir = chess[num].dir;

		// find
		int idx=0;
		for (int i = 0; i < map[y][x].size(); i++) {
			if (map[y][x][i] == num) {
				idx = i;
				break;
			}
		}

		// 이동 and 바뀐 위치 저장
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		if (ny<1 || ny>N || nx<1 || nx>N || color[ny][nx] == BLUE) move_blue(y, x, num, idx, dir);
		else if (color[ny][nx] == RED) move_red(y, x, idx, dir);
		else move_white(y, x, idx, dir); // WHITE
	}
}

void solution() {
	int ans = 0;
	while (++ans <= 1000) {
		game();
		if (!iscontinue) break;
	}
	if(ans > 1000) cout << -1;  // 값이 1,000보다 크거나 절대로 게임이 종료되지 않는 경우
	else cout << ans; // 게임이 종료되는 턴의 번호
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	solution();
}