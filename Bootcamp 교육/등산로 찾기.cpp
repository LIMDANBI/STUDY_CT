#include<iostream>
#include<queue>
#define MAX 105
#define INF 1e9
using namespace std;

struct POS{int y, x;};

int N;
int ey, ex; // 도착지
int P[MAX][MAX]; // 힘
int H[MAX][MAX]; // 높이
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void init(){
    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++) P[i][j] = INF; 
    }
}

void input(){
    cin >> N;
    cin >> ey >> ex;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++) cin >> H[i][j];
    }
}

void solve(){
    int ans = INF;

    // 1. 초기화 및 도착점 처리 (역방향 탐색)
    queue<POS> q;
    P[ey][ex] = 0;
    q.push({ey, ex});

    // 2. bfs
    while(!q.empty()){
        int y = q.front().y;
        int x = q.front().x;
        q.pop();

        // 출발지까지 도달하는 데 가장 적게 드는 힘
        if(y == 0 || x == 0 || y==N+1 || x==N+1) ans = min(ans, P[y][x]);

        int ny, nx, power;
        for(int d=0; d<4; d++){
            ny = y+dy[d];
            nx = x+dx[d];
            if(ny<0 || ny>N+1 || nx<0 || nx>N+1) continue; // 범위를 벗어나는 경우
            power = abs(H[y][x]-H[ny][nx]); // 높이 차이
            if(H[ny][nx] < H[y][x]) power *= power; // 내려가는 경우 (=실제로 올라온 경우)
            if(P[y][x]+power < P[ny][nx]){ // 더 적은 힘으로 갈 수 있는 경우
                P[ny][nx] = P[y][x]+power;
                q.push({ny, nx});
            }
        }
    }

    // 3. 정답 출력
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    init();
    input();
    solve();
}