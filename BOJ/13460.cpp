#include<iostream>
#define MAX 11
#define INF 987654321
using namespace std;

int N, M;
int ans = INF;
string board[MAX];

int y1, x1, y2, x2;
int dy[] = {-1,1,0,0}; // 상 하 좌 우
int dx[] = {0,0,-1,1};

void input(){
    cin >> N >> M;
    for(int i=0; i<N; i++) {
        cin >> board[i];
        for(int j=0; j<M; j++){
            if(board[i][j] == 'R'){ // 빨간 구슬 초기 위치 저장
                y1 = i;
                x1 = j;
            }
            if(board[i][j] == 'B'){ // 파라 구슬 초기 위치 저장
                y2 = i;
                x2 = j;
            }
        }
    }
}

void print_board(){
    for(int i=0; i<N; i++) cout << board[i] << "\n";
}

void simulation(int cnt, int dir, int ry, int rx, int by, int bx){ 
    
    if(cnt == 10) return; // 10번 이하로 움직여서 빨간 구슬을 구멍을 통해 빼낼 수 없으면 -1을 출력
    
    // copy
    string copy_board[MAX];
    for(int i=0; i<N; i++) copy_board[i] = board[i]; 


    
    // red 
    while(){

    }

    // blue 
    while(){

    }
    

    for(int i=0; i<4; i++) {
        simulation(cnt+1, i, ry, rx, by, bx);
        for(int i=0; i<N; i++) board[i] = copy_board[i]; // recover
    }
}

void solution(){
    simulation(-1, -1, y1, x1, y2, x2); 
    if(ans == INF) cout << -1;
    else cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}