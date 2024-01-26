#include<iostream>
#include<queue>
#define MAX 201
#define INF 10001
using namespace std;

int N;
char map[MAX][MAX];
int cost[MAX][MAX];
int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};

void input(){
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) cin >> map[i][j];
    }
}


void init(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) cost[i][j] = INF;
    }
}

void solve(){
    queue<pair<int, int> > q;
    cost[0][0] = 0;
    q.push({0, 0});

    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for(int d=0; d<4; d++){
            int ny = y+dy[d];
            int nx = x+dx[d];
            if(ny<0 || ny>=N || nx<0 || nx>=N) continue;

            int new_cost = cost[y][x] + map[ny][nx]-'0';
            if(new_cost < cost[ny][nx]){ // 비용이 더 줄어드는 경우에만 갱신
                cost[ny][nx] = new_cost;
                q.push({ny, nx});
            }
        }
    }

    cout << cost[N-1][N-1];
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    init();
    solve();
}