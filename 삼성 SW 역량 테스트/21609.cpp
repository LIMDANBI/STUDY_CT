#include<iostream>
#include<cstring>
#include<queue>
#define MAX 21
#define EMPTY -2
#define BLACK -1
#define RAINBOW 0
using namespace std;

struct DATA {
	int size, rainbow, row, col;

	bool operator < (const DATA &d) const {
		if (size == d.size) {
			if (rainbow == d.rainbow) {
				if (row == d.row) return col < d.col; // 기준 블록의 열이 가장 큰 것
				return row < d.row; // 기준 블록의 행이 가장 큰 것
			} return rainbow < d.rainbow; // 무지개 블록의 수가 가장 많은 블록 그룹
		} return size < d.size; // 크기가 가장 큰 블록 그룹
	}
};

int N, M;
int map[MAX][MAX];
int copy_map[MAX][MAX];
bool visited[MAX][MAX];
int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

void input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			copy_map[i][j] = EMPTY; // init
		}
	}
}

void turn_rainbow() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == RAINBOW) visited[i][j] = false;
		}
	}
}

DATA get_group(int i, int j, int col) {
	queue<pair<int, int> > q;
	visited[i][j] = true;
	q.push({ i,j });

	int size = 1, rainbow = 0;
	while (!q.empty()) {
		int r = q.front().first;
		int c = q.front().second;
		q.pop();
		for (int d = 0; d < 4; d++) {
			int nr = r + dr[d];
			int nc = c + dc[d];
			if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue; // 범위를 벗어나는 경우
			if (map[nr][nc] != RAINBOW && map[nr][nc] != map[i][j]) continue; // 무지개 블록이 아닌데, 블록의 색상이 다른 경우
			if (visited[nr][nc] || map[nr][nc] == EMPTY || map[nr][nc] == BLACK) continue; // 이미 방문한 경우, 그룹에 포함될 수 없는 경우
			if (map[nr][nc] == RAINBOW) rainbow++; size++;
			visited[nr][nc] = true;
			q.push({ nr, nc });
		}
	}
	return { size, rainbow, i, j };
}

void remove_block(int r, int c, int col) {
	visited[r][c] = true;
	map[r][c] = EMPTY; // block 제거
	for (int d = 0; d < 4; d++) {
		int nr = r + dr[d];
		int nc = c + dc[d];
		if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue; // 범위를 벗어나는 경우
		if (map[nr][nc] != RAINBOW && map[nr][nc] != col) continue; // 무지개 블록이 아닌데, 블록의 색상이 다른 경우
		if (visited[nr][nc] || map[nr][nc] == EMPTY || map[nr][nc] == BLACK) continue; // 이미 방문한 경우, 그룹에 포함될 수 없는 경우
		remove_block(nr, nc, col);
	}
}

void gravity() {
	for (int c = 0; c < N; c++) {
		int idx = N - 1;
		for (int r = N - 1; r >= 0; r--) {
			if (map[r][c] == EMPTY) continue;
			if (map[r][c] == BLACK) idx = r - 1;
			else copy_map[idx--][c] = map[r][c];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == BLACK) continue;
			map[i][j] = copy_map[i][j];
			copy_map[i][j] = EMPTY;
		}
	}
}

void rotate() {
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			copy_map[N - c - 1][r] = map[r][c];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j] = copy_map[i][j];
			copy_map[i][j] = EMPTY;
		}
	}
}

void solution() {

	int ans = 0;
	while (1) {
		priority_queue<DATA> pq;

		// 1. 크기가 가장 큰 블록 그룹을 찾음
		memset(visited, false, sizeof(visited));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j] < 1 || visited[i][j]) continue; // 일반 블록이 아닌 경우, 이미 방문한 경우
				DATA group = get_group(i, j, map[i][j]); // (i,j)는 기준 블록
				turn_rainbow(); // 무지개 블록은 중복해서 가질 수 있음
				if (group.size >= 2) pq.push(group); // 그룹에 속한 블록의 개수는 2보다 크거나 같아야 함
			}
		}

		if (pq.empty()) break; // 오토 플레이 종료

		// 2. 1에서 찾은 블록 그룹의 모든 블록 제거
		memset(visited, false, sizeof(visited));
		int r = pq.top().row, c = pq.top().col;
		remove_block(r, c, map[r][c]);
		ans += (pq.top().size * pq.top().size); // B^2점 획득

		// 3. 격자에 중력 작용
		gravity();

		// 4. 격자가 90도 반시계 방향으로 회전
		rotate();

		// 5. 격자에 중력 작용
		gravity();
	}
	cout << ans;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	solution();
}