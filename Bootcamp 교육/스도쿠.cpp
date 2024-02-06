#include<iostream>
#include<vector>
#define MAX 9
using namespace std;

struct POS{int y, x;};
vector<POS> pos; // 빈칸 좌표

int N; // 빈칸 개수
bool ismake; // 스도쿠를 만들었는지
int sdoku[MAX][MAX]; // 스도쿠 정보

void input(){
    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++){
            cin >> sdoku[i][j];
            if(sdoku[i][j]) continue;
            pos.push_back({i, j});
        }
    }
}

bool check(int y, int x, int num){

    // 1. 가로, 세로 체크
    for(int i=0; i<MAX; i++){
        if(sdoku[i][x] == num) return false; // 가로
        if(sdoku[y][i] == num) return false; // 세로
    }

    // 2. 작은 격자 체크
    y=(y/3*3); x=(x/3*3);
    for(int i=y; i<y+3; i++){
        for(int j=x; j<x+3; j++){
            if(sdoku[i][j] == num) return false;
        }
    }

    return true;
}

void simul(int n){

    // 1. 이미 스도쿠를 만든 경우
    if(ismake) return;

    // 2. 스도쿠를 만드는데 성공한 경우
    if(N <= n){
        ismake = true;
        return; 
    }

    // 3. 다음 빈칸에 들어갈 숫자를 선택
    int y = pos[n].y;
    int x = pos[n].x;
    for(int num=1; num<=MAX; num++){
        if(check(y, x, num)) {            
            sdoku[y][x] = num;
            simul(n+1);
            if(ismake) return;
            sdoku[y][x] = 0;
        }
    }
}

void solve(){
    
    // 1. 초기화
    N = (int)pos.size();

    // 2. 스도쿠 만들기
    simul(0);
}

void output(){
    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++)
            cout << sdoku[i][j] << " ";
        cout << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
    output();
}