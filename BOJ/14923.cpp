#include<iostream>
#include<queue>
#define MAX 1001
using namespace std;

struct DATA{int y, x, chance, movecnt;};

int N, M;
int hy, hx, ey, ex;
bool maze[MAX][MAX];
bool visited[MAX][MAX][2];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input(){
    cin >> N >> M;
    cin >> hy >> hx >> ey >> ex;
    hy--; hx--; ey--; ex--;

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++) cin >> maze[i][j];
    }
}

int solution(){
    queue<DATA> q;
    q.push({hy, hx, 1, 0});
    visited[hy][hx][1] = true;

    while (!q.empty()){
        int y = q.front().y;
        int x = q.front().x;
        int chance = q.front().chance;
        int movecnt = q.front().movecnt;
        q.pop();

        if(y == ey && x == ex) return movecnt;

        for(int d=0; d<4; d++){
            int ny = y+dy[d];
            int nx = x+dx[d];
            if(ny<0 || ny>=N || nx<0 || nx>=M || visited[ny][nx][chance]) continue;
            if(maze[ny][nx] && chance){
                q.push({ny, nx, 0, movecnt+1});
                visited[ny][nx][0] = true;
            }
            if(!maze[ny][nx]){
                q.push({ny, nx, chance, movecnt+1});
                visited[ny][nx][chance] = true;
            }
        }
    }
    
    return -1;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    cout << solution();
}