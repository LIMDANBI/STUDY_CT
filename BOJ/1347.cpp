#include<iostream>
#define MAX 101
using namespace std;

struct HJ {int y=50, x=50, d=2;} hj; // 홍준

int moveCnt;
string content;
bool maze[MAX][MAX];
int dy[] = {-1, 0, 1, 0};
int dx[] = {0, 1, 0, -1};

void solution(){
    cin >> moveCnt >> content;
    maze[hj.y][hj.x] = true;

    for(char c : content){
        if(c == 'L'){
            if(--hj.d < 0) hj.d = 3;
        }
        else if(c == 'R'){
            if(++hj.d > 3) hj.d = 0;
        }
        else { // c == 'F'
            hj.y += dy[hj.d];
            hj.x += dx[hj.d];
            maze[hj.y][hj.x] = true;
        }
    }
}

void output(){

    // find boundary
    int sy, sx, ey, ex;
    sy = sx = MAX;
    ey = ex = 0;

    for (int y = 0; y < MAX; y++){
        for (int x = 0; x < MAX; x++){
            if(maze[y][x]){
                if(y < sy) sy = y;
                if(x < sx) sx = x;
                if(y > ey) ey = y;
                if(x > ex) ex = x;
            }
        }
    }

    // print maze
    for (int y = sy; y <= ey; y++){
        for (int x = sx; x <= ex; x++){
            if(maze[y][x]) cout << ".";
            else cout << "#";
        } cout << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    solution();
    output();
}