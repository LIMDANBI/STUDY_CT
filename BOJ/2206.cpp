#include<iostream>
#include<vector>
#include<queue>
#define INF 100000001
#define MAX 1001
#define WALL 1
#define EMPTY 0
using namespace std;

struct DATA { int y, x, chance; };

int N, M;
int map[MAX][MAX];
int dist[MAX][MAX][2];
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

void input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		string str; cin >> str;
		for (int j = 0; j < M; j++) map[i][j] = str[j] - '0';
	}
}

int solution() {
	queue<DATA> q;
	q.push({ 0,0,1 }); // (0,0)에서 출발, 벽을 꺨 수 있는 기회 한번
	dist[0][0][1] = 1;

	while (!q.empty()) {
		int y = q.front().y;
		int x = q.front().x;
		int chance = q.front().chance;
		q.pop();

		if(y==N-1 && x==M-1) return dist[y][x][chance]; // 도착한 경우
		for(int d=0; d<4; d++){
			int ny = y+dy[d];
			int nx = x+dx[d];
			if(ny<0 || ny>=N || nx<0 || nx>=M || dist[ny][nx][chance]) continue; // 범위를 벗어나는 경우, 이미 방문한 경우
			if(map[ny][nx]==WALL && chance){
				dist[ny][nx][0] = dist[y][x][1]+1;
				q.push({ny, nx, 0});
			}
			else if(map[ny][nx]==EMPTY){
				dist[ny][nx][chance] = dist[y][x][chance]+1;
				q.push({ny, nx, chance});
			}
		}
	}
	return -1; // 도착 불가능한 경우
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	cout << solution();
}