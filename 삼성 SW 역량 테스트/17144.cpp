#include<iostream>
#define MAX 51
using namespace std;

int ar = 0;
int R, C, T;
int home[MAX][MAX];
int copy_home[MAX][MAX];
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};
 
void input(){
    cin >> R >> C >> T;
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            cin >> home[i][j];
            if(home[i][j] == -1){
                home[i][j] = 0;
                if(ar==0) ar = i; // 공기 청정기의 위치
            }
        }
    }
}

void dust(){
    int r, c, div;
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            if(home[i][j] == 0) continue; // 먼지가 없거나, 공기청정기인 경우
            div = home[i][j]/5;
            for(int d=0; d<4; d++){
                r = i+dr[d];
                c = j+dc[d];
                if(r<0 || r>=R || c<0 || c>=C) continue; // 범위를 벗어나는 경우
                if((r==ar || r==ar+1) && c==0) continue; // 공기청정기 위치인 경우
                copy_home[r][c] += div;
                copy_home[i][j] -= div;
            }
        }
    }

    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            home[i][j] += copy_home[i][j];
            copy_home[i][j] = 0;
        }
    }
}

void clean(){
    // 위쪽 순환
    for(int i=ar-1; i>0; i--) home[i][0] = home[i-1][0]; // 하
    for(int i=0; i<C-1; i++) home[0][i] = home[0][i+1]; // 좌
    for(int i=0; i<ar; i++) home[i][C-1] = home[i+1][C-1]; // 상
    for(int i=C-1; i>0; i--) home[ar][i] = home[ar][i-1]; // 우

    // 아래쪽 순환
    for(int i=ar+2; i<R-1; i++) home[i][0] = home[i+1][0]; // 상
    for(int i=0; i<C-1; i++) home[R-1][i] = home[R-1][i+1]; // 좌
    for(int i=R-1; i>ar+1; i--) home[i][C-1] = home[i-1][C-1]; // 하
    for(int i=C-1; i>0; i--) home[ar+1][i] = home[ar+1][i-1]; // 우
}

void output(){ // T초가 지난 후 구사과의 방에 남아있는 미세먼지의 양
    int ans = 0;
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++) ans+=home[i][j];
    } cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    while(T--){
        dust(); // 미세먼지가 확산
        clean(); // 공기청정기가 작동
    }
    output();
}