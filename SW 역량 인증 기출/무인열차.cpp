#include<iostream>
#include<vector>
#define MAX 51
using namespace std;

int N, M;
int map[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};
vector<pair<int, int> > v[2];

void input(){
    cin >> N >> M;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++)
            cin >> map[i][j];
    }
}

void dfs(int y, int x, int n){
    map[y][x] = 2; // 방문 처리
    v[n].push_back({y, x});
    for (int d = 0; d < 4; d++){
        int ny = y + dy[d];
        int nx = x + dx[d];
        if(ny<0 || ny>=N || nx<0 || nx>=M || map[ny][nx]!=1) continue;
        dfs(ny, nx, n);
    }
}

int getMinModule(){
    int res = MAX*MAX, dist;
    for(auto p1 : v[0]){
        for(auto p2: v[1]){
            dist = abs(p1.first - p2.first) + abs(p1.second - p2.second) - 1;
            res = min(res, dist);
        }
    }
    return res;
}

void solve(){

    // 1. 두 생산라인 좌표 구하기
    int n = 0;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            if(map[i][j]!=1) continue;
            dfs(i, j, n++);
        }
    }

    // 2. 두 생산라인 연결에 필요한 최소 레일 모듈 개수 구하기
    cout << getMinModule();
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}