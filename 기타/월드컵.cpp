#include<iostream>
#define END 15 // 6C2
#define WIN 0
#define TIE 1
#define LOSE 2
#define COUNTRY 6
using namespace std;

int ans[4];
int res[COUNTRY+1][3]; // 0:승, 1:무, 2:패
int ipt[4][COUNTRY+1][3]; // 입력, ipt[i][c][j] : i번 결과에서 c국가의 승/무/패

void input(){
    for(int i=0; i<4; i++){
        for(int c=1; c<=COUNTRY; c++){
            for(int j=0; j<3; j++) cin >> ipt[i][c][j];
        }
    }
}

void check(){
    for(int i=0; i<4; i++){
        bool ispossible = true;
        for(int c=1; c<=COUNTRY && ispossible; c++){
            for(int j=0; j<3 && ispossible; j++) {
                if(ipt[i][c][j] != res[c][j]) ispossible = false;
            }
        }
        if(ispossible) ans[i] = 1; // 가능한 결과임
    }
}

void dfs(int cnt, int a, int b){ // 완전 탐색으로 모든 가능한 경우의 수를 만들어봄
    if(6 < b){
        a++;
        b = a+1;
    }
    if(cnt == END){
        check(); // input과 매치되는 것이 있는지 확인
        return;
    }

    // a국가 승
    res[a][WIN]++; 
    res[b][LOSE]++;
    dfs(cnt+1, a, b+1);
    res[a][WIN]--;
    res[b][LOSE]--;

    // 무승 부
    res[a][TIE]++; 
    res[b][TIE]++;
    dfs(cnt+1, a, b+1);
    res[a][TIE]--; 
    res[b][TIE]--;

    // b국가 승
    res[a][LOSE]++; 
    res[b][WIN]++;
    dfs(cnt+1, a, b+1);
    res[a][LOSE]--; 
    res[b][WIN]--;
}

void output(){
    for(int i=0; i<4; i++) cout << ans[i] << " ";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    dfs(0, 1, 2);
    output();
}