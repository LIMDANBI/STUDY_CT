#include<iostream>
#include<string>
#include<vector>
#include<queue>
#define MAX 51
using namespace std;

struct POS{int y, x;};
queue<POS> waters;

int R, C, sr, sc;
char map[MAX][MAX];
int rtime[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void init(){
    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++) rtime[i][j] = -1;
    }
    while(!waters.empty()) waters.pop();
}

void input(){
    cin >> R >> C;
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            cin >> map[i][j]; // input
            if(map[i][j] == '*') { // 홍수 시작점
                waters.push({i, j});
            }
            else if(map[i][j] == 'S'){ // 화가 출발지
                sr = i; sc = j;
                map[i][j] = '.';
            }
        }
    }
}

void moveWater(){
    int size = waters.size();
    while (size--){
        int y = waters.front().y;
        int x = waters.front().x;
        waters.pop();

        for(int d=0; d<4; d++){
            int ny = y+dy[d];
            int nx = x+dx[d];
            if(ny<0 || ny>=R || nx<0 || nx>=C) continue; // 범위를 벗어나는 경우
            if(map[ny][nx] != '.') continue; // 이동 불가능한 곳
            waters.push({ny, nx});
            map[ny][nx] = '*';
        }
    }
}

void print_water() {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) cout << map[i][j];
        cout << "\n";
    }
}

string bfs(){

    // 1. 초기값 처리
    queue<POS> q;
    q.push({sr, sc});
    rtime[sr][sc] = 0;

    // 2. bfs
    int nt = 0;
    while (!q.empty()){
        int y = q.front().y;
        int x = q.front().x;
        q.pop();

        // 바버의 굴로 도망치는 데 성공한 경우
        if(map[y][x] == 'D') return to_string(rtime[y][x]);
        
        // 홍수 이동 (시간 마다)
        if(nt == rtime[y][x]){
            moveWater();
            nt++;
        }

        // 화가 이동
        for(int d=0; d<4; d++){
            int ny = y+dy[d];
            int nx = x+dx[d];
            if(ny<0 || ny>=R || nx<0 || nx>=C) continue; // 범위를 벗어나는 경우
            if(map[ny][nx]=='X' || map[ny][nx]=='*' || rtime[ny][nx]>=0) continue; // 바위, 홍수, 이미 방문
            rtime[ny][nx] = rtime[y][x] + 1;
            q.push({ny, nx});
        }
    }

    // 비버의 굴로 도망칠 수 없는 경우
    return "KAKTUS";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int TC; cin >> TC;
    while(TC--){
        init();
        input();
        cout << bfs() << "\n";
    }
}