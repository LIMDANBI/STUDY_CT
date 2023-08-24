#include<iostream>
#define MAX 101
using namespace std;

int N, M;
bool ispeak;
int map[MAX][MAX];
bool visited[MAX][MAX];
int dy[] = {-1, -1, -1, 0, 1, 1, 1, 0};
int dx[] = {-1, 0, 1, 1, 1, 0, -1, -1};

void input(){
    cin >> N >> M;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++) cin >> map[i][j];
    }
}

void dfs(int y, int x){
    visited[y][x] = true;
    for (int d = 0; d < 8; d++){
        int ny = y + dy[d];
        int nx = x + dx[d];
        if(ny<0 || ny>=N || nx<0 || nx>=M) continue;
        if(map[y][x] < map[ny][nx]) ispeak = false; // 더 높은 산 봉우리
        if(visited[ny][nx] || map[y][x] != map[ny][nx]) continue;
        dfs(ny, nx);
    }
}

void solution(){
    int ans = 0;
    for (int y = 0; y < N; y++){
        for (int x = 0; x < M; x++){
            if(visited[y][x]) continue;
            ispeak = true;
            dfs(y, x);
            if(ispeak) ans++;
        }
    } cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}