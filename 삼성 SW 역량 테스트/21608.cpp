#include<iostream>
#include<vector>
#include<queue>
#define MAX 21
#define MAX2 450
#define EMPTY 0
using namespace std;

struct DATA {
	int like, empty, row, col;

	bool operator < (const DATA &d) const {
		if (like == d.like) {
			if (empty == d.empty) {
				if (row == d.row) return col > d.col; // 열의 번호가 가장 작은 칸
				return row > d.row; //  행의 번호가 가장 작은 칸
			} return empty < d.empty; // 인접한 칸 중에서 비어있는 칸이 가장 많은 칸
		} return like < d.like; // 좋아하는 학생이 인접한 칸에 가장 많은 칸
	}
};

int N;
int seat[MAX][MAX];
int order_to_num[MAX2];
vector<int> student[MAX2];
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };
int satisfy[] = { 0, 1, 10, 100, 1000 };

void input() {
	cin >> N;

	int n, s;
	for (int i = 0; i < N*N; i++) {
		cin >> n; // 학생의 번호
		order_to_num[i] = n;
		for (int j = 0; j < 4; j++) { // 그 학생이 좋아하는 학생 4명의 번호
			cin >> s;
			student[n].push_back(s);
		}
	}
}

void set_seat(int num) {

	priority_queue<DATA> pq;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (seat[y][x]) continue; // 이미 주인이 있는 자리
			int like = 0, empty = 0;
			for (int d = 0; d < 4; d++) {
				int ny = y + dy[d];
				int nx = x + dx[d];
				if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue; // 범위를 벗어나는 경우
				for (int l = 0; l < 4; l++) { // 좋아하는 학생
					if (seat[ny][nx] == student[num][l]) like++;
				}
				if (seat[ny][nx] == EMPTY) empty++; // 빈자리
			}
			pq.push({ like, empty, y, x });
		}
	}
	seat[pq.top().row][pq.top().col] = num;
}

void get_satisfy() {
	int ans = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int like = 0;
			int num = seat[i][j];
			for (int d = 0; d < 4; d++) {
				int ny = i + dy[d];
				int nx = j + dx[d];
				if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue;
				for (int l = 0; l < 4; l++) {
					if (seat[ny][nx] == student[num][l]) like++;
				}
			}
			ans += satisfy[like];
		}
	} cout << ans;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	for (int i = 0; i < N * N; i++) set_seat(order_to_num[i]);
	get_satisfy();
}