#include<iostream>
#include<vector>
#define EMPTY 0
#define WALL 6
#define MAX 10
using namespace std;

struct CCTV{int y, x, num;};
vector<CCTV> cctv;

int N, M, ans = MAX*MAX;
int dy[] = {0, 1, 0, -1};  // → ↓ ← ↑
int dx[] = {1, 0, -1, 0};
int dir[MAX], map[MAX][MAX], copy_map[MAX][MAX];

void input(){
    cin >> N >> M;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> map[i][j];
            if(0<map[i][j] && map[i][j]<6) cctv.push_back({i, j, map[i][j]}); // cctv 위치, 종류 저장
        }
    }
}

void check_area(int y, int x, int d){
    int ny=y, nx=x;
    while(1){
        if(ny<0 || ny>=N || nx<0 || nx>=M || map[ny][nx]==WALL) return; // 범위를 벗어나는 경우, 벽인 경우
        copy_map[ny][nx] = map[y][x]; // 감시 영역 check
        ny+=dy[d]; nx+=dx[d]; // move
    }
}

int get_blind_spot(){
    
    // copy 
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++) copy_map[i][j] = map[i][j];
    }

    // check surveillance area
    for(int i=0; i<cctv.size(); i++){ // cctv 종류에 따라 감시 영역 체크
        int num = cctv[i].num;
        int y = cctv[i].y, x = cctv[i].x;
        if(num == 1) check_area(y, x, dir[i]);
        else if(num == 2){
            check_area(y, x, dir[i]);
            check_area(y, x, (dir[i]+2)%4);
        }
        else if(num == 3){
            check_area(y, x, dir[i]);
            check_area(y, x, (dir[i]+1)%4);
        }
        else if(num == 4){
            check_area(y, x, dir[i]);
            check_area(y, x, (dir[i]+1)%4);
            check_area(y, x, (dir[i]+2)%4);
        }
        else{
            check_area(y, x, dir[i]);
            check_area(y, x, (dir[i]+1)%4);
            check_area(y, x, (dir[i]+2)%4);
            check_area(y, x, (dir[i]+3)%4);
        }
    }

    // check blind spot
    int blind_spot = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(copy_map[i][j] == EMPTY) blind_spot++;
        }
    } return blind_spot;
}

void solution(int cnt){
    if(cnt == cctv.size()){
        ans = min(ans, get_blind_spot());
        return;
    }
    for(int i=0; i<4; i++){
        dir[cnt] = i; // cctv 방향 설정
        solution(cnt+1);
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution(0);
    cout << ans;
}