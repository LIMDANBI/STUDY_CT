#include<iostream>
#include<cstring>
#define MAX 4
#define SIZE 8
using namespace std;

int dirs[MAX]; // 회전 방향 저장
string gear[MAX]; // N극은 0, S극은 1

void rotate(int num, int dir){
    if(dir == -1){ // 반시계 방향 회전
        gear[num] = gear[num] + gear[num][0];
        gear[num] = gear[num].substr(1, SIZE);
    }
    else{ // 시계 방향 회전
        gear[num] = gear[num][SIZE-1] + gear[num];
        gear[num] = gear[num].substr(0, SIZE);
    }
}

void solution(){
    for(int i=0; i<MAX; i++) cin >> gear[i];
    int K; cin >> K;

    int num, dir;
    while(K--){

        // 1. 방향 정하기
        cin >> num >> dir;
        num--; // start with 0 index
        memset(dirs, 0, sizeof(dirs)); // init

        // 2. 방향 저장
        dirs[num] = dir;
        for(int i=num-1; i>=0; i--) { // 좌측 방향
            if(gear[i][2] == gear[i+1][6]) break; // 서로 맞닿은 톱니의 극이 같은 경우
            if(dirs[i+1] == -1) dirs[i] = 1;
            else dirs[i] = -1;
        }
        for(int i=num+1; i<MAX; i++) { // 우측 방향
            if(gear[i-1][2] == gear[i][6]) break;
            if(dirs[i-1] == -1) dirs[i] = 1;
            else dirs[i] = -1;
        }

        // 3. 회전
        for(int i=0; i<MAX; i++){
            if(dirs[i] == 0) continue;
            rotate(i, dirs[i]);
        }
    }
}

void output(){
    int ans = 0;
    int power2[] = {1, 2, 4, 8}; 
    for(int i=0; i<MAX; i++){
        if(gear[i][0] == '1') ans+=power2[i]; // S극
    } cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    solution();
    output();
}