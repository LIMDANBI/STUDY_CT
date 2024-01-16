#include<iostream>
#include<algorithm>
#include<queue>
#define MAX 5001
using namespace std;

struct BUS{
    int x1, y1, x2, y2;
    bool is_in(const int &x, const int &y){
        return (x1<=x && x<=x2 && y1<=y && y <=y2);
    }
    bool is_in(const BUS &b){
        return (b.x1<=x2 && x1<=b.x2 && b.y1<=y2 && y1<=b.y2);
    }
};

int M, N, K;
BUS bus[MAX];
int usedcnt[MAX];
int sx, sy, dx, dy; // 출발지, 목적지

void input(){
    cin >> M >> N >> K;
    int b, x1, y1, x2, y2;
    for(int i=0; i<K; i++){
        cin >> b >> x1 >> y1 >> x2 >> y2;
        if(x1>x2) swap(x1, x2);
        if(y1>y2) swap(y1, y2);
        bus[b] = {x1, y1, x2, y2};
    }
    cin >> sx >> sy >> dx >> dy;
}

int bfs(){ // 이용하는 최소 버스 수
    
    queue<int> q;

    // 1. 처음 탈 수 있는 버스 queue에 넣기
    for(int b=1; b<=K; b++){
        if(!bus[b].is_in(sx, sy)) continue;
        usedcnt[b] = 1;
        q.push(b);
    }

    // 2. bfs
    while(!q.empty()){
        int now = q.front(); q.pop();
        if(bus[now].is_in(dx, dy)) return usedcnt[now];
        
        for(int b=1; b<=K; b++){
            if(usedcnt[b]) continue;
            if(bus[now].is_in(bus[b])){
                usedcnt[b] = usedcnt[now]+1;
                q.push(b);
            }
        }
    }
}


int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    cout << bfs();
}