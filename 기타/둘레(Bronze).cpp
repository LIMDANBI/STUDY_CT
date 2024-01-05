#include<iostream>
#define MAX 102
using namespace std;

int N, r, c;
bool hay[MAX][MAX];
bool visited[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input(){
    cin >> N;
    for(int i=0; i<N; i++){
        cin >> r >> c;
        hay[r][c] = true; // 건초
    }
}

int dfs(int y, int x){ // '건초 더미 밖 빈칸'을 기준으로 확산
    int res = 0;
    visited[y][x] = true;
    for(int d=0; d<4; d++){
        int ny = y+dy[d];
        int nx = x+dx[d];
        if(ny<0 || ny>=MAX || nx<0 || nx>=MAX) continue;
        if(hay[ny][nx]) res++;
        if(hay[ny][nx] || visited[ny][nx]) continue;
        res += dfs(ny, nx);
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    cout << dfs(0, 0);
}