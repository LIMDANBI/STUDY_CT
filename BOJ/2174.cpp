#include<iostream>
#include<vector>
#define MAX 101
using namespace std;

struct ROBOT{int y, x, d;};
vector<ROBOT> robot(MAX);

int A, B, N, M;
int map[MAX][MAX];
int dy[] = {1, 0, -1, 0}; // N E S W
int dx[] = {0, 1, 0, -1};


void input(){
    cin >> A >> B;
    cin >> N >> M;

    int y, x, cd; char d;
    for (int i = 1; i <= N; i++){
        cin >> x >> y >> d;
        if(d=='N') cd=0; 
        if(d=='E') cd=1;
        if(d=='S') cd=2;
        if(d=='W') cd=3;
        robot[i] = {y, x, cd}; 
        map[y][x] = i;
    }
}

void solution(){

    int rnum, rcnt; char order;
    while(M--){ // simulation
        cin >> rnum >> order >> rcnt;

        int y = robot[rnum].y;
        int x = robot[rnum].x;
        int d = robot[rnum].d;
        while (rcnt--){
            if(order=='L') d=(d+3)%4; // 현재 방향을 기준으로 왼쪽으로 90도 회전
            else if(order=='R') d=(d+1)%4; // 현재 방향을 기준으로 오른쪽으로 90도 회전
            else if(order=='F'){
                map[y][x] = 0;
                y += dy[d]; x += dx[d];
                if(y<1 || y>B || x<1 || x>A) { // 범위를 벗어나는 경우
                    cout << "Robot " << rnum << " crashes into the wall";
                    return;
                }
                if(map[y][x]!=0){ // 충돌하는 경우
                    cout << "Robot " << rnum << " crashes into robot " << map[y][x];
                    return;
                }
                robot[rnum] = {y, x, d}; // update
                map[y][x] = rnum;
            }
            robot[rnum].d = d; // update
        }
    }
    cout << "OK";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}