#include<iostream>
#include<cstring>
#include<queue>
#define INF 1000000001
#define MAX 21
#define WALL 1
#define EMPTY 0
using namespace std;

struct POS{int y, x;};
struct DATA{
    int y, x, cost;
    bool operator < (const DATA &d) const {
        if(cost == d.cost){
            if(y == d.y) return x > d.x; // 열 번호가 가장 작은 승객
            return y > d.y; // 행 번호가 가장 작은 승객
        } return cost > d.cost; //  최단거리가 가장 짧은 승객
    }
};

int N, M;
int ty, tx, fuel=0;
bool map[MAX][MAX];
bool visited[MAX][MAX];
POS passenger[MAX][MAX]; // 승객 정보 저장
int Dy[] = {-1, 1, 0, 0};
int Dx[] = {0, 0, -1, 1};

void input(){
    cin >> N >> M >> fuel;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++) cin >> map[i][j];
    }
    cin >> ty >> tx; 

    int sy, sx, dy, dx;
    for(int i=0; i<M; i++){
        cin >> sy >> sx >> dy >> dx;
        passenger[sy][sx] = {dy, dx};
    }
}

DATA nearest_passenger(){

    priority_queue<DATA> pq;

    queue<DATA> q;
    q.push({ty, tx, 0}); // 택시 출발 
    visited[ty][tx] = true;

    while(!q.empty()){
        int y = q.front().y;
        int x = q.front().x;
        int cost = q.front().cost;
        q.pop();

        if(passenger[y][x].y) pq.push({y, x, cost});

        for(int d=0; d<4; d++){
            int ny = y+Dy[d];
            int nx = x+Dx[d];
            if(ny<1 || ny>N || nx<1 || nx>N) continue; // 범위를 벗어나는 경우
            if(map[ny][nx]==WALL || visited[ny][nx]) continue; // 벽인 경우, 이미 방문한 경우
            visited[ny][nx] = true;
            q.push({ny, nx, cost+1});
        }
    }
    if(pq.empty()) return {0, 0, INF}; // 모든 손님을 이동시킬 수 없는 경우
    return pq.top();
}

int move_passenger(int dy, int dx){ // 도착지 좌표
    queue<DATA> q;
    q.push({ty, tx, 0}); // 택시 출발 
    visited[ty][tx] = true;

    while(!q.empty()){
        int y = q.front().y;
        int x = q.front().x;
        int cost = q.front().cost;
        q.pop();

        if(y==dy && x==dx) return cost; // 목적지로 이동할 때까지 소비한 연료

        for(int d=0; d<4; d++){
            int ny=y+Dy[d];
            int nx=x+Dx[d];
            if(ny<1 || ny>N || nx<1 || nx>N) continue; // 범위를 벗어나는 경우
            if(map[ny][nx]==WALL || visited[ny][nx]) continue; // 벽인 경우, 이미 방문한 경우
            visited[ny][nx] = true;
            q.push({ny, nx, cost+1});
        }
    }
    return INF;  // 모든 손님을 이동시킬 수 없는 경우
}

void solution(){
    int complete=0, needFuel=0;
    while(complete < M){

        // go to passenger
        memset(visited, false, sizeof(visited)); // init
        DATA info = nearest_passenger(); 
        needFuel = info.cost;
        if(fuel < needFuel) {cout << -1; return;} // 연료가 부족한 경우
        fuel-=needFuel; // 연료 소모 (승객을 태우러 이동)
        ty = info.y; tx = info.x; // 택시 위치 update
        POS next = passenger[ty][tx]; // 승객의 도착지
        passenger[ty][tx] = {0,0}; // 해당 승객은 태웠음 (재방문 방지)

        // go to destination
        memset(visited, false, sizeof(visited));
        needFuel = move_passenger(next.y, next.x);
        ty = next.y; tx = next.x; // 택시 위치 update
        if(fuel < needFuel) {cout << -1; return;}
        fuel += needFuel; // 연료 충전
        complete++; // 이동을 완료한 손님 수 
    }
    cout << fuel;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}