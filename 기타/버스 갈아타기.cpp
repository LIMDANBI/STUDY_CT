#include<iostream>
#include<algorithm>
#include<queue>
#define MAX 5001
using namespace std;

struct QUEUE{int x, y, cnt;};
struct BUS{int x1, y1, x2, y2;} bus[MAX];

int M, N, K;
bool used[MAX];
int sx, sy, dx, dy; // 출발지, 목적지

void input(){
    cin >> M >> N >> K;
    int id, x1, y1, x2, y2;
    for(int i=0; i<K; i++){
        cin >> id >> x1 >> y1 >> x2 >> y2;
        if(x1>x2) swap(x1, x2);
        if(y1>y2) swap(y1, y2);
        bus[id] = {x1, y1, x2, y2};
    }
    cin >> sx >> sy >> dx >> dy;
}

int solve(){ // 이용하는 최소 버스 수

    queue<QUEUE> q;

    // 1. 처음 탈 수 있는 버스 queue에 넣기
    for(int id=1; id<=K; id++){
        if(bus[id].x1<=sx && sx<=bus[id].x2 && bus[id].y1<=sy && sy<=bus[id].y2){
            used[id] = true;
            for(int s=bus[id].x1; s<=bus[id].x2; s++){
                for(int e=bus[id].y1; e<=bus[id].y2; e++) {
                    if(s==sx && e==sy) continue;
                    q.push({s, e, 1});
                }
            }
        }
    }

    // 2. bfs
    while(!q.empty()){
        int x = q.front().x;
        int y = q.front().y;
        int cnt = q.front().cnt;
        q.pop();

        if(x==dx && y==dy) return cnt;
        for(int id=1; id<=K; id++){
            if(!(bus[id].x1<=x && x<=bus[id].x2 && bus[id].y1<=y && y<=bus[id].y2) || used[id]) continue;
            used[id] = true;
            for(int s=bus[id].x1; s<=bus[id].x2; s++){
                for(int e=bus[id].y1; e<=bus[id].y2; e++) {
                    if(s==sx && e==sy) continue;
                    q.push({s, e, cnt+1});
                }
            }
        }
    }
    
    return -1;
}


int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    cout << solve();
}