#include<iostream>
#include<cstring>
#define MAX 101
using namespace std;

int N;
char map[MAX][MAX];
bool visited[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input(){
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) cin >> map[i][j];
    }
}

void dfs(int y, int x, char c){
    visited[y][x] = true;
    for(int d=0; d<4; d++){
        int ny = y+dy[d];
        int nx = x+dx[d];
        if(ny<0 || ny>=N || nx<0 || nx>=N) continue;
        if(visited[ny][nx] || map[ny][nx]!=c) continue;
        dfs(ny, nx, c);
    }
}

void solve(){

    // 일반 꿀꿀이
    int rgbCnt = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(visited[i][j]) continue;
            dfs(i, j, map[i][j]);
            rgbCnt++;
        }
    }

    // init
    memset(visited, false, sizeof(visited));
    for(int i=0; i<N; i++){ // red -> green
        for(int j=0; j<N; j++){
            if(map[i][j] == 'R') map[i][j] = 'G';
        }
    }

    // 적록색맹 꿀꿀이
    int rbCnt = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(visited[i][j]) continue;
            dfs(i, j, map[i][j]);
            rbCnt++;
        }
    }

    cout << rgbCnt << " " << rbCnt;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}