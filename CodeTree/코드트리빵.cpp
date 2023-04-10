// ** 틀린 이유 ** (정확히 1, 2, 3 순서로 진행되어야 함에 유의)
// 사람이 움직인 후, 다음사람의 베이스 캠프를 찾아줘야 하는데!!
// 다음 사람의 베이스 캠프를 먼저 찾고,,, 이전 사람들을 움직여서 틀렸었다,,
// ++ 추가로 도착 편의점 위치 (y, x)를 idx 0부터 사용하기 위해 -1을 해줘야 함!!

#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#define MAX 16
#define MAXM 31
using namespace std;

struct BASECAMP {
	int y, x, dist;
	bool operator < (const BASECAMP &b) const {
		if (dist == b.dist) {
			if (y == b.y) return x > b.x; // 3. 작은 열
			return y > b.y; // 2. 작은 행
		} return dist > b.dist; //  1. 짧은 거리
	}
};

struct NEXTDIR {
	int d, dist;
	bool operator < (const NEXTDIR &n) const {
		if (dist == n.dist) return d > n.d; // 2. 우선 방향
		return dist > n.dist; //  1. 짧은 거리
	}
};

struct POS { int y, x; };
vector<POS> basecamp, store(MAXM);

struct PERSON {
	int y, x; // 현재 좌표
	bool isArrive; // 도착 여부
};
vector<PERSON> person(MAXM);

int N, M;
bool never[MAX][MAX]; // 앞으로 절대 지나갈 수 없는 곳
bool visited[MAX][MAX]; // 매번 초기화해서 사용할 방문 체크 배열
int dy[] = { -1, 0, 0, 1 }; //  ↑, ←, →, ↓
int dx[] = { 0, -1, 1, 0 };

void input() {
	cin >> N >> M;

	bool isBaseCamp;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> isBaseCamp;
			if (isBaseCamp) basecamp.push_back({ i, j }); // 베이스 캠프 정보 저장
		}
	}

	int y, x;
	for (int p = 1; p <= M; p++) { // p번 사람의
		cin >> y >> x;
		store[p] = { y - 1, x - 1 }; // 도착 편의점 정보 저장 (idx 0 부터 시작!!!)
	}
}

BASECAMP find_base_camp(int p) {

	priority_queue<BASECAMP> pq;
	for (int i = 0; i < (int)basecamp.size(); i++) { // 각 베이스캠프에서 해당 편의점까지 BFS
		if (never[basecamp[i].y][basecamp[i].x]) continue; // 이미 사용한 베이스캠프

		memset(visited, false, sizeof(visited)); // init

		queue<BASECAMP> q;
		q.push({ basecamp[i].y, basecamp[i].x, 0 });
		visited[basecamp[i].y][basecamp[i].x] = true;

		while (!q.empty()) {
			int y = q.front().y;
			int x = q.front().x;
			int dist = q.front().dist;
			q.pop();

			if (y == store[p].y && x == store[p].x) {
				pq.push({ basecamp[i].y, basecamp[i].x, dist });
				break;
			}

			for (int d = 0; d < 4; d++) {
				int ny = y + dy[d];
				int nx = x + dx[d];
				if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue;
				if (visited[ny][nx] || never[ny][nx]) continue;
				visited[ny][nx] = true;
				q.push({ ny, nx, dist + 1 });
			}
		}
	}
	never[pq.top().y][pq.top().x] = true;
	return pq.top(); // 선택된 basecamp
}

int get_next_dir(int sy, int sx, int ey, int ex) { // 현 위치 -> 편의점

	priority_queue<NEXTDIR> pq;

	for (int d = 0; d < 4; d++) {

		int y = sy + dy[d];
		int x = sx + dx[d];
		if (y < 0 || y >= N || x < 0 || x >= N || never[y][x]) continue;

		memset(visited, false, sizeof(visited));
		visited[sy][sx] = true;

		queue<BASECAMP> q;
		q.push({ y, x, 1 });
		visited[y][x] = true;

		while (!q.empty()) {
			int y = q.front().y;
			int x = q.front().x;
			int dist = q.front().dist;
			q.pop();

			if (y == ey && x == ex) {
				pq.push({ d, dist });
				break;
			}

			for (int d = 0; d < 4; d++) {
				int ny = y + dy[d];
				int nx = x + dx[d];
				if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue;
				if (never[ny][nx] || visited[ny][nx]) continue;
				visited[ny][nx] = true;
				q.push({ ny, nx, dist + 1 });
			}
		}
	}
	return pq.top().d;
}

// p 번 사람이 본인이 가고 싶은 편의점 방향을 향해 1칸 움직임
void go_to_store(int p) {

	// 현재 위치
	int y = person[p].y;
	int x = person[p].x;

	// convenience store
	int cy = store[p].y;
	int cx = store[p].x;

	int d = get_next_dir(y, x, cy, cx);
	y += dy[d]; x += dx[d];
	person[p] = { y, x, false };

	if (y == cy && x == cx) {// 목표한 편의점에 도착 
		person[p].isArrive = true; // 도착 여부 true
		never[store[p].y][store[p].x] = true; // 앞으로 해당 편의점이 있는 칸을 지나갈 수 없음
	}

}

void solution() {

	// 1분에는 3번 과정부터 진행
	BASECAMP b = find_base_camp(1); // 1번 사람 base camp 찾기
	person[1] = { b.y, b.x, false };

	// 2분 ~ M 분
	for (int m = 2; m <= M; m++) {
		for (int p = 1; p < m; p++) { // 편의점을 향해 한 칸 움직임 !!!
			if (!person[p].isArrive) go_to_store(p);
		}
		b = find_base_camp(m);  // base camp 찾기 (2번, ...)
		person[m] = { b.y, b.x, false };
	}

	int ans = M; 
	while (true) { // M분 이후
		bool isEnd = true;
		for (int p = 1; p <= M; p++) {
			if (person[p].isArrive) continue; // 이미 도착한 경우
			isEnd = false;
			go_to_store(p); // 편의점을 향해 한 칸 움직임
		}
		if (isEnd) break;
		ans++;
	}
	cout << ans;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	solution();
}