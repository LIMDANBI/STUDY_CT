#include<iostream>
#include<algorithm>
#define MAX 101
using namespace std;

int N;
char map[MAX][MAX];
bool visited[MAX][MAX];
int dy[] = {-1, 1, 0, 0, -1, -1, 1, 1};
int dx[] = {0, 0, -1, 1, -1, 1, -1, 1};

void input(){
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) cin >> map[i][j];
    }
}

void dfs(int y, int x){
    visited[y][x] = true;
    for(int d=0; d<8; d++){
        int ny = y+dy[d];
        int nx = x+dx[d];
        if(ny<0 || ny >=N || nx<0 || nx>=N) continue;
        if(map[ny][nx]=='0' || visited[ny][nx]) continue;
        dfs(ny, nx);
    }
}

void solve(){
    int ans = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(map[i][j]=='0' || visited[i][j]) continue;
            dfs(i, j); ans++;
        }
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}