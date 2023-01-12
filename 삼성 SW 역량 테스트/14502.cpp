#include<iostream>
#include<vector>
#define MAX 9
#define EMPTY 0
#define WALL 1
#define VIRUS 2
using namespace std;

int N, M;
int ans = 0;
int lab[MAX][MAX];
int copy_lab[MAX][MAX];
int dy[] = { -1,1,0,0 };
int dx[] = { 0,0,-1,1 };
vector<pair<int, int>> virus;

void input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
            cin >> lab[i][j];
            if(lab[i][j] == VIRUS) virus.push_back({i, j});
        }
	}
}

void spread_virus(int y, int x) {
    copy_lab[y][x] = VIRUS;
    for (int d = 0; d < 4; d++) {
        int ny = y + dy[d];
        int nx = x + dx[d];
        if (ny < 0 || ny >= N || nx < 0 || nx >= M) continue;
        if (copy_lab[ny][nx] != EMPTY) continue;
        spread_virus(ny, nx);
    }
}

void solution(int cnt) {
	if (cnt == 3) {

		// 1. copy map
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) copy_lab[i][j] = lab[i][j];
		}

		// 2. spread_virus
		for (int i = 0; i < virus.size(); i++) {
            spread_virus(virus[i].first, virus[i].second);
		}

		// 3. get max safety zone
		int res = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
                if(copy_lab[i][j] == EMPTY) res++;
			}
		}

        // 4. update ans;
        ans = max(ans, res);

		return;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (lab[i][j] != EMPTY) continue;
			lab[i][j] = WALL;
			solution(cnt + 1);
			lab[i][j] = EMPTY;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	solution(0);
	cout << ans;
}