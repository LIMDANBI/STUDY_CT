#include<iostream>
#include<string>
#define MAX 11
#define EMPTY 0
#define WALL 1
#define HOLE -1
using namespace std;

int N, M;
int ans=MAX;
int ry, rx, by, bx;
int map[MAX][MAX];

void input(){
    cin >> N >> M;

    string line;
    for(int i=0; i<N; i++){
        cin >> line;
        for(int j=0; j<M; j++){
            if(line[j] == '.') map[i][j] = EMPTY;
            else if(line[j] == '#') map[i][j] = WALL;
            else if(line[j] == 'O') map[i][j] = HOLE;
            else if(line[j] == 'R') { ry=i; rx=j; map[i][j] = EMPTY; }
            else if(line[j] == 'B') { by=i; bx=j; map[i][j] = EMPTY; }
        }
    }
}

bool move_up(int cnt){

    int ny;
    bool redfall=false, bluefall = false;

    if(rx == bx){ // 같은 열에 있는 경우
        if(ry < by){ // 빨간 구슬이 더 위에 있는 경우
            // 빨간 구슬 먼저 움직임
            ny=ry;
            while(1){
                ry=ny; ny--;
                if(map[ny][rx] == WALL) break;
                if(map[ny][rx] == HOLE) {redfall=true; ry=-1; break;}
            }

            // 파란 구슬 움직임
            ny=by;
            while(1){
                by=ny; ny--;
                if(ny==ry) break; // 빨간 구슬을 만난 경우
                if(map[ny][bx] == WALL) break;
                if(map[ny][bx] == HOLE) {bluefall=true; by=-1; break;}
            }
        }
        else{ // 파란 구슬이 더 위에 있는 경우

            // 파란 구슬 먼저 움직임
            ny=by;
            while(1){
                by=ny; ny--;
                if(map[ny][bx] == WALL) break;
                if(map[ny][bx] == HOLE) {bluefall=true; by=-1; break;}
            }

            // 빨간 구슬 움직임
            ny=ry;
            while(1){
                ry=ny; ny--;
                if(ny==by) break; // 파란 구슬을 만난 경우
                if(map[ny][rx] == WALL) break;
                if(map[ny][rx] == HOLE) {redfall=true; ry=-1; break;}
            }
        }
    }
    else{ // 각 구슬이 움직임
        ny=ry; // 빨간 구슬
        while(1){
            ry=ny; ny--;
            if(map[ny][rx] == WALL) break;
            if(map[ny][rx] == HOLE) {redfall=true; ry=-1; break;}
        }

        ny=by; // 파란 구슬
        while(1){
            by=ny; ny--;
            if(map[ny][bx] == WALL) break;
            if(map[ny][bx] == HOLE) {bluefall=true; by=-1; break;}
        }
    }

    if(redfall && bluefall) return false;
    if(redfall) {ans = min(ans, cnt); return false;}
    return true;
}

bool move_down(int cnt){
    int ny;
    bool redfall=false, bluefall = false;

    if(rx == bx){ // 같은 열에 있는 경우
        if(ry < by){ // 파란 구슬이 더 아래 있는 경우
            // 파란 구슬 먼저 움직임
            ny=by;
            while(1){
                by=ny; ny++;
                if(map[ny][bx] == WALL) break;
                if(map[ny][bx] == HOLE) {bluefall=true; by=-1; break;}
            }

            // 빨간 구슬 움직임
            ny=ry;
            while(1){
                ry=ny; ny++;
                if(ny==by) break; // 파란 구슬을 만난 경우
                if(map[ny][rx] == WALL) break;
                if(map[ny][rx] == HOLE) {redfall=true; ry=-1; break;}
            }
        }
        else{ // 빨간 구슬이 더 아래 있는 경우
            // 빨간 구슬 먼저 움직임
            ny=ry;
            while(1){
                ry=ny; ny++;
                if(map[ny][rx] == WALL) break;
                if(map[ny][rx] == HOLE) {redfall=true; ry=-1; break;}
            }

            // 파란 구슬 움직임
            ny=by;
            while(1){
                by=ny; ny++;
                if(ny==ry) break; // 빨간 구슬을 만난 경우
                if(map[ny][bx] == WALL) break;
                if(map[ny][bx] == HOLE) {bluefall=true; by=-1; break;}
            }
        }
    }
    else{ // 각 구슬이 움직임
        ny=ry; // 빨간 구슬
        while(1){
            ry=ny; ny++;
            if(map[ny][rx] == WALL) break;
            if(map[ny][rx] == HOLE) {redfall=true; ry=-1; break;}
        }

        ny=by; // 파란 구슬
        while(1){
            by=ny; ny++;
            if(map[ny][bx] == WALL) break;
            if(map[ny][bx] == HOLE) {bluefall=true; by=-1; break;}
        }
    }

    if(redfall && bluefall) return false;
    if(redfall) {ans = min(ans, cnt); return false;}
    return true;
}

