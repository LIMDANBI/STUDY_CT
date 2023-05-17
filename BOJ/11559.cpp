#include<iostream>
#include<cstring>
#include<queue>
#define R 12
#define C 6
using namespace std;

char map[R][C];
bool visited[R][C];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input(){
    for (int i = 0; i < R; i++){
        for (int j = 0; j < C; j++) cin >> map[i][j];
    }
}

int check(int y, int x, char c){
    visited[y][x] = true;

    int res = 1;
    for (int d = 0; d < 4; d++){
        int ny = y + dy[d];
        int nx = x + dx[d];
        if(ny<0 || ny>=R || nx<0 || nx>=C) continue;
        if(visited[ny][nx] || map[ny][nx]!=c) continue;
        res += check(ny, nx, c);
    }
    return res;
}

void bomb(int y, int x, char c){
    map[y][x] = '.';

    for (int d = 0; d < 4; d++){
        int ny = y + dy[d];
        int nx = x + dx[d];
        if(ny<0 || ny>=R || nx<0 || nx>=C || map[ny][nx]!=c) continue;
        bomb(ny, nx, c);
    }
}

void gravity(){
    for (int c = 0; c < C; c++){
        queue<char> q;
        for (int r = R - 1; r >= 0; r--){
            if(map[r][c] != '.') q.push(map[r][c]);
            map[r][c] = '.';
        }

        int idx = R-1;
        while (!q.empty()){
            map[idx--][c] = q.front();
            q.pop();
        }
    }
}

void solution(){
    int ans = 0;
    while (true){

        bool isend = true;
        memset(visited, false, sizeof(visited)); // check에 사용

        for (int i = 0; i < R; i++){
            for (int j = 0; j < C; j++){
                if(map[i][j] == '.' || check(i, j, map[i][j])<4) continue;
                bomb(i, j, map[i][j]);
                isend = false;
            }
        }
        if(isend) {cout << ans; return;}
        gravity(); ans++;
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}