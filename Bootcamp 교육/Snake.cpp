#include<iostream>
#include<queue>
#include<deque>
#define MAX 101
using namespace std;

struct INFO{ int t; char c;};
struct SNAKE{int y, x;};

int N, K, L;
queue<INFO> path; // 경로
deque<SNAKE> snake; // 뱀
bool map[MAX][MAX];
bool fruit[MAX][MAX]; // 과일
int dy[] = {0, 1, 0, -1}; // 우 하 좌 상
int dx[] = {1, 0, -1, 0};

void input(){

    // 격자 정보
    cin >> N;
    
    // 과일 정보
    cin >> K;
    for(int i=0, r, c; i<K; i++){
        cin >> r >> c;
        fruit[r][c] = true;
    }

    // 경로 정보
    cin >> L;
    int x; char c;
    for(int i=0; i<L; i++){
        cin >> x >> c;
        path.push({x, c});
    }
}

int solve(){
    
    // 1. 처음 뱀의 위치 설정
    map[1][1] = true;
    snake.push_back({1, 1});

    // 2. 게임 진행
    int t=0; // 시간
    int d=0; // 뱀이 보고 있는 방향
    while(++t){

        // (1) 뱀의 이동
        int y = snake.front().y;
        int x = snake.front().x;

        int ny = y+dy[d];
        int nx = x+dx[d];

        // 뱀이 벽 또는 자기 자신과 부딪히는 경우
        if(ny<1 || ny>N || nx<1 || nx>N || map[ny][nx]) return t;

        // 뱀 정보 기록
        map[ny][nx] = true;
        snake.push_front({ny, nx});

        if(fruit[ny][nx]){ // 과일을 먹는 경우
            fruit[ny][nx] = false;
        }
        else{ // 과일을 먹지 못하는 경우
            y = snake.back().y;
            x = snake.back().x;
            map[y][x] = false;
            snake.pop_back();
        }

        // (2) 뱀의 회전
        if(path.front().t == t){
            if(path.front().c == 'D') d=(d+1)%4; // 오른쪽 90도
            else d=(d+3)%4; // 왼쪽 90도
            path.pop();
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    cout << solve();
}