bool move_left(int cnt){
    int nx;
    bool redfall=false, bluefall = false;

    if(ry == by){ // 같은 행에 있는 경우
        if(rx < bx){ // 빨간 구슬이 더 왼쪽에 있는 경우
            // 빨간 구슬 먼저 움직임
            nx=rx;
            while(1){
                rx=nx; nx--;
                if(map[ry][nx] == WALL) break;
                if(map[ry][nx] == HOLE) {redfall=true; rx=-1; break;}
            }

            // 파란 구슬 움직임
            nx=bx;
            while(1){
                bx=nx; nx--;
                if(nx==rx) break; // 빨간 구슬을 만난 경우
                if(map[by][nx] == WALL) break;
                if(map[by][nx] == HOLE) {bluefall=true; bx=-1; break;}
            }
        }
        else{ // 파란 구슬이 더 왼쪽에 있는 경우
            // 파란 구슬 먼저 움직임
            nx=bx;
            while(1){
                bx=nx; nx--;
                if(map[by][nx] == WALL) break;
                if(map[by][nx] == HOLE) {bluefall=true; bx=-1; break;}
            }

            // 빨간 구슬 움직임
            nx=rx;
            while(1){
                rx=nx; nx--;
                if(nx==bx) break; // 파란 구슬을 만난 경우
                if(map[ry][nx] == WALL) break;
                if(map[ry][nx] == HOLE) {redfall=true; rx=-1; break;}
            }
        }
    }
    else{
        nx=rx; // 빨간 구슬
        while(1){
            rx=nx; nx--;
            if(map[ry][nx] == WALL) break;
            if(map[ry][nx] == HOLE) {redfall=true; rx=-1; break;}
        }
        nx=bx; // 파란 구슬
        while(1){
            bx=nx; nx--;
            if(map[by][nx] == WALL) break;
            if(map[by][nx] == HOLE) {bluefall=true; bx=-1; break;}
        }
    }

    if(redfall && bluefall) return false;
    if(redfall) {ans = min(ans, cnt); return false;}
    return true;
}

bool move_right(int cnt){
    int nx;
    bool redfall=false, bluefall = false;

    if(ry == by){ // 같은 행에 있는 경우
        if(rx < bx){ // 파란 구슬이 더 오른쪽에 있는 경우
            // 파란 구슬 먼저 움직임
            nx=bx;
            while(1){
                bx=nx; nx++;
                if(map[by][nx] == WALL) break;
                if(map[by][nx] == HOLE) {bluefall=true; bx=-1; break;}
            }

            // 빨간 구슬 움직임
            nx=rx;
            while(1){
                rx=nx; nx++;
                if(nx==bx) break; // 파란 구슬을 만난 경우
                if(map[ry][nx] == WALL) break;
                if(map[ry][nx] == HOLE) {redfall=true; rx=-1; break;}
            }
        }
        else{ // 빨간 구슬이 더 오른쪽에 있는 경우
            // 빨간 구슬 먼저 움직임
            nx=rx;
            while(1){
                rx=nx; nx++;
                if(map[ry][nx] == WALL) break;
                if(map[ry][nx] == HOLE) {redfall=true; rx=-1; break;}
            }

            // 파란 구슬 움직임
            nx=bx;
            while(1){
                bx=nx; nx++;
                if(nx==rx) break; // 빨간 구슬을 만난 경우
                if(map[by][nx] == WALL) break;
                if(map[by][nx] == HOLE) {bluefall=true; bx=-1; break;}
            }
        }
    }
    else{
        nx=rx; // 빨간 구슬
        while(1){
            rx=nx; nx++;
            if(map[ry][nx] == WALL) break;
            if(map[ry][nx] == HOLE) {redfall=true; rx=-1; break;}
        }
        nx=bx; // 파란 구슬
        while(1){
            bx=nx; nx++;
            if(map[by][nx] == WALL) break;
            if(map[by][nx] == HOLE) {bluefall=true; bx=-1; break;}
        }
    }

    if(redfall && bluefall) return false;
    if(redfall) {ans = min(ans, cnt); return false;}
    return true;
}

void solution(int cnt){
    if(rx<0 || ry<0 || by<0 || bx<0) return; // 이미 구슬이 떨어진 경우
    if(ans<=cnt || cnt==MAX) return; // 이미 더 작은 답을 찾은 경우, 이동 기회를 모두 사용한 경우

    // copy
    int tmp_ry = ry, tmp_rx = rx;
    int tmp_by = by, tmp_bx = bx;

    for(int d=0; d<4; d++){

        if(d==0 && move_up(cnt)) solution(cnt+1);
        else if(d==1 && move_down(cnt)) solution(cnt+1);
        else if(d==2 && move_left(cnt)) solution(cnt+1);
        else if(d==3 && move_right(cnt)) solution(cnt+1);
        
        // recovery
        ry = tmp_ry; rx = tmp_rx;
        by = tmp_by; bx = tmp_bx;
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution(1); // 최소 몇 번 만에 빨간 구슬을 구멍을 통해 빼낼 수 있는지 출력
    ans==MAX ? cout << -1 : cout << ans;
}