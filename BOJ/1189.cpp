#include<iostream>
#define MAX 6
using namespace std;

int ans = 0;
int R, C, K;
char map[MAX][MAX];
bool visited[MAX][MAX];
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

void input(){
    cin >> R >> C >> K;
    for (int i = 0; i < R; i++){
        string line;
        cin >> line;
        for (int j = 0; j < C; j++) map[i][j] = line[j];
    }
}

void solution(int r, int c, int dist){
    if(dist == K){
        if(r==0 && c==C-1) ans++;
        return;
    }

    for (int d = 0; d < 4; d++){
        int nr = r + dr[d];
        int nc = c + dc[d];
        if(nr<0 || nr>=R || nc<0 || nc>=C) continue;
        if(map[nr][nc]=='T' || visited[nr][nc]) continue;
        visited[nr][nc] = true;
        solution(nr, nc, dist + 1);
        visited[nr][nc] = false;
    }
}

int main(){
    freopen("../input.txt", "r", stdin);
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    visited[R - 1][0] = true;
    solution(R - 1, 0, 1);
    cout << ans;
}