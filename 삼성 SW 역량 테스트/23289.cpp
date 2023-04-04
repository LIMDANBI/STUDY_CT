#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#define EMPTY 0
#define NEED 5
#define MAX 21
using namespace std;

struct POS {int r, c, d;}; // 좌표, 온풍기 번호
vector<POS> heater, check;

int R, C, K;
bool visited[MAX][MAX];
bool wall[MAX][MAX][4];
int map[MAX][MAX], tmpMap[MAX][MAX];
int dr[] = {0, 0, -1, 1}; // 우 좌 상 하
int dc[] = {1, -1, 0, 0};
int dy[][3] = {
    {-1, 0, 1}, // 우
    {-1, 0, 1}, // 좌
    {-1, -1, -1}, // 상
    {1, 1, 1} // 하
};
int dx[][3] = {
    {1, 1, 1}, // 우
    {-1, -1, -1}, // 좌
    {-1, 0, 1}, // 상
    {-1, 0, 1} // 하
};

void input(){
    cin >> R >> C >> K;

    int d;
    for (int r = 0; r < R; r++){
        for (int c = 0; c < C; c++){
            cin >> d;
            if(d == EMPTY) continue;
            if(d == NEED) check.push_back({r, c, d}); // 온도 조사가 필요한 칸
            else heater.push_back({r, c, d-1}); // 온풍기
        }
    }

    int W, r, c, t; // 좌표 -1 (idx 0부터 사용)
    cin >> W;
    while(W--){
        cin >> r >> c >> t; r--; c--;
        if(t==0){
            wall[r][c][2] = true; // 상
            if(r-1>=0) wall[r - 1][c][3] = true; // 하
        }
        else{
            wall[r][c][0] = true; // 우
            if(c+1<C) wall[r][c+1][1] = true; // 좌
        }
    }
}

void wind(){ // 집에 있는 모든 온풍기에서 바람이 한 번 나옴 (벽 고려)

    for (int h = 0; h < (int)heater.size(); h++){
        memset(visited, false, sizeof(visited));
        int hy = heater[h].r;
        int hx = heater[h].c;
        int hd = heater[h].d;

        queue<POS> q;
        q.push({hy+dr[hd], hx+dc[hd], 5});
        visited[hy+dr[hd]][hx+dc[hd]] = true;

        while (!q.empty()){
            int y = q.front().r;
            int x = q.front().c;
            int cnt = q.front().d;
            map[y][x] += cnt;
            q.pop();

            for (int d = 0; d < 3; d++){
                int ny = y + dy[hd][d];
                int nx = x + dx[hd][d];
                if(ny<0 || ny>=R || nx<0 || nx>=C || cnt-1==0 || visited[ny][nx]) continue; // 범위를 벗어나는 경우, 이미 방문한 경우
                if(d==0) { // 상
                    if(hd<2 && (wall[ny][x][hd] || wall[y][x][2])) continue; // 우 좌
                    if(hd>=2 && (wall[y][nx][hd] || wall[y][x][1])) continue; // 상 하
                }
                if(d==1 && wall[y][x][hd]) continue; // 중
                if(d==2) { // 하
                    if(hd<2 && (wall[ny][x][hd] || wall[y][x][3])) continue; // 우 좌
                    if(hd>=2 && (wall[y][nx][hd] || wall[y][x][0])) continue; // 상 하
                }
                q.push({ny, nx, cnt - 1});
                visited[ny][nx] = true;
            }
        }
    }
}

void control(){ // 온도 조절 (벽 고려)
    for (int r = 0; r < R; r++){
        for (int c = 0; c < C; c++){

            for (int d = 0; d < 4; d+=2){ // (우 상) 방향으로만 탐색 (겹치는 경우가 있음)
                int nr = r + dr[d];
                int nc = c + dc[d];
                if(nr<0 || nr>=R || nc<0 || nc>=C || wall[r][c][d]) continue;
                int diff = abs(map[r][c] - map[nr][nc])/4;
                if(map[r][c] < map[nr][nc]) {
                    tmpMap[nr][nc] -= diff;
                    tmpMap[r][c] += diff;
                }
                else {
                    tmpMap[nr][nc] += diff;
                    tmpMap[r][c] -= diff;
                }
            }
        }
    }

    for (int r = 0; r < R; r++){
        for (int c = 0; c < C; c++){
            map[r][c] += tmpMap[r][c];
            tmpMap[r][c] = 0; // init
        }
    }
}

void reduce(){ // 온도가 1 이상인 가장 바깥쪽 칸의 온도가 1씩 감소
    for (int c = 0; c < C; c++) map[0][c] = max(0, map[0][c] - 1);
    for (int r = 1; r < R; r++) map[r][C-1] = max(0, map[r][C-1] - 1);
    for (int c = 0; c < C-1; c++) map[R-1][c] = max(0, map[R-1][c] - 1);
    for (int r = 1; r < R-1; r++) map[r][0] = max(0, map[r][0] - 1);
}

bool isEnd(){ // 조사하는 모든 칸의 온도가 K 이상이 되었는지 검사
    for (int i = 0; i < (int)check.size(); i++){
        int r = check[i].r;
        int c = check[i].c;
        if(map[r][c] < K) return false;
    } return true;
}

void solution(){
    int ans = 0;
    while(true){
        wind();
        control();
        reduce();
        if (++ans > 100) break;
        if(isEnd()) break;
    } cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}