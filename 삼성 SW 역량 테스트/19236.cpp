#include<iostream>
#define MAX 4
#define EMPTY 0
#define SHARK -1
#define FISHNUM 17
using namespace std;

struct FISH{int y, x, d; bool isdead;};
FISH fish[FISHNUM];

int ans = 0;
int map[MAX][MAX];
int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1}; // ↑, ↖, ←, ↙, ↓, ↘, →, ↗ 
int dx[] = {0, -1, -1, -1, 0, 1, 1, 1};

void input(){
    int num, dir;
    for(int y=0; y<MAX; y++){
        for(int x=0; x<MAX; x++){
            cin >> num >> dir;
            fish[num] = {y, x, dir-1, false};
            map[y][x] = num;
        }
    }
}

void move_fish(){
    for(int num=1; num<FISHNUM; num++){
        if(fish[num].isdead) continue;
        int y = fish[num].y;
        int x = fish[num].x;
        int d = fish[num].d;

        int ny, nx, nd;
        for(int dir=0; dir<8; dir++){
            nd = (d+dir)%8;
            ny = y+dy[nd];
            nx = x+dx[nd];
            if(ny<0 || ny>=MAX || nx<0 || nx>=MAX || map[ny][nx]==SHARK) continue;
            break;
        }

        // change
        int other = map[ny][nx];
        map[ny][nx] = num;
        map[y][x] = other;
        
        fish[num] = {ny, nx, nd, false};
        fish[other].y=y; fish[other].x=x; 
    }
}

void move_shark(int y, int x, int d, int eat){ // 상어이동
    ans = max(ans, eat); // 상어가 먹을 수 있는 물고기 번호의 합의 최댓값

    // save
    int tmp_map[MAX][MAX];
    FISH tmp_fish[FISHNUM];
    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++) tmp_map[i][j] = map[i][j];
    }
    for(int i=1; i<FISHNUM; i++) tmp_fish[i] = fish[i];

    move_fish(); // 물고기 이동

    for(int k=1; k<MAX; k++){
        int ny = y + dy[d]*k;
        int nx = x + dx[d]*k;
        if(ny<0 || ny>=MAX || nx<0 || nx>=MAX || map[ny][nx]==EMPTY) continue;
        
        // save
        int num = map[ny][nx];
        map[y][x] = EMPTY;
        map[ny][nx] = SHARK;
        fish[num].isdead = true;

        // 물고기를 먹고, 그 물고기의 방향을 가짐
        move_shark(ny, nx, fish[num].d, eat+num);
        
        // restore
        fish[num].isdead = false;
        map[y][x] = SHARK;
        map[ny][nx] = num;
    }

    // restore
    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++) map[i][j] = tmp_map[i][j];
    }
    for(int i=1; i<FISHNUM; i++) fish[i] = tmp_fish[i];
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    int num = map[0][0];
    map[0][0] = SHARK;
    fish[num].isdead = true; // (0, 0)에 있는 물고기를 먹고,
    move_shark(0, 0, fish[num].d, num); // (0, 0)에 들어감
    cout << ans;
}