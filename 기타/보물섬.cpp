#include<iostream>
#include<cstring>
#include<queue>
#define MAX 51
using namespace std;

struct DATA{int y, x, t;};

int H, W;
char map[MAX][MAX];
bool visited[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input(){
    cin >> H >> W;
    for(int i=0; i<H; i++){
        for(int j=0; j<W; j++) cin >> map[i][j];
    }
}

int bfs(int y, int x){

    // init
    memset(visited, false, sizeof(visited));

    queue<DATA> q;
    q.push({y, x, 0});
    visited[y][x] = true;
    
    int t = 0;
    while(!q.empty()){
        y = q.front().y;
        x = q.front().x;
        t = q.front().t;
        q.pop();

        for(int d=0; d<4; d++){
            int ny=y+dy[d];
            int nx=x+dx[d];
            if(ny<0 || ny>=H || nx<0 || nx>=W) continue;
            if(visited[ny][nx] || map[ny][nx]!='L') continue;
            visited[ny][nx] = true;
            q.push({ny, nx, t+1});
        }
    }
    return t;
}

void solve(){ // 보물은 서로 간에 최단 거리로 이동하는데 있어 가장 긴 시간이 걸리는 육지 두 곳에 나뉘어 묻혀있음
    int ans = 0;
    for(int y=0; y<H; y++){
        for(int x=0; x<W; x++){
            if(map[y][x]=='L') ans = max(ans, bfs(y, x));
        }
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}