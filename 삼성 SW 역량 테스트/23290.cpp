#include<iostream>
#include<vector>
#define MAX 4
using namespace std;

int M, S;
int sy, sx;
int maxEat = -1;
int smell[MAX][MAX];
vector<int> map[MAX][MAX];
vector<int> moveMap[MAX][MAX]; // 이동한 물고기들
vector<int> copyMap[MAX][MAX]; // 복제된 물고기들
int dy[] = { 0, -1, -1, -1, 0, 1, 1, 1 }; //  ←, ↖, ↑, ↗, →, ↘, ↓, ↙ 
int dx[] = { -1, -1, 0, 1, 1, 1, 0, -1 };

int sdy[] = {-1, 0, 1, 0}; // 상어 이동에 사용 (상 좌 하 우)
int sdx[] = {0, -1, 0, 1}; 
int tmpPath[MAX], path[MAX]; // 상어의 이동 경로

void input() {
	cin >> M >> S;

	int y, x, d;
	while (M--) {
		cin >> y >> x >> d;
		map[y-1][x-1].push_back(d-1);
	}
	cin >> sy >> sx; 
	sy--; sx--;
}

void copy_start() {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++)
			copyMap[i][j] = map[i][j];
	}
}

void move_fish() {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			if (!map[i][j].size()) continue; // 물고기가 없는 칸

			for (int f = 0; f < map[i][j].size(); f++) {

				int y = i, x = j;
				int dir = map[i][j][f]; // 물고기 방향
				
				bool ismove = false;
				for (int d = 0; d < 8; d++) { 
					int nd = dir - d;
					if (nd < 0) nd += 8; // 45' 반시계 회전
					int ny = y + dy[nd];
					int nx = x + dx[nd];
					if (ny < 0 || ny >= MAX || nx < 0 || nx >= MAX) continue; // 격자의 범위를 벗어나는 칸
					if (smell[ny][nx] || (sy == ny && sx == nx)) continue; // 상어가 있는 칸, 물고기의 냄새가 있는 칸
					ismove = true; // 움직이는 것 성공
					moveMap[ny][nx].push_back(nd);
					break;
				}
				if (!ismove) moveMap[y][x].push_back(dir); // 움직이는 것 실패 (제자리에 넣어줌)
			}
		}
	}

	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			map[i][j] = moveMap[i][j];
			moveMap[i][j].clear();
		}
	}
}

void find_path(int y, int x, int cnt, int eat) {
	if (cnt == 0) maxEat = -1;
	if (cnt == 3) {
		if (maxEat < eat) {
			maxEat = eat;
			for (int i = 0; i < cnt; i++) {
				path[i] = tmpPath[i];
			}
		}
		return;
	}
	for (int d = 0; d < 4; d++) {
		int ny = y + sdy[d];
		int nx = x + sdx[d];
		if (ny < 0 || ny >= MAX || nx < 0 || nx >= MAX) continue;
		
		vector<int> tmp = map[ny][nx];
		map[ny][nx].clear();
		tmpPath[cnt] = d;
		find_path(ny, nx, cnt + 1, eat + tmp.size());
		map[ny][nx] = tmp;
	}
}

void move_shark() {
	for (int i = 0; i < 3; i++) {
		int d = path[i];
		sy += sdy[d];
		sx += sdx[d];
		if (map[sy][sx].size()) {
			smell[sy][sx] = 3; // 제외되는 물고기는 냄새를 남김
			map[sy][sx].clear();
		}
	}
}

void reduce_smell() {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			if (smell[i][j]) smell[i][j]--;
		}
	}
}

void copy_finish() {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			for (int k = 0; k < copyMap[i][j].size(); k++) {
				map[i][j].push_back(copyMap[i][j][k]);
			} 
			copyMap[i][j].clear();
		}
	}
}

void solution() {
	while (S--) {
		copy_start(); // 물고기 복제 마법 시전
		move_fish(); // 모든 물고기가 한 칸 이동
		find_path(sy, sx, 0, 0); // 상어의 이동 경로를 찾음 
		move_shark(); // 상어가 연속해서 3칸 이동
		reduce_smell(); // 두 번 전 연습에서 생긴 물고기의 냄새가 격자에서 사라짐
		copy_finish(); // 물고기 복제 마법 완료
	}
}

void output() { // S번의 연습을 마친 후 격자에 있는 물고기의 수
	int ans = 0;
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) ans += map[i][j].size();
	} cout << ans;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	solution();
	output();
}