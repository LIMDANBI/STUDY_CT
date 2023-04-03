#include<iostream>
#include<cstring>
#include<vector>
#define MAX 101
#define MAXK 1001
using namespace std;

struct MICROBE { 
	int y, x, cnt, dir;
	bool isdead = false;
};
vector<MICROBE> micorbe;

int N, M, K;
int map[MAX][MAX];
int tmpMap[MAX][MAX];
int maxCnt[MAX][MAX];
int dy[] = {-1, 1, 0, 0}; // 상: 1, 하: 2, 좌: 3, 우: 4
int dx[] = {0, 0, -1, 1}; // (-1 해서 idx 0 부터 사용)

void init() {
	micorbe.resize(MAXK);
	memset(map, 0, sizeof(map));
}

void input() {
	cin >> N >> M >> K;
	
	int y, x, cnt, dir;
	for (int n = 1; n <= K; n++) {
		cin >> y >> x >> cnt >> dir;
		map[y][x] = n;
		micorbe[n] = { y, x, cnt, dir-1, false };
	}
}

void move() {
	for (int n = 1; n <= K; n++) {
		if (micorbe[n].isdead) continue; // 합쳐졌거나, 사라진 군집인 경우
		
		int y = micorbe[n].y;
		int x = micorbe[n].x;
		int cnt = micorbe[n].cnt;
		int dir = micorbe[n].dir;

		int ny = y + dy[dir];
		int nx = x + dx[dir];

		if (ny == 0 || ny == N - 1 || nx == 0 || nx == N - 1) { // 약품이 칠해진 셀
			cnt /= 2; // 군집 내 미생물의 절반이 죽고,
			(dir == 0 || dir == 2) ? dir++ : dir--; // 이동방향이 반대로 바뀜
		}
		if (cnt == 0) { // 군집이 사라지는 경우
			micorbe[n].isdead = true;
			continue;
		}

		// 군집 정보 update
		micorbe[n] = { ny, nx, cnt, dir, false};
		
		if (tmpMap[ny][nx] == 0) {
			tmpMap[ny][nx] = n; // 비어 있는 경우
			maxCnt[ny][nx] = cnt;
		}
		else { // 두 개 이상의 군집이 한 셀에 모이는 경우 (군집이 합쳐짐)
			int on = tmpMap[ny][nx]; // 다른 군집 번호
			int oy = ny, ox = nx;
			int ocnt = micorbe[on].cnt;
			int odir = micorbe[on].dir;

			if (cnt < maxCnt[ny][nx]) { // 상대 군집의 미생물이 많은 경우
				micorbe[n].isdead = true;
				micorbe[on].cnt += cnt;
			}
			else { // 내 군집의 미생물이 많은 경우
				tmpMap[ny][nx] = n;
				maxCnt[ny][nx] = cnt;
				micorbe[on].isdead = true;
				micorbe[n].cnt += ocnt;
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if(tmpMap[i][j]) map[i][j] = tmpMap[i][j];
			else map[i][j] = 0;
			tmpMap[i][j] = 0;
			maxCnt[i][j] = 0;
		}
	}
}

void output(int t) { // M시간 후 남아 있는 미생물 수의 총 합
	int ans = 0;
	for (int n = 1; n <= K; n++) {
		if (micorbe[n].isdead) continue;
		ans += micorbe[n].cnt;
	}
	cout << "#" << t << " " << ans << "\n";
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	for (int t = 1; t <= T; t++) {
		init();
		input();
		while (M--) move();
		output(t);
	}
}