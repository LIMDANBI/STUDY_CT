#include<iostream>
#include<cstring>
#define MAX 301
using namespace std;

int N, M;
bool allmelt;
int arr[MAX][MAX];
int copy_arr[MAX][MAX];
bool visited[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input(){
    cin >> N >> M;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++) cin >> arr[i][j];
    }
}

void dfs(int y, int x){
    visited[y][x] = true;
    for(int d=0; d<4; d++){
        int ny = y+dy[d];
        int nx = x+dx[d];
        if(ny<0 || ny>=N || nx<0 || nx>=M) continue;
        if(arr[ny][nx]==0 || visited[ny][nx]) continue;
        dfs(ny, nx);
    }
}

bool isend(){
    
    memset(visited, false, sizeof(visited)); // init

    int count = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(visited[i][j] || arr[i][j] == 0) continue;
            if(++count > 1) return true;
            dfs(i, j);
        }
    }
    if(count == 0) {
        allmelt = true;
        return true;
    }
    return false;
}

void melt(){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++) copy_arr[i][j] = arr[i][j];
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(arr[i][j] == 0) continue;

            int cnt = 0;
            for(int d=0; d<4; d++){
                int ny = i+dy[d];
                int nx = j+dx[d];
                if(ny<0 || ny>=N || nx<0 || nx>=M || arr[ny][nx]!=0) continue;
                cnt++;
            }
            copy_arr[i][j]-=min(cnt, copy_arr[i][j]);
        }
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++) arr[i][j] = copy_arr[i][j];
    }
}

void solution(){ // 빙산이 분리되는 최초의 시간(년) 출력 (빙산이 다 녹을 때까지 분리되지 않으면 0을 출력)
    
    int year = 0;
    while(++year){
        melt(); // 빙산이 녹음
        if(isend()) break; // 분리되었는지 체크
    }
    if(allmelt) cout << 0;
    else cout << year;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}