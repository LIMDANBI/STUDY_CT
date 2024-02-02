#include<iostream>
#include<cstring>
#include<queue>
#define MAX 15
using namespace std;

int R = 12;
int C = 6;
char map[MAX][MAX];
bool visited[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input(){
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++) cin >> map[i][j];
    }
}

int dfs(int y, int x, char c, bool bomb){
    int res = 1;

    // 방문 여부 처리
    visited[y][x] = true;
    if(bomb) map[y][x] = '.';
    
    // 다음 방문점 찾기
    for(int d=0; d<4; d++){
        int ny = y+dy[d];
        int nx = x+dx[d];
        if(ny<0 || ny>=R || nx<0 || nx>=C) continue;
        if(map[ny][nx]!=c || visited[ny][nx]) continue;
        res += dfs(ny, nx, c, bomb);
    }

    return res;
}

void gravity(){
    for(int x=0; x<C; x++){
        
        queue<char> q;
        for(int y=R-1; y>=0; y--){
            if(map[y][x]!='.') q.push(map[y][x]);
            map[y][x] = '.';
        }

        int y = R-1;
        while(!q.empty()){
            map[y--][x] = q.front();
            q.pop();
        }
    }
}

void solve(){
    int ans = 0;
    while(true){

        // 1. 연쇄 작용
        bool isBomb = false;
        memset(visited, false, sizeof(visited)); // 초기화
        for(int y=0; y<R; y++){
            for(int x=0; x<C; x++){
                if(map[y][x] == '.') continue;

                // 4개 이상 연결되어 있는 지 확인
                int cnt = dfs(y, x, map[y][x], false);
                
                // 4개 이상인 경우 폭발 진행
                memset(visited, false, sizeof(visited)); // 초기화
                if(cnt >= 4) {
                    isBomb = true;
                    dfs(y, x, map[y][x], true); 
                }
            }
        }
        
        // 2. 더 이상 연쇄 작용이 일어나지 않는 경우
        if(!isBomb) break;

        // 3. 중력 작용
        gravity();

        // 4. 횟수 증가
        ans++;
    }
    cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int TC; cin >> TC;
    while(TC--){
        input();
        solve();
    }
}