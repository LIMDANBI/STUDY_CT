#include<iostream>
#include<queue>
#define WALL 1
#define MAX 51
using namespace std;

struct DATA { int y, x, dir; };

int N, M;
int r, c, d;
int map[MAX][MAX];
bool visited[MAX][MAX];
int dy[] = {-1, 0, 1, 0}; // 북 동 남 서
int dx[] = {0, 1, 0, -1};

void input(){
    cin >> N >> M;
    cin >> r >> c >> d;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++) cin >> map[i][j];
    }
}

void solution(){

    queue<DATA> q;
    q.push({r, c, d});
    visited[r][c] = true;

    int ans = 1;
    while(!q.empty()){
        int y = q.front().y;
        int x = q.front().x;
        int dir = q.front().dir;
        q.pop();

        bool flag = true;
        int left = dir;
        for(int i=0; i<4; i++){
            left = (left+3)%4; // 반시계 방향 탐색 (2-1, 2-2)
            int ny = y+dy[left];
            int nx = x+dx[left];

            if(ny<0 || ny>=N || nx<0 || nx>=M) continue; // 범위를 벗어나는 경우
            if(visited[ny][nx] || map[ny][nx]==WALL) continue; // 이미 청소한 경우, 벽인 경우
            visited[ny][nx] = true; // 청소
            q.push({ny, nx, left});
            flag = false; ans++;
            break;
        }

        if(flag){
            int back = (dir+2)%4; // 뒤쪽
            int ny = y+dy[back];
            int nx = x+dx[back];

            if(ny<0 || ny>=N || nx<0 || nx>=M || map[ny][nx]==WALL) break; // 네 방향 모두 청소가 이미 되어있거나 벽이면서, 뒤쪽이 벽이라 후진도 할 수 없는 경우
            q.push({ny, nx, dir}); // 후진 가능한 경우
        }
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}