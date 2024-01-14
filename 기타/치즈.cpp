#include<iostream>
#include<cstring>
#define MAX 101
using namespace std;

int R, C;
int totalCheese;
bool map[MAX][MAX], out[MAX][MAX], tmp[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input(){
    cin >> R >> C;
    for (int i = 0; i < R; i++){
        for (int j = 0; j < C; j++) {
            cin >> map[i][j];
            if(map[i][j]) totalCheese++;
        }
    }
}

void mark_out(int y, int x){
    out[y][x] = true;
    for (int d = 0; d < 4; d++){
        int ny = y + dy[d];
        int nx = x + dx[d];
        if(ny<0 || ny>=R || nx<0 || nx>=C) continue;
        if(out[ny][nx] || map[ny][nx]) continue;
        mark_out(ny, nx);
    }
}

int melt(){
    memset(tmp, false, sizeof(tmp));
    for (int y = 0; y < R; y++){
        for (int x = 0; x < C; x++){
            if(!map[y][x]) continue; // 치즈가 아닌 경우
            for (int d = 0; d < 4; d++){ // 녹는 치즈인지 확인
                int ny = y + dy[d];
                int nx = x + dx[d];
                if(ny<0 || ny>=R || nx<0 || nx>=C) continue;
                if(out[ny][nx]) tmp[y][x] = true; // 녹는 치즈임을 표시
            }
        }
    }

    int res = 0;
    for (int y = 0; y < R; y++){
        for (int x = 0; x < C; x++){
            if(tmp[y][x]){
                map[y][x] = false;
                mark_out(y, x);
                totalCheese--;
                res++;
            }
        }
    }
    return res;
}

void solve(){
    int t = 0, cnt = 0; // 치즈가 모두 녹아서 없어지는 데 걸리는 시간, 모두 녹기 한 시간 전에 남아있는 치즈조각이 놓여 있는 칸의 개수
    mark_out(0, 0);
    while(totalCheese != 0){
        cnt = melt();
        t++;
    }
    cout << t << "\n" << cnt;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}