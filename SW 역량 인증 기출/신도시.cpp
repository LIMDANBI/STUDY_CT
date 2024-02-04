#include<iostream>
#define MAX 15
using namespace std;

int N; // 정사각형 지도 크기
int X, Y; // 수돗물 공급되는 시작 좌표 (가로, 세로)
int totalPipe; // 총 파이프 개수
int map[MAX][MAX]; // 지도 정보
bool pipe[MAX][4]; // 우하좌상
bool visited[MAX][MAX];
int dy[] = {0, 1, 0, -1}; // 우하좌상
int dx[] = {1, 0, -1, 0};

void init(){

    // 1번 파이프
    pipe[1][0] = pipe[1][2] = true;

    // 2번 파이프
    pipe[2][1] = pipe[2][3] = true;

    // 3~6번 파이프
    int s = 0;
    for (int n = 3; n <= 6; n++){
        for (int d = s; d < s+2; d++){
            pipe[n][d % 4] = true;
        }
        s = (s + 1) % 4;
    }

    // 7~A(10)번 파이프
    s = 3;
    for (int n = 7; n <= 10; n++){
        for (int d = s; d < s+3; d++){
            pipe[n][d % 4] = true;
        }
        s = (s + 1) % 4;
    }

    // B(11)번 파이프
    for (int d = 0; d < 4; d++)
        pipe[11][d] = true;
}

void input(){
	cin >> N;
	cin >> X >> Y;
	for (int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
		    char c; cin >> c;
			if(c < 'A') map[i][j] = c - '0';
			else map[i][j] = c - 'A' + 10;
            if(map[i][j]) totalPipe++;
        }
    }
}

int dfs(int y, int x, int n){
    int res = 1;
    
    // 방문 처리
    visited[y][x] = true;

    // 다음 방문점
    for (int d = 0; d < 4; d++){
        int ny = y + dy[d];
        int nx = x + dx[d];
        int nxt = map[ny][nx];

        if(ny<0 || ny>=N || nx<0 || nx>=N || visited[ny][nx]) continue; // 범위를 벗어나는 경우, 이미 방문한 경우
        if(!pipe[n][d] || !pipe[nxt][(d+2)%4]) continue; // 다음 파이프와 방향이 맞지 않은 경우
        res += dfs(ny, nx, nxt);
    }

    return res;
}

void solve(){
    int ans = totalPipe - dfs(Y, X, map[Y][X]);
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    init();
    input();
    solve();
}