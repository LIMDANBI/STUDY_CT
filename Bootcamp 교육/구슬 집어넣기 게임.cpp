#include<iostream>
#define MAX 11
#define SIZE 20
using namespace std;

int R, C, ans;
int rr, rc, br, bc;
char map[SIZE][SIZE];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void init(){
    ans = MAX;
}

void input(){
    cin >> R >> C;
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            map[i][j] = '.'; // init
            cin >> map[i][j];
            if(map[i][j] == 'R'){
                rr = i; rc = j;
                map[i][j] = '.';
            }
            if(map[i][j] == 'B'){
                br = i; bc = j;
                map[i][j] = '.';
            }
        }
    }
}

void dfs(int cnt, int ry, int rx, int by, int bx){ // 빨간 구슬이 구멍에 들어갈 수 있게 하는 가장 적은 기울임 횟수
    if(ans <= cnt) return; // 가지치기
    if(map[ry][rx] == 'H'){ // 빨간 구슬을 넣는 것에 성공
        ans = cnt;
        return ;
    }

    // dfs (위위위..위 -> 위위위..아래) + 가지치기
    for(int d=0; d<4; d++){
        int nry = ry+dy[d], nrx = rx+dx[d]; // 빨간 구슬
        int nby = by+dy[d], nbx = bx+dx[d]; // 파란 구슬

        // 벽에 막혀 해당 방향으로 움직일 수 없는 경우
        if(map[nry][nrx] == '#'){
            nry = ry;
            nrx = rx;
        }
        if(map[nby][nbx] == '#'){
            nby = by;
            nbx = bx;
        }

        // 불가능한 경우 (구슬이 깨지는 경우, 파란 구슬이 구멍에 들어가는 경우)
        if((nry==nby && nrx==nbx) || map[nby][nbx]=='H') continue;

        // 다음 탐색을 이어서 해야 하는 경우
        dfs(cnt+1, nry, nrx, nby, nbx);
    }
}

void output(){
    if(ans == MAX) ans = -1; // 불가능한 경우
    cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int TC; cin >> TC;
    while(TC--){
        init();
        input();
        dfs(0, rr, rc, br, bc);
        output();
    }
}