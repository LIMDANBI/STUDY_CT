#include<iostream>
#include<queue>
#define MAXISLAND 8
#define MAX 11
#define SEA 0
#define LAND 1
using namespace std;

struct EDGE { 
	int from, to, len;
	bool operator < (const EDGE &e) const {
		if (len == e.len) {
			if (from == e.from) return to > e.to;
			return from > e.from;
		} return len > e.len;
	}
}; priority_queue<EDGE> pq; // 다리 후보들

int N, M;
int map[MAX][MAX];
int root[MAXISLAND];
int dy[] = { -1, 0, 1, 0 }; // 상 좌 하 우
int dx[] = { 0, -1, 0, 1 };

void input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) cin >> map[i][j];
	}
}

int find_(int x) {
	if (x == root[x]) return x;
	return root[x] = find_(root[x]);
}

void union_(int x, int y) {
	root[find_(x)] = find_(y);
}

void grouping(int y, int x, int num) {
	if (y < 0 || y >= N || x < 0 || x >= M) return; // 범위를 벗어나는 경우
	if (map[y][x] != LAND) return; // 땅이 아닌 경우
	map[y][x] = num;
	for (int d = 0; d < 4; d++) grouping(y + dy[d], x + dx[d], num);
}

void make_candidates() {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			
			if (map[y][x] == SEA) continue; // 바다인 경우
			
			int from = map[y][x]; // 출발지
			int to, len;
			for (int d = 0; d < 2; d++) { // 상,좌 만 탐색 (겹치는 다리를 없도록 하기 위해)
				to = 0; len = 0; // 도착지, 다리 길이

				int ny = y, nx = x;
				while (1) {
					ny+=dy[d]; nx+=dx[d]; // move
					len++; // 이동 거리
					if (ny < 0 || ny >= N || nx < 0 || nx >= M ) break; // 범위를 벗어나는 경우
					if (map[ny][nx] == from) break; // 같은 섬인 경우
					if (map[ny][nx] > LAND) { // 다른 섬에 도착한 경우
						if(--len > 1) to = map[ny][nx]; // 다리의 길이는 2 이상
						break;
					}
				} if (to != 0) pq.push({from, to, len});
			}
		}
	}
}

int make_bridge(int need) { // need : MST edge 수 
	for (int i = 2; i < MAXISLAND; i++) root[i] = i; // union-find를 위한 초기화
	int ans = 0, bridge_num = 0;
	while (!pq.empty() && bridge_num != need) {
		int len = pq.top().len;
		int from = pq.top().from;
		int to = pq.top().to;
		pq.pop();

		if (find_(from) != find_(to)) { // 연결되지 않은 경우
			ans += len;
			bridge_num++;
			union_(from, to); // 연결
		}
	}
	if (bridge_num != need) return -1; // 모든 섬을 연결하는 것이 불가능한 경우
	return ans;
}

void solution() { // 모든 섬을 연결하는 것이 불가능하면 -1을 출력
	
    // 1. grouping
	int island_num = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == LAND) grouping(i, j, ++island_num); // 각 섬에 대표 번호를 매김 (start with 2)
		}
	}

	// 2. 다리 후보 선정
	make_candidates();

	// 3. MST로 다리 만들기
	cout << make_bridge(island_num-2);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); 
	input();
	solution(); //모든 섬을 연결하는 다리 길이의 최솟값
}