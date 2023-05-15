#include<iostream>
#define R 5
#define C 9
using namespace std;

int pinCnt, minPin;

char map[R][C];
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

void init(){
    pinCnt = 0;
    minPin = R*C;
}

void input(){
    for (int i = 0; i < R; i++){
        for (int j = 0; j < C; j++){
            cin >> map[i][j];
            if(map[i][j] == 'o') pinCnt++;
        }
    }
}

void backtracking(int pin){
    
    minPin = min(pin, minPin); // ans update

    for (int r = 0; r < R; r++){
        for (int c = 0; c < C; c++){
            if(map[r][c]!='o') continue;
            for (int d = 0; d < 4; d++){
                int nr = r + dr[d];
                int nc = c + dc[d];
                if(nr<0 || nr>=R || nc<0 || nc>=C || map[nr][nc]!='o') continue;

                int nnr = r + dr[d] * 2;
                int nnc = c + dc[d] * 2;
                if(nnr<0 || nnr>=R || nnc<0 || nnc>=C || map[nnr][nnc]!='.') continue;
                map[nnr][nnc] = 'o';
                map[r][c] = map[nr][nc] = '.';
                backtracking(pin - 1);
                map[nnr][nnc] = '.';
                map[r][c] = map[nr][nc] = 'o';
            }
        }
    }
}

int main(){
    freopen("../input.txt", "r", stdin);
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;
    while (N--){
        init();
        input();
        backtracking(pinCnt);
        cout << minPin << " " << pinCnt-minPin << "\n";
    }
}