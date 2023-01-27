#include<iostream>
#include<vector>
#include<queue>
#define MAX 16
#define ENEMY 1
#define EMPTY 0
using namespace std;

struct POS { int r, c; };
vector<POS> archer, enemy;

struct ATTACK {
	int dist, r, c;
	bool operator < (const ATTACK &a) const {
		if (dist == a.dist) {
			if (c == a.c) return r < a.r;
			return c > a.c;
		} return dist > a.dist;
	}
};

int ans = 0;
int N, M, D;
int map[MAX][MAX];
int copy_map[MAX][MAX];

void input() {
	cin >> N >> M >> D;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == ENEMY) enemy.push_back({ i, j }); // 적의 위치 저장
		}
	}
}

int get_dist(int r1, int c1, int r2, int c2) {
	return abs(r1 - r2) + abs(c1 - c2);
}

int attack_enemy(int move) {

	int kill = 0;
	int ar, ac; // 궁수의 위치
	vector<POS> attack_pos; // 공격할 적들의 위치 

	for (int a = 0; a < (int)archer.size(); a++) { // 궁수 
		ar = archer[a].r-move;
		ac = archer[a].c;

		int er, ec, dist; // 적의 위치
		priority_queue<ATTACK> pq; // dist, row, col 
		for (int e = 0; e < (int)enemy.size(); e++) { // 적
			er = enemy[e].r;
			ec = enemy[e].c;
			dist = get_dist(ar, ac, er, ec); // 거리 계산
			if (dist > D || ar<=er || map[er][ec]==EMPTY) continue; // 공격 거리 D를 초과하는 경우, 격자판을 벗어난 적인 경우, 이미 공격한 적인 경우
			pq.push({dist, er, ec}); // maxHeap to minHeap
		}
		if (pq.size() == 0) continue;
		int r = pq.top().r;
		int c = pq.top().c;

		//cout << r << " " << c << "  is pq top\n";
		attack_pos.push_back({ r,c });
	}

	for (int i = 0; i < attack_pos.size(); i++) { // 모든 궁수는 동시에 공격
		int r = attack_pos[i].r;
		int c = attack_pos[i].c;
		if (map[r][c] == EMPTY) continue;
		map[r][c] = 0; // 선택된 적 공격 (같은 적이 여러 궁수에게 공격당할 수 있음)
		kill++;
	}
	return kill; // 제거한 적의 수
}

int simulation() {
	int kill = 0;
	for (int move = 0; move < N; move++) {
		kill += attack_enemy(move); // 적 공격 + 이동 (적 대신 궁수가 이동하는 것으로 대체)
	} return kill;
}

void solution(int cnt, int idx) {
	if (cnt == 3) { // 모든 궁수를 배치한 경우

		// 1. copy 
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) copy_map[i][j] = map[i][j];
		}

		// 2. simulation
		ans = max(ans, simulation());

		// 3. recovery
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) map[i][j] = copy_map[i][j];
		}

		return;
	}
	for (int col = idx; col < M; col++) {
		archer.push_back({N, col}); //  궁수 배치
		solution(cnt + 1, col + 1); // 다음 궁수 배치
		archer.pop_back();
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	solution(0, 0);
	cout << ans;
}