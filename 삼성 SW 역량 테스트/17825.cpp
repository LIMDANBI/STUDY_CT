#include<iostream>
#define MAX 35
#define DEST 21
#define TURN 10
#define PIECE 4
using namespace std;

int ans=0;
int score[MAX];
int nextP[MAX], blueP[MAX];
int dice[TURN], piece[PIECE];

void init(){

    // 점수판
    for(int i=1; i<21; i++) score[i] = i*2;
    score[22]=13; score[23]=16; score[24]=19;
    score[25]=25; score[26]=30; score[27]=35;
    score[28]=28; score[29]=27; score[30]=26;
    score[31]=22; score[32]=24;

    // 다음 위치
    for(int i=0; i<21; i++) nextP[i]=i+1;
    for(int i=22; i<27; i++) nextP[i] = i+1;
    nextP[21]=21; 
    nextP[27]=20; nextP[28]=29; nextP[29]=30;
    nextP[30]=25; nextP[31]=32; nextP[32]=25;

    // 파란색 지점
    blueP[5]=22; blueP[10]=31; blueP[15]=28;
}

void input(){
    for(int i=0; i<TURN; i++) cin >> dice[i];
}

bool possible(int p, int cnt){
    if(blueP[p]) { p = blueP[p]; cnt--; }
    while(cnt--) p = nextP[p];
    for(int i=0; i<4; i++) {
        if(piece[i] == p && p!=DEST) return false; // 다른 말이 있는데, 도착칸이 아닌 경우
    } return true;
}

void solution(int cnt, int sum){ // 얻을 수 있는 점수의 최댓값
    if(cnt==TURN){
        ans = max(ans, sum);
        return;
    }
    for(int i=0; i<PIECE; i++){ // 말 4개 
        if(!possible(piece[i], dice[cnt])) continue; // 이동이 불가능한 경우

        int before = piece[i]; // copy
        int move_cnt = dice[cnt];

        // move
        if(blueP[piece[i]]) { piece[i] = blueP[piece[i]]; move_cnt--; }
        while(move_cnt--) piece[i] = nextP[piece[i]];
        solution(cnt+1, sum+score[piece[i]]);

        piece[i] = before; // recovery
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    init();
    input();
    solution(0, 0);
    cout << ans;
}