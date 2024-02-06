#include<iostream>
#define INF 1e9
#define MAXH 5
#define MAXW 9
using namespace std;

struct POS{
    int y, x;
} pos[MAXW];

int P;
int solremain, solmove;
char map[MAXH+2][MAXW+2];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input(){
    for (int h=1; h<=MAXH; h++){
        for(int w=1; w<=MAXW; w++){
            cin >> map[h][w];
            if(map[h][w] == 'o') P++;
        }
    }
}

void simul(int cnt, int move){

    // 1. 답 갱신
    if(cnt <= solremain){
        if(cnt == solremain) solmove = min(move, solmove);
        else{
            solremain = cnt;
            solmove = move;
        }
    }

    // 2. 다음 핀 확인
    for(int y=1; y<=MAXH; y++){
        for(int x=1; x<=MAXW; x++){
            if(map[y][x] != 'o') continue;

            for(int d=0; d<4; d++){
                int ny = y+dy[d];
                int nx = x+dx[d];
                
                // 인접한 칸이 핀인지 확인
                if(ny<1 || ny>MAXH || nx<1 || nx>MAXW) continue;
                if(map[ny][nx] != 'o') continue;

                // 인접한 핀을 뛰어 넘는 칸이 빈칸인지 확인
                int nny = ny+dy[d];
                int nnx = nx+dx[d];
                if(nny<1 || nny>MAXH || nnx<1 || nnx>MAXW) continue;
                if(map[nny][nnx] != '.') continue;

                map[y][x] = '.';
                map[ny][nx] = '.';
                map[nny][nnx] = 'o';

                simul(cnt-1, move+1);

                map[y][x] = 'o';
                map[ny][nx] = 'o';
                map[nny][nnx] = '.';
            }
        }
    }

}

void solve(){

    // 1. 초기화
    solremain = P;
    solmove = INF;

    // 2. 시뮬레이션
    simul(P, 0);

    // 3. 초기화
    P = 0;

    // 4. 정답 출력
    cout << solremain << " " << solmove << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int TC; cin >> TC;
    while(TC--){
        input();
        solve();
    }
}