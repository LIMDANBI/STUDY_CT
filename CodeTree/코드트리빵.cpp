// ** Ʋ�� ���� ** (��Ȯ�� 1, 2, 3 ������ ����Ǿ�� �Կ� ����)
// ����� ������ ��, ��������� ���̽� ķ���� ã����� �ϴµ�!!
// ���� ����� ���̽� ķ���� ���� ã��,,, ���� ������� �������� Ʋ�Ⱦ���,,

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
			if (y == b.y) return x > b.x; // 3. ���� ��
			return y > b.y; // 2. ���� ��
		} return dist > b.dist; //  1. ª�� �Ÿ�
	}
};

struct NEXTDIR {
	int d, dist;
	bool operator < (const NEXTDIR &n) const {
		if (dist == n.dist) return d > n.d; // �켱 ����
		return dist > n.dist; //  1. ª�� �Ÿ�
	}
};

struct POS { int y, x; };
vector<POS> basecamp, store(MAXM);

struct PERSON {
	int y, x; // ���� ��ǥ
	bool isArrive; // ���� ����
};
vector<PERSON> person(MAXM);

int N, M;
bool never[MAX][MAX]; // ������ ���� ������ �� ���� ��
bool visited[MAX][MAX]; // �Ź� �ʱ�ȭ�ؼ� ����� �湮 üũ �迭
int dy[] = { -1, 0, 0, 1 }; //  ��, ��, ��, ��
int dx[] = { 0, -1, 1, 0 };

void input() {
	cin >> N >> M;

	bool isBaseCamp;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> isBaseCamp;
			if (isBaseCamp) basecamp.push_back({ i, j }); // ���̽� ķ�� ���� ����
		}
	}

	int y, x;
	for (int p = 1; p <= M; p++) { // p�� �����
		cin >> y >> x;
		store[p] = { y - 1, x - 1 }; // ���� ������ ���� ����
	}
}

BASECAMP find_base_camp(int p) {

	priority_queue<BASECAMP> pq;
	for (int i = 0; i < (int)basecamp.size(); i++) { // �� ���̽�ķ������ �ش� ���������� BFS
		if (never[basecamp[i].y][basecamp[i].x]) continue; // �̹� ����� ���̽�ķ��

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
	return pq.top(); // ���õ� basecamp
}

int get_next_dir(int sy, int sx, int ey, int ex) { // �� ��ġ -> ������

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

// p �� ����� ������ ���� ���� ������ ������ ���� 1ĭ ������
void go_to_store(int p) {

	// ���� ��ġ
	int y = person[p].y;
	int x = person[p].x;

	// convenience store
	int cy = store[p].y;
	int cx = store[p].x;

	int d = get_next_dir(y, x, cy, cx);
	y += dy[d]; x += dx[d];
	person[p] = { y, x, false };

	if (y == cy && x == cx) {// ��ǥ�� �������� ���� 
		person[p].isArrive = true; // ���� ���� true
		never[store[p].y][store[p].x] = true; // ������ �ش� �������� �ִ� ĭ�� ������ �� ����
	}

}

void solution() {

	// 1�п��� 3�� �������� ����
	BASECAMP b = find_base_camp(1); // 1�� ��� base camp ã��
	person[1] = { b.y, b.x, false };

	// 2�� ~ M ��
	for (int m = 2; m <= M; m++) { // base camp ã�� (2��, ...)
		for (int p = 1; p < m; p++) { // �������� ���� �� ĭ ������
			if (!person[p].isArrive) go_to_store(p);
		}
		b = find_base_camp(m);
		person[m] = { b.y, b.x, false };
	}

	int ans = M; 
	while (true) { // M�� ����
		bool isEnd = true;
		for (int p = 1; p <= M; p++) {
			if (person[p].isArrive) continue; // �̹� ������ ���
			isEnd = false;
			go_to_store(p); // �������� ���� �� ĭ ������
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