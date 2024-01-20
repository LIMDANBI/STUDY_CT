#include<iostream>
#include<vector>
#define MAX 51
#define INF (1<<30)
using namespace std;

struct POS{int y, x;};
vector<POS> v[3];

int N, M;
char map[MAX][MAX];
bool visited[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input(){
    cin >> N >> M;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++)
            cin >> map[i][j];
    }
}

void dfs(int y, int x, int idx){
    visited[y][x] = true;
    v[idx].push_back({y, x});

    for (int d = 0; d < 4; d++){
        int ny = y + dy[d];
        int nx = x + dx[d];
        if(ny<0 || ny>=N || nx<0 || nx>=M) continue;
        if(map[ny][nx]!='X' || visited[ny][nx]) continue;
        v[idx].push_back({ny, nx});
        dfs(ny, nx, idx);
    }
}

int distBetweenDot(){ // 각 점(x) 간 최단 거리
    int dist[3] = {INF, INF, INF};
    for (int i = 0; i < 3; i++){
        int j = (i + 1) % 3;
        for(POS p1 : v[i]){
            for(POS p2 : v[j])
                dist[i] = min(dist[i], abs(p1.y - p2.y) + abs(p1.x - p2.x) - 1);
        }
    }

    int max=dist[0], idx=0;
    for (int i = 1; i < 3; i++){
        if(max < dist[i]){
            max = dist[i];
            idx = i;
        }
    }

    int res = 0;
    dist[idx] = 0;
    for(int d : dist) res+=d;
    return res;
}

int distPointToDot(int y, int x){
    int dist[3] = {INF, INF, INF};
    visited[y][x] = true;
    for (int i = 0; i < 3; i++){
        for(POS p : v[i]){
            dist[i] = min(dist[i], abs(y - p.y) + abs(x - p.x));
        }
    }
    return (dist[0] + dist[1] + dist[2] - 2);
}

int ditFromPoint(){ // 특정 위치(.)에서 3영역 연결
    int res = INF;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            if(map[i][j] != '.' || visited[i][j]) continue;
            res = min(res, distPointToDot(i, j));
        }
    }
    return res;
}

void solve(){

    // 1. 'X' 좌표 저장
    int idx = 0;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            if(map[i][j] == 'X' && !visited[i][j]) dfs(i, j, idx++);
        }
    }

    // 2. 세 개의 점을 하나의 점으로 만드는 새로운 ‘X’의 최소 개수
    cout << min(distBetweenDot(), ditFromPoint());
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}