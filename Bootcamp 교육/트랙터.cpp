#include<iostream>
#include<cstring>
#define MAX 505
using namespace std;

int N;
int half;
int ans = 1e9;
int map[MAX][MAX];
bool visited[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input(){
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) cin >> map[i][j];
    }

    // 들판의 반
    half = (N*N+1)/2;
}

int dfs(int y, int x, int power){

    int res = 1;
    visited[y][x] = true;
    
    for(int d=0; d<4; d++){
        int ny = y+dy[d];
        int nx = x+dx[d];
        if(ny<0 || ny>=N || nx<0 || nx>=N) continue;
        
        int diff = abs(map[ny][nx]-map[y][x]); // 높이 차이
        if(power < diff || visited[ny][nx] || half < res) continue;
        res += dfs(ny, nx, power);
    }

    return res;
}

bool check(int D){
    
    // 1.초기화
    memset(visited, false, sizeof(visited));

    // 2. 모든 지점에서 출발 해봄
    for(int y=0; y<N; y++){
        for(int x=0; x<N; x++){

            if(visited[y][x]) continue;
            
            // 출발
            int cnt = dfs(y, x, D);
            if(half <= cnt) return true;
        }
    }
    return false;
}

void solve(){

    // 1. 들판의 반
    half = (N*N+1)/2;

    // 2. 이분탐색 (트랙터의 최소 성능)
    int low=0, mid, high=1e6;
    while(low <= high){
        mid = (low+high)/2;
        if(check(mid)) high = mid-1;
        else low = mid+1;
    }
    cout << low;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}