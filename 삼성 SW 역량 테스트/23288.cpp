#include<iostream>
#include<cstring>
#define MAX 21

// 주사위
#define UP 0
#define BACK 1
#define RIGHT 2
#define LEFT 3
#define FRONT 4
#define DOWN 5

// 동서 남북 
#define EAST 1
#define WEST 3
#define SOUTH 2
#define NORTH 0

using namespace std;

int N, M, K;
int map[MAX][MAX];
bool visited[MAX][MAX];
int dice[6] = { 1,2,3,4,5,6 };
int dy[] = { -1, 0, 1, 0 }; // 상 우 하 좌
int dx[] = { 0, 1, 0, -1 };

void input() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) cin >> map[i][j];
	}
}

void change_dice(int d) {

	int tmp = dice[UP];
	if (d == EAST) {
		dice[UP] = dice[LEFT];
		dice[LEFT] = dice[DOWN];
		dice[DOWN] = dice[RIGHT];
		dice[RIGHT] = tmp;
	}
	else if (d == WEST) {
		dice[UP] = dice[RIGHT];
		dice[RIGHT] = dice[DOWN];
		dice[DOWN] = dice[LEFT];
		dice[LEFT] = tmp;
	}
	else if (d == SOUTH) {
		dice[UP] = dice[BACK];
		dice[BACK] = dice[DOWN];
		dice[DOWN] = dice[FRONT];
		dice[FRONT] = tmp;
	}
	else { // NORTH
		dice[UP] = dice[FRONT];
		dice[FRONT] = dice[DOWN];
		dice[DOWN] = dice[BACK];
		dice[BACK] = tmp;
	}
}

int dfs(int y, int x) {
	visited[y][x] = true;
	
	int res = 1;
	for (int d = 0; d < 4; d++) {
		int ny = y + dy[d];
		int nx = x + dx[d];
		if (ny < 0 || ny >= N || nx < 0 || nx >= M) continue;
		if (visited[ny][nx] || map[ny][nx] != map[y][x]) continue;
		res += dfs(ny, nx);
	}
	return res;
}

void solution() { // 각 이동에서 획득하는 점수의 합 출력
	int ans = 0;
	int y = 0, x = 0, dir = EAST; // 초기 주사위 정보
	
	while (K--) {
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		if (ny < 0 || ny >= N || nx < 0 || nx >= M) { // 범위를 벗어나는 경우
			// 이동 방향을 반대로 한 다음 한 칸 굴러감
			if (dir == NORTH) dir = SOUTH;
			else if (dir == SOUTH) dir = NORTH;
			else if (dir == WEST) dir = EAST;
			else if (dir == EAST) dir = WEST;
			ny = y + dy[dir];
			nx = x + dx[dir];
		}
		
		y = ny; x = nx;
		memset(visited, false, sizeof(visited));
		ans += map[y][x] * dfs(y, x); // 점수획득
		change_dice(dir); // 주사위 전개도 변경

		if (dice[DOWN] > map[y][x]) { // 이동 방향을 90도 시계 방향으로 회전
			dir = (dir + 1) % 4;
		}
		else if (dice[DOWN] < map[y][x]) { // 이동 방향을 90도 반시계 방향으로 회전
			dir--; if (dir < 0) dir = 3;
		}
	}
	cout << ans;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	solution();
}