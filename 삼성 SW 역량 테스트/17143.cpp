#include<iostream>
#include<vector>
#define MAX 101
using namespace std;

struct SHARK {
    bool isdead;
    int r, c, s, d, z; // 위치, 속력, 이동방향, 크기
};

int pc = 0; // 낚시왕의 위치
int ans = 0; // 낚시왕이 잡은 상어 크기의 합

int R, C, M;
int num[MAX][MAX];
int moved_num[MAX][MAX];
vector<SHARK> shark(MAX*MAX);
int dr[] = {-1, 1, 0, 0}; // 상 하 우 좌
int dc[] = {0, 0, 1, -1};

void input(){
    cin >> R >> C >> M;

    int r, c, s, d, z;
    for(int i=1; i<=M; i++){
        cin >> r >> c >> s >> d >> z;
        num[r][c] = i;
        shark[i] = {false, r, c, s, d-1, z};
    }
}

void catch_shark(){

    // 1. 낚시왕이 오른쪽으로 한 칸 이동
    pc++;

    // 2. 땅과 제일 가까운 상어를 잡음
    for(int pr=1; pr<=R; pr++){
        if(num[pr][pc]==0) continue;
        shark[num[pr][pc]].isdead = true; // 상어를 잡음
        ans += shark[num[pr][pc]].z; // ans update
        num[pr][pc] = 0; // 격자판에서 제거
        return;
    }
}

// 3. 상어 이동
void move_shark(){

    int r, c, s, d;
    for(int i=1; i<=M; i++){
        if(shark[i].isdead) continue; // 잡혔거나, 잡아먹힌 상어
        
        r = shark[i].r;
        c = shark[i].c;
        s = shark[i].s;
        d = shark[i].d;
 
        if(d < 2) s%=(2*R-2); // 상하 !!
        else s%=(2*C-2); // 좌우 !!

        while(s--){ // s칸 이동
            r += dr[d];
            c += dc[d];
            if(r<1 || r>R || c<1 || c>C){
                (d==0 || d==2) ? d++ : d--; // 상우, 하좌 (방향 정보 update)
                shark[i].d = d; // 바뀐 방향 저장 !!
                r += dr[d]*2;
                c += dc[d]*2;
            }
        }

        // 위치 정보 update
        shark[i].r = r;
        shark[i].c = c;

        if(moved_num[r][c] == 0) moved_num[r][c] = i; // 빈 칸인 경우
        else{ // 이미 다른 상어가 있는 경우
            if(shark[i].z > shark[moved_num[r][c]].z){ // 새로 온 상어가 더 큰 경우
                shark[moved_num[r][c]].isdead = true;
                moved_num[r][c] = i;
            }
            else shark[i].isdead = true; // 기존 상어가 더 큰 경우
        }
    }

    // copy and init
    for(int i=1; i<=R; i++){
        for(int j=1; j<=C; j++){
            num[i][j] = moved_num[i][j];
            moved_num[i][j] = 0;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    while(pc < C){
        catch_shark();
        move_shark();
    }
    cout << ans;
}