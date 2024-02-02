#include<iostream>
#include<algorithm>
#include<vector>
#define MAX 105
using namespace std;

int N, M, K;
bool map[MAX][MAX];
bool visited[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void paint(int sy, int sx, int ey, int ex){
    for(int i=sy; i>ey; i--){
        for(int j=sx; j<ex; j++) map[i][j] = true;
    }
}

void input(){
    cin >> N >> M >> K;
    int sy, sx, ey, ex;
    for(int i=0; i<K; i++){
        cin >> sx >> sy >> ex >> ey;
        paint(N-sy-1, sx, N-ey-1, ex); // 직사각형을 그림
    }
}

int dfs(int y, int x){
    int res = 1;
    visited[y][x] = true;
    for(int d=0; d<4; d++){
        int ny = y+dy[d];
        int nx = x+dx[d];
        if(ny<0 || ny>=N || nx<0 || nx>=M) continue; // 범위를 벗어나는 경우
        if(map[ny][nx] || visited[ny][nx]) continue; // 분리된 영역이 아니거나, 이미 방문한 경우
        res += dfs(ny, nx);
    }
    return res;
}

void solve(){
    int cnt = 0;
    vector<int> area;

    // 1. 분리된 영역 정보 구하기
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(map[i][j] || visited[i][j]) continue;
            area.push_back(dfs(i, j));
            cnt++;
        }
    }

    // 2. 넓이 정렬
    sort(area.begin(), area.end());

    // 3. 정답 출력
    cout << cnt << "\n";
    for(auto a : area) cout << a << " ";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}