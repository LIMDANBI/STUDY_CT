#include<iostream>
#include<cstring>
#include<queue>
#define MAX 1005
using namespace std;

struct POS{int y, x;};

int W, H;
queue<POS> sg;
queue<POS> fire;
char map[MAX][MAX];
bool visited[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void init(){
    while (!sg.empty()) sg.pop();
    while (!fire.empty()) fire.pop();
    memset(visited, false, sizeof(visited));
}

void input(){
    cin >> W >> H;
    for (int i = 0; i < H; i++){
        for (int j = 0; j < W; j++){
            cin >> map[i][j];
            if(map[i][j] == '@'){ // 상근이
                map[i][j] = '.';
                visited[i][j] = true;
                sg.push((POS){i, j});
            }
            else if(map[i][j] == '*'){ // 불
                visited[i][j] = true;
                fire.push((POS){i, j});
            }
        }
    }
}

void solve(){

    int ans = -1, turn = 0;
    while (ans==-1 && !sg.empty()){

        // 1. turn 횟수 증가
        turn++;

        // 2. 불 먼저 이동
        int fire_size = (int)fire.size();
        while (fire_size--){
            int y = fire.front().y;
            int x = fire.front().x;
            fire.pop();

            for (int d = 0; d < 4; d++){
                int ny = y + dy[d];
                int nx = x + dx[d];
                if (ny < 0 || ny >= H || nx < 0 || nx >= W || visited[ny][nx]) continue; // 범위를 벗어나는 경우, 이미 방문한 경우
                if (map[ny][nx] == '.') { // 빈칸인 경우
                    map[ny][nx] = '*';
                    visited[ny][nx] = true;
                    fire.push((POS){ny, nx});
                }
            }
        }

        // 3. 상근이 이동
        int sg_size = (int)sg.size();
        while(sg_size--){
            int y = sg.front().y;
            int x = sg.front().x;
            sg.pop();

            for (int d = 0; d < 4; d++){
                int ny = y + dy[d];
                int nx = x + dx[d];
                if (ny < 0 || ny >= H || nx < 0 || nx >= W ) { // 빌딩을 탈출하는 경우
                    ans = turn;
                    break;
                }
                if (!visited[ny][nx] && map[ny][nx] == '.') { // 빈칸인 경우
                    visited[ny][nx] = true;
                    sg.push((POS){ny, nx});
                }
            }
        }
    }

    if(ans == -1) cout << "IMPOSSIBLE\n";
    else cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int TC; cin >> TC;
    while (TC--){
        init();
        input();
        solve();
    }    
}