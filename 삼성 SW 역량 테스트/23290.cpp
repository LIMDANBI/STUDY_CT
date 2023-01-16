#include<iostream>
#include<cstring>
#include<vector>
#define MAX 4
using namespace std;

int max_eat = -1;
int M, S, sy, sx;
int smell[MAX][MAX];
bool visited[MAX][MAX];
vector<int> fish[MAX][MAX];
vector<int> tmp_fish[MAX][MAX];
pair<int, int> path[MAX], tmp_path[MAX];
int sdy[] = {-1, 0, 1, 0}; // 상 좌 하 우 (상어)
int sdx[] = {0, -1, 0, 1};
int fdy[] = {0, -1, -1, -1, 0, 1, 1, 1}; // ←, ↖, ↑, ↗, →, ↘, ↓, ↙ (물고기)
int fdx[] = {-1, -1, 0, 1, 1, 1, 0, -1};

void input() {
	cin >> M >> S;

	int y, x, d;
	for (int i = 0; i < M; i++) {
		cin >> y >> x >> d;
		fish[y - 1][x - 1].push_back(d - 1); // idx 0 부터 시작 
	}
	cin >> sy >> sx; 
    sy--; sx--; // idx 0 부터 시작 
}

void copy_fish() { // 상어가 모든 물고기에게 복제 마법 시전
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) 
            tmp_fish[i][j] = fish[i][j];
	}
}

void move_fish() { // 모든 물고기가 한 칸 이동

	vector<int> moved[MAX][MAX];
	for (int y = 0; y < MAX; y++) {
		for (int x = 0; x < MAX; x++) {
			for (int k = 0; k < fish[y][x].size(); k++) {
				
				int ny = y, nx = x;
				bool isfind = false;
				int d = fish[y][x][k] + 1;
				for(int i=0; i<8; i++) {

					d--; // 반 시계 방향으로 회전하며 이동할 수 있는 칸을 찾음
					if (d < 0) d += 8; //  modular 역할
					
					// 이동
					ny = y + fdy[d];
					nx = x + fdx[d];
					
					if (ny < 0 || ny >= MAX || nx < 0 || nx >= MAX) continue; // 범위를 벗어나는 경우
					if (smell[ny][nx] || ny == sy && nx == sx) continue; // 냄새 또는 상어가 있는 칸
					moved[ny][nx].push_back(d);
					isfind = true;
					break;
				}
				if (!isfind) moved[y][x].push_back(fish[y][x][k]); // 움직이지 못한 경우
			}
		}
	}

	// 움직인 물고기
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) fish[i][j] = moved[i][j];
	}
}

void simul_shark(int y, int x, int cnt, int eat) { // 상어의 이동 시뮬레이션
    if(cnt == 0){
        max_eat = -1; // 초기화,,
        memset(visited, false, sizeof(visited));
    }
	if (cnt == 3) { // 3칸 선택 완료
		if (max_eat < eat) {
			max_eat = eat; // 최대 먹을 수 있는 물고기 수 update
			for (int i = 0; i < 3; i++) path[i] = tmp_path[i]; // path 정보 저장
		}
        return; 
	}
    for(int d=0; d<MAX; d++){
        int ny = y+sdy[d];
        int nx = x+sdx[d];
        if(ny<0 || ny>=MAX || nx<0 || nx>=MAX) continue;
        tmp_path[cnt] = {ny, nx};
        if(visited[ny][nx]) simul_shark(ny, nx, cnt+1, eat);
        else{
            visited[ny][nx] = true;
            simul_shark(ny, nx, cnt+1, eat+fish[ny][nx].size());
            visited[ny][nx] = false;
        }
    }
}

void move_shark() { // 상어가 연속해서 3칸 이동
    simul_shark(sy, sx, 0, 0);
	for (int i = 0; i < 3; i++) {
        sy = path[i].first;
        sx = path[i].second;
		if (fish[sy][sx].size() == 0) continue; // 물고기가 없는 경우 
        fish[sy][sx].clear(); // 물고기가 있는 경우
        smell[sy][sx] = 3; // 냄새를 남김
	}
}

void remove_smell() { // 두 번 전 연습에서 생긴 물고기의 냄새가 격자에서 사라짐
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			if (smell[i][j] > 0) smell[i][j]--;
		}
	}
}

void complete_copy() { // 사용한 복제 마법 완료
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			for (int k = 0; k < tmp_fish[i][j].size(); k++) 
                fish[i][j].push_back(tmp_fish[i][j][k]);
		}
	}
}

void output() {
	int ans = 0;
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) 
            ans += fish[i][j].size();
	} cout << ans;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	while (S--) {
		copy_fish();
		move_fish();
		move_shark();
		remove_smell();
		complete_copy();
	}
	output();
}