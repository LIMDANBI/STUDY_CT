#include<iostream>
#include<vector>
#include<queue>
#define INF 1000000001
#define MAX 51
#define EMPTY 0
#define WALL 1
#define VIRUS 2
#define VISITED 3
using namespace std;

int N, M, ans=INF;
int empty_cnt = 0; // 바이러스가 놓여야 하는 칸
int lab[MAX][MAX];
int copy_lab[MAX][MAX];
int dy[] = { -1,1,0,0 };
int dx[] = { 0,0,-1,1 };
vector<int> active;
vector<pair<int, int>> virus;

struct DATA { int y, x, sec; };

void input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> lab[i][j];
			if (lab[i][j] == WALL)  continue; // 벽인 경우
			if (lab[i][j] == VIRUS) virus.push_back({ i, j }); // 바이러스 위치
			else empty_cnt++; 
		}
	}
}

int spread_virus() {

	// 1. copy
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) copy_lab[i][j] = lab[i][j];
	}

	queue<DATA> q;
	for (int i = 0; i < active.size(); i++) {
		int num = active[i]; // 활성화한 바이러스
		int y = virus[num].first;
		int x = virus[num].second;
		copy_lab[y][x] = VISITED;
		q.push({y, x, 0});
	}
	if (empty_cnt == 0) return 0;

	int sec = 0; // 걸린 시간
	int spread = 0;
	while (!q.empty()) {
		int y = q.front().y;
		int x = q.front().x;
		int s = q.front().sec;
		q.pop();
		
		for (int d = 0; d < 4; d++) {
			int ny = y + dy[d];
			int nx = x + dx[d];
			if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue; // 범위를 벗어나는 경우
			if (copy_lab[ny][nx] == WALL || copy_lab[ny][nx] == VISITED) continue; // 벽인 경우,이미 방문한 경우
			if (copy_lab[ny][nx] == EMPTY) {
				spread++; // 바이러스 전파
				sec = max(sec, s + 1); // 비활성화 바이러스가 활성화 되는 시간은 계산 x
			}
			copy_lab[ny][nx] = VISITED; // 바이러스 전파, 비활성 바이러스 -> 활성화 
			q.push({ ny, nx, s + 1 });
		}
	} 
	if (spread == empty_cnt) return sec; // 바이러스가 모두 전파된 경우 
	return INF; // 바이러스가 모두 전파될 수 없는 경우
}

void solution(int cnt, int idx) {
	if (cnt == M) { // 바이러스 M개를 활성 상태로 변경한 경우
		ans = min(ans, spread_virus()); // 바이러스를 퍼뜨림
		return;
	}
	for (int i = idx; i < virus.size(); i++) {
		active.push_back(i); // 바이러스 활성화
		solution(cnt + 1, i + 1);  // 조합 구현 
		active.pop_back(); // 바이러스 비활성화
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	solution(0, 0);
	if (ans == INF) cout << -1; // 바이러스를 어떻게 놓아도 모든 빈 칸에 바이러스를 퍼뜨릴 수 없는 경우
	else cout << ans; // 모든 빈 칸에 바이러스를 퍼뜨리는 최소 시간
}